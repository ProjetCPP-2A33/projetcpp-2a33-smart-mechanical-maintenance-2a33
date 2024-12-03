#include "gestionL.h"
#include "ui_gestionL.h"  // Vérifier que l'UI est importée correctement, avec le bon nom
#include <QMessageBox>
#include "local.h"
#include "connection.h"
#include "tableviewwindow.h"
#include "graphview.h"
#include <QMap>
#include <QTimer>
#include <QSqlQuery>
#include <QSqlError>
#include"arduinogestionL.h"

GestionL::GestionL(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::GestionL) {  // Changer MainWindow en GestionL ici
    ui->setupUi(this);

    // Timer pour vérifier la température toutes les 1 seconde
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GestionL::checkTemperature);  // Changer MainWindow en GestionL ici
    timer->start(1000); // Vérifier la température toutes les 1 seconde
    arduino.connect_arduino();

    tableViewWindow = nullptr;

    // Remplir la comboBox_Service avec des options
    ui->gLcomboBox_Service->addItems(QStringList()
                                   << "Reparation mecanique"
                                   << "Diagnostic electronique"
                                   << "Entretien general"
                                   << "Remplacement de pneus"
                                   << "Recharge climatisation");
}

GestionL::~GestionL() {  // Changer MainWindow en GestionL ici
    delete ui;
    delete tableViewWindow;
}

bool GestionL::isValidId(const QString &idText) {
    bool conversionOk;
    idText.toInt(&conversionOk);
    if (!conversionOk) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un numéro valide pour l'ID du local.");
    }
    return conversionOk;
}

void GestionL::on_gLpushbutton_ajouter_clicked() {
    QString idText = ui->gLlineEdit_idlocal->text();
    if (!isValidId(idText)) return;

    int idLocal = idText.toInt();
    QString adresse = ui->gLlineEdit_adresse->text();
    QString responsable = ui->gLlineEdit_Responsable->text();
    int numTel = ui->gLlineEdit_Num_telephone->text().toInt();
    QString service = ui->gLcomboBox_Service->currentText();
    int heureTravail = ui->gLlineEdit_heure->text().toInt();
    QString email = ui->gLlineEdit_email->text();

    Local nouveauLocal(idLocal, adresse, responsable, numTel, service, heureTravail, email);
    if (nouveauLocal.ajouter()) {
        QMessageBox::information(this, "Succès", "Local ajouté avec succès !");

        // Réinitialiser les champs
        ui->gLlineEdit_idlocal->clear();
        ui->gLlineEdit_adresse->clear();
        ui->gLlineEdit_Responsable->clear();
        ui->gLlineEdit_Num_telephone->clear();
        ui->gLcomboBox_Service->setCurrentIndex(0);
        ui->gLlineEdit_heure->clear();
        ui->gLlineEdit_email->clear();
    } else {
        QMessageBox::warning(this, "Erreur", "Échec de l'ajout du local.");
    }
}

void GestionL::on_gLpushbutton_modifier_clicked() {
    QString idText = ui->gLlineEdit_idlocal->text();
    if (!isValidId(idText)) return;

    int idLocal = idText.toInt();
    QString adresse = ui->gLlineEdit_adresse->text();
    QString responsable = ui->gLlineEdit_Responsable->text();
    int numTel = ui->gLlineEdit_Num_telephone->text().toInt();
    QString service = ui->gLcomboBox_Service->currentText();
    int heureTravail = ui->gLlineEdit_heure->text().toInt();
    QString email = ui->gLlineEdit_email->text();

    Local localModifie(idLocal, adresse, responsable, numTel, service, heureTravail, email);
    if (localModifie.modifier()) {
        QMessageBox::information(this, "Succès", "Local modifié avec succès !");
    } else {
        QMessageBox::warning(this, "Erreur", "Échec de la modification du local.");
    }
}

void GestionL::on_gLpushbutton_supprimer_clicked() {
    QString idText = ui->gLlineEdit_idlocal->text();
    if (!isValidId(idText)) return;

    int idLocal = idText.toInt();
    Local localASupprimer(idLocal);
    if (localASupprimer.supprimer()) {
        QMessageBox::information(this, "Succès", "Local supprimé avec succès !");
        ui->gLlineEdit_idlocal->clear();
    } else {
        QMessageBox::warning(this, "Erreur", "Échec de la suppression du local.");
    }
}

void GestionL::on_gLpushbutton_afficher_clicked() {
    if (!tableViewWindow) {
        tableViewWindow = new TableViewWindow(this);
    }

    Local local;
    QSqlQueryModel* model = local.afficher();
    if (model->rowCount() == 0) {
        QMessageBox::warning(this, "Attention", "Aucun local trouvé dans la base de données.");
        return;
    }

    tableViewWindow->setModel(model);
    tableViewWindow->show();
}

