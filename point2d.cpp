#include "point2d.h"

Point2D::Point2D(QGraphicsView *graphWidget, int id)
    : graph(graphWidget) , widget(new Point2DWidget), id_(id), sourceEdgeCreated(false), destEdgeCreated(false)
{
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
}

void Point2D::addEdge(Edge *edge)
{
    edgeList << edge;
    edge->adjust();
}

void Point2D::addSrcEdge(Edge *edge)
{
    sourceEdge = edge;
    sourceEdgeCreated = true;
}

void Point2D::addDestEdge(Edge *edge)
{
    destEdge = edge;
    destEdgeCreated = true;
}

void Point2D::removeEdge(Edge *edge)
{
    edgeList.removeAll(edge);
    edge->adjust();
}

QRectF Point2D::boundingRect() const
{
    qreal adjust = 2;
    return QRectF( -10 - adjust, -10 - adjust,
                  23 + adjust, 23 + adjust);
}
//! [8]

//! [9]
QPainterPath Point2D::shape() const
{
    QPainterPath path;
    path.addEllipse(-10, -10, 20, 20);
    return path;
}

void Point2D::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::darkGray);
    painter->drawEllipse(-7, -7, 20, 20);

    QRadialGradient gradient(-3, -3, 10);
    if (option->state & QStyle::State_Sunken) {
        gradient.setCenter(3, 3);
        gradient.setFocalPoint(3, 3);
        gradient.setColorAt(1, QColor(Qt::yellow).light(120));
        gradient.setColorAt(0, QColor(Qt::darkYellow).light(120));
    } else {
        gradient.setColorAt(0, Qt::yellow);
        gradient.setColorAt(1, Qt::darkYellow);
    }
    painter->setBrush(gradient);

    painter->setPen(QPen(Qt::black, 0));
    painter->drawEllipse(-10, -10, 20, 20);
    if(id_<10){
        painter->drawText(QRectF(-5,-10,10,20),QString::number(id_));
    }else{
        painter->drawText(QRectF(-10,-10,20,20),QString::number(id_));
    }
}

QVariant Point2D::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch (change) {
    case ItemPositionHasChanged:
        if(sourceEdgeCreated) sourceEdge->adjust();
        if(destEdgeCreated) destEdge->adjust();
        //foreach (Edge *edge, edgeList)
        //    edge->adjust();
        break;
    default:
        break;
    };

    widget->move();
    return QGraphicsItem::itemChange(change, value);
}

void Point2D::addPoint(QPointF pt)
{
    if(destEdgeCreated){
        destEdge->destNode()->addPoint(pt);
    }else{
        Point2D *p = new Point2D(this->graph,this->id_+1);
        p->setPos(pt);
        this->graph->scene()->addItem(p);
        this->graph->scene()->addItem( new Edge(this,p,this->graph) );
    }
}

QPolygonF Point2D::getPoly()
{
    QPolygonF poly;
    Point2D *p = this;
    poly << p->pos();
    while(p->isDest()){
        p = p->destEdge->destNode();
        poly << p->pos();
        if(p==this)
            break;
    }
    qDebug() << poly.size();
    return poly;
}

Point2D* Point2D::getLast()
{
    Point2D *p = this;
    while(p->isDest()){
        p = p->destEdge->destNode();
        if(p==this)
            break;
    }
    return p;
}
