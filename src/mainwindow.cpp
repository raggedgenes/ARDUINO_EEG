#include <QtWidgets>
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "ui/console.h"
#include "ui/settingsdialog.h"
#include <QMessageBox>

MainWindow::MainWindow():ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    serial = new QSerialPort(this);
    settings = new SettingsDialog;

    realTimeDisplay = new RTDisplay(this, 1500,1000,0,1024,1000.f); // parent, window, tick, offset, resol, freq);
    monitor = new Monitor();
//    QWidget *central = new QWidget(this);
//    QVBoxLayout *centralLO = new QVBoxLayout;
    QSplitter *splitter = new QSplitter(Qt::Vertical,this);
    splitter->addWidget(realTimeDisplay);
    splitter->addWidget(monitor);
//    splitter->setLayout(centralLO);
    setCentralWidget(splitter);
    monitor->hide();
    setWindowTitle(tr("Arduino EEG - Szabolcs Makai"));

//    console = new Console;
//    console->setEnabled(false);
//    setCentralWidget(console);
    eegreader = new EEGReader(serial, realTimeDisplay, monitor);
    ui->in_samplingRate->setText(QString::number(realTimeDisplay->getFS()));
    ui->input_SampleBuff->setText(QString::number(realTimeDisplay->getSampleSize()));
    ui->dialOffset->setValue(this->realTimeDisplay->getOffset());
    ui->dialZoom->setValue(realTimeDisplay->getZoom());
    ui->actionConnect->setEnabled(true);
    ui->actionDisconnect->setEnabled(false);
    ui->actionConfigure->setEnabled(true);
//    ui->actionWavelet->setEnabled(false);

    initActionsConnections();
//    connect(serial, SIGNAL(readyRead()),this, SLOT(readData()));
    connect(serial, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(handleError(QSerialPort::SerialPortError)));
}
void MainWindow::analyze()
{
    if (this->ui->actionWavelet->isChecked()) {
        eegreader->analyseData();
        monitor->show();
    } else {
        monitor->hide();
    }
}

void MainWindow::openSerialPort()
{
    SettingsDialog::Settings p = settings->settings();
    serial->setPortName(p.name);
    if (serial->open(QIODevice::ReadWrite)) {
        if (serial->setBaudRate(p.baudRate)
                && serial->setDataBits(p.dataBits)
                && serial->setParity(p.parity)
                && serial->setStopBits(p.stopBits)
                && serial->setFlowControl(p.flowControl)) {

//            console->setEnabled(true);
//            console->setLocalEchoEnabled(p.localEchoEnabled);
            ui->actionConnect->setEnabled(false);
            ui->actionDisconnect->setEnabled(true);
            ui->actionConfigure->setEnabled(false);
            ui->actionWavelet->setEnabled(true);
            ui->input_SampleBuff->setEnabled(false);
            ui->statusBar->showMessage(tr("%1 connected on %2, %3, %4, %5, %6, %7")
                                       .arg(p.description).arg(p.name).arg(p.stringBaudRate).arg(p.stringDataBits)
                                       .arg(p.stringParity).arg(p.stringStopBits).arg(p.stringFlowControl));

//            eegreader->setDisplay(realTimeDisplay);
//            eegreader->setMonitor(monitor);
            this->eegScreenRefreshTimerID = eegreader->startTimer(20);

        } else {
            serial->close();
            QMessageBox::critical(this, tr("Error"), serial->errorString());

            ui->statusBar->showMessage(tr("Open error"));
        }
    } else {
        QMessageBox::critical(this, tr("Error"), serial->errorString());

        ui->statusBar->showMessage(tr("Configure error"));
    }
}
void MainWindow::closeSerialPort()
{
    serial->close();
//    console->setEnabled(false);
    ui->actionConnect->setEnabled(true);
    ui->actionDisconnect->setEnabled(false);
    ui->actionConfigure->setEnabled(true);
    ui->statusBar->showMessage(tr("Disconnected"));
    ui->input_SampleBuff->setEnabled(true);
    eegreader->killTimer(eegScreenRefreshTimerID);
}
void MainWindow::writeData(const QByteArray &data)
{
    serial->write(data);
}

void MainWindow::readData()
{
//    QByteArray data = serial->readAll();
//    printf(data);
//    console->putData(data);
}

void MainWindow::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        QMessageBox::critical(this, tr("Critical Error"), serial->errorString());
        closeSerialPort();
    }
}
void MainWindow::initActionsConnections()
{
    connect(ui->actionConnect, SIGNAL(triggered()), this, SLOT(openSerialPort()));
    connect(ui->actionDisconnect, SIGNAL(triggered()), this, SLOT(closeSerialPort()));
    connect(ui->actionConfigure, SIGNAL(triggered()), settings, SLOT(show()));
    connect(ui->actionWavelet, SIGNAL(triggered()), this, SLOT(analyze()));
}
void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Escape)
        close();
    else if (e->key() == Qt::Key_Space){
        if (serial->isOpen())
            closeSerialPort();
        else
            openSerialPort();
    }
    else
        QWidget::keyPressEvent(e);
}

void MainWindow::on_in_samplingRate_returnPressed()
{
    float newsr = this->ui->in_samplingRate->text().toFloat();
    this->realTimeDisplay->setFS(newsr);
}

void MainWindow::on_input_SampleBuff_returnPressed()
{
    int newsr = this->ui->input_SampleBuff->text().toInt();
    this->realTimeDisplay->setSampleSize(newsr);
    this->realTimeDisplay->update();
}

void MainWindow::on_dialOffset_sliderReleased()
{
    int v = ui->dialOffset->value();
    this->realTimeDisplay->setOffset(v);
    ui->dialZoom->setToolTip(QString::number(v));
    this->realTimeDisplay->update();
}

void MainWindow::on_dialZoom_sliderReleased()
{
    int v = ui->dialZoom->value();
    this->realTimeDisplay->setZoom(v);
    ui->dialZoom->setToolTip(QString::number(v));
    this->realTimeDisplay->update();
}
