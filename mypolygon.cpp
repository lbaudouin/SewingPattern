#include "mypolygon.h"

MyPolygon::MyPolygon(MyPattern *pattern, QMenu *contextMenu)
{
    pattern_ = pattern;
    myContextMenu = contextMenu;
    setAcceptedMouseButtons( Qt::LeftButton );
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setZValue(-1);
}

void MyPolygon::remove()
{
    for(int i=0;i<points_.size();i++)
        points_.at(i)->remove();
    points_.clear();

    if(scene())
        scene()->removeItem(this);
}

void MyPolygon::addPoint(MyPoint *point)
{
    point->setPolygon(this);
    points_ << point;
}

/*void MyPolygon::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(poly_.containsPoint(event->scenePos(),Qt::WindingFill)){
        setSelected(true);
    }else{
        QGraphicsItem::mousePressEvent(event);
    }
}*/

void MyPolygon::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    //painter->save();
    Q_UNUSED(option);
    QColor color = color_;
    if(isSelected())
        color.setAlpha(125);
    else
        color.setAlpha(50);
    painter->setPen(Qt::NoPen);
    painter->setBrush(color);

    QPolygonF poly = getPoly();
    setPolygon(poly);

    painter->drawPolygon(poly,Qt::WindingFill);

    painter->setPen(Qt::black);
    //qDebug() << pattern_->getName();
    //QRect rect(0,0,200,50);
    //painter->drawText(rect, Qt::AlignCenter, pattern_->getName());
    painter->drawText(poly.boundingRect(), Qt::AlignCenter, pattern_->getName());
    //painter->drawText(QRect(pattern_->getPolygon().at(0).toPoint(),QSize(200,50)), Qt::AlignCenter, pattern_->getName());
    //painter->restore();
}

void MyPolygon::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    if(myContextMenu!=0){
        scene()->clearSelection();
        setSelected(true);
        myContextMenu->exec(event->screenPos());
    }else{
        QGraphicsItem::contextMenuEvent(event);
    }
}

void MyPolygon::adjust()
{
    prepareGeometryChange();
}

void MyPolygon::setColor(QColor color)
{
    color_ = color;
}

void MyPolygon::remove(MyPoint *p)
{
    points_.removeAll(p);
}

QPolygonF MyPolygon::getPoly()
{
    QPolygonF poly;
    for(int i=0;i<points_.size();i++)
        poly << points_.at(i)->getPoint();
    return poly;
}

void  MyPolygon::insert(MyPoint* p1, MyPoint* p2, MyPoint *p)
{
    Q_UNUSED(p1);
    int index = points_.indexOf(p2);
    points_.insert(index,p);
}
