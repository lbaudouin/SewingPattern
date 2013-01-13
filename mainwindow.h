#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "point2d.h"
#include "edge.h"
#include "meshing.h"
#include "patternscene.h"
#include <QDebug>

#include "mypolygon.h"
#include "mypoint.h"
#include "myedge.h"

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

    QMenu *nodeMenu,*edgeMenu;
    QAction *deleteAction,*splitAction;

private slots:
    void pressTest();
    void addPoint(QPointF pt);
    void closePoly();
};

#endif // MAINWINDOW_H
