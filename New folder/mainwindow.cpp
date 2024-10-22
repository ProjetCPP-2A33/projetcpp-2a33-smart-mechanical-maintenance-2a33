#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addclient.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>

// Constructor
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug() << "Available database drivers: " << QSqlDatabase::drivers();

    // Load clients into the table view on startup
    loadClientData();

    // Connect Add and Remove buttons to their respective slots
    connect(ui->addButton, &QPushButton::clicked, this, &MainWindow::on_addButton_clicked);
    connect(ui->removeButton, &QPushButton::clicked, this, &MainWindow::on_removeButton_clicked);
}

// Destructor
MainWindow::~MainWindow()
{
    delete ui;
}

// Function to load client data from the database
void MainWindow::loadClientData()
{
    // Create a new QSqlQueryModel
    QSqlQueryModel *model = new QSqlQueryModel(this);

    // Set the SQL query to fetch client data
    model->setQuery("SELECT NUM_CIN, NOM_COMPLET, ADRESSE, ADRESSE_MAIL, TYPE_CLIENT, REMISE, RESSOURCE_ASSOSIE FROM CLIENT");

    // Check if there was an error in the query
    if (model->lastError().isValid()) {
        qDebug() << "Error loading data from database: " << model->lastError().text();
        return;
    }

    // Set the model to the QTableView to display the data
    ui->tableView->setModel(model);

    // Resize the columns to fit the data
    ui->tableView->resizeColumnsToContents();
}

// Slot to open the AddClientDialog when the Add button is clicked
void MainWindow::on_addButton_clicked()
{
    // Create and open the AddClientDialog
    AddClient addClientDialog(this);

    if (addClientDialog.exec() == QDialog::Accepted) {
        // If dialog was accepted, add the client to the database
        addClientDialog.addClientToDatabase();

        // Reload the client data to show the new entry
        loadClientData();
    }
}

// Slot to handle removing a client
void MainWindow::on_removeButton_clicked()
{
    // Get the selected row from the table
    QModelIndexList selectedRows = ui->tableView->selectionModel()->selectedRows();

    if (selectedRows.size() > 0) {
        int row = selectedRows[0].row();
        QString numCin = ui->tableView->model()->index(row, 0).data().toString();  // Get the NUM_CIN of the selected client

        // Create an SQL query to remove the selected client by NUM_CIN
        QSqlQuery query;
        query.prepare("DELETE FROM CLIENT WHERE NUM_CIN = :numCin");
        query.bindValue(":numCin", numCin);

        // Execute the query and check if it was successful
        if (query.exec()) {
            QMessageBox::information(this, "Success", "Client removed successfully.");
            loadClientData();  // Reload the client data after removing
        } else {
            QMessageBox::warning(this, "Error", "Failed to remove client: " + query.lastError().text());
        }
    } else {
        QMessageBox::warning(this, "Error", "No client selected for removal.");
    }
}
