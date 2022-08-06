#include "line.h"
#include "math.h"
#include <QPainter>
#include <QPen>
#include <QtMath>
#include <QDebug>
MyLine::MyLine(ElementItem *startItem, ElementItem *endItem, QPointF linestartpoint, QPointF lineendpoint, QObject  *parent) :
    QObject(parent), myStartItem(startItem), myEndItem(endItem),lineStartPoint(linestartpoint),lineEndPoint(lineendpoint)
{ 
    setFlag(QGraphicsItem::ItemIsSelectable);
    setAcceptHoverEvents(true);
    countS=0;
    countE=0;

    Sp.setX(myStartItem->pos().x());
    Sp.setY(myStartItem->pos().y());
    Ep.setX(myEndItem->pos().x());
    Ep.setY(myEndItem->pos().y());
    startPoint  = GetStartPoint(Sp,linestartpoint);
    endPoint = GetEndPoint(Ep,lineendpoint);

    if(myStartItem->angle==0 || myStartItem->angle==180 || myStartItem->angle==-180)
    {
        W.setX(startPoint.x());
        W.setY(startPoint.y()-((startPoint.y()-endPoint.y())/2));
        D.setX(endPoint.x());
        D.setY(endPoint.y()+((startPoint.y()-endPoint.y())/2));
    }
    if(myStartItem->angle==90 || myStartItem->angle==270 || myStartItem->angle==-90 || myStartItem->angle==-270)
    {
        W.setX(startPoint.x()-((startPoint.x()-endPoint.x())/2));
        W.setY(startPoint.y());
        D.setX(endPoint.x()+((startPoint.x()-endPoint.x())/2));
        D.setY(endPoint.y());
    }
    listpointer.push_back(startPoint);
    listpointer.push_back(W);
    listpointer.push_back(D);
    listpointer.push_back(endPoint);

    listelements.push_back(startItem);
    listelements.push_back(endItem);
}

MyLine::MyLine(QPointF linestartpoint, QPointF lineendpoint,QObject  *parent) :
    QObject(parent),lineStartPoint(linestartpoint),lineEndPoint(lineendpoint)
{
    setFlag(QGraphicsItem::ItemIsSelectable);
    setAcceptHoverEvents(true);
    countS=0;
    countE=0;
    StartItemisDelete=true;
    EndItemisDelete=true;
    myStartItem=nullptr;
    myEndItem=nullptr;

    Sp.setX(linestartpoint.x());
    Sp.setY(linestartpoint.y());
    Ep.setX(lineendpoint.x());
    Ep.setY(lineendpoint.y());

    startPoint  = Sp;
    endPoint = Ep;
    W.setX(Sp.x()-((Sp.x()-Ep.x())/2));
    W.setY(Sp.y());
    D.setX(Ep.x()+((Sp.x()-Ep.x())/2));
    D.setY(Ep.y());

    listpointer.push_back(startPoint);
    listpointer.push_back(W);
    listpointer.push_back(D);
    listpointer.push_back(endPoint);

    listelements.push_back(0);
    listelements.push_back(0);
}

MyLine::MyLine(ElementItem *startItem, QPointF linestartpoint, QPointF lineendpoint,QObject  *parent) :
    QObject(parent), myStartItem(startItem),lineStartPoint(linestartpoint),lineEndPoint(lineendpoint)
{
    setFlag(QGraphicsItem::ItemIsSelectable);
    setAcceptHoverEvents(true);
    countS=0;
    countE=0;
    EndItemisDelete=true;
    myEndItem=nullptr;
    Sp.setX(myStartItem->pos().x());
    Sp.setY(myStartItem->pos().y());
    Ep.setX(lineendpoint.x());
    Ep.setY(lineendpoint.y());

    startPoint  = GetStartPoint(Sp,linestartpoint);
    endPoint = Ep;

    W.setX(startPoint.x()-((startPoint.x()-Ep.x())/2));
    W.setY(startPoint.y());
    D.setX(Ep.x()+((startPoint.x()-Ep.x())/2));
    D.setY(Ep.y());

    listpointer.push_back(startPoint);
    listpointer.push_back(W);
    listpointer.push_back(D);
    listpointer.push_back(endPoint);

    listelements.push_back(startItem);
    listelements.push_back(0);
}

MyLine::MyLine(QPointF linestartpoint, QPointF lineendpoint, ElementItem *endItem, QObject  *parent) :
    QObject(parent), myEndItem(endItem),lineStartPoint(linestartpoint),lineEndPoint(lineendpoint)
{
    setFlag(QGraphicsItem::ItemIsSelectable);
    setAcceptHoverEvents(true);
    countS=0;
    countE=0;
    StartItemisDelete=true;
    myStartItem=nullptr;

    Sp.setX(linestartpoint.x());
    Sp.setY(linestartpoint.y());
    Ep.setX(myEndItem->pos().x());
    Ep.setY(myEndItem->pos().y());

    startPoint  = Sp;
    endPoint = GetEndPoint(Ep,lineendpoint);

    W.setX(Sp.x()-((Sp.x()-endPoint.x())/2));
    W.setY(Sp.y());
    D.setX(endPoint.x()+((Sp.x()-endPoint.x())/2));
    D.setY(endPoint.y());

    listpointer.push_back(startPoint);
    listpointer.push_back(W);
    listpointer.push_back(D);
    listpointer.push_back(endPoint);

    listelements.push_back(0);
    listelements.push_back(endItem);
}

MyLine::MyLine(QPointF linestartpoint,QPointF lineendpoint,QList <QPointF> listpoint,QObject  *parent) :
    QObject(parent),lineStartPoint(linestartpoint),lineEndPoint(lineendpoint)
{
    setFlag(QGraphicsItem::ItemIsSelectable);
    setAcceptHoverEvents(true);
    countS=0;
    countE=0;
    StartItemisDelete=true;
    EndItemisDelete=true;
    myStartItem=nullptr;
    myEndItem=nullptr;

    startPoint=linestartpoint;
    endPoint=lineendpoint;
    listpointer=listpoint;
}

MyLine::MyLine(DotSignal *DotstartItem, DotSignal *DotendItem, QPointF linestartpoint, QPointF lineendpoint,QObject *parent) :
    QObject(parent), dotStartItem(DotstartItem), dotEndItem(DotendItem),lineStartPoint(linestartpoint),lineEndPoint(lineendpoint)
{
    setFlag(QGraphicsItem::ItemIsSelectable);
    setAcceptHoverEvents(true);
    countS=0;
    countE=0;

    myStartItem = qgraphicsitem_cast<ElementItem*>(dotStartItem->parentItem());
    myEndItem = qgraphicsitem_cast<ElementItem*>(dotEndItem->parentItem());
    Sp.setX(myStartItem->pos().x());
    Sp.setY(myStartItem->pos().y());
    Ep.setX(myEndItem->pos().x());
    Ep.setY(myEndItem->pos().y());

    startPoint  = GetStartPoint(Sp,linestartpoint);
    endPoint = GetEndPoint(Ep,lineendpoint);

    W.setX(startPoint.x()-((startPoint.x()-endPoint.x())/2));
    W.setY(startPoint.y());
    D.setX(endPoint.x()+((startPoint.x()-endPoint.x())/2));
    D.setY(endPoint.y());

    listpointer.push_back(startPoint);
    listpointer.push_back(W);
    listpointer.push_back(D);
    listpointer.push_back(endPoint);

    listelements.push_back(myStartItem);
    listelements.push_back(myEndItem);
}

