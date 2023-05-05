#ifndef RESERVATION_H
#define RESERVATION_H


#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include<QDate>

class Reservation
{
public:
    Reservation();
    Reservation(int ,int ,QString ,QDate );



    bool ajouter();
    QSqlQueryModel * afficher();
    QSqlQueryModel * prises(QDate);
    bool supprimer(int);
    bool modifier();

    QSqlQueryModel * remplircomboreser();
    QSqlQueryModel * displayClause(QString cls);
    QSqlQueryModel * trideccroissant();
    QSqlQueryModel * tricroissant();
  QSqlQueryModel * tri();


private:

    int id,numprise;
    QDate datee;
    QString matricule;
};
#endif // RESERVATION_H
