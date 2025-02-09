/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QGroupBox *groupBox;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSlider *servo_slider;
    QGroupBox *groupBox_4;
    QHBoxLayout *horizontalLayout_3;
    QLCDNumber *servo_angle_state;
    QGroupBox *groupBox_5;
    QHBoxLayout *horizontalLayout_4;
    QLCDNumber *stepper_angle_state;
    QGroupBox *groupBox_6;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_3;
    QLineEdit *dc_vel_textbox;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_4;
    QLineEdit *dc_angle_textbox;
    QGroupBox *groupBox_7;
    QHBoxLayout *horizontalLayout_12;
    QLCDNumber *dc_rpm_state;
    QGroupBox *groupBox_13;
    QHBoxLayout *horizontalLayout_13;
    QLCDNumber *dc_angle_state;
    QGroupBox *groupBox_12;
    QVBoxLayout *verticalLayout_2;
    QRadioButton *stepper_mode_button;
    QHBoxLayout *horizontalLayout_16;
    QLabel *label_2;
    QSlider *stepper_slider;
    QGroupBox *groupBox_14;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox_10;
    QHBoxLayout *horizontalLayout_7;
    QLCDNumber *potentiometer_sensor_state;
    QGroupBox *groupBox_11;
    QHBoxLayout *horizontalLayout_8;
    QLCDNumber *IMU_sensor_state;
    QGroupBox *groupBox_8;
    QHBoxLayout *horizontalLayout_5;
    QLCDNumber *temperature_sensor_state;
    QGroupBox *groupBox_9;
    QHBoxLayout *horizontalLayout_6;
    QLCDNumber *ultrasonic_sensor_state;
    QGroupBox *groupBox_22;
    QVBoxLayout *verticalLayout_4;
    QCustomPlot *transferFunctionPlot;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName("Dialog");
        Dialog->resize(1280, 1024);
        Dialog->setAutoFillBackground(false);
        groupBox = new QGroupBox(Dialog);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(10, 20, 641, 471));
        QFont font;
        font.setPointSize(13);
        groupBox->setFont(font);
        groupBox->setAlignment(Qt::AlignmentFlag::AlignCenter);
        groupBox_2 = new QGroupBox(groupBox);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(10, 40, 421, 91));
        groupBox_2->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);
        horizontalLayout = new QHBoxLayout(groupBox_2);
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(groupBox_2);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        servo_slider = new QSlider(groupBox_2);
        servo_slider->setObjectName("servo_slider");
        servo_slider->setMinimum(0);
        servo_slider->setMaximum(180);
        servo_slider->setOrientation(Qt::Orientation::Horizontal);

        horizontalLayout->addWidget(servo_slider);

        groupBox_4 = new QGroupBox(groupBox);
        groupBox_4->setObjectName("groupBox_4");
        groupBox_4->setGeometry(QRect(440, 40, 191, 91));
        groupBox_4->setAlignment(Qt::AlignmentFlag::AlignCenter);
        horizontalLayout_3 = new QHBoxLayout(groupBox_4);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        servo_angle_state = new QLCDNumber(groupBox_4);
        servo_angle_state->setObjectName("servo_angle_state");
        servo_angle_state->setProperty("intValue", QVariant(0));

        horizontalLayout_3->addWidget(servo_angle_state);

        groupBox_5 = new QGroupBox(groupBox);
        groupBox_5->setObjectName("groupBox_5");
        groupBox_5->setGeometry(QRect(440, 140, 191, 91));
        groupBox_5->setAlignment(Qt::AlignmentFlag::AlignCenter);
        horizontalLayout_4 = new QHBoxLayout(groupBox_5);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        stepper_angle_state = new QLCDNumber(groupBox_5);
        stepper_angle_state->setObjectName("stepper_angle_state");

        horizontalLayout_4->addWidget(stepper_angle_state);

        groupBox_6 = new QGroupBox(groupBox);
        groupBox_6->setObjectName("groupBox_6");
        groupBox_6->setGeometry(QRect(10, 280, 421, 181));
        groupBox_6->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);
        verticalLayout = new QVBoxLayout(groupBox_6);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName("horizontalLayout_10");
        label_3 = new QLabel(groupBox_6);
        label_3->setObjectName("label_3");

        horizontalLayout_10->addWidget(label_3);

        dc_vel_textbox = new QLineEdit(groupBox_6);
        dc_vel_textbox->setObjectName("dc_vel_textbox");

        horizontalLayout_10->addWidget(dc_vel_textbox);


        verticalLayout->addLayout(horizontalLayout_10);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName("horizontalLayout_11");
        label_4 = new QLabel(groupBox_6);
        label_4->setObjectName("label_4");

        horizontalLayout_11->addWidget(label_4);

        dc_angle_textbox = new QLineEdit(groupBox_6);
        dc_angle_textbox->setObjectName("dc_angle_textbox");

        horizontalLayout_11->addWidget(dc_angle_textbox);


        verticalLayout->addLayout(horizontalLayout_11);

        groupBox_7 = new QGroupBox(groupBox);
        groupBox_7->setObjectName("groupBox_7");
        groupBox_7->setGeometry(QRect(440, 250, 191, 91));
        groupBox_7->setAlignment(Qt::AlignmentFlag::AlignCenter);
        horizontalLayout_12 = new QHBoxLayout(groupBox_7);
        horizontalLayout_12->setObjectName("horizontalLayout_12");
        dc_rpm_state = new QLCDNumber(groupBox_7);
        dc_rpm_state->setObjectName("dc_rpm_state");

        horizontalLayout_12->addWidget(dc_rpm_state);

        groupBox_13 = new QGroupBox(groupBox);
        groupBox_13->setObjectName("groupBox_13");
        groupBox_13->setGeometry(QRect(440, 350, 191, 91));
        groupBox_13->setAlignment(Qt::AlignmentFlag::AlignCenter);
        horizontalLayout_13 = new QHBoxLayout(groupBox_13);
        horizontalLayout_13->setObjectName("horizontalLayout_13");
        dc_angle_state = new QLCDNumber(groupBox_13);
        dc_angle_state->setObjectName("dc_angle_state");

        horizontalLayout_13->addWidget(dc_angle_state);

        groupBox_12 = new QGroupBox(groupBox);
        groupBox_12->setObjectName("groupBox_12");
        groupBox_12->setGeometry(QRect(10, 140, 421, 131));
        groupBox_12->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);
        verticalLayout_2 = new QVBoxLayout(groupBox_12);
        verticalLayout_2->setObjectName("verticalLayout_2");
        stepper_mode_button = new QRadioButton(groupBox_12);
        stepper_mode_button->setObjectName("stepper_mode_button");

        verticalLayout_2->addWidget(stepper_mode_button, 0, Qt::AlignmentFlag::AlignHCenter);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName("horizontalLayout_16");
        label_2 = new QLabel(groupBox_12);
        label_2->setObjectName("label_2");

        horizontalLayout_16->addWidget(label_2);

        stepper_slider = new QSlider(groupBox_12);
        stepper_slider->setObjectName("stepper_slider");
        stepper_slider->setTabletTracking(false);
        stepper_slider->setAcceptDrops(false);
        stepper_slider->setAutoFillBackground(false);
        stepper_slider->setMinimum(-180);
        stepper_slider->setMaximum(180);
        stepper_slider->setValue(0);
        stepper_slider->setSliderPosition(0);
        stepper_slider->setOrientation(Qt::Orientation::Horizontal);

        horizontalLayout_16->addWidget(stepper_slider);


        verticalLayout_2->addLayout(horizontalLayout_16);

        groupBox_14 = new QGroupBox(Dialog);
        groupBox_14->setObjectName("groupBox_14");
        groupBox_14->setGeometry(QRect(670, 20, 241, 471));
        groupBox_14->setFont(font);
        groupBox_14->setAlignment(Qt::AlignmentFlag::AlignCenter);
        verticalLayout_3 = new QVBoxLayout(groupBox_14);
        verticalLayout_3->setObjectName("verticalLayout_3");
        groupBox_10 = new QGroupBox(groupBox_14);
        groupBox_10->setObjectName("groupBox_10");
        groupBox_10->setAlignment(Qt::AlignmentFlag::AlignCenter);
        horizontalLayout_7 = new QHBoxLayout(groupBox_10);
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        potentiometer_sensor_state = new QLCDNumber(groupBox_10);
        potentiometer_sensor_state->setObjectName("potentiometer_sensor_state");
        potentiometer_sensor_state->setProperty("intValue", QVariant(0));

        horizontalLayout_7->addWidget(potentiometer_sensor_state);


        verticalLayout_3->addWidget(groupBox_10);

        groupBox_11 = new QGroupBox(groupBox_14);
        groupBox_11->setObjectName("groupBox_11");
        groupBox_11->setAlignment(Qt::AlignmentFlag::AlignCenter);
        horizontalLayout_8 = new QHBoxLayout(groupBox_11);
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        IMU_sensor_state = new QLCDNumber(groupBox_11);
        IMU_sensor_state->setObjectName("IMU_sensor_state");
        IMU_sensor_state->setProperty("intValue", QVariant(0));

        horizontalLayout_8->addWidget(IMU_sensor_state);


        verticalLayout_3->addWidget(groupBox_11);

        groupBox_8 = new QGroupBox(groupBox_14);
        groupBox_8->setObjectName("groupBox_8");
        groupBox_8->setAlignment(Qt::AlignmentFlag::AlignCenter);
        horizontalLayout_5 = new QHBoxLayout(groupBox_8);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        temperature_sensor_state = new QLCDNumber(groupBox_8);
        temperature_sensor_state->setObjectName("temperature_sensor_state");
        temperature_sensor_state->setProperty("intValue", QVariant(0));

        horizontalLayout_5->addWidget(temperature_sensor_state);


        verticalLayout_3->addWidget(groupBox_8);

        groupBox_9 = new QGroupBox(groupBox_14);
        groupBox_9->setObjectName("groupBox_9");
        groupBox_9->setAlignment(Qt::AlignmentFlag::AlignCenter);
        horizontalLayout_6 = new QHBoxLayout(groupBox_9);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        ultrasonic_sensor_state = new QLCDNumber(groupBox_9);
        ultrasonic_sensor_state->setObjectName("ultrasonic_sensor_state");

        horizontalLayout_6->addWidget(ultrasonic_sensor_state);


        verticalLayout_3->addWidget(groupBox_9);

        groupBox_22 = new QGroupBox(Dialog);
        groupBox_22->setObjectName("groupBox_22");
        groupBox_22->setGeometry(QRect(10, 500, 901, 311));
        groupBox_22->setFont(font);
        groupBox_22->setAlignment(Qt::AlignmentFlag::AlignCenter);
        verticalLayout_4 = new QVBoxLayout(groupBox_22);
        verticalLayout_4->setObjectName("verticalLayout_4");
        transferFunctionPlot = new QCustomPlot(groupBox_22);
        transferFunctionPlot->setObjectName("transferFunctionPlot");

        verticalLayout_4->addWidget(transferFunctionPlot);


        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Dialog", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Dialog", "Motor Control", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("Dialog", "RC Servo Motor", nullptr));
        label->setText(QCoreApplication::translate("Dialog", "Angle (degrees)", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("Dialog", "RC Servo Motor Angle", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("Dialog", "Stepper Motor Angle", nullptr));
        groupBox_6->setTitle(QCoreApplication::translate("Dialog", "DC Motor", nullptr));
        label_3->setText(QCoreApplication::translate("Dialog", "Velocity (RPM)", nullptr));
        label_4->setText(QCoreApplication::translate("Dialog", "Position (degrees)", nullptr));
        groupBox_7->setTitle(QCoreApplication::translate("Dialog", "DC Motor RPM", nullptr));
        groupBox_13->setTitle(QCoreApplication::translate("Dialog", "DC Motor Angle", nullptr));
        groupBox_12->setTitle(QCoreApplication::translate("Dialog", "Stepper Motor", nullptr));
        stepper_mode_button->setText(QCoreApplication::translate("Dialog", "Switch Mode", nullptr));
        label_2->setText(QCoreApplication::translate("Dialog", "Angle (degrees)", nullptr));
        groupBox_14->setTitle(QCoreApplication::translate("Dialog", "Sensor Readings", nullptr));
        groupBox_10->setTitle(QCoreApplication::translate("Dialog", "Potentiometer Sensor", nullptr));
        groupBox_11->setTitle(QCoreApplication::translate("Dialog", "IMU Sensor Pitch Angle", nullptr));
        groupBox_8->setTitle(QCoreApplication::translate("Dialog", "Temperature (Celcius)", nullptr));
        groupBox_9->setTitle(QCoreApplication::translate("Dialog", "Ultrasonic Sensor (cm)", nullptr));
        groupBox_22->setTitle(QCoreApplication::translate("Dialog", "Transfer Function", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