MyLine::MyLine(ElementItem *startItem, DotSignal *DotendItem, QPointF linestartpoint, QPointF lineendpoint,QObject  *parent):
    QObject(parent), myStartItem(startItem), dotEndItem(DotendItem),lineStartPoint(linestartpoint),lineEndPoint(lineendpoint)
{
    setFlag(QGraphicsItem::ItemIsSelectable);
    setAcceptHoverEvents(true);
    countS=0;
    countE=0;
    myEndItem = qgraphicsitem_cast<ElementItem*>(dotEndItem->parentItem());
    Sp.setX(myStartItem->pos().x());
    Sp.setY(myStartItem->pos().y());
    Ep.setX(myEndItem->pos().x());
    Ep.setY(myEndItem->pos().y());

    startPoint  = GetStartPoint(Sp,linestartpoint);;
    endPoint = GetEndPoint(Ep,lineendpoint);;

    W.setX(startPoint.x()-((startPoint.x()-endPoint.x())/2));
    W.setY(startPoint.y());
    D.setX(endPoint.x()+((startPoint.x()-endPoint.x())/2));
    D.setY(endPoint.y());

    listpointer.push_back(startPoint);
    listpointer.push_back(W);
    listpointer.push_back(D);
    listpointer.push_back(endPoint);

    listelements.push_back(myStartItem);
    listelements.push_back(myEndItem);
}

MyLine::MyLine(DotSignal *DotstartItem, ElementItem *endItem, QPointF linestartpoint, QPointF lineendpoint,QObject  *parent) :
    QObject(parent), dotStartItem(DotstartItem), myEndItem(endItem),lineStartPoint(linestartpoint),lineEndPoint(lineendpoint)
{
    setFlag(QGraphicsItem::ItemIsSelectable);
    setAcceptHoverEvents(true);
    countS=0;
    countE=0;

    myStartItem = qgraphicsitem_cast<ElementItem*>(dotStartItem->parentItem());
    Sp.setX( myStartItem->pos().x());
    Sp.setY( myStartItem->pos().y());
    Ep.setX(myEndItem->pos().x());
    Ep.setY(myEndItem->pos().y());

    startPoint  = Sp;
    endPoint = GetEndPoint(Ep,lineendpoint);
    ;

    W.setX(startPoint.x()-((startPoint.x()-endPoint.x())/2));
    W.setY(startPoint.y());
    D.setX(endPoint.x()+((startPoint.x()-endPoint.x())/2));
    D.setY(endPoint.y());

    listpointer.push_back(startPoint);
    listpointer.push_back(W);
    listpointer.push_back(D);
    listpointer.push_back(endPoint);


    listelements.push_back(myStartItem);
    listelements.push_back(myEndItem);
}

MyLine::MyLine(DotSignal *DotstartItem, QPointF linestartpoint, QPointF lineendpoint,QObject *parent) :
    QObject(parent), dotStartItem(DotstartItem),lineStartPoint(linestartpoint),lineEndPoint(lineendpoint)
{
    setFlag(QGraphicsItem::ItemIsSelectable);
    setAcceptHoverEvents(true);
    countS=0;
    countE=0;
    EndItemisDelete=true;
    myEndItem=nullptr;
    myStartItem = qgraphicsitem_cast<ElementItem*>(dotStartItem->parentItem());
    Sp.setX(myStartItem->pos().x());
    Sp.setY(myStartItem->pos().y());
    Ep.setX(lineendpoint.x());
    Ep.setY(lineendpoint.y());

    startPoint  = GetStartPoint(Sp,linestartpoint);
    endPoint = Ep;

    W.setX(startPoint.x()-((startPoint.x()-Ep.x())/2));
    W.setY(startPoint.y());
    D.setX(Ep.x()+((startPoint.x()-Ep.x())/2));
    D.setY(Ep.y());

    listpointer.push_back(startPoint);
    listpointer.push_back(W);
    listpointer.push_back(D);
    listpointer.push_back(endPoint);

    listelements.push_back(myStartItem);
    listelements.push_back(0);

}

MyLine::MyLine(QPointF linestartpoint, QPointF lineendpoint, DotSignal *DotendItem, QObject *parent) :
    QObject(parent), dotEndItem(DotendItem),lineStartPoint(linestartpoint),lineEndPoint(lineendpoint)
{
    setFlag(QGraphicsItem::ItemIsSelectable);
    setAcceptHoverEvents(true);
    countS=0;
    countE=0;
    StartItemisDelete=true;
    myStartItem=nullptr;
    myEndItem = qgraphicsitem_cast<ElementItem*>(dotEndItem->parentItem());
    Sp.setX(linestartpoint.x());
    Sp.setY(linestartpoint.y());
    Ep.setX(myEndItem->pos().x());
    Ep.setY(myEndItem->pos().y());

    startPoint  = Sp;
    endPoint = GetEndPoint(Ep,lineendpoint);

    W.setX(Sp.x()-((Sp.x()-endPoint.x())/2));
    W.setY(Sp.y());
    D.setX(endPoint.x()+((Sp.x()-endPoint.x())/2));
    D.setY(endPoint.y());

    listpointer.push_back(startPoint);
    listpointer.push_back(W);
    listpointer.push_back(D);
    listpointer.push_back(endPoint);

    listelements.push_back(0);
    listelements.push_back(myEndItem);
}

MyLine::~MyLine(){}

void MyLine::setPath(const QPainterPath &path)
{
    QGraphicsPathItem::setPath(path);
}

float MyLine::GetDistance(QPointF ancor,QPointF linepoint)
{
    float distance;
    distance=sqrt(ancor.x()*ancor.x()-2*ancor.x()*linepoint.x()+
                  linepoint.x()*linepoint.x()+ancor.y()*ancor.y()-
                  2*ancor.y()*linepoint.y()+linepoint.y()*linepoint.y());
    return distance;
}

QPointF MyLine::GetStartPoint(QPointF center,QPointF linepoint)
{
    QPointF minDistancePoint;
    QList<QPointF> inputs = myStartItem->GetInputs(center);
    float minDistance = 1000;
    if(countS<=inputs.count())
    {
        foreach(QPointF ancor, inputs)
        {
            countS++;
            float currentDistance = GetDistance(ancor,linepoint);
            if (currentDistance < minDistance)
            {
                minDistance = currentDistance;
                minDistancePoint = ancor;
                position1 = inputs.indexOf(ancor);
            }
        }
    }
    //qDebug()<<"GetInputsStart="<<inputs.at(position1);
    return inputs.at(position1);

    Q_UNUSED(center);
}
void MyLine::ExeguteGetStartPoint(){startPoint= GetStartPoint(Sp,lineStartPoint);qDebug()<<"GetStartPoint="<<startPoint;}

QPointF MyLine::GetEndPoint(QPointF center,QPointF linepoint)
{
    QPointF minDistancePoint;
    QList<QPointF> inputs = myEndItem->GetInputs(center);
    //QList<QPointF> inputs = myEndItem->GetlistDotElementsCoordinate();
    float minDistance = 1000;
    if(countE<=inputs.count())
    {
        foreach(QPointF ancor, inputs)
        {
            countE++;
            float currentDistance = GetDistance(ancor,linepoint);
            if (currentDistance < minDistance)
            {
                minDistance = currentDistance;
                minDistancePoint = ancor;
                position2 = inputs.indexOf(ancor);
            }
        }
    }
    //qDebug()<<"GetInputsEnd="<<inputs.at(position1);
    return inputs.at(position2);
    Q_UNUSED(center);
}

void MyLine::ExeguteGetEndPoint(){endPoint = GetEndPoint(Ep,lineEndPoint);qDebug()<<"GetEndPoint="<<endPoint;}

void MyLine::SetPositionDotes()
{
    for(int i=0;i<listDotes.count();i++)
    {
        listDotes.at(i)->setPos(listpointer.at(i));
    }
}

void MyLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)//------------------------------------------------------------
{//qDebug()<<"PaintLine1";

    QPen pen;
    pen.setWidth(5);
    pen.setBrush(Qt::black);
    painter->setPen(pen);
    // qDebug()<<"SceneMouseEventPos = "<<SceneMouseEventPos;

    if(listelements.at(0)!=NULL && listelements.at(1)!=NULL)
    {
        if(this->isSelected() && this->myStartItem->isSelected() && this->myEndItem->isSelected())
        {//qDebug()<<"deleteDots";
            pen.setBrush(Qt::gray);
            painter->setPen(pen);
            this->setZValue(500);
            if(!listDotes.isEmpty()){
                foreach (DotSignal *dot, listDotes) {
                    dot->deleteLater();}
                listDotes.clear();
            }
        }
        //qDebug()<<"PaintLine1.1";
        if((this->isSelected() && !this->myStartItem->isSelected() && !this->myEndItem->isSelected()) ||
                (this->isSelected() && this->myStartItem->isSelected() && !this->myEndItem->isSelected()) ||
                (this->isSelected() && !this->myStartItem->isSelected() && this->myEndItem->isSelected()))
        {pen.setBrush(Qt::gray);
            painter->setPen(pen);
            this->setZValue(500);
            if(listDotes.isEmpty())
            {for(int i=0;i<listpointer.count();i++)
                {   dot=new DotSignal(listpointer.at(i),this);
                    dot->setDotFlags(DotSignal::Movable);
                    dot->setLineFlag(true);
                    listDotes.append(dot);
                }
            }
        }
    }

    if((this->isSelected() && listelements.at(0)!=NULL && listelements.at(1)==NULL && this->myStartItem->isSelected()) ||
            (this->isSelected() && listelements.at(0)==NULL && listelements.at(1)!=NULL && this->myEndItem->isSelected()))
    {//qDebug()<<"deleteDots2";
        pen.setBrush(Qt::gray);
        painter->setPen(pen);
        this->setZValue(500);
        if(!listDotes.isEmpty()){
            foreach (DotSignal *dot, listDotes) {
                dot->deleteLater();}
            listDotes.clear();
        }
    }
    else if((this->isSelected() && listelements.at(0)==NULL && listelements.at(1)==NULL) ||
            (this->isSelected() && listelements.at(0)!=NULL && listelements.at(1)==NULL && !this->myStartItem->isSelected()) ||
            (this->isSelected() && listelements.at(0)==NULL && listelements.at(1)!=NULL && !this->myEndItem->isSelected()))
    {
        pen.setBrush(Qt::gray);
        painter->setPen(pen);
        this->setZValue(500);
        if(listDotes.isEmpty())
        {for(int i=0;i<listpointer.count();i++)
            {   dot=new DotSignal(listpointer.at(i),this);
                dot->setDotFlags(DotSignal::Movable);
                dot->setLineFlag(true);
                listDotes.append(dot);
            }
        }
    }

    //qDebug()<<"PaintLine1.3";
    enddot=listDotes.count()-1;
    endpoint=listpointer.count()-1;

    if(!this->isSelected())
    {this->setZValue(-1000);
        if(!listDotes.isEmpty()){
            foreach (DotSignal *dot, listDotes) {
                dot->deleteLater();}
            listDotes.clear();
        }
    }
    //qDebug()<<"PaintLine1.4";
    //qDebug()<<"listelements = "<<listelements;
    if(!listelements.isEmpty() && listelements.at(0)!=NULL && listelements.at(1)!=NULL && !myStartItem->isSelected() && !myEndItem->isSelected())
    {qDebug()<<"START_&_END_NOT_NULL";
        listpointerUnderstudy.clear();
        for(int i=1;i<listpointer.count()-1;i++)
        {listpointerUnderstudy.push_back(listpointer.at(i)); }

        if(listpointerUnderstudy.count()!=listpointer.count()-2)
        {    listpointerUnderstudy.clear();
            for(int i=1;i<listpointer.count()-1;i++)
            {listpointerUnderstudy.push_back(listpointer.at(i)); }
        }
        if(listpointer.count()==2)
        {   for(int i=0;i<listpointer.count();i++)
            {listpointerUnderstudy.push_back(listpointer.at(i)); }
        }
    }
    ////    qDebug()<<"PaintLine1.4.2";
    if(!listelements.isEmpty() && listelements.at(0)!=NULL && !myStartItem->isSelected() && listelements.at(1)==NULL)
    {qDebug()<<"START_NOT_NULL";
        listpointerUnderstudy.clear();
        for(int i=1;i<listpointer.count();i++)
        {listpointerUnderstudy.push_back(listpointer.at(i)); }

        if(listpointerUnderstudy.count()!=listpointer.count()-1)
        {    listpointerUnderstudy.clear();
            for(int i=1;i<listpointer.count();i++)
            {listpointerUnderstudy.push_back(listpointer.at(i)); }
        }
        if(listpointer.count()==2)
        {   for(int i=0;i<listpointer.count();i++)
            {listpointerUnderstudy.push_back(listpointer.at(i)); }
        }
    }
    //   qDebug()<<"PaintLine1.4.3";
    if(!listelements.isEmpty() && listelements.at(0)==NULL && listelements.at(1)!=NULL && !myEndItem->isSelected())
    {qDebug()<<"END_NOT_NULL";
        listpointerUnderstudy.clear();
        for(int i=0;i<listpointer.count()-1;i++)
        {listpointerUnderstudy.push_back(listpointer.at(i)); }

        if(listpointerUnderstudy.count()!=listpointer.count()-1)
        {    listpointerUnderstudy.clear();
            for(int i=0;i<listpointer.count()-1;i++)
            {listpointerUnderstudy.push_back(listpointer.at(i)); }
        }
        if(listpointer.count()==2)
        {   for(int i=0;i<listpointer.count();i++)
            {listpointerUnderstudy.push_back(listpointer.at(i)); }
        }
    }
    ////qDebug()<<"PaintLine1.5";
    if(listelements.at(0)==NULL && listelements.at(1)==NULL)
    {if(horizontal==false && popadanie_horizontal==false && vertical==false && popadanie_vertical==false)
        {
            qDebug()<<"ELEMENTS_NULL";
            listpointerUnderstudy.clear();
            for(int i=0;i<listpointer.count();i++)
            {listpointerUnderstudy.push_back(listpointer.at(i)); }

            if(listpointerUnderstudy.count()!=listpointer.count())
            {
                listpointerUnderstudy.clear();
                for(int i=0;i<listpointer.count();i++)
                {listpointerUnderstudy.push_back(listpointer.at(i)); }
            }
        }
    }

    //qDebug()<<"PaintLine2";
    if(!listDotes.isEmpty())

    {if(connectionSP==false && listelements.at(0)!=NULL  && listDotes.at(0)->isSelected()==true && listDotes.at(0)->GetDotHoverEvent()==true && listDotes.at(0)->Movable==1)
        {qDebug()<<"Dot_0_is_Movable";
            disconnectionSP=true;
            this->deleteStartAncorElements();
        }
        //qDebug()<<"PaintLine2.2";
        if(connectionEP==false && listelements.at(1)!=NULL  && listDotes.at(enddot)->isSelected()==true && listDotes.at(enddot)->GetDotHoverEvent()==true && listDotes.at(enddot)->Movable==1 )
        {qDebug()<<"Dot_end_is_Movable";
            disconnectionEP=true;
            this->deleteEndAncorElements();
        }

        if(listDotes.at(0)->MoveDotsFlag()==false && listelements.at(0)==NULL )
        {//qDebug()<<"disconnectionSP=false;connectionSP=false;";
            disconnectionSP=false;connectionSP=false;}
        if(listDotes.at(enddot)->MoveDotsFlag()==false && listelements.at(1)==NULL)
        {//qDebug()<<"disconnectionEP=false;connectionEP=false;";
            disconnectionEP=false;connectionEP=false;}
    }
    //qDebug()<<"PaintLine3";
    //qDebug()<<"SceneMouseEventPosOffset="<<SceneMouseEventPosOffset;
    qDebug()<<"listpointer="<<listpointer;
    qDebug()<<"listpointerUnderstudy="<<listpointerUnderstudy;
    //qDebug()<<"this->isUnderMouse()==true"<<this->isUnderMouse();
    //qDebug()<<"mouseLeftbuttonPress"<<mouseLeftbuttonPress;
    //    qDebug()<<"startPoint="<<startPoint;
    //    qDebug()<<"endPoint="<<endPoint;
    //qDebug()<<"PaintLine3.5";
    if(StartItemisDelete==false)
    {       Sp.setX(myStartItem->pos().x());
        Sp.setY(myStartItem->pos().y());
        //qDebug()<<"myStartItem->scenePos()="<<Sp;
        startPoint=(GetStartPoint(Sp,lineStartPoint));//qDebug()<<"startPoint="<<startPoint;//startPoint = GetStartPoint(Sp,lineStartPoint);}
        listpointer.replace(0,startPoint);
    }
    if(EndItemisDelete==false)
    {       Ep.setX(myEndItem->pos().x());
        Ep.setY(myEndItem->pos().y());
        //qDebug()<<"myEndItem->scenePos()="<<Ep;
        endPoint=(GetEndPoint(Ep,lineEndPoint));//qDebug()<<"endPoint="<<endPoint;//endPoint = GetEndPoint(Ep,lineEndPoint);}
        listpointer.replace(listpointer.count()-1,endPoint);
    }

    if(StartItemisDelete==true)
    {
        startPoint=listpointer.at(0);
    }
    if(EndItemisDelete==true)
    {
        endPoint=listpointer.at(endpoint);
    }

    //if(!listDotes.isEmpty()){
    //qDebug()<<"listDotes0="<<listDotes.at(0)->scenePos()<<"listDotesEnd="<<listDotes.at(enddot)->scenePos();}
    //qDebug()<<"PaintLine4";
    if(!listDotes.isEmpty() && this->isSelected() && listDotes.at(0)->isSelected() && listelements.at(0)==NULL)//!listDotes.isEmpty() &&
    {//qDebug()<<"if(hoverenter==true && this->isSelected() && listelements.at(0)==NULL)";
        startPoint.setX(listDotes.at(0)->x());
        startPoint.setY(listDotes.at(0)->y());
        listpointer.replace(0,startPoint);
    }
    if(!listDotes.isEmpty() && this->isSelected() && listDotes.at(enddot)->isSelected() && listelements.at(1)==NULL)//!listDotes.isEmpty() &&
    {//qDebug()<<"if(hoverenter==true && this->isSelected() && listelements.at(1)==NULL)";
        endPoint.setX(listDotes.at(enddot)->x());
        endPoint.setY(listDotes.at(enddot)->y());
        listpointer.replace(listpointer.count()-1,endPoint);
    }
    //qDebug()<<"PaintLine5";

    if((StartItemisDelete==false && listelements.at(0)!=NULL && listelements.at(1)!=NULL && myStartItem->isSelected() && !myEndItem->isSelected()) ||
            (StartItemisDelete==false && listelements.at(0)!=NULL && listelements.at(1)==NULL && myStartItem->isSelected()))
    {//qDebug()<<"myStartItem->MoveElementFlag()"<<myStartItem->MoveElementFlag();
        if(myStartItem->isSelected() && myStartItem->MoveElementFlag()==true)
        {
            QPointF zamena;
            if(listpointer.count()==2)
            {  qDebug()<<"zamena_insert_strat";
                zamena.setX(listpointer.at(endpoint).x());
                zamena.setY(listpointer.at(endpoint).y());
                //qDebug()<<"listpointer="<<listpointer;
                listpointer.insert(1,zamena);
                if(this->isSelected())
                {   dot=new DotSignal(listpointer.at(1),this);
                    dot->setDotFlags(DotSignal::Movable);
                    dot->setLineFlag(true);
                    listDotes.append(dot);
                }
            }
            LineСhangeAlgorithmStart();
        }
    }
    //qDebug()<<"PaintLine6";
    if((EndItemisDelete==false && listelements.at(0)!=NULL && listelements.at(1)!=NULL && !myStartItem->isSelected() && myEndItem->isSelected()) ||
            (EndItemisDelete==false && listelements.at(0)==NULL && listelements.at(1)!=NULL && myEndItem->isSelected()))
    {
        if(myEndItem->isSelected() && myEndItem->MoveElementFlag()==true)
        {//qDebug()<<"myEndItem->MoveElementFlag()"<<myEndItem->MoveElementFlag();
            QPointF zamena;
            if(listpointer.count()==2)
            {  qDebug()<<"zamena_insert_end";
                zamena.setX(listpointer.at(0).x());
                zamena.setY(listpointer.at(0).y());
                listpointer.insert(1,zamena);
                if(this->isSelected())
                {   dot=new DotSignal(listpointer.at(1),this);
                    dot->setDotFlags(DotSignal::Movable);
                    dot->setLineFlag(true);
                    listDotes.append(dot);
                    listDotes.at(enddot)->setSelected(true);
                }
            }
            LineСhangeAlgorithmEnd();
        }//qDebug()<<"==============================";
    }
    //qDebug()<<"PaintLine7";
    if(this->isSelected() && !listDotes.isEmpty() && listelements.at(0)==NULL && listDotes.at(0)->isSelected() && listDotes.at(0)->Movable==1)
    {qDebug()<<"if(hoverenter==true && this->isSelected() && listelements.at(0)==NULL)";
        LineСhangeAlgorithmStart();
    }
    if(this->isSelected() && !listDotes.isEmpty() && listelements.at(1)==NULL && listDotes.at(enddot)->isSelected() && listDotes.at(enddot)->Movable==1)
    {    LineСhangeAlgorithmEnd();

    }
    //qDebug()<<"PaintLine8";

    //qDebug()<<"PaintLine9";
    //event->modifiers() & Qt::ControlModifier
    if(Shiftpushed==true && this->isSelected())//Shiftpushed==true
    {//qDebug()<<"Shift_Pused";
        for(int i=0;i<listDotes.count();i++)
        {//qDebug()<<"Shift_Pused2";
            if(listDotes.at(i)->isSelected())
            {//qDebug()<<"Shift_Pused3";
                //qDebug()<<"i="<<i;
                if(i<listDotes.count()-1 && (int)listpointer.at(i).x()==(int)listpointer.at(i+1).x() && (int)listpointer.at(i).y()==(int)listpointer.at(i+1).y())
                {qDebug()<<"i2="<<i;
                    scene()->removeItem(listDotes.at(i));
                    listDotes.removeAt(i);
                    scene()->removeItem(listDotes.at(i+1));
                    listDotes.removeAt(i+1);
                    listpointer.removeAt(i+1);
                    listpointer.removeAt(i);
                }
                //qDebug()<<"i2="<<i;

                if(i>0 && (int)listpointer.at(i).x()==(int)listpointer.at(i-1).x() && (int)listpointer.at(i).y()==(int)listpointer.at(i-1).y())
                {qDebug()<<"i3="<<i;
                    scene()->removeItem(listDotes.at(i));
                    listDotes.removeAt(i);
                    scene()->removeItem(listDotes.at(i-1));
                    listDotes.removeAt(i-1);
                    listpointer.removeAt(i);
                    listpointer.removeAt(i-1);
                }
            }
        }
    }

    //qDebug()<<"PaintLine10";
    //qDebug()<<"listpointer_before="<<listpointer;
    //updateListDotes();
    LineStraightnessTest();
    SetPositionDotes();
    //    qDebug()<<"listpointer="<<listpointer;
    //    qDebug()<<"listpointerUnderstudy="<<listpointerUnderstudy;

    QPainterPath path;
    path.moveTo(startPoint);
    foreach (QPointF p,listpointer)
    {
        path.lineTo(p);
    }
    path.lineTo(endPoint);
    painter->drawPath(path);
    this->setPath(path);

    //qDebug()<<"PaintLine11";
    Q_UNUSED(option);
    Q_UNUSED(widget);
}//---------------------------------------------------------------------------------------------------------------------------------------------------------

