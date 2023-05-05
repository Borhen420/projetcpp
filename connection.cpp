#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("Station_Charge");
db.setUserName("admin");//inserer nom de l'utilisateur
db.setPassword("123");//inserer mot de passe de cet utilisateur
if (db.open())
test=true;





    return  test;
}
