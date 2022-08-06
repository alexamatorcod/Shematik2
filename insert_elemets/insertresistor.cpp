#include "insert_elemets/insertresistor.h"

InsertResistor::InsertResistor()
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
    modelT->setTable("Resistors");
    modelT->select();
    ui->tableViewRE->setModel(modelT);
    ui->tableViewRE->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

InsertResistor::~InsertResistor(){}

void InsertResistor::on_pBtn_Choice_clicked()
{
    myindex = ui->tableViewRE->model()->index(row, 0, QModelIndex());
    data = ui->tableViewRE->model()->data(myindex,Qt::DisplayRole);
    imarking = data.toString();

    myindex = ui->tableViewRE->model()->index(row, 1, QModelIndex());
    data = ui->tableViewRE->model()->data(myindex,Qt::DisplayRole);
    iresistortype = data.toString();

    myindex = ui->tableViewRE->model()->index(row, 2, QModelIndex());
    data = ui->tableViewRE->model()->data(myindex,Qt::DisplayRole);
    iresistance = data.toFloat();

    myindex = ui->tableViewRE->model()->index(row, 3, QModelIndex());
    data = ui->tableViewRE->model()->data(myindex,Qt::DisplayRole);
    ipower = data.toInt();

    myindex = ui->tableViewRE->model()->index(row, 4, QModelIndex());
    data = ui->tableViewRE->model()->data(myindex,Qt::DisplayRole);
    itypeofshell = data.toString();

    myindex = ui->tableViewRE->model()->index(row, 5, QModelIndex());
    data = ui->tableViewRE->model()->data(myindex,Qt::DisplayRole);
    ilength = data.toFloat();

    myindex = ui->tableViewRE->model()->index(row, 6, QModelIndex());
    data = ui->tableViewRE->model()->data(myindex,Qt::DisplayRole);
    iwight = data.toFloat();

    myindex = ui->tableViewRE->model()->index(row, 7, QModelIndex());
    data = ui->tableViewRE->model()->data(myindex,Qt::DisplayRole);
    iheight = data.toFloat();

    myindex = ui->tableViewRE->model()->index(row, 8, QModelIndex());
    data = ui->tableViewRE->model()->data(myindex,Qt::DisplayRole);
    ithicknessofleg = data.toFloat();

    mysceneobj->resistorobj = new ResistorClass(mysceneobj->countResistor);
    mysceneobj->rowdbmemory = row;
    mysceneobj->resistorobj->rowindatabase = row;
    mysceneobj->resistorobj->setMarking(imarking);
    mysceneobj->resistorobj->setResistortype(iresistortype);
    mysceneobj->resistorobj->setResistance(iresistance);
    mysceneobj->resistorobj->setPower(ipower);
    mysceneobj->resistorobj->setTypeofshell(itypeofshell);
    mysceneobj->resistorobj->setLength(ilength);
    mysceneobj->resistorobj->setWight(iwight);
    mysceneobj->resistorobj->setHeight(iheight);
    mysceneobj->resistorobj->setThicknessofleg(ithicknessofleg);


    qDebug()<<imarking<<" "<<iresistortype<<" "<<iresistance<<
              " "<<ipower<<" "<<itypeofshell<<" "<<ilength<<
              " "<<iwight<<" "<<iheight<<" "<<ithicknessofleg;
}

void InsertResistor::on_tableViewRE_clicked(const QModelIndex &index)
{
    row = index.row();
    column = index.column();
    qDebug()<<row<<" "<<column;
}

QString InsertResistor::getMarking(){return imarking;}
QString InsertResistor::getResistortype(){return iresistortype;}
float InsertResistor::getResistance(){return iresistance;}
int InsertResistor::getPower(){return ipower;}
QString InsertResistor::getTypeofshell(){return itypeofshell;}
float InsertResistor::getLength(){return ilength;}
float InsertResistor::getWight(){return iwight;}
float InsertResistor::getHeight(){return iheight;}
float InsertResistor::getThicknessofleg(){return ithicknessofleg;}
