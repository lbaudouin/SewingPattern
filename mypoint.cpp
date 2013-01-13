#include "mypoint.h"

MyPoint::MyPoint(QMenu *contextMenu, QPointF pt)//, QGraphicsScene *scene) // :    QGraphicsItem(parent,scene)
{
    myContextMenu = contextMenu;
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setZValue(-1);
    this->setPos(pt);
}

void MyPoint::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::red);
    painter->drawEllipse(-10, -10, 20, 20);
}


QRectF MyPoint::boundingRect() const
{
    qreal adjust = 2;
    return QRectF( -10 - adjust, -10 - adjust,
                  20 + adjust, 20 + adjust);
}

void MyPoint::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    scene()->clearSelection();
    setSelected(true);
    myContextMenu->exec(event->screenPos());

    QGraphicsItem::contextMenuEvent(event);
}
