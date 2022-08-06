#ifndef CONDENSATORCLASS_H
#define CONDENSATORCLASS_H
#include <QGraphicsItem>
#include <QPen>
#include <QPainter>
#include <elementitem.h>

class CondensatorClass: public ElementItem
{
public:
    CondensatorClass(int count);
    CondensatorClass(int count,QString Marking,QString Capacitortype,float Capacity,QString Typeofshell,float Length,
                     float Wight,float Height,float Thicknessofleg);
    CondensatorClass(QPointF p,int number);
    ~CondensatorClass();
    QList<QPointF> GetInputs( QPointF currentCenterPosition) override;
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void setMarking(QString marking);
    void setCapacitortype(QString capacitortype);
    void setCapacity(float capacity);
    void setTypeofshell(QString typeofshell);
    void setLength(float langth);
    void setWight(float wight);
    void setHeight(float height);
    void setThicknessofleg(float thicknessofleg);
public:

    QString Marking;
    QString Capacitortype;
    float Capacity;
    QString Typeofshell;
    float Length;
    float Wight;
    float Height;
    float Thicknessofleg;
};

#endif // CONDENSATORCLASS_H
