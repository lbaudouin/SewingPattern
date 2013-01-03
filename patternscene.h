#ifndef PATTERNSCENE_H
#define PATTERNSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include <QDebug>

class PatternScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit PatternScene(QObject *parent = 0);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);

signals:
    void rightClicked(QPointF);
    void leftClicked(QPointF);
    void middleClicked(QPointF);
    
public slots:
    
};

#endif // PATTERNSCENE_H
