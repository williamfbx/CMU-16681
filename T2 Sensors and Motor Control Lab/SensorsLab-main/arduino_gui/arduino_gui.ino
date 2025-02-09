#include <Adafruit_Sensor.h>
#include <Adafruit_MPU6050.h>
#include <Wire.h>
#include <Servo.h>
#include <SharpIR.h>
#include <RoboClaw.h>
#include <AccelStepper.h>

#define SERIAL_PORT Serial

#define ADDRESS 0x80

// Motor & Encoder parameters
#define ENCODER_TICKS_PER_REV 3416
#define DEGREE_TO_TICKS (ENCODER_TICKS_PER_REV / 360.0)

// Position PID Tuning
#define Kp_pos 2.0
#define Ki_pos 0.5
#define Kd_pos 1.0

// Velocity PID Tuning
#define Kp_vel 1.0
#define Ki_vel 0.5
#define Kd_vel 0.25

// Maximum speed in encoder counts per second
#define MAX_QPPS 6718

// Pins
#define EN_StepperDriver 2
#define Stp_StepperDriver 3
#define Dir_StepperDriver 4
#define servoPin 6
#define PushButtonPin 7
#define PotentiometerPin A0
#define temperaturePin A1
#define ultrasonicPin A2
#define PushbuttonPin 7

AccelStepper stepper(AccelStepper::DRIVER, Stp_StepperDriver, Dir_StepperDriver);


// GLOBAL VARIABLES
// Note: GUI will execute commands sent by Arduino once every 2 intervals as it discards every other command due to serial buffer
unsigned long previousMillis = 0;
const unsigned long interval = 100;

Adafruit_MPU6050 mpu;
Servo servo;
RoboClaw roboclaw(&Serial1, 10000);

int servoAngle = 0;
int dc_motor_speed = 0;
int dc_motor_angle = 0;
double cm = 0.0;

int PotControlFlag = 0;
volatile int PotVal = 0;
volatile int globalStepperValue = 0;
volatile int globalStepperAngle = 0;

// Debounce variables
volatile unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 100;
const int incrementServo = 30;

bool isMoving = false;
uint32_t targetPosition = 0;

void setup() {
  SERIAL_PORT.begin(9600);
  Serial1.begin(38400);
  while (!SERIAL_PORT) {
    // Wait for the serial port to be ready
  }

  // IMU
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1)
      ;
  }

  // Servo Motor
  servo.attach(servoPin);
  servo.write(0);

  // Push Button
  attachInterrupt(digitalPinToInterrupt(PushbuttonPin), pushISR, FALLING);

  // DC Motor
  unsigned long startTime = millis();

  // Stepper
  pinMode(EN_StepperDriver, OUTPUT);
  digitalWrite(EN_StepperDriver, LOW);  // enable stepper(s)
  stepper.setMaxSpeed(2000);
  stepper.setAcceleration(1000);
  stepper.setSpeed(0);

  // // Initialize RoboClaw
  // if (!roboclaw.ReadError(ADDRESS)) {
  //   Serial.println("RoboClaw connected successfully.");
  // } else {
  //   Serial.println("Error detected in RoboClaw!");
  // }

  roboclaw.SetM1VelocityPID(ADDRESS, Kp_vel, Ki_vel, Kd_vel, MAX_QPPS);
  roboclaw.SetM1PositionPID(ADDRESS, Kp_pos, Ki_pos, Kd_pos, Kp_vel, Ki_vel, Kd_vel, MAX_QPPS);

  roboclaw.SpeedM1(ADDRESS, 0);
  // Serial.println("Motor stopped at startup.");

  SERIAL_PORT.print("Arduino Due Serial is ready!;");
}


void loop() {
  if (isMoving) {
    uint32_t currentPos = roboclaw.ReadEncM1(ADDRESS);
    if (abs((int32_t)(currentPos - targetPosition)) <= 15) {  // Position tolerance
      roboclaw.SpeedM1(ADDRESS, 0);                           // Stop motor
      // Serial.println("Target position reached.");
      isMoving = false;  // Reset movement flag
    }
  }

  // Check if data is available to read from the serial port
  if (SERIAL_PORT.available() > 0) {
    // Read the incoming string
    String receivedString = SERIAL_PORT.readStringUntil(';');

    // // Echo the string back to the serial port
    // SERIAL_PORT.print("Arduino received command: ");
    // SERIAL_PORT.print(receivedString);
    // SERIAL_PORT.print(";");
    // SERIAL_PORT.flush();

    if (receivedString.length() > 1) {
      char commandType = receivedString.charAt(0);

      String valueString = receivedString.substring(1);
      if (isNumeric(valueString)) {
        int commandValue = valueString.toInt();
        handleCommand(commandType, commandValue);
      }
    }
  }

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    timerCallback();
  }

  stepperCallback();
}

