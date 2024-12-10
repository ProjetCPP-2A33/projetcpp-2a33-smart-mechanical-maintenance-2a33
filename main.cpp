#include "mainwindowgestionemployer.h"
#include <QApplication>
#include "connexiongestionemployer.h"
#include <QMessageBox>

#include "gestionL.h"
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    connexion c;
    bool test = c.createconnexion();
    GestionL L;
    MainWindow w;
    if (test) {
        w.show();  // Affiche la fenêtre principale si la connexion est réussie

    } else {
        return -1;
    }

    return a.exec();
}
