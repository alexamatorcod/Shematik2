#include "radio_elements/transistorclass.h"

TransistorClass::TransistorClass(int count)
{
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    ancorpoint = GetInputs(QPointF (0,0));
    foreach(QPointF p, ancorpoint)
    {
        dote = new DotSignal(p, this);
        dote->setZValue(-500);
        dote->setElementFlag(true);
        listDotElements.append(dote);
    }
    this->typeElement=TRANSISTOR;
    TypeRadioElement = "TRANZISTOR";
    ecount=count;
    text = new TextGen("VT"+QString::number(ecount+1),this);
}

TransistorClass::TransistorClass(int count,QString marking,QString transistortype,QString structure,
                                 QString typeofshell,float length,
                                 float wight,float height,float thicknessofleg)
{
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    ancorpoint = GetInputs(QPointF (0,0));
    foreach(QPointF p, ancorpoint)
    {
        dote = new DotSignal(p, this);
        dote->setZValue(-500);
        dote->setElementFlag(true);
        listDotElements.append(dote);
    }
    this->typeElement=TRANSISTOR;
    TypeRadioElement = "TRANZISTOR";
    ecount=count;

    text = new TextGen("VT"+QString::number(ecount+1),this);

    Marking = marking;
    Transistortype = transistortype;
    Structure = structure;
    Typeofshell = typeofshell;
    Length = length;
    Wight = wight;
    Height = height;
    Thicknessofleg = thicknessofleg;
};

TransistorClass::TransistorClass(QPointF p,int number)
{
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    ancorpoint = GetInputs(QPointF (0,0));
    foreach(QPointF p, ancorpoint)
    {
        dote = new DotSignal(p, this);
        dote->setZValue(-500);
        dote->setElementFlag(true);
        listDotElements.append(dote);
    }
    this->typeElement=TRANSISTOR;
    TypeRadioElement = "TRANZISTOR";
    ecount=number;
    this->setPos(p);

    text = new TextGen("VT"+QString::number(ecount+1),this);
};

TransistorClass::~TransistorClass(){}

QRectF TransistorClass::boundingRect() const
{
    return QRectF (-30,-30,60,60);
}
void TransistorClass::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(this->isSelected())
    {
        painter->setPen(Qt::black);
        painter->drawRect(-30,-30,60,60);
        pen.setWidth(5);
        pen.setBrush(Qt::black);
        painter->setPen(pen);
        painter->drawLine(-10,-20,-10,20);
        painter->drawLine(-9,-7,10,-29);
        painter->drawLine(-9,7,10,29);
        painter->drawLine(-28,0,-10,0);
        painter->setPen(Qt::yellow);
        painter->drawPoint(-28,0);
        painter->drawPoint(10,-29);
        painter->drawPoint(10,29);
    }
    else{
        pen.setWidth(5);
        pen.setBrush(Qt::black);
        painter->setPen(pen);
        painter->drawLine(-10,-20,-10,20);
        painter->drawLine(-9,-7,10,-29);
        painter->drawLine(-9,7,10,29);
        painter->drawLine(-28,0,-10,0);
        painter->setPen(Qt::yellow);
        painter->drawPoint(-28,0);
        painter->drawPoint(10,-29);
        painter->drawPoint(10,29);}

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QList<QPointF> TransistorClass::GetInputs( QPointF currentCenterPosition)
{
    QList<QPointF> result;
    QPointF point1(currentCenterPosition.x() - 28, currentCenterPosition.y());
    QPointF point2(currentCenterPosition.x() + 10, currentCenterPosition.y()-29);
    QPointF point3(currentCenterPosition.x() + 10, currentCenterPosition.y()+29);
    result.push_back(RotateAncorPoint(currentCenterPosition,point1,angle));
    result.push_back(RotateAncorPoint(currentCenterPosition,point2,angle));
    result.push_back(RotateAncorPoint(currentCenterPosition,point3,angle));
    return result;
}

void TransistorClass::setMarking(QString marking){Marking=marking;}
void TransistorClass::setTransistortype(QString transistortype){Transistortype=transistortype;}
void TransistorClass::setStructure(QString structure){Structure=structure;}
void TransistorClass::setTypeofshell(QString typeofshell){Typeofshell=typeofshell;}
void TransistorClass::setLength(float length){Length=length;}
void TransistorClass::setWight(float wight){Wight=wight;}
void TransistorClass::setHeight(float height){Height=height;}
void TransistorClass::setThicknessofleg(float thicknessofleg){Thicknessofleg=thicknessofleg;}
