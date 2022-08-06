#include "textgen.h"
#include <QDebug>

TextGen::TextGen(QString str, QGraphicsItem *parent) : QGraphicsTextItem(parent)
{
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setTextInteractionFlags(Qt::NoTextInteraction);
    setParentItem(parent);
    setPlainText(str);
    setDefaultTextColor(myTextColor);
    myfont = QFont("Bahnschrift Light Condensed");
    myfont.setPixelSize(50);
    setFont(myfont);
    setTextWidth(100);
    setPos(10,-80);

}

void TextGen::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{qDebug()<<"mouseDoubleClickEvent";
    if (textInteractionFlags() == Qt::NoTextInteraction)
        setTextInteractionFlags(Qt::TextEditorInteraction);
    QGraphicsTextItem::mouseDoubleClickEvent(event);
}

void TextGen::noRotate()
{
    if(this->parentItem()->isSelected())
    {qDebug()<<"function:textitem->parentItem()->isSelected()";
        this->setPos(this->pos().x(),this->pos().y());
    }
}
