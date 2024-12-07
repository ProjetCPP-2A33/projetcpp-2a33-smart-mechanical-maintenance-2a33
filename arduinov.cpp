#include "arduinov.h"
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QSerialPort>
#include "qregularexpression.h"
#include "qsqlquery.h"
#include <QDebug>
#include <QString>
#include <QApplication>
#include <QObject>
#include "qsqlerror.h"

arduinov::arduinov(QObject *parent) : QObject(parent), serial(new QSerialPort(this)) {}

bool arduinov::connectToArduino()
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

            serial->setPortName("COM3");

            serial->setPort(info);
            serial->setBaudRate(QSerialPort::Baud9600);
            serial->setDataBits(QSerialPort::Data8);
            serial->setParity(QSerialPort::NoParity);
            serial->setStopBits(QSerialPort::OneStop);
            serial->setFlowControl(QSerialPort::NoFlowControl);

            if (serial->open(QIODevice::ReadWrite))
            {
                connect(serial, &QSerialPort::readyRead, this, &arduinov::readSerialData);
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


void arduinov::readSerialData()
{
    if (serial->canReadLine())
    {
        QString matricule = serial->readLine().trimmed();
        qDebug() << "Matricule reçue de l'Arduino :" << matricule;

        // Vérifiez si la matricule respecte le format attendu
        QRegularExpression regex(R"(\d{3}tunis\d{4})");
        if (!regex.match(matricule).hasMatch())
        {
            emit matriculeVerified(matricule, false);
            return;
        }

        // Vérifiez si la matricule existe dans la base de données
        bool exists = verifyMatriculeInDatabase(matricule);

        // Emettez un signal avec le résultat
        emit matriculeVerified(matricule, exists);
    }
}


bool arduinov::verifyMatriculeInDatabase(const QString &matricule)
{
    if (matricule.isEmpty()) {
        qDebug() << "Matricule vide reçue.";
        return false;
    }

    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM Vehicules WHERE num_matricule = :matricule");
    query.bindValue(":matricule", matricule);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la vérification de la matricule : " << query.lastError().text();
        return false;
    }

    if (query.next() && query.value(0).toInt() > 0) {
        qDebug() << "La matricule existe dans la base de données : " << matricule;
        return true; // La matricule existe
    }

    /*qDebug() << "La matricule n'existe pas dans la base de données : " << matricule;
    return false; // La matricule n'existe pas*/
}


void arduinov::disconnectFromArduino()
{
    if (serial->isOpen())
    {
        serial->close();
    }
}
