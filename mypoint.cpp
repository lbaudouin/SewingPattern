#include "mypoint.h"

MyPoint::MyPoint(QPointF pt, MyPolygon *poly, int patternID, int pointID, QMenu *contextMenu) : srcEdge_(NULL), destEdge_(NULL), poly_(poly), patternID_(patternID), pointID_(pointID), select_(false)
{
    widget = new MyPointWidget(patternID,pointID);
    myContextMenu = contextMenu;
    poly->addPoint(this);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(ItemSendsGeometryChanges);
    setZValue(2);
    this->setPos(pt);
}

void MyPoint::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    Q_UNUSED(option);
    painter->setPen(Qt::NoPen);
    QColor color(Qt::red);
    if( select_ ){
        color.setAlpha(125);
    }
    painter->setBrush(color);
    painter->drawEllipse(-10, -10, 20, 20);
    painter->drawText(this->boundingRect(),Qt::AlignCenter,QString::number(pointID_));
}

void MyPoint::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    select_ = true;
    this->update();
    QGraphicsItem::mousePressEvent(event);
}

void MyPoint::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    select_ = false;
    this->update();
    QGraphicsItem::mouseReleaseEvent(event);
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
        if(poly_) poly_->adjust();
        widget->pointMoved(this->pos());
        break;
    default:
        break;
    };

    return QGraphicsItem::itemChange(change, value);
}