bool MyLine::ctrlpush(bool b){return Ctrlpushed = b;}
bool MyLine::shiftpush(bool b){return Shiftpushed = b;}

void MyLine::deleteStartAncorElements()
{qDebug()<<"StartItemisDelete="<<StartItemisDelete;
    qDebug()<<"EndItemisDelete="<<EndItemisDelete;
    if(StartItemisDelete==false && listelements.at(0)!=NULL)
    {qDebug()<<"DeleteStartItem1=";
        //        if(!listDotes.isEmpty() && listDotes.at(0)->isSelected())
        //        {   //..................^ ^
        //           qDebug()<<"DeleteStartItem2=";
        listelements.replace(0,0);
        //qDebug()<<"DeleteStartItem3=";
        countS=0;
        Sp.setX(0);
        Sp.setY(0);
        lineStartPoint.setX(0);
        lineStartPoint.setY(0);
        myStartItem=nullptr;
        StartItemisDelete=true;
        //qDebug()<<"StartItemisDelete2="<<StartItemisDelete;
        //}
    }
}
void MyLine::deleteEndAncorElements()
{
    if(EndItemisDelete==false && listelements.at(1)!=NULL)
    {
        //        if(!listDotes.isEmpty() && listDotes.at(enddot)->isSelected())
        //        {
        qDebug()<<"DeletemyEndItem3=";
        listelements.replace(1,0);
        countE=0;
        Ep.setX(0);
        Ep.setY(0);
        lineEndPoint.setX(0);
        lineEndPoint.setY(0);
        myEndItem=nullptr;
        EndItemisDelete=true;
        //qDebug()<<"myEndItem2=";
        // }
    }
}


