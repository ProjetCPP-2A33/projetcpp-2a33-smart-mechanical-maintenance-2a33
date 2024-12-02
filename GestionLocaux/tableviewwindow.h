#ifndef TABLEVIEWWINDOW_H
#define TABLEVIEWWINDOW_H
#include <QSqlQueryModel>
#include <QDialog>
#include <QSortFilterProxyModel>

namespace Ui {
class TableViewWindow;
}

class TableViewWindow : public QDialog {
    Q_OBJECT

public:
    explicit TableViewWindow(QWidget *parent = nullptr);
    ~TableViewWindow();

    void setModel(QSqlQueryModel *model);
      void exporterPDF();
      void on_gLpushbutton_exporterPDF_clicked();


private slots:
    void on_gLpushButton_sort_clicked();

    // Nouveau slot pour tri par ID

private:
    Ui::TableViewWindow *ui;
    QSortFilterProxyModel *proxyModel; // Modèle pour tri
};

#endif // TABLEVIEWWINDOW_H
