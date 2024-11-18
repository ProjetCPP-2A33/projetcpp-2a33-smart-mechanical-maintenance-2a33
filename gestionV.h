#ifndef GESTIONV_H
#define GESTIONV_H

#include <QMainWindow>
#include <QChartView>
#include "vehicules.h"
#include <QPushButton>
#include <QStandardItemModel>
#include <QStyledItemDelegate>
#include <QPainter>
#include <QTableView>
#include <QSqlTableModel>  // Assurez-vous d'inclure QSqlTableModel

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_ajouter_clicked();
    //void afficher();  // Fonction pour afficher les véhicules (utilisation de model)
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

private:
    Ui::MainWindow *ui;

    Vehicules V;
    QSqlTableModel *model;  // Déclaration du modèle pour QTableView
    QChartView *chartView = nullptr;  // Pour afficher les graphiques
    QStandardItemModel *conversationModel;  // Modèle pour afficher les messages de chatbot

};

#endif // GESTIONV_H
