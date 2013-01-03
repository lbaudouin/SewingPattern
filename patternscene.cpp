#include "patternscene.h"

PatternScene::PatternScene(QObject *parent) :
    QGraphicsScene(parent)
{
}

void PatternScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    switch(mouseEvent->button()){
    case Qt::LeftButton: emit this->leftClicked(mouseEvent->scenePos()); break;
    case Qt::RightButton: emit this->rightClicked(mouseEvent->scenePos()); break;
    case Qt::MiddleButton: emit this->middleClicked(mouseEvent->scenePos()); break;
    default: break;
    }
    QGraphicsScene::mousePressEvent(mouseEvent);
}
