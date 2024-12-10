#ifndef ARDUINOGESTIONEMPLOYER_H
#define ARDUINOGESTIONEMPLOYER_H

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QObject>

class Arduinov : public QObject
{
    Q_OBJECT

public:
    explicit Arduinov(QObject *parent = nullptr);
    ~Arduinov();

    bool connectToArduino(const QString &portName);
    void disconnectFromArduino();
    bool sendMessage(const QString &message);
    QString getLastError() const;

private:
    QSerialPort *serial;
    QString lastError;
};

#endif // ARDUINOGESTIONEMPLOYER_H
