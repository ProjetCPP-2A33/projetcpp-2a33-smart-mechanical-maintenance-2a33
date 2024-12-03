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
    /*serial->setBaudRate(QSerialPort::Baud9600);  // Assurez-vous que la vitesse du port série est correcte
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);*/

    if (serial->open(QIODevice::WriteOnly)) {
        qDebug() << "Port série ouvert";
    } else {
        qDebug() << "Erreur d'ouverture du port série : " << serial->errorString();
    }

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
        QMessageBox::warning(this, "Entrée manquante", "Veuillez saisir une matricule.");
        return;
    }


    QSqlQuery query;
    query.prepare("SELECT rendez_vous, status FROM vehicule WHERE matricule = :matricule");
    query.bindValue(":matricule", inputmatricule);

    if (!query.exec()) {
        qDebug() << "Erreur de requête SQL : " << query.lastError().text();
        return;
    }

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
        // Si la matricule n'existe pas, envoyer un message à l'Arduino
        QString message = "Aucun rendez-vous pour la matricule: " + inputmatricule + "\n";
        if (serial->isOpen() && serial->isWritable()) {
            qDebug() << "Aucun rendez-vous trouvé pour cette matricule.";
            serial->write(message.toUtf8());
        }
    }
}
