#include "mainwindowgestionemployer.h"
#include"employer.h"
#include "ui_mainwindowgestionemployer.h"
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QFileDialog>
#include <QTableView>
#include <QPieSeries>
#include <QChartView>
#include <QChart>
#include <QPainter>
#include <QLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QPixmap>
#include <QLabel>
#include <QStandardPaths>
#include <QImage>
#include <QInputDialog>
#include <QCryptographicHash>
#include <QVBoxLayout>
#include "arduinogestionemployer.h"


//integration client :
#include "addclient.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include <QMessageBox>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QValueAxis>
#include <QtCharts/QBarCategoryAxis>
#include <QSqlRecord>


//vehicules
#include "vehicules.h"
#include <QString>
#include <QApplication>
#include <QMessageBox>
#include <QProcess>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QFileDialog>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QVBoxLayout>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QPushButton>
#include <QStyledItemDelegate>
#include <QPainter>
#include <QDateTime>
#include <QItemDelegate>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QtCharts>
#include <QMessageBox>
#include <QSqlQuery>
#include <QChartView>
#include <QBarSeries>
#include <QBarSet>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QObject>
#include <QtSql>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) ,ui(new Ui::MainWindow)
    , serial(new QSerialPort(this))
{
    ui->setupUi(this);
     // Connecter le signal du bouton au slot de vérification
    identifiants.insert("gestionvéhicule", QPair<QString, QString>("vehicule_admin", "password123"));
    identifiants.insert("gestionclient", QPair<QString, QString>("client_admin", "password456"));
    identifiants.insert("gestionlocaux", QPair<QString, QString>("locaux_admin", "password789"));
    identifiants.insert("gestionequipement", QPair<QString, QString>("equipement_admin", "password321"));
    identifiants.insert("gestionfacture", QPair<QString, QString>("facture_admin", "password654"));
    // Connect buttons to corresponding functions
    connect(ui->GestionVehicule, &QPushButton::clicked, this, &MainWindow::onGestionVehicule);
    connect(ui->GestionClient, &QPushButton::clicked, this, &MainWindow::onGestionClient);
    connect(ui->GestionLocaux, &QPushButton::clicked, this, &MainWindow::onGestionLocaux);
    connect(ui->GestionEquipement, &QPushButton::clicked, this, &MainWindow::onGestionEquipement);
    connect(ui->GestionFacture, &QPushButton::clicked, this, &MainWindow::onGestionFacture);
    connect(ui->gestionemployer, &QPushButton::clicked, this, &MainWindow::onGestionEmployerClicked);
    connect(ui->verifier, &QPushButton::clicked, this, &MainWindow::on_verifier_clicked);
    serial = new QSerialPort(this);
    serial->setPortName("COM6"); // Utilisez le bon port COM


    if (serial->open(QIODevice::WriteOnly)) {
        qDebug() << "Port série ouvert";
    } else {
        qDebug() << "Erreur d'ouverture du port série : " << serial->errorString();
    }

    loadClientData();


    connect(ui->addButton_2, &QPushButton::clicked, this, &MainWindow::on_addButton_clicked);
    connect(ui->removeButton_2, &QPushButton::clicked, this, &MainWindow::on_removeButton_clicked);
    connect(ui->chercherbut_2, &QPushButton::clicked, this, &MainWindow::onChercherButClicked);
    connect(ui->sort_2, &QPushButton::clicked, this, &MainWindow::onSortClicked);
    connect(ui->pdf_2, &QPushButton::clicked, this, &MainWindow::onPdfClicked);
    connect(ui->stats_2, &QPushButton::clicked, this, &MainWindow::onStatsClicked);
    connect(ui->load_2, &QPushButton::clicked, this, &MainWindow::onLoadClicked);
    connect(ui->backup_2, &QPushButton::clicked, this, &MainWindow::onBackupClicked);
    connect(ui->restore_2, &QPushButton::clicked, this, &MainWindow::onRestoreClicked);
    connect(ui->importImageButton_2, &QPushButton::clicked, this, &MainWindow::onImportImageButtonClicked);
    connect(ui->tableView_2->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWindow::onTableViewSelectionChanged);
    connect(ui->tableView_2->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWindow::onTableViewSelectionChanged);
    connect(ui->employee1, &QPushButton::clicked, this, &MainWindow::gotoemployee);
    connect(ui->employee2, &QPushButton::clicked, this, &MainWindow::gotoemployee);
    connect(ui->client1, &QPushButton::clicked, this, &MainWindow::gotoclient);
    connect(ui->client2, &QPushButton::clicked, this, &MainWindow::gotoclient);
    connect(ui->vehicule, &QPushButton::clicked, this, &MainWindow::gotovehicule);

//vehicules

    ui->Aff->setModel(V.afficher());


    // Initialiser le modèle
    model = new QSqlTableModel(this);
    model->setTable("Vehicules");
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->select();

    ui->Aff->setModel(model);
    ui->setupUi(this);
    ui->Aff->setModel(V.afficher());


    // Initialiser le modèle
    model = new QSqlTableModel(this);
    model->setTable("Vehicules");
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->select();

    ui->Aff->setModel(model);


    conversationModel = new QStandardItemModel(this);
    conversationModel->setHorizontalHeaderLabels({"Message"});
    ui->chatbotview->setModel(conversationModel);
    ui->chatbotview->resizeColumnsToContents();

    connect(ui->Chatbutton, &QPushButton::clicked, this, &MainWindow::on_chatbutton_clicked);
    connect(ui->alertes, &QPushButton::clicked, this, &MainWindow::on_alertes_clicked);
    connect(ui->modify, &QPushButton::clicked, this, &MainWindow::on_modify_clicked);
    connect(ui->cancel, &QPushButton::clicked, this, &MainWindow::on_cancel_clicked);
    connect(arduino, &arduinov::dataReceived, this, &MainWindow::handleArduinoData);
    connect(arduino, &arduinov::matriculeVerified, this, &MainWindow::onMatriculeVerified);

}

