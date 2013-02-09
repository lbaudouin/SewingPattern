#ifndef MYMESHINGTRIANGLE_H
#define MYMESHINGTRIANGLE_H

class MyMeshingTriangle;

#include "mymeshingpoint.h"
#include "math.h"
#include <QList>

class MyMeshingTriangle
{
public:
    MyMeshingTriangle(MyMeshingPoint *p1, MyMeshingPoint *p2, MyMeshingPoint *p3, QList<MyMeshingPoint*> *points,  QList<MyMeshingTriangle*> *triangles);

    void split(double length_min = 10.0);
    double area();
    double longestSide();

private:
    MyMeshingPoint *p1_,*p2_,*p3_;
    QList<MyMeshingTriangle*> *triangles_;
    QList<MyMeshingPoint*> *points_;
};

#endif // MYMESHINGTRIANGLE_H
