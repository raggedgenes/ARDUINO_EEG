#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>

class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    GLWidget(QWidget *parent = 0);
    ~GLWidget();

    QSize minimumSizeHint() const;
    QSize sizeHint() const;

    int getWindow() const;
    void setWindow(int value);

    int getYgrid() const;
    void setYgrid(int value);

    double *power_spectrum;
    QImage *scalogram;

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

private:
    void drawFFT() const;
    void drawScalogram();
    int ADC; //ADC resolution Arduino: 1024
    float FS; //sampling rate
    int offset;
    int *running_buffer;
    int windowsize;
    float xresol;
    int ygrid;
};


#endif
