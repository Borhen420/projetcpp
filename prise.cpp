#include "prise.h"
#include <QObject>
#include <QMainWindow>
#include <QMessageBox>
#include <QDesktopServices>
#include <QDateTime>
#include <QDate>
#include <QFile>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QHttpMultiPart>
#include <QUrl>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTimer>
#include <QEventLoop>
#include <QPdfWriter>
#include <QPainter>

Prise::Prise(){
    ID =0;
    DISPONIBILITE= "";
    ETAT= 0;
    VOLTAGE= 0;

}
Prise::Prise(int ID,QString DISPONIBILITE,int ETAT,int VOLTAGE){
    this->ID=ID;
    this->DISPONIBILITE=DISPONIBILITE;
    this->ETAT=ETAT;
    this->VOLTAGE = VOLTAGE;
}
/**************************************/
int Prise::getid(){return ID;}
QString Prise::getdispo(){return DISPONIBILITE;}
int Prise::getetat(){return ETAT;}
int Prise::getvolt(){return VOLTAGE;}
/**************************************/
void Prise::setid(int ID){this->ID=ID;}
void Prise::setdispo(QString DISPONIBILITE){this->DISPONIBILITE=DISPONIBILITE;}
void Prise::setetat(int ETAT){this->ETAT=ETAT;}
void Prise::setvolt(int VOLTAGE){this->VOLTAGE=VOLTAGE;}
/**************************************/
bool Prise::ajouter(){
QSqlQuery query;
query.prepare("INSERT INTO PRISES (DISPONIBILITE,ETAT_PRISE, VOLTAGE, ID_PRISE )" "VALUES (:dispo, :etat_pris, :volt, :id_pri)");
query.bindValue(":dispo", DISPONIBILITE);
query.bindValue(":etat_pris", ETAT);
query.bindValue(":volt", VOLTAGE);
query.bindValue(":id_pri", ID);
return query.exec();
}
bool Prise::ajouter_distance(int d){
    QSqlQuery query;
    query.prepare("UPDATE PRISES SET DISTANCE=:distance WHERE ID_PRISE=:id");
    query.bindValue(":id", ID);
    query.bindValue(":distance", d);
    return query.exec();
}

bool Prise::supprimer(int ID)
{
    QSqlQuery query;
         query.prepare("DELETE FROM PRISES where ID_PRISE= :ID");
         query.bindValue(0, ID);
    return query.exec();
}
bool Prise::modifier()
{
    QSqlQuery query;
    query.prepare("UPDATE PRISES SET DISPONIBILITE=:DISPONIBILITE, ETAT_PRISE=:ETAT, VOLTAGE=:VOLTAGE WHERE ID_PRISE=:ID ");
    query.bindValue(":ID", ID);
    query.bindValue(":DISPONIBILITE", DISPONIBILITE);
    query.bindValue(":ETAT", ETAT);
    query.bindValue(":VOLTAGE", VOLTAGE);
    return query.exec();
}
/**************************************/
QSqlQueryModel* Prise::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT* FROM PRISES");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Disponibilite"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Etat"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Voltage"));
    return  model;
}
QSqlQueryModel* Prise ::afficher_id()
{
    QSqlQueryModel* model=new QSqlQueryModel();
        model->setQuery("SELECT ID_PRISE from PRISES");
        model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    return model;
}
/**************************************/
QSqlQueryModel * Prise::tri_id()
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("SELECT * from PRISES order by ID_PRISE");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Disponibilite"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Etat"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("Voltage"));
    return model;
}
QSqlQueryModel * Prise::tri_etat()
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("select * from PRISES order by ETAT_PRISE");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Disponibilite"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Etat"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("Voltage"));
    return model;
}
QSqlQueryModel * Prise::tri_volt()
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("select * from PRISES order by VOLTAGE");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Disponibilite"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Etat"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("Voltage"));
    return model;
}
/**************************************/
void Prise::clearTable(QTableView *table)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->clear();
    table->setModel(model);
}
void Prise::chercheID(QTableView *table, QString x)
{
   QSqlQueryModel *model=new QSqlQueryModel();
   QSqlQuery *query =new QSqlQuery;
   query->prepare("select * from PRISES where regexp_like(ID_PRISE,:ID_PRISE);");
   query->bindValue(":ID_PRISE",x);
   if(x==0)
   {
       query->prepare("select * from PRISES;");
   }
   query->exec();
   model->setQuery(*query);
   table->setModel(model);
   table->show();
}
void Prise::chercheVolt(QTableView *table, QString x)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    QSqlQuery *query =new QSqlQuery;
    query->prepare("select * from PRISES where regexp_like(VOLTAGE,:VOLTAGE);");
    query->bindValue(":VOLTAGE",x);
    if(x==0)
    {
        query->prepare("select * from PRISES;");
    }
    query->exec();
    model->setQuery(*query);
    table->setModel(model);
    table->show();
}

