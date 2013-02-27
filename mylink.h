#ifndef MYLINK_H
#define MYLINK_H

class MyLink;

#include "myedge.h"

class MyLinkObject : public QObject
{
    Q_OBJECT
public:
    MyLinkObject() : show_(true), inverse_(false) {}
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

class MyLink : public QGraphicsItem
{
public:
    explicit MyLink(MyEdge *src, MyEdge *dest, QMenu *contextMenu);
    QRectF boundingRect() const;
    void adjust();

    MyLinkObject* object;

    enum { Type = UserType + 4 };
    int type() const { return Type; }

    QString getText();

    void remove();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

private:
    MyEdge *src_,*dest_;
    QMenu *myContextMenu;
    QPolygonF poly1_,poly2_;
};

#endif // MYLINK_H
