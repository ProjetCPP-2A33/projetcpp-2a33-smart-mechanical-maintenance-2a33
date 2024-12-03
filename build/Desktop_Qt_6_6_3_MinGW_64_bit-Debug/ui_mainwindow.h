/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    QLabel *label;
    QLineEdit *lineEdit_id;
    QLineEdit *lineEdit_nom;
    QLineEdit *lineEdit_type;
    QLineEdit *lineEdit_responsable;
    QComboBox *comboBox_statut;
    QDateEdit *dateEdit_date_acquisition;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QPushButton *ajouter_equi;
    QPushButton *modifer_equi;
    QTableView *tableView_equipement;
    QLineEdit *lineEdit_recherche_id;
    QPushButton *recherche_equi;
    QPushButton *statistique_equi;
    QPushButton *tri_equi;
    QPushButton *export_pdf;
    QPushButton *supp_equi;
    QPushButton *historique;
    QWidget *tab_2;
    QLabel *label_statistiques;
    QWidget *tab_3;
    QWidget *tab_4;
    QTableView *tableView_historique;
    QWidget *tab_5;
    QLabel *label_8;
    QLineEdit *lineEditRecipient;
    QLineEdit *lineEditSubject;
    QTextEdit *textEditMessage;
    QPushButton *pushButtonSend;
    QWidget *tab_6;
    QLCDNumber *lcdNumber;
    QLabel *label_9;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1550, 821);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(0, 0, 1391, 741));
        tabWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(136, 159, 214);"));
        tabWidget->setIconSize(QSize(5, 5));
        tab = new QWidget();
        tab->setObjectName("tab");
        label = new QLabel(tab);
        label->setObjectName("label");
        label->setGeometry(QRect(50, 20, 511, 81));
        lineEdit_id = new QLineEdit(tab);
        lineEdit_id->setObjectName("lineEdit_id");
        lineEdit_id->setGeometry(QRect(200, 130, 251, 61));
        lineEdit_id->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        lineEdit_nom = new QLineEdit(tab);
        lineEdit_nom->setObjectName("lineEdit_nom");
        lineEdit_nom->setGeometry(QRect(200, 220, 251, 61));
        lineEdit_nom->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        lineEdit_type = new QLineEdit(tab);
        lineEdit_type->setObjectName("lineEdit_type");
        lineEdit_type->setGeometry(QRect(200, 300, 251, 61));
        lineEdit_type->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        lineEdit_responsable = new QLineEdit(tab);
        lineEdit_responsable->setObjectName("lineEdit_responsable");
        lineEdit_responsable->setGeometry(QRect(200, 560, 251, 61));
        lineEdit_responsable->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        comboBox_statut = new QComboBox(tab);
        comboBox_statut->setObjectName("comboBox_statut");
        comboBox_statut->setGeometry(QRect(200, 380, 251, 71));
        comboBox_statut->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        dateEdit_date_acquisition = new QDateEdit(tab);
        dateEdit_date_acquisition->setObjectName("dateEdit_date_acquisition");
        dateEdit_date_acquisition->setGeometry(QRect(200, 470, 251, 71));
        dateEdit_date_acquisition->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_2 = new QLabel(tab);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 130, 171, 51));
        label_3 = new QLabel(tab);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 230, 171, 51));
        label_4 = new QLabel(tab);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(20, 310, 171, 51));
        label_5 = new QLabel(tab);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 390, 171, 51));
        label_6 = new QLabel(tab);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 480, 171, 51));
        label_7 = new QLabel(tab);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(0, 570, 181, 51));
        ajouter_equi = new QPushButton(tab);
        ajouter_equi->setObjectName("ajouter_equi");
        ajouter_equi->setGeometry(QRect(330, 640, 141, 51));
        modifer_equi = new QPushButton(tab);
        modifer_equi->setObjectName("modifer_equi");
        modifer_equi->setGeometry(QRect(180, 640, 131, 51));
        tableView_equipement = new QTableView(tab);
        tableView_equipement->setObjectName("tableView_equipement");
        tableView_equipement->setGeometry(QRect(520, 140, 551, 331));
        tableView_equipement->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        lineEdit_recherche_id = new QLineEdit(tab);
        lineEdit_recherche_id->setObjectName("lineEdit_recherche_id");
        lineEdit_recherche_id->setGeometry(QRect(660, 30, 271, 41));
        lineEdit_recherche_id->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        recherche_equi = new QPushButton(tab);
        recherche_equi->setObjectName("recherche_equi");
        recherche_equi->setGeometry(QRect(960, 30, 131, 41));
        statistique_equi = new QPushButton(tab);
        statistique_equi->setObjectName("statistique_equi");
        statistique_equi->setGeometry(QRect(730, 550, 131, 61));
        tri_equi = new QPushButton(tab);
        tri_equi->setObjectName("tri_equi");
        tri_equi->setGeometry(QRect(890, 550, 131, 61));
        export_pdf = new QPushButton(tab);
        export_pdf->setObjectName("export_pdf");
        export_pdf->setGeometry(QRect(1040, 550, 151, 51));
        supp_equi = new QPushButton(tab);
        supp_equi->setObjectName("supp_equi");
        supp_equi->setGeometry(QRect(570, 550, 131, 61));
        historique = new QPushButton(tab);
        historique->setObjectName("historique");
        historique->setGeometry(QRect(700, 640, 191, 51));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        label_statistiques = new QLabel(tab_2);
        label_statistiques->setObjectName("label_statistiques");
        label_statistiques->setGeometry(QRect(220, 60, 761, 501));
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName("tab_3");
        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName("tab_4");
        tableView_historique = new QTableView(tab_4);
        tableView_historique->setObjectName("tableView_historique");
        tableView_historique->setGeometry(QRect(440, 20, 531, 361));
        tableView_historique->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        tabWidget->addTab(tab_4, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName("tab_5");
        label_8 = new QLabel(tab_5);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(210, 80, 211, 61));
        lineEditRecipient = new QLineEdit(tab_5);
        lineEditRecipient->setObjectName("lineEditRecipient");
        lineEditRecipient->setGeometry(QRect(480, 100, 231, 51));
        lineEditRecipient->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        lineEditSubject = new QLineEdit(tab_5);
        lineEditSubject->setObjectName("lineEditSubject");
        lineEditSubject->setGeometry(QRect(390, 200, 441, 101));
        lineEditSubject->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        textEditMessage = new QTextEdit(tab_5);
        textEditMessage->setObjectName("textEditMessage");
        textEditMessage->setGeometry(QRect(300, 310, 631, 231));
        textEditMessage->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        pushButtonSend = new QPushButton(tab_5);
        pushButtonSend->setObjectName("pushButtonSend");
        pushButtonSend->setGeometry(QRect(530, 590, 161, 51));
        tabWidget->addTab(tab_5, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName("tab_6");
        lcdNumber = new QLCDNumber(tab_6);
        lcdNumber->setObjectName("lcdNumber");
        lcdNumber->setGeometry(QRect(550, 160, 311, 171));
        label_9 = new QLabel(tab_6);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(60, 200, 421, 71));
        label_9->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        tabWidget->addTab(tab_6, QString());
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1550, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(5);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:22pt; font-weight:700; font-style:italic;\">GESTION DES EQUIPEMENTS</span></p></body></html>", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:16pt; font-weight:700;\">IDENTIFIANT</span></p></body></html>", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:16pt; font-weight:700;\">NOM</span></p></body></html>", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:16pt; font-weight:700;\">TYPE</span></p></body></html>", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:16pt; font-weight:700;\">STATUS</span></p></body></html>", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:16pt; font-weight:700;\">DATE</span></p></body></html>", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:16pt; font-weight:700;\">RESPONSABLE</span></p></body></html>", nullptr));
        ajouter_equi->setText(QCoreApplication::translate("MainWindow", "AJOUTER", nullptr));
        modifer_equi->setText(QCoreApplication::translate("MainWindow", "MODIFIER", nullptr));
        recherche_equi->setText(QCoreApplication::translate("MainWindow", "RECHERCHE", nullptr));
        statistique_equi->setText(QCoreApplication::translate("MainWindow", "STATISTIQUE", nullptr));
        tri_equi->setText(QCoreApplication::translate("MainWindow", "TRI", nullptr));
        export_pdf->setText(QCoreApplication::translate("MainWindow", "EXPORT", nullptr));
        supp_equi->setText(QCoreApplication::translate("MainWindow", "SUPPRIMER", nullptr));
        historique->setText(QCoreApplication::translate("MainWindow", "HISTORIQUE", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "Equipement", nullptr));
        label_statistiques->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "Statistique", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("MainWindow", "page", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QCoreApplication::translate("MainWindow", "Historique", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:11pt; font-weight:700;\">mailling</span></p></body></html>", nullptr));
        pushButtonSend->setText(QCoreApplication::translate("MainWindow", "SEND", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QCoreApplication::translate("MainWindow", "Mailling", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:18pt; font-weight:700;\">TEMPERATURE DU LOCAL :</span></p></body></html>", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_6), QCoreApplication::translate("MainWindow", "arduino", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
