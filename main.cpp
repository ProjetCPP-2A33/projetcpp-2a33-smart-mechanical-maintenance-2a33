#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QMessageBox>
#include "connection.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connection c;
    bool test = c.createconnection();
    MainWindow w;

    if (test)
    {
        w.setWindowState(Qt::WindowMaximized);
        w.show();
        QMessageBox::information(nullptr, QObject::tr("Database is open"),
                                 QObject::tr("connection successfull.\nClick cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical (nullptr, QObject::tr("Database is not open"),
                                 QObject::tr("connection failed.\nClick cancel to exit."), QMessageBox::Cancel);
    }

    return a.exec();
}
