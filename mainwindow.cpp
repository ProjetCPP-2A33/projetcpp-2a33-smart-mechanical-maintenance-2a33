#include "mainwindow.h"
#include "qsqldatabase.h"
#include "ui_mainwindow.h"
#include "vehicules.h"
#include <QString>
#include <QApplication>
#include <QMessageBox>
#include <QProcess>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include<QString>
#include"vehicules.h"


QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");

bool cnameCheck = false, empCheck = false, dateChanged = false, startChanged = false, endChanged = false;

MainWindow::~MainWindow()
{
    // Destructor logic (if needed) goes here
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(V.afficher());
}



void MainWindow:: on_ajouter_clicked()
{
    int num_matricule=ui -> reponsematricule->text().toInt ();
    QString marque=ui-> reponsemarque ->text();
    QString modele =ui -> reponsemodele ->text();
    QString kilometrages =ui ->reponsekilometrages ->text();
    int id_prop =ui -> reponseidclient ->text().toInt();
    int annee_fab=ui ->reponseanneefab ->text().toInt();
    QString etat =ui ->reponseetat ->text();
    QString assurance = ui ->reponseassurance ->text();

    qDebug() << "Attempting to add vehicle with details:"
             << "num_matricule:" << num_matricule
             << "marque:" << marque
             << "modele:" << modele
             << "kilometrages:" << kilometrages
             << "id_prop:" << id_prop
             << "annee_fab:" << annee_fab
             << "etat:" << etat
             << "assurance:" << assurance;

    Vehicules V (num_matricule, marque, modele, kilometrages,id_prop,annee_fab,etat,assurance);

    bool test=V.ajouter();



    if(test)
    {
        qDebug() << "Ajout succeeded";
        ui->tableView->setModel(V.afficher());
        QMessageBox::information(this, QObject::tr("OK"),
                                 QObject::tr("Ajout Effectué\n "
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        qDebug() << "Ajout failed";

        QMessageBox::critical(this, QObject::tr("NOT OK"),
                              QObject::tr("Ajout non effectué.\n"
                                          "Click cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow:: on_supprimer_clicked()
{
    int num_matricule=ui  ->reponsematricule->text().toInt();
    bool test=V.supprimer(num_matricule);
    if (test)
    {
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Suppression Effectué\n "
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                              QObject::tr("Suppression non effectué.\n"
                                          "Click cancel to exit."), QMessageBox::Cancel);
    }
}




void MainWindow::on_modifier_clicked()
{
    int num_matricule =ui -> reponsematricule->text().toInt ();
    QString marque=ui-> reponsemarque ->text();
    QString modele =ui -> reponsemodele ->text();
    QString kilometrages =ui ->reponsekilometrages ->text();
    int id_prop =ui -> reponseidclient ->text().toInt();
    int annee_fab=ui ->reponseanneefab ->text().toInt();
    QString etat =ui ->reponseetat ->text();
    QString assurance = ui ->reponseassurance ->text();

    Vehicules V (num_matricule, marque, modele, kilometrages,id_prop,annee_fab,etat,assurance);



    if (V.modifier())
    {
        ui->tableView->setModel(V.afficher());
        QMessageBox::information(this, "Succès", "La vehicule a été modifié avec succès.");
    }
    else {
        QMessageBox::critical(this, "Erreur", "Erreur lors de la modification de la vehicule.");
    }
}

void MainWindow::on_afficher_clicked()
{
    int num_matricule = ui->reponsematricule->text().toInt();
    QString marque = ui->reponsemarque->text();
    QString modele = ui->reponsemodele->text();
    QString kilometrages = ui->reponsekilometrages->text();
    int id_prop = ui->reponseidclient->text().toInt();
    int annee_fab = ui->reponseanneefab->text().toInt();
    QString etat = ui->reponseetat->text();
    QString assurance = ui->reponseassurance->text();


    Vehicules V(num_matricule, marque, modele, kilometrages, id_prop, annee_fab, etat, assurance);


    if (V.afficher())
    {
        ui->tableView->setModel(V.afficher());
        QMessageBox::information(this, "Succès", "Les données du véhicule ont été affichées avec succès.");
    }
    else
    {
        QMessageBox::critical(this, "Erreur", "Erreur lors de l'affichage des données du véhicule.");
    }
}

