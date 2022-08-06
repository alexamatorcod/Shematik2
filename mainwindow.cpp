#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "line.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pScene = new MyScene(this);
    ui->toolBar_DBElem->addActions(ui->menu_Insert->actions());
    ui->toolBar_Act->addActions(ui->menu_Act->actions());
    ui->graphicsView->setScene(pScene);
    ui->graphicsView->Scene=pScene;
    pScene->setItemIndexMethod(QGraphicsScene::NoIndex); // настраиваем индексацию элементов
    pScene->setSceneRect(0,0,1000,1000);
    ui->graphicsView->resize(600,600);  // Устанавливаем размер graphicsView
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);    // Настраиваем рендер
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground); // Кэш фона QGraphicsView::
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);//QGraphicsView::

    connect(ui->pBtn_InsLine, SIGNAL(clicked(bool)), ui->graphicsView, SLOT(on_pBtn_InsLine_clicked(bool)));
    connect(ui->pBtn_Move, SIGNAL(clicked()), ui->graphicsView->scene(), SLOT(on_pBtn_Move_clicked()));
    connect(ui->Rotate_clockwise, SIGNAL(triggered()), ui->graphicsView->scene(), SLOT(on_Rotate_clockwise_triggered()));
    connect(ui->Rotate_counterclockwise, SIGNAL(triggered()), ui->graphicsView->scene(), SLOT(on_Rotae_counterclockwise_triggered()));
    connect(ui->action_Delete, SIGNAL(triggered()), ui->graphicsView->scene(), SLOT(on_action_Delete_triggered()));

    fileName="Shema1.bin";
    DirPath = QCoreApplication::applicationDirPath().append('/');
    isSaved = true;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_action_T_DB_triggered()
{   addtodbelem = new Add_Transistor();
    addtodbelem->setWindowModality(Qt::WindowModal);
    addtodbelem->show();}

void MainWindow::on_action_R_DB_triggered()
{   addtodbelem = new Add_Resistor();
    addtodbelem->setWindowModality(Qt::WindowModal);
    addtodbelem->show();}

void MainWindow::on_action_C_DB_triggered()
{   addtodbelem = new Add_Capacitor();
    addtodbelem->setWindowModality(Qt::WindowModal);
    addtodbelem->show();}

void MainWindow::on_action_D_DB_triggered()
{   addtodbelem = new Add_Diodes();
    addtodbelem->setWindowModality(Qt::WindowModal);
    addtodbelem->show();}


void MainWindow::on_action_Add_Transistor_triggered()
{   it = new InsertTransistor();
    it->mysceneobj = pScene;
    it->setWindowModality(Qt::WindowModal);
    it->show();}

void MainWindow::on_action_Add_Capacitor_triggered()
{   ic = new InsertCondensator();
    ic->mysceneobj = pScene;
    ic->setWindowModality(Qt::WindowModal);
    ic->show();}

void MainWindow::on_action_Add_Diode_triggered()
{   id = new InsertDiode();
    id->mysceneobj = pScene;
    id->setWindowModality(Qt::WindowModal);
    id->show();}

void MainWindow::on_action_Add_Resistor_triggered()
{   ir = new InsertResistor();
    ir->mysceneobj = pScene;
    pScene->Figure = MyScene::setResistor;
    ir->setWindowModality(Qt::WindowModal);
    ir->show();}

void MainWindow::on_pBtn_InsResistor_clicked()
{   ir = new InsertResistor();
    ir->mysceneobj = pScene;
    pScene->Figure = MyScene::setResistor;
    ir->setWindowModality(Qt::WindowModal);
    ir->show();
}
void MainWindow::on_pBtn_InsCondensator_clicked()
{   ic = new InsertCondensator();
    ic->mysceneobj = pScene;
    pScene->Figure = MyScene::setCondensator;
    ic->setWindowModality(Qt::WindowModal);
    ic->show();}

void MainWindow::on_pBtn_InsDiode_clicked()
{
    id = new InsertDiode();
    id->mysceneobj = pScene;
    pScene->Figure = MyScene::setDiode;
    id->setWindowModality(Qt::WindowModal);
    id->show();
}

void MainWindow::on_pBtn_InsTransistor_clicked()
{   it = new InsertTransistor();
    it->mysceneobj = pScene;
    pScene->Figure = MyScene::setTransistor;
    it->setWindowModality(Qt::WindowModal);
    it->show();}

