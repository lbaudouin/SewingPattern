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

    void addPoint(MyPoint* p);
    void addEdge(MyEdge* e);
    void removePoint(MyPoint* p);
    void removeEdge(MyEdge* e);

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

    int getID() {return id_;}
    QString getName();
    void setName(QString name) {name_ = name;}

    int getEmptyPointID();
    int getEmptyEdgeID();

    void setOrientation(double orientation) { orientation_ = orientation; }
    double getOrientation() { return orientation_; }

    void hidePoints();
    void showPoints();

    void setPointsVisible(bool visible = true);

private:
    int id_;
    QString name_;

    QMap<int,MyPoint*> pointsMap_;
    QMap<int,MyEdge*> edgesMap_;
    QMap<int,MyCurve*> curvesMap_;
    MyPolygon *poly_;

    double orientation_;

public slots:
};

#endif // MYPATTERN_H
