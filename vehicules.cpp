#include "vehicules.h"
#include <QDate>
#include <QDebug>
#include <QSqlError>

Vehicules::Vehicules()
{


}

Vehicules::Vehicules(int num_matricule, QString marque , QString modele , QString kilometrages, int annee_fab, int id_prop,  QString etat, QString assurance)
{
    this->num_matricule=num_matricule;
    this->marque=marque;
    this->modele=modele;
    this->kilometrages=kilometrages;
    this->annee_fab=annee_fab;
    this->id_prop=id_prop;
    this->etat=etat;
    this->assurance=assurance;
}

bool Vehicules ::ajouter()
{
    QSqlQuery query;

    query.prepare("INSERT INTO VEHICULES "
                  "(NUM_MATRICULE, MARQUE, MODELE, KILOMETRAGES, ANNEE_FAB,ID_PROP,ETAT,ASSURANCE) "
                  "VALUES (:num_matricule, :marque, :modele, :kilometrages, :annee_fab, :id_prop,  :etat, :assurance,)");

    query.bindValue(":num_matricule", num_matricule);
    query.bindValue(":marque", marque);
    query.bindValue(":modele", modele);
    query.bindValue(":kilometrages", kilometrages);
    query.bindValue(":annee_fab", annee_fab);
    query.bindValue(":id_prop", id_prop);
    query.bindValue(":etat", etat);
    query.bindValue(":assurance", assurance);



    if(!query.exec())
    {
        qDebug() <<"Erreur lors de l'insertion: " <<query.lastError().text();
        return false;
    }
    return true;

    if (!QSqlDatabase::database().isOpen()) {
        qDebug() << "Database connection is not open!";
        return false;
    }


}

bool Vehicules::supprimer(int num_matricule)
{
    QSqlQuery query;
    query.prepare("DELETE FROM VEHICULES WHERE NUM_MATRICULE = :num_matricule");
    query.bindValue(":num_matricule", num_matricule);

    return query.exec();
}


bool Vehicules::modifier()
{
    QSqlQuery query;
    query.prepare("UPDATE VEHICULES SET NUM_MATRICULE = :num_matricule, MARQUE = :marque, MODELE = :modele, "
                  "KILOMETRAGES = :kilometrages, ANNEE_FAB = :annee_fab, ID_PROP = :id_prop, ETAT = :etat, ASSURANCE = :assurance ");

    query.bindValue(":num_matricule", num_matricule);
    query.bindValue(":marque", marque);
    query.bindValue(":modele", modele);
    query.bindValue(":kilometrages", kilometrages);
    query.bindValue(":annee_fab", annee_fab);
    query.bindValue(":id_prop", id_prop);
    query.bindValue(":etat", etat);
    query.bindValue(":assurance", assurance);

    if (query.exec())
    {
        qDebug() << "modif Vehicules";
        return true;
    }
    else
    {
        return false;
    }
}

QSqlQueryModel* Vehicules::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM VEHICULES");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("NUM_MATRICULE"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("MARQUE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("MODELE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("KILOMETRAGES"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("ANNEE_FAB"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("ID_PROP"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("ETAT"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("ASSURANCE"));




    return model;
}
