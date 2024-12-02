#include "arduino.h"
#include <QDebug>

Arduino::Arduino(QObject *parent) : QObject(parent), serial(new QSerialPort(this)) {}

Arduino::~Arduino()
{
    if (serial->isOpen()) {
        serial->close();
    }
    delete serial;
}

bool Arduino::connectToArduino(const QString &portName)
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

void Arduino::disconnectFromArduino()
{
    if (serial->isOpen()) {
        serial->close();
        qDebug() << "Port série déconnecté.";
    }
}

bool Arduino::sendMessage(const QString &message)
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

QString Arduino::getLastError() const
{
    return lastError;
}
