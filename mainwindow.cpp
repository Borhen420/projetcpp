#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "prise.h"
#include <QMessageBox>
#include <QPdfWriter>
#include <QPainter>
#include <QDesktopServices>
#include "smtp.h"
#include <QSettings>
#include "prise.h"
#include "connection.h"
#include "arduino.h"
#include "voitures.h"
#include<QMessageBox>
#include <QSqlQuery>
#include<QSqlQueryModel>
#include<QDesktopServices>
#include<QUrl>
#include<QFile>
#include<QFileInfo>
#include<QFileDialog>
#include<QTextStream>
#include<QPdfWriter>
#include<QPrinter>
#include<QTextDocument>
#include <QZXing.h>
#include<QDebug>
#include<QMessageBox>
#include <QSqlQuery>
#include<QSqlQueryModel>
#include<QDesktopServices>
#include<QUrl>
#include<QFile>
#include<QFileInfo>
#include<QFileDialog>
#include<QTextStream>
#include<QPdfWriter>
#include<QPrinter>
#include<QTextDocument>
#include <QZXing.h>
#include<QDebug>

#include "reservation.h"
#include "notification.h"
#include "historique.h"
#include <QPieSlice>
#include <QPieSeries>
#include <QtCharts/QChartView>
#include <QSqlRecord>



Notification N;
Reservation R;
Historique h;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Station Charge");
    ui->return_from_ajout_2->setVisible(false);
    ui->return_from_ajout_3->setVisible(false);
    ui->stackedWidget->setCurrentIndex(4);
    ui->line_id->setValidator( new QIntValidator(0, 99999999, this));
    ui->label_distance->setStyleSheet("color:white;");
    QSettings settings(QSettings::IniFormat, QSettings::UserScope,QCoreApplication::organizationName(), QCoreApplication::applicationName());
    ui->Loc_WebBrowser->dynamicCall("Navigate(const QString&)", "https://www.google.com/maps/place/ESPRIT/@36.9016729,10.1713215,15z");
    int ret=A.connect_arduino(); // lancer la connexion à arduino
        switch(ret){
        case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
            break;
        case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
           break;
        case(-1):qDebug() << "arduino is not available";
        }

        ui->tableViewEmployes->setModel(etmp.afficher());

         QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
         //le slot update_label suite à la reception du signal readyRead (reception des données).
}
MainWindow::MainWindow(QString e,QString n,QMainWindow *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    int ret=A.connect_arduino(); // lancer la connexion à arduino
        switch(ret){
        case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
            break;
        case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
           break;
        case(-1):qDebug() << "arduino is not available";
        }

         QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
         //le slot update_label suite à la reception du signal readyRead (reception des données).
          ui->label_distance->setStyleSheet("color:white;");
    QString contenu="Contenu";
    ui->setupUi(this);
    ui->recipient_2->setText(e);
    ui->uname->setText("gestiondesprisesemail@gmail.com");
    ui->passwd_2->setText("vouwnatvsbjucmox");
    ui->passwd_2->setEchoMode(QLineEdit::Password);
    ui->tableView_reservations->setModel(R.afficher());
    ui->tableView_HISTORIQUE->setModel(h.load());
    ui->tableView_HISTORIQUE->resizeColumnsToContents();

}
MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_push_ajouter_clicked()
{
    int ID=ui->line_id->text().toInt();
    QString DISPONIBILITE=ui->comboBox_dispo->currentText();
    int ETAT=ui->line_etat->text().toInt();
    int VOLTAGE=ui->line_voltage->text().toInt();
    Prise P(ID,DISPONIBILITE,ETAT,VOLTAGE);
    bool test=P.ajouter();
    if(test)
    {
        ui->label_info->setText("Ajout effectué");
        ui->comboBox_id->setModel(P.afficher_id());
        ui->tableView->setModel(P.afficher());
    }
    else
    {
        ui->label_info->setText("Ajout non effectué");
    }
}

void MainWindow::on_push_modifier_clicked()
{
    int ID=ui->line_id->text().toInt();
    QString DISPONIBILITE=ui->comboBox_dispo->currentText();
    int ETAT=ui->line_etat->text().toInt();
    int VOLTAGE=ui->line_voltage->text().toInt();
    Prise P(ID,DISPONIBILITE,ETAT,VOLTAGE);
    bool test=P.modifier();
    if(test)
    {
        ui->label_info->setText("Modification effectué");
        ui->comboBox_id->setModel(P.afficher_id());
        ui->tableView->setModel(P.afficher());
    }
    else
    {
        ui->label_info->setText("Modification non effectué");
    }
}

void MainWindow::on_push_supprimer_clicked()
{
    Prise P;
    P.setid(ui->comboBox_id->currentText().toInt());
    bool test=P.supprimer(P.getid());
    if(test)
    {
        ui->label_info->setText("Suppression effectué");
        ui->comboBox_id->setModel(P.afficher_id());
        ui->tableView->setModel(P.afficher());
    }
    else
    {
        ui->label_info->setText("Suppression non effectué");
    }
}

