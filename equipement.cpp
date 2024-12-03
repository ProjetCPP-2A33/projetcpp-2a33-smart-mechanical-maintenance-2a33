#include "equipement.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QDebug>
#include <QPainter>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QDebug>



// Constructeurs
Equipement::Equipement() {}

Equipement::Equipement(int id, QString nom, QString type, QString statut, QDate dateAcquisition, QString responsable)
    : id(id), nom(nom), type(type), statut(statut), dateAcquisition(dateAcquisition), responsable(responsable) {}

Equipement::Equipement(QString nom, QString type, QString statut, QDate dateAcquisition, QString responsable)
    : nom(nom), type(type), statut(statut), dateAcquisition(dateAcquisition), responsable(responsable) {}

// Getters
int Equipement::getID() const {
    return id;
}

QString Equipement::getNom() const {
    return nom;
}

QString Equipement::getType() const {
    return type;
}

QString Equipement::getStatut() const {
    return statut;
}

QDate Equipement::getDateAcquisition() const {
    return dateAcquisition;
}

QString Equipement::getResponsable() const {
    return responsable;
}

// Setters
void Equipement::setID(int id) {
    this->id = id;
}

void Equipement::setNom(QString nom) {
    this->nom = nom;
}

void Equipement::setType(QString type) {
    this->type = type;
}

void Equipement::setStatut(QString statut) {
    this->statut = statut;
}

void Equipement::setDateAcquisition(QDate dateAcquisition) {
    this->dateAcquisition = dateAcquisition;
}

void Equipement::setResponsable(QString responsable) {
    this->responsable = responsable;
}

// Méthodes de gestion de la base de données
bool Equipement::ajouter() {
    QSqlQuery query;

    // Here, we assume the ID is manually provided and is not auto-incremented by the database
    query.prepare("INSERT INTO equipement (id, nom, type, statut, date_acquisition, responsable) "
                  "VALUES (:id, :nom, :type, :statut, :date_acquisition, :responsable)");

    query.bindValue(":id", id); // Bind the id value
    query.bindValue(":nom", nom);
    query.bindValue(":type", type);
    query.bindValue(":statut", statut);
    query.bindValue(":date_acquisition", dateAcquisition);
    query.bindValue(":responsable", responsable);

    return query.exec();
}

bool Equipement::modifier(int id) {
    QSqlQuery query;

    query.prepare("UPDATE equipement SET nom = :nom, type = :type, statut = :statut, "
                  "date_acquisition = :date_acquisition, responsable = :responsable "
                  "WHERE id = :id");

    query.bindValue(":id", id); // Use the provided ID for updating
    query.bindValue(":nom", nom);
    query.bindValue(":type", type);
    query.bindValue(":statut", statut);
    query.bindValue(":date_acquisition", dateAcquisition);
    query.bindValue(":responsable", responsable);

    return query.exec();
}

QSqlQueryModel* Equipement::afficher() {
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM equipement ORDER BY id");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Statut"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date d'Acquisition"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Responsable"));

    return model;
}

bool Equipement::supprimer(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM equipement WHERE id = :id");
    query.bindValue(":id", id);
    return query.exec();
}

QSqlQueryModel* Equipement::trierPar(bool ordreAscendant) {
    QSqlQueryModel *model = new QSqlQueryModel();
    QString ordre = ordreAscendant ? "ASC" : "DESC";

    QString requete = QString("SELECT * FROM equipement ORDER BY date_acquisition %1").arg(ordre);

    model->setQuery(requete);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Statut"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date d'Acquisition"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Responsable"));

    return model;
}

QMap<QString, int> Equipement::getStatistiques() {
    QMap<QString, int> statistiques;
    QSqlQuery query;

    query.prepare("SELECT statut, COUNT(*) FROM equipement GROUP BY statut");

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête pour les statistiques :"
                 << query.lastError().text(); // Use .text() for detailed error
        qDebug() << "Query attempted:" << query.lastQuery();
        return statistiques;
    }

    while (query.next()) {
        QString statut = query.value(0).toString();
        int count = query.value(1).toInt();
        statistiques[statut] = count;
    }

    return statistiques;
}


QSqlQueryModel* Equipement::rechercherParID(int id) {
    QSqlQueryModel* model = new QSqlQueryModel();

    QString queryString = QString("SELECT * FROM equipement WHERE id = %1").arg(id);
    model->setQuery(queryString);

    if (model->lastError().isValid()) {
        qDebug() << "Erreur lors de l'exécution de la requête : " << model->lastError().text();
        delete model; // Clean up allocated memory if returning nullptr
        return nullptr;
    }

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Statut"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date d'Acquisition"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Responsable"));

    return model;
}
