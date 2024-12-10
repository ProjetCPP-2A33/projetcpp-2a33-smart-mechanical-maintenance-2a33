#ifndef LOCAL_H
#define LOCAL_H
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QString>



class Local
{

    int ID_local,Num_telephone,heure_travail;
   QString adresse,Responsable,Service,email;
public:
   Local();
   Local(int id);
   Local(int,QString,QString,int,QString,int,QString);
   int getID(){return ID_local;}
   QString getAdresse(){return adresse;}
   QString getResponsable(){return Responsable;}
   QString getService(){return Service;}
   int getNum_telephone(){return Num_telephone;}
   int getheure_travail(){return heure_travail;};
   void setResponsable(QString x){Responsable=x;}
   void setService(QString n){Service=n;}
   void setNum_telephone(int x){Num_telephone=x;}
   void setheure_travail(int a){heure_travail=a;};
   bool ajouter();
   bool supprimer();
   bool modifier();
   QSqlQueryModel * afficher();
   int countLocaux();



};

#endif // LOCAL_H
