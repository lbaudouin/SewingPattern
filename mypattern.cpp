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

QString MyPattern::getName()
{
    return name_;
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

QString MyPattern::getText()
{
    QString text;
    text +=  QString("PATTERN %1 %2\n").arg(QString::number(id_),name_);
    QList<int> ids = points_.keys();
    for(int i=0;i<ids.size();i++){
        text +=  QString("POINT %1 %2 %3\n").arg(QString::number(ids.at(i)),QString::number( points_[ids.at(i)].x()),QString::number(points_[ids.at(i)].y()));
    }
    ids = edges_.keys();
    for(int i=0;i<ids.size();i++){
        text +=  QString("EDGE %1 %2 %3\n").arg(QString::number(ids.at(i)),QString::number( edges_[ids.at(i)].first),QString::number(edges_[ids.at(i)].second));
    }
    ids = curves_.keys();
    for(int i=0;i<ids.size();i++){
        int id = ids.at(i);
        text +=  QString("CURVE %1").arg(QString::number(id));
        for(int j=0;j<curves_[id].size();j++)
            text +=  QString(" %1").arg(QString::number(curves_[id].at(j)));
        text += "\n";
    }
    return text;
}

void MyPattern::setPoint(int id, MyPoint *point)
{
    refPoints_.insert(id,point);
    //qDebug() << "Add point " << id;
}

QList<MyEdge*> MyPattern::getEdges(QMenu *menu)
{
    QList<QPair<int,int> > edges = edges_.values();
    for(int i=0;i<edges.size();i++){
        if(!refPoints_.contains(edges[i].first)) qDebug() << "Point " << edges[i].first << " not existing";
        if(!refPoints_.contains(edges[i].second)) qDebug() << "Point " << edges[i].second << " not existing";
        MyEdge* e = new MyEdge(refPoints_[edges[i].first],refPoints_[edges[i].second],menu);
    }
}
