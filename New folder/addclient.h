#ifndef ADDCLIENT_H
#define ADDCLIENT_H

#include <QDialog>

namespace Ui {
class AddClient;
}

class AddClient : public QDialog
{
    Q_OBJECT

public:
    explicit AddClient(QWidget *parent = nullptr);
    ~AddClient();

    // Methods to get data from the dialog inputs
    QString getNumCin() const;
    QString getNomComplet() const;
    QString getAdresse() const;
    QString getAdresseMail() const;
    QString getTypeClient() const;
    double getRemise() const;
    QString getRessourceAssocie() const;

    // Function to add client to the database
    bool addClientToDatabase();

private:
    Ui::AddClient *ui;
};

#endif // ADDCLIENT_H
