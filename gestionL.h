#ifndef GESTIONL_H
#define GESTIONL_H

#include <QMainWindow>
#include <QSqlQueryModel>
#include "arduinogestionL.h"
#include "tableviewwindow.h"
#include "NoteWindow.h"



namespace Ui {
    class GestionL;  // Changer MainWindow en GestionL ici

}

class GestionL : public QMainWindow {  // Changer MainWindow en GestionL ici
    Q_OBJECT

public:
    explicit GestionL(QWidget *parent = nullptr);  // Changer MainWindow en GestionL ici
    ~GestionL();
    Ui::GestionL *ui;

private slots:
    void on_gLpushbutton_ajouter_clicked();
    void on_gLpushbutton_modifier_clicked();
    void on_gLpushbutton_supprimer_clicked();
    void on_gLpushbutton_afficher_clicked();
    void on_gLpushButton_aff_clicked();
    void on_gLpushButton_showGraph_clicked();
    void checkTemperature();
    void on_gLpushButton_updateTemperature_clicked();
    void on_gLpushButton_note_clicked();
    void onEquipementClicked();
signals:
    void showClientPage();
    void showEmployeePage();
    void showFacturePage();
    void someSignal();
    void switchToVehicle();
    void switchToEquipement();
private:

    QSqlQueryModel *model;
    TableViewWindow *tableViewWindow;
    Arduino arduino;
  NoteWindow *noteWindow;
    bool isValidId(const QString &idText);
};

#endif // GESTIONL_H
