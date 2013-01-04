#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPushButton *button = new QPushButton("New Polygon");
    connect(button,SIGNAL(clicked()),this,SLOT(closePoly()));
    ui->mainToolBar->addWidget(button);

    scene = new PatternScene(ui->graphicsView);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(-200, -200, 400, 400);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    /*p2d_1 = new Point2D(ui->graphicsView,0);
    p2d_2 = new Point2D(ui->graphicsView,1);
    p2d_3 = new Point2D(ui->graphicsView,2);
    p2d_4 = new Point2D(ui->graphicsView,3);
    p2d_5 = new Point2D(ui->graphicsView,4);
    p2d_6 = new Point2D(ui->graphicsView,5);

    scene->addItem(p2d_1);
    scene->addItem(p2d_2);
    scene->addItem(p2d_3);
    scene->addItem(p2d_4);
    scene->addItem(p2d_5);
    scene->addItem(p2d_6);

    scene->addItem( new Edge(p2d_1,p2d_2) );
    scene->addItem( new Edge(p2d_2,p2d_3) );
    scene->addItem( new Edge(p2d_3,p2d_4) );
    scene->addItem( new Edge(p2d_4,p2d_5) );
    scene->addItem( new Edge(p2d_5,p2d_6) );
    scene->addItem( new Edge(p2d_6,p2d_1) );

    /*p2d_1->setPos(0, 0);
    p2d_2->setPos(-100, -50);
    p2d_3->setPos(-100, 100);
    p2d_4->setPos(-50, 100);
    p2d_5->setPos(-50, 35);
    p2d_6->setPos(0, 25);

    /*connect(p2d_1->widget,SIGNAL(moved()),this,SLOT(pressTest()));
    connect(p2d_2->widget,SIGNAL(moved()),this,SLOT(pressTest()));
    connect(p2d_3->widget,SIGNAL(moved()),this,SLOT(pressTest()));
    connect(p2d_4->widget,SIGNAL(moved()),this,SLOT(pressTest()));
    connect(p2d_5->widget,SIGNAL(moved()),this,SLOT(pressTest()));
    connect(p2d_6->widget,SIGNAL(moved()),this,SLOT(pressTest()));


    /*p2d_1->setPos(0, 0);
    p2d_2->setPos(-100, -100);
    p2d_3->setPos(-150, -50);
    p2d_4->setPos(-75, 50);
    p2d_5->setPos(-50, 100);
    p2d_6->setPos(-25, 50);*/



    n = 1;

    /*p2d_1->setPos(1000, 1000);
    p2d_2->setPos(1000, 1000);
    p2d_3->setPos(1000, 1000);
    p2d_4->setPos(1000, 1000);
    p2d_5->setPos(1000, 1000);
    p2d_6->setPos(1000, 1000);*/
    connect(ui->buttonTest,SIGNAL(clicked()),this,SLOT(pressTest()));
    connect(scene,SIGNAL(middleClicked(QPointF)),this,SLOT(addPoint(QPointF)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::pressTest()
{
    for(int i=0;i<polyDraw.size();i++)
        scene->removeItem(polyDraw.at(i));
    polyDraw.clear();

    for(int k=0;k<polys.size();k++){
        QPolygonF poly;
        for(int i=0;i<polys.at(k).size();i++)
            poly << polys.at(k).at(i)->pos();

        Meshing mesh(poly,25.0);
        QList<QPolygonF> triangles = mesh.getMesh();

        for(int i=0;i<triangles.size();i++){
            polyDraw << scene->addPolygon(triangles.at(i),QPen(QColor(rand()%200,rand()%200,rand()%200)));
        }
    }
}

void MainWindow::addPoint(QPointF pt)
{
    Point2D *p = new Point2D(ui->graphicsView,points.size());
    points << p;
    currentPoly.push_back(p);
    scene->addItem(p);
    if(currentPoly.size()>1)
        scene->addItem( new Edge(currentPoly.at(currentPoly.size()-2),p,ui->graphicsView) );
    p->setPos(pt);
}

void MainWindow::closePoly()
{
    if(currentPoly.size()<=2)
        return;
    polys << currentPoly;
    scene->addItem( new Edge(currentPoly.at(0),currentPoly.at(currentPoly.size()-1),ui->graphicsView) );
    currentPoly.clear();
}
