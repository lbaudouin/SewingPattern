#ifndef MYMESHINGEDGE_H
#define MYMESHINGEDGE_H

class MyMeshingEdge;

#include "mymeshingpoint.h"
#include "mymeshingtriangle.h"

class MyMeshingEdge
{
public:
    MyMeshingEdge(MyMeshingPoint *p1, MyMeshingPoint *p2, MyMeshingTriangle *t1 = 0, MyMeshingTriangle *t2 = 0);
    double getWeight(QPointF p);
    double getWeight(MyMeshingPoint &p);
    double getWeight(MyMeshingPoint *p);
    double getLenght();
private:
    MyMeshingPoint *p1_,*p2_;
    MyMeshingTriangle *t1_,*t2_;
};

#endif // MYMESHINGEDGE_H
