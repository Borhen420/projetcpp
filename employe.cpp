#include "employe.h"

Employe::Employe()
{

}
Employe::Employe(int id, QString nom ,QString prenom ,QString email ,QString password,QString role)
{
    this->id = id ;
    this->nom = nom ;
    this->prenom = prenom ;
    this->email = email ;
    this->password = password ;
    this->role = role ;
}
Employe::Employe( QString nom ,QString prenom ,QString email ,QString password,QString role)
{
    this->nom = nom ;
    this->prenom = prenom ;
    this->email = email ;
    this->password = password ;
    this->role = role ;
}
bool Employe::ajouter()
{
    QSqlQuery query;
        query.prepare("INSERT INTO employes (nom,prenom,email,password,role) "
                      "VALUES (:1,:2,:3,:4,:5)");

        query.bindValue(":1",this->nom);
        query.bindValue(":2",this->prenom);
        query.bindValue(":3",this->email);
        query.bindValue(":4",this->password);
        query.bindValue(":5",this->role);

       return query.exec();
}
bool Employe::supprimer(int id)
{
    QSqlQuery query;
        QString res= QString ::number(id);
        query.prepare("Delete from employes where id = :id");
        query.bindValue(":id",res);
        return query.exec();
}
QSqlQueryModel* Employe::afficher()
{
    QSqlQueryModel* model =new QSqlQueryModel();

    model->setQuery ("select * from employes");

    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOM"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("EMAIL"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("MOT DE PASSE"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("ROLE"));

    return model;
}


bool Employe::autentifier(QString email, QString password)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM employes WHERE email = ? AND PASSWORD = ?");
    query.addBindValue(email);
    query.addBindValue(password);
    query.exec();

    query.next();
    int count = query.value(0).toInt();

    return count > 0;
}



bool Employe::modifier()
{
    QSqlQuery query;

    QString res = QString::number(this->id);

    query.prepare("Update employes set nom=:1, prenom = :2 , email= :3 , password= :4 , role = :5 where id= :6 ");

    query.bindValue(":1",this->nom);
    query.bindValue(":2",this->prenom);
    query.bindValue(":3",this->email);
    query.bindValue(":4",this->password);
    query.bindValue(":5",this->role);
    query.bindValue(":6",res);

    return query.exec();
}
QSqlQueryModel * Employe::recherche(QString a)
{

    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM employes WHERE ( nom LIKE '%"+a+"%' OR email LIKE '%"+a+"%' OR id LIKE '%"+a+"%' ) ");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOM"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("EMAIL"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("MOT DE PASSE"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("ROLE"));
    /*model->setHeaderData(6,Qt::Horizontal,QObject::tr("NUMERO_TEL"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("PASSWORD"));*/

    return model;
}

QSqlQueryModel * Employe::Tri(QString cls ,QString champ)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    QString queryString = "SELECT * FROM employes ORDER BY " + champ + " " + cls;
    QSqlQuery query ;
    query.prepare(queryString);
    query.exec();
    model->setQuery(query);
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOM"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("EMAIL"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("MOT DE PASSE"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("ROLE"));
    /*model->setHeaderData(6,Qt::Horizontal,QObject::tr("NUMERO_TEL"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("PASSWORD"));*/

    return model;
}

