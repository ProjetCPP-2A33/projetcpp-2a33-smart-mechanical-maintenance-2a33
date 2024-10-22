#ifndef CLIENT_H
#define CLIENT_H

#include <QString>
#include <QDate>
#include <QSqlQueryModel>

class Client
{
public:
    // Constructors
    Client();
    Client(int numCin, QString nomComplet, QString adresse, QString adresseMail, QString typeClient, double remise, QString ressourceAssocie);

    // Getters
    int getNumCin();
    QString getNomComplet();
    QString getAdresse();
    QString getAdresseMail();
    QString getTypeClient();
    double getRemise();
    QString getRessourceAssocie();

    // Setters
    void setNumCin(int numCin);
    void setNomComplet(QString nomComplet);
    void setAdresse(QString adresse);
    void setAdresseMail(QString adresseMail);
    void setTypeClient(QString typeClient);
    void setRemise(double remise);
    void setRessourceAssocie(QString ressourceAssocie);

    // Database operations
    bool addClient();
    QSqlQueryModel* displayClients();
    bool deleteClient(int numCin);
    bool editClient(int numCin);

private:
    int numCin;
    QString nomComplet;
    QString adresse;
    QString adresseMail;
    QString typeClient;
    double remise;
    QString ressourceAssocie;
};

#endif // CLIENT_H
