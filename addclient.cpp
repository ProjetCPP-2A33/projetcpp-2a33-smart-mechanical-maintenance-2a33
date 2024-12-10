#include "addclient.h"
#include "ui_addclient.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QFileDialog>
#include <QPixmap>

AddClient::AddClient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddClient)
{
    ui->setupUi(this);

    // Connect the upload image button
    connect(ui->importImageButton, &QPushButton::clicked, this, &AddClient::onUploadImageClicked);
}

AddClient::~AddClient()
{
    delete ui;
}

// Getters for form fields
QString AddClient::getNumCin() const { return ui->numCinLineEdit->text(); }
QString AddClient::getNomComplet() const { return ui->nomCompletLineEdit->text(); }
QString AddClient::getAdresse() const { return ui->adresseLineEdit->text(); }
QString AddClient::getAdresseMail() const { return ui->adresseMailLineEdit->text(); }
QString AddClient::getTypeClient() const { return ui->typeClientLineEdit->text(); }
double AddClient::getRemise() const { return ui->remiseLineEdit->text().toDouble(); }
QString AddClient::getRessourceAssocie() const { return ui->ressourceAssocieLineEdit->text(); }
QString AddClient::getImagePath() const { return imagePath; } // Added getter for image path

bool AddClient::addClientToDatabase() {
    QSqlQuery query;
    query.prepare("INSERT INTO CLIENT (NUM_CIN, NOM_COMPLET, ADRESSE, ADRESSE_MAIL, TYPE_CLIENT, REMISE, RESSOURCE_ASSOSIE, IMAGE_PATH) "
                  "VALUES (:num_cin, :nom_complet, :adresse, :adresse_mail, :type_client, :remise, :ressource_associe, :image_path)");
    query.bindValue(":num_cin", getNumCin());
    query.bindValue(":nom_complet", getNomComplet());
    query.bindValue(":adresse", getAdresse());
    query.bindValue(":adresse_mail", getAdresseMail());
    query.bindValue(":type_client", getTypeClient());
    query.bindValue(":remise", getRemise());
    query.bindValue(":ressource_associe", getRessourceAssocie());
    query.bindValue(":image_path", getImagePath()); // Bind image path

    if (query.exec()) {
        QMessageBox::information(this, "Success", "Client added successfully.");
        return true;
    } else {
        QMessageBox::warning(this, "Error", "Failed to add client: " + query.lastError().text());
        return false;
    }
}

bool AddClient::updateClientToDatabase() {
    QSqlQuery query;
    query.prepare("UPDATE CLIENT SET NOM_COMPLET = :nom_complet, ADRESSE = :adresse, ADRESSE_MAIL = :adresse_mail, "
                  "TYPE_CLIENT = :type_client, REMISE = :remise, RESSOURCE_ASSOSIE = :ressource_associe, IMAGE_PATH = :image_path "
                  "WHERE NUM_CIN = :num_cin");

    query.bindValue(":num_cin", getNumCin());
    query.bindValue(":nom_complet", getNomComplet());
    query.bindValue(":adresse", getAdresse());
    query.bindValue(":adresse_mail", getAdresseMail());
    query.bindValue(":type_client", getTypeClient());
    query.bindValue(":remise", getRemise());
    query.bindValue(":ressource_associe", getRessourceAssocie());
    query.bindValue(":image_path", getImagePath()); // Bind image path

    if (query.exec()) {
        QMessageBox::information(this, "Success", "Client updated successfully.");
        return true;
    } else {
        QMessageBox::warning(this, "Error", "Failed to update client: " + query.lastError().text());
        return false;
    }
}

void AddClient::onUploadImageClicked() {
    QString filePath = QFileDialog::getOpenFileName(this, "Select Image", "", "Images (*.png *.jpg *.jpeg *.bmp);;All Files (*)");
    if (!filePath.isEmpty()) {
        imagePath = filePath; // Store the selected image path
        QPixmap pixmap(imagePath);
        ui->imageLabel->setPixmap(pixmap.scaled(150, 150, Qt::KeepAspectRatio)); // Display the image in the QLabel
    } else {
        QMessageBox::warning(this, "Image Upload", "No image selected.");
    }
}
