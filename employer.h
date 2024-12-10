#ifndef EMPLOYER_H
#define EMPLOYER_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QFile>
#include <QTextStream>

class Employer {
public:
    Employer();
    Employer(int id, int age,QString nomemployee, QString adresse, QString email, int num_telephone, int date_embauche);

    int getId() const;
    int getage()const;
    QString getNomemployee() const;
    QString getAdresse() const;
    QString getEmail() const;
    int getNumTelephone() const;
    int getDateEmbauche() const;

    void setId(int id);
    void setNomemployee(const QString &nomemployee);
    void setage(int age);
    void setAdresse(const QString &adresse);
    void setEmail(const QString &email);
    void setNumTelephone(int num_telephone);
    void setDateEmbauche(int date_embauche);
    bool test;

    bool ajouter(int id,int age, const QString& nomemployee, const QString& adresse, const QString& email, int num_telephone, int date_embauche);
    QList<Employer> afficher();
    bool supprimer(int id);
    QSqlQueryModel* afficherEmployes();
    QSqlQueryModel* afficherTriParId();
    void exporterPDF(const QString &nomFichier, QSqlQueryModel *model);
    QSqlQueryModel* rechercherParId(int id);
    static QMap<QString, int> statistiquesParTrancheAge();
private:
    int id;
    int age;
    QString nomemployee;
    QString adresse;
    QString email;
    int num_telephone;
    int date_embauche;
    static QVector<int> ages;
};


#endif // EMPLOYER_H
