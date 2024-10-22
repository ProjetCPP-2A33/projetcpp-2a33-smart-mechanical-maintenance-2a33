#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Slot to handle adding a new client
    void on_addButton_clicked();

    // Slot to handle removing a client
    void on_removeButton_clicked();

private:
    Ui::MainWindow *ui;

    // Function to load client data from the database
    void loadClientData();
};

#endif // MAINWINDOW_H
