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

QLineF MyMeshingEdge::getLineF()
{
    return QLineF(p1_->getPoint(),p2_->getPoint());
}

void MyMeshingEdge::split()
{
    if(t1_==0 && t2_==0)
        return;
    MyMeshingPoint::DOF dof = MyMeshingPoint::FREE;
    if(p1_->getDOF()!=MyMeshingPoint::FREE && p2_->getDOF()!=MyMeshingPoint::FREE)
        dof = MyMeshingPoint::ONEDIRECTION;
    MyMeshingPoint *pt = new MyMeshingPoint( 0.5*p1_->getPoint() + 0.5*p2_->getPoint(), dof, this->getLineF() );

    if(t1_!=0){
        t1_->split(this,pt);
    }

    if(t2_!=0){
        t2_->split(this,pt);
    }
    delete this;
}
