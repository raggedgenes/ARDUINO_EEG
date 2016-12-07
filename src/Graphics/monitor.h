#ifndef MONITOR_H
#define MONITOR_H

#include <QWidget>
#include <QMouseEvent>
#include "eegreader.h"

class EEGReader;

class Monitor : public QWidget
{
    Q_OBJECT
public:
    explicit Monitor(QWidget *parent = 0);
    EEGReader *getOwner() const;
    void setOwner(EEGReader *value);

    QSize minimumSizeHint() const;
    QSize sizeHint() const;
signals:

public slots:

private:
    EEGReader* owner;
protected:
    void mouseReleaseEvent(QMouseEvent* e);
};

#endif // MONITOR_H
