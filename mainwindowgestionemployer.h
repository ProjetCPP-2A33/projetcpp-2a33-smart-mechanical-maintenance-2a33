#ifndef MAINWINDOWGESTIONEMPLOYER_H
#define MAINWINDOWGESTIONEMPLOYER_H
#include <QMainWindow>
#include "arduinov.h"
#include "employer.h"
#include "qchartview.h"
#include "qlabel.h"
#include "qlineedit.h"
#include "qpushbutton.h"
#include "qsqltablemodel.h"
#include "vehicules.h"
#include <QVBoxLayout>
#include <QSerialPort>
#include <QSerialPortInfo>

#include <QMainWindow>
#include <QChartView>
#include "qserialport.h"
#include <QPushButton>
#include <QStandardItemModel>
#include <QStyledItemDelegate>
#include <QPainter>
#include <QTableView>
#include <QSqlTableModel>
#include <QMainWindow>
#include <QtCharts>
#include <QSerialPort>
#include <QSerialPortInfo>
#include "vehicules.h"

namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE
class MainWindow : public QMainWindow
{
    Q_OBJECT
private slots:
    void on_ajouterButton_clicked();
    void on_supprimerButton_clicked();
    void on_afficherButton_clicked();
    void on_miseajourButton_clicked();
    void on_PDF_clicked();
    void on_trier_clicked();
    void on_Rechrche_clicked();
    void on_statistique_clicked();
    void on_notification_clicked();
    void onGestionVehicule();
    void onGestionClient();
    void onGestionLocaux();
    void onGestionEquipement();
    void onGestionFacture();
    void onGestionEmployerClicked();
    void on_verifier_clicked();
    void on_addButton_clicked();
    void onStatsClicked();
    void onPdfClicked();
    void onSortClicked();
    void onChercherButClicked();
    void onLoadClicked();
    void onBackupClicked();
    void onRestoreClicked();
    void onImportImageButtonClicked();
    void onTableViewSelectionChanged();
    void selectLastAddedClient(const QString &numCin);
    void gotoclient();
    void gotoemployee();
    void on_removeButton_clicked();
    void on_pb_select_clicked();

//vehicules
    void gotovehicule();
    void on_ajouter_clicked();
    void on_supprimer_clicked();
    void on_modifier_clicked();
    void on_trie_clicked();
    void on_rechercher_clicked();
    void on_pdf_clicked();
    void on_stat_clicked();
    void on_chatbutton_clicked();
    void on_alertes_clicked();
    void on_modify_clicked();
    void on_cancel_clicked();
    void on_arduino_clicked ();



public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void afficherNotification(const QString &message);
    bool verifierIdentifiants(const QString &username, const QString &password, const QString &module);
    QMap<QString, QPair<QString, QString>> identifiants;
    bool authenticate(const QString &username, const QString &password);



private:
    Ui::MainWindow *ui;
    Employer *employerWindow;
    Employer Employer;
    void afficherEmployesTable();
    QVBoxLayout *verticalLayout;
    QPushButton *notification;
    QLineEdit *dateInput;
    QSerialPort *serial;
    void loadClientData();


    Vehicules V;
    QSqlTableModel *model;
    QStandardItemModel *conversationModel;
    QChartView *chartView = nullptr;
    arduinov *arduino;
    QSerialPortInfo arduinoPortInfo;
    //QTableWidget *arduinoWidget;
    QString arduinoPortName;
    void handleArduinoData(QString data);
    //void setupConnections();
    void onMatriculeVerified(const QString &matricule, bool exists);

};
#endif // MAINWINDOWGESTIONEMPLOYER_H