void MyLine::AddAncorStartElements(ElementItem *item)
{qDebug()<<"FUNCTION1="<<disconnectionSP;
    if(this->isSelected() && listelements.at(0)==NULL && disconnectionSP==false)
    {qDebug()<<"AddStartItem1=";
        listelements.replace(0,item);
        Sp.setX(item->pos().x());
        Sp.setY(item->pos().y());
        lineStartPoint.setX(listDotes.at(0)->pos().x());
        lineStartPoint.setY(listDotes.at(0)->pos().y());
        qDebug()<<"item1="<<Sp;
        //qDebug()<<"listDotes1="<<lineStartPoint;
        item->addArrow(this);
        myStartItem=item;
        startPoint  = GetStartPoint(Sp,lineStartPoint);
        listDotes.at(0)->setDotFlags(0);
        StartItemisDelete=false;
        connectionSP=true;
        qDebug()<<"AddStartItem=";
    }
}
void MyLine::AddAncorEndElements(ElementItem* item)
{
    if(this->isSelected() && listelements.at(1)==NULL && disconnectionEP==false)
    {qDebug()<<"AddEndItem1=";
        //qDebug()<<"countE="<<countE;
        listelements.replace(1,item);
        Ep.setX(item->pos().x());
        Ep.setY(item->pos().y());
        lineEndPoint.setX(listDotes.at(enddot)->pos().x());
        lineEndPoint.setY(listDotes.at(enddot)->pos().y());
        item->addArrow(this);
        myEndItem=item;
        endPoint = GetEndPoint(Ep,lineEndPoint);
        listDotes.at(enddot)->setDotFlags(0);
        EndItemisDelete=false;
        connectionEP=true;
    }
}

void MyLine::AddStartElement(ElementItem* item,QPointF sp)
{
    //qDebug()<<"AddSI1=";
    listelements.insert(0,item);
    Sp.setX(item->pos().x());
    Sp.setY(item->pos().y());
    //        lineStartPoint.setX(listDotes.at(0)->pos().x());
    //        lineStartPoint.setY(listDotes.at(0)->pos().y());
    myStartItem=item;
    startPoint  = GetStartPoint(Sp,sp);
    //listDotes.at(0)->setDotFlags(0);
    StartItemisDelete=false;
    connectionSP=true;
    //qDebug()<<"AddSI3=";
}
void MyLine::AddEndElement(ElementItem* item,QPointF ep)
{
    qDebug()<<"AddEI2=";
    listelements.insert(1,item);
    Ep.setX(item->pos().x());
    Ep.setY(item->pos().y());
    //        lineEndPoint.setX(listDotes.at(enddot)->pos().x());
    //        lineEndPoint.setY(listDotes.at(enddot)->pos().y());
    myEndItem=item;
    endPoint = GetEndPoint(Ep,ep);
    //listDotes.at(enddot)->setDotFlags(0);
    EndItemisDelete=false;
    connectionEP=true;
}

DotSignal* MyLine::StartDot()
{
    return listDotes.at(0);
}
DotSignal* MyLine::EndDot()
{
    return listDotes.at(enddot);
}
bool MyLine::HoverEnter()
{return hoverenter;}

void MyLine::SetKoncyOtrezka(QPointF mousePos)
{
    for(int i=0;i<listpointer.count()-1;i++)//определяем вертикальныи отрезок или горизонтальный
    {
        if(listpointer.at(i).x()==listpointer.at(i+1).x())//если вертикальный
        {
            vertical=true;
            horizontal=false;
            if(listpointer.at(i).y()<mousePos.y() &&
                    mousePos.y()<listpointer.at(i+1).y() &&
                    mousePos.x()<listpointer.at(i).x()+20 &&
                    mousePos.x()>listpointer.at(i).x()-20)
            {popadanie_vertical=true;
                popadanie_horizontal=false;
                nachalo_otrezka=i;
                konec_otrezka=i+1;
                break;}
            if(listpointer.at(i).y()>mousePos.y() &&
                    mousePos.y()>listpointer.at(i+1).y() &&
                    mousePos.x()<listpointer.at(i).x()+20 &&
                    mousePos.x()>listpointer.at(i).x()-20)
            {popadanie_vertical=true;
                popadanie_horizontal=false;
                nachalo_otrezka=i;
                konec_otrezka=i+1;
                break;}
        }

        if(listpointer.at(i).y()==listpointer.at(i+1).y())//если горизонтальный
        {
            horizontal=true;
            vertical=false;
            if(listpointer.at(i).x()<mousePos.x() &&
                    mousePos.x()<listpointer.at(i+1).x() &&
                    mousePos.y()<listpointer.at(i).y()+20 &&
                    mousePos.y()>listpointer.at(i).y()-20)
            {popadanie_horizontal=true;
                popadanie_vertical=false;
                nachalo_otrezka=i;
                konec_otrezka=i+1;
                break;}
            if(listpointer.at(i).x()>mousePos.x() &&
                    mousePos.x()>listpointer.at(i+1).x() &&
                    mousePos.y()<listpointer.at(i).y()+20 &&
                    mousePos.y()>listpointer.at(i).y()-20)
            {popadanie_horizontal=true;
                popadanie_vertical=false;
                nachalo_otrezka=i;
                konec_otrezka=i+1;
                break;}
        }
    }
}

void MyLine::LineAjustment()
{
    for(int i=0;i<listpointer.count()-2;i++)
    {
        qreal dx,dy;
        dx=abs(listpointer.at(i).x()-listpointer.at(i+1).x());
        dy=abs(listpointer.at(i).y()-listpointer.at(i+1).y());
        if(dy>dx && listpointer.at(i).x()!=listpointer.at(i+1).x())//если отрезок вертикальный
        {
            QPointF zamena;
            zamena.setX(listpointer.at(i+1).x());
            zamena.setY(listpointer.at(i).y());
            listpointer.replace(i,zamena);
        }

        if(dx>dy && listpointer.at(i).y()!=listpointer.at(i+1).y())//если отрезок горизонтальный
        {
            QPointF zamena;
            zamena.setX(listpointer.at(i).x());
            zamena.setY(listpointer.at(i+1).y());
            listpointer.replace(i,zamena);
        }

    }
}

