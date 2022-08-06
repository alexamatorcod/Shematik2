#include "add_db_elements/add_capacitor.h"


Add_Capacitor::Add_Capacitor() :
    ui(new Ui::AddtoDBaseElem)
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
        return;
    }
    if(db.open())
    {
        qDebug()<<"База найдена и открыта";
    }
    query =new QSqlQuery(db);
    query->exec("CREATE TABLE Capacitors (Marking TEXT,CapacitorType TEXT,Capacity INT,Type_of_Shell TEXT,Length INT,Wight INT,Height INT,ThicknessOfLeg FLOAT,Apearance DATE);");

    modelT = new QSqlTableModel(this,db);
    modelT->setTable("Capacitors");
    modelT->select();
    ui->tV_Elem->setModel(modelT);
    ui->tV_Elem->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

Add_Capacitor::~Add_Capacitor()
{
    delete ui;
}

void Add_Capacitor::on_pBtn_ADD_DB_Elem_clicked()
{
    modelT->insertRow(modelT->rowCount());
}

void Add_Capacitor::on_pBtn_Delete_clicked()
{
    modelT->removeRow(row);
}

void Add_Capacitor::on_tV_Elem_clicked(const QModelIndex &index)
{
    row = index.row();
}

