#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "point2d.h"
#include "edge.h"
#include "meshing/meshing.h"
#include "patternscene.h"
#include <QDebug>

#include "graphicsview.h"
#include "mypattern.h"
#include "mypolygon.h"
#include "mypoint.h"
#include "mylink.h"
#include "myedge.h"
#include "glwidget.h"
#include "engine.h"
#include "grid.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void loadFile(QString filename);
    void saveFile(QString filename);
    
private:
    Ui::MainWindow *ui;
    QList<Point2D*> currentPoly;
    QList< QPolygonF > polys;
    PatternScene *scene;
    int n;
    QList<Point2D*> points;

    QList<Point2D*> allref;
    Point2D *ref;
    bool first;

    QList<QGraphicsPolygonItem*> polyDraw;

    QList<MyPoint*> allPoints_;
    QList<MyEdge*> allEdges_;
    QList<MyPoint*> listPoint;
    QMenu *nodeMenu,*edgeMenu,*polyMenu,*linkMenu;
    QAction *deleteAction,*splitAction,*closeAction,*transformAction,*swapAction,*moveAction,*renameAction;


    QList<MyPattern*> patterns_;
    QList< QPair<MyEdge*,MyEdge*> > link_;

    QList<MyPolygon*> polygons_;

    GLWidget *gl;

    QList<QGraphicsLineItem*> grids;

private slots:
    void pressTest();
    void pressSimu();
    void pressSave();
    MyPoint* addPoint(QPointF pt, int patternID, int pointID);
    void closePoly();
    void pointMovedInScene(int patternID, int pointID, QPointF newPos);
    void enableGrid(bool state);
    void connectEdges();

signals:
    void pointMoved(int patternID, int pointID, QPointF newPos);
    void gridEnabled(bool state);
};

#endif // MAINWINDOW_H
