#ifndef MYEDGE_H
#define MYEDGE_H

#include <QtGui>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>
#include <QObject>

#include <QDebug>

class MyPoint;
class MyEdge;

#include <mypoint.h>

class MyEdgeObject : public QObject
{
    Q_OBJECT
public:
    MyEdgeObject() : show_(false) {}
    bool show() { return show_; }
    bool inverse() { return inverse_; }
private:
    bool show_;
    bool inverse_;
public slots:
    void showStich(){ show_ = true; }
    void hideStich(){ show_ = false; }
    void setStichVisible(bool visibility) { show_ = visibility; }
    void toggle() { inverse_ = !inverse_; }
};

class MyEdge : public QGraphicsItem
{
public:
    explicit MyEdge(MyPoint *src, MyPoint *dest, QMenu *contextMenu);
    QRectF boundingRect() const;

    QPointF getSourcePoint();
    QPointF getDestPoint();

    QPointF proj(QPointF p);
    double distance(QPointF p);

    QPointF selectedPoint();

    void adjust();

    MyEdgeObject* object;


protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

private:
    MyPoint *src_,*dest_;
    QMenu *myContextMenu;
    QPointF selectedPoint_;
    MyEdge *stitchWith_;
    
};

#endif // MYEDGE_H
