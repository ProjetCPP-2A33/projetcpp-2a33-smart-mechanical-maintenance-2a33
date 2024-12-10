#ifndef MAINWINDOWGESTIONEMPLOYER_H
#define MAINWINDOWGESTIONEMPLOYER_H
#include <QMainWindow>
#include "employer.h"
#include "qlineedit.h"
#include "qpushbutton.h"
#include <QVBoxLayout>
#include <QSerialPort>
#include <QSerialPortInfo>
#include "gestionL.h"
#include <QStandardItem>

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
    void showFacturePage();
    void showClientPage();
    void on_pb_select_clicked();
    void onEquipementClicked();
    void openGestionL();
    void on_ajouter_f_clicked();
    void populateStatutComboBox();
    void populateClientComboBox();
    void gotofacture();
    void on_modfi_f_clicked();

    void on_tableView_factures_doubleClicked(const QModelIndex &index);

    void on_supp_f_clicked();

    void on_lineEdit_search_textChanged( QString text);

    void on_dateEdit_recherche_dateChanged(const QDate &date);

    void on_tri_clicked();
    void PDFfacture( QString filePath);

    void on_pdf_facture_clicked();
    void displayStatutFactures();
    void sendInvoiceStatusSMS();
    void sendSMS(const QString &numTel, const QString &message);
    void onVehiculeClicked();;

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
    GestionL *gestionLWindow; // Declare this variable here
    QStandardItemModel *historyModel;

};
#endif // MAINWINDOWGESTIONEMPLOYER_H