void MainWindow::gotoemployee() {
    ui->stackedWidget->setCurrentWidget(ui->employeepage);
}
void MainWindow::gotoclient() {
    ui->stackedWidget->setCurrentWidget(ui->omarclient);
}

void MainWindow::gotovehicule()
{
    ui->stackedWidget->setCurrentWidget(ui->habiba);
}
MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_ajouterButton_clicked() {
    int id = ui->l1->text().toInt();
    QString nomemployee = ui->l2->text();
    int age = ui->l3->text().toInt();
    int num_telephone = ui->l4->text().toInt();
    int date_embauche = ui->l5->text().toInt();
    QString adresse = ui->l6->text();
    QString email = ui->l7->text();

    if (Employer.ajouter(id, age, nomemployee, adresse, email, num_telephone, date_embauche)) {
        QMessageBox::information(this, "Succès", "Employé ajouté avec succès.");
        QString message = QString("Employé ajouté avec succès à %1").arg(QDateTime::currentDateTime().toString("HH:mm:ss"));
        afficherNotification(message);
        on_afficherButton_clicked();  // Rafraîchir l'affichage après l'ajout
    } else {
        QMessageBox::warning(this, "Erreur", "Erreur lors de l'ajout de l'employé.");
    }
}
void MainWindow::on_afficherButton_clicked() {
    int id = ui->l1->text().toInt();
    qDebug() << "ID employé recherché : " << id;

    QSqlQuery query;
    query.prepare("SELECT AGE, NOMEMPLOYEE, ADRESSE, EMAIL, NUM_TELEPHONE, DATE_EMBAUCHE FROM EMPLOYER WHERE ID = :id");
    query.bindValue(":id", id);

    if (query.exec()) {
        if (query.next()) {
            ui->l3->setText(query.value("AGE").toString());
            ui->l2->setText(query.value("NOMEMPLOYEE").toString());
            ui->l6->setText(query.value("ADRESSE").toString());
            ui->l7->setText(query.value("EMAIL").toString());
            ui->l4->setText(query.value("NUM_TELEPHONE").toString());
            ui->l5->setText(query.value("DATE_EMBAUCHE").toString());

             // Afficher les données dans tableView_employes
        } else {
            QMessageBox::warning(this, "Erreur", "Employé non trouvé.");
        }
    } else {
        QMessageBox::warning(this, "Erreur SQL", "Erreur lors de la requête : " + query.lastError().text());
    }
}

void MainWindow::on_miseajourButton_clicked() {
    int id = ui->l1->text().toInt();
    int age = ui->l3->text().toInt();
    QString nomemployee = ui->l2->text();
    QString adresse = ui->l6->text();
    QString email = ui->l7->text();
    int num_telephone = ui->l4->text().toInt();
    int date_embauche = ui->l5->text().toInt();

    // Création de la requête SQL pour mettre à jour l'employé
    QSqlQuery query;
    query.prepare("UPDATE EMPLOYER SET NOMEMPLOYEE = :nomemployee, ADRESSE = :adresse, "
                  "EMAIL = :email, NUM_TELEPHONE = :num_telephone, DATE_EMBAUCHE = :date_embauche, "
                  "AGE = :age WHERE ID = :id");

    // Lier les valeurs aux paramètres dans la requête
    query.bindValue(":nomemployee", nomemployee);
    query.bindValue(":adresse", adresse);
    query.bindValue(":email", email);
    query.bindValue(":num_telephone", num_telephone);
    query.bindValue(":date_embauche", date_embauche);
    query.bindValue(":age", age);  // Lier l'age à la requête
    query.bindValue(":id", id);

    if (query.exec()) {
        QMessageBox::information(this, "Succès", "Informations de l'employé mises à jour avec succès.");
        QString message = QString("Employé modifié avec succès à %1").arg(QDateTime::currentDateTime().toString("HH:mm:ss"));
        afficherNotification(message);
    } else {
        QMessageBox::warning(this, "Erreur", "Erreur lors de la mise à jour de l'employé.");
    }
}

void MainWindow::on_supprimerButton_clicked(){
    int id = ui->l1->text().toInt();
class Employer employer;
if (employer.supprimer(id)) {
    QMessageBox::information(this, "Succès", "Employé supprimé avec succès.");
    QString message = QString("Employé supprimer avec succès à %1").arg(QDateTime::currentDateTime().toString("HH:mm:ss"));
    afficherNotification(message);
} else {
    // Affichage d'un message d'erreur en cas de problème
    QMessageBox::warning(this, "Erreur", "Erreur lors de la suppression de l'employé.");
}
}
void MainWindow::on_PDF_clicked()
{
    QString nomFichier = QFileDialog::getSaveFileName(this, "Enregistrer le PDF", "", "Fichiers PDF (*.pdf)");
    if (!nomFichier.isEmpty()) {
        class Employer employer;
        QSqlQueryModel *model = employer.afficherEmployes();  // Appeler la méthode afficherEmployes() qui retourne un modèle

        if (model) {
            employer.exporterPDF(nomFichier, model);

            // Libérer la mémoire allouée pour le modèle
            delete model;
            QMessageBox::information(this, "Exportation PDF", "Exportation vers PDF réussie !");
        } else {
            // Si la récupération des données échoue, afficher un message d'erreur
            QMessageBox::warning(this, "Erreur", "Erreur lors de la récupération des données.");
        }
    }
}

