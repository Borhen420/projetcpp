#ifndef EMPLOYE_H
#define EMPLOYE_H
#include <QString>
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>

class Employe
{
private :
   int id ;
     QString nom ;
     QString prenom ;
    QString email ;
    QString password ;
    QString role ;


public:
    Employe();
    Employe(int , QString ,QString,QString,QString,QString);
    Employe(QString ,QString,QString,QString,QString);
    bool autentifier(QString email, QString password);


    int getID()
    {
        return this->id ;
    }
    void setID(int id )
    {
        this->id = id ;
    }
    QString getNom()
    {
        return this->nom ;
    }
    void setNom(QString nom )
    {
        this->nom = nom ;
    }
    QString getPrenom()
    {
        return this->prenom ;
    }
    void setPrenom(QString prenom )
    {
        this->prenom = prenom ;
    }
    QString getEmail()
    {
        return this->email ;
    }
    void setEmail(QString email )
    {
        this->email =email ;
    }
    QString getPassword()
    {
        return this->password ;
    }
    void setPassword(QString password)
    {
        this->password = password;
    }
    QString getRole()
    {
        return this->role ;
    }
    void setRole(QString role )
    {
        this->role = role ;
    }

        bool ajouter();
        bool supprimer(int);
        QSqlQueryModel* afficher();
        bool modifier();
        QSqlQueryModel * recherche(QString a);
        QSqlQueryModel * Tri(QString cls,QString champ);
};

#endif // EMPLOYE_H
