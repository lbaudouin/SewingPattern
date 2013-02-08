#ifndef MESHING_H
#define MESHING_H

#include <iostream>

#include <QPolygonF>
#include <QList>
#include <QLineF>
#include <QDebug>
#include <QGraphicsScene>

class MyMeshingPoint;
class MyMeshingEdge;
class MyMeshingPolygon;

class MyMeshingPoint
{
public:
    enum DOF {FREE = 0, CONSTANT, ONEDIRECTION};
    MyMeshingPoint(MyMeshingPolygon *poly, QPointF pt, DOF dof = FREE, QLineF dir = QLineF()) : poly_(poly), pt_(pt), dof_(dof), dir_(dir) {}
    double getWeight(QPointF p);
    double getWeight(MyMeshingPoint &p);
    double getWeight(MyMeshingPoint *p);
    QPointF getPoint();

    void addEdge(MyMeshingEdge *edge) { edges_.push_back(edge); }
private:
    QPointF pt_;
    DOF dof_;
    QLineF dir_;
    QList<MyMeshingEdge*> edges_;
    MyMeshingPolygon* poly_;
};

class MyMeshingEdge
{
public:
    MyMeshingEdge(MyMeshingPolygon *poly, MyMeshingPoint *p1, MyMeshingPoint *p2)  : poly_(poly), p1_(p1), p2_(p2) {}
    double getWeight(QPointF p);
    double getWeight(MyMeshingPoint &p);
    double getWeight(MyMeshingPoint *p);
    double getLenght() {return QLineF(p1_->getPoint(),p2_->getPoint()).length();}
private:
    MyMeshingPoint *p1_,*p2_;
    MyMeshingPolygon* poly_;
};

class MyMeshingPolygon
{
public:
    MyMeshingPolygon(QPolygonF poly) : poly_(poly)
    {
        if(poly_.isEmpty())
            return;

        if(!poly_.isClosed())
            poly_ << poly_.at(0);

        for(int i=0;i<poly_.size()-1;i++){
            points_ <<  new MyMeshingPoint(this,poly_.at(i));
        }
        for(int i=0;i<poly_.size()-2;i++){
            new MyMeshingEdge(this,points_.at(i),points_.at(i+1));
        }
        new MyMeshingEdge(this,points_.at(poly.size()-2),points_.at(0));
    }
private:
    QPolygonF poly_;
    QList<MyMeshingPoint*> points_;
};


class Meshing
{
public:
    //Meshing(QPolygonF polyIn, int iter, QGraphicsView *graphicsView, QGraphicsScene *scene);
    Meshing(QPolygonF polyIn, double dist, QList<QPolygonF> polyOut = QList<QPolygonF>());
    bool isGood();

    QList<QPolygonF> getMesh() {return mesh_;}


protected:
    void splitDiag();
    int findBiggestPoly();
    void addPoint(QPointF point);
    QPointF addMiddlePoint(int id);
    void refine();
    double computeArea(QPolygonF poly);
    QLineF findLongestLine();
    QPointF cutLine(QLineF line);

    bool intersects(QPolygonF poly, QLineF line);

    QString findID(QPointF pt);

private:
    QList<QPolygonF> mesh_;
    QPolygonF original_;
};

#endif // MESHING_H