void MainWindow::on_trier_clicked() {
    ui->tableView_employes->setModel(Employer.afficherTriParId());
    QMessageBox::information(this, tr("Tri par ID"), tr("Les employés ont été triés par ID."), QMessageBox::Ok);
}
void MainWindow::on_Rechrche_clicked()
{
    int id = ui->l11->text().toInt();
    QSqlQueryModel* model = Employer.rechercherParId(id);

    if (model != nullptr) {
        if (model->rowCount() > 0) {
            ui->tableView_employes->setModel(model);
            QMessageBox::information(this, "Recherche", "L'employé a été trouvé.");
        } else {
            QMessageBox::information(this, "Recherche", "Aucun employé trouvé avec cet ID.");
            delete model;
        }
    }
    else {
        QMessageBox::critical(this, "Erreur", "Erreur lors de la recherche de l'employé.");
    }
}
void MainWindow::on_statistique_clicked() {
    ui->tabWidget->setCurrentIndex(1);
    QLayoutItem* item;

    // Vider le layout avant d'ajouter de nouveaux éléments
    while ((item = ui->verticalLayout->takeAt(0)) != nullptr) {
        delete item;  // Libère la mémoire de l'élément
    }

    // Obtenez les statistiques par tranche d'âge depuis la classe Employer
    QMap<QString, int> statistiques = Employer::statistiquesParTrancheAge();

    // Calculer le total des employés
    int totalEmployes = 0;
    for (auto it = statistiques.constBegin(); it != statistiques.constEnd(); ++it) {
        totalEmployes += it.value();
    }

    // Créer un pie series pour le graphique
    QPieSeries *series = new QPieSeries();

    // Ajouter les données des tranches d'âge dans le graphique avec le pourcentage
    for (auto it = statistiques.constBegin(); it != statistiques.constEnd(); ++it) {
        QString trancheAge = it.key();
        int count = it.value();
        double percentage = (totalEmployes > 0) ? (count * 100.0 / totalEmployes) : 0.0;

        // Ajouter l'élément avec le pourcentage
        QString label = QString("%1: %2%").arg(trancheAge).arg(percentage, 0, 'f', 1);
        series->append(label, count);
    }

    // Créer un graphique à partir de la série
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistiques des employés par tranche d'âge");

    // Créer un chart view pour afficher le graphique
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Afficher le graphique dans un layout
    ui->verticalLayout->addWidget(chartView); // Ajoutez le graphique au layout
}
void MainWindow::afficherNotification(const QString &message)
{
    QString dateHeure = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");

    // Ajouter la date et l'heure au message
    QString messageAvecDate = message + " Date et Heure: " + dateHeure;
    QString filePath = "notifications.txt";

    // Ouvrir le fichier en mode ajout
    QFile file(filePath);
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << messageAvecDate << "\n";  // Écrire le message dans le fichier
        file.close();  // Fermer le fichier après l'écriture
    } else {
        QMessageBox::warning(nullptr, "Erreur", "Impossible d'ouvrir le fichier pour enregistrer la notification.");
    }
    QMessageBox::information(this, "Notification", messageAvecDate);
}

void MainWindow::on_notification_clicked() {
    QString message = "Dernière action effectuée: ";
    afficherNotification(message);
    QMessageBox::information(this, "Notification", "Dernière action effectuée:!");
}

bool MainWindow::verifierIdentifiants(const QString &module, const QString &username, const QString &password)
{
    // Vérification des identifiants pour chaque module
    if (identifiants.contains(module)) {
        QPair<QString, QString> cred = identifiants[module];
        // Optionally, hash the password and compare it to a hashed value (recommended)
        QString hashedPassword = QString(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex());
        return (username == cred.first && hashedPassword == cred.second); // Compare hashed passwords
    }
    return false;  // Module inconnu ou identifiants incorrects
}

bool MainWindow::authenticate(const QString &username, const QString &password)
{
    // Identifiants valides (statique dans cet exemple)
    const QString validUsername = "admin";
    const QString validPassword = "1234";

    return username == validUsername && password == validPassword;
}

void MainWindow::onGestionVehicule()
{
    // Using QInputDialog to get username and password securely
    QString username = QInputDialog::getText(this, "Connexion", "Nom d'utilisateur :");
    QString password = QInputDialog::getText(this, "Connexion", "Mot de passe :", QLineEdit::Password);

    if (verifierIdentifiants("gestionvéhicule", username, password)) {
        QMessageBox::information(this, "Succès", "Bienvenue dans Gestion Véhicule !");
    } else {
        QMessageBox::warning(this, "Erreur", "Identifiants incorrects !");
    }
}

void MainWindow::onGestionClient()
{
    QString username = QInputDialog::getText(this, "Connexion", "Nom d'utilisateur :");
    QString password = QInputDialog::getText(this, "Connexion", "Mot de passe :", QLineEdit::Password);

    if (verifierIdentifiants("gestionclient", username, password)) {
        QMessageBox::information(this, "Succès", "Bienvenue dans Gestion Client !");
    } else {
        QMessageBox::warning(this, "Erreur", "Identifiants incorrects !");
    }
}

void MainWindow::onGestionLocaux()
{
    QString username = QInputDialog::getText(this, "Connexion", "Nom d'utilisateur :");
    QString password = QInputDialog::getText(this, "Connexion", "Mot de passe :", QLineEdit::Password);

    if (verifierIdentifiants("gestionlocaux", username, password)) {
        QMessageBox::information(this, "Succès", "Bienvenue dans Gestion Locaux !");
    } else {
        QMessageBox::warning(this, "Erreur", "Identifiants incorrects !");
    }
}

void MainWindow::onGestionEquipement()
{
    QString username = QInputDialog::getText(this, "Connexion", "Nom d'utilisateur :");
    QString password = QInputDialog::getText(this, "Connexion", "Mot de passe :", QLineEdit::Password);

    if (verifierIdentifiants("gestionequipement", username, password)) {
        QMessageBox::information(this, "Succès", "Bienvenue dans Gestion Équipement !");
    } else {
        QMessageBox::warning(this, "Erreur", "Identifiants incorrects !");
    }
}

void MainWindow::onGestionFacture()
{
    QString username = QInputDialog::getText(this, "Connexion", "Nom d'utilisateur :");
    QString password = QInputDialog::getText(this, "Connexion", "Mot de passe :", QLineEdit::Password);

    if (verifierIdentifiants("gestionfacture", username, password)) {
        QMessageBox::information(this, "Succès", "Bienvenue dans Gestion Facture !");
    } else {
        QMessageBox::warning(this, "Erreur", "Identifiants incorrects !");
    }
}

