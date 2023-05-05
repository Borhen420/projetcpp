#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidgetEmploye->setCurrentIndex(0);
    ui->tableViewEmployes->setModel(etmp.afficher());
    ui->stackedWidget->setCurrentIndex(1);



}

MainWindow::~MainWindow()
{
    delete ui;
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

void MainWindow::on_btnAnnulerModifEmploye_clicked()
{
    ui->tabWidgetEmploye->setCurrentIndex(0);
    ui->leNomEmployeModif->clear();
    ui->lePrenomEmployeModif->clear();
    ui->leEmailEmployeModif->clear();
    ui->leMdpEmployeModif->clear();
    ui->cbRoleEmployeModif->setCurrentText("Admin");

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



void MainWindow::on_pushButton_pdfEmploye_clicked()
{
    QPdfWriter pdf("C:/Users/RayenSabri/Desktop/Borhen-Gestion-Employes/test5.pdf");
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
               QImage image("‪C:/Users/RayenSabri/Downloads/images.png");
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
                   QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/RayenSabri/Desktop/Borhen-Gestion-Employes/test5.pdf"));

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

void MainWindow::on_pushButton_clicked()
{
    QString email = ui->email->text();
    QString password = ui->password->text();
    if (etmp.autentifier(email,password)){
        QMessageBox::information(nullptr, QObject::tr("ok"),
                        QObject::tr("authentification successful !\n""Click Cancel to exit."), QMessageBox::Cancel);
        ui->stackedWidget->setCurrentIndex(0);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("non"),
                        QObject::tr("invalid credentials !\n""Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_pushButton_logout_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}