void MainWindow::on_comboBox_id_currentIndexChanged(int)
{
    int id=ui->comboBox_id->currentText().toInt();
    QString id_1=QString::number(id);
    QSqlQuery query;
    query.prepare("SELECT * FROM PRISES where ID_PRISE='"+id_1+"'");
    if(query.exec())
    {
        while (query.next())
        {
            ui->line_id->setText(query.value(0).toString()) ;
            ui->comboBox_dispo->setCurrentText(query.value(1).toString());
            ui->line_etat->setText(query.value(2).toString()) ;
            ui->line_voltage->setText(query.value(3).toString()) ;
        }
    }
    else
    {
        ui->label_info->setText("Echec de chargement");
    }
}

void MainWindow::on_push_triID_clicked()
{
    ui->label_infolist->setText("Tri par ID effectué");
    ui->tableView->setModel(P.tri_id());
}

void MainWindow::on_push_triEtat_clicked()
{
    ui->label_infolist->setText("Tri par Etat effectué");
    ui->tableView->setModel(P.tri_etat());
}

void MainWindow::on_push_triVoltage_clicked()
{
    ui->label_infolist->setText("Tri par Voltage effectué");
    ui->tableView->setModel(P.tri_volt());
}

void MainWindow::on_line_recherche_textChanged(const QString &arg1)
{
    if (ui->radio_id->isChecked()==true)
    {
        P.clearTable(ui->tableView);
        P.chercheID(ui->tableView,arg1);
    }
    if (ui->radio_voltage->isChecked()==true)
    {
        P.clearTable(ui->tableView);
        P.chercheVolt(ui->tableView,arg1);
    }
}

void MainWindow::on_push_ExportPDF_clicked()
{
    QPdfWriter pdf("C:/Users/21620/OneDrive/Documents/gestion des prises/list.pdf");
    QPainter painter(&pdf);
    int i = 4000;
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 30));
    painter.drawPixmap(QRect(100,400,2000,2000),QPixmap("C:/Users/21620/OneDrive/Bureau/2A/SEM2/PC++/logo.png"));
    painter.drawText(3000,1500,"LISTE DES PRISES");
    painter.setPen(Qt::cyan);
    painter.setFont(QFont("Arial", 50));
    painter.drawRect(2700,200,6300,2600);
    painter.drawRect(0,3000,9600,500);
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 9));
    painter.drawText(300,3300,"ID");
    painter.drawText(2300,3300,"Disponibilite");
    painter.drawText(4300,3300,"Etat");
    painter.drawText(5300,3300,"Voltage");
    QSqlQuery query;
    query.prepare("<SELECT CAST( GETDATE() AS Date ) ");
    time_t tt;
    struct tm* ti;
    time(&tt);
    ti=localtime(&tt);
    asctime(ti);
    painter.drawText(500,300, asctime(ti));
    query.prepare("select * from PRISES");
    query.exec();
    while (query.next())
    {
        painter.drawText(300,i,query.value(0).toString());
        painter.drawText(2300,i,query.value(1).toString());
        painter.drawText(4300,i,query.value(2).toString());
        painter.drawText(5300,i,query.value(3).toString());
        i = i +500;
    }
    int reponse = QMessageBox::question(this, "PDF généré", "Afficher le PDF ?", QMessageBox::Yes |  QMessageBox::No);
    if (reponse == QMessageBox::Yes)
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/21620/OneDrive/Documents/gestion des prises/list.pdf"));
        painter.end();
    }
    if (reponse == QMessageBox::No)
    {
        painter.end();
    }
}