void MainWindow::onGestionEmployerClicked()
{
    // Boîte de dialogue pour le nom d'utilisateur
    bool ok;
    QString username = QInputDialog::getText(this, "Authentification",
                                             "Nom d'utilisateur :", QLineEdit::Normal,
                                             "", &ok);
    if (!ok || username.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Nom d'utilisateur requis !");
        return;
    }

    // Boîte de dialogue pour le mot de passe
    QString password = QInputDialog::getText(this, "Authentification",
                                             "Mot de passe :", QLineEdit::Password,
                                             "", &ok);
    if (!ok || password.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Mot de passe requis !");
        return;
    }

    // Vérifiez les identifiants (statiques pour cet exemple)
    if (username == "admin" && password == "1234") {
        QMessageBox::information(this, "Succès", "Connexion réussie !");
        // Basculez vers la page "Employé"
        ui->tabWidget->setCurrentIndex(1); // Remplacez "1" par l'index de la page employé
    } else {
        QMessageBox::critical(this, "Erreur", "Nom d'utilisateur ou mot de passe incorrect !");
    }
}

void MainWindow::on_verifier_clicked()
{
    QString inputmatricule = ui->matriculeInput->text();

    if (inputmatricule.isEmpty()) {
        QMessageBox::warning(this, "Entrée manquante", "Veuillez saisir une date.");
        return;
    }

    // Préparer la requête SQL pour vérifier les rendez-vous pour la date saisie
    QSqlQuery query;
    query.prepare("SELECT rendez_vous, status FROM vehicule WHERE matricule = :matricule");
    query.bindValue(":matricule", inputmatricule);

    if (!query.exec()) {
        qDebug() << "Erreur de requête SQL : " << query.lastError().text();
        return;
    }

    // Si la date existe dans la base de données
    if (query.next()) {
        QString date_rendezvous = query.value(0).toString();
        QString status = query.value(1).toString();

        // Formatage du message à envoyer à l'Arduino
        QString message = "Date: " + date_rendezvous+ "\n"+ status + "\n";

        // Envoyer le message à l'Arduino via le port série
        if (serial->isOpen() && serial->isWritable()) {
            qDebug() << "Envoi du message à l'Arduino : " << message; // Debug message
            serial->write(message.toUtf8());
        } else {
            qDebug() << "Le port série n'est pas prêt.";
        }
    } else {
        // Si la date n'existe pas, envoyer un message à l'Arduino
        QString message = "Aucun rendez-vous pour la matricule: " + inputmatricule + "\n";
        if (serial->isOpen() && serial->isWritable()) {
            qDebug() << "Aucun rendez-vous trouvé pour cette matricule.";
            serial->write(message.toUtf8());
        }
    }
}

void MainWindow::onImportImageButtonClicked()
{
    QModelIndexList selectedRows = ui->tableView_2->selectionModel()->selectedRows();
    if (selectedRows.isEmpty()) {
        QMessageBox::warning(this, "Selection Error", "No row selected.");
        return;
    }

    QString imagePath = QFileDialog::getOpenFileName(this, "Select Image", "", "Images (*.png *.jpg *.jpeg *.bmp);;All Files (*)");
    if (imagePath.isEmpty()) return;

    int row = selectedRows[0].row();
    QString numCin = ui->tableView_2->model()->index(row, 0).data().toString();

    QSqlQuery query;
    query.prepare("UPDATE CLIENT SET IMAGE_PATH = :imagePath WHERE NUM_CIN = :numCin");
    query.bindValue(":imagePath", imagePath);
    query.bindValue(":numCin", numCin);

    if (query.exec()) {
        QMessageBox::information(this, "Success", "Image updated successfully.");
        onTableViewSelectionChanged();  // Refresh image display
    } else {
        QMessageBox::warning(this, "Error", "Failed to update image: " + query.lastError().text());
    }
}

void MainWindow::onTableViewSelectionChanged()
{
    QModelIndexList selectedRows = ui->tableView_2->selectionModel()->selectedRows();
    if (selectedRows.isEmpty()) {
        ui->imageLabel_2->clear();
        return;
    }

    int row = selectedRows[0].row();
    QString numCin = ui->tableView_2->model()->index(row, 0).data().toString();

    QSqlQuery query;
    query.prepare("SELECT IMAGE_PATH FROM CLIENT WHERE NUM_CIN = :numCin");
    query.bindValue(":numCin", numCin);

    if (query.exec() && query.next()) {
        QString imagePath = query.value("IMAGE_PATH").toString();
        if (!imagePath.isEmpty()) {
            QPixmap pixmap(imagePath);
            ui->imageLabel_2->setPixmap(pixmap.scaled(150, 150, Qt::KeepAspectRatio));
        } else {
            ui->imageLabel_2->setText("No Image");
        }
    } else {
        ui->imageLabel_2->setText("Error Loading Image");
    }
}


void MainWindow::loadClientData()
{

    QSqlQueryModel *model = new QSqlQueryModel(this);


    model->setQuery("SELECT NUM_CIN, NOM_COMPLET, ADRESSE, ADRESSE_MAIL, TYPE_CLIENT, REMISE, RESSOURCE_ASSOSIE FROM CLIENT");


    if (model->lastError().isValid()) {
        qDebug() << "Error loading data from database: " << model->lastError().text();
        return;
    }
    ui->tableView_2->setModel(model);
    ui->tableView_2->resizeColumnsToContents();
}

void MainWindow::on_addButton_clicked()
{
    AddClient addClientDialog(this);

    if (addClientDialog.exec() == QDialog::Accepted) {
        if (addClientDialog.addClientToDatabase()) {
            loadClientData();  // Reload data in the table view
            selectLastAddedClient(addClientDialog.getNumCin());  // Select and display the last added client
        }
    }
}


