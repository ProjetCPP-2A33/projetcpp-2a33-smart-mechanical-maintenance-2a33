#ifndef CONNEXIONGESTIONEMPLOYER_H
#define CONNEXIONGESTIONEMPLOYER_H
#include <QSqlDatabase>
#include <QDebug>

class connexion
{    QSqlDatabase db;
public:
    connexion();
    bool createconnexion();
    void closeConnexion();
};

#endif // CONNEXIONGESTIONEMPLOYER_H
