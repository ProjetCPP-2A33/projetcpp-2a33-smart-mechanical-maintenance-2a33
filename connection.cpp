#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnection()
{
    db = QSqlDatabase::addDatabase("QODBC");
    bool test=false;
    db.setDatabaseName("CPP_Project2A33");//inserer le nom de la source de données
    db.setUserName("Habiba");//inserer nom de l'utilisateur
    db.setPassword("hbiba");//inserer mot de passe de cet utilisateur

    if (db.open()) test=true;


    return  test;
}
void Connection ::closeConnection()
{
    db.close();
}
