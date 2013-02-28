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
    for(int i=0;i<points_.size();i++){
        text +=  QString("POINT %1 %2 %3\n").arg(QString::number(i),QString::number( points_[i]->getPoint().x()),QString::number(points_[i]->getPoint().y()));
    }
    for(int i=0;i<edges_.size();i++){
        text +=  QString("EDGE %1 %2 %3\n").arg(QString::number(i),QString::number( edges_[i]->getSource()->getID()),QString::number(edges_[i]->getDest()->getID()));
    }
    for(int i=0;i<curves_.size();i++){
        text +=  QString("CURVE %1").arg(QString::number(i));
        for(int j=0;j<curves_[i]->size();j++)
            text +=  QString(" %1").arg(QString::number(curves_[i]->getPoint(j)->getID()));
        text += "\n";
    }
    if(poly_){
        text +=  QString("POLYGON");
        for(int i=0;i<poly_->size();i++)
            text +=  QString(" %1").arg(QString::number(poly_->getPoint(i)->getID()));
    }
    text += "\n";
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
