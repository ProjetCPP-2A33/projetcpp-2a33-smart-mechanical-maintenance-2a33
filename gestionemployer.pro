QT       += core gui \
    quick    
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
    addclient.cpp \
    arduinogestionemployer.cpp \
    arduinov.cpp \
    client.cpp \
    connection.cpp \
    employer.cpp \
    main.cpp \
    mainwindowgestionemployer.cpp \
    rendezvous.cpp \
    vehicules.cpp

HEADERS += \
    addclient.h \
    arduinogestionemployer.h \
    arduinov.h \
    client.h \
    connection.h \
    employer.h \
    mainwindowgestionemployer.h \
    rendezvous.h \
    vehicules.h

FORMS += \
    addclient.ui \
    mainwindowgestionemployer.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
