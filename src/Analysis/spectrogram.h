#ifndef SPECTROGRAM_H
#define SPECTROGRAM_H

#include <QObject>
#include "fftw3.h"

class Spectrogram : public QObject
{
    Q_OBJECT
public:
    explicit Spectrogram(QObject *parent = 0);

    void doFFTW3();
signals:

public slots:

};

#endif // SPECTROGRAM_H
