#ifndef PRISE_H
#define PRISE_H
#include <QTableView>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDoubleValidator>
#include <QtDebug>
#include <QObject>
#include <QMainWindow>
#include <QDateTime>
#include <QFile>
#include <QMessageBox>
#include <QDate>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include<QDate>

class Prise
{
public:
    Prise();
    Prise(int ,QString ,int ,int );
    /*   GETTERS   */
    int getid();
    QString getdispo();
    int getetat();
    int getvolt();
    /*   SETTERS   */
    void setid(int);
    void setdispo(QString);
    void setetat(int);
    void setvolt(int);
    /*   CRUD   */
    bool ajouter();
    bool modifier();
    bool supprimer(int);
bool ajouter_distance(int);
    QSqlQueryModel* afficher(); //pour afficher dans TableView
    QSqlQueryModel* afficher_id(); //pour afficher les ID dans Combobox
    /*   Les Tris   */
    QSqlQueryModel* tri_id();
    QSqlQueryModel* tri_volt();
    QSqlQueryModel* tri_etat();
    /*   Historique   */
    QString read();
    void write(QString,QString);
    QString time();
    void clearh();
    /*   Recherches   */
    void clearTable(QTableView * table);
    void chercheID(QTableView *table, QString x);
    void chercheVolt(QTableView *table, QString x);
private:
    int ID;
    QString DISPONIBILITE;
    int ETAT;
    int VOLTAGE;

};
#endif
