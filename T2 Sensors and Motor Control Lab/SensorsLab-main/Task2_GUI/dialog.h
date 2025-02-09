#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QtWidgets>

QT_BEGIN_NAMESPACE
namespace Ui {
class Dialog;
}
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:

    void updateArduino(QString);

    void readSerial();

    void on_servo_slider_valueChanged(int value);

    void on_stepper_slider_valueChanged(int value);

    void on_stepper_mode_button_toggled(bool checked);

    void parseCallbackCommands(QString command);

    void updatePlot();

    int filterMean(std::vector<int>&);

private:
    Ui::Dialog *ui;
    QSerialPort *arduino;

    // Arduino Due setup
    static const quint16 arduino_due_vendor_id = 9025;
    static const quint16 arduino_due_product_id = 61;
    QString arduino_port_name;
    bool arduino_is_available;

    QByteArray serialData;
    QString serialBuffer;
    QString parsed_data;

    QTimer *dataTimer;
    QVector<double> xData, yData;

    double transferFunctionInput;
    double transferFunctionOutput;

    void onDCPosCommentSubmitted();
    void onDCVelCommentSubmitted();

    std::vector<int> ultrasonicReadings;
};
#endif // DIALOG_H
