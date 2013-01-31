#include "grid.h"

Grid::Grid(QGraphicsScene *scene, int size, QObject *parent) :
    QObject(parent), scene_(scene)
{
    QPen penGrid(Qt::gray,0.2);
    for(int i=-1000;i<=1000;i+=size){
        lines << scene_->addLine(QLineF(QPointF(-1000,i),QPointF(1000,i)),penGrid);
        lines << scene_->addLine(QLineF(QPointF(i,-1000),QPointF(i,1000)),penGrid);
    }
}

void Grid::setVisible(bool state)
{
    if(state)
        show();
    else
        hide();
}

void Grid::show()
{
    for(int i=0;i<lines.size();i++)
        lines[i]->show();
}

void Grid::hide()
{
    for(int i=0;i<lines.size();i++)
        lines[i]->hide();
}
