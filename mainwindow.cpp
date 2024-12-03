#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "equipement.h"

#include <QMainWindow>
#include <QTableView>
#include <QComboBox>
#include <QLineEdit>
#include <QDateEdit>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QFileDialog>
#include <QTextDocument>

#include <QLabel>

#include <QPrinter>
#include <QPainter>
#include <QDebug>
#include <QStandardItemModel>
#include <QDateTime>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>
#include "QTimer"

Equipement equipement;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView_equipement->setModel(equipement.afficher());
    populateStatutComboBox();

    // Initialize Arduino and connect it
    if (arduino.connect_arduino() == 0) {
        qDebug() << "Arduino connected!";
    } else {
        qDebug() << "Failed to connect to Arduino.";
    }

    // Set up a QTimer to update the temperature every second
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateTemperature);
    timer->start(1000);  // Update every 1000 ms (1 second)

    // Set up LCDNumber (ensure your UI has a QLCDNumber widget)
    ui->lcdNumber->display(0);  // Initialize with 0 or any default value



    // Initialize the historique model
    historiqueModel = new QStandardItemModel(this);
    historiqueModel->setColumnCount(3);
    historiqueModel->setHeaderData(0, Qt::Horizontal, "Operation");
    historiqueModel->setHeaderData(1, Qt::Horizontal, "Details");
    historiqueModel->setHeaderData(2, Qt::Horizontal, "Timestamp");

    // Optionally, you can create a separate tableView for historique in your UI
    ui->tableView_historique->setModel(historiqueModel);

    connect(ui->pushButtonSend, &QPushButton::clicked, this, &MainWindow::sendEmailWithPostmark);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::populateStatutComboBox() {
    ui->comboBox_statut->addItem(" libre");
    ui->comboBox_statut->addItem("non libre ");

}

void MainWindow::on_ajouter_equi_clicked()
{
    // Récupérer les valeurs des champs de l'interface utilisateur
    QString id = ui->lineEdit_id->text(); // Nouvel identifiant saisissable
    QString nom = ui->lineEdit_nom->text();
    QString type = ui->lineEdit_type->text(); // Utiliser un QLineEdit pour le type
    QString statut = ui->comboBox_statut->currentText(); // Récupérer le statut depuis le QComboBox
    QDate date_acquisition = ui->dateEdit_date_acquisition->date(); // Assurez-vous que c'est un QDateEdit
    QString responsable = ui->lineEdit_responsable->text();

    // Vérifier si tous les champs sont remplis
    if (id.isEmpty() || nom.isEmpty() || type.isEmpty() || statut.isEmpty() || responsable.isEmpty()) {
        QMessageBox::warning(this, "Champ(s) manquant(s)", "Veuillez remplir tous les champs.");
        return;
    }

    // Vérifier la validité de l'identifiant
    if (!id.toInt() || id.toInt() <= 0) {
        QMessageBox::warning(this, "Identifiant invalide", "L'identifiant doit être un entier positif.");
        return;
    }

    // Vérifier la validité de la date
    QDate aujourdhui = QDate::currentDate();
    if (!date_acquisition.isValid() || date_acquisition < aujourdhui) {
        QMessageBox::warning(this, "Date invalide", "La date doit être valide et ne peut pas être antérieure à aujourd'hui.");
        return;
    }

    // Créer une instance de la classe Equipement avec les données récupérées
    Equipement equipement(id.toInt(), nom, type, statut, date_acquisition, responsable);

    // Appeler la méthode ajouter() pour insérer les données dans la base de données
    bool success = equipement.ajouter();

    // Afficher un message en fonction du résultat de l'opération
    if (success) {
        ui->tableView_equipement->setModel(equipement.afficher());
        QMessageBox::information(this, "Succès", "L'équipement a été ajouté avec succès.");

        // Optionnel : Effacer les champs après ajout
        ui->lineEdit_id->clear(); // Réinitialiser le champ de l'identifiant
        ui->lineEdit_nom->clear();
        ui->lineEdit_type->clear();
        ui->comboBox_statut->setCurrentIndex(-1); // Réinitialiser le QComboBox pour le statut
        ui->dateEdit_date_acquisition->setDate(QDate::currentDate());
        ui->lineEdit_responsable->clear();
    } else {
        QMessageBox::critical(this, "Erreur", "Une erreur est survenue lors de l'ajout de l'équipement.");
    }
}

