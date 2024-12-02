#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "employer.h"
#include "qlabel.h"
#include "qlineedit.h"
#include "qpushbutton.h"
#include <QVBoxLayout>
#include <QSerialPort>
#include <QSerialPortInfo>

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
};
#endif // MAINWINDOW_H
