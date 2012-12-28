#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPushButton *button = new QPushButton("Toto");
    ui->mainToolBar->addWidget(button);

    QGraphicsScene *scene = new QGraphicsScene(ui->graphicsView);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(-200, -200, 400, 400);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    Point2D *p2d_1 = new Point2D(ui->graphicsView);
    Point2D *p2d_2 = new Point2D(ui->graphicsView);
    Point2D *p2d_3 = new Point2D(ui->graphicsView);
    Point2D *p2d_4 = new Point2D(ui->graphicsView);
    Point2D *p2d_5 = new Point2D(ui->graphicsView);
    Point2D *p2d_6 = new Point2D(ui->graphicsView);
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

    p2d_1->setPos(0, 0);
    p2d_2->setPos(-100, -50);
    p2d_3->setPos(-100, 100);
    p2d_4->setPos(-50, 100);
    p2d_5->setPos(-50, 35);
    p2d_6->setPos(0, 25);
}

MainWindow::~MainWindow()
{
    delete ui;
}