void MyLine::PushedControlModifier(QPointF mousePosition)
{qDebug()<<"PushedControlModifier";
    QPointF mousePos2(mousePosition);
    QPointF ADDPoint1, ADDPoint2;
    SetKoncyOtrezka(mousePos2);
    //qDebug()<<"CTRL+MOUSELeftButton";
    if(vertical==true && popadanie_vertical==true)//Добавить новый изгиб
    {//К вертикальному отрезку
        //qDebug()<<"CTRL+Vertical";
        ADDPoint1.setX(listpointer.at(nachalo_otrezka).x());
        ADDPoint1.setY(mousePos2.y());
        ADDPoint2.setX(mousePos2.x());
        ADDPoint2.setY(listpointer.at(konec_otrezka).y());
        qDebug()<<"ADDPoint1 = "<<ADDPoint1;
        qDebug()<<"ADDPoint2 ="<<ADDPoint2;
        listpointer.replace(konec_otrezka,ADDPoint2);
        qDebug()<<"nachalo_otrezkaV="<<nachalo_otrezka;
        if((nachalo_otrezka>0 && nachalo_otrezka<endpoint-1) && (konec_otrezka>1 && konec_otrezka<endpoint))
        {
            listpointer.insert(nachalo_otrezka+1,mousePos2);
            listpointer.insert(nachalo_otrezka+1,ADDPoint1);
        }
        else if(listpointer.count()!=2 && nachalo_otrezka==endpoint-1 && konec_otrezka==endpoint)
        {
            listpointer.insert(nachalo_otrezka+1,mousePos2);
            listpointer.insert(nachalo_otrezka+1,ADDPoint1);
        }
        else if(nachalo_otrezka==0 && konec_otrezka==1)
        {
            listpointer.insert(nachalo_otrezka+1,mousePos2);
            listpointer.insert(nachalo_otrezka+1,ADDPoint1);
        }
        updateListDotes();
    }

    if(horizontal==true && popadanie_horizontal==true)
    {//К горизонтальному отрезку
        //qDebug()<<"CTRL+Horizontal";
        ADDPoint1.setX(mousePos2.x());
        ADDPoint1.setY(listpointer.at(nachalo_otrezka).y());
        ADDPoint2.setX(listpointer.at(konec_otrezka).x());
        ADDPoint2.setY(mousePos2.y());
        qDebug()<<"ADDPoint1H = "<<ADDPoint1;
        qDebug()<<"ADDPoint2H="<<ADDPoint2;
        listpointer.replace(konec_otrezka,ADDPoint2);
        if((nachalo_otrezka>0 && nachalo_otrezka<endpoint-1) && (konec_otrezka>1 && konec_otrezka<endpoint))
        {
            listpointer.insert(nachalo_otrezka+1,mousePos2);
            listpointer.insert(nachalo_otrezka+1,ADDPoint1);
        }
        else if(listpointer.count()!=2 && nachalo_otrezka==endpoint-1 && konec_otrezka==endpoint)
        {
            listpointer.insert(nachalo_otrezka+1,mousePos2);
            listpointer.insert(nachalo_otrezka+1,ADDPoint1);
        }
        else if(nachalo_otrezka==0 && konec_otrezka==1)
        {
            listpointer.insert(nachalo_otrezka+1,mousePos2);
            listpointer.insert(nachalo_otrezka+1,ADDPoint1);
        }
        updateListDotes();
    }
}

void MyLine::mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent)//-----------------------------------------------------------------------------------
{
    qDebug()<<"MyLine::mousePressEvent";

    SetKoncyOtrezka(mouseEvent->scenePos());
    if((horizontal==true &&  popadanie_horizontal==true && vertical==false && popadanie_vertical==false) ||
            (horizontal==false &&  popadanie_horizontal==false && vertical==true && popadanie_vertical==true))
    {//qDebug()<<"this->setSelected(true)";
        this->setSelected(true);
    }
    QGraphicsItem::mousePressEvent(mouseEvent);
    Q_UNUSED(mouseEvent);
}

void MyLine::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{//qDebug()<<"MyLine::mouseMoveEvent";
    //qDebug()<<"SceneMouseEventPosOffset = "<<SceneMouseEventPosOffset;

    QGraphicsItem::mouseMoveEvent(mouseEvent);
}


void MyLine::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)//-----------------------------------------------------------------------------------
{
    qDebug()<<"MyLine::mouseReleaseEvent";
    vertical=false;
    horizontal=false;
    popadanie_vertical=false;
    popadanie_horizontal=false;
    start_horizontal=false;
    start_vertical=false;
    end_horizontal=false;
    end_vertical=false;
    LineAjustment();
    LineStraightnessTest();
    //UpdateListpointerUnderstudy();
    QGraphicsItem::mouseReleaseEvent(mouseEvent);
    Q_UNUSED(mouseEvent);

}

//void MyLine::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
//  {
//     hoverenter=true;
//      QGraphicsItem::hoverEnterEvent(event);
//  }

void MyLine::LineStraightnessTest()
{//qDebug()<<"LineStraightnessTest";
    int coincidencesxd=0,coincidencesyd=0;
    for(int i=0;i<listpointer.count()-1;i++)
    {   if(listpointer.at(i).x()>=listpointer.at(i+1).x()-1 && listpointer.at(i).x()<=listpointer.at(i+1).x()+1)
        {    coincidencesxd++;

        }
        if(listpointer.at(i).y()>=listpointer.at(i+1).y()-1 && listpointer.at(i).y()<=listpointer.at(i+1).y()+1)
        {    coincidencesyd++;

        }
        //qDebug()<<"LineStraightnessTest1";
        if((coincidencesyd==listpointer.count()-1) || (coincidencesxd==listpointer.count()-1))
        {   for(int k=0;k<listpointer.count();k++)
            {
                if(listpointer.count()>2 && k>0 && k<listpointer.count())
                {
                    if(this->isSelected() && !listDotes.isEmpty())
                    {
                        scene()->removeItem(listDotes.at(k));listDotes.removeAt(k);}
                    listpointer.removeAt(k);
                }
            }
        }
    }
}

void MyLine::LineСhangeAlgorithmStart()
{//qDebug()<<"LineСhangeAlgorithmStart()";
    qreal sdx,sdy;
    sdx=abs(startPoint.x()-listpointer.at(1).x());
    sdy=abs(startPoint.y()-listpointer.at(1).y());
    QPointF zamena;
    //если от startPoint идет вертикальная линия,
    //значит при его перемещении от startPoint отрезок должен рисоваться горизонтальным и под 90град
    if(sdy>sdx && start_horizontal==false)
    {   qDebug()<<"zamena_vertical_1";
        start_horizontal=false;
        start_vertical=true;
        //QPointF zamena;
        sdx=startPoint.x();
        zamena.setX(sdx);
        zamena.setY(listpointer.at(1).y());
        listpointer.replace(1,zamena);        }

    if(sdx>sdy && start_horizontal==false && start_vertical==true)//обеспечивает 90град при пердвижении радиоэлемнта по сцене
    {   qDebug()<<"zamena_v2_1";
        start_horizontal=false;
        start_vertical=true;
        //QPointF zamena;
        sdx=startPoint.x();
        zamena.setX(sdx);
        zamena.setY(listpointer.at(1).y());
        listpointer.replace(1,zamena);        }

    //если от startPoint идет горизонтальная линия,
    //значит при его перемещении от startPoint отрезок должен рисоваться вертикальным и под 90град
    if(sdx>sdy && start_vertical==false)
    {   qDebug()<<"zamena_horizontal_1";
        start_horizontal=true;
        start_vertical=false;
        //QPointF zamena;
        sdy=startPoint.y();
        zamena.setY(sdy);
        zamena.setX(listpointer.at(1).x());
        listpointer.replace(1,zamena);        }

    if(sdy>sdx && start_horizontal==true && start_vertical==false)//обеспечивает 90град при пердвижении радиоэлемнта по сцене
    {   qDebug()<<"zamena_h2_1";
        start_horizontal=true;
        start_vertical=false;
        //QPointF zamena;
        sdy=startPoint.y();
        zamena.setY(sdy);
        zamena.setX(listpointer.at(1).x());
        listpointer.replace(1,zamena);        }
}//qDebug()<<"==============================";

