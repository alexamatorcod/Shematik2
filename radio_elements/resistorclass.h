#ifndef RESISTOR_H
#define RESISTOR_H
#include <QGraphicsItem>
#include <QPen>
#include <QPainter>
#include <elementitem.h>
#include "textgen.h"

class ResistorClass : public ElementItem
{
    //Q_OBJECT
public:
    ResistorClass(int count);
    ResistorClass(int rowindb,int count,QString Marking,QString Resistortype,float Resistance,int Power,QString Typeofshell,float Length,
                  float Wight,float Height,float Thicknessofleg);
    ResistorClass(QPointF p,int number);
    ~ResistorClass();
    QList<QPointF> GetInputs( QPointF currentCenterPosition) override;

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QPointF rotateText(QPointF center,QPointF point,double angle);

    void setMarking(QString marking);
    void setResistortype(QString resistortype);
    void setResistance(float resistance);
    void setPower(int power);
    void setTypeofshell(QString typeofshell);
    void setLength(float langth);
    void setWight(float wight);
    void setHeight(float height);
    void setThicknessofleg(float thicknessofleg);


public:

    QString Marking;
    QString Resistortype;
    float Resistance;
    int Power;
    QString Typeofshell;
    float Length;
    float Wight;
    float Height;
    float Thicknessofleg;
    QColor color;

};

#endif // RESISTOR_H
