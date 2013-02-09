#include "mymeshingedge.h"

MyMeshingEdge::MyMeshingEdge(MyMeshingPoint *p1, MyMeshingPoint *p2, MyMeshingTriangle *t1, MyMeshingTriangle *t2) :
    p1_(p1), p2_(p2), t1_(t1), t2_(t2)
{

}

double MyMeshingEdge::getWeight(QPointF p)
{

}

double MyMeshingEdge::getWeight(MyMeshingPoint &p)
{

}

double MyMeshingEdge::getWeight(MyMeshingPoint *p)
{

}

double MyMeshingEdge::getLenght()
{
    return QLineF(p1_->getPoint(),p2_->getPoint()).length();
}
