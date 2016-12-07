#include "serialreading.h"

SerialReading::SerialReading(QSerialPort *serial, RTDisplay *disp, QObject *parent) :
    QThread(parent), serial(serial), display(disp)
{
}
void SerialReading::run() {
    counter = 0;
    while(serial->isOpen()){
        this->readSerialValue();
    }
}
void SerialReading::readSerialValue()
{
//    QByteArray ba = serial->read(1);
    if (serial->read(1)[0] == '\xFF') {
        QByteArray b = serial->read(2);
        quint16 read = b[0] << 8 | b[1];
//        this->display->addValueAt(counter,(float) read);
        counter++;
        if (counter >= display->getSampleSize()) counter = 0;
    }
//        QByteArray ba = serial->readAll();
//        int i = 0;
//        while(ba[i] != '\xFF'){
//            i++;
//        }
//        for (i; i < ba.size(); i += 3) {
//            quint16 read = ba[i+1] << 8 | ba[i+2];
//            this->display->addValueAt(counter,(float) read);
//            counter++;
//            if (counter >= display->getWindow()) counter = 0;
//        }
}
