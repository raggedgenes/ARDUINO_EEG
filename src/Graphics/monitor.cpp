#include "monitor.h"
#include "iostream"


Monitor::Monitor(QWidget *parent) :
    QWidget(parent)
{
}

QSize Monitor::minimumSizeHint() const
{
    return QSize(50, 50);
}
QSize Monitor::sizeHint() const
{
    return QSize(400, 400);
}

EEGReader *Monitor::getOwner() const
{
    return owner;
}

void Monitor::setOwner(EEGReader *value)
{
    owner = value;
//    this->setVisible(false);
}

void Monitor::mouseReleaseEvent(QMouseEvent *e)
{
    //printf("mouse: %i, %i\n", e->x(), e->y());
    this->owner->mouseReleased(e);
}
