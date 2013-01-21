#include "myedge.h"

MyEdge::MyEdge(MyPoint *src, MyPoint *dest, QMenu *contextMenu)
{
    src_ = src;
    dest_ = dest;
    src_->setDestEdge(this);
    dest_->setSrcEdge(this);
    myContextMenu = contextMenu;
    setZValue(1);
    adjust();
}

void MyEdge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    Q_UNUSED(option);
    painter->setPen(Qt::green);
    painter->drawLine(src_->pos(),dest_->pos());
}

QRectF MyEdge::boundingRect() const
{
    if (!src_ || !dest_)
        return QRectF();

    //qreal penWidth = 1;
    //qreal extra = (penWidth + arrowSize) / 2.0;
    qreal extra = 1.0;

    return QRectF(src_->pos(), QSizeF(dest_->x() - src_->x(),
                                      dest_->y() - src_->y()))
        .normalized()
        .adjusted(-extra, -extra, extra, extra);
}

void MyEdge::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    scene()->clearSelection();
    setSelected(true);
    if(distance(event->scenePos())<10.0){
        selectedPoint_ = proj(event->scenePos());
        myContextMenu->exec(event->screenPos());
    }else{
        QGraphicsItem::contextMenuEvent(event);
    }
}

double MyEdge::distance(QPointF pt)
{
    if (!src_ || !dest_)
        return 0.0;
    if(src_->pos()==dest_->pos())
        return QLineF(src_->pos(),pt).length();

    return QLineF(proj(pt),pt).length();
}


QPointF MyEdge::proj(QPointF pt)
{
    if (!src_ || !dest_)
        return QPointF();
    if(src_->pos()==dest_->pos())
        return src_->pos();


    QLineF line(src_->pos(),dest_->pos());
    QPointF p;

    QLineF normal = line.normalVector();
    normal.setP2( normal.p2() - normal.p1() + pt);
    normal.setP1( pt );
    line.intersect(normal,&p);
    return p;
}

QPointF MyEdge::selectedPoint()
{
    return selectedPoint_;
}

void MyEdge::adjust()
{
    prepareGeometryChange();
}
