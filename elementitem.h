#ifndef ELEMENTITEM_H
#define ELEMENTITEM_H
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPen>
#include <QVector>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>
#include "dotsignal.h"
#include "textgen.h"

class MyLine;

class ElementItem :public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    ElementItem();

    ~ElementItem();

    virtual QList<QPointF> GetInputs(QPointF currentCenterPosition);
    enum {Type = UserType+1};
    enum typeclass {ELEMENT};
    enum TypeElements {RESISTOR,CONDENSATOR,DIODE,TRANSISTOR};

    int type() const override
    {
        // Enable the use of qgraphicsitem_cast with this item.
        return Type;
    }

    void removeArrow(MyLine *arrow);
    void removeArrows();
    void setLinePosinZero();
    void addArrow(MyLine *arrow);
    bool MoveElementFlag();
    QPointF RotateAncorPoint(QPointF center,QPointF point,double angle);
    void setAngle(double setangle);
    DotSignal* returnSelectedDot();
    void setCountElement(int count);
    void setMoveFlag(bool b);
    QList<QPointF> GetlistDotElementsCoordinate();
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QPointF rotateText(QPointF point,double angle);
    double GetAngle();

public:
    typeclass typeClass;
    TypeElements typeElement;
    QString TypeRadioElement;
    int position=0;
    int ecount=0;
    int rowindatabase=0;
    QPainter *painter;
    QPen pen;
    TextGen *text;
    QColor myTextColor;
    QFont *myFont;

    QList <QPointF> ancorpoint;

    QString Signature;
    QVector<MyLine *> arrows;
    QPointF linepoint;
    bool moveflag=false;
    bool blockCaptured=false;
    double angle=0;
    DotSignal *dote;
    QList<DotSignal*> listDotElements;
    QList<QPointF> DotCoordinate;

};
#endif // ELEMENTITEM_H
