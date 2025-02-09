#include "dialog.h"
#include "qcustomplot.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    w.setFixedSize(940, 850);
    w.setWindowTitle("Sensors & Motor Lab Controller");
    w.show();
    return a.exec();
}
