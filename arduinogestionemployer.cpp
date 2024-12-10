#include "arduinogestionemployer.h"
#include <QDebug>

Arduinov::Arduinov(QObject *parent) : QObject(parent), serial(new QSerialPort(this)) {}

Arduinov::~Arduinov()
{
    if (serial->isOpen()) {
        serial->close();
    }
    delete serial;
}

bool Arduinov::connectToArduino(const QString &portName)
{
    serial->setPortName(portName);
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    if (serial->open(QIODevice::WriteOnly)) {
        qDebug() << "Connecté au port série: " << portName;
        return true;
    } else {
        lastError = serial->errorString();
        qDebug() << "Erreur d'ouverture du port série: " << lastError;
        return false;
    }
}

void Arduinov::disconnectFromArduino()
{
    if (serial->isOpen()) {
        serial->close();
        qDebug() << "Port série déconnecté.";
    }
}

bool Arduinov::sendMessage(const QString &message)
{
    if (serial->isOpen() && serial->isWritable()) {
        serial->write(message.toUtf8());
        serial->flush();
        qDebug() << "Message envoyé à l'Arduino: " << message;
        return true;
    } else {
        lastError = "Le port série n'est pas prêt.";
        qDebug() << lastError;
        return false;
    }
}

QString Arduinov::getLastError() const
{
    return lastError;
}
