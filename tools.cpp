#include "tools.h"

Tools::Tools()
{
}

bool Tools::placePolygon(QPolygonF polyIn, QList<PlacedPolygon> &parts)
{
    QRectF boundingRect = polyIn.boundingRect();
    double x_incr = 0.1;
    double y_incr = 0.1;
    double t_incr = 1.0;
    for(int i=0;i<parts.size();i++){
        QPolygonF poly = parts[i].poly;
        if(polyIn.intersected(poly)==poly){
            //ok
        }
    }
}
