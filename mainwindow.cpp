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

   /* MyPattern p(0,"Test pattern");
    p.addPoint(0,QPointF(0,0));
    p.addPoint(1,QPointF(100,0));
    p.addPoint(2,QPointF(100,100));
    p.addPoint(3,QPointF(0,100));
    patterns_.push_back(p);

    saveFile("test.txt");*/

    loadFile("test.txt");

    //foreach(MyPattern pattern, patterns_){
    for(int i=0;i<patterns_.size();i++){
        MyPattern *pattern = patterns_.at(i);
        QMap<int,QPointF> pts = pattern->getPoints();
        QList<int> keys = pts.keys();
        for(int i=0;i<keys.size();i++)
            allPoints_ << addPoint(pts[keys.at(i)],pattern->id_,keys.at(i));
        for(int i=0;i<edges.size();i++){
            MyPoint *p1;
            MyPoint *p2;
            allEdges_ << new MyEdge(p1,p2,edgeMenu);
        }
    }
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
    //for(int i=0;i<allref.size();i++)
    //    polys << allref.at(i)->getPoly();

    for(int i=0;i<patterns_.size();i++){
        polys << patterns_[i]->getPolygon();
    }

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

void MainWindow::addPoint(QPointF pt, int patternID, int pointID)
{
    MyPoint *p = new MyPoint(pt,patternID,pointID,nodeMenu);
    connect(p->widget,SIGNAL(moved(int,int,QPointF)),this,SLOT(pointMovedInScene(int,int,QPointF)));
    scene->addItem(p);

    /*if(!listPoint.isEmpty()){
        MyPoint *p2 = listPoint.at(listPoint.size()-1);
        MyEdge *e = new MyEdge(p,p2,edgeMenu);
        scene->addItem(e);
    }*/

    listPoint.push_back(p);

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

        patterns_.clear();
        MyPattern* pattern = new MyPattern(-1,"");

        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            if(line.isEmpty())
                continue;
            QStringList items = line.split(" ");

            if(items.at(0)=="PATTERN"){
                int id = items.at(1).toInt();
                QString name;
                for(int i=2;i<items.size();i++){
                    name += items.at(i);
                }
                name = name.trimmed();
                if(pattern->isValid())
                    patterns_.push_back(pattern);
                pattern = new MyPattern(id,name);
            }else
            if(items.at(0)=="POINT"){
                if(!pattern->isValid()){
                    QMessageBox::critical(this,tr("Error"),tr("Invalid pattern on loading"));
                    return;
                }
                int id = items.at(1).toInt();
                QPointF point;
                point.setX( items.at(2).toDouble() );
                point.setY( items.at(3).toDouble() );
                pattern->addPoint(id,point);
            }else
            if(items.at(0)=="EDGE"){
                if(!pattern->isValid()){
                    QMessageBox::critical(this,tr("Error"),tr("Invalid pattern on loading"));
                    return;
                }
                int id = items.at(1).toInt();
                int startID =  items.at(2).toInt();
                int endID =  items.at(3).toInt();
                pattern->addEdge(id,startID,endID);
            }else
            if(items.at(0)=="CURVE"){
                if(!pattern->isValid()){
                    QMessageBox::critical(this,tr("Error"),tr("Invalid pattern on loading"));
                    return;
                }
                int id = items.at(1).toInt();
                QList<int> list;
                for(int i=2;i<items.size();i++)
                    list << items.at(i).toInt();
                pattern->addCurve(id,list);
            }
        }

        if(pattern->isValid())
            patterns_.push_back(pattern);

        for(int i=0;i<patterns_.size();i++)
            connect(this,SIGNAL(pointMoved(int,int,QPointF)),patterns_[i],SLOT(pointMoved(int,int,QPointF)));
    }else{
        qDebug() << "Error on file loading";
    }
}

void MainWindow::saveFile(QString filename)
{
    QFile file(filename);
    file.open(QFile::WriteOnly);
    QTextStream out(&file);
    for(int i=0;i<patterns_.size();i++)
        out << patterns_.at(i);
    file.close();
}

void MainWindow::pointMovedInScene(int patternID, int pointID, QPointF newPos)
{
    emit this->pointMoved(patternID,pointID,newPos);
}
