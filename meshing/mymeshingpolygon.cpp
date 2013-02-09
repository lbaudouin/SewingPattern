#include "mymeshingpolygon.h"


MyMeshingPolygon::MyMeshingPolygon(QPolygonF poly) : poly_(poly)
{
    if(poly_.isEmpty())
        return;

    if(!poly_.isClosed())
        poly_ << poly_.at(0);

    for(int i=0;i<poly_.size()-1;i++){
        points_ <<  new MyMeshingPoint(&points_,poly_.at(i));
    }
    for(int i=0;i<poly_.size()-2;i++){
        new MyMeshingEdge(points_.at(i),points_.at(i+1));
    }
    new MyMeshingEdge(points_.at(poly.size()-2),points_.at(0));
}

QList<MyMeshingPoint*> MyMeshingPolygon::getPoints()
{
    return points_;
}
