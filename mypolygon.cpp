#include "mypolygon.h"

MyPolygon::MyPolygon(QPolygonF poly, QMenu *contextMenu)
{
    poly_ = poly;
    myContextMenu = contextMenu;
    setAcceptedMouseButtons( Qt::LeftButton );
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setZValue(-1);
}

void MyPolygon::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(poly_.containsPoint(event->scenePos(),Qt::WindingFill)){
        qDebug() << "Is inside poly";
        if (event->button() == Qt::LeftButton){// && (flags() & ItemIsSelectable)) {
            bool multiSelect = (event->modifiers() & Qt::ControlModifier) != 0;
            if (!multiSelect) {
                setSelected(true);
                qDebug() << "Set selected";
                event->accept();
                /*
                if (!d_ptr->selected) {
                    if (QGraphicsScene *scene = d_ptr->scene) {
                        ++scene->d_func()->selectionChanging;
                        scene->clearSelection();
                        --scene->d_func()->selectionChanging;
                    }
                    setSelected(true);
                }*/
            }
        } else if (!(flags() & ItemIsMovable)) {
            event->ignore();
        }
        /*if (d_ptr->isWidget) {
            // Qt::Popup closes when you click outside.
            QGraphicsWidget *w = static_cast<QGraphicsWidget *>(this);
            if ((w->windowFlags() & Qt::Popup) == Qt::Popup) {
                event->accept();
                if (!w->rect().contains(event->pos()))
                    w->close();
            }
        }*/
    }else{
        QGraphicsItem::mousePressEvent(event);
    }
}

/*void MyPolygon::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(poly_.containsPoint(event->scenePos(),Qt::WindingFill)){
        setSelected(true);
    }else{
        QGraphicsItem::mousePressEvent(event);
    }
}*/

void MyPolygon::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    Q_UNUSED(option);
    QColor color = color_;
    if(isSelected())
        color.setAlpha(125);
    else
        color.setAlpha(50);
    painter->setPen(Qt::NoPen);
    painter->setBrush(color);
    painter->drawPolygon(poly_);
}

QRectF MyPolygon::boundingRect() const
{
    return poly_.boundingRect();
}

void MyPolygon::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    if(poly_.containsPoint(event->scenePos(),Qt::WindingFill)){
        scene()->clearSelection();
        setSelected(true);
        myContextMenu->exec(event->screenPos());
    }else{
        QGraphicsItem::contextMenuEvent(event);
    }
}

void MyPolygon::adjust()
{
    prepareGeometryChange();
}

void MyPolygon::setColor(QColor color)
{
    color_ = color;
}

/*void MyPolygon::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button()==Qt::LeftButton){
        setSelected( !isSelected());
        adjust();
    }
}*/
