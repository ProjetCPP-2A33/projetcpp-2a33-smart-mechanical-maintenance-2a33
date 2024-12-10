#define ARDUINO_VENDOR_ID    0x2341  // Vendor ID for Arduino Uno
#define ARDUINO_PRODUCT_ID   0x0043  // Product ID for Arduino Uno
#include "gestionV.h"
#include "qsqldatabase.h"
#include "ui_gestionV.h"
#include "vehicules.h"
#include "arduinogestionL.h"
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


QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");


MainWindow2::~MainWindow2()
{
    delete ui;
    delete arduino; // Assurez-vous de libérer la mémoire si nécessaire

}


MainWindow2::MainWindow2(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow2),
    arduino(new Arduino(this))
{
    ui->setupUi(this);
    ui->Aff->setModel(V.afficher());


    // Initialiser le modèle
    model = new QSqlTableModel(this);
    model->setTable("Vehicules");
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->select();

    ui->Aff->setModel(model);
    ui->Aff->setModel(V.afficher());


    conversationModel = new QStandardItemModel(this);
    conversationModel->setHorizontalHeaderLabels({"Message"});
    ui->chatbotview->setModel(conversationModel);
    ui->chatbotview->resizeColumnsToContents();

    connect(ui->Chatbutton, &QPushButton::clicked, this, &MainWindow2::on_chatbutton_clicked);
    connect(ui->alertes, &QPushButton::clicked, this, &MainWindow2::on_alertes_clicked);
    connect(ui->modify, &QPushButton::clicked, this, &MainWindow2::on_modify_clicked);
    connect(ui->cancel, &QPushButton::clicked, this, &MainWindow2::on_cancel_clicked);
    connect(arduino, &Arduino::dataReceived, this, &MainWindow2::handleArduinoData);
    connect(arduino, &Arduino::matriculeVerified, this, &MainWindow2::onMatriculeVerified);
    connect(ui->client, &QPushButton::clicked, this, &MainWindow2::showClientPage);
    connect(ui->employee, &QPushButton::clicked, this, &MainWindow2::showEmployeePage);
    connect(ui->equipements, &QPushButton::clicked, this, &MainWindow2::showEquipementPage);
    connect(ui->locaux, &QPushButton::clicked, this, &MainWindow2::showLocauxPage);
    connect(ui->facture, &QPushButton::clicked, this, &MainWindow2::showFacturePage);
    connect(ui->equipements, &QPushButton::clicked, this, &::MainWindow2::switchToEquipement);
    connect(ui->locaux, &QPushButton::clicked, this, &::MainWindow2::switchToLocaux);

}


void MainWindow2::on_ajouter_clicked()
{
    QString num_matricule = ui->reponsematricule->text();
    QString marque = ui->reponsemarque->text();
    QString modele = ui->reponsemodele->text();
    QString kilometrages = ui->reponsekilometrages->text();
    int annee_fab = ui->reponseanneefab->text().toInt();
    QString id_client = ui->reponseidclient->text();
    QString etat = ui->reponseetat->text();
    QString assurance = ui->reponseassurance->text();

    //QPushButton *button = new QPushButton("ajouter", this);
    //QIcon icon(":/path/to/add");
    //button->setIcon(icon);


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


void MainWindow2::on_supprimer_clicked()
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


void MainWindow2::on_modifier_clicked()
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


void MainWindow2::on_trier_clicked()
{
    ui->Aff->setModel(V.trierParModele());

    /*QPushButton *button3 = new QPushButton("trier", this);
    QIcon icon(":/path/to/trier.png"); // Remplacez par le chemin de votre icône
    button3->setIcon(icon);*/

    QMessageBox::information(this, "Tri", "Les véhicules ont été triés par modèle.");

}


void MainWindow2::on_rechercher_clicked()
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


void MainWindow2::on_PDF_clicked()
{
    QString nomFichier = QFileDialog::getSaveFileName(this, "Enregistrer le PDF", "", "Fichiers PDF (*.pdf)");

    /*QPushButton *button4 = new QPushButton("PDF", this);
    QIcon icon(":/path/to/down.png"); // Remplacez par le chemin de votre icône
    button4->setIcon(icon);*/

    if (!nomFichier.isEmpty())
    {
        Vehicules V;

        QSqlQueryModel *model = V.afficher();

        V.exporterPDF(nomFichier, model);

        delete model;

        QMessageBox::information(this, "Exportation PDF", "Exportation vers PDF réussie !");
    }
}


void MainWindow2::on_statistique_clicked()
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




void MainWindow2::on_chatbutton_clicked()
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


void MainWindow2::on_alertes_clicked()
{
    Vehicules::showAlert("Rendez-vous confirmé", "Le véhicule a été pris en compte et est en cours de réparation.");
}


void MainWindow2::on_modify_clicked()
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


void MainWindow2::on_cancel_clicked()
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

void MainWindow2::on_arduino_clicked()
{
    if (arduino->connectToArduino())
    {
        QMessageBox::information(this, "Confirmation", "Connexion à l'Arduino réussie !");

        connect(arduino, &Arduino::matriculeVerified, this, &MainWindow2::onMatriculeVerified);
    }
    else
    {
        QMessageBox::critical(this, "Erreur", "Échec de la connexion à l'Arduino.");
    }
}


void MainWindow2::handleArduinoData(QString data)
{
    qDebug() << "Données reçues :" << data;
    QMessageBox::information(this, "Données Arduino", "Données reçues : " + data);
}


void MainWindow2::onMatriculeVerified(const QString &matricule, bool exists)
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







