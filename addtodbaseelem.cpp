#include "addtodbaseelem.h"
#include "ui_addtodbaseelem.h"

AddtoDBaseElem::AddtoDBaseElem() :
    ui(new Ui::AddtoDBaseElem)
{
    //ui->setupUi(this);
}

AddtoDBaseElem::~AddtoDBaseElem()
{
    delete ui;
}

void AddtoDBaseElem::on_pBtn_ADD_DB_Elem_clicked()
{

}

void AddtoDBaseElem::on_pBtn_Delete_clicked()
{

}

void AddtoDBaseElem::on_tV_Elem_clicked(const QModelIndex &index)
{
    Q_UNUSED(index);
}

void AddtoDBaseElem::on_pBtn_Cancel_clicked()
{
    QWidget::close();
}


