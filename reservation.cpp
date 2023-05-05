#include "reservation.h"
#include <QDebug>

Reservation::Reservation()
{
id=0;
numprise=0;
matricule="";
}

Reservation::Reservation(int id,int numprise,QString matricule,QDate datee)
{
    this->id=id;
    this->numprise=numprise;
    this->matricule=matricule;
    this->datee = datee;
}
/*
int Reservation::get_id(){return id;}
int Reservation::get_numprise(){return numprise;}
int Reservation::get_disponibilite(){return disponibilite;}
QDateTime Reservation::get_date(){return  datee;}



void Reservation::set_id(int id){this->id=id;}
void Reservation::set_numprise(int) numprise){this->numprise=numprise;}
void Reservation::set_disponibilite(int disponibilite){this->disponibilite=disponibilite;}
*/


//*******AJOUTER

bool Reservation::ajouter()
{
QSqlQuery query;

query.prepare("INSERT INTO RESERVATION (ID_PRISE, MATRICULE, DATE_RESERVATION) "
                    "VALUES (:numprise, :disponibilite, :date)");


query.bindValue(":numprise", numprise);
query.bindValue(":disponibilite", matricule);
query.bindValue(":date", datee);


return    query.exec();
}

//******AFFICHER

QSqlQueryModel * Reservation::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from RESERVATION");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Date reservation"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("matricule"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Numero de prise"));



    return model;
}

QSqlQueryModel* Reservation::prises(QDate d)
{
    QSqlQueryModel* model = new QSqlQueryModel();
QString formattedDate =  d.toString("dd-MMM-yy").toUpper();
    model->setQuery("SELECT * FROM prises WHERE id_prise NOT IN (SELECT id_prise FROM reservation WHERE date_reservation LIKE '"+formattedDate+"')");
  // model->setQuery("SELECT * FROM prises");
//qDebug() << "Query:" << query.lastQuery() ;


  //  model->setQuery(query);

    return model;
}


//*******SUPPRIMPER

bool Reservation::supprimer(int idd)
{
QSqlQuery query;
QString res= QString::number(idd);
query.prepare("Delete from RESERVATION where ID_RESERVATION = :id ");
query.bindValue(":id", res);
return    query.exec();
}



//*******MODIFIER

bool Reservation::modifier()
{
QSqlQuery query;

query.prepare("UPDATE RESERVATION SET ID_PRISE= :numprise,MATRICULE=:disponibilite, DATE_RESERVATION= :datee "
                    " WHERE  ID_RESERVATION = :id ");


query.bindValue(":id", id);
query.bindValue(":numprise", numprise);
query.bindValue(":disponibilite", matricule);
query.bindValue(":datee", datee);



return    query.exec();
}


QSqlQueryModel *Reservation::displayClause(QString cls)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from RESERVATION " +cls);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_RESERVATION"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("DATE_RESERVATION"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("ID_PRISE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("MATRICULE"));

    return model;
}
//******REMPLIR COMBO BOX

/*

QSqlQueryModel * Reservation::remplircomboreser()
{
    QSqlQueryModel * mod= new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("select ID from RESERVATION");
    query.exec();
    mod->setQuery(query);
    return mod;
}

*/

QSqlQueryModel *Reservation:: trideccroissant()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from RESERVATION order by ID_PRISE DESC " );
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_RESERVATION"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("DATE_RESERVATION"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("ID_PRISE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("MATRICULE"));

 return model;

}

QSqlQueryModel *Reservation:: tricroissant()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from RESERVATION order by ID_PRISE ASC " );
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_RESERVATION"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("DATE_RESERVATION"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("ID_PRISE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("MATRICULE"));

 return model;

}

QSqlQueryModel *Reservation:: tri()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from RESERVATION order by MATRICULE  " );
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_RESERVATION"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("DATE_RESERVATION"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("ID_PRISE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("MATRICULE"));

 return model;

}
