#ifndef DIODECLASS_H
#define DIODECLASS_H
#include <QGraphicsItem>
#include <QPen>
#include <QPainter>
#include <elementitem.h>

class DiodeClass : public ElementItem
{
public:
    DiodeClass(int count);
    DiodeClass(int count,QString Marking,QString Diodetype,float BrackeDownVoltge,QString Typeofshell,float Length,
               float Wight,float Height,float Thicknessofleg);
    DiodeClass(QPointF p,int number);
    ~DiodeClass();
    QList<QPointF> GetInputs( QPointF currentCenterPosition) override;

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void setMarking(QString marking);
    void setDiodetype(QString dioetype);
    void setBrackeDownVoltage(float breackedownvoltage);
    void setTypeofshell(QString typeofshell);
    void setLength(float langth);
    void setWight(float wight);
    void setHeight(float height);
    void setThicknessofleg(float thicknessofleg);
public:

    QString Marking;
    QString Diodetype;
    float Breackdownvoltage;
    QString Typeofshell;
    float Length;
    float Wight;
    float Height;
    float Thicknessofleg;
};

#endif // DIODECLASS_H
