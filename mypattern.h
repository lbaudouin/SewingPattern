#ifndef MYPATTERN_H
#define MYPATTERN_H

#include <QPolygonF>
#include <QMap>
#include <QPair>
#include <QTextStream>
#include <QDebug>
#include <QObject>

class MyPattern : public QObject
{
    Q_OBJECT
public:
    MyPattern(int id, QString name);
    bool isEmpty();
    bool isValid();

    void addPoint(int id, QPointF pt);
    void addEdge(int id, int startID, int endID);
    void addCurve(int id, QList<int> points);

    QPolygonF getPolygon();

    inline QMap<int,QPointF> getPoints(){return points_;}
    inline QMap<int,QPair<int,int> > getEdges(){return edges_;}
    inline QMap<int,QList<int> > getCurves(){return curves_;}

    inline friend QTextStream& operator<< (QTextStream& os, const MyPattern& pattern)
    {
        os << "PATTERN " << pattern.id_ << " " << pattern.name_ << "\n";
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
        }
        return os;
    }
    /*std::ostream& operator<< (std::ostream& os)
    {
        os << "PATTERN " << this->id_ << " " << this->name_ << std::endl;
        QList<int> ids = points_.keys();
        for(int i=0;i<ids.size();i++){
            os << "POINT " << ids.at(i) << " " << points_[ids.at(i)].x() << " " << points_[ids.at(i)].y() << std::endl;
        }
        ids = edges_.keys();
        for(int i=0;i<ids.size();i++){
            os << "EDGE " << ids.at(i) << " " << edges_[ids.at(i)].first << " " << edges_[ids.at(i)].second << std::endl;
        }
        ids = curves_.keys();
        for(int i=0;i<ids.size();i++){
            int id = ids.at(i);
            os << "CURVE " << id;
            for(int j=0;j<curves_[id].size();j++)
                os << " " << curves_[id].at(j);
            os << std::endl;
        }
        return os;
    }*/

    int id_;
    QString name_;
    QMap<int,QPointF> points_;
    QMap<int,QPair<int,int> > edges_;
    QMap<int,QList<int> > curves_;
private:

public slots:
    void pointMoved(int patternID, int pointID, QPointF newPos);
};

#endif // MYPATTERN_H
