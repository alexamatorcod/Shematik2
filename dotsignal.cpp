#include "dotsignal.h"
#include <QDebug>
#include <QBrush>
#include <QColor>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneMouseEvent>

DotSignal::DotSignal(QGraphicsItem *parentItem, QObject *parent) :
    QObject(parent)
{
    typeC=DOTSIGNAL;
    setFlag(QGraphicsItem::ItemIsSelectable);
    setParentItem(parentItem);
    setAcceptHoverEvents(true);
    setBrush(QBrush(Qt::black));
    setRect(-4,-4,8,8);
    setDotFlags(0);
}

DotSignal::DotSignal(QPointF pos, QGraphicsItem *parentItem, QObject *parent) :
    QObject(parent)
{
    typeC=DOTSIGNAL;
    setFlag(QGraphicsItem::ItemIsSelectable);
    setParentItem(parentItem);
    setAcceptHoverEvents(true);
    setBrush(QBrush(Qt::black));
    setRect(-4,-4,8,8);
    setPos(pos);
    setPreviousPosition(pos);
    setDotFlags(0);
}

DotSignal::~DotSignal()
{ }

bool DotSignal::setLineFlag(bool lf)
{   elementflag=false;
    return lineflag=lf;}

bool DotSignal::setElementFlag(bool ef)
{   lineflag=false;
    return elementflag=ef;}

bool DotSignal::MoveDotsFlag()
{
    return movedotsflag;
}

QPointF DotSignal::previousPosition() const
{
    return m_previousPosition;
}

void DotSignal::setPreviousPosition(const QPointF previousPosition)
{
    if (m_previousPosition == previousPosition)
        return;

    m_previousPosition = previousPosition;
    emit previousPositionChanged();
}

void DotSignal::setDotFlags(unsigned int flags)
{
    m_flags = flags;
}

void DotSignal::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{//qDebug()<<"DotSignal::mouseMoveEvent";
    this->setSelected(true);
    if(m_flags & Movable){
        auto dx = event->scenePos().x() - m_previousPosition.x();
        auto dy = event->scenePos().y() - m_previousPosition.y();
        moveBy(dx,dy);
        setPreviousPosition(event->scenePos());
    } else {
        QGraphicsItem::mouseMoveEvent(event);
    }
}

void DotSignal::mousePressEvent(QGraphicsSceneMouseEvent *event)
{//qDebug()<<"DotSignal::mousePressEvent";
    movedotsflag=true;
    dotpresevent=true;
    if(lineflag==true)
    {
        this->setSelected(true);
        this->parentItem()->setSelected(true);
    }
    if(m_flags & Movable){
        setPreviousPosition(event->scenePos());
    } else {
        QGraphicsItem::mousePressEvent(event);
    }
}

void DotSignal::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{//qDebug()<<"DotSignal::mouseReleaseEvent";
    movedotsflag=false;
    dotpresevent=false;
    if(lineflag==true)
    {
        this->setSelected(false);
        this->parentItem()->setSelected(true);
    }
    if(m_flags & Movable){
        setPreviousPosition(event->scenePos());
    } else {
        QGraphicsItem::mouseReleaseEvent(event);}
}

void DotSignal::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event)
    DotHoverEvent=true;
    if(lineflag==true)
        setBrush(QBrush(Qt::yellow));
    if(elementflag==true)
        setBrush(QBrush(Qt::red));
}

void DotSignal::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event)
    DotHoverEvent=false;
    setBrush(QBrush(Qt::black));
}

bool DotSignal::GetDotHoverEvent(){return DotHoverEvent;}