void MainWindow::on_removeButton_clicked()
{

    QModelIndexList selectedRows = ui->tableView_2->selectionModel()->selectedRows();

    if (selectedRows.size() > 0) {
        int row = selectedRows[0].row();
        QString numCin = ui->tableView_2->model()->index(row, 0).data().toString();


        QSqlQuery query;
        query.prepare("DELETE FROM CLIENT WHERE NUM_CIN = :numCin");
        query.bindValue(":numCin", numCin);


        if (query.exec()) {
            QMessageBox::information(this, "Success", "Client removed successfully.");
            loadClientData();
        } else {
            QMessageBox::warning(this, "Error", "Failed to remove client: " + query.lastError().text());
        }
    } else {
        QMessageBox::warning(this, "Error", "No client selected for removal.");
    }
}




void MainWindow::on_pb_select_clicked()
{
    AddClient addClientDialog(this);

    if (addClientDialog.exec() == QDialog::Accepted) {

        addClientDialog.updateClientToDatabase();


        loadClientData();
    }
}
void MainWindow::onChercherButClicked()
{
    QString searchText = ui->chercher_2->text().trimmed();
    QString selectedColumn;

    if (ui->sortbox_2->currentText() == "Nom") {
        selectedColumn = "NOM_COMPLET";
    } else if (ui->sortbox_2->currentText() == "Role") {
        selectedColumn = "TYPE_CLIENT";
    } else {
        QMessageBox::warning(this, "Search Error", "Please select a valid search category.");
        return;
    }

    QSqlQueryModel *model = new QSqlQueryModel(this);
    QString query = QString("SELECT NUM_CIN, NOM_COMPLET, ADRESSE, ADRESSE_MAIL, TYPE_CLIENT, REMISE, RESSOURCE_ASSOSIE FROM CLIENT WHERE LOWER(%1) LIKE LOWER('%%2%')").arg(selectedColumn).arg(searchText);
    model->setQuery(query);

    if (model->lastError().isValid()) {
        qDebug() << "Error searching data: " << model->lastError().text();
        return;
    }

    ui->tableView_2->setModel(model);
    ui->tableView_2->resizeColumnsToContents();
}

void MainWindow::onSortClicked()
{
    QString selectedOption = ui->sortbox_2->currentText();
    QString sortColumn;

    if (selectedOption == "Nom") {
        sortColumn = "LOWER(NOM_COMPLET)";
    } else if (selectedOption == "Role") {
        sortColumn = "LOWER(TYPE_CLIENT)";
    } else {
        QMessageBox::warning(this, "Sort Error", "Please select a valid sort category.");
        return;
    }

    QSqlQueryModel *model = new QSqlQueryModel(this);
    QString query = QString("SELECT NUM_CIN, NOM_COMPLET, ADRESSE, ADRESSE_MAIL, TYPE_CLIENT, REMISE, RESSOURCE_ASSOSIE FROM CLIENT ORDER BY %1 ASC").arg(sortColumn);
    model->setQuery(query);

    if (model->lastError().isValid()) {
        qDebug() << "Error sorting data: " << model->lastError().text();
        return;
    }

    ui->tableView_2->setModel(model);
    ui->tableView_2->resizeColumnsToContents();
}

void MainWindow::onPdfClicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save PDF"), "", tr("PDF Files (*.pdf);;All Files (*)"));
    if (fileName.isEmpty()) return;

    QPdfWriter pdfWriter(fileName);
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));
    pdfWriter.setResolution(300);

    QPainter painter(&pdfWriter);
    painter.setFont(QFont("Arial", 12));
    painter.drawText(100, 100, "Client Data");

    int yOffset = 150;
    QSqlQuery query("SELECT NUM_CIN, NOM_COMPLET, ADRESSE, ADRESSE_MAIL, TYPE_CLIENT, REMISE, RESSOURCE_ASSOSIE FROM CLIENT");

    while (query.next()) {
        painter.drawText(100, yOffset, "CIN: " + query.value("NUM_CIN").toString());
        yOffset += 30;
        painter.drawText(100, yOffset, "Name: " + query.value("NOM_COMPLET").toString());
        yOffset += 30;
        painter.drawText(100, yOffset, "Address: " + query.value("ADRESSE").toString());
        yOffset += 30;
        painter.drawText(100, yOffset, "Email: " + query.value("ADRESSE_MAIL").toString());
        yOffset += 30;
        painter.drawText(100, yOffset, "Client Type: " + query.value("TYPE_CLIENT").toString());
        yOffset += 30;
        painter.drawText(100, yOffset, "Discount: " + query.value("REMISE").toString());
        yOffset += 30;
        painter.drawText(100, yOffset, "Associated Resource: " + query.value("RESSOURCE_ASSOSIE").toString());
        yOffset += 50;  // Space between records
    }

    painter.end();
    QMessageBox::information(this, tr("PDF Generated"), tr("The client data has been saved as a PDF."));
}

void MainWindow::onStatsClicked()
{
    QBarSeries *series = new QBarSeries();
    QBarSet *set = new QBarSet("Clients by Type");

    QSqlQuery query("SELECT TYPE_CLIENT, COUNT(*) as client_count FROM CLIENT GROUP BY TYPE_CLIENT");

    while (query.next()) {
        *set << query.value("client_count").toInt();
    }

    series->append(set);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Client Statistics by Type");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(query.value("TYPE_CLIENT").toStringList());
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Number of Clients");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QMainWindow *statsWindow = new QMainWindow();
    statsWindow->setCentralWidget(chartView);
    statsWindow->resize(800, 600);
    statsWindow->show();
}

void MainWindow::onLoadClicked()
{
    loadClientData();
}

