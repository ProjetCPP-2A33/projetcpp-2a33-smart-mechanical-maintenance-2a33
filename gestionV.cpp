#include "gestionV.h"
#include "qsqldatabase.h"
#include "ui_gestionV.h"
#include "vehicules.h"
#include <QString>
#include <QApplication>
#include <QMessageBox>
#include <QProcess>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include<QString>
#include <QFileDialog>
#include <QBarSeries>
#include <QBarSet>
#include <QChart>
#include <QChartView>
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


QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");


bool cnameCheck = false, empCheck = false, dateChanged = false, startChanged = false, endChanged = false;


MainWindow::~MainWindow()
{
    delete ui;
}


MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->Aff->setModel(V.afficher());


    // Initialiser le modèle
    model = new QSqlTableModel(this);
    model->setTable("Vehicules");  // Spécifier la table à afficher
    model->setEditStrategy(QSqlTableModel::OnFieldChange);  // Modification en temps réel
    model->select();  // Charger les données

    // Lier le modèle à la QTableView
    ui->Aff->setModel(model);  // Associer le modèle à la vue

    // Initialize other UI components
    conversationModel = new QStandardItemModel(this);
    conversationModel->setHorizontalHeaderLabels({"Message"});
    ui->chatbotview->setModel(conversationModel);
    ui->chatbotview->resizeColumnsToContents();

    // Connect signals and slots
    connect(ui->Chatbutton, &QPushButton::clicked, this, &MainWindow::on_chatbutton_clicked);
    connect(ui->alertes, &QPushButton::clicked, this, &MainWindow::on_alertes_clicked);
    connect(ui->modify, &QPushButton::clicked, this, &MainWindow::on_modify_clicked);
    connect(ui->cancel, &QPushButton::clicked, this, &MainWindow::on_cancel_clicked);
}




void MainWindow::on_ajouter_clicked()
{
    QString num_matricule = ui->reponsematricule->text();
    QString marque = ui->reponsemarque->text();
    QString modele = ui->reponsemodele->text();
    QString kilometrages = ui->reponsekilometrages->text();
    int annee_fab = ui->reponseanneefab->text().toInt();
    int id_client = ui->reponseidclient->text().toInt();
    QString etat = ui->reponseetat->text();
    QString assurance = ui->reponseassurance->text();

    if (V.ajouter(num_matricule, marque, modele, kilometrages, annee_fab, id_client, etat, assurance))
    {
        ui->Aff->setModel(V.afficher());  // Associer le modèle à la vue
        qDebug() << "Véhicule ajouté et modèle mis à jour!";
    }
    else
    {
        qDebug() << "Erreur lors de l'ajout du véhicule!";
    }
}

/*void MainWindow::afficher()
{

    QSqlQueryModel *model = V.afficher();
    if (model)
    {
        ui->Aff->setModel(model);
        qDebug() << "Affichage des vehicules : modèle mis à jour";
    }
    else
    {
        qDebug() << "Erreur : impossible d'afficher les vehicules.";
    }
}*/



void MainWindow::on_supprimer_clicked()
{
    QString num_matricule_str = ui->recherche->text();

    bool ok;
    int num_matricule = num_matricule_str.toInt(&ok);

    if (!ok)
    {
        QMessageBox::warning(this, "Erreur", "Numéro de matricule invalide.");
        return;
    }

    QString num_matricule_str_final = QString::number(num_matricule);

    bool test = V.supprimer(num_matricule_str_final);

    if (test)
    {
        QMessageBox::information(this, "Suppression", "Le véhicule a été supprimé avec succès.");
    }
    else
    {
        QMessageBox::warning(this, "Suppression", "Le véhicule n'a pas pu être supprimé.");
    }
}



void MainWindow::on_modifier_clicked()
{
    QString num_matricule = ui->reponsematricule->text();
    QString marque = ui->reponsemarque->text();
    QString modele = ui->reponsemodele->text();
    QString kilometrages = ui->reponsekilometrages->text();
    int annee_fab = ui->reponseanneefab->text().toInt();
    int id_client = ui->reponseidclient->text().toInt();
    QString etat = ui->reponseetat->text();
    QString assurance = ui->reponseassurance->text();

    Vehicules V(num_matricule, marque, modele, kilometrages, annee_fab, id_client, etat, assurance);
    bool test = V.modifier();

    if (test)
    {
        QMessageBox::information(this, "Succès", "Le véhicule a été modifié avec succès.");
        ui->Aff->setModel(V.afficher());  // Mettre à jour l'affichage
    }
    else
    {
        QMessageBox::critical(this, "Erreur", "Échec de la modification du véhicule.");
    }
}


/*void MainWindow::on_afficher_clicked()
{
    ui->Aff->setModel(V.afficher());
    QMessageBox::information(this, "Affichage", "Les véhicules ont été affichés avec succès.");
}
*/

void MainWindow::on_trier_clicked()
{
    ui->Aff->setModel(V.trierParModele());
    QMessageBox::information(this, "Tri", "Les véhicules ont été triés par modèle.");
}


