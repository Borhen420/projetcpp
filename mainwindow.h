#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QtGui/QValidator>
#include <QtGui/QRegExpValidator>
#include "employe.h"
#include <QPainter>
#include <QPdfWriter>
#include <QDesktopServices>
#include <QtCharts>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnAjoutEmploye_clicked();

    void on_btnAnnulerEmploye_clicked();

    void on_btnSupprimerEmploye_clicked();

    void on_btnModifierEmployeSelect_clicked();

    void on_btnModifierEmploye_clicked();

    void on_btnAnnulerModifEmploye_clicked();

    void on_line_research_textChanged(const QString &arg1);

    void on_pushButton_sort_clicked();

    void on_pushButton_pdfEmploye_clicked();

    void on_pushButton_statEmploye_clicked();

    void on_pushButton_clicked();

    void on_pushButton_logout_clicked();

private:
    Ui::MainWindow *ui;
    Employe etmp ;
};
#endif // MAINWINDOW_H
