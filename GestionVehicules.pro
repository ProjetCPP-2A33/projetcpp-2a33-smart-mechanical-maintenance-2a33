
#-------------------------------------------------
#
# Project created by QtCreator 2018-10-26T21:45:23
#
#-------------------------------------------------

QT       += core gui sql quick widgets charts

TARGET = Atelier_Connexion
TEMPLATE = app

# Enable warnings for deprecated Qt features
DEFINES += QT_DEPRECATED_WARNINGS

# Set the C++ standard to C++11
CONFIG += c++11

# Specify source files
SOURCES += \
    gestionV.cpp \
    main.cpp \
    connection.cpp \
    rendezvous.cpp \
    vehicules.cpp

# Specify header files
HEADERS += \
    connection.h \
    gestionV.h \
    rendezvous.h \
    vehicules.h

# Specify UI forms
FORMS += \
    gestionV.ui

# Default rules for deployment
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