void MainWindow::onBackupClicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Backup"), "", tr("CSV Files (*.csv);;All Files (*)"));
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "File Error", "Unable to open file for backup.");
        return;
    }

    QTextStream out(&file);

    QSqlQuery query("SELECT NUM_CIN, NOM_COMPLET, ADRESSE, ADRESSE_MAIL, TYPE_CLIENT, REMISE, RESSOURCE_ASSOSIE, IMAGE_PATH FROM CLIENT");
    while (query.next()) {
        QStringList rowData;
        for (int i = 0; i < query.record().count(); ++i) {
            rowData << query.value(i).toString();  // Add all fields including IMAGE_PATH
        }
        out << rowData.join(",") << "\n";  // Write each row as comma-separated
    }

    file.close();
    QMessageBox::information(this, "Backup Completed", "Data has been backed up successfully, including image paths.");
}

void MainWindow::onRestoreClicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Restore Backup"), "", tr("CSV Files (*.csv);;All Files (*)"));
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "File Error", "Unable to open file for restore.");
        return;
    }

    QTextStream in(&file);
    QSqlDatabase::database().transaction();  // Start a transaction to ensure data integrity

    QSqlQuery query;
    query.exec("DELETE FROM CLIENT");  // Clear the table before restoring

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(",");

        if (fields.size() == 8) {  // Ensure there are 8 fields (including IMAGE_PATH)
            query.prepare("INSERT INTO CLIENT (NUM_CIN, NOM_COMPLET, ADRESSE, ADRESSE_MAIL, TYPE_CLIENT, REMISE, RESSOURCE_ASSOSIE, IMAGE_PATH) "
                          "VALUES (:numCin, :nomComplet, :adresse, :adresseMail, :typeClient, :remise, :ressource, :imagePath)");
            query.bindValue(":numCin", fields[0]);
            query.bindValue(":nomComplet", fields[1]);
            query.bindValue(":adresse", fields[2]);
            query.bindValue(":adresseMail", fields[3]);
            query.bindValue(":typeClient", fields[4]);
            query.bindValue(":remise", fields[5]);
            query.bindValue(":ressource", fields[6]);
            query.bindValue(":imagePath", fields[7]);  // Restore the image path

            if (!query.exec()) {
                qDebug() << "Error restoring row:" << query.lastError().text();
                QMessageBox::warning(this, "Restore Error", "Error restoring data.");
                QSqlDatabase::database().rollback();  // Rollback if there's an error
                return;
            }
        } else {
            QMessageBox::warning(this, "Restore Error", "Invalid data format in backup file.");
        }
    }

    QSqlDatabase::database().commit();  // Commit the transaction
    file.close();
    loadClientData();  // Refresh the view
    QMessageBox::information(this, "Restore Completed", "Data has been restored successfully, including image paths.");
}

void MainWindow::selectLastAddedClient(const QString &numCin)
{
    // Look for the row corresponding to the newly added client
    QAbstractItemModel *model = ui->tableView_2->model();
    for (int row = 0; row < model->rowCount(); ++row) {
        QModelIndex index = model->index(row, 0);  // Assuming NUM_CIN is in the first column
        if (index.data().toString() == numCin) {
            ui->tableView_2->selectRow(row);  // Select the row
            onTableViewSelectionChanged();  // Refresh image display
            return;
        }
    }
}

void MainWindow::on_ajouter_clicked()
{
    QString num_matricule = ui->reponsematricule->text();
    QString marque = ui->reponsemarque->text();
    QString modele = ui->reponsemodele->text();
    QString kilometrages = ui->reponsekilometrages->text();
    int annee_fab = ui->reponseanneefab->text().toInt();
    QString id_client = ui->reponseidclient->text();
    QString etat = ui->reponseetat->text();
    QString assurance = ui->reponseassurance->text();

    if (V.ajouter(num_matricule, marque, modele, kilometrages, annee_fab, id_client, etat, assurance))
    {
        ui->Aff->setModel(V.afficher());
        qDebug() << "Véhicule ajouté et modèle mis à jour!";
    }
    else
    {
        qDebug() << "Erreur lors de l'ajout du véhicule!";
    }
}



void MainWindow::on_supprimer_clicked()
{
    QString num_matricule = ui->recherche->text();

    // Vérification du numéro de matricule
    QRegularExpression matriculeRegex("^\\d{3}(tunis|nt|etranger)\\d{4}$");
    QRegularExpressionMatch matriculeMatch = matriculeRegex.match(num_matricule);

    if (!matriculeMatch.hasMatch())
    {
        QMessageBox::warning(this, "Erreur", "Numéro de matricule invalide. Format attendu : 123tunis1234.");
        return;
    }

    bool test = V.supprimer(num_matricule);

    if (test)
    {
        QMessageBox::information(this, "Suppression", "Le véhicule a été supprimé avec succès.");
        ui->Aff->setModel(V.afficher());
    }
    else
    {
        QMessageBox::warning(this, "Erreur", "Échec de la suppression. Vérifiez si le numéro de matricule existe.");
    }
}


void MainWindow::on_modifier_clicked()
{
    QString num_matricule = ui->reponsematricule->text();
    QString marque = ui->reponsemarque->text();
    QString modele = ui->reponsemodele->text();
    QString kilometrages = ui->reponsekilometrages->text();
    int annee_fab = ui->reponseanneefab->text().toInt();
    QString id_client = ui->reponseidclient->text();
    QString etat = ui->reponseetat->text();
    QString assurance = ui->reponseassurance->text();


    Vehicules V(num_matricule, marque, modele, kilometrages, annee_fab, id_client, etat, assurance);
    bool test = V.modifier();

    if (test)
    {
        QMessageBox::information(this, "Succès", "Le véhicule a été modifié avec succès.");
        ui->Aff->setModel(V.afficher());
    }
    else
    {
        QMessageBox::critical(this, "Erreur", "Échec de la modification du véhicule.");
    }
}


void MainWindow::on_trie_clicked()
{
    ui->Aff->setModel(V.trierParModele());


    QMessageBox::information(this, "Tri", "Les véhicules ont été triés par modèle.");

}


