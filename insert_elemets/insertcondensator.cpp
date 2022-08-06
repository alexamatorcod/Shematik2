#include "insert_elemets/insertcondensator.h"

InsertCondensator::InsertCondensator()
    : ui(new Ui::InsertElement)
{
    ui->setupUi(this);
    dbFileName = ("../Shematik2/radioelementsdb.db");
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName( dbFileName );
    if (!db.open())
    {  QMessageBox::critical(0, qApp->tr("Поиск файла БД"),
                             qApp->tr("Файл БД не обнаружен"),
                             QMessageBox::Cancel);


        QMessageBox::critical(0, qApp->tr("Открытие файла БД"),
                              qApp->tr("БД открыть не удалось"),
                              QMessageBox::Cancel);
        return;}
    if(db.open())
    {
        qDebug()<<"База найдена и открыта";
    }

    modelT = new QSqlTableModel(this,db);
    modelT->setTable("Capacitors");
    modelT->setEditStrategy(QSqlTableModel::OnManualSubmit);
    modelT->select();
    ui->tableViewRE->setModel(modelT);
    ui->tableViewRE->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

}

InsertCondensator::~InsertCondensator(){}

void InsertCondensator::on_pBtn_Choice_clicked()
{
    myindex = ui->tableViewRE->model()->index(row, 0, QModelIndex());
    data = ui->tableViewRE->model()->data(myindex,Qt::DisplayRole);
    imarking = data.toString();

    myindex = ui->tableViewRE->model()->index(row, 1, QModelIndex());
    data = ui->tableViewRE->model()->data(myindex,Qt::DisplayRole);
    icapacitortype = data.toString();

    myindex = ui->tableViewRE->model()->index(row, 2, QModelIndex());
    data = ui->tableViewRE->model()->data(myindex,Qt::DisplayRole);
    icapacity = data.toFloat();

    myindex = ui->tableViewRE->model()->index(row, 3, QModelIndex());
    data = ui->tableViewRE->model()->data(myindex,Qt::DisplayRole);
    itypeofshell = data.toString();

    myindex = ui->tableViewRE->model()->index(row, 4, QModelIndex());
    data = ui->tableViewRE->model()->data(myindex,Qt::DisplayRole);
    ilength = data.toFloat();

    myindex = ui->tableViewRE->model()->index(row, 5, QModelIndex());
    data = ui->tableViewRE->model()->data(myindex,Qt::DisplayRole);
    iwight = data.toFloat();

    myindex = ui->tableViewRE->model()->index(row, 6, QModelIndex());
    data = ui->tableViewRE->model()->data(myindex,Qt::DisplayRole);
    iheight = data.toFloat();

    myindex = ui->tableViewRE->model()->index(row, 7, QModelIndex());
    data = ui->tableViewRE->model()->data(myindex,Qt::DisplayRole);
    ithicknessofleg = data.toFloat();

    mysceneobj->condensatorobj = new CondensatorClass(mysceneobj->countCondensator);
    mysceneobj->condensatorobj->rowindatabase = row;
    mysceneobj->condensatorobj->setMarking(imarking);
    mysceneobj->condensatorobj->setCapacitortype(icapacitortype);
    mysceneobj->condensatorobj->setCapacity(icapacity);
    mysceneobj->condensatorobj->setTypeofshell(itypeofshell);
    mysceneobj->condensatorobj->setLength(ilength);
    mysceneobj->condensatorobj->setWight(iwight);
    mysceneobj->condensatorobj->setHeight(iheight);
    mysceneobj->condensatorobj->setThicknessofleg(ithicknessofleg);


    qDebug()<<imarking<<" "<<icapacitortype<<" "<<icapacity<<
              " "<<itypeofshell<<" "<<ilength<<
              " "<<iwight<<" "<<iheight<<" "<<ithicknessofleg;
}

void InsertCondensator::on_tableViewRE_clicked(const QModelIndex &index)
{
    row = index.row();
    column = index.column();
    qDebug()<<row<<" "<<column;
}

QString InsertCondensator::getMarking(){return imarking;}
QString InsertCondensator::getCapacitortype(){return icapacitortype;}
float InsertCondensator::getCapacity(){return icapacity;}
QString InsertCondensator::getTypeofshell(){return itypeofshell;}
float InsertCondensator::getLength(){return ilength;}
float InsertCondensator::getWight(){return iwight;}
float InsertCondensator::getHeight(){return iheight;}
float InsertCondensator::getThicknessofleg(){return ithicknessofleg;}
