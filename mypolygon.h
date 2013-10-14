#ifndef MYPOLYGON_H
#define MYPOLYGON_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QMenu>
#include <QPainter>
#include <QGraphicsSceneContextMenuEvent>
#include <QDebug>

#include <mypoint.h>
#include <mypattern.h>

class MyPolygon : public QGraphicsPolygonItem
{
public:
    MyPolygon(MyPattern *pattern, QMenu *contextMenu = 0);

    void setColor(QColor color);
    //void setPolygon(QPolygonF &poly);
    void adjust();
    void addPoint(MyPoint *point);

    void insert(MyPoint* p1, MyPoint* p2, MyPoint *p);

    MyPoint* getPoint(int index) {return points_.at(index);}

    enum { Type = UserType + 3 };
    int type() const { return Type; }

    int size() { return points_.size(); }

    QPolygonF getPoly();

    MyPattern* getPattern() {return pattern_;}

    void remove();
    void remove(MyPoint *p);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

private:
    QMenu *myContextMenu;
    MyPattern *pattern_;
    QList<MyPoint*> points_;

    QColor color_;
};


#endif // MYPOLYGON_H