void MainWindow::on_modifer_equi_clicked()
{
    QString idText = ui->lineEdit_id->text();
    if (idText.isEmpty()) {
        QMessageBox::warning(this, "Champ manquant", "Veuillez saisir l'identifiant de l'équipement.");
        return;
    }

    int id = idText.toInt();
    if (id <= 0) {
        QMessageBox::warning(this, "Identifiant invalide", "L'identifiant doit être un entier positif.");
        return;
    }

    QString nom = ui->lineEdit_nom->text();
    QString type = ui->lineEdit_type->text();
    QString statut = ui->comboBox_statut->currentText();
    QDate date_acquisition = ui->dateEdit_date_acquisition->date();
    QString responsable = ui->lineEdit_responsable->text();

    if (nom.isEmpty() || type.isEmpty() || statut.isEmpty() || responsable.isEmpty()) {
        QMessageBox::warning(this, "Champ(s) manquant(s)", "Veuillez remplir tous les champs.");
        return;
    }

    QDate aujourdhui = QDate::currentDate();
    if (!date_acquisition.isValid() || date_acquisition < aujourdhui) {
        QMessageBox::warning(this, "Date invalide", "La date doit être valide et ne peut pas être antérieure à aujourd'hui.");
        return;
    }

    Equipement equipement(id, nom, type, statut, date_acquisition, responsable);

    if (equipement.modifier(id)) {
        ui->tableView_equipement->setModel(equipement.afficher());

        // Log the modification
        QList<QStandardItem*> row;
        row.append(new QStandardItem("Modification"));
        row.append(new QStandardItem(QString("Modified equipment ID: %1").arg(id)));
        row.append(new QStandardItem(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss")));
        historiqueModel->appendRow(row);

        QMessageBox::information(this, "Succès", "L'équipement a été modifié avec succès.");
    } else {
        QMessageBox::critical(this, "Erreur", "Une erreur est survenue lors de la modification.");
    }
}




void MainWindow::on_recherche_equi_clicked()
{
    // Récupérer l'identifiant saisi par l'utilisateur
    QString idText = ui->lineEdit_recherche_id->text();

    if (idText.isEmpty()) {
        QMessageBox::warning(this, "Recherche invalide", "Veuillez entrer un identifiant.");
        return;
    }

    int id = idText.toInt();

    // Utiliser la méthode rechercherParID pour récupérer les résultats
    QSqlQueryModel* model = equipement.rechercherParID(id);

    if (model->rowCount() > 0) {
        ui->tableView_equipement->setModel(model);
    } else {
        QMessageBox::information(this, "Aucun résultat", "Aucun équipement trouvé avec cet identifiant.");
        delete model; // Supprimer le modèle si vide
    }
}


void MainWindow::on_tableView_equipement_doubleClicked(const QModelIndex &index)
{
    // Récupérer la ligne de l'élément sélectionné
    int row = index.row();

    // Extraire les données de la ligne sélectionnée pour chaque attribut de l'équipement
    int id = ui->tableView_equipement->model()->data(ui->tableView_equipement->model()->index(row, 0)).toInt();
    QString nom = ui->tableView_equipement->model()->data(ui->tableView_equipement->model()->index(row, 1)).toString();
    QString type = ui->tableView_equipement->model()->data(ui->tableView_equipement->model()->index(row, 2)).toString();
    QString statut = ui->tableView_equipement->model()->data(ui->tableView_equipement->model()->index(row, 3)).toString();
    QDate dateAcquisition = ui->tableView_equipement->model()->data(ui->tableView_equipement->model()->index(row, 4)).toDate();
    QString responsable = ui->tableView_equipement->model()->data(ui->tableView_equipement->model()->index(row, 5)).toString();

    // Mettre à jour l'interface utilisateur avec les données récupérées
    ui->lineEdit_id->setText(QString::number(id));
    ui->lineEdit_nom->setText(nom);
    ui->lineEdit_type->setText(type);
    ui->comboBox_statut->setCurrentText(statut);
    ui->dateEdit_date_acquisition->setDate(dateAcquisition);
    ui->lineEdit_responsable->setText(responsable);
}



void MainWindow::on_supp_equi_clicked()
{
    QModelIndexList selectedIndexes = ui->tableView_equipement->selectionModel()->selectedIndexes();

    if (!selectedIndexes.isEmpty()) {
        int id = selectedIndexes.at(0).sibling(selectedIndexes.at(0).row(), 0).data().toInt();

        if (equipement.supprimer(id)) {
            ui->tableView_equipement->setModel(equipement.afficher());

            // Log the deletion
            QList<QStandardItem*> row;
            row.append(new QStandardItem("Deletion"));
            row.append(new QStandardItem(QString("Deleted equipment ID: %1").arg(id)));
            row.append(new QStandardItem(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss")));
            historiqueModel->appendRow(row);

            QMessageBox::information(this, "Succès", "L'équipement a été supprimé avec succès.");
        } else {
            QMessageBox::warning(this, "Erreur", "Échec de la suppression de l'équipement.");
        }
    } else {
        QMessageBox::warning(this, "Aucune sélection", "Veuillez sélectionner un équipement à supprimer.");
    }
}



void MainWindow::on_tri_equi_clicked()
{
    static bool ordreAscendant = true;  // Variable pour alterner l'ordre de tri
    ui->tableView_equipement->setModel(equipement.trierPar(ordreAscendant));
    ordreAscendant = !ordreAscendant;  // Inverser l'ordre de tri pour le prochain clic
}



void MainWindow::on_statistique_equi_clicked() {
    // Retrieve statistics
    QMap<QString, int> statistiques = equipement.getStatistiques();
    if (statistiques.isEmpty()) {
        QMessageBox::warning(this, "Aucune donnée", "Aucune donnée disponible pour les statistiques.");
        return;
    }

    // Reference the QLabel in tab2
    QLabel *chartLabel = ui->tab_2->findChild<QLabel*>("label_statistiques");
    if (!chartLabel) {
        QMessageBox::critical(this, "Erreur", "label_statistiques introuvable dans tab_2.");
        return;
    }

    // Prepare the chart image
    QImage chartImage(chartLabel->width(), chartLabel->height(), QImage::Format_ARGB32);
    chartImage.fill(Qt::white);

    QPainter painter(&chartImage);
    painter.setRenderHint(QPainter::Antialiasing);

    // Chart dimensions
    int barWidth = 50;
    int spacing = 20;
    int originX = 50;
    int originY = chartLabel->height() - 50; // Leave space for labels
    int chartHeight = chartLabel->height() - 100;

    // Draw axes
    painter.setPen(Qt::black);
    painter.drawLine(originX, originY, originX + (statistiques.size() * (barWidth + spacing)), originY); // X-axis
    painter.drawLine(originX, originY, originX, originY - chartHeight); // Y-axis

    // Draw bars
    int x = originX + spacing / 2;
    foreach (QString statut, statistiques.keys()) {
        int barHeight = static_cast<int>((static_cast<double>(statistiques[statut]) / 10) * chartHeight); // Adjust normalization

        // Draw bar
        painter.setBrush(Qt::blue);
        painter.drawRect(x, originY - barHeight, barWidth, barHeight);

        // Draw labels
        painter.setPen(Qt::black);
        painter.drawText(x, originY + 15, barWidth, 20, Qt::AlignCenter, statut);
        painter.drawText(x, originY - barHeight - 20, barWidth, 20, Qt::AlignCenter, QString::number(statistiques[statut]));

        x += barWidth + spacing;
    }

    painter.end();

    // Display the chart in the QLabel
    chartLabel->setPixmap(QPixmap::fromImage(chartImage));

    // Switch to tab_2
    ui->tabWidget->setCurrentWidget(ui->tab_2);
}



void MainWindow::on_export_pdf_clicked()
{
    // Ouvre un dialogue pour choisir le fichier de sortie PDF
    QString filename = QFileDialog::getSaveFileName(this, "Exporter la liste des clients au format PDF", "", "*.pdf");
    if (filename.isEmpty()) return;

    // Configurer le QPrinter pour la sortie en PDF
    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(filename);

    // Création du document texte pour générer le PDF
    QTextDocument doc;
    QString text;

    // Récupère le modèle de données du QTableView
    QAbstractItemModel *model = ui->tableView_equipement->model();
    if (!model) {
        QMessageBox::warning(this, "Exportation PDF", "Aucun modèle de données trouvé dans la table !");
        return;
    }

    // Construire le texte à partir des données du modèle
    text.append("<table border='1' cellspacing='0' cellpadding='3'>");
    text.append("<tr>");

    // En-têtes de colonnes
    for (int col = 0; col < model->columnCount(); ++col) {
        text.append("<th>").append(model->headerData(col, Qt::Horizontal).toString()).append("</th>");
    }
    text.append("</tr>");

    // Données des lignes
    for (int row = 0; row < model->rowCount(); ++row) {
        text.append("<tr>");
        for (int col = 0; col < model->columnCount(); ++col) {
            text.append("<td>").append(model->data(model->index(row, col)).toString()).append("</td>");
        }
        text.append("</tr>");
    }
    text.append("</table>");

    doc.setHtml(text);

    // Imprimer le document sur le QPrinter configuré
    doc.print(&printer);

    // Message de confirmation
    QMessageBox::information(this, "Exportation PDF", "La liste des clients a été exportée avec succès en PDF !");
}



void MainWindow::on_historique_clicked()
{
    ui->tabWidget->setCurrentWidget(ui->tableView_historique); // Assuming historique is in a tab
}

//mail
void MainWindow::sendEmailWithPostmark() {
    // Récupérer les informations saisies par l'utilisateur
    QString recipient = ui->lineEditRecipient->text(); // Email du destinataire

    if (recipient.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez saisir l'adresse email du destinataire.");
        return;
    }

    // Initialiser le manager réseau
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    // Préparer la requête HTTP vers l'API Postmark
    QNetworkRequest request(QUrl("https://api.postmarkapp.com/email"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("X-Postmark-Server-Token", "f5260d25-b23a-4c52-9671-c28cd9db2915"); // Votre token API

    // Construire le contenu de l'email
    QJsonObject emailObject;
    emailObject["From"] = "mohamedaziz.slouma@esprit.tn"; // Adresse email expéditeur (vérifiée dans Postmark)
    emailObject["To"] = recipient; // Adresse email du destinataire
    emailObject["Subject"] = "Email de test depuis Qt et Postmark"; // Sujet de l'email
    emailObject["TextBody"] = "Bonjour,\nCeci est un test envoyé avec Qt et Postmark."; // Contenu texte de l'email

    QJsonDocument emailDoc(emailObject);

    // Envoyer la requête POST
    QNetworkReply *reply = manager->post(request, emailDoc.toJson());

    // Gérer la réponse de l'API
    connect(reply, &QNetworkReply::finished, this, [reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            QMessageBox::information(nullptr, "Succès", "Email envoyé avec succès !");
        } else {
            QMessageBox::critical(nullptr, "Erreur", "Échec de l'envoi de l'email : " + reply->errorString());
        }
        reply->deleteLater();
    });
}

void MainWindow::on_pushButtonSend_clicked()
{
    // Appeler la fonction pour envoyer l'email
    sendEmailWithPostmark();
}


void MainWindow::updateTemperatureInDatabase(float temperature)
{
    // Ensure the database is connected and open
    QSqlDatabase db = QSqlDatabase::database(); // Assuming the default connection
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return;
    }

    QSqlQuery query;

    // Prepare the SQL query to update the temperature in the database
    query.prepare("UPDATE LOCAUX SET TEMPERATURE = :temp WHERE ID = 1"); // Adjust WHERE clause as necessary
    query.bindValue(":temp", temperature);

    // Execute the query
    if (!query.exec()) {
        qDebug() << "Failed to update database: " << query.lastError().text();
    } else {
        qDebug() << "Temperature updated in database!";
    }
}







void MainWindow::updateTemperature()
{
    QByteArray data = arduino.read_from_arduino();  // Read data from Arduino

    if (!data.isEmpty()) {
        // Convert QByteArray to QString and trim unnecessary characters
        QString dataString = QString::fromUtf8(data).trimmed();  // Using UTF-8 conversion and trimming extra spaces/newlines

        // Debug: Print raw data received
        qDebug() << "Data received from Arduino:" << dataString;

        // Handle cases where multiple values are received (like "Temperature: 26.70\r\n26.70\r\n")
        QStringList lines = dataString.split("\r\n");  // Split by carriage return + newline
        foreach (const QString &line, lines) {
            if (line.startsWith("Temperature: ")) {
                // Extract the temperature value from the line (after "Temperature: ")
                QString tempString = line.mid(13);  // Extract substring after "Temperature: "

                bool ok;
                float temperature = tempString.toFloat(&ok);  // Try to convert the extracted substring to float

                if (ok) {
                    // If conversion is successful, display temperature on the LCD
                    ui->lcdNumber->display(temperature);

                    // Now update the temperature column in the database
                    updateTemperatureInDatabase(temperature);
                } else {
                    qDebug() << "Failed to parse temperature data.";
                }
            }
        }
    } else {
        qDebug() << "No data received from Arduino.";
    }
}



