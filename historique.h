#ifndef HISTORIQUE_H
#define HISTORIQUE_H
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QDebug>
#include <QStandardItemModel>

class Historique
{
    QString tmp;
public:
    Historique();
    void save(int ,QString ,int ,QString );
    QStandardItemModel* load();


};

#endif // HISTORIQUE_H
