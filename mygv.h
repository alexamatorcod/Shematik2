#ifndef MYGV_H
#define MYGV_H

#include <QWidget>
#include <QGraphicsView>
#include <QDebug>
#include <QWheelEvent>
#include <QSlider>
#include "myscene.h"

class MyGV : public QGraphicsView
{
    Q_OBJECT
public:

    explicit MyGV(QWidget *parent = nullptr);
    ~MyGV(){}

    void Scale_plus();
    void Scale_minus();

protected:
#if QT_CONFIG(wheelevent)
    void wheelEvent(QWheelEvent *) override;
#endif

    void mousePressEvent(QMouseEvent * mouseEvent) override;
    void mouseMoveEvent(QMouseEvent * mouseEvent) override;
    void mouseReleaseEvent(QMouseEvent *mouseEvent) override;

public:
    MyScene *Scene;
    qreal sx=1;
    qreal sy=1;
    //int m=0;
    qreal scaleFactor=0;

public slots:
    void on_pBtn_InsLine_clicked(bool checked);

};

#endif // MYGV_H
