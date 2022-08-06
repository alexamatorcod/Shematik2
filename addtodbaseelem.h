#ifndef ADDTODBASEELEM_H
#define ADDTODBASEELEM_H

#include <QWidget>
#include <QtSql>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlTableModel>
#include <QSqlQuery>

namespace Ui {
class AddtoDBaseElem;
}

class AddtoDBaseElem : public QWidget
{
    Q_OBJECT

public:
    explicit AddtoDBaseElem();
    ~AddtoDBaseElem();
private slots:
     virtual void on_pBtn_ADD_DB_Elem_clicked();
     virtual void on_pBtn_Delete_clicked();
     virtual void on_tV_Elem_clicked(const QModelIndex &index);
     void on_pBtn_Cancel_clicked();

private:
    Ui::AddtoDBaseElem *ui;
    QString dbFileName;//Имя файла БД
    QSqlDatabase db;
    QSqlQuery *query;
    QSqlTableModel* modelT;
    //int row;
};

#endif // ADDTODBASEELEM_H
