#include "mygv.h"

MyGV::MyGV(QWidget *parent) : QGraphicsView(parent)
{
    setFrameStyle(Sunken | StyledPanel);
    setDragMode(QGraphicsView::RubberBandDrag);
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

}
#if QT_CONFIG(wheelevent)
void MyGV::wheelEvent(QWheelEvent *event)
{qDebug()<<"MyGV::wheelEvent";
    if (event->modifiers() & Qt::ControlModifier) {
        qDebug()<<"ControlModifier";
        if (event->angleDelta().y() > 0)
            //zoomIn(6);
            Scale_plus();
        else
            //zoomOut(6);
            Scale_minus();
        event->accept();
    } else {
        QGraphicsView::wheelEvent(event);
    }
}
#endif

void MyGV::mousePressEvent(QMouseEvent * mouseEvent)
{   qDebug()<<"MyGV::mousePressEvent";
    if(!rubberBandRect().isEmpty())
    {
        Scene->SetFlagSelectionRect(true);
    }
    QGraphicsView::mousePressEvent(mouseEvent);
    //update();
}
void MyGV::mouseMoveEvent(QMouseEvent * mouseEvent)
{//qDebug()<<"MyGV::mouseMoveEvent";
    if(!rubberBandRect().isEmpty())
    {
        Scene->SetFlagSelectionRect(true);
    }
    setInteractive(true);
    QGraphicsView::mouseMoveEvent(mouseEvent);
}
void MyGV::mouseReleaseEvent(QMouseEvent *mouseEvent)
{   qDebug()<<"MyGV::mouseReleaseEvent";
    Scene->SetFlagSelectionRect(false);
    QGraphicsView::mouseReleaseEvent(mouseEvent);
    // update();
}

void MyGV::Scale_plus()
{//qDebug()<<"MyGV::Scale_plus";
    sx+=0.1;
    sy+=0.1;
    qDebug()<<"sx="<<sx<<"sy="<<sy;
    QTransform matrix;
    matrix.scale(sx, sy);
    setTransform(matrix);
}

void MyGV::Scale_minus()
{//qDebug()<<"MyGV::Scale_minus";
    sx-=0.1;
    sy-=0.1;
    qDebug()<<"sx="<<sx<<"sy="<<sy;
    QTransform matrix;
    matrix.scale(sx,sy);
    setTransform(matrix);
}

void MyGV::on_pBtn_InsLine_clicked(bool checked)
{
    if(checked)
    {  qDebug()<<"pushButton_InsertLine";
        Scene->Figure=MyScene::InsertLine;
        setDragMode(QGraphicsView::NoDrag);}
    if(!checked)
    {  qDebug()<<"pushButton_Move false";
        Scene->Figure=MyScene::Move;
        setDragMode(QGraphicsView::RubberBandDrag);
        //setFocusItem(myline);
    }
}