void timerCallback() {
  // SERIAL_PORT.print("Timer callback executed at: ");
  // SERIAL_PORT.print(previousMillis);
  // SERIAL_PORT.print(";");

  // A "$" is used to indicate the serial port return is a command
  String serialReturn;
  serialReturn.concat("$");

  int servoMotorState = servoMotorStateCallback();
  serialReturn.concat(servoMotorState);
  serialReturn.concat(",");

  int stepperMotorState = stepperMotorStateCallback();
  serialReturn.concat(stepperMotorState);
  serialReturn.concat(",");

  int velDCMotorState = velDCMotorStateCallback();
  serialReturn.concat(velDCMotorState);
  serialReturn.concat(",");

  int angleDCMotorState = angleDCMotorStateCallback();
  serialReturn.concat(angleDCMotorState);
  serialReturn.concat(",");

  int potentiometerSensorState = potentiometerSensorCallback();
  serialReturn.concat(potentiometerSensorState);
  serialReturn.concat(",");

  double imuSensorState = imuSensorCallback();
  serialReturn.concat(imuSensorState);
  serialReturn.concat(",");

  double temperatureSensorState = temperatureSensorCallback();
  serialReturn.concat(temperatureSensorState);
  serialReturn.concat(",");

  int ultrasonicSensorState = ultrasonicSensorCallback();
  serialReturn.concat(ultrasonicSensorState);
  serialReturn.concat(",");

  double electricalInput = analogRead(ultrasonicPin);
  double transferFunctionState = transferFunctionCallback(electricalInput);
  double electricalVoltage = analogRead(ultrasonicPin) * (5.0 / 1023.0);

  serialReturn.concat(electricalVoltage);
  serialReturn.concat(":");
  serialReturn.concat(transferFunctionState);

  SERIAL_PORT.print(serialReturn);
  SERIAL_PORT.print(";");
}


void handleCommand(char commandType, int value) {
  switch (commandType) {
    case 'R':
      servoMotorController(value);
      break;
    case 'S':
      stepperMotorController(value);
      break;
    case 'V':
      velDCMotorController(value);
      break;
    case 'A':
      angleDCMotorController(value);
      break;
    case 'B':
      buttonStepperMotorController(value);
      break;
    default:
      break;
  }
}


bool isNumeric(String str) {
  if (str.length() == 0) return false;

  int startIndex = 0;

  if (str[0] == '-') {
    if (str.length() == 1) return false;
    startIndex = 1;
  }

  for (unsigned int i = startIndex; i < str.length(); i++) {
    if (!isDigit(str[i])) {
      return false;
    }
  }

  return true;
}


// CONTROLLER FUNCTIONS

void servoMotorController(int control) {
  /*
  INPUT: Integer in min/max range of 0 to 180 corresponding to desired angle
  OUTPUT: Void
  */

  SERIAL_PORT.print("Servo motor controller received command: ");
  SERIAL_PORT.print(control);
  SERIAL_PORT.print(";");

  // TODO: IMPLEMENT FUNCTION BELOW
  servoAngle = control;
  servo.write(servoAngle);
}

void stepperMotorController(int control) {
  /*
  INPUT: Integer in min/max range of -180 to 180 corresponding to desired angle
  OUTPUT: Void
  */

  SERIAL_PORT.print("Stepper motor controller received command: ");
  SERIAL_PORT.print(control);
  SERIAL_PORT.print(";");

  // TODO: IMPLEMENT FUNCTION BELOW
  if (PotControlFlag == 0) {
    globalStepperValue = map(control, -180, 180, -1600, 1600);
    globalStepperAngle = control;
  }
}

void velDCMotorController(int control) {
  /*
  INPUT: Integer in min/max range of -118 to 118 corresponding to desired RPM
  OUTPUT: Void
  */

  SERIAL_PORT.print("Velocity DC motor controller received command: ");
  SERIAL_PORT.print(control);
  SERIAL_PORT.print(";");

  // TODO: IMPLEMENT FUNCTION BELOW
  // Set motor velocity (positive for forward, negative for reverse)
  int dc_motor_speed = (control / 118.0) * 100.0;
  int encoderSpeed = (dc_motor_speed * MAX_QPPS) / 100;  // Scale input speed (user enters 0-100%)
  roboclaw.SpeedM1(ADDRESS, encoderSpeed);
}

void angleDCMotorController(int control) {
  /*
  INPUT: Integer in min/max range of -360 to 360 corresponding to desired angle
  OUTPUT: Void
  */

  // SERIAL_PORT.print("Angle DC motor controller received command: ");
  // SERIAL_PORT.print(control);
  // SERIAL_PORT.print(";");

  // TODO: IMPLEMENT FUNCTION BELOW
  uint32_t currentPos = roboclaw.ReadEncM1(ADDRESS);
  targetPosition = currentPos + (control * DEGREE_TO_TICKS);

  // Serial.print("Moving motor to position: ");
  // Serial.println(targetPosition);

  roboclaw.SpeedAccelDeccelPositionM1(ADDRESS, 10000, MAX_QPPS, 10000, targetPosition, 0);

  isMoving = true;  // Set flag for movement tracking
}