void MyLine::LineСhangeAlgorithmEnd()
{//qDebug()<<"LineСhangeAlgorithmEnd()";
    qreal edx,edy;
    //int n=listpointer.count()-1;
    edx=abs(endPoint.x()-listpointer.at(endpoint-1).x());
    edy=abs(endPoint.y()-listpointer.at(endpoint-1).y());
    QPointF zamena;
    //если от endPoint идет вертикальная линия,
    //значит при его перемещении от endPoint отрезок должен рисоваться горизонтальным и под 90град
    if(edy>edx && end_horizontal==false)//значит отрезок должен быть вертикальным
    {   qDebug()<<"end_zamena_vertical2";
        end_horizontal=false;
        end_vertical=true;
        //QPointF zamena;
        edx=endPoint.x();
        zamena.setX(edx);
        zamena.setY(listpointer.at(endpoint-1).y());
        listpointer.replace(endpoint-1,zamena);         }

    if(edx>edy && end_horizontal==false && end_vertical==true)//обеспечивает 90град при пердвижении радиоэлемнта по сцене
    {   qDebug()<<"end_zamena_v2_2";
        end_horizontal=false;
        end_vertical=true;
        //QPointF zamena;
        edx=endPoint.x();
        zamena.setX(edx);
        zamena.setY(listpointer.at(endpoint-1).y());
        listpointer.replace(endpoint-1,zamena);         }
    //если от endPoint идет горизонтальная линия,
    //значит при его перемещении от endPoint отрезок должен рисоваться вертикальным и под 90град
    if(edx>edy && end_vertical==false)
    {   qDebug()<<"end_zamena_horizontal2";
        end_horizontal=true;
        end_vertical=false;
        //QPointF zamena;
        edy=endPoint.y();
        zamena.setY(edy);
        zamena.setX(listpointer.at(endpoint-1).x());
        listpointer.replace(endpoint-1,zamena);        }

    if(edy>edx && end_vertical==false && end_horizontal==true)//обеспечивает 90град при пердвижении радиоэлемнта по сцене
    {   qDebug()<<"end_zamena_h2_2";
        end_horizontal=true;
        end_vertical=false;
        //QPointF zamena;
        edy=endPoint.y();
        zamena.setY(edy);
        zamena.setX(listpointer.at(endpoint-1).x());
        listpointer.replace(endpoint-1,zamena);       }

    if(edx==edy){ //qDebug()<<"ravno2";
    }
}//qDebug()<<"==============================";

DotSignal* MyLine::returnSelectedDot()
{qDebug()<<"returnSelectedDot()";
    if(!listDotes.isEmpty()){
        for(int i=0;i<listDotes.count();i++)
        {//qDebug()<<"SortDots";
            if(listDotes.at(i)->DotHoverEvent==true)
            {qDebug()<<"listDotes.at(i)->isSelected()="<<i;
                return listDotes.at(i);}
        }
    }
    else{return 0;}
    return 0;
}

void MyLine::UpdateListpointerUnderstudy()
{
    //    if(this->isSelected())
    //    {
    //        for(int i=1;i<listpointer.count()-1;i++){listpointerUnderstudy.replace(i-1,listpointer.at(i));}
    //    }

    if(listelements.at(0)!=NULL && listelements.at(1)!=NULL && listDotes.isEmpty() && myStartItem->isSelected() && myEndItem->isSelected())
    {qDebug()<<"IF_ELEMENTS_NOT_NULL";
        listpointerUnderstudy.clear();
        for(int i=1;i<listpointer.count()-1;i++)
        {listpointerUnderstudy.push_back(listpointer.at(i)); }

        if(listpointerUnderstudy.count()!=listpointer.count()-2)
        {
            listpointerUnderstudy.clear();
            for(int i=1;i<listpointer.count()-1;i++)
            {listpointerUnderstudy.push_back(listpointer.at(i)); }
        }
        if(listpointer.count()==2)
        {
            for(int i=0;i<listpointer.count();i++)
            {listpointerUnderstudy.push_back(listpointer.at(i)); }
        }
    }
    else if((!listelements.isEmpty() && listelements.at(0)!=NULL && listelements.at(1)!=NULL && myStartItem->isSelected() && !myEndItem->isSelected()) ||
            (!listelements.isEmpty() && listelements.at(0)!=NULL && listelements.at(1)==NULL && listDotes.isEmpty() && myStartItem->isSelected()))
    {qDebug()<<"IF_START_NOT_NULL";
        listpointerUnderstudy.clear();
        for(int i=1;i<listpointer.count();i++)
        {listpointerUnderstudy.push_back(listpointer.at(i)); }

        if(listpointerUnderstudy.count()!=listpointer.count()-1)
        {    listpointerUnderstudy.clear();
            for(int i=1;i<listpointer.count();i++)
            {listpointerUnderstudy.push_back(listpointer.at(i)); }
        }
        if(listpointer.count()==2)
        {   for(int i=0;i<listpointer.count();i++)
            {listpointerUnderstudy.push_back(listpointer.at(i)); }
        }
    }
    // qDebug()<<"PaintLine1.4.3";
    else if((!listelements.isEmpty() && listelements.at(0)!=NULL && listelements.at(1)!=NULL && myEndItem->isSelected() && !myStartItem->isSelected()) ||
            (!listelements.isEmpty() && listelements.at(0)==NULL && listelements.at(1)!=NULL && listDotes.isEmpty() && myEndItem->isSelected()))
    {qDebug()<<"IF_END_NOT_NULL";
        listpointerUnderstudy.clear();
        for(int i=0;i<listpointer.count()-1;i++)
        {listpointerUnderstudy.push_back(listpointer.at(i)); }

        if(listpointerUnderstudy.count()!=listpointer.count()-1)
        {    listpointerUnderstudy.clear();
            for(int i=0;i<listpointer.count()-1;i++)
            {listpointerUnderstudy.push_back(listpointer.at(i)); }
        }
        if(listpointer.count()==2)
        {   for(int i=0;i<listpointer.count();i++)
            {listpointerUnderstudy.push_back(listpointer.at(i)); }
        }
    }
    else if(listelements.at(0)==NULL && listelements.at(1)==NULL)
    {//if(horizontal==false && popadanie_horizontal==false && vertical==false && popadanie_vertical==false)
        // {
        //qDebug()<<"listelements.at(0)==NULL && listelements.at(1)==NULL && this->isUnderMouse()==false";
        qDebug()<<"IF_ELEMENTS_NULL";
        listpointerUnderstudy.clear();
        for(int i=0;i<listpointer.count();i++)
        {listpointerUnderstudy.push_back(listpointer.at(i)); }

        if(listpointerUnderstudy.count()!=listpointer.count())
        {
            listpointerUnderstudy.clear();
            for(int i=0;i<listpointer.count();i++)
            {listpointerUnderstudy.push_back(listpointer.at(i)); }
        }
        // }
    }

}

//void MyLine::SetflagDrawingSelectedrect(bool b){flagDrawingSelectedrect=b;}

