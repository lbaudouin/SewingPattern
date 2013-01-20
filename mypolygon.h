#ifndef MYPOLYGON_H
#define MYPOLYGON_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QMenu>
#include <QPainter>
#include <QGraphicsSceneContextMenuEvent>

class MyPolygon : public QGraphicsItem
{
public:
    MyPolygon(QPolygonF poly, QMenu *contextMenu = 0);
    QRectF boundingRect() const;

    void setColor(QColor color);
    void setPolygon(QPolygonF &poly);
    void adjust();

protected:
    //void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

private:
    QMenu *myContextMenu;
    QPolygonF poly_;

    QColor color_;
};


#endif // MYPOLYGON_H
