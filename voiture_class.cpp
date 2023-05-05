#include "voiture_class.h"
#include "dbconnect.h"
#include <QSqlQuery>
#include "voiture.h"
Voiture_Class::Voiture_Class()
{

}

bool Voiture_Class::ajout_voiture(Voiture_Class v)
{
    DBConnect dataBase;

    QSqlQuery query(dataBase.db);
    if(dataBase.openConnexion())
        {
        query.prepare("insert into VOITURES (MATRICULE) VALUES(:matricule)");
        query.bindValue(":matricule",v.matricule);
        }
    return query.exec();
}