void MainWindow::on_Scale_plus_triggered()
{
    sx+=0.1;
    sy+=0.1;
    m+=1;
    QTransform matrix;
    matrix.scale(sx, sy);
    ui->graphicsView->setTransform(matrix);
}

void MainWindow::on_Scale_minus_triggered()
{
    sx-=0.1;
    sy-=0.1;
    m-=1;
    QTransform matrix;
    matrix.scale(sx,sy);
    ui->graphicsView->setTransform(matrix);
}

void MainWindow::updateWindowTitle ( )
{
    //Конструкция " [*] " помечает место для отображения знака "_" в случае,
    //  когда содержимое редактора модифицировано и не сохранено
    QString newTitle=QString ( " Simple Notepad - %1[*]" ).arg ( fileName );
    setWindowModified(!isSaved);
    //Обновить заголовок окна
    setWindowTitle ( newTitle );
}

bool  MainWindow::saveFile(QString nameFile)
{
    int radioelementscount=0,listlinecount=0,typeelements=0,elementcount=0,rowindatabase=0;
    qreal posx=0,posy=0,angle=0;
    ///QString typeelement;

    QFile file(nameFile);
    if (!file.open(QIODevice::WriteOnly))
    {QMessageBox::warning(this,tr("Сохранение"),
                          tr("Не удалось открыть файл для записи:\n %1").arg(file.errorString()),
                          QMessageBox::Ok|QMessageBox::Default);
        return false;
    }

    radioelementscount=pScene->radioelements.count();
    listlinecount=pScene->listLine.count();

    QDataStream outstream(&file);
    qDebug()<<"---WRITE---";
    outstream << radioelementscount;
    outstream << listlinecount;
    qDebug()<<"radioelements.count()"<<pScene->radioelements.count();
    qDebug()<<"listLine.count()"<<pScene->listLine.count();

    for(int i=0;i<pScene->radioelements.count();i++)
    {
        if(pScene->radioelements.at(i)->typeElement == ElementItem::RESISTOR){
            typeelements=pScene->radioelements.at(i)->typeElement;
            posx=pScene->radioelements.at(i)->pos().x();
            posy=pScene->radioelements.at(i)->pos().y();
            elementcount=pScene->radioelements.at(i)->ecount;
            rowindatabase=pScene->radioelements.at(i)->rowindatabase;
            angle=pScene->radioelements.at(i)->angle;
            outstream << typeelements;//............
            outstream << posx;
            outstream << posy;
            outstream << elementcount;
            outstream << rowindatabase;
            outstream << angle;
            outstream << pScene->resistorobj->Marking;
            outstream << pScene->resistorobj->Resistortype;
            outstream << pScene->resistorobj->Resistance;
            outstream << pScene->resistorobj->Power;
            outstream << pScene->resistorobj->Typeofshell;
            outstream << pScene->resistorobj->Length;
            outstream << pScene->resistorobj->Wight;
            outstream << pScene->resistorobj->Height;
            outstream << pScene->resistorobj->Thicknessofleg;
        }
        if(pScene->radioelements.at(i)->typeElement == ElementItem::CONDENSATOR){
            typeelements=pScene->radioelements.at(i)->typeElement;
            posx=pScene->radioelements.at(i)->pos().x();
            posy=pScene->radioelements.at(i)->pos().y();
            elementcount=pScene->radioelements.at(i)->ecount;
            rowindatabase=pScene->radioelements.at(i)->rowindatabase;
            angle=pScene->radioelements.at(i)->angle;
            outstream << typeelements;//............
            outstream << posx;
            outstream << posy;
            outstream << elementcount;
            outstream << rowindatabase;
            outstream << angle;
            outstream << pScene->condensatorobj->Marking;
            outstream << pScene->condensatorobj->Capacitortype;
            outstream << pScene->condensatorobj->Capacity;
            outstream << pScene->condensatorobj->Typeofshell;
            outstream << pScene->condensatorobj->Length;
            outstream << pScene->condensatorobj->Wight;
            outstream << pScene->condensatorobj->Height;
            outstream << pScene->condensatorobj->Thicknessofleg;
        }
        if(pScene->radioelements.at(i)->typeElement == ElementItem::DIODE){
            typeelements=pScene->radioelements.at(i)->typeElement;
            posx=pScene->radioelements.at(i)->pos().x();
            posy=pScene->radioelements.at(i)->pos().y();
            elementcount=pScene->radioelements.at(i)->ecount;
            rowindatabase=pScene->radioelements.at(i)->rowindatabase;
            angle=pScene->radioelements.at(i)->angle;
            outstream << typeelements;//............
            outstream << posx;
            outstream << posy;
            outstream << elementcount;
            outstream << rowindatabase;
            outstream << angle;
            outstream << pScene->diodeobj->Marking;
            outstream << pScene->diodeobj->Diodetype;
            outstream << pScene->diodeobj->Breackdownvoltage;
            outstream << pScene->diodeobj->Typeofshell;
            outstream << pScene->diodeobj->Length;
            outstream << pScene->diodeobj->Wight;
            outstream << pScene->diodeobj->Height;
            outstream << pScene->diodeobj->Thicknessofleg;
        }
        if(pScene->radioelements.at(i)->typeElement == ElementItem::TRANSISTOR){
            typeelements=pScene->radioelements.at(i)->typeElement;
            posx=pScene->radioelements.at(i)->pos().x();
            posy=pScene->radioelements.at(i)->pos().y();
            elementcount=pScene->radioelements.at(i)->ecount;
            rowindatabase=pScene->radioelements.at(i)->rowindatabase;
            angle=pScene->radioelements.at(i)->angle;
            outstream << typeelements;//............
            outstream << posx;
            outstream << posy;
            outstream << elementcount;
            outstream << rowindatabase;
            outstream << angle;
            outstream << pScene->transistorobj->Marking;
            outstream << pScene->transistorobj->Transistortype;
            outstream << pScene->transistorobj->Structure;
            outstream << pScene->transistorobj->Typeofshell;
            outstream << pScene->transistorobj->Length;
            outstream << pScene->transistorobj->Wight;
            outstream << pScene->transistorobj->Height;
            outstream << pScene->transistorobj->Thicknessofleg;
        }
    }

    for(int i=0;i<pScene->listLine.count();i++)
    {
        outstream << pScene->listLine.at(i)->typeClass;
        outstream << pScene->listLine.at(i)->startPoint;//.............
        outstream << pScene->listLine.at(i)->endPoint;
        outstream << pScene->listLine.at(i)->listpointer;
    }
    return true;
}

