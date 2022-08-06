#ifndef TEXTGEN_H
#define TEXTGEN_H

#include <QObject>
#include <QGraphicsTextItem>
#include <QFont>
class TextGen : public QGraphicsTextItem
{
    Q_OBJECT
public:
    explicit TextGen(QString str, QGraphicsItem *parent = nullptr);
    ~TextGen(){}
    enum typeclass{TEXT};
    void noRotate();

protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
signals:
public:
    typeclass typeClass;
    QFont myfont;
    QColor  myTextColor = Qt::black;
};

#endif // TEXTGEN_H
