#ifndef MYMESHINGPOLYGON_H
#define MYMESHINGPOLYGON_H

class MyMeshingPolygon;

#include "mymeshingpoint.h"

#include <QPolygonF>


class MyMeshingPolygon
{
public:
    MyMeshingPolygon(QPolygonF poly);

    QList<MyMeshingPoint*> getPoints();

private:
    QPolygonF poly_;
    QList<MyMeshingPoint*> points_;
};

#endif // MYMESHINGPOLYGON_H
