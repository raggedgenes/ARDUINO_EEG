#ifndef SCALOGRAM_H
#define SCALOGRAM_H

#include <QObject>
#include <QImage>
#include "stdio.h"
#include "../Graphics/ColourMap.h"

class ScalogramCreatorParams
{
public:
    /// The waveform.
//    WaveformRef wave;

//    /// The destination image.
//    SoundImage* image;

//    /// The smallest scale to render.
//    double lowerScale;

//    /// The largest scale to render.
//    double upperScale;

//    /// "Wave number". Higher means more frequency localization. Smaller means
//    /// more time localization.
//    double f0;

//    /// Type of image to create when rendering to the Dib.
//    SoundImage::ImageType type;

//    /// Colour map to use when rendering to the DibImage.
//    ColourMap map;

//    /// DibImage to which to render on the fly.
//    DibImage* dib;
};

class Scalogram : public QObject
{
    Q_OBJECT
public:
    explicit Scalogram(QObject *parent = 0);
    ~Scalogram();
    void run(float *eegreading, unsigned numSamples, unsigned sr, float xresol);
    unsigned calcBands(float sampleRate, float *upperScale, float *lowerScale);
    double getFrequency(int row) const;
    QImage* image;
    double* power_spectrum;
signals:
    void scaloIsDone();
public slots:
private:
    void makeVertexBuffer(int row, float *samples, int end);

    void findMaxInRow(float *data);

    ColourMap map;
    /// Number of rows in the image.
    unsigned bands;

    /// Number of samples in the image. Each sample has a real and complex
    /// part.
    unsigned samples;
    /// Sample rate of the represented audio file.
    unsigned sampleRate;

    float* lowerScale ;
    float* upperScale;
    double f0;
    unsigned avoid_overlap;
    double df;
    unsigned N;
    float (*func)(float* data);
    /// minimum value of any sample.
    float mmin;

    /// maximum value of any sample.
    float mmax;
};

#endif // SCALOGRAM_H
