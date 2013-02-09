#include "mymeshingpoint.h"

MyMeshingPoint::MyMeshingPoint(QList<MyMeshingPoint*> *poly, QPointF pt, DOF dof, QLineF dir) : poly_(poly), pt_(pt), dof_(dof), dir_(dir)
{

}

double MyMeshingPoint::getWeight(QPointF p)
{
    return 0.0;
}

double MyMeshingPoint::getWeight(MyMeshingPoint &p)
{
    return 0.0;
}


double MyMeshingPoint::getWeight(MyMeshingPoint *p)
{
    return 0.0;
}


QPointF MyMeshingPoint::getPoint()
{
    return pt_;
}

void MyMeshingPoint::computeDisplacement()
{
    if(dof_==CONSTANT)
        return;

    QPointF delta(0,0);
    for(int i=0;i<poly_->size();i++){
        if(poly_->at(i)==this)
            continue;

        QPointF pt = poly_->at(i)->getPoint();
        QLineF l = QLineF(pt,pt_);
        double d = l.length();

        if(d==0.0)
            continue;

        QPointF tmp(l.dx()/d,l.dy()/d);
        delta += tmp;
    }

    if(dof_==FREE){
        pt_ += delta;
    }
    if(dof_==ONEDIRECTION){
        QLineF u = dir_.unitVector();
        double dx = delta.x() * (u.x2()-u.x1());
        double dy = delta.y() * (u.y2()-u.y1());
        pt_ += QPointF(dx,dy);
    }
}

void MyMeshingPoint::addEdge(MyMeshingEdge *edge)
{
    edges_.push_back(edge);
}

