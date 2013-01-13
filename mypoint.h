#ifndef MYPOINT_H
#define MYPOINT_H

#include <QtGui>
#include <QGraphicsItem>
#include <QPainter>

class MyEdge;

#include "myedge.h"


class MyPoint : public QGraphicsItem
{
    //Q_OBJECT
public:
    explicit MyPoint(QMenu *contextMenu, QPointF pt = QPointF(0,0));//, QObject *parent = 0, QGraphicsScene *scene = 0);
    QRectF boundingRect() const;
    
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

private:
    QMenu *myContextMenu;

signals:
    
public slots:
    
};

#endif // MYPOINT_H
