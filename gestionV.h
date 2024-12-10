#ifndef GESTIONV_H
#define GESTIONV_H

#include <QMainWindow>
#include <QChartView>
#include "arduinogestionL.h"
#include "vehicules.h"
#include <QPushButton>
#include <QStandardItemModel>
#include <QStyledItemDelegate>
#include <QPainter>
#include <QTableView>
#include <QSqlTableModel> // Assurez-vous d'inclure QSqlTableModel
#include <QMainWindow>
#include <QtCharts>
#include <QSerialPort>
#include <QSerialPortInfo>


namespace Ui
{
class MainWindow2;
}

class MainWindow2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow2(QWidget *parent = nullptr);
    ~MainWindow2();
signals:
    void showClientPage();
    void showEmployeePage();
    void showEquipementPage();
    void showLocauxPage();
    void showFacturePage();
    void switchToEquipement();
    void switchToLocaux();

private slots:
    void on_ajouter_clicked();
    void on_supprimer_clicked();
    void on_modifier_clicked();
    void on_trier_clicked();
    void on_rechercher_clicked();
    void on_PDF_clicked();
    void on_statistique_clicked();
    void on_chatbutton_clicked();
    void on_alertes_clicked();
    void on_modify_clicked();
    void on_cancel_clicked();
    void on_arduino_clicked ();
    //void on_clear_clicked();


private:
    Ui::MainWindow2 *ui;
    Vehicules V;
    QSqlTableModel *model;  // Déclaration du modèle pour QTableView
    QChartView *chartView = nullptr;
    QStandardItemModel *conversationModel;    // Modèle pour afficher les messages de chatbot
    Arduino *arduino; // Déclaration de l'objet Arduino
    QSerialPortInfo arduinoPortInfo;
    //QTableWidget *arduinoWidget;
    QString arduinoPortName;
    void handleArduinoData(QString data);
    //void setupConnections();
    void onMatriculeVerified(const QString &matricule, bool exists);




};

#endif // GESTIONV_H
