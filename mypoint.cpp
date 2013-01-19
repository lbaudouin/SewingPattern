#include "mypoint.h"

MyPoint::MyPoint(QPointF pt, int patternID, int pointID, QMenu *contextMenu) : srcEdge_(NULL), destEdge_(NULL), patternID_(patternID), pointID_(pointID)
{
    widget = new MyPointWidget(patternID,pointID);
    myContextMenu = contextMenu;
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(ItemSendsGeometryChanges);
    setZValue(-1);
    this->setPos(pt);
}

void MyPoint::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    Q_UNUSED(option);
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

void MyPoint::setSrcEdge(MyEdge *edge)
{
    srcEdge_ = edge;
}

void MyPoint::setDestEdge(MyEdge *edge)
{
    destEdge_ = edge;
}

QVariant MyPoint::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch (change) {
    case ItemPositionHasChanged:
        if(srcEdge_) srcEdge_->adjust();
        if(destEdge_) destEdge_->adjust();
        widget->pointMoved(this->pos());
        break;
    default:
        break;
    };

    return QGraphicsItem::itemChange(change, value);
}