void MainWindow::on_envoyer_dialog_2_clicked()
{
    QString status;
    Smtp* smtp = new Smtp(ui->uname->text(), ui->passwd_2->text(), "smtp.gmail.com", 465); //smtp.gmail.com
    smtp->sendMail(ui->uname->text(), ui->recipient_2->text() , ui->subjectLineEdit_2->text() ,ui->message_2->toPlainText());
    if(status == "Message sent")
        QMessageBox::warning( 0, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
}

void MainWindow::on_push_stats_clicked()
{

}



void MainWindow::on_pushButton_on_clicked()
{
    QByteArray donnee="1";
    A.write_to_arduino(donnee);
}

void MainWindow::on_pushButton_off_clicked()
{
    QByteArray donnee="0";
    A.write_to_arduino(donnee);
}

void MainWindow::on_label_distance_linkActivated(const QString &link)
{
    data=A.read_from_arduino();
    ui->label_distance->setText(data);


}

void   MainWindow::update_label()
{
     data=A.read_from_arduino();
    if(data=="5" || data=="6")
    {
         ui->label_distance->setText("0");
    }
    else {
        ui->label_distance->setText(data);
    }

}

void MainWindow::on_ajoutedis_clicked()
{
    int data = ui->label_distance->text().toInt();
    Prise P;
    P.setid(ui->iddis->text().toInt());
    P.ajouter_distance(data);
}
void MainWindow::on_pushButton_4_clicked()
{
    ui->voiture_stacked_widget->setCurrentIndex(2);
    ui->table_afficher->setModel(V.afficher_voiture());

}

void MainWindow::on_pushButton_5_clicked()
{
    ui->voiture_stacked_widget->setCurrentIndex(0);
}

void MainWindow::on_return_from_afficher_clicked()
{
    ui->voiture_stacked_widget->setCurrentIndex(3);
}

void MainWindow::on_return_from_modifier_clicked()
{
    ui->voiture_stacked_widget->setCurrentIndex(2);
    ui->table_afficher->setModel(V.afficher_voiture());
}

void MainWindow::on_return_from_ajout_clicked()
{
    ui->voiture_stacked_widget->setCurrentIndex(3);
}
void MainWindow::return_data_going_update(int id)
{
    QSqlQuery query=V.return_data(id);
    if(query.exec() && query.numRowsAffected())
        {

        while (query.next()) {
            QString mat=query.value(0).toString();
            ui->matricule_3->setText(mat);
            QString marque=query.value(1).toString();
            ui->marque_3->setText(marque);
            QString prop=query.value(2).toString();
            ui->prop_3->setText(prop);
            int etat=query.value(3).toUInt();
            if(etat==0)
            {ui->etat->setText("non charger");}
            else if(etat==1)
            {ui->etat_3->setText("charger");}
        }
    }
}
void MainWindow::on_modifier_table_clicked()
{
    int id;
    id=getting_id_selected();

    return_data_going_update(id);

    ui->voiture_stacked_widget->setCurrentIndex(1);
}
void MainWindow::renderQMessageBox(QString title,QString message)
{
    QMessageBox msgBox;
    msgBox.setText(message);
    msgBox.setWindowTitle(title);
    msgBox.setIcon(QMessageBox::Information);
    msgBox.exec();
}
void MainWindow::on_pushButton_clicked()
{
    int mat=ui->matricule->text().toInt();
    V.matricule=mat;
    V.marque=ui->marque->text();
    V.prop=ui->prop->text();
    if(ui->etat->text()=="non charger")
    {V.etat=0;}
    else if(ui->etat->text()=="charger")
        {V.etat=1;}
    bool test=V.ajout_voiture(V);
    if(test)
    {
        ui->voiture_stacked_widget->setCurrentIndex(3);}
    else
    {renderQMessageBox("Ajout","failed");}

}

int MainWindow::getting_id_selected()
{
    QItemSelectionModel *selectionModel = ui->table_afficher->selectionModel();
    QModelIndex selectedIndex = selectionModel->currentIndex();
    QVariant cellData = V.afficher_voiture()->data(V.afficher_voiture()->index(selectedIndex.row(), 0));
    return cellData.toInt();
}



void MainWindow::on_supprimer_table_clicked()
{
    int id;
    id=getting_id_selected();
    bool test=V.supprimer_voiture(id);
    if(test)
    { ui->table_afficher->setModel(V.afficher_voiture());}
    else
    {renderQMessageBox("Supprimer","failed");}
}

void MainWindow::on_pushButton_3_clicked()
{
    int etatv=-1;
    int mat;
    mat=ui->matricule_3->text().toInt();
    QString marque=ui->marque_3->text();
    QString prop=ui->prop_3->text();
    if(ui->etat_3->text()=="non charger")
    {etatv=0;}
    else if(ui->etat_3->text()=="charger")
        {etatv=1;}
    bool test=V.modifier_voiture(mat,etatv,marque,prop);
    if(test)
    {ui->voiture_stacked_widget->setCurrentIndex(2);
    ui->table_afficher->setModel(V.afficher_voiture());}
    else
    {renderQMessageBox("Update","failed");}

}

void MainWindow::on_generate_pdf_clicked()
{



    QString strStream;
        QTextStream out(&strStream);

         const int rowCount = ui->table_afficher->model()->rowCount();
         const int columnCount = ui->table_afficher->model()->columnCount();
        out <<  "<html>\n"
        "<head>\n"
                         "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                         <<  QString("<title>%1</title>\n").arg("strTitle")
                         <<  "</head>\n"
                         "<body bgcolor=#ffffff link=#5000A0>\n"
                            " <center><img width='200' height='100' src='C:/Users/MSI/Desktop/logo.png' style='position:absolute;top:20px;right:20px;width:5px;height:5px;'>"

                        //     "<align='right'> " << datefich << "</align>"

                         "<center> <H1>Liste des Reservations</H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

                     // headers
                     out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
                     out<<"<cellspacing=10 cellpadding=3>";
                     for (int column = 0; column < columnCount; column++)
                         if (!ui->table_afficher->isColumnHidden(column))
                             out << QString("<th>%1</th>").arg(ui->table_afficher->model()->headerData(column, Qt::Horizontal).toString());
                     out << "</tr></thead>\n";

                     // data table
                     for (int row = 0; row < rowCount; row++) {
                         out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                         for (int column = 0; column < columnCount; column++) {
                             if (!ui->table_afficher->isColumnHidden(column)) {
                                 QString data = ui->table_afficher->model()->data(ui->table_afficher->model()->index(row, column)).toString().simplified();
                                 out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                             }
                         }
                         out << "</tr>\n";
                     }
                     out <<  "</table> </center>\n"
                         "</body>\n"
                         "</html>\n";

               QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Sauvegarder en PDF", QString(), "*.pdf");
                 if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

                QPrinter printer (QPrinter::PrinterResolution);
                 printer.setOutputFormat(QPrinter::PdfFormat);
                printer.setPaperSize(QPrinter::A4);
               printer.setOutputFileName(fileName);




                QTextDocument doc;
                 doc.setHtml(strStream);
                 doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
                 doc.print(&printer);

    }
void MainWindow::on_pushButton_2_clicked()
{
    ui->table_afficher->setModel(V.afficher_trier());
}



void MainWindow::on_recherche_textChanged(const QString &arg1)
{
    if(ui->recherche->text()=="")
    {
        ui->table_afficher->setModel(V.afficher_voiture());
    }
    else
    {
        QString r=ui->recherche->text();
        ui->table_afficher->setModel(V.afficher_recherche(r));
    }
}

void MainWindow::on_pushButton_6_clicked()
{
    int e1=V.return_info_etat(-1);
    int e2=V.return_info_etat(1);
    V.stat(e1,e2,ui->pdf_widget);
    ui->table_afficher->setModel(V.afficher_voiture());
}
void MainWindow::generateQRCode(int mat, QString marq , QString prop, int etat)
{
    ui->voiture_stacked_widget->setCurrentIndex(5);
    QString equipmentInfo = QString("mat: %1\nmarq: %2\nProp : %3\nEtat : %4\n").arg(mat).arg(marq).arg(prop).arg(etat);
    QImage qrCodeImage = QZXing::encodeData(equipmentInfo.toUtf8(), QZXing::EncoderFormat_QR_CODE, QSize(200, 200));
    QPixmap qrCodePixmap = QPixmap::fromImage(qrCodeImage);

    // Find the label object within the current page of the stacked widget
    QLabel *qrCodeLabel = ui->voiture_stacked_widget->currentWidget()->findChild<QLabel*>("qrCodeLabel");

    if (qrCodeLabel) {
        qrCodeLabel->setPixmap(qrCodePixmap);
    }
}
void MainWindow::on_pushButton_7_clicked()
{

    QSqlQuery query;

        int id=ui->matricule->text().toInt();
        query.prepare("SELECT * FROM VOITURES WHERE MATRICULE = :id");
        query.bindValue(":id", id);
        if (!query.exec() || !query.next()) {
            qInfo()<<"erreur"; // Equipment with the given ID not found
        }
            int mat = query.value("MATRICULES").toInt();
            QString marq = query.value("MARQUES").toString();
            QString prop = query.value("PROPRIETAIRE").toString();
            int etat = query.value("ETAT").toInt();


     generateQRCode(mat,marq,prop,etat);

}

void MainWindow::on_pushButton_8_clicked()
{


        QString fileName = QFileDialog::getSaveFileName((QWidget*)0, "Exporter EXCEL", QString(), "*.csv");
        if (QFileInfo(fileName).suffix().isEmpty()) {
            fileName.append(".csv");
        }

        QFile data(fileName);
        if (data.open(QFile::WriteOnly)) {
            QTextStream output(&data);
            output << "MATRICULES" << "," << "MARQUE" << "," << "PROPRIETAIRE" << "," << "ETAT" << '\n';
            for (int i = 0; i < ui->table_afficher->model()->rowCount(); i++) {
                for (int j = 0; j < ui->table_afficher->model()->columnCount(); j++) {
                    QString value = ui->table_afficher->model()->index(i, j).data().toString();
                    output << value << ",";
                    if(j==3){
                        output << value << '\n';
                    }


                }
            }
            data.close();
        }
    }

void MainWindow::on_Menu_Prises_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_Menu_Voiture_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_return_from_ajout_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
void MainWindow::Prises_choix_pie(){
    QChartView *chartView ;
    QSqlQuery q1,q2,q3,q4;
    qreal tot=0,c1=0,c2=0,c3=0;
    q1.prepare("SELECT * FROM PRISES");
    q1.exec(); q2.prepare("SELECT VOLTAGE FROM Prises WHERE VOLTAGE < 120;");
    q2.exec(); q3.prepare("SELECT VOLTAGE FROM Prises WHERE VOLTAGE BETWEEN 120 AND 220;");
    q3.exec(); q4.prepare("SELECT VOLTAGE FROM Prises WHERE VOLTAGE > 220;");
    q4.exec();
    while (q1.next()){tot++;}
    while (q2.next()){c1++;}
    while (q3.next()){c2++;}
    while (q4.next()){c3++;}
    c1=c1/tot; c2=c2/tot; c3=c3/tot;
    QPieSeries *series = new QPieSeries();
    series->append("120<",c1);
    series->append("120-220",c2);
    series->append(">220",c3);
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->legend()->show();
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->setTheme(QChart::ChartThemeQt);
    chartView = new QChartView(chart,ui->Label_Stats);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(570,570);
    chartView->show();
}
void MainWindow::on_push_UpdateStats_clicked()
{
    Prises_choix_pie();
    show();
}

void MainWindow::on_Menu_Voiture_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}



