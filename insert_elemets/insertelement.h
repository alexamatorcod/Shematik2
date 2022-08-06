#ifndef INSERTELEMENT_H
#define INSERTELEMENT_H

#include <QWidget>
#include <QtSql>
#include <QDebug>
#include <QFile>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QMenu>
#include <QTableView>
#include "myscene.h"

namespace Ui {
class InsertElement;
}

class InsertElement : public QWidget
{
    Q_OBJECT

public:
    explicit InsertElement(QWidget *parent = nullptr);
    ~InsertElement();

public slots:
    void on_pBtn_Cancel_clicked();
    virtual void on_pBtn_Choice_clicked();
    virtual  void on_tableViewRE_clicked(const QModelIndex &index);
private:
    Ui::InsertElement *ui;
    QString dbFileName;//Имя файла БД
    QSqlDatabase db; //Объект для работы с БД
    int openDBState; //При == 1 БД загрузилась
    QSqlTableModel* modelT;
public:
    MyScene *mysceneobj;
    int row;
    int column;
};

#endif // INSERTELEMENT_H
