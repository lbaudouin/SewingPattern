#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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
    QList< QPolygonF > polys;
    PatternScene *scene;

    QList<QGraphicsPolygonItem*> polyDraw;

    QMenu *nodeMenu,*edgeMenu,*polyMenu,*linkMenu;
    QAction *deleteAction,*splitAction,*closeAction,*transformAction,*swapAction,*moveAction,*renameAction;


    QList<MyPattern*> patterns_;
    QList<MyLink*> links_;

    GLWidget *gl;

    QList<QGraphicsLineItem*> grids;

private slots:
    void pressTest();
    void pressSimu();
    void pressSave();
    void pointMovedInScene(int patternID, int pointID, QPointF newPos);
    void enableGrid(bool state);
    void connectEdges();

    void actionSwap();
    void actionDelete();
    void actionRename();
    void actionSplit();
    void actionClose();
    void actionMove();
    void actionTransform();

signals:
    void pointMoved(int patternID, int pointID, QPointF newPos);
    void gridEnabled(bool state);
};

#endif // MAINWINDOW_H
