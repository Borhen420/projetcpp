#include "main_voiture.h"
#include "dbconnect.h"
#include <QSqlQuery>
#include <QString>
#include <QTextDocument>
#include <QFileDialog>
#include <QSqlRecord>
#include <QTextTableCell>
#include <QPrinter>
#include <QPainter>
#include <QtCharts>
main_voiture::main_voiture()
{

}

bool main_voiture::ajout_voiture(main_voiture v)
{
    DBConnect dataBase;
    QSqlQuery qry(dataBase.db);
    if(dataBase.openConnexion())
    {
        qry.prepare("insert into VOITURES (MATRICULES,MARQUES,PROPRIETAIRE,ETAT) values (:mat,:marque,:prop,:etat)");
        qry.bindValue(":mat",v.matricule);
        qry.bindValue(":marque",v.marque);
        qry.bindValue(":prop",v.prop);
        qry.bindValue(":etat",v.etat);
    }
    return qry.exec();
}

bool main_voiture::modifier_voiture(int matricule,int etat,QString marque,QString prop)
{
    DBConnect dataBase;
    QSqlQuery qry(dataBase.db);
    if(dataBase.openConnexion())
    {
        qry.prepare("update VOITURES set ETAT= :etat,MARQUES= :marque,PROPRIETAIRE= :prop where MATRICULES= :mat");
        qry.bindValue(":mat",matricule);
        qry.bindValue(":marque",marque);
        qry.bindValue(":prop",prop);
        qry.bindValue(":etat",etat);


    }
    return qry.exec();

}

bool main_voiture::supprimer_voiture(int matr)
{
    DBConnect dataBase;
    QSqlQuery qry(dataBase.db);
    if(dataBase.openConnexion())
    {
        qry.prepare("delete from VOITURES where MATRICULES=:mat");
        qry.bindValue(":mat",matr);
    }
    return qry.exec();
}

int main_voiture::return_info_etat(int etat)
{
    int num=0;
    DBConnect dataBase;
    if(dataBase.openConnexion())
        {
            QSqlQuery qry(dataBase.db);
            qry.prepare("select ETAT from VOITURES where ETAT=:e");
            qry.bindValue(":e",etat);
            if(qry.exec() && qry.numRowsAffected())
            {
                while (qry.next())
                {
                    num++;
                }
            }
         }
      return num;

}

QSqlQueryModel *main_voiture::afficher_voiture()
{
    QSqlQueryModel *model=new QSqlQueryModel();
        DBConnect dataBase;
        if(dataBase.openConnexion())
            {
                QSqlQuery *qry=new QSqlQuery(dataBase.db);
                qry->prepare("select MATRICULES,MARQUES,PROPRIETAIRE,ETAT from VOITURES");
                if(qry->exec() && qry->numRowsAffected())
                {
                    model->setQuery(*qry);
                    model->setHeaderData(0,Qt::Horizontal,QObject::tr("MATRICULES"));
                    model->setHeaderData(1,Qt::Horizontal,QObject::tr("MARQUES"));
                    model->setHeaderData(2,Qt::Horizontal,QObject::tr("PROPRIETAIRE"));
                    model->setHeaderData(3,Qt::Horizontal,QObject::tr("ETAT"));
                }

            }
        return model;
}

QSqlQueryModel *main_voiture::afficher_trier()
{
    QSqlQueryModel *model=new QSqlQueryModel();
        DBConnect dataBase;
        if(dataBase.openConnexion())
            {
                QSqlQuery *qry=new QSqlQuery(dataBase.db);
                qry->prepare("select MATRICULES,MARQUES,PROPRIETAIRE,ETAT from VOITURES ORDER BY MARQUES");
                if(qry->exec() && qry->numRowsAffected())
                {
                    model->setQuery(*qry);
                    model->setHeaderData(0,Qt::Horizontal,QObject::tr("MATRICULES"));
                    model->setHeaderData(1,Qt::Horizontal,QObject::tr("MARQUES"));
                    model->setHeaderData(2,Qt::Horizontal,QObject::tr("PROPRIETAIRE"));
                    model->setHeaderData(3,Qt::Horizontal,QObject::tr("ETAT"));
                }

            }
        return model;
}

QSqlQueryModel *main_voiture::afficher_recherche(QString r)
{
    QSqlQueryModel *model=new QSqlQueryModel();
        DBConnect dataBase;

        if(dataBase.openConnexion())
            {
                QSqlQuery *qry=new QSqlQuery(dataBase.db);
                qry->prepare("select MATRICULES,MARQUES,PROPRIETAIRE,ETAT from VOITURES where PROPRIETAIRE=:mat ");
                qry->bindValue(":mat",r);
                if(qry->exec() && qry->numRowsAffected())
                {
                    model->setQuery(*qry);
                    model->setHeaderData(0,Qt::Horizontal,QObject::tr("MATRICULES"));
                    model->setHeaderData(1,Qt::Horizontal,QObject::tr("MARQUES"));
                    model->setHeaderData(2,Qt::Horizontal,QObject::tr("PROPRIETAIRE"));
                    model->setHeaderData(3,Qt::Horizontal,QObject::tr("ETAT"));
                }

            }
        return model;
}

QSqlQuery main_voiture::return_data(int mat)
{
    DBConnect dataBase;
        QSqlQuery query(dataBase.db);
        if(dataBase.openConnexion() ){
            query.prepare("select MATRICULES,MARQUES,PROPRIETAIRE,ETAT from VOITURES where MATRICULES=:mat");
            query.bindValue(":mat",mat);
        }

        return query;
}

void main_voiture::stat(int e1, int e2,QWidget *widget)
{
    QPieSeries *series = new QPieSeries();
           series->append("Charger", e1);
           series->append("Non charger", e2);
           QChart *chart = new QChart();
               chart->addSeries(series);
               chart->setTitle("Voitures Statistiques");
               chart->setAnimationOptions(QChart::SeriesAnimations);
               chart->legend()->setVisible(true);
               chart->legend()->setAlignment(Qt::AlignRight);
               QChartView *chartView = new QChartView(chart);
               chartView->setRenderHint(QPainter::Antialiasing);
               chartView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
               QWidget *size=widget;
               chartView->resize(size->size());
               chartView->show();
}




