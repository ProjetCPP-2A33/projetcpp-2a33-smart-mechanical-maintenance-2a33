#include "employer.h"
#include <QSqlError>
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QPainter>
#include <QPrinter>
#include <QFont>
#include <QPdfWriter>
#include <QMessageBox>
#include <QDate>
#include <QRegularExpression>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QProcess>

Employer::Employer() : id(0),age(0), nomemployee(""), adresse(""), email(""), num_telephone(0), date_embauche(0) {}

Employer::Employer(int id,int age, QString nomemployee, QString adresse, QString email, int num_telephone, int date_embauche)
    : id(id),age (age), nomemployee(nomemployee), adresse(adresse), email(email), num_telephone(num_telephone), date_embauche(date_embauche) {}

int Employer::getId() const { return id; }
int Employer::getage() const{return age ;}
QString Employer::getNomemployee() const { return nomemployee; }
QString Employer::getAdresse() const { return adresse; }
QString Employer::getEmail() const { return email; }
int Employer::getNumTelephone() const { return num_telephone; }
int Employer::getDateEmbauche() const { return date_embauche; }

void Employer::setId(int id) { this->id = id; }
void Employer::setage(int age) { this->age = age; }
void Employer::setNomemployee(const QString &nomemployee) { this->nomemployee = nomemployee; }
void Employer::setAdresse(const QString &adresse) { this->adresse = adresse; }
void Employer::setEmail(const QString &email) { this->email = email; }
void Employer::setNumTelephone(int num_telephone) { this->num_telephone = num_telephone; }
void Employer::setDateEmbauche(int date_embauche) { this->date_embauche = date_embauche; }

bool Employer::ajouter(int id, int age, const QString& nomemployee, const QString& adresse, const QString& email, int num_telephone, int date_embauche) {
    QSqlQuery query;
    query.prepare("INSERT INTO EMPLOYER (ID, AGE, NOMEMPLOYEE, ADRESSE, EMAIL, NUM_TELEPHONE, DATE_EMBAUCHE) "
                  "VALUES (:id, :age, :nomemployee, :adresse, :email, :num_telephone, :date_embauche)");
    if (id <= 0) {
        QMessageBox::warning(nullptr, "Erreur", "L'ID doit être un entier positif.");
        return false;
    }
    if (age < 18 || age > 100) {
        QMessageBox::warning(nullptr, "Erreur", "L'âge doit être compris entre 18 et 100 ans.");
        return false;
    }
    QString numTelStr = QString::number(num_telephone);
    QRegularExpression phoneRegex("^\\d{8}$");  // Doit être composé de 8 chiffres
    if (num_telephone <= 0 || !phoneRegex.match(numTelStr).hasMatch()) {
        QMessageBox::warning(nullptr, "Erreur", "Le numéro de téléphone doit être composé de 8 chiffres.");
        return false;
    }

    query.bindValue(":id", id);
    query.bindValue(":age", age);
    query.bindValue(":nomemployee", nomemployee);
    query.bindValue(":adresse", adresse);
    query.bindValue(":email", email);
    query.bindValue(":num_telephone", num_telephone);
    query.bindValue(":date_embauche", date_embauche);

    return query.exec();
}


#include <QList>

QList<Employer> Employer:: afficher()
{
    QList<Employer> employes;
    QSqlQuery query("SELECT ID, AGE, NOMEMPLOYEE, ADRESSE, EMAIL, NUM_TELEPHONE, DATE_EMBAUCHE FROM EMPLOYER");

    while (query.next()) {
        int id = query.value(0).toInt();
        int age = query.value(1).toInt();
        QString nomemployee = query.value(2).toString();
        QString adresse = query.value(3).toString();
        QString email = query.value(4).toString();
        int num_telephone = query.value(5).toInt();
        int date_embauche = query.value(6).toInt();

        Employer emp(id, age, nomemployee, adresse, email, num_telephone, date_embauche);
        employes.append(emp);
    }

    return employes;
}

