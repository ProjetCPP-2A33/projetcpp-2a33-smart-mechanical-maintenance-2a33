#ifndef EQUIPEMENT_H
#define EQUIPEMENT_H

#include <QString>
#include <QDate>
#include <QSqlQueryModel>
#include <QMap>

class Equipement
{
public:
    // Constructors
    Equipement();
    Equipement(int id, QString nom, QString type, QString statut, QDate dateAcquisition, QString responsable);
    Equipement(QString nom, QString type, QString statut, QDate dateAcquisition, QString responsable);

    // Getters
    int getID() const;
    QString getNom() const;
    QString getType() const;
    QString getStatut() const;
    QDate getDateAcquisition() const;
    QString getResponsable() const;

    // Setters
    void setID(int id);
    void setNom(QString nom);
    void setType(QString type);
    void setStatut(QString statut);
    void setDateAcquisition(QDate dateAcquisition);
    void setResponsable(QString responsable);

    // Database management methods
    bool ajouter(); // Add a new equipment
    bool modifier(int id); // Modify an equipment
    bool supprimer(int id); // Delete an equipment
    QSqlQueryModel* afficher(); // Display all equipment
    QSqlQueryModel* trierPar(bool ordreAscendant); // Sort equipment by acquisition date
    QMap<QString, int> getStatistiques(); // Get statistics based on the 'statut'
    QSqlQueryModel* rechercherParID(int id); // Search equipment by ID

    // Add method for logging history
    bool logHistorique(const QString &actionType, int equipementId, const QString &oldData = "", const QString &newData = "");

private:
    int id;
    QString nom;
    QString type;
    QString statut;
    QDate dateAcquisition;
    QString responsable;
};

#endif // EQUIPEMENT_H
