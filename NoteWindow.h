/*CREATE NOTE TABLE !!!!
CREATE TABLE Note (
    id_local INTEGER,
    contenu CLOB, -- Utilisation de CLOB pour les longs textes
    CONSTRAINT fk_local FOREIGN KEY (id_local) REFERENCES Local(ID_local) ON DELETE CASCADE
);

*/
#ifndef NOTEWINDOW_H
#define NOTEWINDOW_H

#include <QDialog>
#include <QSqlQuery>
#include <QTimer>  // Include QTimer header

namespace Ui {
class NoteWindow;
}

class NoteWindow : public QDialog
{
    Q_OBJECT

public:
    explicit NoteWindow(QWidget *parent = nullptr);
    ~NoteWindow();

private slots:
    void on_pushButton_save_clicked();
    void on_pushButton_load_clicked();
    void loadIds();

private:
    Ui::NoteWindow *ui;
    QTimer *timer;  // Add a QTimer member
};

#endif // NOTEWINDOW_H
