#include "mypoint.h"

MyPoint::MyPoint(QPointF pt, MyPattern *pattern, int pointID, QMenu *contextMenu) : pt_(pt), srcEdge_(NULL), destEdge_(NULL), pattern_(pattern), pointID_(pointID), select_(false)
{
    widget = new MyPointWidget(pattern_->getID(),pointID);
    myContextMenu = contextMenu;
    poly_ = pattern_->getPoly();
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(ItemSendsGeometryChanges);
    setZValue(2);
    this->setPos(pt);
}

void MyPoint::remove()
{  
    if(srcEdge_){
        srcEdge_->remove();
        srcEdge_ = 0;
    }
    if(destEdge_){
        destEdge_->remove();
        destEdge_ = 0;
    }
    if(scene())
        scene()->removeItem(this);
    pattern_->removePoint(this);
}

void MyPoint::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    Q_UNUSED(option);
    painter->setPen(Qt::NoPen);
    if( isSelected() ){
        painter->setBrush(Qt::darkRed);
    }else{
        painter->setBrush(Qt::red);
    }
    painter->drawEllipse(-5, -5, 10, 10);

    /*QFont font = QApplication::font();
    font.setPixelSize( 8 );
    painter->setFont( font );
    painter->setBrush(Qt::NoBrush);
    painter->setPen(Qt::black);
    painter->drawText(QRect(-5,-5,10,10),Qt::AlignCenter,QString::number(pointID_));*/
}

void MyPoint::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

    if(widget->useGrid()){
        int gridSize = widget->gridSize();
        int poseX = gridSize*((int)(pos().x()+(pos().x()>0?gridSize/2:-gridSize/2))/gridSize);
        int poseY = gridSize*((int)(pos().y()+(pos().y()>0?gridSize/2:-gridSize/2))/gridSize);
        this->setPos(poseX,poseY);
    }

    this->update();
    QGraphicsItem::mouseReleaseEvent(event);
}

QRectF MyPoint::boundingRect() const
{
    qreal adjust = 2;
    return QRectF( -5 - adjust, -5 - adjust,
                  10 + adjust, 10 + adjust);
}

void MyPoint::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    scene()->clearSelection();
    setSelected(true);
    myContextMenu->exec(event->screenPos());

    //QGraphicsItem::contextMenuEvent(event);
}

QPointF MyPoint::getPoint()
{
    return pt_;
}

void MyPoint::setSrcEdge(MyEdge *edge)
{
    srcEdge_ = edge;
}

void MyPoint::setDestEdge(MyEdge *edge)
{
    destEdge_ = edge;
}

QVariant MyPoint::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch (change) {
    case ItemPositionHasChanged:
        if(srcEdge_) srcEdge_->adjust();
        if(destEdge_) destEdge_->adjust();
        if(poly_) poly_->adjust();
        widget->pointMoved(this->pos());
        pt_ = this->pos();
        break;
    default:
        break;
    };

    return QGraphicsItem::itemChange(change, value);
}
