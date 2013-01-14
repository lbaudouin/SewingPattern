#ifndef MYPOINT_H
#define MYPOINT_H

#include <QtGui>
#include <QGraphicsItem>
#include <QPainter>

class MyEdge;

#include "myedge.h"

QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
QT_END_NAMESPACE

class MyPoint : public QGraphicsItem
{
    //Q_OBJECT
public:
    explicit MyPoint(QMenu *contextMenu, QPointF pt = QPointF(0,0));
    QRectF boundingRect() const;

    void setSrcEdge(MyEdge *edge);
    void setDestEdge(MyEdge *edge);
    
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
    QMenu *myContextMenu;

    MyEdge *srcEdge_,*destEdge_;

signals:
    
public slots:
    
};

#endif // MYPOINT_H
