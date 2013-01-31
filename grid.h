#ifndef GRID_H
#define GRID_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsLineItem>

class Grid : public QObject
{
    Q_OBJECT
public:
    explicit Grid(QGraphicsScene *scene, int size = 10, QObject *parent = 0);

private:
    QList<QGraphicsLineItem*> lines;
    QGraphicsScene *scene_;
    
signals:
    
public slots:
    void setVisible(bool state);
    void show();
    void hide();
    
};

#endif // GRID_H
