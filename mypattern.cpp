#include "mypattern.h"

MyPattern::MyPattern(int id, QString name) : id_(id), name_(name)
{
}

void MyPattern::addPoint(int id, QPointF pt)
{
    points_.insert(id,pt);
}

void MyPattern::addEdge(int id, int startID, int endID)
{
    edges_.insert(id, QPair<int,int>(startID,endID));
}

void MyPattern::addCurve(int id, QList<int> points)
{
    curves_.insert(id,points);
}

bool MyPattern::isEmpty()
{
    return points_.isEmpty();
}

bool MyPattern::isValid()
{
    return id_>=0;
}

QPolygonF MyPattern::getPolygon()
{
    QPolygonF poly;
    QList<QPair<int,int> > edges = edges_.values();
    QList<QList<int> > curves = curves_.values();


    int first = -1;
    if(edges.size()>0){
        first = edges.at(0).first;
    }else
    if(curves.size()>0){
        first = curves.at(0).first();

    }else{
        return poly;
    }
    poly << points_[first];

    while(edges.size()!=0 || curves.size()!=0){
        for(int i=0;i<edges.size();i++){
            if(edges.at(i).first==first){
                first = edges.at(i).second;
                poly << points_[first];
                edges.removeAt(i);
                break;
            }
        }
        for(int i=0;i<curves.size();i++){
            if(curves.at(i).first()==first){
                first = curves.at(i).last();
                poly << points_[first];
                curves.removeAt(i);
                break;
            }
        }
    }
    return poly;
}

void MyPattern::pointMoved(int patternID, int pointID, QPointF newPos)
{
    if(patternID!=id_)
        return;
    if(points_.contains(pointID))
        points_[pointID] = newPos;
}
