#include "historique.h"
#include <QDateTime>
#include <QSqlQuery>
#include "mainwindow.h"

/*historique::historique()
{

}*/

Historique::Historique()
{

}
void Historique::save(int id, QString matricule, int numprise, QString action)
{
    QDateTime date = QDateTime::currentDateTime();
    QString dates = date.toString();

    QFile file("D:/QT/reservation copie1/historique.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
    {
        qDebug() << "Erreur: Impossible d'ouvrir le fichier";
        return;
    }

    QTextStream out(&file);
    QString line = " ID reservation : " + QString::number(id) + " Matricule: " + matricule + " numero de prise: " + QString::number(numprise)
                 + " Date de l'action: " + dates + " Action: " + action + "\n";
    out << line;
    file.close();
}

/*
void Historique::save(int id,QString matricule,int numprise,QString action)
{
    //QDate date;
    QDateTime date = QDateTime::currentDateTime();
    QString dates=date.toString();
    QFile file ("D:/QT/reservation copie1/historique.txt");
     if (!file.open(QIODevice::WriteOnly|QIODevice::Append | QIODevice::Text))
      qDebug()<<"erreur";
     QTextStream out(&file);
     out << " id : "+id+" Matricule: "+matricule+" numero de prise: "+numprise+" Date de l'action: "+dates+" Action: "+action << "\n";
}
*/
QStandardItemModel* Historique::load()
{
    QFile file("D:/QT/reservation copie1/historique.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return nullptr;

    QStandardItemModel* model = new QStandardItemModel();

    QTextStream in(&file);
    int i = 0;

    while (!in.atEnd()) {
        QString data = in.readLine();
        QList<QStandardItem*> rowItems;

        // Create a QStandardItem object for each column and set its data
        switch (i) {
        case 0:
            rowItems << new QStandardItem(data);
            break;
        case 1:
            rowItems << new QStandardItem(data);
            break;
        case 2:
            rowItems << new QStandardItem(data);
            break;
        case 3:
            rowItems << new QStandardItem(data);
            break;
        }

        i++;
        if (i == 4) {
            // Append the list of QStandardItem objects to the model as a row
            model->appendRow(rowItems);
            i = 0;
        }
    }

    return model;
}