void MyLine::updateListDotes()
{
    if(!listDotes.isEmpty()){
        foreach (DotSignal *dot, listDotes) {
            dot->deleteLater();
        }
        listDotes.clear();
    }

    for(int i=0;i<listpointer.count();i++)
    {
        dot=new DotSignal(listpointer.at(i),this);
        dot->setDotFlags(DotSignal::Movable);
        dot->setLineFlag(true);
        listDotes.append(dot);
    }
}
int MyLine::DotsUnderMouse()
{
    int countDotesUndermouse=0;
    if(!listDotes.isEmpty())
    {
        for(int i=0;i<listDotes.count();i++)
        {
            if(listDotes.at(i)->isSelected())
            {
                countDotesUndermouse++;
            }
        }
    }
    qDebug()<<"countDotesUndermouse = "<<countDotesUndermouse;
    return countDotesUndermouse;
}

void MyLine::MoveFullLine(QPointF mouseposoffset)
{
    if(listelements.at(0)!=NULL && listelements.at(1)!=NULL && this->isSelected() && myStartItem->isSelected() && myEndItem->isSelected() && listDotes.isEmpty())
    {qDebug()<<"Peremeshenie_linii";
        for(int i=1;i<listpointer.count()-1;i++)
        {
            listpointer.replace(i,listpointerUnderstudy.at(i-1)+mouseposoffset);
        }
    }
    //qDebug()<<"MoveFullLine1";

    else if(listelements.at(0)==NULL && listelements.at(1)==NULL && this->isSelected() && this->DotsUnderMouse()==0)//&& this->isUnderMouse()==true
    {qDebug()<<"Peremeshenie_linii2";
        for(int i=0;i<listpointer.count();i++)
        {
            listpointer.replace(i,listpointerUnderstudy.at(i)+mouseposoffset);
            startPoint = listpointer.at(0);
            endPoint = listpointer.at(endpoint);
        }
    }

    else if(listelements.at(0)!=NULL && this->isSelected() && myStartItem->isSelected() && this->DotsUnderMouse()==0)//&& this->isUnderMouse()==true
    {qDebug()<<"Peremeshenie_linii3";
        for(int i=1;i<listpointer.count();i++)
        {
            listpointer.replace(i,listpointerUnderstudy.at(i-1)+mouseposoffset);
            startPoint = listpointer.at(0);
        }
    }
    else if(listelements.at(1)!=NULL && this->isSelected() && myEndItem->isSelected() && this->DotsUnderMouse()==0)//&& this->isUnderMouse()==true
    {qDebug()<<"Peremeshenie_linii4";
        for(int i=0;i<listpointer.count()-1;i++)
        {
            listpointer.replace(i,listpointerUnderstudy.at(i)+mouseposoffset);
            endPoint = listpointer.at(endpoint);
        }
    }
}

void MyLine::MoveSegmentLine(QPointF mousePos2)
{
    for(int i=0;i<listDotes.count();i++)
    {
        if(listDotes.at(i)->isSelected())
        {//atleastoneSelectDot=true;
            //QPointF mousePos2=listDotes.at(i)->pos();
            qDebug()<<"MoveSegmentLine";
            if(listpointer.at(i)!=listpointer.at(0) &&
                    listpointer.at(i)!=listpointer.at(endpoint) &&
                    listpointer.at(i).x()==listpointer.at(i+1).x() &&
                    listpointer.at(i).y()==listpointer.at(i-1).y())//подвинуть отрезок линии мышкой зажатой левой кнопкой
            {   qDebug()<<"1";
                QPointF zamena1,zamena2,zamena3;
                zamena1.setX(listpointer.at(i-1).x());
                zamena1.setY(mousePos2.y());
                zamena2.setX(mousePos2.x());
                zamena2.setY(mousePos2.y());
                zamena3.setX(mousePos2.x());
                zamena3.setY(listpointer.at(i+1).y());
                listpointer.replace(i-1,zamena1);
                listpointer.replace(i,zamena2);
                listpointer.replace(i+1,zamena3);

                if(listDotes.indexOf(listDotes.at(i-1))==0)
                {qDebug()<<"2";
                    QPointF insertpoint;
                    insertpoint.setX(listpointer.at(0).x());
                    insertpoint.setY(listpointer.at(0).y());
                    listpointer.insert(1,insertpoint);
                    dot=new DotSignal(listpointer.at(0),this);
                    dot->setDotFlags(DotSignal::Movable);
                    dot->setLineFlag(true);
                    listDotes.insert(1,dot);
                    endpoint++;enddot++;
                }
                if(listDotes.indexOf(listDotes.at(i+1))==listDotes.indexOf(listDotes.at(enddot)))
                {qDebug()<<"3";
                    QPointF insertpoint;
                    insertpoint.setX(listpointer.at(i+1).x());
                    insertpoint.setY(listpointer.at(i).y());
                    listpointer.insert(endpoint,listpointer.at(endpoint));
                    endpoint++;
                    dot=new DotSignal(listpointer.at(i),this);
                    dot->setDotFlags(DotSignal::Movable);
                    dot->setLineFlag(true);
                    listDotes.insert(endpoint,dot);
                    enddot++;
                }
            }

            if(listpointer.at(i)!=listpointer.at(0) &&
                    listpointer.at(i)!=listpointer.at(endpoint) &&
                    listpointer.at(i).x()==listpointer.at(i-1).x() &&
                    listpointer.at(i).y()==listpointer.at(i+1).y())
            {qDebug()<<"4";
                QPointF zamena1,zamena2,zamena3;
                zamena1.setX(mousePos2.x());
                zamena1.setY(listpointer.at(i-1).y());
                zamena2.setX(mousePos2.x());
                zamena2.setY(mousePos2.y());
                zamena3.setX(listpointer.at(i+1).x());
                zamena3.setY(mousePos2.y());
                listpointer.replace(i-1,zamena1);
                listpointer.replace(i,zamena2);
                listpointer.replace(i+1,zamena3);

                if(listDotes.indexOf(listDotes.at(i-1))==0)
                {qDebug()<<"5";
                    QPointF insertpoint;//insertpoint2;
                    insertpoint.setX(listpointer.at(0).x());
                    insertpoint.setY(listpointer.at(0).y());
                    listpointer.insert(1,insertpoint);
                    dot=new DotSignal(listpointer.at(0),this);
                    dot->setDotFlags(DotSignal::Movable);
                    dot->setLineFlag(true);
                    listDotes.insert(1,dot);
                    endpoint++;enddot++;
                }
                if(listDotes.indexOf(listDotes.at(i+1))==listDotes.indexOf(listDotes.at(enddot)))
                {qDebug()<<"6";
                    QPointF insertpoint;
                    insertpoint.setX(listpointer.at(i+1).x());
                    insertpoint.setY(listpointer.at(i).y());
                    listpointer.insert(endpoint,listpointer.at(endpoint));
                    endpoint++;
                    dot=new DotSignal(listpointer.at(i),this);
                    dot->setDotFlags(DotSignal::Movable);
                    dot->setLineFlag(true);
                    listDotes.insert(endpoint,dot);
                    enddot++;
                }
            }
        }
    }
}

void MyLine::PointSelectionControl()
{
    if(!listDotes.isEmpty())
    {int indexHoverEnterDotTrue=0,insexHoverEnterDotFalse=0;
        for(int i=0;i<listDotes.count();i++)
        {   if(listDotes.at(i)->GetDotHoverEvent()==false)
            {insexHoverEnterDotFalse++;}
            if(listDotes.at(i)->GetDotHoverEvent()==true)
            {indexHoverEnterDotTrue=i;}
        }
        for(int i=0;i<listDotes.count();i++)
        {   if(insexHoverEnterDotFalse==listDotes.count())
            {listDotes.at(i)->setSelected(false);}
            else if(i!=indexHoverEnterDotTrue && listDotes.at(i)->isSelected())
            {listDotes.at(i)->setSelected(false);}
        }
    }
}
