#ifndef MYMESHINGPOINT_H
#define MYMESHINGPOINT_H

class MyMeshingPoint;

#include <QList>
#include <QLineF>
#include "mymeshingedge.h"

class MyMeshingPoint
{
public:
    enum DOF {FREE = 0, CONSTANT, ONEDIRECTION};
    MyMeshingPoint(QPointF pt, DOF dof = MyMeshingPoint::FREE, QLineF dir = QLineF());
    double getWeight(QPointF p);
    double getWeight(MyMeshingPoint &p);
    double getWeight(MyMeshingPoint *p);
    QPointF getPoint();

    void computeDisplacement();
    void addEdge(MyMeshingEdge *edge);

    DOF getDOF();

private:
    QPointF pt_;
    DOF dof_;
    QLineF dir_;
    QList<MyMeshingEdge*> edges_;
};

#endif // MYMESHINGPOINT_H
