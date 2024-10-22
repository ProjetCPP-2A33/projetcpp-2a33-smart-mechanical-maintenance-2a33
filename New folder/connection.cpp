#include "connection.h"
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>

Connection::Connection()
{
    // Constructor
    db = QSqlDatabase::addDatabase("QODBC");
}

bool Connection::createconnect()
{
    db.setDatabaseName("2a33 source");  // Your DSN
    db.setUserName("projetcpp2a33");   // Your username
    db.setPassword("2a33user");        // Your password

    if (!db.open()) {
        qDebug() << "Error: Could not open database. Error details: " << db.lastError().text();
        return false;
    }

    qDebug() << "Database connection successful!";
    return true;
}
