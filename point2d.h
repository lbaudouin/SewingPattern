#ifndef POINT2D_H
#define POINT2D_H

#include <QtGui>
#include <QGraphicsItem>
#include <QGraphicsView>

class Edge;

#include "edge.h"
#include <QDebug>

QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
QT_END_NAMESPACE

class Point2DWidget : public QObject
{
    Q_OBJECT
public:
    Point2DWidget(){}
    void move(){emit this->moved();}
signals:
    void moved();
};

class Point2D : public QGraphicsItem
{
public:
    Point2D(QGraphicsView *graphWidget, int id = -1);

    void addEdge(Edge *edge);
    void removeEdge(Edge *edge);
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    Point2DWidget *widget;

    void addPoint(QPointF pt);

    void addDestEdge(Edge *edge);
    void addSrcEdge(Edge *edge);

    QPolygonF getPoly();

    inline bool isSource(){ return sourceEdgeCreated;}
    inline bool isDest(){ return destEdgeCreated;}

    Point2D *getLast();

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
    bool sourceEdgeCreated,destEdgeCreated;
    Edge *sourceEdge,*destEdge;


    QList<Edge *> edgeList;
    QGraphicsView *graph;
    int id_;
};

#endif // POINT2D_H
