#include "mylink.h"

MyLink::MyLink(MyEdge *src, MyEdge *dest, QMenu *contextMenu) : src_(src), dest_(dest), object(new MyLinkObject)
{
    src_->setLink(this);
    dest_->setLink(this);
    myContextMenu = contextMenu;
    setZValue(1);
    adjust();
    setFlag(QGraphicsItem::ItemIsSelectable, true);
}

void MyLink::remove()
{
    src_->setLink(0);
    dest_->setLink(0);
    if(scene())
        scene()->removeItem(this);
}

void MyLink::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    Q_UNUSED(option);

    if(src_==0 || dest_==0)
        return;

    if(isSelected()){
        painter->setPen(Qt::red);
    }else{
        painter->setPen(Qt::green);
    }

    if(object->show()){
        QPointF a1,a2,a3,a4,a5, b1,b2,b3,b4,b5;
        a1 = src_->getSourcePoint();
        a2 = 0.75*src_->getSourcePoint() + 0.25*src_->getDestPoint();
        a3 = 0.5*src_->getSourcePoint() + 0.5*src_->getDestPoint();
        a4 = 0.25*src_->getSourcePoint() + 0.75*src_->getDestPoint();
        a5 = src_->getDestPoint();
        b1 = dest_->getSourcePoint();
        b2 = 0.75*dest_->getSourcePoint() + 0.25*dest_->getDestPoint();
        b3 = 0.5*dest_->getSourcePoint() + 0.5*dest_->getDestPoint();
        b4 = 0.25*dest_->getSourcePoint() + 0.75*dest_->getDestPoint();
        b5 = dest_->getDestPoint();
        QPolygonF poly;
        if(object->inverse()){
            poly << a1 << a5 << b1 << b5;
            painter->drawLine(QLineF(a1,b5));
            painter->drawLine(QLineF(a2,b4));
            painter->drawLine(QLineF(a3,b3));
            painter->drawLine(QLineF(a4,b2));
            painter->drawLine(QLineF(a5,b1));
        }else{
            poly << a1 << a5 << b5 << b1;
            painter->drawLine(QLineF(a1,b1));
            painter->drawLine(QLineF(a2,b2));
            painter->drawLine(QLineF(a3,b3));
            painter->drawLine(QLineF(a4,b4));
            painter->drawLine(QLineF(a5,b5));
        }

        setPolygon(poly);
    }
}

void MyLink::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    if(myContextMenu==0){
        QGraphicsItem::contextMenuEvent(event);
        return;
    }else{
        scene()->clearSelection();
        setSelected(true);
        myContextMenu->exec(event->screenPos());
        return;
    }
}

void MyLink::adjust()
{
    prepareGeometryChange();
}

QString MyLink::getText()
{
    int srcPattern = src_->getPattern()->getID();
    int srcEdge = src_->getID();
    int destPattern = dest_->getPattern()->getID();
    int destEdge = dest_->getID();
    bool swap = object->inverse();
    return QString("LINK %1 %2 %3 %4 %5\n").arg(QString::number(srcPattern),QString::number(srcEdge),QString::number(destPattern),QString::number(destEdge),swap?"true":"false");
}

void MyLink::display(QGraphicsScene *scene)
{
    scene->addItem(this);
}
