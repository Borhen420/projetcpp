#include "voiture.h"
#include "ui_voiture.h"
#include "dbconnect.h"
#include "main_voiture.h"
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



voiture::voiture(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::voiture)
{
    ui->setupUi(this);
    ui->voiture_stacked_widget->setCurrentIndex(3);

}



voiture::~voiture()
{
    delete ui;
}

QWidget *voiture::return_ui()
{
    return ui->voiture_stacked_widget;
}

void voiture::on_pushButton_4_clicked()
{
    main_voiture v;
    ui->voiture_stacked_widget->setCurrentIndex(2);
    ui->table_afficher->setModel(v.afficher_voiture());

}

void voiture::on_pushButton_5_clicked()
{
    ui->voiture_stacked_widget->setCurrentIndex(0);
}

void voiture::on_return_from_afficher_clicked()
{
    ui->voiture_stacked_widget->setCurrentIndex(3);
}

void voiture::on_return_from_modifier_clicked()
{   main_voiture v;
    ui->voiture_stacked_widget->setCurrentIndex(2);
    ui->table_afficher->setModel(v.afficher_voiture());
}

void voiture::on_return_from_ajout_clicked()
{
    ui->voiture_stacked_widget->setCurrentIndex(3);
}
void voiture::return_data_going_update(int id)
{
    main_voiture v;
    QSqlQuery query=v.return_data(id);
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
void voiture::on_modifier_table_clicked()
{
    int id;
    id=getting_id_selected();

    return_data_going_update(id);

    ui->voiture_stacked_widget->setCurrentIndex(1);
}
void voiture::renderQMessageBox(QString title,QString message)
{
    QMessageBox msgBox;
    msgBox.setText(message);
    msgBox.setWindowTitle(title);
    msgBox.setIcon(QMessageBox::Information);
    msgBox.exec();
}
void voiture::on_pushButton_clicked()
{
    main_voiture v;
    int mat=ui->matricule->text().toInt();
    v.matricule=mat;
    v.marque=ui->marque->text();
    v.prop=ui->prop->text();
    if(ui->etat->text()=="non charger")
    {v.etat=0;}
    else if(ui->etat->text()=="charger")
        {v.etat=1;}
    bool test=v.ajout_voiture(v);
    if(test)
    {
        ui->voiture_stacked_widget->setCurrentIndex(3);}
    else
    {renderQMessageBox("Ajout","failed");}

}

int voiture::getting_id_selected()
{
    main_voiture v;
    QItemSelectionModel *selectionModel = ui->table_afficher->selectionModel();
    QModelIndex selectedIndex = selectionModel->currentIndex();
    QVariant cellData = v.afficher_voiture()->data(v.afficher_voiture()->index(selectedIndex.row(), 0));
    return cellData.toInt();
}



void voiture::on_supprimer_table_clicked()
{
    main_voiture v;
    int id;
    id=getting_id_selected();
    bool test=v.supprimer_voiture(id);
    if(test)
    { ui->table_afficher->setModel(v.afficher_voiture());}
    else
    {renderQMessageBox("Supprimer","failed");}
}

void voiture::on_pushButton_3_clicked()
{
    main_voiture v;
    int etatv=-1;
    int mat;
    mat=ui->matricule_3->text().toInt();
    QString marque=ui->marque_3->text();
    QString prop=ui->prop_3->text();
    if(ui->etat_3->text()=="non charger")
    {etatv=0;}
    else if(ui->etat_3->text()=="charger")
        {etatv=1;}
    bool test=v.modifier_voiture(mat,etatv,marque,prop);
    if(test)
    {ui->voiture_stacked_widget->setCurrentIndex(2);
    ui->table_afficher->setModel(v.afficher_voiture());}
    else
    {renderQMessageBox("Update","failed");}

}

void voiture::on_generate_pdf_clicked()
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
void voiture::on_pushButton_2_clicked()
{
    main_voiture v;

    ui->table_afficher->setModel(v.afficher_trier());
}



void voiture::on_recherche_textChanged(const QString &arg1)
{
    main_voiture v;
    if(ui->recherche->text()=="")
    {
        ui->table_afficher->setModel(v.afficher_voiture());
    }
    else
    {
        QString r=ui->recherche->text();
        ui->table_afficher->setModel(v.afficher_recherche(r));
    }
}

void voiture::on_pushButton_6_clicked()
{
    main_voiture v;
    int e1=v.return_info_etat(-1);
    int e2=v.return_info_etat(1);
    v.stat(e1,e2,ui->pdf_widget);
    ui->table_afficher->setModel(v.afficher_voiture());
}
void voiture::generateQRCode(int mat, QString marq , QString prop, int etat)
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
void voiture::on_pushButton_7_clicked()
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

void voiture::on_pushButton_8_clicked()
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

