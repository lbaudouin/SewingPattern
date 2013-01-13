#ifndef MYEDGE_H
#define MYEDGE_H

#include <QtGui>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>

#include <QDebug>

class MyPoint;

#include <mypoint.h>

class MyEdge : public QGraphicsItem
{
    //Q_OBJECT
public:
    explicit MyEdge(MyPoint *src, MyPoint *dest, QMenu *contextMenu);//, QObject *parent = 0, QGraphicsScene *scene = 0);
    QRectF boundingRect() const;

    QPointF proj(QPointF p);
    double distance(QPointF p);

    QPointF selectedPoint();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

private:
    MyPoint *src_,*dest_;
    QMenu *myContextMenu;
    QPointF selectedPoint_;
    
signals:
    
public slots:
    
};

#endif // MYEDGE_H
