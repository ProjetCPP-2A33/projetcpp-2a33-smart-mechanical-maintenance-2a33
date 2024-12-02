#ifndef CONNEXION_H
#define CONNEXION_H
#include <QSqlDatabase>
#include <QDebug>

class connexion
{    QSqlDatabase db;
public:
    connexion();
    bool createconnexion();
    void closeConnexion();
};

#endif // CONNEXION_H
