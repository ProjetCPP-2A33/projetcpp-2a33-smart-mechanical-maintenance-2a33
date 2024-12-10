#include"connexiongestionemployer.h"
connexion::connexion()
{}
bool connexion::createconnexion()
{bool test=false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("2a33 source");
    db.setUserName("omar");
    db.setPassword("esprit18");
    if (db.open())
        test=true;





    return  test;
}
void connexion::closeConnexion(){db.close();
};

