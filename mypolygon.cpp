#include "mypolygon.h"

MyPolygon::MyPolygon(QPolygonF poly, QMenu *contextMenu)
{
    poly_ = poly;
    myContextMenu = contextMenu;
    setAcceptedMouseButtons( Qt::LeftButton );
    //setFlag(QGraphicsItem::ItemIsSelectable, true);
    setZValue(-1);
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
    Q_UNUSED(option);
    QColor color = color_;
    if(isSelected())
        color.setAlpha(125);
    else
        color.setAlpha(50);
    painter->setPen(Qt::NoPen);
    painter->setBrush(color);
    painter->drawPolygon(poly_);
}

QRectF MyPolygon::boundingRect() const
{
    return poly_.boundingRect();
}

void MyPolygon::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    if(poly_.containsPoint(event->scenePos(),Qt::WindingFill)){
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

/*void MyPolygon::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button()==Qt::LeftButton){
        setSelected( !isSelected());
        adjust();
    }
}*/
