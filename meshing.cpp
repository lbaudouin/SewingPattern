#include "meshing.h"
#include "point2d.h"

Meshing::Meshing(QPolygonF polyIn, double dist, QList<QPolygonF> polyOut) : original_(polyIn)
{
    if(polyIn.isEmpty())
        return;

    if(!polyIn.isClosed())
        polyIn << polyIn.at(0);

    //Test poly
    for(int i=0;i<polyIn.size()-1;i++){
        QLineF line(polyIn.at(i),polyIn.at(i+1));
        if(intersects(polyIn,line)){
            qDebug() << "Invalid polygon";
            return;
        }
    }

    mesh_.clear();
    mesh_.push_back(polyIn);

    //qDebug();
    splitDiag();

    //int id = findBiggestPoly();
    //QPointF p = addMiddlePoint(id);

    double length = 0.0;
    do{
        QLineF l = findLongestLine();
        length = l.length();
        cutLine(l);
    }while(length>dist);

}

Meshing::Meshing(QPolygonF polyIn, int iter, QGraphicsView *graphicsView, QGraphicsScene *scene)
{
    mesh_.clear();
    mesh_.push_back(polyIn);

    int id = findBiggestPoly();
    QPointF p = addMiddlePoint(id);

    for(int i=0;i<iter;i++){
        //qDebug() << "\n iter nb " << i;
        //int id = findBiggestPoly();
        //QPointF p = addMiddlePoint(id);
        //Point2D *pt = new Point2D(graphicsView);
        //scene->addItem(pt);
        //pt->setPos(p);
        QLineF l = findLongestLine();
        //QPointF p =
        cutLine(l);
        //Point2D *pt = new Point2D(graphicsView);
        //scene->addItem(pt);
        //pt->setPos(p);

        refine();
    }

}

void Meshing::addPoint(QPointF point)
{

}

int Meshing::findBiggestPoly()
{
    if(mesh_.size()==1) return 0;
    double area = computeArea(mesh_.at(0));
    int id = 0;
    for(int i=1;i<mesh_.size();i++){
        double a = computeArea(mesh_.at(i));
        if(a>area){
            id = i;
            area = a;
        }
    }
    return id;
}

double Meshing::computeArea(QPolygonF poly)
{
    if(poly.size()<3) return 0.0;
    double a = QLineF(poly.at(0),poly.at(1)).length();
    double b = QLineF(poly.at(1),poly.at(2)).length();
    double c = QLineF(poly.at(2),poly.at(0)).length();
    double s = (a+b+c)/2;

    return sqrt(s*(s-a)*(s-b)*(s-c));
}

QPointF Meshing::addMiddlePoint(int id)
{
    QPointF point(0,0);
    QPolygonF poly = mesh_.at(id);
    if(poly.isEmpty())
        return point;

    if(!poly.isClosed())
        poly << poly.at(0);

    mesh_.removeAt(id);

    for(int i=0;i<poly.size()-1;i++)
        point += poly.at(i);
    point /= (double)(poly.size()-1);

    /*while(!poly.containsPoint(point,Qt::WindingFill)){
        point += QPointF(-50+rand()%100,-50+rand()%100);
    }*/

    for(int i=0;i<poly.size()-1;i++){
        QPolygonF p;
        p << poly.at(i) << poly.at(i+1) << point << poly.at(i);
        mesh_.push_back(p);
    }
    return point;
}

bool Meshing::intersects(QPolygonF poly, QLineF line)
{
    for(int i=0;i<poly.size()-1;i++){
        QLineF l(poly.at(i) , poly.at(i+1));
        QPointF p;
        if(l.p1()==line.p1() || l.p1()==line.p2() || l.p2()==line.p1() || l.p2()==line.p2())
            continue;
        if(l.intersect(line,&p)==QLineF::BoundedIntersection){
                return true;
        }
    }
    return false;
}

