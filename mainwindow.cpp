#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), first(true)
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


    nodeMenu = new QMenu(this);
    deleteAction = new QAction("Delete",this);
    deleteAction->setShortcut(tr("Delete"));
    deleteAction->setStatusTip(tr("Delete item from diagram"));
    //connect(deleteAction, SIGNAL(triggered()), this, SLOT(deleteItem()));
    nodeMenu->addAction( deleteAction );

    edgeMenu = new QMenu(this);
    edgeMenu->addAction( deleteAction );
    splitAction = new QAction("Split",this);
    //splitAction->setShortcut(tr("Split"));
    splitAction->setStatusTip(tr("Split edge here"));
    //connect(splitAction, SIGNAL(triggered()), this, SLOT(deleteItem()));
    edgeMenu->addAction( splitAction );

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

    polys.clear();
    for(int i=0;i<allref.size();i++)
        polys << allref.at(i)->getPoly();

    for(int k=0;k<polys.size();k++){
        /*QPolygonF poly;
        for(int i=0;i<polys.at(k).size();i++)
            poly << polys.at(k).at(i)->pos();*/

        Meshing mesh(polys.at(k),25.0);
        QList<QPolygonF> triangles = mesh.getMesh();

        for(int i=0;i<triangles.size();i++){
            polyDraw << scene->addPolygon(triangles.at(i),QPen(QColor(rand()%200,rand()%200,rand()%200)));
        }
    }
}

void MainWindow::addPoint(QPointF pt)
{
    MyPoint *p = new MyPoint(nodeMenu,pt);
    scene->addItem(p);
    MyPoint *p2 = new MyPoint(nodeMenu,pt+QPointF(200,200));
    scene->addItem(p2);
    MyEdge *e = new MyEdge(p,p2,edgeMenu);
    scene->addItem(e);

    /*
    if(first){
        ref = new Point2D(ui->graphicsView,0);
        ref->setPos(pt);
        scene->addItem(ref);
        first = false;
        allref << ref;
    }else{
        ref->addPoint(pt);
    }*/
    /*Point2D *p = new Point2D(ui->graphicsView,points.size());
    points << p;
    currentPoly.push_back(p);
    scene->addItem(p);
    if(currentPoly.size()>1)
        scene->addItem( new Edge(currentPoly.at(currentPoly.size()-2),p,ui->graphicsView) );
    p->setPos(pt);*/
}

void MainWindow::closePoly()
{
    if(first)
        return;
    scene->addItem( new Edge(ref,ref->getLast(),ui->graphicsView) );
    first = true;
}

void MainWindow::loadFile(QString filename)
{
    QFile file(filename);
    if(file.open(QFile::ReadOnly)){
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            if(line.isEmpty())
                continue;
            QStringList items = line.split(" ");

            if(items.at(0)=="POLYGON"){
                QString name;
                for(int i=1;i<items.size();i++){
                    name += items.at(i);
                }
                name = name.trimmed();
            }
            if(items.at(0)=="POINT"){
                QPointF point;
                point.setX( items.at(1).toDouble() );
                point.setY( items.at(2).toDouble() );
            }
        }
    }else{
        qDebug() << "Error on file loading";
    }
}

void MainWindow::saveFile(QString filename)
{

}
