#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDockWidget>
#include "myscene.h"
#include "insert_elemets/insertelement.h"
#include "insert_elemets/insertcondensator.h"
#include "insert_elemets/insertdiode.h"
#include "insert_elemets/insertresistor.h"
#include "insert_elemets/inserttransistor.h"
#include "addtodbaseelem.h"
#include "add_db_elements/add_capacitor.h"
#include "add_db_elements/add_diodes.h"
#include "add_db_elements/add_resistor.h"
#include "add_db_elements/add_transistor.h"
#include <QScrollBar>
#include <QGraphicsView>
#include <QFileDialog>
//#include "mygv.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class MyScrollBar;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    enum TYPE{RESISTOR,CONDENSATOR,DIODE,TRANSISTOR,LINE};


    bool  saveFile(QString nameFile);
    bool  openFile(QString nameFile);
    void updateWindowTitle();
    bool preparationReplacement();
private slots:
    void on_action_T_DB_triggered();
    void on_action_R_DB_triggered();
    void on_action_C_DB_triggered();
    void on_action_D_DB_triggered();
    void on_action_Add_Transistor_triggered();
    void on_action_Add_Capacitor_triggered();
    void on_action_Add_Diode_triggered();
    void on_action_Add_Resistor_triggered();
    void on_Scale_plus_triggered();
    void on_Scale_minus_triggered();
    void on_pBtn_InsTransistor_clicked();
    void on_pBtn_InsResistor_clicked();
    void on_pBtn_InsCondensator_clicked();
    void on_pBtn_InsDiode_clicked();
    void on_action_Save_triggered();
    void on_action_Save_As_triggered();
    void on_action_Open_triggered();

private:
    Ui::MainWindow *ui;
    MyScene *pScene;
    QDockWidget *dockwidget;
    InsertElement *E;
    AddtoDBaseElem *addtodbelem;
    MyScrollBar  *msb;
    qreal sx=1,sy=1;
    int m=500;
    double m2=1;
    QString DirPath;
    QString fileName;
    bool isSaved=false;
    TYPE etype;

public:
    InsertResistor *ir;
    InsertCondensator *ic;
    InsertTransistor *it;
    InsertDiode *id;

};
#endif
