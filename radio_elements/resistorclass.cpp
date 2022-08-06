#include "radio_elements/resistorclass.h"
#include "qstyleoption.h"
#include <QDebug>
#include <QStyle>
ResistorClass::ResistorClass(int count)
{
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setAcceptHoverEvents(true);
    ancorpoint = GetInputs(QPointF (0,0));
    foreach(QPointF p, ancorpoint)
    {
        dote = new DotSignal(p, this);
        dote->setZValue(-500);
        dote->setElementFlag(true);
        listDotElements.append(dote);
    }
    this->typeElement=RESISTOR;
    TypeRadioElement = "REZISTOR";
    ecount=count;
    text = new TextGen("R"+QString::number(ecount+1),this);
};
ResistorClass::ResistorClass(int rowindb,int count, QString marking, QString resistortype, float resistance,
                             int power, QString typeofshell, float length,
                             float wight, float height, float thicknessofleg)
{
    ecount=count;
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setAcceptHoverEvents(true);

    ancorpoint = GetInputs(QPointF (0,0));
    foreach(QPointF p, ancorpoint)
    {
        dote = new DotSignal(p, this);
        dote->setZValue(-500);
        dote->setElementFlag(true);
        listDotElements.append(dote);
    }
    this->typeElement=RESISTOR;
    TypeRadioElement = "REZISTOR";

    text = new TextGen("R"+QString::number(ecount+1),this);

    rowindatabase = rowindb;
    Marking = marking;
    Resistortype = resistortype;
    Resistance = resistance;
    Power = power;
    Typeofshell = typeofshell;
    Length = length;
    Wight = wight;
    Height = height;
    Thicknessofleg = thicknessofleg;
};

ResistorClass::ResistorClass(QPointF p, int number)
{
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setAcceptHoverEvents(true);
    ancorpoint = GetInputs(QPointF (0,0));
    foreach(QPointF p, ancorpoint)
    {
        dote = new DotSignal(p, this);
        dote->setZValue(-500);
        dote->setElementFlag(true);
        listDotElements.append(dote);
    }
    this->typeElement=RESISTOR;
    TypeRadioElement = "REZISTOR";
    ecount=number;
    this->setPos(p);
    text = new TextGen("R"+QString::number(ecount+1),this);
    qDebug()<<"TextPos="<<text->pos();
}

ResistorClass::~ResistorClass(){}
QRectF ResistorClass::boundingRect() const
{
    return QRectF (-14,-38,27,75);
}

void ResistorClass::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(this->isSelected())
    {

        painter->setPen(Qt::black);
        painter->drawRect(-14,-38,27,75);
        painter->setPen(Qt::black);
        painter->setBrush(Qt::green);
        pen.setWidth(5);
        pen.setBrush(Qt::black);
        painter->setPen(pen);
        painter->drawRect(-13,-25,25,50);
        painter->drawLine(0,-25,0,-35);
        painter->drawLine(0,25,0,35);
        painter->setPen(Qt::yellow);
        painter->drawPoint(0,-35);
        painter->setPen(Qt::red);
        painter->drawPoint(0,35);
    }
    else{
        painter->setPen(Qt::black);
        painter->setBrush(Qt::green);
        pen.setWidth(5);
        pen.setBrush(Qt::black);
        painter->setPen(pen);
        painter->drawRect(-13,-25,25,50);
        painter->drawLine(0,-25,0,-35);
        painter->drawLine(0,25,0,35);
        painter->setPen(Qt::yellow);
        painter->drawPoint(0,-35);
        painter->drawPoint(0,35);}



    Q_UNUSED(widget);
}

QList<QPointF> ResistorClass::GetInputs( QPointF currentCenterPosition)
{
    QList<QPointF> result;
    QPointF point1(currentCenterPosition.x(), currentCenterPosition.y()+35);
    QPointF point2(currentCenterPosition.x(), currentCenterPosition.y()-35);
    result.push_back(RotateAncorPoint(currentCenterPosition,point1,-angle));
    result.push_back(RotateAncorPoint(currentCenterPosition,point2,-angle));
    return result;
    qDebug()<<"poinrR="<<result;
}

void ResistorClass::setMarking(QString marking){Marking=marking;}
void ResistorClass::setResistortype(QString resistortype){Resistortype=resistortype;}
void ResistorClass::setResistance(float resistance){Resistance=resistance;}
void ResistorClass::setPower(int power){Power=power;}
void ResistorClass::setTypeofshell(QString typeofshell){Typeofshell=typeofshell;}
void ResistorClass::setLength(float length){Length=length;}
void ResistorClass::setWight(float wight){Wight=wight;}
void ResistorClass::setHeight(float height){Height=height;}
void ResistorClass::setThicknessofleg(float thicknessofleg){Thicknessofleg=thicknessofleg;}


