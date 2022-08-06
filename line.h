#ifndef LINE_H
#define LINE_H
#include <QGraphicsItem>
#include <QGraphicsLineItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QMouseEvent>
#include "elementitem.h"
#include "dotsignal.h"
#include "textgen.h"
class ElementItem;

class MyLine :public QObject, public QGraphicsPathItem
{
    Q_OBJECT
public:

    MyLine(ElementItem *startItem, ElementItem *endItem, QPointF linestartpoint, QPointF lineendpoint,QObject  *parent = 0);
    MyLine(QPointF StartPoint, QPointF EndPoint,QObject  *parent = 0);
    MyLine(ElementItem *startItem, QPointF linestartpoint, QPointF lineendpoint,QObject  *parent = 0);
    MyLine(QPointF linestartpoint, QPointF lineendpoint, ElementItem *endItem, QObject  *parent = 0);
    MyLine(QPointF linestartpoint,QPointF lineendpoint,QList <QPointF> listpointer,QObject  *parent = 0);
    MyLine(DotSignal *DotstartItem, DotSignal *DotendItem, QPointF linestartpoint, QPointF lineendpoint,QObject  *parent = 0);
    MyLine(ElementItem *startItem, DotSignal *DotendItem, QPointF linestartpoint, QPointF lineendpoint,QObject  *parent = 0);
    MyLine(DotSignal *DotstartItem, ElementItem *endItem, QPointF linestartpoint, QPointF lineendpoint, QObject  *parent = 0);
    MyLine(DotSignal *DotstartItem, QPointF linestartpoint, QPointF lineendpoint,QObject  *parent = 0);
    MyLine(QPointF linestartpoint, QPointF lineendpoint, DotSignal *DotendItem, QObject  *parent = 0);
    ~MyLine();

    void setPath(const QPainterPath &path);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void SetKoncyOtrezka(QPointF mousePos);
    //void setPositionAcorPoint(bool horizontalflag, bool verticalflag,QPointF center,QPointF ancorpoint);
    void LineAjustment();
    void deleteStartAncorElements();
    void deleteEndAncorElements();
    void AddAncorStartElements(ElementItem* item);
    void AddAncorEndElements(ElementItem* item);
    void AddStartElement(ElementItem* item,QPointF sp);
    void AddEndElement(ElementItem* item,QPointF ep);
    DotSignal* StartDot();
    DotSignal* EndDot();
    bool HoverEnter();
    void LineStraightnessTest();
    DotSignal* returnSelectedDot();
    void PushedControlModifier(QPointF mousePosition);

    void setFlag_vertical(bool b){vertical=b;}
    void setFlag_horizontal(bool b){horizontal=b;}
    void setFlag_popadanie_vertical(bool b){popadanie_vertical=b;}
    void setFlag_popadanie_horizontal(bool b){popadanie_horizontal=b;}
    void setFlag_start_horizontal(bool b){start_horizontal=b;}
    void setFlag_start_vertical(bool b){start_vertical=b;}
    void setFlag_end_horizontal(bool b){end_horizontal=b;}
    void setFlag_end_vertical(bool b){end_vertical=b;}
    void setFlag_hoverenter(bool b){hoverenter=b;}

    void ExeguteGetStartPoint();
    void ExeguteGetEndPoint();
    void MoveFullLine(QPointF mouseposoffset);
    void MoveSegmentLine(QPointF mousePos2);
    void PointSelectionControl();

    ElementItem *startItem() const { return myStartItem; }
    ElementItem *endItem() const { return myEndItem; }
    QPointF lstartItem() const { return lineStartPoint; }
    QPointF lendItem() const { return lineEndPoint; }
    DotSignal *DotStartItem() const {return dotStartItem;}
    DotSignal *DotEndItem() const {return dotEndItem;}

    QPointF GetStartPoint(QPointF center,QPointF linepoint);
    QPointF GetEndPoint(QPointF center,QPointF linepoint);
    float GetDistance(QPointF ancor,QPointF linepoint);

    QPointF previousPosition() const;
    void setPreviousPosition(const QPointF previousPosition);
    bool ctrlpush(bool b);
    bool shiftpush(bool b);

    void SetPositionDotes();
    void UpdateListpointerUnderstudy();
    int DotsUnderMouse();
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void updateListDotes();
    void LineСhangeAlgorithmStart();
    void LineСhangeAlgorithmEnd();

public:
    int typeClass=4;
    ElementItem *myStartItem;
    DotSignal *dotStartItem;
    ElementItem *myEndItem;
    DotSignal *dotEndItem;
    DotSignal *dot;

    QList<DotSignal*> listDotes;
    QList <QPointF> listpointer;
    QList<QPointF> listpointerUnderstudy;
    QList<QGraphicsItem*> listelements;

    QPointF p1,p2,Sp,Ep,D,W;
    QPointF lineStartPoint;
    QPointF lineEndPoint;
    QPointF ancorPoint;
    QPointF startPoint,endPoint;
    QPointF dotposition,m_previousPosition;

    bool Ctrlpushed=false;
    bool Shiftpushed=false;
    bool vertical=false;
    bool horizontal=false;
    bool popadanie_vertical=false;
    bool popadanie_horizontal=false;
    bool start_horizontal=false;
    bool start_vertical=false;
    bool end_horizontal=false;
    bool end_vertical=false;
    bool StartItemisDelete=false;
    bool EndItemisDelete=false;
    bool hoverenter=false;
    bool disconnectionSP=false,disconnectionEP=false;
    bool connectionSP=false,connectionEP=false;

    int countS,countE,countD;
    int enddot=0;
    int position1,position2;
    int nachalo_otrezka, konec_otrezka;
    int endpoint=0;
    int indikatorTwoPointsInListpointer=0;
    bool atleastoneSelectDot=false;

};


#endif // LINE_H
