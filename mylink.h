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
    void setInverse(bool inverse) { inverse_ = inverse; }
    void toggle() { inverse_ = !inverse_; }
};

class MyLink : public QGraphicsPolygonItem
{
public:
    explicit MyLink(MyEdge *src, MyEdge *dest, QMenu *contextMenu);
    //~MyLink() {qDebug()<<"~MyLink()";}
    void adjust();
    void display(QGraphicsScene *scene);

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
};

#endif // MYLINK_H
