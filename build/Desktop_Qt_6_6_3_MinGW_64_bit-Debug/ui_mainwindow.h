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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    QLabel *label;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_2;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_68;
    QLabel *label_74;
    QLabel *label_73;
    QLabel *label_75;
    QLabel *label_76;
    QPushButton *ajouterButton;
    QLabel *label_71;
    QPushButton *trier;
    QPushButton *supprimerButton;
    QPushButton *miseajourButton;
    QLineEdit *l1;
    QLabel *label_8;
    QLineEdit *l3;
    QLineEdit *l6;
    QLabel *label_10;
    QLabel *label_19;
    QLineEdit *l7;
    QLabel *label_20;
    QLabel *label_21;
    QLineEdit *l2;
    QLabel *label_22;
    QLineEdit *l4;
    QLabel *label_23;
    QLineEdit *l5;
    QPushButton *afficherButton;
    QPushButton *PDF;
    QLabel *label_9;
    QTableView *tableView_employes;
    QPushButton *Rechrche;
    QLabel *label_24;
    QLineEdit *l11;
    QPushButton *statistique;
    QPushButton *notification;
    QWidget *tab_2;
    QLabel *label_14;
    QLabel *label_15;
    QLabel *label_16;
    QLabel *label_17;
    QLabel *label_35;
    QLabel *label_36;
    QLabel *label_37;
    QLabel *label_38;
    QLabel *label_39;
    QLabel *label_40;
    QLabel *label_64;
    QLabel *label_65;
    QLabel *label_66;
    QLabel *label_67;
    QLabel *label_77;
    QLabel *label_78;
    QLabel *label_80;
    QLabel *label_82;
    QLabel *label_81;
    QLabel *label_86;
    QLabel *label_85;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *verticlLayout;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1171, 711);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(0, 0, 1061, 651));
        tab = new QWidget();
        tab->setObjectName("tab");
        label = new QLabel(tab);
        label->setObjectName("label");
        label->setGeometry(QRect(-30, 10, 1211, 621));
        label->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_3 = new QLabel(tab);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(150, 0, 901, 71));
        label_3->setStyleSheet(QString::fromUtf8("background-color: rgb(136, 159, 214);"));
        label_4 = new QLabel(tab);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(0, 70, 131, 541));
        label_4->setStyleSheet(QString::fromUtf8("background-color: rgb(136, 159, 214);"));
        label_2 = new QLabel(tab);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(0, 0, 151, 71));
        label_2->setPixmap(QPixmap(QString::fromUtf8("../../Bureau/logo inter.png")));
        label_2->setScaledContents(true);
        label_5 = new QLabel(tab);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 80, 121, 41));
        label_6 = new QLabel(tab);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 120, 111, 41));
        label_7 = new QLabel(tab);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(10, 170, 101, 31));
        label_7->setStyleSheet(QString::fromUtf8("background-color: rgb(147, 154, 255);"));
        label_11 = new QLabel(tab);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(10, 320, 101, 41));
        label_12 = new QLabel(tab);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(10, 360, 63, 31));
        label_13 = new QLabel(tab);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(10, 400, 111, 31));
        label_68 = new QLabel(tab);
        label_68->setObjectName("label_68");
        label_68->setGeometry(QRect(10, 580, 121, 20));
        label_74 = new QLabel(tab);
        label_74->setObjectName("label_74");
        label_74->setGeometry(QRect(950, 10, 81, 61));
        label_74->setPixmap(QPixmap(QString::fromUtf8("../../Bureau/15.png")));
        label_74->setScaledContents(true);
        label_73 = new QLabel(tab);
        label_73->setObjectName("label_73");
        label_73->setGeometry(QRect(910, 10, 51, 51));
        label_73->setPixmap(QPixmap(QString::fromUtf8("../../Bureau/6086198-icone-de-notification-pour-le-web-vectoriel.png")));
        label_73->setScaledContents(true);
        label_75 = new QLabel(tab);
        label_75->setObjectName("label_75");
        label_75->setGeometry(QRect(940, 150, 91, 41));
        label_75->setPixmap(QPixmap(QString::fromUtf8("../../Bureau/icone.webp")));
        label_75->setScaledContents(true);
        label_76 = new QLabel(tab);
        label_76->setObjectName("label_76");
        label_76->setGeometry(QRect(150, 220, 861, 351));
        label_76->setStyleSheet(QString::fromUtf8("background-color: rgb(136, 159, 214);"));
        ajouterButton = new QPushButton(tab);
        ajouterButton->setObjectName("ajouterButton");
        ajouterButton->setGeometry(QRect(910, 540, 93, 29));
        ajouterButton->setStyleSheet(QString::fromUtf8("\n"
"background-color: rgb(255, 255, 255);"));
        label_71 = new QLabel(tab);
        label_71->setObjectName("label_71");
        label_71->setGeometry(QRect(150, 180, 31, 20));
        label_71->setPixmap(QPixmap(QString::fromUtf8("../../Bureau/25321.png")));
        label_71->setScaledContents(true);
        trier = new QPushButton(tab);
        trier->setObjectName("trier");
        trier->setGeometry(QRect(190, 180, 93, 29));
        trier->setStyleSheet(QString::fromUtf8("background-color: rgb(147, 154, 255);"));
        supprimerButton = new QPushButton(tab);
        supprimerButton->setObjectName("supprimerButton");
        supprimerButton->setGeometry(QRect(10, 210, 93, 29));
        supprimerButton->setStyleSheet(QString::fromUtf8("background-color: rgb(252, 252, 252);"));
        miseajourButton = new QPushButton(tab);
        miseajourButton->setObjectName("miseajourButton");
        miseajourButton->setGeometry(QRect(10, 260, 93, 29));
        l1 = new QLineEdit(tab);
        l1->setObjectName("l1");
        l1->setGeometry(QRect(270, 230, 113, 26));
        label_8 = new QLabel(tab);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(150, 230, 91, 20));
        l3 = new QLineEdit(tab);
        l3->setObjectName("l3");
        l3->setGeometry(QRect(270, 280, 113, 26));
        l6 = new QLineEdit(tab);
        l6->setObjectName("l6");
        l6->setGeometry(QRect(270, 330, 113, 26));
        label_10 = new QLabel(tab);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(160, 280, 91, 31));
        label_19 = new QLabel(tab);
        label_19->setObjectName("label_19");
        label_19->setGeometry(QRect(160, 330, 91, 31));
        l7 = new QLineEdit(tab);
        l7->setObjectName("l7");
        l7->setGeometry(QRect(270, 390, 113, 26));
        label_20 = new QLabel(tab);
        label_20->setObjectName("label_20");
        label_20->setGeometry(QRect(160, 390, 91, 31));
        label_21 = new QLabel(tab);
        label_21->setObjectName("label_21");
        label_21->setGeometry(QRect(160, 440, 63, 20));
        l2 = new QLineEdit(tab);
        l2->setObjectName("l2");
        l2->setGeometry(QRect(270, 440, 113, 26));
        label_22 = new QLabel(tab);
        label_22->setObjectName("label_22");
        label_22->setGeometry(QRect(150, 500, 121, 20));
        l4 = new QLineEdit(tab);
        l4->setObjectName("l4");
        l4->setGeometry(QRect(270, 490, 113, 26));
        label_23 = new QLabel(tab);
        label_23->setObjectName("label_23");
        label_23->setGeometry(QRect(130, 590, 151, 20));
        l5 = new QLineEdit(tab);
        l5->setObjectName("l5");
        l5->setGeometry(QRect(270, 530, 113, 26));
        afficherButton = new QPushButton(tab);
        afficherButton->setObjectName("afficherButton");
        afficherButton->setGeometry(QRect(10, 300, 93, 29));
        PDF = new QPushButton(tab);
        PDF->setObjectName("PDF");
        PDF->setGeometry(QRect(930, 180, 93, 29));
        label_9 = new QLabel(tab);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(160, 540, 141, 20));
        tableView_employes = new QTableView(tab);
        tableView_employes->setObjectName("tableView_employes");
        tableView_employes->setGeometry(QRect(460, 280, 511, 231));
        Rechrche = new QPushButton(tab);
        Rechrche->setObjectName("Rechrche");
        Rechrche->setGeometry(QRect(720, 90, 101, 31));
        label_24 = new QLabel(tab);
        label_24->setObjectName("label_24");
        label_24->setGeometry(QRect(420, 90, 63, 20));
        label_24->setStyleSheet(QString::fromUtf8("alternate-background-color: rgb(0, 0, 0);"));
        l11 = new QLineEdit(tab);
        l11->setObjectName("l11");
        l11->setGeometry(QRect(270, 90, 431, 26));
        l11->setStyleSheet(QString::fromUtf8("alternate-background-color: rgb(0, 0, 0);\n"
"background-color: rgb(147, 154, 255);"));
        statistique = new QPushButton(tab);
        statistique->setObjectName("statistique");
        statistique->setGeometry(QRect(830, 180, 93, 29));
        notification = new QPushButton(tab);
        notification->setObjectName("notification");
        notification->setGeometry(QRect(880, 10, 93, 29));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        label_14 = new QLabel(tab_2);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(0, 0, 1051, 621));
        label_14->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_15 = new QLabel(tab_2);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(0, 0, 151, 71));
        label_15->setPixmap(QPixmap(QString::fromUtf8("../../Bureau/logo inter.png")));
        label_15->setScaledContents(true);
        label_16 = new QLabel(tab_2);
        label_16->setObjectName("label_16");
        label_16->setGeometry(QRect(0, 80, 151, 531));
        label_16->setStyleSheet(QString::fromUtf8("background-color: rgb(136, 159, 214);"));
        label_17 = new QLabel(tab_2);
        label_17->setObjectName("label_17");
        label_17->setGeometry(QRect(150, 0, 901, 81));
        label_17->setStyleSheet(QString::fromUtf8("background-color: rgb(136, 159, 214);"));
        label_35 = new QLabel(tab_2);
        label_35->setObjectName("label_35");
        label_35->setGeometry(QRect(10, 60, 161, 101));
        label_36 = new QLabel(tab_2);
        label_36->setObjectName("label_36");
        label_36->setGeometry(QRect(10, 110, 141, 91));
        label_37 = new QLabel(tab_2);
        label_37->setObjectName("label_37");
        label_37->setGeometry(QRect(10, 190, 101, 31));
        label_37->setStyleSheet(QString::fromUtf8("background-color: rgb(147, 154, 255);"));
        label_38 = new QLabel(tab_2);
        label_38->setObjectName("label_38");
        label_38->setGeometry(QRect(10, 230, 121, 31));
        label_39 = new QLabel(tab_2);
        label_39->setObjectName("label_39");
        label_39->setGeometry(QRect(0, 260, 131, 20));
        label_40 = new QLabel(tab_2);
        label_40->setObjectName("label_40");
        label_40->setGeometry(QRect(0, 280, 151, 20));
        label_64 = new QLabel(tab_2);
        label_64->setObjectName("label_64");
        label_64->setGeometry(QRect(10, 310, 101, 41));
        label_65 = new QLabel(tab_2);
        label_65->setObjectName("label_65");
        label_65->setGeometry(QRect(10, 370, 63, 31));
        label_66 = new QLabel(tab_2);
        label_66->setObjectName("label_66");
        label_66->setGeometry(QRect(10, 410, 111, 31));
        label_67 = new QLabel(tab_2);
        label_67->setObjectName("label_67");
        label_67->setGeometry(QRect(30, 580, 121, 20));
        label_77 = new QLabel(tab_2);
        label_77->setObjectName("label_77");
        label_77->setGeometry(QRect(970, 10, 81, 61));
        label_77->setPixmap(QPixmap(QString::fromUtf8("../../Bureau/15.png")));
        label_77->setScaledContents(true);
        label_78 = new QLabel(tab_2);
        label_78->setObjectName("label_78");
        label_78->setGeometry(QRect(920, 20, 51, 51));
        label_78->setPixmap(QPixmap(QString::fromUtf8("../../Bureau/6086198-icone-de-notification-pour-le-web-vectoriel.png")));
        label_78->setScaledContents(true);
        label_80 = new QLabel(tab_2);
        label_80->setObjectName("label_80");
        label_80->setGeometry(QRect(380, 20, 431, 51));
        label_82 = new QLabel(tab_2);
        label_82->setObjectName("label_82");
        label_82->setGeometry(QRect(410, 260, 63, 81));
        label_81 = new QLabel(tab_2);
        label_81->setObjectName("label_81");
        label_81->setGeometry(QRect(170, 100, 241, 141));
        label_86 = new QLabel(tab_2);
        label_86->setObjectName("label_86");
        label_86->setGeometry(QRect(790, 100, 241, 141));
        label_85 = new QLabel(tab_2);
        label_85->setObjectName("label_85");
        label_85->setGeometry(QRect(800, 470, 241, 141));
        verticalLayoutWidget = new QWidget(tab_2);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(350, 190, 451, 321));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticlLayout = new QLabel(verticalLayoutWidget);
        verticlLayout->setObjectName("verticlLayout");
        verticlLayout->setPixmap(QPixmap(QString::fromUtf8("../../Bureau/sat.png")));
        verticlLayout->setScaledContents(true);

        verticalLayout->addWidget(verticlLayout);

        tabWidget->addTab(tab_2, QString());
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1171, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QString());
        label_3->setText(QString());
        label_4->setText(QString());
        label_2->setText(QString());
        label_5->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:12pt; color:#ffffff;\"> v\303\251hicules</span></p></body></html>", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:12pt; color:#ffffff;\">Equipement</span></p></body></html>", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:12pt; color:#ffffff;\">Employ\303\251</span></p></body></html>", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:12pt; color:#ffffff;\">clients</span></p></body></html>", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:12pt; color:#ffffff;\">Locaux</span></p></body></html>", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:12pt; color:#ffffff;\">Facturations</span></p></body></html>", nullptr));
        label_68->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" color:#ffffff;\">se d\303\251connecter</span></p></body></html>", nullptr));
        label_74->setText(QString());
        label_73->setText(QString());
        label_75->setText(QString());
        label_76->setText(QString());
        ajouterButton->setText(QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        label_71->setText(QString());
        trier->setText(QCoreApplication::translate("MainWindow", "trier par", nullptr));
        supprimerButton->setText(QCoreApplication::translate("MainWindow", "supprimer", nullptr));
        miseajourButton->setText(QCoreApplication::translate("MainWindow", "mise \303\240 jour", nullptr));
        l1->setText(QString());
        label_8->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700; color:#ffffff;\">ID_Employer</span></p></body></html>", nullptr));
        l3->setText(QString());
        l6->setText(QString());
        label_10->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:11pt; font-weight:700; color:#ffffff;\">Age</span></p></body></html>", nullptr));
        label_19->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700; color:#ffffff;\">Adresse</span></p></body></html>", nullptr));
        l7->setText(QString());
        label_20->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:700; color:#ffffff;\">Email</span></p></body></html>", nullptr));
        label_21->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:11pt; font-weight:700; color:#ffffff;\">nom</span></p></body></html>", nullptr));
        l2->setText(QString());
        label_22->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:8pt; font-weight:700; color:#ffffff;\">num_telephone</span></p></body></html>", nullptr));
        label_23->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:8pt; font-weight:700; color:#ffffff;\">Date_embauche</span></p></body></html>", nullptr));
        afficherButton->setText(QCoreApplication::translate("MainWindow", "afficher", nullptr));
        PDF->setText(QCoreApplication::translate("MainWindow", "PDF", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:8pt; color:#ffffff;\">date_embauche</span></p></body></html>", nullptr));
        Rechrche->setText(QCoreApplication::translate("MainWindow", "Rechrche ", nullptr));
        label_24->setText(QString());
        statistique->setText(QCoreApplication::translate("MainWindow", "statistique", nullptr));
        notification->setText(QCoreApplication::translate("MainWindow", "notification", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "employ\303\251", nullptr));
        label_14->setText(QString());
        label_15->setText(QString());
        label_16->setText(QString());
        label_17->setText(QString());
        label_35->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:12pt; color:#ffffff;\"> v\303\251hicules</span></p></body></html>", nullptr));
        label_36->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:12pt; color:#ffffff;\">Equipement</span></p></body></html>", nullptr));
        label_37->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:12pt; color:#ffffff;\">Employ\303\251</span></p></body></html>", nullptr));
        label_38->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:7pt; color:#ffffff;\">-Ajouter un employer</span></p></body></html>", nullptr));
        label_39->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:7pt; color:#ffffff;\">-Supprimer un employer</span></p></body></html>", nullptr));
        label_40->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:7pt; color:#ffffff;\">-Mise \303\240 jour d'un employer</span></p></body></html>", nullptr));
        label_64->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:12pt; color:#ffffff;\">clients</span></p></body></html>", nullptr));
        label_65->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:12pt; color:#ffffff;\">Locaux</span></p></body></html>", nullptr));
        label_66->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:12pt; color:#ffffff;\">Facturations</span></p></body></html>", nullptr));
        label_67->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:10pt; color:#ffffff;\">se d\303\251connecter</span></p></body></html>", nullptr));
        label_77->setText(QString());
        label_78->setText(QString());
        label_80->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:18pt; font-weight:700; color:#ffffff;\">Statistique selon l'age</span></p></body></html>", nullptr));
        label_82->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:14pt; color:#ffffff;\">70%</span></p></body></html>", nullptr));
        label_81->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Des employ\303\251s entre :25 ans-35 ans</p></body></html>", nullptr));
        label_86->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Des employ\303\251s entre :46 ans-60 ans</p></body></html>", nullptr));
        label_85->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Des employ\303\251s entre :36ans-46 ans</p></body></html>", nullptr));
        verticlLayout->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "statistique", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
