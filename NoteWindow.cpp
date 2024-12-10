#include "notewindow.h"
#include "ui_notewindow.h"
#include <QMessageBox>
#include <QSqlError>
#include <QDebug>
#include <QSqlQuery>// Include QDebug for detailed debug messages

NoteWindow::NoteWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NoteWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Note Management");
    loadIds();
      ui->textEdit_note->setPlainText("Type here...");


    // Initialize and start the timer

}

NoteWindow::~NoteWindow()
{
    delete ui;
    delete timer;
}

void NoteWindow::loadIds()
{



    ui->comboBox_idLocal->clear();


    // Prepare and execute the SQL query to retrieve the IDs from the Local table
    QSqlQuery query("SELECT ID_local FROM Local");



    // Add the results to the comboBox
    while (query.next()) {
        int idLocal = query.value(0).toInt();
        ui->comboBox_idLocal->addItem(QString::number(idLocal));
        qDebug() << "ID ajouté à la comboBox: " << idLocal;

}}

void NoteWindow::on_pushButton_save_clicked()
{
    int idLocal = ui->comboBox_idLocal->currentText().toInt();
    QString note = ui->textEdit_note->toPlainText();

    QSqlQuery query;
    QString sql = "MERGE INTO Notes n "
                  "USING (SELECT :ID_local AS ID_local, :note AS note FROM dual) vals "
                  "ON (n.ID_local = vals.ID_local) "
                  "WHEN MATCHED THEN "
                  "  UPDATE SET n.note = vals.note "
                  "WHEN NOT MATCHED THEN "
                  "  INSERT (ID_local, note) "
                  "  VALUES (vals.ID_local, vals.note)";

    query.prepare(sql);
    query.bindValue(":ID_local", idLocal);
    query.bindValue(":note", note);

    qDebug() << "Executing SQL:" << query.executedQuery();

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur", "Échec de la sauvegarde de la note : " + query.lastError().text());
        qDebug() << "Erreur lors de la sauvegarde de la note: " << query.lastError().text();
    } else {
        QMessageBox::information(this, "Succès", "Note sauvegardée avec succès !");
        qDebug() << "Note sauvegardée avec succès pour l'ID_local: " << idLocal;
    }
}


void NoteWindow::on_pushButton_load_clicked()
{
    int idLocal = ui->comboBox_idLocal->currentText().toInt();

    QSqlQuery query;
    query.prepare("SELECT note FROM Notes WHERE ID_local = :ID_local");
    query.bindValue(":ID_local", idLocal);

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur", "Échec du chargement de la note : " + query.lastError().text());
        qDebug() << "Erreur lors du chargement de la note: " << query.lastError().text();
        return;
    }

    if (query.next()) {
        QString note = query.value(0).toString();
        ui->textEdit_note->setText(note);
        qDebug() << "Note chargée pour l'ID_local: " << idLocal;
    } else {
        QMessageBox::warning(this, "Aucune note trouvée", "Aucune note trouvée pour cet ID.");
        qDebug() << "Aucune note trouvée pour l'ID_local: " << idLocal;
    }
}