void MainWindow::on_dateEdit_dateChanged(const QDate &date)
{
    ui->comboBox_nprise->setModel(R.prises(date));
    ui->tableView->setModel(R.prises(date));
}

void MainWindow::on_pushButton_Reserver_2_clicked()
{
    // Récupération de l'identifiant de la ligne sélectionnée
    QModelIndex index = ui->tableView_reservations->currentIndex();
    int id_reservation = index.sibling(index.row(), 0).data().toInt(); // On supposant que l'identifiant est dans la première colonne

    // Récupération des nouvelles valeurs
    QDate datee = ui->dateEdit_2->date();
    int numprise = ui->comboBox_nprise_2->currentText().toInt();
    QString matricule = ui->lineEdit_matricule_2->text();

    // Vérification de la validité de la saisie
    if (datee.isNull() || numprise <= 0 || matricule.isEmpty()) {
        QMessageBox::critical(this, "Erreur de saisie", "Veuillez remplir tous les champs.");
        return;
    }

    Reservation newR(id_reservation, numprise, matricule, datee);

    // Appel de newR.modifier() et affichage du résultat dans un QMessageBox
    if (newR.modifier()) {
        QMessageBox::information(this, "Réservation modifiée", "La réservation a été modifiée avec succès.");
        N.notification_modifierReservation();

        int id=ui->tableView_reservations->model()->data(ui->tableView_reservations->model()->index(ui->tableView_reservations->currentIndex().row(),0)).toInt();
        int numprise = ui->comboBox_nprise->currentText().toInt();
        QString matricule = ui->lineEdit_matricule->text();
        h.save(id,matricule,numprise,"Modifier");
       // ui->historique_2->setText(h.load());

        N.notification_modifierReservation();

        ui->tableView_reservations->setModel(R.afficher()); // refresh affichage

    } else {
        QMessageBox::critical(this, "Erreur", "Une erreur s'est produite lors de la modification de la réservation.");
    }
}

