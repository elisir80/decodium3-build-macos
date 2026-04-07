#-------------------------------------------------
#
# Project created by QtCreator 2011-07-07T08:39:24
#
#-------------------------------------------------

QT       += core gui network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG   += thread
#CONFIG   += console

TARGET = qmap
VERSION = 0.1
TEMPLATE = app
DEFINES = QT5

win32 {
DEFINES = WIN32
}

unix {
DEFINES = UNIX
}

SOURCES += main.cpp mainwindow.cpp plotter.cpp about.cpp \
    soundin.cpp devsetup.cpp \
    widegraph.cpp getfile.cpp \
    astro.cpp displaytext.cpp getdev.cpp \
    meterwidget.cpp signalmeter.cpp

HEADERS  += mainwindow.h plotter.h soundin.h \
            about.h devsetup.h widegraph.h getfile.h \
            commons.h sleep.h astro.h displaytext.h \
            meterwidget.h signalmeter.h

FORMS    += mainwindow.ui about.ui devsetup.ui widegraph.ui \
    astro.ui txtune.ui
