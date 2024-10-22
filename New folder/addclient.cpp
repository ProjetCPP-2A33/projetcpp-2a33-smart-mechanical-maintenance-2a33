#include "addclient.h"
#include "ui_addclient.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

AddClient::AddClient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddClient)
{
    ui->setupUi(this);
}

AddClient::~AddClient()
{
    delete ui;
}

// Methods to get data from the dialog inputs
QString AddClient::getNumCin() const { return ui->numCinLineEdit->text(); }
QString AddClient::getNomComplet() const { return ui->nomCompletLineEdit->text(); }
QString AddClient::getAdresse() const { return ui->adresseLineEdit->text(); }
QString AddClient::getAdresseMail() const { return ui->adresseMailLineEdit->text(); }
QString AddClient::getTypeClient() const { return ui->typeClientLineEdit->text(); }
double AddClient::getRemise() const { return ui->remiseLineEdit->text().toDouble(); }
QString AddClient::getRessourceAssocie() const { return ui->ressourceAssocieLineEdit->text(); }

// Function to add client to database
bool AddClient::addClientToDatabase() {
    QSqlQuery query;
    query.prepare("INSERT INTO CLIENT (NUM_CIN, NOM_COMPLET, ADRESSE, ADRESSE_MAIL, TYPE_CLIENT, REMISE, RESSOURCE_ASSOSIE) "
                  "VALUES (:num_cin, :nom_complet, :adresse, :adresse_mail, :type_client, :remise, :ressource_associe)");
    query.bindValue(":num_cin", getNumCin());
    query.bindValue(":nom_complet", getNomComplet());
    query.bindValue(":adresse", getAdresse());
    query.bindValue(":adresse_mail", getAdresseMail());
    query.bindValue(":type_client", getTypeClient());
    query.bindValue(":remise", getRemise());
    query.bindValue(":ressource_associe", getRessourceAssocie());

    if (query.exec()) {
        QMessageBox::information(this, "Success", "Client added successfully.");
        return true;
    } else {
        QMessageBox::warning(this, "Error", "Failed to add client: " + query.lastError().text());
        return false;
    }
}
