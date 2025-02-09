/*
The following starter template is adapted from the following repos, which is under a GNU GPLv3.0 license:
https://github.com/vannevar-morgan/Qt-RGB-LED
https://github.com/vannevar-morgan/Qt-Temperature-Sensor
*/

#include "dialog.h"
#include "ui_dialog.h"
#include "qcustomplot.h"

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QtWidgets>

#include <vector>

#include <iostream>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    arduino_is_available = false;
    arduino_port_name = "";
    arduino = new QSerialPort(this);

    serialBuffer = "";
    parsed_data = "";

    transferFunctionInput = 0;
    transferFunctionOutput = 0;

    // Initialize transfer function plot
    QCustomPlot *plot = ui->transferFunctionPlot;
    plot->addGraph();

    plot->xAxis->setLabel("Input Voltage (V)");
    plot->yAxis->setLabel("Output Reading (cm)");

    plot->xAxis->setRange(0, 5);
    plot->yAxis->setRange(0, 1000);

    dataTimer = new QTimer(this);
    connect(dataTimer, &QTimer::timeout, this, &Dialog::updatePlot);
    dataTimer->start(100);

    connect(ui->dc_angle_textbox, &QLineEdit::returnPressed, this, &Dialog::onDCPosCommentSubmitted);
    connect(ui->dc_vel_textbox, &QLineEdit::returnPressed, this, &Dialog::onDCVelCommentSubmitted);

    /*
    // Finds product and vendor ID of Arduino Due
    qDebug() << "Number of available ports: " << QSerialPortInfo::availablePorts().length();
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
        qDebug() << "Has vendor ID: " << serialPortInfo.hasVendorIdentifier();
        if(serialPortInfo.hasVendorIdentifier()){
            qDebug() << "Vendor ID: " << serialPortInfo.vendorIdentifier();
        }
        qDebug() << "Has Product ID: " << serialPortInfo.hasProductIdentifier();
        if(serialPortInfo.hasProductIdentifier()){
            qDebug() << "Product ID: " << serialPortInfo.productIdentifier();
        }
    }
    */

    // Connects to Arduino via serial port
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
        if(serialPortInfo.hasVendorIdentifier() && serialPortInfo.hasProductIdentifier()){
            if(serialPortInfo.vendorIdentifier() == arduino_due_vendor_id){
                if(serialPortInfo.productIdentifier() == arduino_due_product_id){
                    arduino_port_name = serialPortInfo.portName();
                    arduino_is_available = true;
                }
            }
        }
    }

    if(arduino_is_available){
        // Open and configure the serialport
        arduino->setPortName(arduino_port_name);
        arduino->open(QSerialPort::ReadWrite);
        arduino->setBaudRate(QSerialPort::Baud9600);
        arduino->setDataBits(QSerialPort::Data8);
        arduino->setParity(QSerialPort::NoParity);
        arduino->setStopBits(QSerialPort::OneStop);
        arduino->setFlowControl(QSerialPort::NoFlowControl);
        QObject::connect(arduino, SIGNAL(readyRead()), this, SLOT(readSerial()));
        qDebug() << "Connected to Arduino!";
    }
    else{
        // Give error message if not available
        QMessageBox::warning(this, "Port error", "Couldn't find the Arduino!");
    }
}

Dialog::~Dialog()
{
    if(arduino->isOpen()){
        arduino->close();
    }
    delete ui;
}

void Dialog::updateArduino(QString command)
{
    if(arduino->isWritable()){
        arduino->write(command.toStdString().c_str());
    }else{
        qDebug() << "Couldn't write to serial!";
    }
}

void Dialog::readSerial()
{
    QStringList buffer_split = serialBuffer.split(";");

    if (buffer_split.length() < 3) {
        serialData = arduino->readAll();
        serialBuffer = serialBuffer + QString::fromStdString(serialData.toStdString());
        serialData.clear();
    }
    else{
        serialBuffer = "";
        parsed_data = buffer_split[1];
        // qDebug() << parsed_data << "\n";

        // If the parsed data has a $ sign at index 0, then recognize it as a callback command
        if (parsed_data.at(0) == '$') {
            parseCallbackCommands(parsed_data);
        }
        else {
            // qDebug() << parsed_data << "\n";
        }
    }
}


