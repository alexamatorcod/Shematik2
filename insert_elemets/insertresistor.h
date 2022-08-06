#ifndef INSERTRESISTOR_H
#define INSERTRESISTOR_H
#include "insert_elemets/insertelement.h"
#include "ui_insertelement.h"
#include <QMessageBox>

class InsertResistor : public InsertElement
{
    Q_OBJECT
public:
    InsertResistor();
    ~InsertResistor();

    QString getMarking();
    QString getResistortype();
    float getResistance();
    int getPower();
    QString getTypeofshell();
    float getLength();
    float getWight();
    float getHeight();
    float getThicknessofleg();

public slots:
    void on_pBtn_Choice_clicked() override;
    void on_tableViewRE_clicked(const QModelIndex &index) override;
signals:
    void sendData(QString imarking,QString iresistortype,float iresistance,
                  int ipower,QString itypeofshell,float ilength,float iwight,float iheight,float ithicknessofleg);
public:
    Ui::InsertElement *ui;
    QString dbFileName;//Имя файла БД
    QSqlDatabase db; //Объект для работы с БД
    int openDBState; //При == 1 БД загрузилась
    QSqlTableModel* modelT;

    QModelIndex myindex;
    QVariant data;
    int rowpos=0;
    bool fb=false;

    QString imarking;
    QString iresistortype;
    float iresistance;
    int ipower;
    QString itypeofshell;
    float ilength;
    float iwight;
    float iheight;
    float ithicknessofleg;
};

#endif // INSERTRESISTOR_H
