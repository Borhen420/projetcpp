#ifndef VOITURE_H
#define VOITURE_H
#include <QWidget>
#include <QDialog>
#include "voitures.h"
namespace Ui {
class voiture;
}

class voiture : public QDialog
{
    Q_OBJECT

public:
    explicit voiture(QWidget *parent = nullptr);

    ~voiture();
    void renderQMessageBox(QString title,QString message);
    int getting_id_selected();
    void return_data_going_update(int id);
    QWidget *return_ui();

private slots:
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
private:
    Ui::voiture *ui;
    voitures V;
};

#endif // VOITURE_H
