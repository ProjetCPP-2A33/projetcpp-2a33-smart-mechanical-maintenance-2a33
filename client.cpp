#include "client.h"
#include <QSqlQuery>
#include <QSqlQueryModel>


Client::Client() {}


Client::Client(int numCin, QString nomComplet, QString adresse, QString adresseMail, QString typeClient, double remise, QString ressourceAssocie) {
    this->numCin = numCin;
    this->nomComplet = nomComplet;
    this->adresse = adresse;
    this->adresseMail = adresseMail;
    this->typeClient = typeClient;
    this->remise = remise;
    this->ressourceAssocie = ressourceAssocie;
}


int Client::getNumCin() { return numCin; }
QString Client::getNomComplet() { return nomComplet; }
QString Client::getAdresse() { return adresse; }
QString Client::getAdresseMail() { return adresseMail; }
QString Client::getTypeClient() { return typeClient; }
double Client::getRemise() { return remise; }
QString Client::getRessourceAssocie() { return ressourceAssocie; }


void Client::setNumCin(int numCin) { this->numCin = numCin; }
void Client::setNomComplet(QString nomComplet) { this->nomComplet = nomComplet; }
void Client::setAdresse(QString adresse) { this->adresse = adresse; }
void Client::setAdresseMail(QString adresseMail) { this->adresseMail = adresseMail; }
void Client::setTypeClient(QString typeClient) { this->typeClient = typeClient; }
void Client::setRemise(double remise) { this->remise = remise; }
void Client::setRessourceAssocie(QString ressourceAssocie) { this->ressourceAssocie = ressourceAssocie; }


bool Client::addClient() {
    QSqlQuery query;
    query.prepare("INSERT INTO CLIENT (NUM_CIN, NOM_COMPLET, ADRESSE, ADRESSE_MAIL, TYPE_CLIENT, REMISE, RESSOURCE_ASSOSIE) "
                  "VALUES (:numCin, :nomComplet, :adresse, :adresseMail, :typeClient, :remise, :ressourceAssocie)");
    query.bindValue(":numCin", numCin);
    query.bindValue(":nomComplet", nomComplet);
    query.bindValue(":adresse", adresse);
    query.bindValue(":adresseMail", adresseMail);
    query.bindValue(":typeClient", typeClient);
    query.bindValue(":remise", remise);
    query.bindValue(":ressourceAssocie", ressourceAssocie);

    return query.exec();
}


QSqlQueryModel* Client::displayClients() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM CLIENT");
    return model;
}


bool Client::deleteClient(int numCin) {
    QSqlQuery query;
    query.prepare("DELETE FROM CLIENT WHERE NUM_CIN = :numCin");
    query.bindValue(":numCin", numCin);

    return query.exec();
}


bool Client::editClient(int numCin) {
    QSqlQuery query;
    query.prepare("UPDATE CLIENT SET NOM_COMPLET = :nomComplet, ADRESSE = :adresse, ADRESSE_MAIL = :adresseMail, TYPE_CLIENT = :typeClient, "
                  "REMISE = :remise, RESSOURCE_ASSOSIE = :ressourceAssocie WHERE NUM_CIN = :numCin");
    query.bindValue(":numCin", numCin);
    query.bindValue(":nomComplet", nomComplet);
    query.bindValue(":adresse", adresse);
    query.bindValue(":adresseMail", adresseMail);
    query.bindValue(":typeClient", typeClient);
    query.bindValue(":remise", remise);
    query.bindValue(":ressourceAssocie", ressourceAssocie);

    return query.exec();
}