void MainWindow::on_rechercher_clicked()
{
    QString num_matricule = ui->recherche->text();

    QRegularExpression matriculeRegex("^\\d{3}(tunis|nt|etranger)\\d{4}$");
    QRegularExpressionMatch matriculeMatch = matriculeRegex.match(num_matricule);

    if (!matriculeMatch.hasMatch())
    {
        QMessageBox::warning(this, "Erreur", "Le numéro de matricule n'est pas valide. Format attendu : 123tunis1234.");
        return;
    }

    QSqlQueryModel* model = V.rechercher(num_matricule);

    if (model->rowCount() > 0)
    {
        ui->Aff->setModel(model);
        QMessageBox::information(this, "Recherche", "Le véhicule a été trouvé.");
    }
    else
    {
        QMessageBox::information(this, "Recherche", "Aucun véhicule trouvé avec ce numéro de matricule.");
    }
}


void MainWindow::on_pdf_clicked()
{
    QString nomFichier = QFileDialog::getSaveFileName(this, "Enregistrer le PDF", "", "Fichiers PDF (*.pdf)");



    if (!nomFichier.isEmpty())
    {
        Vehicules V;

        QSqlQueryModel *model = V.afficher();

        V.exporterPDF(nomFichier, model);

        delete model;

        QMessageBox::information(this, "Exportation PDF", "Exportation vers PDF réussie !");
    }
}


void MainWindow::on_stat_clicked()
{
    QStringList categories;
    QVector<QString> modele = {"renault", "bmw", "mercedes", "toyota","suzuki","hundai"};
    QVector<int> counts = {3, 1, 2, 1,3,2};

    categories << "semaine 1" << "semaine 2" << "semaine 3" << "semaine 4"<<"semaine 5";

    if (!chartView)
    {
        QBarSeries *series = new QBarSeries();

        for (int i = 0; i < modele.size(); ++i)
        {
            QBarSet *set = new QBarSet(modele[i]);
            *set << counts[i];
            series->append(set);
        }

        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("Modèles Ajoutés par Semaine - Mois Actuel");
        chart->setAnimationOptions(QChart::SeriesAnimations);

        QBarCategoryAxis *axisX = new QBarCategoryAxis();
        axisX->append(categories);
        chart->addAxis(axisX, Qt::AlignBottom);
        series->attachAxis(axisX);

        QValueAxis *axisY = new QValueAxis();
        axisY->setRange(0, *std::max_element(counts.begin(), counts.end()) + 5);
        chart->addAxis(axisY, Qt::AlignLeft);
        series->attachAxis(axisY);

        chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);

        if (!ui->statistique->layout())
        {
            ui->statistiques->setLayout(new QVBoxLayout());
        }

        ui->statistiques->layout()->addWidget(chartView);
    }
}




void MainWindow::on_chatbutton_clicked()
{
    QStandardItemModel *conversationModel = new QStandardItemModel(10, 1, this);
    conversationModel->setHorizontalHeaderLabels({"Message"});

    QLineEdit *idField = new QLineEdit(this);
    QLineEdit *matriculeField = new QLineEdit(this);
    QLineEdit *typeField = new QLineEdit(this);
    QLineEdit *confirmField = new QLineEdit(this);
    confirmField->setReadOnly(true);

    idField->setPlaceholderText("Entrez votre ID");
    matriculeField->setPlaceholderText("Entrez votre numéro de matricule");
    typeField->setPlaceholderText("Entrez le type de rendez-vous");

    idField->hide();
    matriculeField->hide();
    typeField->hide();
    confirmField->hide();

    QPushButton *date1 = new QPushButton("2024-12-03 10:00", this);
    QPushButton *date2 = new QPushButton("2024-12-03 14:00", this);
    QPushButton *date3 = new QPushButton("2024-12-03 16:00", this);

    date1->hide();
    date2->hide();
    date3->hide();

    // Étape 1 : Demander l'ID de l'utilisateur
    conversationModel->setItem(0, 0, new QStandardItem("Veuillez entrer votre ID :"));
    ui->chatbotview->setModel(conversationModel);
    ui->chatbotview->resizeColumnsToContents();

    ui->chatbotview->setIndexWidget(conversationModel->index(1, 0), idField);
    idField->show();

    connect(idField, &QLineEdit::editingFinished, this, [=]()
            {
                QString userId = idField->text();
                conversationModel->setItem(1, 0, new QStandardItem("ID : " + userId));
                ui->chatbotview->setModel(conversationModel);
                ui->chatbotview->resizeColumnsToContents();

                idField->hide();

                // Étape 2 : Demander le numéro de matricule
                conversationModel->setItem(2, 0, new QStandardItem("Veuillez entrer votre numéro de matricule :"));
                ui->chatbotview->setIndexWidget(conversationModel->index(3, 0), matriculeField);
                matriculeField->show();

                connect(matriculeField, &QLineEdit::editingFinished, this, [=]()
                        {
                            QString userMatricule = matriculeField->text();
                            conversationModel->setItem(3, 0, new QStandardItem("Matricule " + userMatricule));
                            ui->chatbotview->setModel(conversationModel);
                            ui->chatbotview->resizeColumnsToContents();

                            matriculeField->hide();

                            // Étape 3 : Demander le type de rendez-vous
                            conversationModel->setItem(4, 0, new QStandardItem("Quel type de rendez-vous souhaitez-vous ?"));
                            ui->chatbotview->setIndexWidget(conversationModel->index(5, 0), typeField);
                            typeField->show();

                            connect(typeField, &QLineEdit::editingFinished, this, [=]()
                                    {
                                        QString userType = typeField->text();
                                        conversationModel->setItem(5, 0, new QStandardItem("Le type est " + userType));
                                        conversationModel->setItem(6, 0, new QStandardItem("Voici 3 dates possibles pour votre rendez-vous :"));
                                        ui->chatbotview->setModel(conversationModel);
                                        ui->chatbotview->resizeColumnsToContents();

                                        typeField->hide();

                                        // Étape 4 : Afficher les dates disponibles
                                        date1->show();
                                        date2->show();
                                        date3->show();

                                        ui->chatbotview->setIndexWidget(conversationModel->index(7, 0), date1);
                                        ui->chatbotview->setIndexWidget(conversationModel->index(8, 0), date2);
                                        ui->chatbotview->setIndexWidget(conversationModel->index(9, 0), date3);

                                        connect(date1, &QPushButton::clicked, this, [=]()
                                                {
                                                    confirmField->setText(date1->text());
                                                    conversationModel->setItem(10, 0, new QStandardItem("Le choix de la date: " + date1->text()));
                                                    conversationModel->setItem(11, 0, new QStandardItem("Votre rendez-vous est confirmé pour le " + date1->text()));
                                                    ui->chatbotview->setModel(conversationModel);
                                                    ui->chatbotview->resizeColumnsToContents();
                                                });

                                        connect(date2, &QPushButton::clicked, this, [=]()
                                                {
                                                    confirmField->setText(date2->text());
                                                    conversationModel->setItem(10, 0, new QStandardItem("Le choix de la date: " + date2->text()));
                                                    conversationModel->setItem(11, 0, new QStandardItem("Votre rendez-vous est confirmé pour le " + date2->text()));
                                                    ui->chatbotview->setModel(conversationModel);
                                                    ui->chatbotview->resizeColumnsToContents();
                                                });

                                        connect(date3, &QPushButton::clicked, this, [=]()
                                                {
                                                    confirmField->setText(date3->text());
                                                    conversationModel->setItem(10, 0, new QStandardItem("Le choix de la date:" + date3->text()));
                                                    conversationModel->setItem(11, 0, new QStandardItem("Votre rendez-vous est confirmé pour le " + date3->text()));
                                                    ui->chatbotview->setModel(conversationModel);
                                                    ui->chatbotview->resizeColumnsToContents();
                                                });
                                    });
                        });
            });
}


