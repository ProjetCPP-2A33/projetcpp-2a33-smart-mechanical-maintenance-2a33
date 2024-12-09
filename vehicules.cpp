#include "vehicules.h"
#include <QDate>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QVariant>
#include <QPdfWriter>
#include <QPainter>
#include <QMessageBox>
#include <QColor>
#include <QDateTime>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QSqlTableModel>


Vehicules::Vehicules()
{
    num_matricule="";
    marque="";
    modele="";
    kilometrages="";
    annee_fab=0;
    id_client="";
    etat="";
    assurance="";
}

Vehicules::Vehicules(QString num_matricule, QString marque , QString modele , QString kilometrages, int annee_fab, QString id_client,  QString etat, QString assurance)
{
    this->num_matricule=num_matricule;
    this->marque=marque;
    this->modele=modele;
    this->kilometrages=kilometrages;
    this->annee_fab=annee_fab;
    this->id_client=id_client;
    this->etat=etat;
    this->assurance=assurance;
}



bool Vehicules::ajouter(const QString &num_matricule, const QString &marque, const QString &modele,
                        const QString &kilometrages, int annee_fab, const QString id_client,
                        const QString &etat, const QString &assurance)
{


    qDebug() << "Vérification des données saisies :";
    qDebug() << "Numéro de matricule: " << num_matricule;
    qDebug() << "Kilométrages: " << kilometrages;
    qDebug() << "ID client: " << id_client;
    qDebug() << "Année de fabrication: " << annee_fab;
    qDebug() << "État: " << etat;
    qDebug() << "Assurance: " << assurance;

    // Contrôle de saisie du numéro de matricule
    QRegularExpression matriculeRegex("^\\d{3}(tunis|nt|etranger)\\d{4}$");
    QRegularExpressionMatch matriculeMatch = matriculeRegex.match(num_matricule);
    if (!matriculeMatch.hasMatch())
    {
        qDebug() << "Erreur: Le numéro de matricule n'est pas valide.";
        return false;
    }

    // Contrôle de saisie du kilométrage
    QRegularExpression kmRegex("^\\d+(KM)$");
    QRegularExpressionMatch kmMatch = kmRegex.match(kilometrages);
    if (!kmMatch.hasMatch())
    {
        qDebug() << "Erreur: Le kilométrage doit se terminer par 'KM'.";
        return false;
    }

    // Contrôle de saisie de l'ID client (8 chiffres, premier chiffre 0 ou 1)
    QRegularExpression idClientRegex("^[01]\\d{7}$");
    QRegularExpressionMatch idClientMatch = idClientRegex.match(id_client);
    if (!idClientMatch.hasMatch())
    {
        qDebug() << "Erreur: L'ID client doit être composé de 8 chiffres et commencer par 0 ou 1.";
        return false;
    }


    QSqlQuery query;
    query.prepare("INSERT INTO Vehicules (num_matricule, marque, modele, kilometrages, annee_fab, id_client, etat, assurance) "
                  "VALUES (:num_matricule, :marque, :modele, :kilometrages, :annee_fab, :id_client, :etat, :assurance)");

    query.bindValue(":num_matricule", num_matricule);
    query.bindValue(":marque", marque);
    query.bindValue(":modele", modele);
    query.bindValue(":kilometrages", kilometrages);
    query.bindValue(":annee_fab", annee_fab);
    query.bindValue(":id_client", id_client);
    query.bindValue(":etat", etat);
    query.bindValue(":assurance", assurance);

    if (query.exec())
    {
        qDebug() << "Véhicule ajouté avec succès!";


        return true;
    }
    else
    {
        qDebug() << "Erreur lors de l'ajout du véhicule:" << query.lastError().text();
        return false;
    }
}


bool Vehicules::supprimer(const QString& num_matricule)
{
    QSqlQuery query;
    query.prepare("DELETE FROM vehicules WHERE num_matricule = :num_matricule");
    query.bindValue(":num_matricule", num_matricule);
    return query.exec();
}