bool Employer::supprimer(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM EMPLOYER WHERE ID = :id");
    query.bindValue(":id", id);
    return query.exec();
}
QSqlQueryModel* Employer::afficherEmployes() {
    QSqlQueryModel *model = new QSqlQueryModel();

    // Exécution de la requête SQL pour récupérer les informations des employés
    QSqlQuery query;
    query.prepare("SELECT ID, NOMEMPLOYEE, ADRESSE, EMAIL, NUM_TELEPHONE, DATE_EMBAUCHE, AGE FROM EMPLOYER");

    if (!query.exec()) {
        qDebug() << query.lastError();  // Affiche l'erreur s'il y en a une
        delete model;  // Libérer la mémoire si une erreur survient
        return nullptr;
    }

    model->setQuery(query);  // Utiliser setQuery pour définir la requête sur le modèle
    return model;
}
void Employer::exporterPDF(const QString &nomFichier, QSqlQueryModel *model)
{
    QPdfWriter pdfWriter(nomFichier);
    QPainter painter(&pdfWriter);


    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 12));


    painter.drawText(2500, 1100, "Liste des Employés");

    // Coordonnées et dimensions des cellules
    int startX = 200;
    int startY = 1800;
    int cellWidth = 1100;
    int cellHeight = 450;

    // En-têtes du tableau
    QStringList headers = {"ID", "Nom", "Adresse", "Email", "Numéro", "Date Embauche", "Age"};
    painter.setFont(QFont("Arial", 10, QFont::Bold));
    for (int col = 0; col < headers.size(); ++col) {
        painter.drawText(startX + col * cellWidth, startY, cellWidth, cellHeight, Qt::AlignCenter, headers[col]);
    }

    // Données des employés
    int rowCount = model->rowCount();
    painter.setFont(QFont("Arial", 10));
    for (int row = 0; row < rowCount; ++row) {
        QColor bgColor = (row % 2 == 0) ? Qt::lightGray : Qt::white;

        for (int col = 0; col < headers.size(); ++col) {
            QString data = model->data(model->index(row, col)).toString();
            QRect cellRect(startX + col * cellWidth, startY + (row + 1) * cellHeight, cellWidth, cellHeight);

            painter.fillRect(cellRect, bgColor);
            painter.drawText(cellRect, Qt::AlignCenter, data);
            painter.drawRect(cellRect);
        }
    }


    painter.end();
}
QSqlQueryModel* Employer::afficherTriParId() {
    QSqlQueryModel *model = new QSqlQueryModel();


    QSqlQuery query;
    query.prepare("SELECT ID, NOMEMPLOYEE, ADRESSE, EMAIL, NUM_TELEPHONE, DATE_EMBAUCHE, AGE FROM EMPLOYER ORDER BY ID ASC");

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête : " << query.lastError();
        delete model;
        return nullptr;
    }

    model->setQuery(query);
    return model;
}
QSqlQueryModel* Employer::rechercherParId(int id)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;

    query.prepare("SELECT id, nomemployee, adresse, email, num_telephone, date_embauche, age FROM EMPLOYER WHERE id = :id");
    query.bindValue(":id", id);

    if (query.exec()) {
        model->setQuery(query);

        if (model->rowCount() == 0) {
            qDebug() << "Aucun employé trouvé avec l'ID:" << id;
            delete model;
            return nullptr;
        }

        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom Employee"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Adresse"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("Email"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Numéro Téléphone"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("Date Embauche"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("Age"));
    }
    else {
        qDebug() << "Erreur lors de la recherche de l'employé par ID:" << query.lastError().text();
        delete model;
        return nullptr;
    }

    return model;
}
QMap<QString, int> Employer::statistiquesParTrancheAge() {
    QMap<QString, int> statistiques;

    QSqlQuery query;


    query.prepare("SELECT COUNT(*) FROM EMPLOYER WHERE age < 25");
    if (query.exec()) {
        query.next();
        statistiques["Moins de 25 ans"] = query.value(0).toInt();
    } else {
        qDebug() << "Erreur requête Moins de 25 ans: " << query.lastError();
    }


    query.prepare("SELECT COUNT(*) FROM EMPLOYER WHERE age >= 25 AND age < 35");
    if (query.exec()) {
        query.next();
        statistiques["25-34 ans"] = query.value(0).toInt();
    } else {
        qDebug() << "Erreur requête 25-34 ans: " << query.lastError();
    }


    query.prepare("SELECT COUNT(*) FROM EMPLOYER WHERE age >= 35 AND age < 45");
    if (query.exec()) {
        query.next();
        statistiques["35-44 ans"] = query.value(0).toInt();
    } else {
        qDebug() << "Erreur requête 35-44 ans: " << query.lastError();
    }


    query.prepare("SELECT COUNT(*) FROM EMPLOYER WHERE age >= 45 AND age < 55");
    if (query.exec()) {
        query.next();
        statistiques["45-54 ans"] = query.value(0).toInt();
    } else {
        qDebug() << "Erreur requête 45-54 ans: " << query.lastError();
    }


    query.prepare("SELECT COUNT(*) FROM EMPLOYER WHERE age >= 55");
    if (query.exec()) {
        query.next();
        statistiques["55 ans et plus"] = query.value(0).toInt();
    } else {
        qDebug() << "Erreur requête 55 ans et plus: " << query.lastError();
    }

    return statistiques;
}

