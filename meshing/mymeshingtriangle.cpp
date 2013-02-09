#include "mymeshingtriangle.h"

MyMeshingTriangle::MyMeshingTriangle(MyMeshingPoint *p1, MyMeshingPoint *p2, MyMeshingPoint *p3, QList<MyMeshingPoint*> *points,  QList<MyMeshingTriangle*> *triangles) :
    p1_(p1), p2_(p2), p3_(p3), triangles_(triangles), points_(points)
{

}

void MyMeshingTriangle::split(double length_min)
{
    double l1 = QLineF(p1_->getPoint(),p2_->getPoint()).length();
    double l2 = QLineF(p2_->getPoint(),p3_->getPoint()).length();
    double l3 = QLineF(p3_->getPoint(),p1_->getPoint()).length();

    double max = qMax(l1,qMax(l2,l3));

    if(max<length_min)
        return;

    if(l1==max){
        QPointF pt = (p1_->getPoint()+p2_->getPoint())/2;
        MyMeshingPoint *p = new MyMeshingPoint(points_,pt);
        points_->push_back(p);

        MyMeshingTriangle* t = new MyMeshingTriangle(p,p2_,p3_,points_,triangles_);
        triangles_->push_back(t);

        p2_ = p;
        return;
    }
    if(l2==max){
        QPointF pt = (p2_->getPoint()+p3_->getPoint())/2;
        MyMeshingPoint *p = new MyMeshingPoint(points_,pt);
        points_->push_back(p);

        MyMeshingTriangle* t = new MyMeshingTriangle(p,p3_,p1_,points_,triangles_);
        triangles_->push_back(t);

        p3_ = p;
        return;
    }
    if(l3==max){
        QPointF pt = (p3_->getPoint()+p1_->getPoint())/2;
        MyMeshingPoint *p = new MyMeshingPoint(points_,pt);
        points_->push_back(p);

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
