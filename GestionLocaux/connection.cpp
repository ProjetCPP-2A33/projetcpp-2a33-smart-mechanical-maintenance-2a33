#include "connection.h"

Connection::Connection()
{

}

bool Connection::createConnection()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("Source_Projet2A");//inserer le nom de la source de données
db.setUserName("malek");//inserer nom de l'utilisateur
db.setPassword("rebaa");//inserer mot de passe de cet utilisateur

if (db.open()) test=true;


    return  test;
}
void Connection::closeConnection(){db.close();}