bool MainWindow::openFile(QString nameFile)
{
    int number=0,rowdb=0,countradioelements=0,countline=0;
    QPointF p,sp,ep;
    qreal posx=0,posy=0,angle=0;
    //QString typeelement;
    QList <QPointF> lp;
    QFile file(nameFile);
    if (!file.open(QIODevice::ReadOnly))
    {QMessageBox::warning(this,tr("Чтение файла"),
                          tr("Не удалось открыть файл:\n %1").arg(file.errorString()),
                          QMessageBox::Ok|QMessageBox::Default);
        return false;
    }

    QDataStream instream (&file);

    qDebug()<<"---READ---";
    instream >> countradioelements;
    instream >> countline;
    qDebug()<<"countradioelements="<<countradioelements;
    qDebug()<<"countline="<<countline;
    for(int i=0;i<countradioelements;i++)
    {
        instream >> etype;
        instream >> posx;
        instream >> posy;
        p.setX(posx);p.setY(posy);
        instream >> number;
        instream >> rowdb;
        instream >> angle;
        qDebug()<<"etype="<<etype;
        qDebug()<<p;
        qDebug()<<"number="<<number;
        qDebug()<<"rowdb="<<rowdb;
        qDebug()<<"angle="<<angle;
        qDebug()<<"Iteraction====================";
        if(etype == RESISTOR){
            pScene->resistorobj = new ResistorClass(p,number);
            pScene->Set_Rotate_Elementn_on_Load(pScene->resistorobj, angle);
            instream >> pScene->resistorobj->Marking;
            instream >> pScene->resistorobj->Resistortype;
            instream >> pScene->resistorobj->Resistance;
            instream >> pScene->resistorobj->Power;
            instream >> pScene->resistorobj->Typeofshell;
            instream >> pScene->resistorobj->Length;
            instream >> pScene->resistorobj->Wight;
            instream >> pScene->resistorobj->Height;
            instream >> pScene->resistorobj->Thicknessofleg;
            pScene->addItem(pScene->resistorobj);
            pScene->radioelements.push_back(pScene->resistorobj);
        }qDebug()<<"Load1";
        if(etype == CONDENSATOR){
            pScene->condensatorobj = new CondensatorClass(p,number);
            pScene->Set_Rotate_Elementn_on_Load(pScene->condensatorobj, angle);
            instream >> pScene->condensatorobj->Marking;
            instream >> pScene->condensatorobj->Capacitortype;
            instream >> pScene->condensatorobj->Capacity;
            instream >> pScene->condensatorobj->Typeofshell;
            instream >> pScene->condensatorobj->Length;
            instream >> pScene->condensatorobj->Wight;
            instream >> pScene->condensatorobj->Height;
            instream >> pScene->condensatorobj->Thicknessofleg;
            pScene->addItem(pScene->condensatorobj);
            pScene->radioelements.push_back(pScene->condensatorobj);
        }
        if(etype == DIODE){
            pScene->diodeobj = new DiodeClass(p,number);
            pScene->Set_Rotate_Elementn_on_Load(pScene->diodeobj, angle);
            instream >> pScene->diodeobj->Marking;
            instream >> pScene->diodeobj->Diodetype;
            instream >> pScene->diodeobj->Breackdownvoltage;
            instream >> pScene->diodeobj->Typeofshell;
            instream >> pScene->diodeobj->Length;
            instream >> pScene->diodeobj->Wight;
            instream >> pScene->diodeobj->Height;
            instream >> pScene->diodeobj->Thicknessofleg;
            pScene->addItem(pScene->diodeobj);
            pScene->radioelements.push_back(pScene->diodeobj);
        }
        if(etype == TRANSISTOR){
            pScene->transistorobj = new TransistorClass(p,number);
            pScene->Set_Rotate_Elementn_on_Load(pScene->transistorobj, angle);
            instream >> pScene->transistorobj->Marking;
            instream >> pScene->transistorobj->Transistortype;
            instream >> pScene->transistorobj->Structure;
            instream >> pScene->transistorobj->Typeofshell;
            instream >> pScene->transistorobj->Length;
            instream >> pScene->transistorobj->Wight;
            instream >> pScene->transistorobj->Height;
            instream >> pScene->transistorobj->Thicknessofleg;
            pScene->addItem(pScene->transistorobj);
            pScene->radioelements.push_back(pScene->transistorobj);
        }
    }

    for(int i=0;i<countline;i++){
        instream >> etype;
        instream >> sp;
        instream >> ep;
        instream >> lp;
        qDebug()<<"etype="<<etype;
        qDebug()<<"sp="<<sp;
        qDebug()<<"ep="<<ep;
        qDebug()<<"lp="<<lp;

        pScene->myline = new MyLine(sp,ep,lp);
        pScene->addItem(pScene->myline);
        pScene->listLine.push_back(pScene->myline);
    }

    for(int i=0;i<pScene->listLine.count();i++){
        for(int j=0;j<pScene->radioelements.count();j++){
            for(int k=0;k<pScene->radioelements.at(j)->ancorpoint.count();k++)
            {
                if(pScene->listLine.at(i)->startPoint.x()+2 >= pScene->radioelements.at(j)->mapToScene(pScene->radioelements.at(j)->ancorpoint.at(k)).x() &&
                        pScene->listLine.at(i)->startPoint.x()-2 <= pScene->radioelements.at(j)->mapToScene(pScene->radioelements.at(j)->ancorpoint.at(k)).x() &&
                        pScene->listLine.at(i)->startPoint.y()+2 >= pScene->radioelements.at(j)->mapToScene(pScene->radioelements.at(j)->ancorpoint.at(k)).y() &&
                        pScene->listLine.at(i)->startPoint.y()-2 <= pScene->radioelements.at(j)->mapToScene(pScene->radioelements.at(j)->ancorpoint.at(k)).y())
                {   qDebug()<<"condition1";
                    pScene->listLine.at(i)->AddStartElement(pScene->radioelements.at(j),pScene->listLine.at(i)->startPoint);
                    pScene->radioelements.at(j)->addArrow(pScene->listLine.at(i));
                }
                qDebug()<<"ancorpoint.at(k)"<<pScene->radioelements.at(j)->mapToScene(pScene->radioelements.at(j)->ancorpoint.at(k));
                if(pScene->listLine.at(i)->endPoint.x()+2 >= pScene->radioelements.at(j)->mapToScene(pScene->radioelements.at(j)->ancorpoint.at(k)).x() &&
                        pScene->listLine.at(i)->endPoint.x()-2 <= pScene->radioelements.at(j)->mapToScene(pScene->radioelements.at(j)->ancorpoint.at(k)).x() &&
                        pScene->listLine.at(i)->endPoint.y()+2 >= pScene->radioelements.at(j)->mapToScene(pScene->radioelements.at(j)->ancorpoint.at(k)).y() &&
                        pScene->listLine.at(i)->endPoint.y()-2 <= pScene->radioelements.at(j)->mapToScene(pScene->radioelements.at(j)->ancorpoint.at(k)).y())
                {qDebug()<<"condition2";
                    pScene->listLine.at(i)->AddEndElement(pScene->radioelements.at(j),pScene->listLine.at(i)->endPoint);
                    pScene->radioelements.at(j)->addArrow(pScene->listLine.at(i));
                }
            }
            qDebug()<<"++++++++++++++++";
        }
    }

    return true;
}