void MainWindow::on_rechercher_clicked()
{
    QString num_matricule = ui->recherche->text();

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




void MainWindow::on_PDF_clicked()
{
    QString nomFichier = QFileDialog::getSaveFileName(this, "Enregistrer le PDF", "", "Fichiers PDF (*.pdf)");

    if (!nomFichier.isEmpty()) {
        Vehicules V;

        QSqlQueryModel *model = V.afficher();

        V.exporterPDF(nomFichier, model);

        delete model;

        QMessageBox::information(this, "Exportation PDF", "Exportation vers PDF réussie !");
    }
}

void MainWindow::on_statistique_clicked()
{
    QStringList categories;
    QVector<QString> modele = {"renault", "bmw", "mercedes", "toyota"};
    QVector<int> counts = {10, 15, 7, 12};

    categories << "semaine 1" << "semaine 2" << "semaine 3" << "semaine 4";

    if (!chartView) {
        QBarSeries *series = new QBarSeries();

        for (int i = 0; i < modele.size(); ++i) {
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

        if (!ui->statistique->layout()) {
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

    QPushButton *date1 = new QPushButton("2024-11-20 10:00", this);
    QPushButton *date2 = new QPushButton("2024-11-21 14:00", this);
    QPushButton *date3 = new QPushButton("2024-11-22 09:00", this);

    date1->hide();
    date2->hide();
    date3->hide();

    // Étape 1 : Demander l'ID de l'utilisateur
    conversationModel->setItem(0, 0, new QStandardItem("Chatbot: Veuillez entrer votre ID :"));
    ui->chatbotview->setModel(conversationModel);
    ui->chatbotview->resizeColumnsToContents();

    ui->chatbotview->setIndexWidget(conversationModel->index(1, 0), idField);
    idField->show();

    connect(idField, &QLineEdit::editingFinished, this, [=]()
            {
                QString userId = idField->text();
                conversationModel->setItem(1, 0, new QStandardItem("Utilisateur: ID " + userId));
                ui->chatbotview->setModel(conversationModel);
                ui->chatbotview->resizeColumnsToContents();

                idField->hide();

                // Étape 2 : Demander le numéro de matricule
                conversationModel->setItem(2, 0, new QStandardItem("Chatbot: Veuillez entrer votre numéro de matricule :"));
                ui->chatbotview->setIndexWidget(conversationModel->index(3, 0), matriculeField);
                matriculeField->show();

                connect(matriculeField, &QLineEdit::editingFinished, this, [=]()
                        {
                            QString userMatricule = matriculeField->text();
                            conversationModel->setItem(3, 0, new QStandardItem("Utilisateur: Matricule " + userMatricule));
                            ui->chatbotview->setModel(conversationModel);
                            ui->chatbotview->resizeColumnsToContents();

                            matriculeField->hide();

                            // Étape 3 : Demander le type de rendez-vous
                            conversationModel->setItem(4, 0, new QStandardItem("Chatbot: Quel type de rendez-vous souhaitez-vous ?"));
                            ui->chatbotview->setIndexWidget(conversationModel->index(5, 0), typeField);
                            typeField->show();

                            connect(typeField, &QLineEdit::editingFinished, this, [=]()
                                    {
                                        QString userType = typeField->text();
                                        conversationModel->setItem(5, 0, new QStandardItem("Utilisateur: " + userType));
                                        conversationModel->setItem(6, 0, new QStandardItem("Chatbot: Voici 3 dates possibles pour votre rendez-vous :"));
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
                                                    conversationModel->setItem(10, 0, new QStandardItem("Utilisateur a choisi la date: " + date1->text()));
                                                    conversationModel->setItem(11, 0, new QStandardItem("Chatbot: Votre rendez-vous est confirmé pour le " + date1->text()));
                                                    ui->chatbotview->setModel(conversationModel);
                                                    ui->chatbotview->resizeColumnsToContents();
                                                });

                                        connect(date2, &QPushButton::clicked, this, [=]()
                                                {
                                                    confirmField->setText(date2->text());
                                                    conversationModel->setItem(10, 0, new QStandardItem("Utilisateur a choisi la date: " + date2->text()));
                                                    conversationModel->setItem(11, 0, new QStandardItem("Chatbot: Votre rendez-vous est confirmé pour le " + date2->text()));
                                                    ui->chatbotview->setModel(conversationModel);
                                                    ui->chatbotview->resizeColumnsToContents();
                                                });

                                        connect(date3, &QPushButton::clicked, this, [=]()
                                                {
                                                    confirmField->setText(date3->text());
                                                    conversationModel->setItem(10, 0, new QStandardItem("Utilisateur a choisi la date: " + date3->text()));
                                                    conversationModel->setItem(11, 0, new QStandardItem("Chatbot: Votre rendez-vous est confirmé pour le " + date3->text()));
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

    connect(cancel, &QPushButton::clicked, this, [=]() {
        conversationModel->setItem(3, 0, new QStandardItem("Chatbot: Votre rendez-vous a été annulé."));
        ui->chatbotview->setModel(conversationModel);
        ui->chatbotview->resizeColumnsToContents();

        Vehicules::showAlert("Rendez-vous Annulé", "Votre rendez-vous a été annulé avec succès.");


    });
}
