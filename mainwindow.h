#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "point2d.h"
#include "edge.h"
#include "meshing.h"
#include "patternscene.h"
#include <QDebug>

#include "graphicsview.h"
#include "mypattern.h"
#include "mypolygon.h"
#include "mypoint.h"
#include "myedge.h"
#include "glwidget.h"

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
    QMenu *nodeMenu,*edgeMenu,*polyMenu;
    QAction *deleteAction,*splitAction,*closeAction,*transformAction;


    QList<MyPattern*> patterns_;

private slots:
    void pressTest();
    MyPoint* addPoint(QPointF pt, int patternID, int pointID);
    void closePoly();
    void pointMovedInScene(int patternID, int pointID, QPointF newPos);

signals:
    void pointMoved(int patternID, int pointID, QPointF newPos);
};

#endif // MAINWINDOW_H
