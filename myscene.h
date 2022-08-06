#ifndef MYSCENE_H
#define MYSCENE_H

#include <QDebug>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QRubberBand>
#include "elementitem.h"
#include "radio_elements/condensatorclass.h"
#include "radio_elements/diodeclass.h"
#include "radio_elements/resistorclass.h"
#include "radio_elements/transistorclass.h"
#include "dotsignal.h"
#include "textgen.h"

class MyScene : public QGraphicsScene
{
    Q_OBJECT
public:
    enum Mode { setResistor, setCondensator, setDiode, setTransistor, InsertLine, Move};
    MyScene(QObject *parent = Q_NULLPTR);
    ~MyScene();

    void StartGraphicElement();
    void EndGraphicElement();
    void Set_Rotate_Elementn_on_Load(ElementItem *item,qreal angle);
    void SetFlagSelectionRect(bool b);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent) ;
    void mouseMoveEvent(QGraphicsSceneMouseEvent * mouseEvent) ;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) ;

    void keyPressEvent(QKeyEvent *event) ;
    void keyReleaseEvent(QKeyEvent *event) ;

public:
    //bool blockCaptured {false};
    bool Ctrlpushed {false};
    bool Shiftpushed {false};

    qreal scale=1;
    TextGen *textitem;
    QColor myTextColor;
    QFont *myFont;
    MyLine *myline;
    QPointF Sp, Ep,sp1,ep1,startPoint,endPoint,W,D;

    QGraphicsLineItem *line;
    QGraphicsItemGroup *group;
    ElementItem * item;
    ResistorClass *resistorobj;
    CondensatorClass *condensatorobj;
    TransistorClass *transistorobj;
    DiodeClass *diodeobj;

    QColor myLineColor;
    QColor SelectRectColor;

    Mode Figure;
    bool isDrawLine = false;
    bool isDrawSquad = false;
    bool mouseLeftButtonPress=false;

    QGraphicsItem * CastItem;
    QList <ElementItem *> radioelements;
    QList<MyLine *> listLine;
    QList<TextGen *> listText;
    QList<QGraphicsItem *> listGraphicsItemCast;
    QPainterPath PathSelectedRect;
    QTransform MoveSelektionArea;

    qreal sx=1,sy=1;
    double m2=1;
    int countResistor=0;
    int countCondensator=0;
    int countDiode=0;
    int countTransistor=0;
    int rowdbmemory=0;
    bool creategroup=false;
    QPoint origin;
    QPointF positionMouse,mouseCoordinateOffset;
    bool selectend=false;
    int selectedRadioelements=0,selectedLines=0,selectedText=0;
    bool selectedrubber=false;

public slots:
    void on_pBtn_Move_clicked();
    void on_action_Delete_triggered();
    void on_Rotate_clockwise_triggered();
    void on_Rotae_counterclockwise_triggered();
};

#endif // MYSCENE_H
