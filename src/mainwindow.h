#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include <QSerialPort>
#include "Graphics/glwidget.h"
#include "Graphics/display.h"
#include "Graphics/monitor.h"
#include "./eegreader.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE
class Console;
class SettingsDialog;
class GLWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    Ui::MainWindow *ui;
    RTDisplay *realTimeDisplay;
    Monitor *monitor;
    SettingsDialog *settings;
    QSerialPort *serial;
    Console *console;
    EEGReader *eegreader;
    void initActionsConnections();

    int eegScreenRefreshTimerID;
private slots:
    void openSerialPort();
    void closeSerialPort();
    void writeData(const QByteArray &data);
    void readData();
    void analyze();
    void handleError(QSerialPort::SerialPortError error);
    void on_in_samplingRate_returnPressed();

    void on_input_SampleBuff_returnPressed();
    void on_dialOffset_sliderReleased();
    void on_dialZoom_sliderReleased();
};

#endif // MAINWINDOW_H
