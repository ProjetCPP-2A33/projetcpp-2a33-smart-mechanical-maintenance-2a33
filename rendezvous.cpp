#include "rendezvous.h"
#include <QDebug>


Rendezvous::Rendezvous()
{

}

Rendezvous::Rendezvous(const QString &t, const QString &s, const QDateTime &d)
    : type(t), statut(s), date(d) {}


ChatBot::ChatBot(QObject *parent) : QObject(parent)
{

}

QString ChatBot::setRendezvous(const QString &type, const QString &statut, const QDateTime &date)
{
    this->type = type;
    this->statut = statut;
    this->date = date;
    return QString("Rendez-vous pour %1 prévu le %2 avec statut: %3")
        .arg(type)
        .arg(date.toString())
        .arg(statut);
}

QString ChatBot::chatbotConversation()
{
    QString typeRdv = "Mécanique";
    QString statutRdv = "Confirmé";
    QDateTime dateRdv = QDateTime::currentDateTime().addDays(2);

    return setRendezvous(typeRdv, statutRdv, dateRdv);
}

QString ChatBot::getRendezvousInfo() const
{
    return QString("Type: %1\nStatut: %2\nDate: %3")
    .arg(type)
        .arg(statut)
        .arg(date.toString());
}