void MainWindow::on_alertes_clicked()
{
    Vehicules::showAlert("Rendez-vous confirmé", "Le véhicule a été pris en compte et est en cours de réparation.");
}


void MainWindow::on_modify_clicked()
{
    QLineEdit *newAppointmentDateLineEdit = new QLineEdit(this);
    newAppointmentDateLineEdit->setPlaceholderText("Entrez la nouvelle date du rendez-vous (ex: 2024-11-30 10:00)");

    QPushButton *confirm = new QPushButton("Confirmer le rendez-vous", this);

    conversationModel->setItem(1, 0, new QStandardItem("Utilisateur: "));
    ui->chatbotview->setModel(conversationModel);
    ui->chatbotview->setIndexWidget(conversationModel->index(1, 0), newAppointmentDateLineEdit);
    ui->chatbotview->resizeColumnsToContents();

    conversationModel->setItem(2, 0, new QStandardItem("Chatbot: Veuillez entrer la nouvelle date."));
    ui->chatbotview->setModel(conversationModel);
    ui->chatbotview->setIndexWidget(conversationModel->index(2, 0), confirm);
    ui->chatbotview->resizeColumnsToContents();

    connect(confirm, &QPushButton::clicked, this, [=]()
            {
                QString newAppointmentDate = newAppointmentDateLineEdit->text();

                if (newAppointmentDate.isEmpty())
                {
                    Vehicules::showAlert("Erreur", "Veuillez entrer une nouvelle date de rendez-vous.");
                    return;
                }

                conversationModel->setItem(3, 0, new QStandardItem("Chatbot: Votre rendez-vous a été modifié à la nouvelle date : " + newAppointmentDate));
                ui->chatbotview->setModel(conversationModel);
                ui->chatbotview->resizeColumnsToContents();

                Vehicules::showAlert("Rendez-vous Modifié", "Le rendez-vous a été modifié à la date suivante : " + newAppointmentDate);
            });
}


void MainWindow::on_cancel_clicked()
{
    QPushButton *cancel = new QPushButton("Confirmer l'annulation", this);

    conversationModel->setItem(1, 0, new QStandardItem("Utilisateur: "));
    ui->chatbotview->setModel(conversationModel);

    conversationModel->setItem(2, 0, new QStandardItem("Chatbot: Êtes-vous sûr de vouloir annuler votre rendez-vous ?"));
    ui->chatbotview->setModel(conversationModel);
    ui->chatbotview->setIndexWidget(conversationModel->index(2, 0), cancel);
    ui->chatbotview->resizeColumnsToContents();

    connect(cancel, &QPushButton::clicked, this, [=]()
            {
                conversationModel->setItem(3, 0, new QStandardItem("Chatbot: Votre rendez-vous a été annulé."));
                ui->chatbotview->setModel(conversationModel);
                ui->chatbotview->resizeColumnsToContents();

                Vehicules::showAlert("Rendez-vous Annulé", "Votre rendez-vous a été annulé avec succès.");


            });
}

void MainWindow::on_arduino_clicked()
{
    if (arduino->connectToArduino())
    {
        QMessageBox::information(this, "Confirmation", "Connexion à l'Arduino réussie !");

        connect(arduino, &arduinov::matriculeVerified, this, &MainWindow::onMatriculeVerified);
    }
    else
    {
        QMessageBox::critical(this, "Erreur", "Échec de la connexion à l'Arduino.");
    }
}


void MainWindow::handleArduinoData(QString data)
{
    qDebug() << "Données reçues :" << data;
    QMessageBox::information(this, "Données Arduino", "Données reçues : " + data);
}


void MainWindow::onMatriculeVerified(const QString &matricule, bool exists)
{
    if (exists)
    {
        QMessageBox::information(this, "Vérification de la matricule",
                                 QString("La matricule '%1' existe dans la base de données.").arg(matricule));
    }
    else
    {
        QMessageBox::warning(this, "Vérification de la matricule",
                             QString("La matricule '%1' n'existe pas dans la base de données.").arg(matricule));
    }
}




