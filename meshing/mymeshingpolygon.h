#ifndef MYMESHINGPOLYGON_H
#define MYMESHINGPOLYGON_H

class MyMeshingPolygon;

#include "mymeshingpoint.h"
#include "mymeshingtriangle.h"

#include <QPolygonF>
#include <QDebug>

class MyMeshingPolygon
{
public:
    MyMeshingPolygon(QPolygonF poly, QList<QPolygonF> out = QList<QPolygonF>());
    void setPoint(QPointF point);
    void setPoints(QList<QPointF> points);
    void setEdge(QLineF edge);
    void setEdges(QList<QLineF> edges);

    void mesh();

    QList<MyMeshingPoint*> getPoints();
    bool intersects(QPolygonF poly, QLineF line);

protected:
    bool split();

private:
    QPolygonF poly_;
    QList<QPointF> constantPoints_;
    QList<QLineF> constantEdges_;
    QList<MyMeshingPoint*> points_;
    QList<MyMeshingTriangle*> triangles_;

    QMap<QPointF,MyMeshingPoint*> mapPoints_;
};

#endif // MYMESHINGPOLYGON_H
