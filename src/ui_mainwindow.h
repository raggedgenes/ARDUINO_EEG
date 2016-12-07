/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDial>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionConfigure;
    QAction *actionConnect;
    QAction *actionDisconnect;
    QAction *actionWavelet;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents_2;
    QFormLayout *formLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_3;
    QLabel *label;
    QLineEdit *in_samplingRate;
    QLabel *label_sb;
    QLineEdit *input_SampleBuff;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QDial *dialZoom;
    QLabel *label_3;
    QDial *dialOffset;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(400, 403);
        actionConfigure = new QAction(MainWindow);
        actionConfigure->setObjectName(QStringLiteral("actionConfigure"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/settings.png"), QSize(), QIcon::Normal, QIcon::On);
        actionConfigure->setIcon(icon);
        actionConnect = new QAction(MainWindow);
        actionConnect->setObjectName(QStringLiteral("actionConnect"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/images/connect.png"), QSize(), QIcon::Normal, QIcon::On);
        actionConnect->setIcon(icon1);
        actionDisconnect = new QAction(MainWindow);
        actionDisconnect->setObjectName(QStringLiteral("actionDisconnect"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/images/disconnect.png"), QSize(), QIcon::Normal, QIcon::On);
        actionDisconnect->setIcon(icon2);
        actionWavelet = new QAction(MainWindow);
        actionWavelet->setObjectName(QStringLiteral("actionWavelet"));
        actionWavelet->setCheckable(true);
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/images/signal.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon3.addFile(QStringLiteral(":/images/wavelet.ico"), QSize(), QIcon::Normal, QIcon::On);
        actionWavelet->setIcon(icon3);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        dockWidget = new QDockWidget(MainWindow);
        dockWidget->setObjectName(QStringLiteral("dockWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(dockWidget->sizePolicy().hasHeightForWidth());
        dockWidget->setSizePolicy(sizePolicy);
        dockWidget->setMinimumSize(QSize(177, 328));
        dockWidget->setMaximumSize(QSize(177, 524287));
        dockWidget->setAutoFillBackground(true);
        dockWidget->setStyleSheet(QStringLiteral("border-color: rgb(0, 0, 0);"));
        dockWidget->setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetMovable);
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName(QStringLiteral("dockWidgetContents_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(dockWidgetContents_2->sizePolicy().hasHeightForWidth());
        dockWidgetContents_2->setSizePolicy(sizePolicy1);
        formLayout = new QFormLayout(dockWidgetContents_2);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        groupBox = new QGroupBox(dockWidgetContents_2);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        groupBox->setMinimumSize(QSize(130, 0));
        verticalLayout_3 = new QVBoxLayout(groupBox);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout_3->addWidget(label);

        in_samplingRate = new QLineEdit(groupBox);
        in_samplingRate->setObjectName(QStringLiteral("in_samplingRate"));
        sizePolicy.setHeightForWidth(in_samplingRate->sizePolicy().hasHeightForWidth());
        in_samplingRate->setSizePolicy(sizePolicy);
        in_samplingRate->setFocusPolicy(Qt::ClickFocus);

        verticalLayout_3->addWidget(in_samplingRate);

        label_sb = new QLabel(groupBox);
        label_sb->setObjectName(QStringLiteral("label_sb"));

        verticalLayout_3->addWidget(label_sb);

        input_SampleBuff = new QLineEdit(groupBox);
        input_SampleBuff->setObjectName(QStringLiteral("input_SampleBuff"));
        sizePolicy.setHeightForWidth(input_SampleBuff->sizePolicy().hasHeightForWidth());
        input_SampleBuff->setSizePolicy(sizePolicy);
        input_SampleBuff->setFocusPolicy(Qt::ClickFocus);

        verticalLayout_3->addWidget(input_SampleBuff);


        formLayout->setWidget(0, QFormLayout::LabelRole, groupBox);

        groupBox_2 = new QGroupBox(dockWidgetContents_2);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy2);
        groupBox_2->setMinimumSize(QSize(130, 0));
        gridLayout = new QGridLayout(groupBox_2);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1, Qt::AlignHCenter);

        dialZoom = new QDial(groupBox_2);
        dialZoom->setObjectName(QStringLiteral("dialZoom"));
        sizePolicy.setHeightForWidth(dialZoom->sizePolicy().hasHeightForWidth());
        dialZoom->setSizePolicy(sizePolicy);
        dialZoom->setMaximumSize(QSize(40, 40));
        dialZoom->setMinimum(1);

        gridLayout->addWidget(dialZoom, 0, 1, 1, 1);

        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 1, 1, 1, 1, Qt::AlignHCenter);

        dialOffset = new QDial(groupBox_2);
        dialOffset->setObjectName(QStringLiteral("dialOffset"));
        sizePolicy.setHeightForWidth(dialOffset->sizePolicy().hasHeightForWidth());
        dialOffset->setSizePolicy(sizePolicy);
        dialOffset->setMaximumSize(QSize(40, 40));
        dialOffset->setMinimum(-500);
        dialOffset->setMaximum(500);

        gridLayout->addWidget(dialOffset, 0, 0, 1, 1);


        formLayout->setWidget(1, QFormLayout::LabelRole, groupBox_2);

        dockWidget->setWidget(dockWidgetContents_2);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockWidget);

        mainToolBar->addAction(actionConnect);
        mainToolBar->addAction(actionDisconnect);
        mainToolBar->addAction(actionConfigure);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionWavelet);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionConfigure->setText(QApplication::translate("MainWindow", "Configure", 0));
#ifndef QT_NO_TOOLTIP
        actionConfigure->setToolTip(QApplication::translate("MainWindow", "Set PORT properties", 0));
#endif // QT_NO_TOOLTIP
        actionConnect->setText(QApplication::translate("MainWindow", "Connect", 0));
#ifndef QT_NO_TOOLTIP
        actionConnect->setToolTip(QApplication::translate("MainWindow", "Connect to port", 0));
#endif // QT_NO_TOOLTIP
        actionDisconnect->setText(QApplication::translate("MainWindow", "Disconnect", 0));
#ifndef QT_NO_TOOLTIP
        actionDisconnect->setToolTip(QApplication::translate("MainWindow", "Disconnect port", 0));
#endif // QT_NO_TOOLTIP
        actionWavelet->setText(QApplication::translate("MainWindow", "wavelet", 0));
#ifndef QT_NO_TOOLTIP
        actionWavelet->setToolTip(QApplication::translate("MainWindow", "Do Wavelet Transfer", 0));
#endif // QT_NO_TOOLTIP
        groupBox->setTitle(QApplication::translate("MainWindow", "Sampling", 0));
        label->setText(QApplication::translate("MainWindow", "Sampling rate:", 0));
        label_sb->setText(QApplication::translate("MainWindow", "Sample buffer:", 0));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Viewing", 0));
        label_2->setText(QApplication::translate("MainWindow", "Offset", 0));
        label_3->setText(QApplication::translate("MainWindow", "Zoom", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
