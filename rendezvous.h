#ifndef RENDEZVOUS_H
#define RENDEZVOUS_H

#include <QString>
#include <QDateTime>
#include <QObject>

class Rendezvous
{
public:
    QString type;
    QString statut;
    QDateTime date;

    Rendezvous();
    Rendezvous(const QString &t, const QString &s, const QDateTime &d);
};

class ChatBot : public QObject
{
    Q_OBJECT

private:
    QString type;
    QString statut;
    QDateTime date;

public:
    ChatBot(QObject *parent = nullptr);

    QString setRendezvous(const QString &type, const QString &statut, const QDateTime &date);

    QString chatbotConversation();

    QString getRendezvousInfo() const;
};

#endif // RENDEZVOUS_H
