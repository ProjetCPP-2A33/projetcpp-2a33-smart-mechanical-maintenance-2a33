#ifndef ARDUINOV_H
#define ARDUINOV_H
#include <QSerialPort>
#include <QString>
#include <QObject>
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QSerialPort>
#include <QDebug>
#include <QString>
#include <QApplication>
#include <QObject>



class arduinov : public QObject
{
    Q_OBJECT
public:
    explicit arduinov(QObject *parent = nullptr);
    bool connectToArduino();
    bool verifyMatriculeInDatabase(const QString &matricule);
    void disconnectFromArduino();

signals:
    void dataReceived(QString data);
    void matriculeVerified(const QString &matricule, bool exists);

private slots:
    void readSerialData();

private:
    QSerialPort *serial;
};

#endif // ARDUINOV_H
