#ifndef ARDUINOGESTIONL_H
#define ARDUINOGESTIONL_H
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>

class Arduino : public QObject
{
    Q_OBJECT

public:
    explicit Arduino(QObject *parent = nullptr);
    ~Arduino();
    bool connectToArduino();
    void disconnectFromArduino();
    void writeToArduino(const QByteArray &data);
    QByteArray readFromArduino();
    void controlFan(bool state);

signals:
    void dataReceived(QString data);
    void matriculeVerified(const QString &matricule, bool exists);

private slots:
    void readSerialData();

private:
    QSerialPort *serial;
    static const quint16 arduino_uno_vendor_id = 9025;
    static const quint16 arduino_uno_product_id = 67;
    QString arduino_port_name;
    bool arduino_is_available;
    QByteArray data;
};



#endif // ARDUINOGESTIONL_H