void MainWindow::on_lineEdit_rechercher_returnPressed()
{

    if(ui->lineEdit_rechercher->text()!="")
    {        //QString b=ui->comboBox_recherche_Publicite_2->currentText();
        QString a=ui->lineEdit_rechercher->text();
        ui->tableView_reservations->setModel(R.displayClause("WHERE (ID_RESERVATION LIKE '%"+a+"%' OR DATE_RESERVATION LIKE '%"+a+"%' OR ID_PRISE LIKE '%"+a+"%' OR MATRICULE LIKE '%"+a+"%' ) "));
    }
    else
        ui->tableView_reservations->setModel(R.afficher());
}

void MainWindow::on_radioButton_desc_clicked()
{
    ui->tableView_reservations->setModel(R.trideccroissant());

}

void MainWindow::on_radioButton_asc_clicked()
{
    ui->tableView_reservations->setModel(R.tricroissant());

}

void MainWindow::on_radioButton_asc_2_clicked()
{
     ui->tableView_reservations->setModel(R.tri());
}

void MainWindow::on_tableView_reservations_clicked(const QModelIndex &index)
{
    ui->lineEdit_matricule_2->setText(ui->tableView_reservations->model()->data(ui->tableView_reservations->model()->index(ui->tableView_reservations->currentIndex().row(),3)).toString());

}

void MainWindow::on_pushButton_supprimer_clicked()
{
    if(ui->tableView_reservations->currentIndex().row()==-1)
        QMessageBox::information(nullptr, QObject::tr("Suppression"),
                                 QObject::tr("Veuillez Choisir une reservation du Tableau.\n"
                                             "Click Ok to exit."), QMessageBox::Ok);
    else
    {   int id=ui->tableView_reservations->model()->data(ui->tableView_reservations->model()->index(ui->tableView_reservations->currentIndex().row(),0)).toInt();
        //Promotion p(ui->afficher_promo->model()->data(ui->afficher_promo->model()->index(ui->afficher_promo->currentIndex().row(),0)).toString(),ui->afficher_promo->model()->data(ui->afficher_promo->model()->index(ui->afficher_promo->currentIndex().row(),1)).toString(),ui->afficher_promo->model()->data(ui->afficher_promo->model()->index(ui->afficher_promo->currentIndex().row(),2)).toInt(),ui->afficher_promo->model()->data(ui->afficher_promo->model()->index(ui->afficher_promo->currentIndex().row(),3)).toDate(),ui->afficher_promo->model()->data(ui->afficher_promo->model()->index(ui->afficher_promo->currentIndex().row(),4)).toString());



        QString str = " Vous voulez vraiment supprimer \n la reservation :";
        int ret = QMessageBox::question(this, tr("reservation"),str,QMessageBox::Ok|QMessageBox::Cancel);

        switch (ret) {
        case QMessageBox::Ok:
            if (R.supprimer(id)){

                N.notification_supprimerReservation();

                QMessageBox::information(0, qApp->tr("Suppression"),

                                         qApp->tr("reservation suprimée"), QMessageBox::Ok);
                int numprise = ui->comboBox_nprise->currentText().toInt();
                QString matricule = ui->lineEdit_matricule->text();
                h.save(id,matricule,numprise,"Supprimer");
                ui->tableView_HISTORIQUE->setModel(h.load());
                ui->tableView_HISTORIQUE->resizeColumnsToContents();




            }
            else
            {

                QMessageBox::critical(0, qApp->tr("Suppression"),
                                      qApp->tr("reservation non trouvé "), QMessageBox::Ok);
            }



            break;
        case QMessageBox::Cancel:

            break;
        default:
            // should never be reached
            break;
        }


    }
ui->tableView_reservations->setModel(R.afficher());
}

