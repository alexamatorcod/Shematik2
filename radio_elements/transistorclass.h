#ifndef TRANSISTORCLASS_H
#define TRANSISTORCLASS_H
#include <QGraphicsItem>
#include <QPen>
#include <QPainter>
#include <elementitem.h>

class TransistorClass : public ElementItem
{
public:
    TransistorClass(int count);
    TransistorClass(int count,QString Marking,QString transistortype,QString Structure,QString Typeofshell,float Length,
                    float Wight,float Height,float Thicknessofleg);
    TransistorClass(QPointF p,int number);
    ~TransistorClass();
    QList<QPointF> GetInputs( QPointF currentCenterPosition) override;

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void setMarking(QString marking);
    void setTransistortype(QString transistortype);
    void setStructure(QString structure);
    void setTypeofshell(QString typeofshell);
    void setLength(float langth);
    void setWight(float wight);
    void setHeight(float height);
    void setThicknessofleg(float thicknessofleg);
public:

    QString Marking;
    QString Transistortype;
    QString Structure;
    QString Typeofshell;
    float Length;
    float Wight;
    float Height;
    float Thicknessofleg;
};

#endif // TRANSISTORCLASS_H
