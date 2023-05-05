#include "dbconnect.h"
#include <QSqlDatabase>
DBConnect::DBConnect()
{
    db=QSqlDatabase::database("Station_Charge");
    if(!db.isValid()){
        db = QSqlDatabase::addDatabase("QODBC","Station_Charge");
        db.setDatabaseName("ProjetA2");//Station_Charge
        db.setUserName("raydux");//admin
        db.setPassword("raydux");//123
    }
}

bool DBConnect::openConnexion()
{
    if(db.open()) return  true;
    return  false;
}

void DBConnect::closeConnexion()
{
    db.close();
}

void DBConnect::addDatabase()
{

}
