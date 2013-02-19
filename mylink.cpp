#include "mylink.h"

MyLink::MyLink(MyEdge *src, MyEdge *dest, QMenu *contextMenu) : src_(0), dest_(0), object(new MyLinkObject)
{
    src_ = src;
    dest_ = dest;
    myContextMenu = contextMenu;
    setZValue(1);
    adjust();
    setFlag(QGraphicsItem::ItemIsSelectable, true);
}

void MyLink::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    Q_UNUSED(option);

    if(src_==0 || dest_==0)
        return;

    if(isSelected()){
        painter->setPen(Qt::red);
    }else{
        painter->setPen(Qt::green);
    }

    if(object->show()){
        QPointF a1,a2,a3,a4, b1,b2,b3,b4;
        a1 = src_->getSourcePoint();
        a2 = 0.75*src_->getSourcePoint() + 0.25*src_->getDestPoint();
        a3 = 0.25*src_->getSourcePoint() + 0.75*src_->getDestPoint();
        a4 = src_->getDestPoint();
        b1 = dest_->getSourcePoint();
        b2 = 0.75*dest_->getSourcePoint() + 0.25*dest_->getDestPoint();
        b3 = 0.25*dest_->getSourcePoint() + 0.75*dest_->getDestPoint();
        b4 = dest_->getDestPoint();
        if(object->inverse()){
            painter->drawLine(QLineF(a1,b4));
            painter->drawLine(QLineF(a2,b3));
            painter->drawLine(QLineF(a3,b2));
            painter->drawLine(QLineF(a4,b1));
        }else{
            painter->drawLine(QLineF(a1,b1));
            painter->drawLine(QLineF(a2,b2));
            painter->drawLine(QLineF(a3,b3));
            painter->drawLine(QLineF(a4,b4));
        }
    }
}

QRectF MyLink::boundingRect() const
{
    if (!src_ || !dest_)
        return QRectF();

    qreal extra = 1.0;

    QPolygonF poly;
    poly << src_->getSourcePoint() << src_->getDestPoint() << dest_->getSourcePoint() << dest_->getDestPoint() ;

    return poly.boundingRect()
        .normalized()
        .adjusted(-extra, -extra, extra, extra);
}

void MyLink::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    scene()->clearSelection();
    setSelected(true);
    myContextMenu->exec(event->screenPos());
}

void MyLink::adjust()
{
    prepareGeometryChange();
}