QT_CHARTS_USE_NAMESPACE
void MainWindow::on_pushButton_stat_clicked()
{
    QT_CHARTS_USE_NAMESPACE


        // Create a QSqlQueryModel object for the results of the query
        // Create a QSqlQueryModel object for the results of the query
        QSqlQueryModel *model = new QSqlQueryModel();

        // Set the query to retrieve the count of reservations grouped by prise
        QString query = "SELECT prises.ID_PRISE, COUNT(reservation.id_reservation)  FROM reservation JOIN prises ON reservation.id_prise = prises.id_prise GROUP BY prises.id_prise";
        model->setQuery(query);

        // Create a QPieSeries object and add slices for each prise
        QPieSeries *series = new QPieSeries();
        float totalCount = 0;
        for (int i = 0; i < model->rowCount(); ++i) {
            QString priseName = model->record(i).value("ID").toString();
            float count = model->record(i).value(1).toFloat();
            totalCount += count;
            QString label = priseName + " (" + QString::number(count) +")";
            series->append(label, count);
        }

        // Create a QChart object and add the series to it
        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("Réservations par prise");

        // Create a QChartView object to display the chart
        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);
        chartView->resize(1000, 500);
        chartView->show();

    }

    void MainWindow::on_pushButton_Reserver_clicked()
    {
        QDate datee = ui->dateEdit->date();
        int numprise = ui->comboBox_nprise->currentText().toInt();
        QString matricule = ui->lineEdit_matricule->text();

        // Vérification de la validité de la saisie
        if (datee.isNull() || numprise <= 0 || matricule.isEmpty()) {
            QMessageBox::critical(this, "Erreur de saisie", "Veuillez remplir tous les champs.");
            return;
        }

        Reservation newR(0, numprise, matricule, datee);

        // Appel de newR.ajouter() et affichage du résultat dans un QMessageBox
        if (newR.ajouter()) {
            QMessageBox::information(this, "Réservation ajoutée", "La réservation a été ajoutée avec succès.");
    /*
            int id=ui->tableView_reservations->model()->data(ui->tableView_reservations->model()->index(ui->tableView_reservations->currentIndex().row(),0)).toInt();
            h.save(id,matricule,numprise,"Ajout");
           //ui->tableView_HISTORIQUE->setText(h.load());
            //ui->tableView_HISTORIQUE->setModel(h.load());
    */



            ui->tableView_reservations->setModel(R.afficher()); // refresh affichage
             N.notification_ajoutReservation();

        } else {
            QMessageBox::critical(this, "Erreur", "Une erreur s'est produite lors de l'ajout de la réservation.");
        }


}

void MainWindow::on_pushButton_pdf_clicked()
{
    QString strStream;
        QTextStream out(&strStream);

         const int rowCount = ui->tableView_reservations->model()->rowCount();
         const int columnCount = ui->tableView_reservations->model()->columnCount();
        out <<  "<html>\n"
        "<head>\n"
                         "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                         <<  QString("<title>%1</title>\n").arg("strTitle")
                         <<  "</head>\n"
                         "<body bgcolor=#ffffff link=#5000A0>\n"
                            " <center><img src=':/logo.png' style='position:absolute;top:20px;right:20px;width:5px;height:5px;'>"

                        //     "<align='right'> " << datefich << "</align>"

                         "<center> <H1>Liste des Reservations</H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

                     // headers
                     out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
                     out<<"<cellspacing=10 cellpadding=3>";
                     for (int column = 0; column < columnCount; column++)
                         if (!ui->tableView_reservations->isColumnHidden(column))
                             out << QString("<th>%1</th>").arg(ui->tableView_reservations->model()->headerData(column, Qt::Horizontal).toString());
                     out << "</tr></thead>\n";

                     // data table
                     for (int row = 0; row < rowCount; row++) {
                         out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                         for (int column = 0; column < columnCount; column++) {
                             if (!ui->tableView_reservations->isColumnHidden(column)) {
                                 QString data = ui->tableView_reservations->model()->data(ui->tableView_reservations->model()->index(row, column)).toString().simplified();
                                 out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                             }
                         }
                         out << "</tr>\n";
                     }
                     out <<  "</table> </center>\n"
                         "</body>\n"
                         "</html>\n";

               QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Sauvegarder en PDF", QString(), "*.pdf");
                 if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

                QPrinter printer (QPrinter::PrinterResolution);
                 printer.setOutputFormat(QPrinter::PdfFormat);
                printer.setPaperSize(QPrinter::A4);
               printer.setOutputFileName(fileName);




                QTextDocument doc;
                 doc.setHtml(strStream);
                 doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
                 doc.print(&printer);

}

void MainWindow::on_dateEdit_2_dateChanged(const QDate &date)
{
    ui->comboBox_nprise_2->setModel(R.prises(date));

}