void Meshing::splitDiag()
{
    for(int id=0;id<mesh_.size();id++){
        QPolygonF poly = mesh_.at(id);
        if(poly.isEmpty())
            continue;

        if(!poly.isClosed())
            poly << poly.at(0);

        if(poly.size()<=4)
            continue;

        QStringList polyID;
        for(int k=0;k<poly.size();k++)
            polyID << findID(poly.at(k));

        /*for(int i=0;i<poly.size()-2;i++){
            QPointF p = (poly.at(i) + poly.at(i+2))/2.0;
            if(poly.containsPoint(p,Qt::WindingFill)){
                QPolygonF p1,p2;
                for(int k=i;k<i+3;k++){
                    p1 << poly.at(k);
                }
                p1 << poly.at(i);
                for(int k=i+3;k<=poly.size()-1;k++){
                    p2 << poly.at(k);
                }
                for(int k=0;k<i;k++){
                    p2 << poly.at(k);
                }
                p2 << poly.at(i);
                mesh_.push_back(p1);
                mesh_.push_back(p2);
                mesh_.removeAt(id);
                splitDiag();
                return;
            }
        }*/

        //qDebug() << "Split poly" << polyID;
        for(int i=0;i<poly.size()-1;i++){
            for(int j=i+2;j<poly.size()-(i==0?2:1);j++){
                //qDebug() << "Try to split along" << findID(poly.at(i)) << findID(poly.at(j));
                QLineF line(poly.at(i),poly.at(j));
                QPointF middle = (poly.at(i)+poly.at(j))/2.0;
                if(!poly.containsPoint(middle,Qt::WindingFill))
                    continue;
                if(!intersects(poly,line)){
                    QPolygonF p1,p2;
                    //QStringList poly1id,poly2id;

                    for(int k=i;k<=j;k++){
                        p1 << poly.at(k);
                        //poly1id << findID(poly.at(k));
                    }
                    p1 << poly.at(i);
                    //poly1id << findID(poly.at(i));
                    for(int k=j;k<poly.size()-1;k++){
                        p2 << poly.at(k);
                        //poly2id << findID(poly.at(k));
                    }
                    for(int k=0;k<=i;k++){
                        p2 << poly.at(k);
                        //poly2id << findID(poly.at(k));
                    }
                    p2 << poly.at(j);
                    //poly2id << findID(poly.at(j));
                    //qDebug() << poly.size() << QPair<int,QString>(i,findID(poly.at(i))) << QPair<int,QString>(j,findID(poly.at(j))) << p1.size() << p2.size();
                    //qDebug() << "Poly1" << poly1id;
                    //qDebug() << "Poly2" << poly2id;
                    mesh_.push_back(p1);
                    mesh_.push_back(p2);
                    mesh_.removeAt(id);
                    splitDiag();
                    return;
                }
            }
        }
        //qDebug() << "Can't split poly " << polyID;
    }
}

QLineF Meshing::findLongestLine()
{
    QLineF line;

    for(int i=0;i<mesh_.size();i++){
        if(mesh_.at(i).size()<2)
            continue;
        if(!mesh_.at(i).isClosed())
            mesh_[i] << mesh_.at(i).at(0);
        for(int j=0;j<mesh_.at(i).size()-1;j++){
            QLineF l(mesh_.at(i).at(j),mesh_.at(i).at(j+1));
            if(l.length()>line.length())
                line = l;
        }
    }

    return line;
}

QPointF Meshing::cutLine(QLineF line)
{
    QPointF point = (line.p1()+line.p2())/2.0;
    QList<int> removeID;
    for(int i=0;i<mesh_.size();i++){
        if(mesh_.at(i).size()<2)
            continue;
        if(!mesh_.at(i).isClosed())
            mesh_[i] << mesh_.at(i).at(0);

        for(int j=0;j<mesh_.at(i).size()-1;j++){
            QLineF l(mesh_.at(i).at(j),mesh_.at(i).at(j+1));
            if(line==l || (line.p1()==l.p2() && line.p2()==l.p1())){
                removeID << i;
                break;
            }
        }
    }

    for(int i=0;i<removeID.size();i++){
        int id = removeID.at(i);
        for(int j=0;j<mesh_.at(id).size()-1;j++){
            QLineF l(mesh_.at(id).at(j),mesh_.at(id).at(j+1));
            if(line!=l && !(line.p1()==l.p2() && line.p2()==l.p1())){
                QPolygonF poly;
                poly << mesh_.at(id).at(j) << mesh_.at(id).at(j+1) << point << mesh_.at(id).at(j);
                mesh_.push_back( poly );
            }
        }
    }

    //qDebug() << "Remove " << removeID.size() << " polygons";
    for(int i=removeID.size()-1;i>=0;i--)
        mesh_.removeAt(removeID.at(i));
    //qDebug() << " -> New size " << mesh_.size() << " polygons";

    return point;
}

void Meshing::refine()
{

}

QString Meshing::findID(QPointF pt)
{
    for(int i=0;i<original_.size();i++)
        if(original_.at(i)==pt)
            return QString::number(i);
    return "*";
}
