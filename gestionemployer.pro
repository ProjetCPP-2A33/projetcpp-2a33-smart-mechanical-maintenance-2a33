QT       += core gui
QT += sql
QT += core gui sql
QT += printsupport
QT += core gui charts
QT += charts
QT += network
QT += core
QT +=serialport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    arduinogestionemployer.cpp \
    connexiongestionemployer.cpp \
    employer.cpp \
    main.cpp \
    mainwindowgestionemployer.cpp

HEADERS += \
    arduinogestionemployer.h \
    connexiongestionemployer.h \
    employer.h \
    mainwindowgestionemployer.h

FORMS += \
    mainwindowgestionemployer.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
