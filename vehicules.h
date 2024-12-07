#ifndef VEHICULES_H
#define VEHICULES_H

#include "rendezvous.h"
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>



class Vehicules
{

private:

    QString num_matricule ;
    QString marque;
    QString  modele;
    QString kilometrages;
    int annee_fab;
    QString id_client;
    QString  etat;
    QString  assurance;


    Rendezvous rendezvous;

public:

    //constructeurs

    Vehicules();
    Vehicules(QString num_matricule, QString marque, QString modele, QString kilometrages, int annee_fab, QString id_client, QString etat, QString assurance);

    //getters

    QString getNum_matricule()  {return num_matricule ;}
    QString getMarque () {return marque; }
    QString getModele () {return modele; }
    QString getKilometrages () {return kilometrages; }
    int getAnnee_fab (){return annee_fab ;}
    QString getId_client () {return id_client;}
    QString getEtat () {return etat; }
    QString getAssurance () {return assurance; }
    Rendezvous getRendezvous() const;

    //Setters

    void setNum_matricule(QString nm)  {num_matricule = nm;}
    void setMarque (QString m) { marque = m; }
    void setModele (QString md) { modele = md; }
    void setKilometrages (QString k) { kilometrages = k; }
    void setAnnee_fab (int af){ annee_fab =af ;}
    void setId_client (QString idc) { id_client = idc;}
    void setEtat (QString e) { etat = e; }
    void setAssurance (QString a) { assurance= a; }




    //Fonctionnalités de base relative à l'entité
    bool ajouter(const QString &num_matricule, const QString &marque, const QString &modele,
                 const QString &kilometrages, int annee_fab,const QString id_client,
                 const QString &etat, const QString &assurance);
    bool supprimer(const QString& num_matricule);
    bool modifier();
    QSqlQueryModel* afficher();
    QSqlQueryModel* rechercher(const QString &num_matricule);
    QSqlQueryModel* trierParModele();
    void exporterPDF(const QString &nomFichier, QAbstractItemModel *model);
    QMap<QString, int> getBrandStatistics();
    static void showAlert(const QString &title, const QString &message);


};

#endif // VEHICULES_H
