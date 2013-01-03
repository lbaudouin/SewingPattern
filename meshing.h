#ifndef MESHING_H
#define MESHING_H

#include <iostream>

#include <QPolygonF>
#include <QList>
#include <QLineF>
#include <QDebug>
#include <QGraphicsScene>

class Meshing
{
public:
    Meshing(QPolygonF polyIn, int iter, QGraphicsView *graphicsView, QGraphicsScene *scene);
    Meshing(QPolygonF polyIn, double dist, QList<QPolygonF> polyOut = QList<QPolygonF>());

    QList<QPolygonF> getMesh() {return mesh_;}
protected:
    void splitDiag();
    int findBiggestPoly();
    void addPoint(QPointF point);
    QPointF addMiddlePoint(int id);
    void refine();
    double computeArea(QPolygonF poly);
    QLineF findLongestLine();
    QPointF cutLine(QLineF line);

    bool intersects(QPolygonF poly, QLineF line);

    QString findID(QPointF pt);

private:
    QList<QPolygonF> mesh_;
    QPolygonF original_;
};

#endif // MESHING_H
