#ifndef MYPOINT_H
#define MYPOINT_H

#include <QtGui>
#include <QGraphicsItem>
#include <QPainter>

class MyEdge;
class MyPolygon;

#include "myedge.h"
#include "mypolygon.h"

QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
QT_END_NAMESPACE

class MyPointWidget : public QWidget
{
    Q_OBJECT
public:
    MyPointWidget(int patternID, int pointID) : patternID_(patternID), pointID_(pointID), useGrid_(false), gridSize_(10){}
    bool useGrid() {return useGrid_;}
    int gridSize() {return gridSize_;}
private:
    int patternID_,pointID_;
    bool useGrid_;
    int gridSize_;
public slots:
    void pointMoved(QPointF pt) { emit moved(patternID_,pointID_,pt); }
    void setUseGrid(bool state){ useGrid_ = state; }
    void setGridSize(int gridsize){ gridSize_ = gridsize; }
signals:
    void moved(int patternID, int pointID, QPointF newPos);
};

class MyPoint : public QGraphicsItem
{
    //Q_OBJECT
public:
    explicit MyPoint(QPointF pt, MyPolygon *poly, int patternID, int pointID, QMenu *contextMenu = 0);
    QRectF boundingRect() const;

    void setSrcEdge(MyEdge *edge);
    void setDestEdge(MyEdge *edge);

    MyPointWidget *widget;
    
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    QMenu *myContextMenu;

    MyEdge *srcEdge_,*destEdge_;
    MyPolygon *poly_;
    int patternID_,pointID_;

    bool select_;

signals:
    
public slots:
    
};

#endif // MYPOINT_H
