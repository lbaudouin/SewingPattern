#include "mypattern.h"

MyPattern::MyPattern(int id, QString name) : id_(id), name_(name), poly_(0)
{

}

bool MyPattern::isValid()
{
    return id_>=0;
}

QString MyPattern::getName()
{
    return name_;
}

MyPolygon*  MyPattern::getPoly()
{
    return poly_;
}

QPolygonF MyPattern::getPolygon()
{
    if(poly_)
        return poly_->getPolygon();
    else
        return QPolygonF();
}

QString MyPattern::getText()
{
    QString text;
    text +=  QString("PATTERN %1 %2\n").arg(QString::number(id_),name_);
    /*QList<int> ids = points_.keys();
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
    }*/
    return text;
}

MyEdge* MyPattern::getEdge(int id)
{
    if(id<edges_.size())
        return edges_.at(id);
    else
        return 0;
}

MyPoint* MyPattern::getPoint(int id)
{
    if(id<points_.size())
        return points_.at(id);
    else
        return 0;
}

QList<MyPoint*> MyPattern::getPointsList()
{
    return points_;
}

QList<MyEdge*> MyPattern::getEdgesList()
{
    return edges_;
}

void MyPattern::display(QGraphicsScene *scene)
{
    for(int i=0;i<points_.size();i++)
        if(points_.at(i))
            scene->addItem(points_.at(i));
    for(int i=0;i<edges_.size();i++)
        if(edges_.at(i))
            scene->addItem(edges_.at(i));
    if(poly_)
        scene->addItem(poly_);
}

QList<QPointF> MyPattern::getPoints()
{
    QPolygonF p = getPoly()->getPolygon();
    QList<QPointF> list;
    for(int i=0;i<p.size();i++)
        list << p.at(i);
    return list;
}