void Dialog::updatePlot()
{
    xData.prepend(transferFunctionInput);
    yData.prepend(transferFunctionOutput);

    while (xData.size() > 1000) {
        xData.removeLast();
        yData.removeLast();
    }

    QCustomPlot *plot = ui->transferFunctionPlot;
    plot->graph(0)->setData(xData, yData);
    plot->replot();
}


void Dialog::parseCallbackCommands(QString command)
{
    QString processedCommand = command.mid(1);
    qDebug() << "Processed command: " << processedCommand;

    // Only update GUI if processed command has 9 elements
    QStringList processedCommand_split = processedCommand.split(",");
    // qDebug() << "Command length: " << processedCommand_split.length();

    if (processedCommand_split.length() == 9) {

        // Motor states
        QString servoMotorState = processedCommand_split.at(0);
        QString stepperMotorState = processedCommand_split.at(1);
        QString velDCMotorState = processedCommand_split.at(2);
        QString angleDCMotorState = processedCommand_split.at(3);

        ui->servo_angle_state->display(servoMotorState);
        ui->stepper_angle_state->display(stepperMotorState);
        ui->dc_rpm_state->display(velDCMotorState);
        ui->dc_angle_state->display(angleDCMotorState);

        // Sensor states
        QString potentiometerSensorState = processedCommand_split.at(4);
        QString imuSensorState = processedCommand_split.at(5);
        QString temperatureSensorState = processedCommand_split.at(6);
        QString ultrasonicSensorState = processedCommand_split.at(7);

        // Filtering for ultrasonic sensor
        int ultrasonicReading = ultrasonicSensorState.toInt();
        if (ultrasonicReadings.size() >= 5) {
            ultrasonicReadings.erase(ultrasonicReadings.begin());
        }
        ultrasonicReadings.push_back(ultrasonicReading);
        int filteredUltrasonicValue = filterMean(ultrasonicReadings);

        ui->potentiometer_sensor_state->display(potentiometerSensorState);
        ui->IMU_sensor_state->display(imuSensorState);
        ui->temperature_sensor_state->display(temperatureSensorState);
        ui->ultrasonic_sensor_state->display(filteredUltrasonicValue);
        // ui->ultrasonic_sensor_state->display(ultrasonicSensorState);

        // Transfer function
        QString transferFunctionState = processedCommand_split.at(8);
        QStringList transferFunctionState_split = transferFunctionState.split(":");

        QString transferFunctionInputString = transferFunctionState_split.at(0);
        QString transferFunctionOutputString = transferFunctionState_split.at(1);

        transferFunctionInput = transferFunctionInputString.toDouble();
        transferFunctionOutput = transferFunctionOutputString.toDouble();
    }
}


void Dialog::on_servo_slider_valueChanged(int value)
{
    QString command = QString("R%1;").arg(value);
    qDebug() << "Slider value:" << value << "Command:" << command;
    updateArduino(command);
}


void Dialog::on_stepper_slider_valueChanged(int value)
{
    QString command = QString("S%1;").arg(value);
    qDebug() << "Slider value:" << value << "Command:" << command;
    updateArduino(command);
}

void Dialog::on_stepper_mode_button_toggled(bool checked)
{
    QString command = QString("B%1;").arg(checked);
    qDebug() << "Button value:" << checked << "Command:" << command;
    updateArduino(command);
}

void Dialog::onDCVelCommentSubmitted()
{
    QString comment = ui->dc_vel_textbox->text();

    QString command = QString("V%1;").arg(comment);
    qDebug() << "Text box value:" << comment << "Command:" << command;
    updateArduino(command);

    ui->dc_vel_textbox->clear();
}

void Dialog::onDCPosCommentSubmitted()
{
    QString comment = ui->dc_angle_textbox->text();

    QString command = QString("A%1;").arg(comment);
    qDebug() << "Text box value:" << comment << "Command:" << command;
    updateArduino(command);

    ui->dc_angle_textbox->clear();
}

int Dialog::filterMean(std::vector<int>& arr) {
    if(arr.empty()) {
        return 0;
    }

    int sum = 0;

    for (size_t i = 1; i < arr.size(); i++) {
        sum += arr[i];
    }

    return sum / arr.size();
}
