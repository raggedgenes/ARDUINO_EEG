#ifndef DISPLAY_H
#define DISPLAY_H

#include <QObject>
#include <QGLWidget>
#include "eegreader.h"

//#define X_SIZE 1500
//class EEGReader;

class RTDisplay : public QGLWidget
{
    Q_OBJECT
public:
    explicit RTDisplay(QWidget *parent, int sampleSize, int tick, int offset, int resolution, float sf);
    ~RTDisplay();

    QSize minimumSizeHint() const;
    QSize sizeHint() const;

//    int samplesize;

    int getSampleSize() const;
    void setSampleSize(int value);

    int getYgrid() const;
    void setYgrid(int value);

    float *getRunning_buffer() const;
    void setRunning_buffer(float *value);

    float getFS() const;
    void setFS(float value);

    float getXresol() const;
    void setXresol(float value);

    void addValueAt(const int v);
    void putData(const QByteArray &ba);

//    EEGReader* eeg;

    int getOffset() const;
    void setOffset(int value);

    int getZoom() const;
    void setZoom(int value);

signals:
    void windowFull();

public slots:

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void drawInstructions(QPainter *painter);

private:
    void init();
    void drawgrid() const;
    void drawRTdata() const;
    void makeRange();
    int ADC; //ADC resolution Arduino: 1024
    float FS; //sampling rate
    int offset;
    int zoom;
    float *running_buffer;
    int sampleSize;
    float xresol;
    float yresol;
    int ygrid;
    int counter;
    QSize range;


};

#endif // DISPLAY_H
