#ifndef EEGREADER_H
#define EEGREADER_H

#include <QObject>
#include <QSerialPort>
#include <QWidget>
#include <QtWidgets>
#include "fftw3.h"
#include <Analysis/scalogram.h>
#include <Graphics/spectrograph.h>
#include "Graphics/display.h"
#include "Graphics/monitor.h"
#include "Utils/serialreading.h"

class RTDisplay;
class SerialReading;
class Monitor;

class EEGReader : public QObject
{
    Q_OBJECT
public:
    explicit EEGReader(QSerialPort *serial, RTDisplay *disp, Monitor *mon, QObject *parent = 0);
    ~EEGReader();
    void update();
    double *getPowerSpectra();
    QImage *getWavelet();


    RTDisplay *getDisplay() const;
    void setDisplay(RTDisplay *value);

    Monitor *getMonitor() const;
    void setMonitor(Monitor *value);

    void startReading();

    void mouseReleased(QMouseEvent* e);
signals:
    void analysisDone();
public slots:
    void readSerialValue();
    void analyseData();
    void refreshMonitor();
    void scaloIsDone();
private:
    QSerialPort *serial;
    Scalogram *scalogram;
    RTDisplay * display;
    Spectrograph *spectra;
    Monitor *monitor;
    SerialReading *readerThread;
    QLabel *scalo;
    float *data;
    unsigned counter;
    void init();
    void readWAV(QString wavfile);
    void doFFTW3();
    double *power_spectrum;
    int readdataTimerId;
    QImage* wavelet;
protected:
    void timerEvent(QTimerEvent *e);
};

#endif // EEGREADER_H
