#include "tableviewwindow.h"
#include "ui_tableviewwindow.h"
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QFileDialog>
#include <QPdfWriter>
#include <QPainter>




TableViewWindow::TableViewWindow(QWidget *parent)
    : QDialog(parent), ui(new Ui::TableViewWindow), proxyModel(nullptr) {
    ui->setupUi(this);

    proxyModel = new QSortFilterProxyModel(this);
    connect(ui->gLpushbutton_exporterPDF, &QPushButton::clicked, this, &TableViewWindow::on_gLpushbutton_exporterPDF_clicked);
}

TableViewWindow::~TableViewWindow() {
    delete ui;
    delete proxyModel;
}

void TableViewWindow::setModel(QSqlQueryModel *model) {
    proxyModel->setSourceModel(model); // Connecter le proxy au modèle source
    ui->gLtableView->setModel(proxyModel); // Associer au QTableView
    ui->gLtableView->setSortingEnabled(false); // Désactiver le tri par défaut
}

// Slot pour gérer le tri par ID_local
void TableViewWindow::on_gLpushButton_sort_clicked() {
    if (!proxyModel) return;

    int columnIndex = 0; // Colonne ID_local
    Qt::SortOrder sortOrder = Qt::AscendingOrder; // Tri croissant

    // Appliquer le tri
    proxyModel->sort(columnIndex, sortOrder);

    QMessageBox::information(this, "Tri", "Table triée par ID (ordre croissant).");
}

void TableViewWindow::exporterPDF() {
    qDebug() << "Exporting to PDF...";

    // Récupère le modèle de données
    QAbstractItemModel *model = ui->gLtableView->model();
    if (!model) {
        qDebug() << "Model is invalid!";
        return;
    }

    // Demande à l'utilisateur où enregistrer le fichier PDF
    QString fileName = QFileDialog::getSaveFileName(this, "Enregistrer le fichier PDF", "", "Fichiers PDF (*.pdf)");
    if (fileName.isEmpty()) {
        qDebug() << "No file selected.";
        return;
    }

    // Configuration de l'écriture dans le fichier PDF
    QPdfWriter writer(fileName);
    writer.setPageSize(QPageSize(QPageSize::A4));
    writer.setPageOrientation(QPageLayout::Portrait);
    writer.setResolution(400);

    // Création du pinceau pour dessiner sur le PDF
    QPainter painter(&writer);
    if (!painter.isActive()) {
        qDebug() << "Error initializing painter!";
        return;
    }

    qDebug() << "Starting to write data to PDF.";

    // Dessiner les en-têtes des colonnes
    int xOffset = 50, yOffset = 50, lineHeight = 100, colWidth = 400;
    int currentY = yOffset;

    for (int col = 0; col < model->columnCount(); ++col) {
        QString header = model->headerData(col, Qt::Horizontal).toString();
        QRect headerRect(xOffset + col * colWidth, currentY, colWidth, lineHeight);
        painter.drawText(headerRect, Qt::AlignCenter, header);
        painter.drawRect(headerRect); // Bordure autour de l'en-tête
    }

    currentY += lineHeight; // Passe à la ligne suivante après les en-têtes

    // Dessiner les données des cellules
    for (int row = 0; row < model->rowCount(); ++row) {
        for (int col = 0; col < model->columnCount(); ++col) {
            QString cellData = model->data(model->index(row, col)).toString();
            QRect cellRect(xOffset + col * colWidth, currentY, colWidth, lineHeight);
            painter.drawText(cellRect, Qt::AlignCenter, cellData);
            painter.drawRect(cellRect); // Bordure autour de la cellule
        }
        currentY += lineHeight;

        // Si le contenu dépasse la page, créer une nouvelle page
        if (currentY > writer.height() - yOffset) {
            writer.newPage();
            currentY = yOffset;
            for (int col = 0; col < model->columnCount(); ++col) {
                QString header = model->headerData(col, Qt::Horizontal).toString();
                QRect headerRect(xOffset + col * colWidth, currentY, colWidth, lineHeight);
                painter.drawText(headerRect, Qt::AlignCenter, header);
                painter.drawRect(headerRect); // Bordure autour de l'en-tête
            }
            currentY += lineHeight; // Déplacer après les en-têtes sur la nouvelle page
        }
    }

    painter.end();
    qDebug() << "PDF export completed.";
    QMessageBox::information(this, "Succès", "Les données ont été exportées en PDF.");
}

void TableViewWindow::on_gLpushbutton_exporterPDF_clicked() {
    // Vérification que la table contient un modèle valide
    QAbstractItemModel *model = ui->gLtableView->model();
    if (!model) {
        QMessageBox::warning(this, "Erreur", "Aucune donnée disponible pour l'exportation.");
        return;
    }

    // Si un modèle est trouvé, on appelle la méthode d'exportation en PDF
    exporterPDF();  // Appel de la méthode d'exportation en PDF
}
