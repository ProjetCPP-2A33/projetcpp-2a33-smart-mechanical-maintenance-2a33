#include "mainwindowgestionemployer.h"
#include <QApplication>
#include "connexiongestionemployer.h"
#include <QMessageBox>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    connexion c;
    bool test = c.createconnexion();

    MainWindow w;
    if (test) {
        w.show();  // Affiche la fenêtre principale si la connexion est réussie
        QMessageBox::information(nullptr, QObject::tr("Database is open"),
                                 QObject::tr("Connection successful.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Database is not open"),
                              QObject::tr("Connection failed.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
        return -1;  // Quitter l'application si la connexion échoue
    }

    return a.exec();
}
