#include <QtWidgets>
#include <QtOpenGL>
#include <iostream>
#include <math.h>
#include "GL/glu.h"
#include "glwidget.h"
#include "display.h"
#include <QFile>
#include <QTextStream>

#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE  0x809D
#endif

static void shiftData(float *data, int len, float newValue)
{
    memmove(data, data + 1, sizeof(*data) * len);
    data[len - 1] = newValue;
}

RTDisplay::RTDisplay(QWidget *parent, int window, int tick, int offset, int resolution, float sf) :
    QGLWidget(QGLFormat(QGL::SampleBuffers), parent), range(0,resolution)
{
    this->ADC = resolution;
    this->offset = offset;
    this->FS = sf;
    this->sampleSize = window;
    this->ygrid = tick*0.001*FS;
    yresol = 400.f/ADC;
    zoom = 1;
    xresol = 400.f / sampleSize;
    setAutoFillBackground(false);
    init();
}
RTDisplay::~RTDisplay(){

}
QSize RTDisplay::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize RTDisplay::sizeHint() const
{
    return QSize(400, 400);
}
void RTDisplay::initializeGL()
{
    glShadeModel(GL_SMOOTH);
    glClearColor(0.1f, 0.1f, 0.1f, 0.5f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

//     display = new RTDisplay(this, 5000,1000,500,1024,1000.f); // parent, window, tick, resol, freq
}
void RTDisplay::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    drawgrid();
    drawRTdata();
    QPainter painter(this);
    drawInstructions(&painter);
}
void RTDisplay::resizeGL(int width, int height)
{
    glViewport(0,0,width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height/zoom,-1,1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    this->xresol = ((float)width)/sampleSize;
    this->yresol = (float) height/ADC;
}

void RTDisplay::drawInstructions(QPainter *painter)
{
    QString txt = "ADC:";
    txt.append(QString::number(ADC));
    txt.append(" | Offset: ");
    txt.append(QString::number(offset));
    txt.append(" | Zoom: ");
    txt.append(QString::number(zoom));
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(QColor(100,100,100));
    painter->drawText(5,5,this->width(),30,Qt::AlignLeft|Qt::TextWordWrap,txt);
    painter->end();
}
void RTDisplay::init()
{
    this->running_buffer = new float[sampleSize];
    counter = 0;
    QFile inputFile("D:/RandD/ARD_EEG/alpha_norm.txt");
    this->FS = 1000;
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       int line = 0;
       while (!in.atEnd() || line > sampleSize*this->FS*.001) //windowsize ms-ban van, ezért kell a .001-es szorzás
       {
          running_buffer[line] = in.readLine().toFloat();
          line++;
       }
      this->sampleSize = line;
       inputFile.close();
    }
//    for (int i=0; i < sampleSize; i++) {
//        running_buffer[i] = 0.f;
//    }
}

void RTDisplay::drawgrid() const
{
    int numofticks = sampleSize / (this->ygrid); //ygrid ms-ben vab ezért az ezres szorzó
    glColor4f(.3f,.3f,.3f,1);
    glBegin(GL_LINES);
    for (int t = 1; t <= numofticks; t++) {
        glVertex2f(t*xresol*ygrid,0);
        glVertex2f(t*xresol*ygrid,(ADC)*yresol);
    }
    glColor4f(1.f,1.f,.0f,1);
    glVertex2f(counter*xresol,0);
    glVertex2f(counter*xresol,(ADC)*yresol);
    glEnd();
}

void RTDisplay::drawRTdata() const
{
    glBegin(GL_LINE_STRIP);
    glColor4f(1,0,0,1);
    for (int i=1; i<sampleSize; i++)
    {
        glVertex2f(i*xresol, yresol*(running_buffer[i]-this->offset/zoom));
//        printf("v: %f",running_buffer[i]);
//        std::cout << running_buffer[i] << "\n";
    }

    glEnd();
}

void RTDisplay::makeRange()
{
}
int RTDisplay::getZoom() const
{
    return zoom;
}

void RTDisplay::setZoom(int value)
{
    zoom = value;
}

int RTDisplay::getOffset() const
{
    return offset;
}

void RTDisplay::setOffset(int value)
{
    offset = value;
}

float RTDisplay::getXresol() const
{
    return xresol;
}

void RTDisplay::setXresol(float value)
{
    xresol = value;
}

void RTDisplay::addValueAt(const int v)
{
    this->running_buffer[counter] = (float)v;
    counter++;
    if (counter >= sampleSize) {
        counter = 0;
        this->windowFull();
    }
//    this->update();
}

void RTDisplay::putData(const QByteArray &ba)
{
    for (int i = 0; i < ba.size()-2; i++) {
       quint8 r = ba[i];
       if (r == 255)
       {
           i++;
           quint16 z = ba[i] << 8;
           i++;
           z |= ba[i];
           float f = (float)z;
           addValueAt(f);
       }
    }

}

float RTDisplay::getFS() const
{
    return FS;
}

void RTDisplay::setFS(float value)
{
    this->ygrid /=FS;
    FS = value;
    this->ygrid *=FS;
}

float *RTDisplay::getRunning_buffer() const
{
    return running_buffer;
}

void RTDisplay::setRunning_buffer(float *value)
{
    running_buffer = value;
}

int RTDisplay::getSampleSize() const
{
    return sampleSize;
}
void RTDisplay::setSampleSize(int value)
{
    float *newbuff = new float[value];
    int diff = value - sampleSize;
    if (diff > 0) {
        memcpy(newbuff,running_buffer,sizeof(float)*sampleSize);
    } else if (diff < 0) {
        int tmp = value-counter;
        (tmp > 0) ? : tmp = 0;
        memcpy(newbuff,running_buffer+tmp,sizeof(float)*value);
    }
    free(this->running_buffer);
    this->running_buffer = newbuff;
    this->xresol *= sampleSize;
    sampleSize = value;
    this->xresol /= sampleSize;
}
int RTDisplay::getYgrid() const
{
    return ygrid;
}

void RTDisplay::setYgrid(int value)
{
    ygrid = value;
}

