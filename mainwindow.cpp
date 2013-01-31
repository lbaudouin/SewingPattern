#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), first(true)
{
    ui->setupUi(this);
    this->setWindowState(Qt::WindowMaximized);
    {
        QPushButton *button = new QPushButton("New Polygon");
        connect(button,SIGNAL(clicked()),this,SLOT(closePoly()));
        ui->mainToolBar->addWidget(button);
    }

    gl = new GLWidget(0, 0);
    gl->setClearColor(QColor(225,255,255));
    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(gl);
    ui->tab_simu->setLayout(vlayout);

    scene = new PatternScene(ui->graphicsView);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(-1000, -1000, 2000, 2000);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    //ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);

    //scene->addPixmap( QPixmap("images/sample.png").scaledToWidth(640) )->setPos(-500,-500);

    Grid *grid = new Grid(scene);
    grid->hide();
    {
        QPushButton *button = new QPushButton("Grid");
        button->setCheckable(true);
        connect(button,SIGNAL(toggled(bool)),grid,SLOT(setVisible(bool)));
        connect(button,SIGNAL(toggled(bool)),this,SLOT(enableGrid(bool)));
        ui->mainToolBar->addWidget(button);
    }

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
    transformAction = new QAction("Transform",this);
    edgeMenu->addAction( transformAction );


    polyMenu = new QMenu(this);
    polyMenu->addAction( deleteAction );
    closeAction = new QAction("Close Polygon",this);
    polyMenu->addAction( closeAction );


    connect(ui->buttonTest,SIGNAL(clicked()),this,SLOT(pressTest()));
    connect(ui->button3D,SIGNAL(clicked()),this,SLOT(pressSimu()));
    connect(ui->buttonSave,SIGNAL(clicked()),this,SLOT(pressSave()));
    //connect(scene,SIGNAL(middleClicked(QPointF)),this,SLOT(addPoint(QPointF)));

   /* MyPattern p(0,"Test pattern");
    p.addPoint(0,QPointF(0,0));
    p.addPoint(1,QPointF(100,0));
    p.addPoint(2,QPointF(100,100));
    p.addPoint(3,QPointF(0,100));
    patterns_.push_back(p);

    saveFile("test.txt");*/

    loadFile("test.txt");

    QList<QColor> colors;
    colors << Qt::blue << Qt::green << Qt::yellow << Qt::magenta << Qt::gray << Qt::cyan << Qt::red << Qt::black;

    /*black, white, darkGray, gray, lightGray,
    red, green, blue, cyan, magenta, yellow,
    darkRed, darkGreen, darkBlue, darkCyan, darkMagenta, darkYellow*/

    //foreach(MyPattern pattern, patterns_){
    for(int i=0;i<patterns_.size();i++){
        MyPattern *pattern = patterns_.at(i);
        MyPolygon *p = new MyPolygon(pattern,polyMenu);
        p->setColor(colors.at(i%colors.size()));
        polygons_ << p;
        scene->addItem(p);
        QMap<int,QPointF> pts = pattern->getPoints();
        QList<int> keys = pts.keys();
        for(int j=0;j<keys.size();j++){
            int key = keys.at(j);
            MyPoint * pt = new MyPoint(pts[key],p,pattern->id_,key,nodeMenu);
            connect(pt->widget,SIGNAL(moved(int,int,QPointF)),this,SLOT(pointMovedInScene(int,int,QPointF)));
            connect(this,SIGNAL(gridEnabled(bool)),pt->widget,SLOT(setUseGrid(bool)));
            pattern->setPoint(key,pt);
            scene->addItem(pt);
            //allPoints_ << addPoint(pts[keys.at(i)],pattern->id_,keys.at(i));
        }
        QList<MyEdge*> edges = pattern->getEdgesList(edgeMenu);
        //qDebug() << "Add " << edges.size() << " edges";
        for(int j=0;j<edges.size();j++){
        //foreach(MyEdge* e, edges){
            scene->addItem(edges[j]);
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

MyPoint* MainWindow::addPoint(QPointF pt, int patternID, int pointID)
{
    MyPoint *p = new MyPoint(pt,polygons_[0],patternID,pointID,nodeMenu);
    connect(p->widget,SIGNAL(moved(int,int,QPointF)),this,SLOT(pointMovedInScene(int,int,QPointF)));
    scene->addItem(p);

    /*if(!listPoint.isEmpty()){
        MyPoint *p2 = listPoint.at(listPoint.size()-1);
        MyEdge *e = new MyEdge(p,p2,edgeMenu);
        scene->addItem(e);
    }*/

    listPoint.push_back(p);

    return p;
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
                    name += " " + items.at(i);
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

void MainWindow::pressSave()
{
    saveFile("test.txt");
}

void MainWindow::saveFile(QString filename)
{
    QFile file(filename);
    file.open(QFile::WriteOnly);
    QTextStream out(&file);
    for(int i=0;i<patterns_.size();i++)
        out << patterns_.at(i)->getText();
    file.close();
}

void MainWindow::pointMovedInScene(int patternID, int pointID, QPointF newPos)
{
    emit this->pointMoved(patternID,pointID,newPos);
}

void MainWindow::pressSimu()
{
    QVector<QVector3D> vertices;
    QVector<QVector2D> texCoords;
    QList<QPolygon3F> polys;
    QStringList textures;
    textures << "images/chanvre.jpg";

    for(int k=0;k<patterns_.size();k++){
        Meshing mesh(patterns_[k]->getPolygon(),25.0);
        QList<QPolygonF> ps = mesh.getMesh();

        QList<QPointF> pts;// = patterns_.at(0)->getPoints().values();
        foreach(QPolygonF p, ps){
            //qDebug() << p.size();
            double a1 = QLineF(p.at(0),p.at(1)).angle() - QLineF(p.at(1),p.at(2)).angle();
            //if(a1>=0)
                pts << p.at(0) << p.at(1) << p.at(2);
            //else
            //    pts << p.at(0) << p.at(2) << p.at(1);
        }

        for(int i=0;i<pts.size();i++)
            vertices << 0.002*QVector3D(pts.at(i).x(),pts.at(i).y(),0.0);
        for(int i=0;i<pts.size();i++)
            texCoords << 0.01*QVector2D(pts.at(i).x(),pts.at(i).y());
        QPolygon3F poly;
        pts = patterns_.at(k)->getPoints().values();
        for(int i=0;i<pts.size();i++)
            poly << 0.002*QVector3D(pts.at(i).x(),pts.at(i).y(),0.0);
        polys << poly;
    }
#if 0
    gl->clearTextures();
    gl->clearTextureCoords();
    gl->clearVertices();
#else
    gl->setVertices(vertices);
    gl->setTextures(textures);
    gl->setTextureCoords(texCoords);
#endif
    gl->setPolygons(polys);
    gl->updateGL();

    ui->tabWidget->setCurrentIndex(2);
}

void MainWindow::enableGrid(bool state)
{
    emit this->gridEnabled(state);
}