void buttonStepperMotorController(int control) {
  /*
  INPUT: Boolean with 0 indicating GUI control and 1 indicating potentiometer control
  OUTPUT: Void
  */

  SERIAL_PORT.print("Button controller received command: ");
  SERIAL_PORT.print(control);
  SERIAL_PORT.print(";");

  // TODO: IMPLEMENT FUNCTION BELOW
  PotControlFlag = control;
}


// CALLBACK FUNCTIONS
int servoMotorStateCallback() {
  /*
  INPUT: Void
  OUTPUT: Integer in min/max range of 0 to 180 corresponding to servo motor angle
  */

  // TODO: IMPLEMENT FUNCTION BELOW
  return servoAngle;
}

int stepperMotorStateCallback() {
  /*
  INPUT: Void
  OUTPUT: Integer in min/max range of -180 to 180 corresponding to stepper motor angle
  */

  // TODO: IMPLEMENT FUNCTION BELOW

  return globalStepperAngle;
}

int velDCMotorStateCallback() {
  /*
  INPUT: Void
  OUTPUT: Integer in min/max range of -118 to 118 corresponding to DC motor RPM
  */

  // TODO: IMPLEMENT FUNCTION BELOW

  int speed = roboclaw.ReadSpeedM1(ADDRESS);
  speed = speed * 118 / 6718;

  return speed;
}

int angleDCMotorStateCallback() {
  /*
  INPUT: Void
  OUTPUT: Integer in min/max range of -360 to 360 corresponding to DC motor angle
  */

  // TODO: IMPLEMENT FUNCTION BELOW

  int enc = roboclaw.ReadEncM1(ADDRESS);
  int angle = (enc * 360) / 3416;
  angle = angle % 360;

  return angle;
}

int potentiometerSensorCallback() {
  /*
  INPUT: Void
  OUTPUT: Integer corresponding to potentiometer reading
  */

  // TODO: IMPLEMENT FUNCTION BELOW
  PotVal = analogRead(PotentiometerPin);

  if (PotControlFlag == 1) {
    globalStepperValue = map(PotVal, 0, 1022, -1600, 1600);
    globalStepperAngle = map(globalStepperValue, -1600, 1600, -180, 180);
  }

  return PotVal;
}

double imuSensorCallback() {
  /*
  INPUT: Void
  OUTPUT: Double corresponding to sensed IMU pitch reading
  */

  // TODO: IMPLEMENT FUNCTION BELOW
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Pitch using accel data
  double pitchAccel = atan2(a.acceleration.x, a.acceleration.z) * 180 / PI;

  return pitchAccel;
}

double temperatureSensorCallback() {
  /*
  INPUT: Void
  OUTPUT: Double corresponding to temperature reading (degree celsius)
  */

  // TODO: IMPLEMENT FUNCTION BELOW
  int reading = analogRead(temperaturePin);
  double voltage = reading * 3.3;
  voltage /= 1024.0;

  double temperatureC = (voltage - 0.5) * 100;

  return temperatureC;
}

int ultrasonicSensorCallback() {
  /*
  INPUT: Void
  OUTPUT: Integer corresponding to ultrasonic reading (cm)
  */

  // TODO: IMPLEMENT FUNCTION BELOW
  cm = analogRead(ultrasonicPin);
  cm = transferFunctionCallback(cm);

  return int(cm);
}

// OTHER FUNCTIONS
void pushISR() {
  /*
  INPUT: Void
  OUTPUT: Void
  */

  // TODO: IMPLEMENT FUNCTION BELOW
  unsigned long currentTime = millis();
  if ((currentTime - lastDebounceTime) > debounceDelay) {
    servoAngle += incrementServo;
    if (servoAngle > 180) {
      servoAngle = 0;
    }
    lastDebounceTime = currentTime;
    servo.write(servoAngle);
  }
}

double transferFunctionCallback(double electricalInput) {
  /*
  INPUT: Double corresponding to electrical input voltage
  OUTPUT: Double corresponding to ultrasonic reading (cm)
  */

  // TODO: IMPLEMENT FUNCTION BELOW
  double val = electricalInput * 0.498 * 2.54;

  return val;
}

void stepperCallback() {
  /*
  INPUT: Void
  OUTPUT: Void
  */

  // TODO: IMPLEMENT FUNCTION BELOW
  stepper.moveTo(globalStepperValue);
  stepper.run();
}
