#include "spectrograph.h"

Spectrograph::Spectrograph(QWidget *parent) :
    QWidget(parent)
{
}
void Spectrograph::setParams(int numBars, int samples, int fs, double* pow_spec, qreal lowFreq, qreal highFreq)
{
    Q_ASSERT(numBars > 0);
    Q_ASSERT(highFreq > lowFreq);
    m_bars.resize(numBars);
    m_lowFreq = lowFreq;
    m_highFreq = highFreq;
    samplingRate = fs;
    power_spectrum = pow_spec;
    updateBars(samples);
}

void Spectrograph::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.fillRect(rect(), Qt::black);

    const int numBars = m_bars.count();

    // Highlight region of selected bar
    if (m_barSelected != NullIndex && numBars) {
        QRect regionRect = rect();
        regionRect.setLeft(m_barSelected * rect().width() / numBars);
        regionRect.setWidth(rect().width() / numBars);
        QColor regionColor(202, 202, 64);
        painter.setBrush(Qt::DiagCrossPattern);
        painter.fillRect(regionRect, regionColor);
        painter.setBrush(Qt::NoBrush);
    }

    QColor barColor(51, 204, 102);
    QColor clipColor(255, 255, 0);

    // Draw the outline
    const QColor gridColor = barColor.darker();
    QPen gridPen(gridColor);
    painter.setPen(gridPen);
    painter.drawLine(rect().topLeft(), rect().topRight());
    painter.drawLine(rect().topRight(), rect().bottomRight());
    painter.drawLine(rect().bottomRight(), rect().bottomLeft());
    painter.drawLine(rect().bottomLeft(), rect().topLeft());

    QVector<qreal> dashes;
    dashes << 2 << 2;
    gridPen.setDashPattern(dashes);
    painter.setPen(gridPen);

    // Draw vertical lines between bars
    if (numBars) {
        const int numHorizontalSections = numBars;
        QLine line(rect().topLeft(), rect().bottomLeft());
        for (int i=1; i<numHorizontalSections; ++i) {
            line.translate(rect().width()/numHorizontalSections, 0);
            painter.drawLine(line);
        }
    }

    // Draw horizontal lines
    const int numVerticalSections = 10;
    QLine line(rect().topLeft(), rect().topRight());
    for (int i=1; i<numVerticalSections; ++i) {
        line.translate(0, rect().height()/numVerticalSections);
        painter.drawLine(line);
    }

    barColor = barColor.lighter();
    barColor.setAlphaF(0.75);
    clipColor.setAlphaF(0.75);

    // Draw the bars
    if (numBars) {
        // Calculate width of bars and gaps
        const int widgetWidth = rect().width();
        const int barPlusGapWidth = widgetWidth / numBars;
        const int barWidth = 0.8 * barPlusGapWidth;
        const int gapWidth = barPlusGapWidth - barWidth;
        const int paddingWidth = widgetWidth - numBars * (barWidth + gapWidth);
        const int leftPaddingWidth = (paddingWidth + gapWidth) / 2;
        const int barHeight = rect().height() - 2 * gapWidth;

        for (int i=0; i<numBars; ++i) {
            const qreal value = m_bars[i].value;
            Q_ASSERT(value >= 0.0 && value <= 1.0);
            QRect bar = rect();
            bar.setLeft(rect().left() + leftPaddingWidth + (i * (gapWidth + barWidth)));
            bar.setWidth(barWidth);
            bar.setTop(rect().top() + gapWidth + (1.0 - value) * barHeight);
            bar.setBottom(rect().bottom() - gapWidth);

            QColor color = barColor;
            if (m_bars[i].clipped)
                color = clipColor;

            painter.fillRect(bar, color);
        }
    }
}
int Spectrograph::barIndex(qreal frequency) const
{
    Q_ASSERT(frequency >= m_lowFreq && frequency < m_highFreq);
    const qreal bandWidth = (m_highFreq - m_lowFreq) / m_bars.count();
    const int index = (frequency - m_lowFreq) / bandWidth;
    if (index <0 || index >= m_bars.count())
        Q_ASSERT(false);
    return index;
}
void Spectrograph::updateBars(int samples)
{
    m_bars.fill(Bar());
//    FrequencySpectrum::const_iterator i = m_spectrum.begin();
//    const FrequencySpectrum::const_iterator end = m_spectrum.end();
    float d = samplingRate/samples;
    for (int i = 0 ; i < samples; ++i) {
        float frequency = i*d;
        if (frequency >= m_lowFreq && frequency < m_highFreq) {
            Bar &bar = m_bars[barIndex(frequency)];
            bar.value = qMax(bar.value, power_spectrum[i]);
        }
    }
    update();
}
