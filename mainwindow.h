#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
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
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include "employe.h"
QT_CHARTS_USE_NAMESPACE
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    MainWindow(QString,QString,QMainWindow *parent = nullptr);
    ~   MainWindow();
    void renderQMessageBox(QString title,QString message);
    int getting_id_selected();
    void return_data_going_update(int id);

private slots:
    /*** INTEGRATION PRISES ***/

    void on_push_ajouter_clicked();
    void on_push_modifier_clicked();
    void on_push_supprimer_clicked();
    void on_comboBox_id_currentIndexChanged(int index);
    void on_push_triID_clicked();
    void on_push_triEtat_clicked();
    void on_push_triVoltage_clicked();
    void on_line_recherche_textChanged(const QString &arg1);
    void on_push_ExportPDF_clicked();
    void on_envoyer_dialog_2_clicked();
    void on_push_stats_clicked();
   //void on_pushButton_clicked();
    void on_pushButton_on_clicked();
    void on_pushButton_off_clicked();
    void on_label_distance_linkActivated(const QString &link);
    void update_label();
    void on_ajoutedis_clicked();
    /*** INTEGRATION VOITURES ***/
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_return_from_afficher_clicked();
    void on_return_from_modifier_clicked();
    void on_return_from_ajout_clicked();
    void on_modifier_table_clicked();
    void on_pushButton_clicked();
    void on_supprimer_table_clicked();
    void on_pushButton_3_clicked();
    void on_generate_pdf_clicked();
    void on_pushButton_2_clicked();
    void on_recherche_textChanged(const QString &arg1);
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void generateQRCode(int mat, QString marq , QString prop, int etat);
    void on_Menu_Prises_clicked();
    void Prises_choix_pie();
    void on_Menu_Voiture_clicked();

    void on_return_from_ajout_2_clicked();

    void on_push_UpdateStats_clicked();

    void on_Menu_Voiture_2_clicked();

    void on_pushButton_Reserver_clicked();

    void on_dateEdit_dateChanged(const QDate &date);

    void on_pushButton_Reserver_2_clicked();

    void on_lineEdit_rechercher_returnPressed();

    void on_radioButton_desc_clicked();

    void on_radioButton_asc_clicked();

    void on_radioButton_asc_2_clicked();

    void on_tableView_reservations_clicked(const QModelIndex &index);

    void on_pushButton_supprimer_clicked();

    void on_pushButton_stat_clicked();

    void on_pushButton_pdf_clicked();

    void on_dateEdit_2_dateChanged(const QDate &date);

    void on_pushButton_9_clicked();

    void on_Menu_Voiture_3_clicked();

    void on_btnAjoutEmploye_clicked();

    void on_btnAnnulerEmploye_clicked();

    void on_line_research_textChanged(const QString &arg1);

    void on_pushButton_sort_clicked();

    void on_btnModifierEmployeSelect_clicked();

    void on_btnSupprimerEmploye_clicked();

    void on_pushButton_pdfEmploye_clicked();

    void on_pushButton_statEmploye_clicked();

    void on_btnModifierEmploye_clicked();

    void on_return_from_ajout_3_clicked();

private:
    Ui::MainWindow *ui;
    Prise P;
    QString tmpemail;
    QByteArray data; //variable contenant les donées reçues
    Arduino A;
    voitures V;
    Employe etmp ;
};
#endif // MAINWINDOW_H