void MainWindow::on_pushButton_9_clicked()
{
    QString email = ui->email->text();
    QString password = ui->password->text();
    if (etmp.autentifier(email,password)){
        QMessageBox::information(nullptr, QObject::tr("ok"),
                        QObject::tr("authentification successful !\n""Click Cancel to exit."), QMessageBox::Cancel);
        ui->stackedWidget->setCurrentIndex(0);
        ui->return_from_ajout_2->setVisible(true);
        ui->return_from_ajout_3->setVisible(true);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("non"),
                        QObject::tr("invalid credentials !\n""Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_Menu_Voiture_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_btnAjoutEmploye_clicked()
{
    QRegularExpression regex("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    QRegularExpressionMatch match = regex.match(ui->leEmailEmploye->text());
    if (ui->leNomEmploye->text().isEmpty() || ui->lePrenomEmploye->text().isEmpty() || ui->leEmailEmploye->text().isEmpty() || ui->leMdpEmploye->text().isEmpty())
    {
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                         QObject::tr("Remplir tout les champs\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else if (! match.hasMatch())
    {
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                         QObject::tr("Email non valide ! \n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);
    }

    else
    {
    etmp.setNom(ui->leNomEmploye->text());
    etmp.setPrenom(ui->lePrenomEmploye->text());
    etmp.setEmail(ui->leEmailEmploye->text());
    etmp.setPassword(ui->leMdpEmploye->text());
    etmp.setRole(ui->cbRoleEmploye->currentText());


    bool test = etmp.ajouter();
    if (test )
    {
        ui->tableViewEmployes->setModel(etmp.afficher());
        QMessageBox::information(nullptr, QObject::tr("ok"),
                        QObject::tr("ajout effectué\n""Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                         QObject::tr("ajout non effectué\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);
    }
    }
}

void MainWindow::on_btnAnnulerEmploye_clicked()
{
    ui->leNomEmploye->clear();
    ui->lePrenomEmploye->clear();
    ui->leMdpEmploye->clear();
    ui->leEmailEmploye->clear();
    ui->cbRoleEmploye->setCurrentText("Admin");
}

void MainWindow::on_line_research_textChanged(const QString &arg1)
{
    ui->tableViewEmployes->setModel(etmp.recherche(arg1));
}

void MainWindow::on_pushButton_sort_clicked()
{
    QString champ = "id" ;
    QString order = "asc";
    qDebug() << ui->comboBoxsortchamp->currentText() ;
   if (ui->comboBoxsortchamp->currentText().compare("Nom") == 0)
    {
        champ = "nom";
    }
    else if (ui->comboBoxsortchamp->currentText().compare("Email") == 0)
    {
        champ = "email";
    }
    if (ui->comboBox_order->currentText().compare("Descendant") == 0 )
    {
        order = "desc";
    }

    ui->tableViewEmployes->setModel(etmp.Tri(order,champ));
}

void MainWindow::on_btnModifierEmployeSelect_clicked()
{

    int id = ui->tableViewEmployes->model()->data(ui->tableViewEmployes->model()->index(ui->tableViewEmployes->currentIndex().row(),0)).toInt();
    if (! ui->tableViewEmployes->currentIndex().isValid())
    {
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                         QObject::tr("Selectionnez un employé pour le modifier\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        etmp.setID(id);
        ui->tabWidgetEmploye->setCurrentIndex(1);
        ui->leNomEmployeModif->setText(ui->tableViewEmployes->model()->data(ui->tableViewEmployes->model()->index(ui->tableViewEmployes->currentIndex().row(),1)).toString());
        ui->lePrenomEmployeModif->setText(ui->tableViewEmployes->model()->data(ui->tableViewEmployes->model()->index(ui->tableViewEmployes->currentIndex().row(),2)).toString());
        ui->leEmailEmployeModif->setText(ui->tableViewEmployes->model()->data(ui->tableViewEmployes->model()->index(ui->tableViewEmployes->currentIndex().row(),3)).toString());
        ui->leMdpEmployeModif->setText(ui->tableViewEmployes->model()->data(ui->tableViewEmployes->model()->index(ui->tableViewEmployes->currentIndex().row(),4)).toString());
        ui->cbRoleEmployeModif->setCurrentText(ui->tableViewEmployes->model()->data(ui->tableViewEmployes->model()->index(ui->tableViewEmployes->currentIndex().row(),5)).toString());
    }

}

void MainWindow::on_btnSupprimerEmploye_clicked()
{
    int id = ui->tableViewEmployes->model()->data(ui->tableViewEmployes->model()->index(ui->tableViewEmployes->currentIndex().row(),0)).toInt();
    if (! ui->tableViewEmployes->currentIndex().isValid())
    {
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                         QObject::tr("Selectionnez un employé pour le supprimer\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else {
       bool test = etmp.supprimer(id);
        if (test)
        {
            ui->tableViewEmployes->setModel(etmp.afficher());
            QMessageBox::information(nullptr, QObject::tr("ok"),
                            QObject::tr("Employé supprimé !\n""Click Cancel to exit."), QMessageBox::Cancel);
        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("not ok"),
                             QObject::tr("suppression non effectué\n"
                                         "Click Cancel to exit."), QMessageBox::Cancel);
        }

    }

}

void MainWindow::on_pushButton_pdfEmploye_clicked()
{
    QPdfWriter pdf("test5.pdf");
               QPainter painter(&pdf);
               int i = 4000;
               painter.setPen(Qt::red);
               painter.setFont(QFont("Arial", 30));
               painter.drawText(2800,1200,"Liste des Employés");
               painter.setPen(Qt::black);
               painter.setFont(QFont("Arial", 50));
               painter.drawRect(1500,200,7300,2600);
               painter.drawRect(0,3000,9600,500);
               painter.setFont(QFont("Arial", 9));
               painter.drawText(1300,3300,"ID");
               painter.drawText(2600,3300,"Nom");
               painter.drawText(3900,3300,"Prenom");
               painter.drawText(5200,3300,"Email");
               QImage image("‪:/logo.png");
               painter.drawImage(10,10, image);

               QSqlQuery query;
               query.prepare("select * from employes");
               query.exec();
               while (query.next())
               {
                   painter.drawText(1300,i,query.value(0).toString());
                   painter.drawText(2600,i,query.value(1).toString());
                   painter.drawText(3900,i,query.value(2).toString());
                   painter.drawText(5200,i,query.value(3).toString());
                   i = i +500;
               }

               int reponse = QMessageBox::question(this, "Génerer PDF", "Vous Voulez Affichez Le PDF ?", QMessageBox::Yes |  QMessageBox::No);
               if (reponse == QMessageBox::Yes)
               {
                   QDesktopServices::openUrl(QUrl::fromLocalFile("test5.pdf"));

                   painter.end();
               }
               if (reponse == QMessageBox::No)
               {
                   painter.end();
               }
}

void MainWindow::on_pushButton_statEmploye_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("SELECT role FROM employes WHERE role='Admin' ");
        float countadmin=model->rowCount();
        model->setQuery("SELECT role FROM employes WHERE role='Gestion1' ");
        float count1=model->rowCount();
        model->setQuery("SELECT role FROM employes WHERE role='Gestion2' ");
        float count2=model->rowCount();
        model->setQuery("SELECT role FROM employes WHERE role='Gestion3' ");
        float count3=model->rowCount();
        model->setQuery("SELECT role FROM employes WHERE role='Gestion4' ");
        float count4=model->rowCount();
        model->setQuery("SELECT role FROM employes WHERE role='Gestion5' ");
        float count5=model->rowCount();

        float total=countadmin+count1+count2+count3+count4+count5;

                QPieSeries *series = new QPieSeries();
                series->append("Admin",countadmin);
                series->append("Gestion1",count1);
                series->append("Gestion2",count2);
                series->append("Gestion3",count3);
                series->append("Gestion4",count4);
                series->append("Gestion5",count5);

                if (countadmin!=0)
                {QPieSlice *slice = series->slices().at(0);
                    slice->setLabel("Admin "+QString("%1%").arg(100*slice->percentage(),3,'f',1));
                    slice->setLabelVisible();
                    slice->setPen(QPen(Qt::black));}
                if ( count1!=0)
                {
                    // Add label, explode and define brush for 2nd slice
                    QPieSlice *slice1 = series->slices().at(1);
                    //slice1->setExploded();
                    slice1->setLabel("Gestion1 "+QString("%1%").arg(100*slice1->percentage(),3,'f',1));
                    slice1->setLabelVisible();
                    slice1->setBrush(QColor(Qt::cyan));
                }
                if ( count2!=0)
                {
                    // Add label, explode and define brush for 2nd slice
                    QPieSlice *slice1 = series->slices().at(2);
                    //slice1->setExploded();
                    slice1->setLabel("Gestion2 "+QString("%1%").arg(100*slice1->percentage(),3,'f',1));
                    slice1->setLabelVisible();
                    slice1->setBrush(QColor(Qt::red));
                }
                if ( count3!=0)
                {
                    // Add label, explode and define brush for 2nd slice
                    QPieSlice *slice1 = series->slices().at(3);
                    //slice1->setExploded();
                    slice1->setLabel("Gestion3 "+QString("%1%").arg(100*slice1->percentage(),3,'f',1));
                    slice1->setLabelVisible();
                    slice1->setBrush(QColor(Qt::green));
                }
                if ( count4!=0)
                {
                    // Add label, explode and define brush for 2nd slice
                    QPieSlice *slice1 = series->slices().at(4);
                    //slice1->setExploded();
                    slice1->setLabel("Gestion4 "+QString("%1%").arg(100*slice1->percentage(),3,'f',1));
                    slice1->setLabelVisible();
                    slice1->setBrush(QColor(Qt::yellow));
                }
                if ( count5!=0)
                {
                    // Add label, explode and define brush for 2nd slice
                    QPieSlice *slice1 = series->slices().at(5);
                    //slice1->setExploded();
                    slice1->setLabel("Gestion5 "+QString("%1%").arg(100*slice1->percentage(),3,'f',1));
                    slice1->setLabelVisible();
                    slice1->setBrush(QColor(Qt::blue));
                }



                // Create the chart widget
                QChart *chart = new QChart();
                // Add data to chart with title and hide legend
                chart->addSeries(series);
                chart->setTitle("Totale "+ QString::number(total));

                // Used to display the chart
                QChartView *chartView = new QChartView(chart);
                chartView->setRenderHint(QPainter::Antialiasing);
                chartView->resize(1000,500);


                chart->legend()->hide();
                chartView->show();
}

void MainWindow::on_btnModifierEmploye_clicked()
{
    QRegularExpression regex("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    QRegularExpressionMatch match = regex.match(ui->leEmailEmployeModif->text());
    if ( ui->leNomEmployeModif->text().isEmpty() || ui->lePrenomEmployeModif->text().isEmpty() || ui->leEmailEmployeModif->text().isEmpty() || ui->leMdpEmployeModif->text().isEmpty())
    {
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                         QObject::tr("Remplir tout les champs !\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else if ( ! match.hasMatch())
    {
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                         QObject::tr("Email non valide ! \n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
    etmp.setNom(ui->leNomEmployeModif->text());
    etmp.setPrenom(ui->lePrenomEmployeModif->text());
    etmp.setEmail(ui->leEmailEmployeModif->text());
    etmp.setPassword(ui->leMdpEmployeModif->text());
    etmp.setRole(ui->cbRoleEmployeModif->currentText());

    bool test = etmp.modifier();
    if (test)
    {
        ui->tableViewEmployes->setModel(etmp.afficher());
        ui->tabWidgetEmploye->setCurrentIndex(0);
        QMessageBox::information(nullptr, QObject::tr("ok"),
                        QObject::tr("Employé modifié !\n""Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                         QObject::tr("modification non effectué\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);
    }
    }
}

void MainWindow::on_return_from_ajout_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
    ui->return_from_ajout_2->setVisible(false);
    ui->return_from_ajout_3->setVisible(false);
}
