#ifndef MYCURVE_H
#define MYCURVE_H

#include <QtGui>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>
#include <QObject>

#include <QDebug>

class MyPoint;
class MyCurve;

#include "mypoint.h"
#include "mylink.h"
#include "mypattern.h"

class MyCurveObject : public QObject
{
    Q_OBJECT
public:
    MyCurveObject() : show_(false) {}
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

class MyCurve : public QGraphicsItem
{
public:
    explicit MyCurve(MyPoint *src, MyPoint *dest, MyPattern *pattern, int edgeID, QMenu *contextMenu);
    QRectF boundingRect() const;

    QPointF getSourcePoint();
    QPointF getDestPoint();
    QPointF getPointF(int index);
    MyPoint* getSource();
    MyPoint* getDest();
    MyPoint* getPoint(int index);

    QPointF proj(QPointF p);
    double distance(QPointF p);

    QPointF selectedPoint();

    void adjust();

    MyCurveObject* object;

    void setLink(MyLink *link){
        link_ = link;
    }

    enum { Type = UserType + 2 };
    int type() const { return Type; }

    void remove();

    int size() {return points_.size();}

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

private:
    MyPoint *src_,*dest_;
    QList<MyPoint*> points_;
    QMenu *myContextMenu;
    QPointF selectedPoint_;
    MyCurve *stitchWith_;
    MyLink *link_;
    MyPattern *pattern_;
    int curveID_;
    
};

#endif // MYCURVE_H
