#ifndef VOITURES_H
#define VOITURES_H
#include <QString>
#include"connection.h"
#include <QSqlQueryModel>

class voitures
{
public:
    voitures();
    int matricule;
    int etat;
    QString marque;
    QString prop;
    int id_prise;
    bool ajout_voiture(voitures v);
    bool modifier_voiture(int matricule,int etat,QString marque,QString prop);
    bool supprimer_voiture(int matr);
    int return_info_etat(int etat);
    QSqlQueryModel *afficher_voiture();
    QSqlQueryModel *afficher_trier();
    QSqlQueryModel *afficher_recherche(QString r);
    QSqlQuery return_data(int mat);
    void stat(int e1,int e2,QWidget *widget);
};

#endif // VOITURES_H
