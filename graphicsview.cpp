#include "graphicsview.h"

GraphicsView::GraphicsView(QWidget *parent) :
    QGraphicsView(parent), myDragMode(false)
{
}

void GraphicsView::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::MiddleButton){
        setCursor(Qt::OpenHandCursor);
        pt_ = event->posF();
        myDragMode = true;
    }
}


void GraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    unsetCursor();
    myDragMode = false;
}

void GraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    if(myDragMode){
        double speed = 0.1;
        QPointF delta = event->pos() - pt_;
        horizontalScrollBar()->setValue(horizontalScrollBar()->value() - speed*delta.x());
        verticalScrollBar()->setValue(verticalScrollBar()->value() - speed*delta.y());
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
