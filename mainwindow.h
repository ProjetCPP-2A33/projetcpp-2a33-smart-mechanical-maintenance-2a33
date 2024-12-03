#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

#include "equipement.h"
#include "qstandarditemmodel.h"
#include "ui_mainwindow.h"
#include "arduino.h"   // Include the Arduino header

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void sendEmailWithPostmark();

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

    void updateTemperature();  // Slot to update the temperature periodically

private:
    void populateStatutComboBox();
    void updateTemperatureInDatabase(float temperature);  // Add this declaration


    Ui::MainWindow *ui;
    Equipement equipement;

    QStandardItemModel *historiqueModel;

    Arduino arduino;  // Arduino object to communicate with the Arduino
};

#endif // MAINWINDOW_H
