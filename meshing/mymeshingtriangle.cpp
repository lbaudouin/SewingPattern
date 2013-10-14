#include "mymeshingtriangle.h"

MyMeshingTriangle::MyMeshingTriangle(MyMeshingPoint *p1, MyMeshingPoint *p2, MyMeshingPoint *p3, QList<MyMeshingPoint*> *points,  QList<MyMeshingTriangle*> *triangles) :
    p1_(p1), p2_(p2), p3_(p3), triangles_(triangles), points_(points)
{
    e1_ = new MyMeshingEdge(p1_,p2_);
    e2_ = new MyMeshingEdge(p2_,p3_);
    e3_ = new MyMeshingEdge(p3_,p1_);
}

bool MyMeshingTriangle::split(double length_max)
{
    double l1 = e1_->getLenght();
    double l2 = e2_->getLenght();
    double l3 = e3_->getLenght();

    double max = qMax(l1,qMax(l2,l3));

    if(max<length_max)
        return false;

    if(l1==max){
        e1_->split();
        return true;
    }
    if(l2==max){
        e2_->split();
        return true;
    }
    if(l3==max){
        e3_->split();
        return true;
    }

}

void MyMeshingTriangle::split(MyMeshingEdge *e, MyMeshingPoint *p)
{
    if(e==e1_){
        MyMeshingTriangle* t = new MyMeshingTriangle(p,p2_,p3_,points_,triangles_);
        triangles_->push_back(t);
        p2_ = p;
        return;
    }
    if(e==e2_){
        MyMeshingTriangle* t = new MyMeshingTriangle(p,p3_,p1_,points_,triangles_);
        triangles_->push_back(t);
        p3_ = p;
        return;
    }
    if(e==e3_){
        MyMeshingTriangle* t = new MyMeshingTriangle(p,p1_,p2_,points_,triangles_);
        triangles_->push_back(t);
        p1_ = p;
        return;
    }

}

double MyMeshingTriangle::area()
{
    double a = QLineF(p1_->getPoint(),p2_->getPoint()).length();
    double b = QLineF(p2_->getPoint(),p3_->getPoint()).length();
    double c = QLineF(p3_->getPoint(),p1_->getPoint()).length();
    double s = (a+b+c)/2;

    return ::sqrt(s*(s-a)*(s-b)*(s-c));
}

double MyMeshingTriangle::longestSide()
{
    double l1 = QLineF(p1_->getPoint(),p2_->getPoint()).length();
    double l2 = QLineF(p2_->getPoint(),p3_->getPoint()).length();
    double l3 = QLineF(p3_->getPoint(),p1_->getPoint()).length();

    return qMax(l1,qMax(l2,l3));
}
