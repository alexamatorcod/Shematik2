#include "insert_elemets/insertelement.h"
#include "ui_insertelement.h"
#include <QMessageBox>

InsertElement::InsertElement(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InsertElement)
{ }

InsertElement::~InsertElement()
{
    delete ui;
}

void InsertElement::on_pBtn_Cancel_clicked()
{
    QWidget::close();
}

void InsertElement::on_pBtn_Choice_clicked()
{

}
void InsertElement::on_tableViewRE_clicked(const QModelIndex &index)
{
    Q_UNUSED(index);
}
