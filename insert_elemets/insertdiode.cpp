#include "insert_elemets/insertdiode.h"

InsertDiode::InsertDiode()
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
    modelT->setTable("Diodes");
    modelT->setEditStrategy(QSqlTableModel::OnManualSubmit);
    modelT->select();
    ui->tableViewRE->setModel(modelT);
    ui->tableViewRE->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

InsertDiode::~InsertDiode(){}

void InsertDiode::on_pBtn_Choice_clicked()
{
    myindex = ui->tableViewRE->model()->index(row, 0, QModelIndex());
    data = ui->tableViewRE->model()->data(myindex,Qt::DisplayRole);
    imarking = data.toString();

    myindex = ui->tableViewRE->model()->index(row, 1, QModelIndex());
    data = ui->tableViewRE->model()->data(myindex,Qt::DisplayRole);
    idiodetype = data.toString();

    myindex = ui->tableViewRE->model()->index(row, 2, QModelIndex());
    data = ui->tableViewRE->model()->data(myindex,Qt::DisplayRole);
    ibracedownvoltage = data.toFloat();

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

    mysceneobj->diodeobj = new DiodeClass(mysceneobj->countDiode);
    mysceneobj->diodeobj->rowindatabase = row;
    mysceneobj->diodeobj->setMarking(imarking);
    mysceneobj->diodeobj->setDiodetype(idiodetype);
    mysceneobj->diodeobj->setBrackeDownVoltage(ibracedownvoltage);
    mysceneobj->diodeobj->setTypeofshell(itypeofshell);
    mysceneobj->diodeobj->setLength(ilength);
    mysceneobj->diodeobj->setWight(iwight);
    mysceneobj->diodeobj->setHeight(iheight);
    mysceneobj->diodeobj->setThicknessofleg(ithicknessofleg);

    qDebug()<<imarking<<" "<<idiodetype<<" "<<ibracedownvoltage<<
              " "<<itypeofshell<<" "<<ilength<<
              " "<<iwight<<" "<<iheight<<" "<<ithicknessofleg;
}
void InsertDiode::on_tableViewRE_clicked(const QModelIndex &index)
{
    row = index.row();
    column = index.column();
    qDebug()<<row<<" "<<column;
}

QString InsertDiode::getMarking(){return imarking;}
QString InsertDiode::getDiodetype(){return idiodetype;}
float InsertDiode::getBraceDownVoltage(){return ibracedownvoltage;}
QString InsertDiode::getTypeofshell(){return itypeofshell;}
float InsertDiode::getLength(){return ilength;}
float InsertDiode::getWight(){return iwight;}
float InsertDiode::getHeight(){return iheight;}
float InsertDiode::getThicknessofleg(){return ithicknessofleg;}