void MainWindow::on_action_Save_triggered()
{
    QString nameFile = DirPath + fileName;
    if ( saveFile(nameFile) )
    { ui->action_Save->setEnabled(false);
        isSaved = true;
        updateWindowTitle();
    }
}

void MainWindow::on_action_Save_As_triggered()
{
    QString nameFile = QFileDialog::getSaveFileName(this, tr("Сохранение документа"),//Заголовок
                                                    DirPath, //Настройка на последнюю папку
                                                    tr("Файлы схем (*.bin)\n"));
    if (nameFile. isEmpty()) return ;
    if (saveFile(nameFile))
    {   ui->action_Save->setEnabled(false);
        isSaved = true;
        // Выделение имени файла из полного имени:
        fileName = nameFile.section('/', -1);
        // Выделение пути без имени файла
        DirPath = nameFile.remove(fileName);
        updateWindowTitle ();
    }
}

bool MainWindow::preparationReplacement()
{ if ( isSaved) return true; //Можно заменять текст
    int reply = QMessageBox::question(this,tr("Редактор"),
                                      tr("Документ был изменен.\n Сохранить изменения?"),
                                      QMessageBox::Yes|QMessageBox::Default,
                                      QMessageBox::No, QMessageBox::Cancel|QMessageBox::Escape);
    QString nameFile;
    int result;
    switch (reply)
    { case QMessageBox::Yes:
        if (fileName == "noName.txt")
        { nameFile = QFileDialog::getSaveFileName(this,
                                                  tr("Сохранение документа"),//Заголовок
                                                  DirPath, //Настройка на нужную папку. При tr(".") - на текущую
                                                  tr("Файлы схем (*.bin)\n"));
            if (nameFile.isEmpty()) return false;//Место сохранения не выбрано
            //Диалог вернет полное имя файла с путем
        }
        else nameFile = DirPath.append(fileName); //Собрали полное имя
        //Передаем полное имя файла:
        result = saveFile(nameFile); //Сохраняем документ
        if (result)
        { ui->action_Save->setEnabled(false);
            isSaved = true;
            // Выделение имени файла из полного имени:
            fileName = nameFile.section('/', -1);
            // Выделение пути без имени файла
            DirPath = nameFile.remove(fileName);
            updateWindowTitle ();
        }
        break;
    case QMessageBox::No: break; //Не сохраняем текст
    case QMessageBox::Cancel:
    default:
        return false; //Отказ от замены текста
    }
    return true;//Разрешено заменять текст
}

void MainWindow::on_action_Open_triggered()
{
    if ( ! preparationReplacement()) return;
    QString nameFile = QFileDialog::getOpenFileName(this,
                                                    tr("Открытие документа"),//Заголовок
                                                    DirPath, //Настройка на нужную папку.
                                                    tr("Файлы схем (*.bin)\n"));
    if (nameFile.isEmpty()) return;//Файл не выбран
    //Диалог вернул полное имя файла
    if (openFile(nameFile))
    {    qDebug()<<"fileOpen";
        ui->action_Save->setEnabled(false);
        isSaved = true;
        // Выделение имени файла из полного имени:
        fileName = nameFile.section('/', -1);
        // Выделение пути без имени файла
        DirPath = nameFile.remove(fileName);
        updateWindowTitle ();
    }
}

