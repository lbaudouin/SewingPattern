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

class MyPointWidget : public QWidget
{
    Q_OBJECT
public:
    MyPointWidget(int patternID, int pointID) : patternID_(patternID), pointID_(pointID){}
private:
    int patternID_,pointID_;
public slots:
    void pointMoved(QPointF pt) { emit moved(patternID_,pointID_,pt); }
signals:
    void moved(int patternID, int pointID, QPointF newPos);
};

class MyPoint : public QGraphicsItem
{
    //Q_OBJECT
public:
    explicit MyPoint(QPointF pt, int patternID, int pointID, QMenu *contextMenu = 0);
    QRectF boundingRect() const;

    void setSrcEdge(MyEdge *edge);
    void setDestEdge(MyEdge *edge);

    MyPointWidget *widget;
    
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
    QMenu *myContextMenu;

    MyEdge *srcEdge_,*destEdge_;
    int patternID_,pointID_;

signals:
    
public slots:
    
};

#endif // MYPOINT_H