void GestionL::on_gLpushButton_aff_clicked() {
    QString idText = ui->gLlineEdit_idlocal->text();

    // Vérifier si l'ID est valide
    if (!isValidId(idText)) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID valide.");
        return;
    }

    int idLocal = idText.toInt();

    // Créer la requête pour récupérer les informations du local par son ID
    QSqlQuery query;
    query.prepare("SELECT * FROM Local WHERE ID_local = :ID_local");
    query.bindValue(":ID_local", idLocal);

    // Exécuter la requête
    if (!query.exec()) {
        QMessageBox::warning(this, "Erreur", "La requête a échoué : " + query.lastError().text());
        return;
    }

    // Vérifier si un local avec cet ID a été trouvé
    if (query.next()) {
        // Si trouvé, remplir les champs avec les données récupérées
        ui->gLlineEdit_adresse->setText(query.value("adresse").toString());
        ui->gLlineEdit_Responsable->setText(query.value("Responsable").toString());
        ui->gLlineEdit_Num_telephone->setText(query.value("Num_telephone").toString());

        // Mise à jour de la comboBox avec le service
        QString service = query.value("Service").toString();
        int index = ui->gLcomboBox_Service->findText(service);  // Rechercher l'index du service dans le comboBox

        if (index != -1) {
            ui->gLcomboBox_Service->setCurrentIndex(index);  // Si trouvé, sélectionner cet item
        } else {
            // Si le service n'est pas dans la comboBox, l'ajouter
            ui->gLcomboBox_Service->addItem(service);
            ui->gLcomboBox_Service->setCurrentText(service);  // Sélectionner le nouveau service
        }

        ui->gLlineEdit_heure->setText(query.value("heure_travail").toString());
        ui->gLlineEdit_email->setText(query.value("email").toString());
    } else {
        QMessageBox::warning(this, "Erreur", "Aucun local trouvé avec cet ID.");
        ui->gLlineEdit_adresse->clear();
        ui->gLlineEdit_Responsable->clear();
        ui->gLlineEdit_Num_telephone->clear();
        ui->gLcomboBox_Service->setCurrentIndex(0);  // Réinitialiser la comboBox
        ui->gLlineEdit_heure->clear();
        ui->gLlineEdit_email->clear();
    }
}

void GestionL::on_gLpushButton_showGraph_clicked() {
    // Implémentation de la fonction pour afficher un graphique
    QMap<QString, int> serviceData;
    QStringList defaultServices = QStringList()
                                   << "Reparation mecanique"
                                   << "Diagnostic electronique"
                                   << "Entretien general"
                                   << "Remplacement de pneus"
                                   << "Recharge climatisation";

    for (const QString &service : defaultServices) {
        serviceData[service] = 0;
    }

    // Récupérer les données depuis la base de données
    QSqlQuery query("SELECT Service, COUNT(*) FROM Local GROUP BY Service");
    while (query.next()) {
        QString serviceName = query.value(0).toString();
        int count = query.value(1).toInt();

        if (serviceData.contains(serviceName)) {
            serviceData[serviceName] = count;
        } else {
            serviceData[serviceName] = count;
        }
    }

    GraphView *graph = new GraphView(this);
    graph->setData(serviceData);
    graph->exec();  // Afficher la fenêtre modale
}

void GestionL::checkTemperature() {
    QSqlQuery query("SELECT temperature FROM Local WHERE ID_local = 14353");
    if (query.next()) {
        float temperature = query.value(0).toFloat();
        if (temperature > 30.0) {
            arduino.control_fan(true);  // Allumer le ventilateur
        } else {
            arduino.control_fan(false); // Éteindre le ventilateur
        }
    } else {
        qDebug() << "Impossible de récupérer la température depuis la base de données.";
    }
}

void GestionL::on_gLpushButton_updateTemperature_clicked() {
    // Récupérer les valeurs des champs
    QString idText = ui->gLlineEdit_idlocal->text();
    QString temperatureText = ui->gLlineEdit_temperature->text();

    int idLocal = idText.toInt();
    float temperature = temperatureText.toFloat();

    QSqlQuery query;
    query.prepare("UPDATE Local SET temperature = :temperature WHERE ID_local = 14353");
    query.bindValue(":temperature", temperature);
    query.bindValue(":ID_local", idLocal);

    if (query.exec()) {
        QMessageBox::information(this, "Succès", "Température mise à jour avec succès !");
    } else {
        QMessageBox::critical(this, "Erreur", "La mise à jour a échoué : " + query.lastError().text());
    }
}
