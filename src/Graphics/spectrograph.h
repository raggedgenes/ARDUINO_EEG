#ifndef SPECTROGRAPH_H
#define SPECTROGRAPH_H

#include <QWidget>

class Spectrograph : public QWidget
{
    Q_OBJECT
public:
    explicit Spectrograph(QWidget *parent = 0);

    // QWidget
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void setParams(int numBars, int samples, int fs, double *pow_spec, qreal lowFreq, qreal highFreq);

signals:

public slots:

private:
    int samplingRate;
    double *power_spectrum;
    struct Bar {
        Bar() : value(0.0), clipped(false) { }
        qreal   value;
        bool    clipped;
    };
    QVector<Bar>    m_bars;
    void            updateBars(int samples);
    int             m_barSelected;
    int barIndex(qreal frequency) const;
};

#endif // SPECTROGRAPH_H
