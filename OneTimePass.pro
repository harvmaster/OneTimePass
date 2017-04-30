#-------------------------------------------------
#
# Project created by QtCreator 2017-04-29T19:00:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OneTimePass
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    otpwidget.cpp \
    adddialog.cpp

HEADERS  += mainwindow.h \
    otpwidget.h \
    adddialog.h

FORMS    += mainwindow.ui \
    otpwidget.ui \
    adddialog.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../usr/lib/release/ -loath
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../usr/lib/debug/ -loath
else:unix: LIBS += -L$$PWD/../../../../../usr/lib/ -loath

INCLUDEPATH += $$PWD/../../../../../usr/include/liboath
DEPENDPATH += $$PWD/../../../../../usr/include/liboath
