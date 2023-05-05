
#include "notification.h"
#include <QSystemTrayIcon>
#include<QString>


Notification::Notification()
{

}

void Notification::notification_ajoutReservation()
{

    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

    notifyIcon->setIcon(QIcon(":/new/prefix1/valider.png"));
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des RESERVATIONS ","Nouvelle RESERVATION ajoutée ",QSystemTrayIcon::Information,15000);
}

void Notification::notification_supprimerReservation(){
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

    notifyIcon->setIcon(QIcon(":/new/prefix1/C:/Users/kouss/Desktop/supprimer.jpg"));
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des RESERVATIONS ","RESERVATION Supprimée",QSystemTrayIcon::Warning,15000);
}

void Notification::notification_modifierReservation(){
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

    notifyIcon->setIcon(QIcon(":/new/prefix1/modifier.png"));
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des RESERVATIONS ","Une RESERVATION est modifiée",QSystemTrayIcon::Information,15000);

}



