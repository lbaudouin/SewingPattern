#ifndef POINT2D_H
#define POINT2D_H

#include <QtGui>
#include <QGraphicsItem>
#include <QGraphicsView>
#include "edge.h"

QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
QT_END_NAMESPACE

class Point2D : public QGraphicsItem
{
public:
    Point2D(QGraphicsView *graphWidget);

    void addEdge(Edge *edge);
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
    QList<Edge *> edgeList;
    QGraphicsView *graph;
};

#endif // POINT2D_H
