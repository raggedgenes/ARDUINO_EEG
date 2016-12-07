#include "eegreader.h"
#include "math.h"
#include "iostream"
//#include "stdio.h"
//#include "QFile"
//#include <QTextStream>

//#define FFT_SCALE_FACTOR (1500*1500*10)
//#define FFT_SIZE 1500

static const int DataInterval = 20; //msec

EEGReader::EEGReader(QSerialPort *serial, RTDisplay *disp, Monitor *mon, QObject *parent) :
    QObject(parent), serial(serial), display(disp), monitor(mon)
{

    monitor->setOwner(this);
    scalo = new QLabel(monitor);
    connect(this->serial, SIGNAL(readyRead()), this, SLOT(readSerialValue()));
    connect(this->display, SIGNAL(windowFull()),this,SLOT(refreshMonitor()));

//    QTimer *readingTimer = new QTimer(this);
//    readingTimer->start(DataInterval);
//    connect(readingTimer, SIGNAL(timeout()), SLOT(getData()));

}

EEGReader::~EEGReader()
{

}
void EEGReader::startReading() {
    this->startTimer(DataInterval);
}

void EEGReader::mouseReleased(QMouseEvent *e)
{
    QString txt = "Frequency: ";
    txt.append(QString::number(this->scalogram->getFrequency(e->y())));
    monitor->setToolTip(txt);
}

void EEGReader::update()  {
    if(serial->isOpen()) {
        if (serial->bytesAvailable() >= 3) {
            QByteArray ba = serial->read(1);
            quint8 z = (quint8)ba[0];
            int j = (int)z;
            char in[16];
            if (j== 255) {
                if (serial->read(in,2) == 2) {
                   quint8 hb = in[0];
                   quint8 lb = in[1];
                   int r = (hb << 8) | lb;
                   display->addValueAt(r);
                }
            }
        }
    } else {
        connect(this->serial, SIGNAL(readyRead()), this, SLOT(readSerialValue()));
        this->killTimer(readdataTimerId);
    }
}

double *EEGReader::getPowerSpectra()
{
    return this->power_spectrum;
}

void EEGReader::readSerialValue()
{
    disconnect(this->serial, SIGNAL(readyRead()), this, SLOT(readSerialValue()));
    this->serial->flush();
    this->readdataTimerId = this->startTimer(0);

}

void EEGReader::analyseData()
{
    this->scalogram = new Scalogram();
    this->data = display->getRunning_buffer();
    this->connect(scalogram, SIGNAL(scaloIsDone()), this, SLOT(scaloIsDone()));
    scalogram->run(data,display->getSampleSize(),display->getFS(),display->getXresol());
//    this->doFFTW3();
}

void EEGReader::refreshMonitor()
{
    if (monitor->isVisible()) {
        scalogram->run(display->getRunning_buffer(),display->getSampleSize(),display->getFS(),display->getXresol());
    }
}
void EEGReader::scaloIsDone()
{
    //Update Wavelet monitor
    scalo->~QLabel();
    scalo = new QLabel(monitor);
    scalo->setPixmap(QPixmap::fromImage(*(this->scalogram->image)));
    scalo->show();

    //Update spectra viewer in sidebar
}

Monitor *EEGReader::getMonitor() const
{
    return monitor;
}

void EEGReader::setMonitor(Monitor *value)
{
    monitor = value;
}

RTDisplay *EEGReader::getDisplay() const
{
    return display;
}

void EEGReader::setDisplay(RTDisplay *value)
{
    display = value;
}

void EEGReader::doFFTW3() {
    //    extern int optind;
    int FFT_SIZE = display->getSampleSize();
    double in[FFT_SIZE];
    power_spectrum = new double[FFT_SIZE];
    fftw_complex *out;
    fftw_plan plan;
    out = (fftw_complex *)fftw_malloc(sizeof (fftw_complex) * FFT_SIZE);
    for (int i=0; i<(0+FFT_SIZE); i++)
    {
        in[i-0] = data[(FFT_SIZE-FFT_SIZE)+i-0]; //ADC resol = 1024
    }

    plan = fftw_plan_dft_r2c_1d(FFT_SIZE,in,out,FFTW_ESTIMATE);
    fftw_execute(plan); //fftw_one(p, in, out);

    //process results
    double r, i;
    for (int k = 0; k < FFT_SIZE/2+1; k++) {
        r = out[k][0];
        i = out[k][1];
        power_spectrum[k] = sqrt((r * r) + (i * i));
//        printf("%i %lf\n", k, power_spectrum[k]);
    }
    fftw_destroy_plan(plan);

}

void EEGReader::timerEvent(QTimerEvent *e)
{
    if(readdataTimerId == e->timerId()){
        this->update();
    } else {
        this->display->update();
    }
}
QImage* EEGReader::getWavelet()
{
    return wavelet;
}


