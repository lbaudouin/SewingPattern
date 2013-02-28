#ifndef MYPATTERN_H
#define MYPATTERN_H

#include <QPolygonF>
#include <QMap>
#include <QPair>
#include <QTextStream>
#include <QDebug>
#include <QObject>

class MyPattern;

#include "mypoint.h"
#include "myedge.h"
#include "mycurve.h"
#include "mypolygon.h"

class MyPattern : public QObject
{
    Q_OBJECT
public:
    MyPattern(int id, QString name);
    bool isValid();

    void display(QGraphicsScene *scene);

    void addPoint(MyPoint* p) { points_.push_back(p); }
    void addEdge(MyEdge* e) { edges_.push_back(e); }

    void addPoint(int id, QPointF pt);
    void addEdge(int id, int startID, int endID);
    void addCurve(int id, QList<int> points);

    MyPolygon* getPoly();
    QPolygonF getPolygon();

    QString getText();

    void setPolygon(MyPolygon* poly) { poly_ = poly; }

    QList<QPointF> getPoints();

    QList<MyEdge*> getEdgesList();
    QList<MyPoint*> getPointsList();
    MyEdge* getEdge(int id);
    MyPoint* getPoint(int id);

    inline friend QTextStream& operator<< (QTextStream& os, const MyPattern& pattern)
    {
        /*os << "PATTERN " << pattern.id_ << " " << pattern.name_ << "\n";
        QMap<int,QPointF> points = pattern.points_;
        QList<int> ids = points.keys();
        for(int i=0;i<ids.size();i++){
            os << "POINT " << ids.at(i) << " " << points[ids.at(i)].x() << " " << points[ids.at(i)].y() << "\n";
        }
        QMap<int,QPair<int,int> > edges = pattern.edges_;
        ids = edges.keys();
        for(int i=0;i<ids.size();i++){
            os << "EDGE " << ids.at(i) << " " << edges[ids.at(i)].first << " " << edges[ids.at(i)].second << "\n";
        }
        QMap<int,QList<int> > curves = pattern.curves_;
        ids = curves.keys();
        for(int i=0;i<ids.size();i++){
            int id = ids.at(i);
            os << "CURVE " << id;
            for(int j=0;j<curves[id].size();j++)
                os << " " << curves[id].at(j);
            os << "\n";
        }*/
        return os;
    }

    int getID() {return id_;}
    QString getName();
    void setName(QString name) {name_ = name;}

private:
    int id_;
    QString name_;

    QList<MyPoint*> points_;
    QList<MyEdge*> edges_;
    QList<MyCurve*> curves_;
    MyPolygon *poly_;

public slots:
};

#endif // MYPATTERN_H
