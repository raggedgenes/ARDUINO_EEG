#-------------------------------------------------
#
# Project created by QtCreator 2015-03-03T09:13:25
#
#-------------------------------------------------

QT           += core gui
QT           += opengl widgets serialport
CONFIG       += static
#CONFIG += console
CONFIG += c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ARD_EEG
TEMPLATE = app


SOURCES += src/main.cpp\
        mainwindow.cpp \
#    src/glwidget.cpp \
#    src/Graphics/sinuscurve.cpp \
#    src/Graphics/testfftw3.cpp \
    src/eegreader.cpp \
    src/ui/settingsdialog.cpp \
    src/ui/console.cpp \
    src/Graphics/display.cpp \
    src/Analysis/scalogram.cpp \
    src/Graphics/ColourMap.cpp \
    src/Graphics/glwidget.cpp \
#    src/wavfile.cpp
    src/Analysis/rgmath.cpp \
    src/Utils/serialreading.cpp \
    src/Graphics/monitor.cpp \
    src/Graphics/spectrograph.cpp \
#    src/Analysis/spectrogram.cpp

HEADERS  += mainwindow.h \
#    glwidget.h \
#    src/Graphics/sinuscurve.h \
#    src/fftw3.h \
#    src/Graphics/testfftw3.h \
    src/eegreader.h \
    src/ui/settingsdialog.h \
    src/ui/ui_settingsdialog.h \
    src/ui/console.h \
    src/Graphics/display.h \
    src/Analysis/scalogram.h \
    src/Graphics/ColourMap.h \
    src/Graphics/glwidget.h \
#    src/wavfile.h
    src/Analysis/rgmath.h \
    src/Utils/serialreading.h \
    src/Graphics/monitor.h \
    src/Graphics/spectrograph.h \
#    src/Analysis/spectrogram.h

FORMS    += src/mainwindow.ui \
    src/ui/settingsdialog.ui

HEADERS += \
    ../../CPPLibraries/fftw-3.3.4-dll32/fftw3.h


win32: LIBS += -L$$PWD/../../CPPLibraries/fftw-3.3.4-dll32/ -llibfftw3-3

INCLUDEPATH += $$PWD/../../CPPLibraries/fftw-3.3.4-dll32
DEPENDPATH += $$PWD/../../CPPLibraries/fftw-3.3.4-dll32

win32: LIBS += -L$$PWD/../../CPPLibraries/fftw-3.3.4-dll32/ -llibfftw3f-3

INCLUDEPATH += $$PWD/../../CPPLibraries/fftw-3.3.4-dll32
DEPENDPATH += $$PWD/../../CPPLibraries/fftw-3.3.4-dll32

win32: LIBS += -L$$PWD/../../CPPLibraries/fftw-3.3.4-dll32/ -llibfftw3l-3

INCLUDEPATH += $$PWD/../../CPPLibraries/fftw-3.3.4-dll32
DEPENDPATH += $$PWD/../../CPPLibraries/fftw-3.3.4-dll32

win32: LIBS += -L$$PWD/../../CPPLibraries/fftw-3.3.4-dll32/ -llibfftw3-3

RESOURCES += \
    resources/icons.qrc
