#include "insert_elemets/inserttransistor.h"

InsertTransistor::InsertTransistor()
    : ui (new Ui::InsertElement)
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
    modelT->setTable("Transistors");
    modelT->setEditStrategy(QSqlTableModel::OnManualSubmit);
    modelT->select();
    ui->tableViewRE->setModel(modelT);
    ui->tableViewRE->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

InsertTransistor::~InsertTransistor(){}

void InsertTransistor::on_pBtn_Choice_clicked()
{
    myindex = ui->tableViewRE->model()->index(row, 0, QModelIndex());
    data = ui->tableViewRE->model()->data(myindex,Qt::DisplayRole);
    imarking = data.toString();

    myindex = ui->tableViewRE->model()->index(row, 1, QModelIndex());
    data = ui->tableViewRE->model()->data(myindex,Qt::DisplayRole);
    itransistortype = data.toString();

    myindex = ui->tableViewRE->model()->index(row, 2, QModelIndex());
    data = ui->tableViewRE->model()->data(myindex,Qt::DisplayRole);
    istructure = data.toString();

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

    mysceneobj->transistorobj = new TransistorClass(mysceneobj->countTransistor);
    mysceneobj->transistorobj->rowindatabase = row;
    mysceneobj->transistorobj->setMarking(imarking);
    mysceneobj->transistorobj->setTransistortype(itransistortype);
    mysceneobj->transistorobj->setStructure(istructure);
    mysceneobj->transistorobj->setTypeofshell(itypeofshell);
    mysceneobj->transistorobj->setLength(ilength);
    mysceneobj->transistorobj->setWight(iwight);
    mysceneobj->transistorobj->setHeight(iheight);
    mysceneobj->transistorobj->setThicknessofleg(ithicknessofleg);


    qDebug()<<imarking<<" "<<itransistortype<<" "<<istructure<<
              " "<<itypeofshell<<" "<<ilength<<
              " "<<iwight<<" "<<iheight<<" "<<ithicknessofleg;
}
void InsertTransistor::on_tableViewRE_clicked(const QModelIndex &index)
{
    row = index.row();
    column = index.column();
    qDebug()<<row<<" "<<column;
}

QString InsertTransistor::getMarking(){return imarking;}
QString InsertTransistor::getTransistortype(){return itransistortype;}
QString InsertTransistor::getStructure(){return istructure;}
QString InsertTransistor::getTypeofshell(){return itypeofshell;}
float InsertTransistor::getLength(){return ilength;}
float InsertTransistor::getWight(){return iwight;}
float InsertTransistor::getHeight(){return iheight;}
float InsertTransistor::getThicknessofleg(){return ithicknessofleg;}
