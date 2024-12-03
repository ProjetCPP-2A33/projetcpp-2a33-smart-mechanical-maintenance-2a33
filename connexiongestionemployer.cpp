#include"connexiongestionemployer.h"
connexion::connexion()
{}
bool connexion::createconnexion()
{bool test=false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("Cpp_Projet");
    db.setUserName("tasnim");
    db.setPassword("oracle");
    if (db.open())
        test=true;





    return  test;
}
void connexion::closeConnexion(){db.close();
};

