#include "elementitem.h"
#include "line.h"
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>
#include <QPainter>
#include <QDebug>
#include <math.h>

ElementItem::ElementItem()
    : QGraphicsItem()
{
    typeClass=ELEMENT;
}

ElementItem::~ElementItem(){}

QRectF ElementItem::boundingRect() const
{
    return QRectF (-30,-35,75,75);
}

void ElementItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}


QList<QPointF> ElementItem::GetInputs( QPointF currentCenterPosition)
{
    QList<QPointF> result;
    Q_UNUSED(currentCenterPosition);
    return result;
}

QList<QPointF> ElementItem::GetlistDotElementsCoordinate()
{
    for(int i=0;i<listDotElements.count();i++)
    {DotCoordinate.replace(i,listDotElements.at(i)->scenePos());}
    return DotCoordinate;
}

bool ElementItem::MoveElementFlag()
{
    return moveflag;
}

void ElementItem::removeArrow(MyLine *arrow)
{
    arrows.removeOne(arrow);

}

void ElementItem::addArrow(MyLine *arrow){arrows.append(arrow);}

void ElementItem::setAngle(double setangle)
{
    if(setangle<360 && setangle>-360){angle=setangle;}
    else{angle=0;}
}
double ElementItem::GetAngle(){return angle;}

QPointF ElementItem::RotateAncorPoint(QPointF center,QPointF point,double angle)
{
    QPointF newcoord,newpoint;
    qreal x,y;
    newcoord.setX(point.x()-center.x());
    newcoord.setY(point.y()-center.y());
    x=floor(newcoord.x()*cos(angle*(3.14159265358979323846/180))-newcoord.y()*sin(angle*(3.14159265358979323846/180)));
    y=floor(newcoord.x()*sin(angle*(3.14159265358979323846/180))-newcoord.y()*cos(angle*(3.14159265358979323846/180)));
    newpoint.setX(x+center.x());
    newpoint.setY(y+center.y());
    return newpoint;
}

void ElementItem::setCountElement(int count){ecount = count;}

DotSignal* ElementItem::returnSelectedDot()
{//qDebug()<<"returnSelectedDot()";
    if(!listDotElements.isEmpty()){
        for(int i=0;i<listDotElements.count();i++)
        {//qDebug()<<"SortDots";
            if(listDotElements.at(i)->DotHoverEvent==true)
            {//qDebug()<<"listDotElements.at(i)->isSelected()="<<i;
                return listDotElements.at(i);}
        }
    }
    else{return 0;}
    return 0;
}

void ElementItem::setMoveFlag(bool b)
{
    moveflag=b;
}

QPointF ElementItem::rotateText(QPointF point,double angle)
{
    QPointF newcoord,newpoint;
    qreal x,y;
    newcoord.setX(point.x());
    newcoord.setY(point.y());
    x=floor(newcoord.x()*cos(angle*(3.14159265358979323846/180))-newcoord.y()*sin(angle*(3.14159265358979323846/180)));
    y=floor(newcoord.x()*sin(angle*(3.14159265358979323846/180))-newcoord.y()*cos(angle*(3.14159265358979323846/180)));
    newpoint.setX(x);
    newpoint.setY(y);
    return newpoint;
}

