#include "radio_elements/condensatorclass.h"

CondensatorClass::CondensatorClass(int count)
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
    this->typeElement=CONDENSATOR;
    TypeRadioElement = "CONDENSATOR";
    ecount=count;
    text = new TextGen("C"+QString::number(ecount+1),this);
}
CondensatorClass::CondensatorClass(int count,QString marking,QString capacitortype,float capacity,
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
    this->typeElement=CONDENSATOR;
    TypeRadioElement = "CONDENSATOR";
    ecount=count;

    text = new TextGen("C"+QString::number(ecount+1),this);

    Marking = marking;
    Capacitortype = capacitortype;
    Capacity = capacity;
    Typeofshell = typeofshell;
    Length = length;
    Wight = wight;
    Height = height;
    Thicknessofleg = thicknessofleg;

};

CondensatorClass::CondensatorClass(QPointF p,int number)
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
    this->typeElement=CONDENSATOR;
    TypeRadioElement = "CONDENSATOR";
    ecount=number;
    this->setPos(p);
    text = new TextGen("C"+QString::number(ecount+1),this);

};

CondensatorClass::~CondensatorClass(){}

QRectF CondensatorClass::boundingRect() const
{
    return QRectF (-30,-30,60,60);
}
void CondensatorClass::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(this->isSelected())
    {
        painter->setPen(Qt::black);
        painter->drawRect(-30,-30,60,60);
        pen.setWidth(5);
        pen.setBrush(Qt::black);
        painter->setPen(pen);
        painter->drawLine(-10,-20,-10,20);
        painter->drawLine(10,-20,10,20);
        painter->drawLine(28,0,10,0);
        painter->drawLine(-28,0,-10,0);
        painter->setPen(Qt::yellow);
        painter->drawPoint(-28,0);
        painter->drawPoint(28,0);
    }
    else{
        pen.setWidth(5);
        pen.setBrush(Qt::black);
        painter->setPen(pen);
        painter->drawLine(-10,-20,-10,20);
        painter->drawLine(10,-20,10,20);
        painter->drawLine(28,0,10,0);
        painter->drawLine(-28,0,-10,0);
        painter->setPen(Qt::yellow);
        painter->drawPoint(-28,0);
        painter->drawPoint(28,0);}

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QList<QPointF> CondensatorClass::GetInputs( QPointF currentCenterPosition)
{
    QList<QPointF> result;
    QPointF point1(currentCenterPosition.x() - 28, currentCenterPosition.y());
    QPointF point2(currentCenterPosition.x() + 28, currentCenterPosition.y());
    result.push_back(RotateAncorPoint(currentCenterPosition,point1,angle));
    result.push_back(RotateAncorPoint(currentCenterPosition,point2,angle));
    return result;
}

void CondensatorClass::setMarking(QString marking){Marking=marking;}
void CondensatorClass::setCapacitortype(QString capacitortype){Capacitortype=capacitortype;}
void CondensatorClass::setCapacity(float capacity){Capacity=capacity;}
void CondensatorClass::setTypeofshell(QString typeofshell){Typeofshell=typeofshell;}
void CondensatorClass::setLength(float length){Length=length;}
void CondensatorClass::setWight(float wight){Wight=wight;}
void CondensatorClass::setHeight(float height){Height=height;}
void CondensatorClass::setThicknessofleg(float thicknessofleg){Thicknessofleg=thicknessofleg;}
