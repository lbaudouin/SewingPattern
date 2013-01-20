#ifndef TOOLS_H
#define TOOLS_H

#include <QPolygonF>
#include <QList>

class PlacedPolygon{
public:
    PlacedPolygon() : forceAngle(false), angle(0.0), x(0.0), y(0.0) {}
    QPolygonF poly;
    bool forceAngle;
    double angle;
    double x,y;
};

class Tools
{
public:
    Tools();

    bool placePolygon(QPolygonF polyIn, QList<PlacedPolygon> &parts);
};

#endif // TOOLS_H
