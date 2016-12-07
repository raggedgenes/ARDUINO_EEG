#ifndef SERIALREADING_H
#define SERIALREADING_H

#include <QThread>
#include <QSerialPort>
#include "Graphics/display.h"

class RTDisplay;

class SerialReading : public QThread
{
    Q_OBJECT
public:
    explicit SerialReading(QSerialPort *serial, RTDisplay *disp, QObject *parent = 0);
    float* reading;
signals:

public slots:

protected:
    void run();
private:
    void readSerialValue();
    int counter;
    QSerialPort *serial;
    RTDisplay *display;
};

#endif // SERIALREADING_H
