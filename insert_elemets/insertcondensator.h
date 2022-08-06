#ifndef INSERTCONDENSATOR_H
#define INSERTCONDENSATOR_H
#include "insert_elemets/insertelement.h"
#include "ui_insertelement.h"
#include <QMessageBox>

class InsertCondensator : public InsertElement
{
    Q_OBJECT
public:
    InsertCondensator();
    ~InsertCondensator();
private slots:

    void on_pBtn_Choice_clicked() override;
    void on_tableViewRE_clicked(const QModelIndex &index) override;

private:
    Ui::InsertElement *ui;
    QString dbFileName;//Имя файла БД
    QSqlDatabase db; //Объект для работы с БД
    int openDBState; //При == 1 БД загрузилась
    QSqlTableModel* modelT;
    QModelIndex myindex;
    QVariant data;
    int rowpos=0;

public:
    QString imarking;
    QString icapacitortype;
    float icapacity;
    QString itypeofshell;
    float ilength;
    float iwight;
    float iheight;
    float ithicknessofleg;

    QString getMarking();
    QString getCapacitortype();
    float getCapacity();
    QString getTypeofshell();
    float getLength();
    float getWight();
    float getHeight();
    float getThicknessofleg();
};

#endif // INSERTCONDENSATOR_H
