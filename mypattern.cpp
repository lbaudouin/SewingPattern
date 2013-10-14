#include "mypattern.h"

MyPattern::MyPattern(int id, QString name) : id_(id), name_(name), poly_(0), orientation_(-1)
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
        return poly_->getPoly();
    else
        return QPolygonF();
}

QString MyPattern::getText()
{
    QString text;
    text +=  QString("PATTERN %1 %2\n").arg(QString::number(id_),name_);
    if(orientation_>=0)
        text +=  QString("ORIENTATION %\n").arg(QString::number(orientation_));

    foreach(MyPoint *p, pointsMap_.values()){
        text +=  QString("POINT %1 %2 %3\n").arg(QString::number(p->getID()),QString::number( p->getPoint().x()),QString::number(p->getPoint().y()));
    }
    foreach(MyEdge *e, edgesMap_.values()){
        text +=  QString("EDGE %1 %2 %3\n").arg(QString::number(e->getID()),QString::number( e->getSource()->getID()),QString::number(e->getDest()->getID()));
    }
    foreach(MyCurve *c, curvesMap_.values()){
        text +=  QString("CURVE %1").arg(QString::number(c->getID()));
        for(int j=0;j<c->size();j++)
            text +=  QString(" %1").arg(QString::number(c->getPoint(j)->getID()));
        text += "\n";
    }
    if(poly_){
        text +=  QString("POLYGON");
        for(int i=0;i<poly_->size();i++)
            text +=  QString(" %1").arg(QString::number(poly_->getPoint(i)->getID()));
        text += "\n";
    }
    text += "\n";
    return text;
}

int MyPattern::getEmptyPointID()
{
    int k=0;
    while(pointsMap_.contains(k)){
        k++;
    }
    return k;
}

int MyPattern::getEmptyEdgeID()
{
    int k=0;
    while(edgesMap_.contains(k)){
        k++;
    }
    return k;
}

void MyPattern::addPoint(MyPoint* p)
{
    pointsMap_.insert(p->getID(),p);
}

void MyPattern::addEdge(MyEdge* e)
{
    edgesMap_.insert(e->getID(),e);
}

void MyPattern::removePoint(MyPoint* p)
{
    pointsMap_.remove(p->getID());
}

void MyPattern::removeEdge(MyEdge* e)
{
    edgesMap_.remove(e->getID());
}

MyEdge* MyPattern::getEdge(int id)
{
    if(edgesMap_.contains(id)){
        return edgesMap_.value(id);
    }else{
        return 0;
    }
}

MyPoint* MyPattern::getPoint(int id)
{
    if(pointsMap_.contains(id)){
        return pointsMap_.value(id);
    }else{
        return 0;
    }
}

QList<MyPoint*> MyPattern::getPointsList()
{
    return pointsMap_.values();
}

QList<MyEdge*> MyPattern::getEdgesList()
{
    return edgesMap_.values();
}

void MyPattern::display(QGraphicsScene *scene)
{
    foreach(MyPoint *p, pointsMap_.values()){
        scene->addItem(p);
    }
    foreach(MyEdge *e, edgesMap_.values()){
        scene->addItem(e);
    }
    if(poly_)
        scene->addItem(poly_);
}

QList<QPointF> MyPattern::getPoints()
{
    QPolygonF p = getPoly()->getPoly();
    QList<QPointF> list;
    for(int i=0;i<p.size();i++)
        list << p.at(i);
    return list;
}

void MyPattern::hidePoints()
{
    QList<int> ids = pointsMap_.keys();
    foreach(int id, ids)
        pointsMap_[id]->hide();
}

void MyPattern::showPoints()
{
    QList<int> ids = pointsMap_.keys();
    foreach(int id, ids)
        pointsMap_[id]->show();
}

void MyPattern::setPointsVisible(bool visible)
{
    if(visible)
        showPoints();
    else
        hidePoints();
}
