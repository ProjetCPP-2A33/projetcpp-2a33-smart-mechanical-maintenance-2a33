#ifndef VEHICULES_H
#define VEHICULES_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>



class Vehicules
{
    int num_matricule ;
    QString marque, modele,kilometrages;
    int annee_fab,id_prop;
    QString  etat, assurance;
    QString Type_rend,Status_rend;
    int date_rend;


    public:
    //constructeurs
    Vehicules();
    Vehicules(int num_matricule, QString marque, QString modele, QString kilometrages, int annee_fab, int id_prop, QString etat, QString assurance);

    //getters
    int getNum_matricule()  {return num_matricule ;}
    QString getMarque () {return marque; }
    QString getModele () {return modele; }
    QString getKilometrages () {return kilometrages; }
    int getAnnee_fab (){return annee_fab ;}
    int getId_prop () {return id_prop;}
    QString getEtat () {return etat; }
    QString getAssurance () {return assurance; }
    QString getType_rend () {return Type_rend; }
    QString getStatus_rend () {return Status_rend; }
    int getDate_rend () {return date_rend;}




    //Fonctionnalités de base relative à l'entité
    bool ajouter();
    bool supprimer(int num_matricule);
    bool modifier();
    QSqlQueryModel* afficher();


};

#endif // VEHICULES_H