bool Vehicules::modifier()
{
    QSqlQuery query;
    query.prepare("UPDATE VEHICULES SET NUM_MATRICULE = :num_matricule, MARQUE = :marque, MODELE = :modele, "
                  "KILOMETRAGES = :kilometrages, ANNEE_FAB = :annee_fab, ID_CLIENT = :id_client, ETAT = :etat, ASSURANCE = :assurance ");

    query.bindValue(":num_matricule", num_matricule);
    query.bindValue(":marque", marque);
    query.bindValue(":modele", modele);
    query.bindValue(":kilometrages", kilometrages);
    query.bindValue(":annee_fab", annee_fab);
    query.bindValue(":id_client", id_client);
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

    model->setQuery("SELECT num_matricule, marque, modele, kilometrages, annee_fab, id_client, etat, assurance FROM VEHICULES");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Num Matricule"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Marque"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Modèle"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Kilométrages"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Année de Fab."));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("ID Client"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("État"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Assurance"));

    return model;
}


QSqlQueryModel* Vehicules::rechercher(const QString &num_matricule)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;

    query.prepare("SELECT * FROM vehicules WHERE num_matricule = :num_matricule");
    query.bindValue(":num_matricule", num_matricule);

    if (query.exec())
    {
        model->setQuery(std::move(query));
    }
    else
    {
        qDebug() << "Erreur lors de l'exécution de la requête de recherche :" << query.lastError().text();
    }

    return model;
}


QSqlQueryModel* Vehicules::trierParModele()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;

    query.prepare("SELECT num_matricule, marque, modele, kilometrages, annee_fab, id_client, etat, assurance FROM VEHICULES ORDER BY modele ASC");

    if (query.exec())
    {
        model->setQuery(std::move(query)); // Use std::move to pass the query by move
    }
    else
    {
        qDebug() << "Erreur lors du tri des véhicules par modèle:" << query.lastError().text();
    }

    return model;
}


void Vehicules::exporterPDF(const QString &nomFichier, QAbstractItemModel *model)
{
    QPdfWriter pdfWriter(nomFichier);
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));
    pdfWriter.setTitle("Liste des Véhicules");

    QPainter painter(&pdfWriter);

    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 20));

    painter.drawText(2500, 1100, "Liste des Véhicules");

    int startX = 200;
    int startY = 1800;
    int cellWidth = 1100;
    int cellHeight = 450;

    QStringList headers = {"Num Matricule", "Marque", "Modèle", "Kilométrages", "Année de Fab.", "ID Client", "État", "Assurance"};
    painter.setFont(QFont("Arial", 10, QFont::Bold));

    for (int col = 0; col < headers.size(); ++col)
    {
        painter.drawText(startX + col * cellWidth, startY, cellWidth, cellHeight, Qt::AlignCenter, headers[col]);
    }

    int rowCount = model->rowCount();
    painter.setFont(QFont("Arial", 10));
    for (int row = 0; row < rowCount; ++row)
    {
        QColor bgColor = (row % 2 == 0) ? Qt::lightGray : Qt::white;

        for (int col = 0; col < headers.size(); ++col)
        {
            QString data = model->data(model->index(row, col)).toString();
            QRect cellRect(startX + col * cellWidth, startY + (row + 1) * cellHeight, cellWidth, cellHeight);

            painter.fillRect(cellRect, bgColor);
            painter.drawText(cellRect, Qt::AlignCenter, data);
            painter.drawRect(cellRect);
        }
    }

    painter.end();

    QMessageBox::information(nullptr, "PDF Créé", "Un fichier PDF a été créé.");

}


QMap<QString, int> Vehicules::getBrandStatistics()
{
    QMap<QString, int> brandCounts;
    QSqlQuery query;

    query.prepare("SELECT marque, COUNT(*) FROM vehicules GROUP BY marque");

    if (query.exec())
    {
        while (query.next())
        {
            QString brand = query.value(0).toString();
            int count = query.value(1).toInt();
            brandCounts[brand] = count;
        }
    }
    else
    {
        qDebug() << "Erreur lors de la récupération des statistiques de marque : " << query.lastError();
    }

    return brandCounts;
}


void Vehicules::showAlert(const QString &title, const QString &message)
{
    QMessageBox::information(nullptr, title, message);
}
