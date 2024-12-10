#include "arduinogestionL.h"
#include "qregularexpression.h"

Arduino::Arduino(QObject *parent) : QObject(parent), serial(new QSerialPort(this))
{
    arduino_port_name = "";
    arduino_is_available = false;
    data = "";
}

Arduino::~Arduino()
{
    if (serial->isOpen()) {
        serial->close();
    }
    delete serial;
}

bool Arduino::connectToArduino()
{
    qDebug() << "Recherche d'Arduino sur les ports série disponibles...";

    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        qDebug() << "Port détecté :";
        qDebug() << "  Nom du port     :" << info.portName();
        qDebug() << "  Description     :" << info.description();
        qDebug() << "  Fabricant       :" << info.manufacturer();

        if (info.description().contains("Arduino", Qt::CaseInsensitive) ||
            info.manufacturer().contains("Arduino", Qt::CaseInsensitive) ||
            info.description().contains("CH340", Qt::CaseInsensitive) ||
            info.manufacturer().contains("wch.cn", Qt::CaseInsensitive))
        {

            serial->setPortName("COM15");

            serial->setPort(info);
            serial->setBaudRate(QSerialPort::Baud9600);
            serial->setDataBits(QSerialPort::Data8);
            serial->setParity(QSerialPort::NoParity);
            serial->setStopBits(QSerialPort::OneStop);
            serial->setFlowControl(QSerialPort::NoFlowControl);

            if (serial->open(QIODevice::ReadWrite))
            {
                connect(serial, &QSerialPort::readyRead, this, &Arduino::readSerialData);
                qDebug() << "Connecté à l'Arduino sur le port" << info.portName();
                return true;
            }
            else
            {
                qDebug() << "Erreur : Impossible d'ouvrir le port" << info.portName()
                << "Raison :" << serial->errorString();
            }
        }
    }

    qDebug() << "Erreur : Aucun Arduino détecté parmi les ports série disponibles.";
    return false;
}

void Arduino::disconnectFromArduino()
{
    if (serial->isOpen()) {
        serial->close();
    }
}

void Arduino::writeToArduino(const QByteArray &data)
{
    if (serial->isWritable()) {
        serial->write(data);
    } else {
        qDebug() << "Couldn't write to serial!";
    }
}

QByteArray Arduino::readFromArduino()
{
    if (serial->isReadable()) {
        data = serial->readAll();
        emit dataReceived(data);
        return data;
    }
    return QByteArray();
}

void Arduino::readSerialData()
{
    QByteArray readData = serial->readAll();
    QString readString = QString::fromUtf8(readData.trimmed());
    QRegularExpression regex(R"(\d{3}tunis\d{4})");
    bool match = regex.match(readString).hasMatch();
    emit matriculeVerified(readString, match);
}

void Arduino::controlFan(bool state)
{
    QByteArray command = state ? "1" : "0";
    writeToArduino(command);
}
