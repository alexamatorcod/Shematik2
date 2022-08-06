#ifndef DOTSIGNAL_H
#define DOTSIGNAL_H

#include <QObject>
#include <QGraphicsRectItem>

class QGraphicsSceneHoverEventPrivate;
class QGraphicsSceneMouseEvent;

class DotSignal : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF previousPosition READ previousPosition WRITE setPreviousPosition NOTIFY previousPositionChanged)

public:
    explicit DotSignal(QGraphicsItem *parentItem = 0, QObject *parent = 0);
    explicit DotSignal(QPointF pos, QGraphicsItem *parentItem = 0, QObject *parent = 0);
    ~DotSignal();
    enum {Type = UserType+2};
    enum Flags {
        Movable = 0x01
    };
    enum typeclass {DOTSIGNAL};

    int type() const override
    {
        // Enable the use of qgraphicsitem_cast with this item.
        return Type;
    }

    QPointF previousPosition() const;
    void setPreviousPosition(const QPointF previousPosition);

    void setDotFlags(unsigned int flags);

    bool MoveDotsFlag();
    bool setLineFlag(bool lf);
    bool setElementFlag(bool ef);

    bool getDotPressEvent(){return dotpresevent;}
    bool getDotReleaseEvent(){return dotreleaseevent;}
    bool GetDotHoverEvent();
signals:
    void previousPositionChanged();

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

public slots:

public:
    typeclass typeC;
    unsigned int m_flags;
    bool movedotsflag=false;
    QPointF m_previousPosition;
    bool lineflag=false;
    bool elementflag=false;
    bool dotpresevent=false;
    bool dotreleaseevent=false;
    bool DotHoverEvent=false;
};

#endif // DOTSIGNAL_H
