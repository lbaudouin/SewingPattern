#include "mymeshingpolygon.h"

bool operator<(const QPointF &p1, const QPointF &p2){
    if(p1.x()<p2.x()) return true;
    if(p1.x()>p2.x()) return false;
    if(p1.y()<p2.y()) return true;
    if(p1.y()>p2.y()) return false;
    return false;
}

MyMeshingPolygon::MyMeshingPolygon(QPolygonF poly, QList<QPolygonF> /*out*/) : poly_(poly)
{
    if(poly_.isEmpty()){
        qDebug() << "Invalid polygon for meshing";
        return;
    }

    if(0){
        qDebug() << "Invalid polygon for meshing";
        return;
    }

    if(!poly_.isClosed())
        poly_ << poly_.at(0);
}

QList<MyMeshingPoint*> MyMeshingPolygon::getPoints()
{
    return points_;
}

void MyMeshingPolygon::mesh()
{
    //Split in triangles
    triangles_.clear();
    split();

    //Split triangles
    while(1){
        bool ok = true;
        for(int i=0;i<triangles_.size();i++){
            if(!triangles_[i]->split())
                ok = false;
        }
        if(ok==true)
            break;
    }

    //Affine

}

bool MyMeshingPolygon::intersects(QPolygonF poly, QLineF line)
{
    for(int i=0;i<poly.size()-1;i++){
        QLineF l(poly.at(i) , poly.at(i+1));
        QPointF p;
        if(l.p1()==line.p1() || l.p1()==line.p2() || l.p2()==line.p1() || l.p2()==line.p2())
            continue;
        if(l.intersect(line,&p)==QLineF::BoundedIntersection){
                return true;
        }
    }
    return false;
}

bool MyMeshingPolygon::split()
{
    QPolygonF temp = poly_;

    int i = 0;
    for(;i<temp.size()-2;i++){
        QLineF l( temp[i], temp[i+2] );
        QPointF p = 0.5*l.p1() + 0.5*l.p2();
        if( temp.containsPoint(p,Qt::WindingFill) )
            continue;
        if( intersects(temp, l) )
            continue;
    }

    int i1,i2,i3;


    if(i==temp.size()-2){
        i1 = i;
        i2 = i+1;
        i3 = 0;
    }else{
        i1 = i;
        i2 = i+1;
        i2 = i+2;
    }

    MyMeshingPoint *p1,*p2,*p3;
    if(mapPoints_.contains(temp[i1])){
        p1 = mapPoints_[temp[i1]];
    }else{
        p1 = new MyMeshingPoint(temp[i1],MyMeshingPoint::FREE,QLineF());
    }
    if(mapPoints_.contains(temp[i2])){
        p2 = mapPoints_[temp[i2]];
    }else{
        p2 = new MyMeshingPoint(temp[i2],MyMeshingPoint::FREE,QLineF());
    }
    if(mapPoints_.contains(temp[i3])){
        p3 = mapPoints_[temp[i3]];
    }else{
        p3 = new MyMeshingPoint(temp[i3],MyMeshingPoint::FREE,QLineF());
    }

    MyMeshingTriangle *t = new MyMeshingTriangle(p1,p2,p3);
    triangles_.push_back(t);
}



void MyMeshingPolygon::setPoint(QPointF point)
{
    if(poly_.containsPoint(point,Qt::WindingFill)){
        constantPoints_.push_back(point);
    }else{
        qDebug() << "Invalid point" << point;
    }
}

void MyMeshingPolygon::setPoints(QList<QPointF> points)
{
    foreach(QPointF point, points){
        if(poly_.containsPoint(point,Qt::WindingFill)){
            constantPoints_.push_back(point);
        }else{
            qDebug() << "Invalid point" << point;
        }
    }
}

void MyMeshingPolygon::setEdge(QLineF edge)
{
    if(poly_.containsPoint(edge.p1(),Qt::WindingFill) && poly_.containsPoint(edge.p2(),Qt::WindingFill)){
        constantEdges_.push_back(edge);
    }else{
        qDebug() << "Invalid edge" << edge;
    }
}

void MyMeshingPolygon::setEdges(QList<QLineF> edges)
{
    foreach(QLineF edge, edges){
        if(poly_.containsPoint(edge.p1(),Qt::WindingFill) && poly_.containsPoint(edge.p2(),Qt::WindingFill)){
            constantEdges_.push_back(edge);
        }else{
            qDebug() << "Invalid edge" << edge;
        }
    }
}
