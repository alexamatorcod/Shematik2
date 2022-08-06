#ifndef ADD_CAPACITOR_H
#define ADD_CAPACITOR_H

#include "addtodbaseelem.h"
#include "ui_addtodbaseelem.h"

namespace Ui {
class Add_Capacitor;
}

class Add_Capacitor : public AddtoDBaseElem
{
    Q_OBJECT

public:
    explicit Add_Capacitor();
    ~Add_Capacitor();

private slots:
    void on_pBtn_ADD_DB_Elem_clicked() override;
    void on_pBtn_Delete_clicked() override;
    void on_tV_Elem_clicked(const QModelIndex &index) override;

private:
    Ui::AddtoDBaseElem *ui;
    QString dbFileName;//Имя файла БД
    QSqlDatabase db;
    QSqlQuery *query;
    QSqlTableModel* modelT;
    int row;
};

#endif // ADD_CAPACITOR_H
