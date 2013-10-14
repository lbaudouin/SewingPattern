#ifndef MYMESHINGTRIANGLE_H
#define MYMESHINGTRIANGLE_H

class MyMeshingTriangle;

#include "mymeshingpoint.h"
#include "math.h"
#include <QList>

class MyMeshingTriangle
{
public:
    MyMeshingTriangle(MyMeshingPoint *p1, MyMeshingPoint *p2, MyMeshingPoint *p3, QList<MyMeshingPoint*> *points = 0,  QList<MyMeshingTriangle*> *triangles = 0);

    bool split(double length_max = 10.0);
    void split(MyMeshingEdge *e, MyMeshingPoint *p);
    double area();
    double longestSide();

private:
    MyMeshingPoint *p1_,*p2_,*p3_;
    MyMeshingEdge *e1_,*e2_,*e3_;
    QList<MyMeshingTriangle*> *triangles_;
    QList<MyMeshingPoint*> *points_;
};

#endif // MYMESHINGTRIANGLE_H
