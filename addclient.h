#ifndef ADDCLIENT_H
#define ADDCLIENT_H

#include <QDialog>
#include <QString>

namespace Ui {
class AddClient;
}

class AddClient : public QDialog
{
    Q_OBJECT

public:
    explicit AddClient(QWidget *parent = nullptr);
    ~AddClient();

    QString getNumCin() const;
    QString getNomComplet() const;
    QString getAdresse() const;
    QString getAdresseMail() const;
    QString getTypeClient() const;
    double getRemise() const;
    QString getRessourceAssocie() const;
    QString getImagePath() const;  // Getter for imagePath

    bool addClientToDatabase();
    bool updateClientToDatabase();

private slots:
    void onUploadImageClicked();  // Slot for image upload

private:
    Ui::AddClient *ui;
    QString imagePath;  // Store the image path
};

#endif // ADDCLIENT_H
