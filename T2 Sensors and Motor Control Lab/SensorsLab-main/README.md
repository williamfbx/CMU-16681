# SensorsLab

## Hardware Components

- Arduino Board (Arduino Due recommended)
- MPU6050 IMU Sensor
- Servo Motor
- DC Motor with RoboClaw Motor Controller
- Stepper Motor with Driver
- Potentiometer
- Temperature Sensor
- Ultrasonic Sensor
- Push Button

## Connections and Pinouts

| Component                   | Arduino Pin                 | Notes                                                           |
|-----------------------------|-----------------------------|-----------------------------------------------------------------|
| **Stepper Driver Enable**   | `EN_StepperDriver = 2`      | Connected to the stepper driver's Enable pin                    |
| **Stepper Driver Step**     | `Stp_StepperDriver = 3`     | Connected to the stepper driver's Step pin                      |
| **Stepper Driver Dir**      | `Dir_StepperDriver = 4`     | Connected to the stepper driver's Direction pin                 |
| **Servo**                   | `servoPin = 6`              | PWM-capable pin                                                 |
| **Push Button**             | `PushButtonPin = 7`         | Digital input (external interrupt pin on Arduino Due)           |
| **Potentiometer**           | `PotentiometerPin = A0`     | Analog input                                                    |
| **Temperature Sensor**      | `temperaturePin = A1`       | Analog input                                       |
| **Ultrasonic Sensor**       | `ultrasonicPin = A2`        | Analog input                                                    |
| **RoboClaw**                | TX1/RX1 (Serial1 on the Due)| TX1 → RoboClaw RX, RX1 → RoboClaw TX (check Arduino Due pinout) |
| **Motor/Encoders**          | RoboClaw external terminals | As per RoboClaw documentation for motor power and encoder lines |

Make sure to provide a proper external power supply for the motors since the Arduino 5V/3.3V rail typically cannot supply enough current for motors.

## Installation and Setup

1. Clone or Download this repository.
2. Navigate to the `arduino_gui` folder and open `arduino_gui.ino` file in the Arduino IDE.
3. Select your board and port under Tools > Board (choose "Arduino Due") and Tools > Port.
4. Upload the code to the Arduino Due.
5. Navigate to the `Task2_GUI/build/Desktop_Qt_6_8_1-Debug/` directory and run the `Task2_GUI` executable file.
   
## Using the GUI

- The GUI will display real-time readings from all connected sensors.
- Control the motors via the provided sliders.
- The stepper motor can also be controlled by the potentiometer when in switch mode.
- The servo motor can also be controlled using the push button, which triggers an interrupt.

