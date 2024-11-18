/********************************************************************************
** Form generated from reading UI file 'gestionV.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GESTIONV_H
#define UI_GESTIONV_H

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
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *acceuil;
    QLabel *boulo;
    QLabel *fond;
    QLabel *logoapp;
    QLabel *boulouna;
    QLabel *boulouna_2;
    QLabel *marque;
    QLabel *idclient;
    QLabel *matricule;
    QLabel *titre;
    QLabel *assurance;
    QLabel *kilometrages;
    QLabel *Recherche;
    QLabel *modele;
    QLabel *fabricationannee;
    QLabel *etat;
    QPushButton *modifier;
    QPushButton *ajouter;
    QLabel *alertesicon;
    QPushButton *supprimer;
    QLineEdit *reponsematricule;
    QLineEdit *reponsemodele;
    QLineEdit *reponsemarque;
    QLineEdit *reponseanneefab;
    QLineEdit *reponseidclient;
    QLineEdit *reponseetat;
    QLineEdit *reponsekilometrages;
    QPushButton *PDF;
    QPushButton *alertes;
    QPushButton *trier;
    QLabel *pdficon;
    QLabel *triericon;
    QPushButton *rechercher;
    QTableView *Aff;
    QLineEdit *reponseassurance;
    QLineEdit *recherche;
    QWidget *statistiques;
    QLabel *fond_2;
    QLabel *boulouna_3;
    QLabel *boulouna_4;
    QLabel *graphecercle;
    QLabel *paragraphe;
    QTableView *statview;
    QPushButton *statistique;
    QWidget *ChatBot;
    QLabel *fond_3;
    QLabel *boulouna_5;
    QLabel *boulouna_6;
    QLabel *paragraphe_2;
    QLabel *chatimage;
    QTableView *chatbotview;
    QPushButton *Chatbutton;
    QPushButton *modify;
    QPushButton *cancel;
    QTableView *tableView;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1298, 818);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName("centralWidget");
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(0, 0, 1301, 781));
        acceuil = new QWidget();
        acceuil->setObjectName("acceuil");
        boulo = new QLabel(acceuil);
        boulo->setObjectName("boulo");
        boulo->setGeometry(QRect(960, 170, 801, 591));
        boulo->setPixmap(QPixmap(QString::fromUtf8("../../interface/boulouna.png")));
        fond = new QLabel(acceuil);
        fond->setObjectName("fond");
        fond->setGeometry(QRect(-40, -60, 2311, 1161));
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(5);
        sizePolicy.setVerticalStretch(5);
        sizePolicy.setHeightForWidth(fond->sizePolicy().hasHeightForWidth());
        fond->setSizePolicy(sizePolicy);
        fond->setSizeIncrement(QSize(5, 5));
        fond->setBaseSize(QSize(5, 5));
        fond->setMouseTracking(true);
        fond->setTabletTracking(true);
        fond->setStyleSheet(QString::fromUtf8("background-color: rgb(136, 159, 214); "));
        fond->setPixmap(QPixmap(QString::fromUtf8("../../../../../../../Downloads/WhatsApp Image 2024-10-05 at 6.18.21 PM.jpeg")));
        fond->setScaledContents(true);
        logoapp = new QLabel(acceuil);
        logoapp->setObjectName("logoapp");
        logoapp->setGeometry(QRect(0, 0, 141, 111));
        logoapp->setPixmap(QPixmap(QString::fromUtf8("../../interface/logo app.png")));
        logoapp->setScaledContents(true);
        boulouna = new QLabel(acceuil);
        boulouna->setObjectName("boulouna");
        boulouna->setGeometry(QRect(1060, -70, 801, 591));
        boulouna->setPixmap(QPixmap(QString::fromUtf8("../../interface/boulouna.png")));
        boulouna_2 = new QLabel(acceuil);
        boulouna_2->setObjectName("boulouna_2");
        boulouna_2->setGeometry(QRect(1080, 250, 801, 591));
        boulouna_2->setPixmap(QPixmap(QString::fromUtf8("../../interface/boulouna.png")));
        marque = new QLabel(acceuil);
        marque->setObjectName("marque");
        marque->setGeometry(QRect(0, 190, 231, 61));
        idclient = new QLabel(acceuil);
        idclient->setObjectName("idclient");
        idclient->setGeometry(QRect(0, 410, 191, 141));
        matricule = new QLabel(acceuil);
        matricule->setObjectName("matricule");
        matricule->setGeometry(QRect(0, 120, 251, 81));
        titre = new QLabel(acceuil);
        titre->setObjectName("titre");
        titre->setGeometry(QRect(320, -10, 581, 141));
        assurance = new QLabel(acceuil);
        assurance->setObjectName("assurance");
        assurance->setGeometry(QRect(0, 590, 201, 61));
        kilometrages = new QLabel(acceuil);
        kilometrages->setObjectName("kilometrages");
        kilometrages->setGeometry(QRect(0, 300, 141, 71));
        Recherche = new QLabel(acceuil);
        Recherche->setObjectName("Recherche");
        Recherche->setGeometry(QRect(500, 130, 461, 111));
        Recherche->setPixmap(QPixmap(QString::fromUtf8("../../interface/search bar.png")));
        modele = new QLabel(acceuil);
        modele->setObjectName("modele");
        modele->setGeometry(QRect(0, 240, 231, 71));
        fabricationannee = new QLabel(acceuil);
        fabricationannee->setObjectName("fabricationannee");
        fabricationannee->setGeometry(QRect(0, 380, 231, 61));
        etat = new QLabel(acceuil);
        etat->setObjectName("etat");
        etat->setGeometry(QRect(0, 510, 251, 81));
        modifier = new QPushButton(acceuil);
        modifier->setObjectName("modifier");
        modifier->setGeometry(QRect(780, 320, 101, 41));
        ajouter = new QPushButton(acceuil);
        ajouter->setObjectName("ajouter");
        ajouter->setGeometry(QRect(570, 320, 101, 41));
        alertesicon = new QLabel(acceuil);
        alertesicon->setObjectName("alertesicon");
        alertesicon->setGeometry(QRect(940, 640, 91, 81));
        alertesicon->setPixmap(QPixmap(QString::fromUtf8("../../interface/notif.png")));
        supprimer = new QPushButton(acceuil);
        supprimer->setObjectName("supprimer");
        supprimer->setGeometry(QRect(990, 320, 101, 41));
        reponsematricule = new QLineEdit(acceuil);
        reponsematricule->setObjectName("reponsematricule");
        reponsematricule->setGeometry(QRect(260, 130, 261, 51));
        reponsemodele = new QLineEdit(acceuil);
        reponsemodele->setObjectName("reponsemodele");
        reponsemodele->setGeometry(QRect(260, 260, 261, 51));
        reponsemarque = new QLineEdit(acceuil);
        reponsemarque->setObjectName("reponsemarque");
        reponsemarque->setGeometry(QRect(260, 200, 261, 51));
        reponseanneefab = new QLineEdit(acceuil);
        reponseanneefab->setObjectName("reponseanneefab");
        reponseanneefab->setGeometry(QRect(260, 380, 261, 51));
        reponseidclient = new QLineEdit(acceuil);
        reponseidclient->setObjectName("reponseidclient");
        reponseidclient->setGeometry(QRect(260, 450, 261, 51));
        reponseetat = new QLineEdit(acceuil);
        reponseetat->setObjectName("reponseetat");
        reponseetat->setGeometry(QRect(260, 530, 261, 51));
        reponsekilometrages = new QLineEdit(acceuil);
        reponsekilometrages->setObjectName("reponsekilometrages");
        reponsekilometrages->setGeometry(QRect(260, 320, 261, 51));
        PDF = new QPushButton(acceuil);
        PDF->setObjectName("PDF");
        PDF->setGeometry(QRect(590, 610, 171, 31));
        alertes = new QPushButton(acceuil);
        alertes->setObjectName("alertes");
        alertes->setGeometry(QRect(910, 610, 161, 29));
        trier = new QPushButton(acceuil);
        trier->setObjectName("trier");
        trier->setGeometry(QRect(670, 240, 101, 41));
        pdficon = new QLabel(acceuil);
        pdficon->setObjectName("pdficon");
        pdficon->setGeometry(QRect(640, 650, 81, 61));
        pdficon->setPixmap(QPixmap(QString::fromUtf8("down.png")));
        triericon = new QLabel(acceuil);
        triericon->setObjectName("triericon");
        triericon->setGeometry(QRect(580, 220, 71, 91));
        triericon->setPixmap(QPixmap(QString::fromUtf8("trier.png")));
        rechercher = new QPushButton(acceuil);
        rechercher->setObjectName("rechercher");
        rechercher->setGeometry(QRect(960, 170, 121, 41));
        Aff = new QTableView(acceuil);
        Aff->setObjectName("Aff");
        Aff->setGeometry(QRect(560, 380, 541, 221));
        reponseassurance = new QLineEdit(acceuil);
        reponseassurance->setObjectName("reponseassurance");
        reponseassurance->setGeometry(QRect(260, 600, 261, 51));
        recherche = new QLineEdit(acceuil);
        recherche->setObjectName("recherche");
        recherche->setGeometry(QRect(560, 170, 341, 31));
        tabWidget->addTab(acceuil, QString());
        statistiques = new QWidget();
        statistiques->setObjectName("statistiques");
        fond_2 = new QLabel(statistiques);
        fond_2->setObjectName("fond_2");
        fond_2->setGeometry(QRect(-10, 0, 1471, 821));
        sizePolicy.setHeightForWidth(fond_2->sizePolicy().hasHeightForWidth());
        fond_2->setSizePolicy(sizePolicy);
        fond_2->setSizeIncrement(QSize(5, 5));
        fond_2->setBaseSize(QSize(5, 5));
        fond_2->setMouseTracking(true);
        fond_2->setTabletTracking(true);
        fond_2->setStyleSheet(QString::fromUtf8("background-color: rgb(136, 159, 214); \n"
"border-color: rgb(255, 255, 255);"));
        fond_2->setPixmap(QPixmap(QString::fromUtf8("../../../../../../../Downloads/WhatsApp Image 2024-10-05 at 6.18.21 PM.jpeg")));
        fond_2->setScaledContents(true);
        boulouna_3 = new QLabel(statistiques);
        boulouna_3->setObjectName("boulouna_3");
        boulouna_3->setGeometry(QRect(1060, -40, 801, 591));
        boulouna_3->setPixmap(QPixmap(QString::fromUtf8("../../interface/boulouna.png")));
        boulouna_4 = new QLabel(statistiques);
        boulouna_4->setObjectName("boulouna_4");
        boulouna_4->setGeometry(QRect(1070, 270, 801, 591));
        boulouna_4->setPixmap(QPixmap(QString::fromUtf8("../../interface/boulouna.png")));
        graphecercle = new QLabel(statistiques);
        graphecercle->setObjectName("graphecercle");
        graphecercle->setGeometry(QRect(50, 350, 391, 311));
        graphecercle->setPixmap(QPixmap(QString::fromUtf8("../../interface/graphe2.png")));
        paragraphe = new QLabel(statistiques);
        paragraphe->setObjectName("paragraphe");
        paragraphe->setGeometry(QRect(20, 130, 481, 231));
        paragraphe->setStyleSheet(QString::fromUtf8(""));
        statview = new QTableView(statistiques);
        statview->setObjectName("statview");
        statview->setGeometry(QRect(590, 160, 441, 371));
        statistique = new QPushButton(statistiques);
        statistique->setObjectName("statistique");
        statistique->setGeometry(QRect(20, 50, 271, 51));
        tabWidget->addTab(statistiques, QString());
        ChatBot = new QWidget();
        ChatBot->setObjectName("ChatBot");
        fond_3 = new QLabel(ChatBot);
        fond_3->setObjectName("fond_3");
        fond_3->setGeometry(QRect(-10, -90, 1471, 891));
        sizePolicy.setHeightForWidth(fond_3->sizePolicy().hasHeightForWidth());
        fond_3->setSizePolicy(sizePolicy);
        fond_3->setSizeIncrement(QSize(5, 5));
        fond_3->setBaseSize(QSize(5, 5));
        fond_3->setMouseTracking(true);
        fond_3->setTabletTracking(true);
        fond_3->setStyleSheet(QString::fromUtf8("background-color: rgb(136, 159, 214); "));
        fond_3->setPixmap(QPixmap(QString::fromUtf8("../../../../../../../Downloads/WhatsApp Image 2024-10-05 at 6.18.21 PM.jpeg")));
        fond_3->setScaledContents(true);
        boulouna_5 = new QLabel(ChatBot);
        boulouna_5->setObjectName("boulouna_5");
        boulouna_5->setGeometry(QRect(1060, -50, 801, 591));
        boulouna_5->setPixmap(QPixmap(QString::fromUtf8("../../interface/boulouna.png")));
        boulouna_6 = new QLabel(ChatBot);
        boulouna_6->setObjectName("boulouna_6");
        boulouna_6->setGeometry(QRect(1060, 230, 801, 591));
        boulouna_6->setPixmap(QPixmap(QString::fromUtf8("../../interface/boulouna.png")));
        paragraphe_2 = new QLabel(ChatBot);
        paragraphe_2->setObjectName("paragraphe_2");
        paragraphe_2->setGeometry(QRect(880, 90, 411, 191));
        chatimage = new QLabel(ChatBot);
        chatimage->setObjectName("chatimage");
        chatimage->setGeometry(QRect(740, 410, 311, 181));
        chatimage->setPixmap(QPixmap(QString::fromUtf8("../../interface/download.jpg")));
        chatbotview = new QTableView(ChatBot);
        chatbotview->setObjectName("chatbotview");
        chatbotview->setGeometry(QRect(10, 140, 631, 491));
        Chatbutton = new QPushButton(ChatBot);
        Chatbutton->setObjectName("Chatbutton");
        Chatbutton->setGeometry(QRect(20, 60, 261, 41));
        modify = new QPushButton(ChatBot);
        modify->setObjectName("modify");
        modify->setGeometry(QRect(1000, 330, 83, 29));
        cancel = new QPushButton(ChatBot);
        cancel->setObjectName("cancel");
        cancel->setGeometry(QRect(760, 330, 83, 29));
        tabWidget->addTab(ChatBot, QString());
        tableView = new QTableView(centralWidget);
        tableView->setObjectName("tableView");
        tableView->setGeometry(QRect(-10, -10, 1331, 651));
        MainWindow->setCentralWidget(centralWidget);
        tableView->raise();
        tabWidget->raise();
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 1298, 25));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName("mainToolBar");
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName("statusBar");
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Gestion des Clients", nullptr));
        boulo->setText(QString());
        fond->setText(QString());
        logoapp->setText(QString());
        boulouna->setText(QString());
        boulouna_2->setText(QString());
        marque->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:700; color:#000000;\">La marque de la voiture</span></p></body></html>", nullptr));
        idclient->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:700; color:#000000;\">L'id du propri\303\251taire </span></p></body></html>", nullptr));
        matricule->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:700; color:#000000;\">La matricule de la voiture</span></p></body></html>", nullptr));
        titre->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:28pt; font-weight:700; font-style:italic; text-decoration: underline; color:#000000;\">Gestion des V\303\251hicules</span></p></body></html>", nullptr));
        assurance->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:700; color:#000000;\">Assurance en cours</span></p></body></html>", nullptr));
        kilometrages->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:700;\">Kilometrages</span></p></body></html>", nullptr));
        Recherche->setText(QString());
        modele->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:700; color:#000000;\">Le mod\303\251le de la voiture</span></p></body></html>", nullptr));
        fabricationannee->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:700; color:#000000;\">L'ann\303\251e de fabrication</span></p></body></html>", nullptr));
        etat->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:700; color:#000000;\">L'etat actuel de la voiture</span></p></body></html>", nullptr));
        modifier->setText(QCoreApplication::translate("MainWindow", "Modifier", nullptr));
        ajouter->setText(QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        alertesicon->setText(QString());
        supprimer->setText(QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
        PDF->setText(QCoreApplication::translate("MainWindow", "Telecharger PDF", nullptr));
        alertes->setText(QCoreApplication::translate("MainWindow", "Alertes et notifications", nullptr));
        trier->setText(QCoreApplication::translate("MainWindow", "Trier", nullptr));
        pdficon->setText(QString());
        triericon->setText(QString());
        rechercher->setText(QCoreApplication::translate("MainWindow", "Rechercher", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(acceuil), QCoreApplication::translate("MainWindow", "Acceuil", nullptr));
        fond_2->setText(QString());
        boulouna_3->setText(QString());
        boulouna_4->setText(QString());
        graphecercle->setText(QString());
        paragraphe->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:12pt; color:#000000;\">Les statistiques sont faites selon la marque</span></p><p><br/></p></body></html>", nullptr));
        statistique->setText(QCoreApplication::translate("MainWindow", "Faire les Statistiques", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(statistiques), QCoreApplication::translate("MainWindow", "Statistiques", nullptr));
        fond_3->setText(QString());
        boulouna_5->setText(QString());
        boulouna_6->setText(QString());
        paragraphe_2->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:12pt;\">La disscussion sera \303\240 propos des rendez-vous : </span></p><p><span style=\" font-size:12pt;\">La date du rendez-vous</span></p><p><span style=\" font-size:12pt;\">Le type du rendez-vous</span></p><p><span style=\" font-size:12pt;\">La statut du rendez-vous</span></p></body></html>", nullptr));
        chatimage->setText(QString());
        Chatbutton->setText(QCoreApplication::translate("MainWindow", "Discutez avec moi", nullptr));
        modify->setText(QCoreApplication::translate("MainWindow", "modify", nullptr));
        cancel->setText(QCoreApplication::translate("MainWindow", "cancel", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(ChatBot), QCoreApplication::translate("MainWindow", "Chatbot", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GESTIONV_H
