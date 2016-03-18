#include "graphicsview.h"

GraphicsView::GraphicsView(QWidget *parent) :
    QGraphicsView(parent), myDragMode(false)
{
}

void GraphicsView::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::MiddleButton){
        setCursor(Qt::OpenHandCursor);
        pt_ = event->localPos();
        myDragMode = true;
    }else{
        QGraphicsView::mousePressEvent(event);
    }
}


void GraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    unsetCursor();
    myDragMode = false;
    QGraphicsView::mouseReleaseEvent(event);
}

void GraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    if(myDragMode){
        QPointF delta = event->pos() - pt_;
        pt_ = event->localPos();
        horizontalScrollBar()->setValue(horizontalScrollBar()->value() - delta.x());
        verticalScrollBar()->setValue(verticalScrollBar()->value() - delta.y());
    }else{
        QGraphicsView::mouseMoveEvent(event);
    }
}

void GraphicsView::wheelEvent(QWheelEvent *event)
{
    scaleView(pow((double)2, -event->delta() / 240.0));
}

void GraphicsView::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}
