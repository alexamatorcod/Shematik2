#include "radio_elements/diodeclass.h"

DiodeClass::DiodeClass(int count)
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
    this->typeElement=DIODE;
    TypeRadioElement = "DIODE";
    ecount=count;
    text = new TextGen("VD"+QString::number(ecount+1),this);
}

DiodeClass::DiodeClass(int count,QString marking,QString diodetype,float breackdownvoltage,
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
    this->typeElement=DIODE;
    TypeRadioElement = "DIODE";
    ecount=count;

    text = new TextGen("VD"+QString::number(ecount+1),this);

    Marking = marking;
    Diodetype = diodetype;
    Breackdownvoltage = breackdownvoltage;
    Typeofshell = typeofshell;
    Length = length;
    Wight = wight;
    Height = height;
    Thicknessofleg = thicknessofleg;

};

DiodeClass::DiodeClass(QPointF p,int number)
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
    this->typeElement=DIODE;
    TypeRadioElement = "DIODE";
    ecount=number;
    this->setPos(p);
    text = new TextGen("VD"+QString::number(ecount+1),this);
    myTextColor = Qt::black;
    myFont = new QFont("Bahnschrift Light Condensed");
    myFont->setPixelSize(50);
    text->setDefaultTextColor(myTextColor);
    text->setFont(*myFont);
    text->setTextWidth(100);
    text->setPos(this->pos().x()+10,this->pos().y()-80);
};

DiodeClass::~DiodeClass(){}

QRectF DiodeClass::boundingRect() const
{
    return QRectF (-30,-30,60,60);
}
void DiodeClass::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(this->isSelected())
    {
      painter->setPen(Qt::black);
      painter->drawRect(-30,-30,60,60);
      pen.setWidth(5);
      pen.setBrush(Qt::black);
      painter->setPen(pen);
      painter->drawLine(28,0,-28,0);
      painter->drawLine(-15,-20,-15,20);
      painter->drawLine(-15,-20,20,0);
      painter->drawLine(20,0,-15,20);
      painter->drawLine(15,-20,15,20);
      painter->setPen(Qt::yellow);
      painter->drawPoint(-28,0);
      painter->drawPoint(28,0);
    }
    else{
    pen.setWidth(5);
    pen.setBrush(Qt::black);
    painter->setPen(pen);
    painter->drawLine(28,0,-28,0);
    painter->drawLine(-15,-20,-15,20);
    painter->drawLine(-15,-20,20,0);
    painter->drawLine(20,0,-15,20);
    painter->drawLine(15,-20,15,20);
    painter->setPen(Qt::yellow);
    painter->drawPoint(-28,0);
    painter->drawPoint(28,0);}

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QList<QPointF> DiodeClass::GetInputs( QPointF currentCenterPosition)
{
    QList<QPointF> result;
    QPointF point1(currentCenterPosition.x() - 28, currentCenterPosition.y());
    QPointF point2(currentCenterPosition.x() + 28, currentCenterPosition.y());
    result.push_back(RotateAncorPoint(currentCenterPosition,point1,angle));
    result.push_back(RotateAncorPoint(currentCenterPosition,point2,angle));
    return result;
}

void DiodeClass::setMarking(QString marking){Marking=marking;}
void DiodeClass::setDiodetype(QString diodetype){Diodetype=diodetype;}
void DiodeClass::setBrackeDownVoltage(float breackedownvoltage){Breackdownvoltage=breackedownvoltage;}
void DiodeClass::setTypeofshell(QString typeofshell){Typeofshell=typeofshell;}
void DiodeClass::setLength(float length){Length=length;}
void DiodeClass::setWight(float wight){Wight=wight;}
void DiodeClass::setHeight(float height){Height=height;}
void DiodeClass::setThicknessofleg(float thicknessofleg){Thicknessofleg=thicknessofleg;}
