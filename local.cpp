#include "local.h"
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlQuery>
#include <QLocale>
#include <QSqlError>

Local::Local() {
    ID_local = 0;
    adresse = "";
    Responsable = "";
    Num_telephone = 0;
    Service = "";
    heure_travail = 0;
    email = "";
}

Local::Local(int id) {
    ID_local = id;
}

Local::Local(int x1, QString x2, QString x3, int x4, QString x5, int x6, QString x7) {
    this->ID_local = x1;
    this->adresse = x2;
    this->Responsable = x3;
    this->Num_telephone = x4;
    this->Service = x5;
    this->heure_travail = x6;
    this->email = x7;
}

bool Local::ajouter() {
    QSqlQuery query;
    query.prepare("INSERT INTO Local (ID_local, adresse, Responsable, Num_telephone, Service, heure_travail, email) "
                  "VALUES (:ID_local, :adresse, :Responsable, :Num_telephone, :Service, :heure_travail, :email)");
    query.bindValue(":ID_local", ID_local);
    query.bindValue(":adresse", adresse);
    query.bindValue(":Responsable", Responsable);
    query.bindValue(":Num_telephone", Num_telephone);
    query.bindValue(":Service", Service);
    query.bindValue(":heure_travail", heure_travail);
    query.bindValue(":email", email);

    return query.exec();
}

bool Local::modifier() {
    QSqlQuery query;
    query.prepare("UPDATE Local SET adresse = ?, Responsable = ?, Num_telephone = ?, Service = ?, heure_travail = ?, email = ? WHERE ID_local = ?");
    query.addBindValue(adresse);
    query.addBindValue(Responsable);
    query.addBindValue(Num_telephone);
    query.addBindValue(Service);
    query.addBindValue(heure_travail);
    query.addBindValue(email);
    query.addBindValue(ID_local);

    return query.exec();
}
bool Local::supprimer() {
    QSqlDatabase db = QSqlDatabase::database();
    db.transaction();  // Start a transaction to ensure atomic operation

    QSqlQuery query;

    // First, delete associated notes
    query.prepare("DELETE FROM Notes WHERE ID_local = :ID_local");
    query.bindValue(":ID_local", ID_local);
    if (!query.exec()) {
        qDebug() << "Erreur lors de la suppression des notes: " << query.lastError().text();
        db.rollback();  // Rollback transaction if this fails
        return false;
    }

    // Then, delete the local entry
    query.prepare("DELETE FROM Local WHERE ID_local = :ID_local");
    query.bindValue(":ID_local", ID_local);
    if (!query.exec()) {
        qDebug() << "Erreur lors de la suppression du local: " << query.lastError().text();
        db.rollback();  // Rollback transaction if this fails
        return false;
    }

    db.commit();  // Commit transaction if both deletions succeed
    return true;
}


QSqlQueryModel* Local::afficher() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM Local");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_local"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Adresse"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Responsable"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Num_telephone"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Service"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Heure_travail"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Email"));

    return model;
}

int Local::countLocaux() {
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM Local");
    if (query.exec()) {
        if (query.next()) {
            return query.value(0).toInt(); // Return the count of rows
        }
    }
    return 0; // Return 0 if the query fails or there are no entries
}


