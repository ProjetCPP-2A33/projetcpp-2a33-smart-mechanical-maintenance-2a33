#include "connection.h"

Connection::Connection()
{

}

bool Connection::createConnection()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("2a33 source");//inserer le nom de la source de données
db.setUserName("aziz");//inserer nom de l'utilisateur
db.setPassword("slouma");//inserer mot de passe de cet utilisateur

if (db.open()) test=true;


    return  test;
}
void Connection::closeConnection(){db.close();}
