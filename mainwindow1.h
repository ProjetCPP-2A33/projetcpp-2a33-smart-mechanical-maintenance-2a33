#ifndef MAINWINDOW1_H
#define MAINWINDOW1_H

#include <QMainWindow>
#include <QTableView>
#include <QComboBox>
#include <QDateEdit>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextDocument>
#include <QMap>
#include <QSqlQueryModel>
#include <QModelIndex>
#include <QLCDNumber>  // Include the header for QLCDNumber
#include <QTimer>      // Include the header for QTimer
#include "arduinogestionL.h"
#include "ui_mainwindow1.h"

#include "equipement.h"
#include "qstandarditemmodel.h"
#include "arduinogestionL.h"   // Include the Arduino header

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow1; }
QT_END_NAMESPACE

class MainWindow1 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow1(QWidget *parent = nullptr);
    ~MainWindow1();
    void sendEmailWithPostmark();
signals:
    void showClientPage1();
    void showEmployeePage1();
    void showFacturePage1();
    void someSignal();
    void switchToVehicle();
    void switchToLocaux();
private slots:
    void on_ajouter_equi_clicked();
    void on_tableView_equipement_doubleClicked(const QModelIndex &index);
    void on_supp_equi_clicked();
    void on_tri_equi_clicked();
    void on_recherche_equi_clicked();
    void on_statistique_equi_clicked();
    void on_export_pdf_clicked();
    void on_historique_clicked();
    void on_modifer_equi_clicked();
    void on_pushButtonSend_clicked();
    void onLocauxClicked();
    void updateTemperature();  // Slot to update the temperature periodically
    void on_vehicleButton_clicked();
    void on_locauxButton_clicked();

private:
    void populateStatutComboBox();
    void updateTemperatureInDatabase(float temperature);  // Add this declaration


    Ui::MainWindow1 *ui;
    Equipement equipement;

    QStandardItemModel *historiqueModel;

    Arduino arduino;  // Arduino object to communicate with the Arduino
};

#endif // MAINWINDOW1_H
