#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowState(Qt::WindowMaximized);
    {
        QPushButton *button = new QPushButton("New Polygon");
        ui->mainToolBar->addWidget(button);
    }
    {
        QPushButton *button = new QPushButton("Connect");
        connect(button,SIGNAL(clicked()),this,SLOT(connectEdges()));
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

    deleteAction = new QAction("Delete",this);
    connect(deleteAction,SIGNAL(triggered()),this,SLOT(actionDelete()));
    splitAction = new QAction("Split",this);
    connect(splitAction,SIGNAL(triggered()),this,SLOT(actionSplit()));
    transformAction = new QAction("Transform",this);
    transformAction->setEnabled(false);
    connect(transformAction,SIGNAL(triggered()),this,SLOT(actionTransform()));
    closeAction = new QAction("Close Polygon",this);
    closeAction->setEnabled(false);
    connect(closeAction,SIGNAL(triggered()),this,SLOT(actionClose()));
    swapAction = new QAction("Swap",this);
    connect(swapAction,SIGNAL(triggered()),this,SLOT(actionSwap()));
    moveAction = new QAction("Move",this);
    moveAction->setEnabled(false);
    connect(moveAction,SIGNAL(triggered()),this,SLOT(actionMove()));
    renameAction = new QAction("Rename",this);
    connect(renameAction,SIGNAL(triggered()),this,SLOT(actionRename()));

    splitAction->setStatusTip(tr("Split edge here"));
    deleteAction->setShortcut(tr("Delete"));
    deleteAction->setStatusTip(tr("Delete item from diagram"));


    nodeMenu = new QMenu(this);
    nodeMenu->addAction( deleteAction );

    edgeMenu = new QMenu(this);
    edgeMenu->addAction( deleteAction );
    edgeMenu->addAction( splitAction );
    edgeMenu->addAction( transformAction );

    polyMenu = new QMenu(this);
    polyMenu->addAction( moveAction );
    polyMenu->addAction( deleteAction );
    polyMenu->addAction( closeAction );
    polyMenu->addAction( renameAction );

    linkMenu =  new QMenu(this);
    linkMenu->addAction( deleteAction );
    linkMenu->addAction( swapAction );

    connect(ui->buttonTest,SIGNAL(clicked()),this,SLOT(pressTest()));
    connect(ui->button3D,SIGNAL(clicked()),this,SLOT(pressSimu()));
    connect(ui->buttonSave,SIGNAL(clicked()),this,SLOT(pressSave()));
    //connect(scene,SIGNAL(middleClicked(QPointF)),this,SLOT(addPoint(QPointF)));

    loadFile("test.txt");

    for(int i=0;i<patterns_.size();i++)
        patterns_.at(i)->display(scene);

    for(int i=0;i<links_.size();i++)
        links_.at(i)->display(scene);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectEdges()
{
    QList<QGraphicsItem *> items = scene->selectedItems();
    if(items.size()!=2){
        QMessageBox::warning(this,tr("Warning"),tr("You have to select 2 edges"));
    }else{
        MyEdge *e1 = qgraphicsitem_cast<MyEdge *>(items[0]);
        MyEdge *e2 = qgraphicsitem_cast<MyEdge *>(items[1]);
        if(e1 && e2){
            MyLink *link = new MyLink(e1,e2,linkMenu);
            scene->addItem(link);
            links_.push_back(link);
            return;
        }
        MyPoint *p1 = qgraphicsitem_cast<MyPoint *>(items[0]);
        MyPoint *p2 = qgraphicsitem_cast<MyPoint *>(items[1]);
        if(p1 && p2){
            if(p1->getPattern()==p2->getPattern()){
                MyEdge *e = 0;
                if(p1->getSrc()==0 && p2->getDest()==0)
                    e = new MyEdge(p2,p1,p1->getPattern(),p1->getPattern()->getEmptyEdgeID(),edgeMenu);
                if(p1->getDest()==0 && p2->getSrc()==0)
                    e = new MyEdge(p1,p2,p1->getPattern(),p1->getPattern()->getEmptyEdgeID(),edgeMenu);
                if(!e){
                    return;
                }
                p1->getPattern()->addEdge(e);
                scene->addItem(e);
                return;
            }else{
                QMessageBox::warning(this,tr("Warning"),tr("You have to select 2 points from the same pattern"));
                return;
            }
        }
        QMessageBox::warning(this,tr("Warning"),tr("You have to select 2 edges or 2 points"));
    }
}

void MainWindow::pressTest()
{
    for(int i=0;i<polyDraw.size();i++)
        scene->removeItem(polyDraw.at(i));
    polyDraw.clear();

    polys.clear();

    for(int i=0;i<patterns_.size();i++){
        polys << patterns_[i]->getPolygon();
    }

    for(int k=0;k<polys.size();k++){
        Meshing mesh(polys.at(k),25.0);
        QList<QPolygonF> triangles = mesh.getMesh();

        for(int i=0;i<triangles.size();i++){
            polyDraw << scene->addPolygon(triangles.at(i),QPen(QColor(rand()%200,rand()%200,rand()%200)));
        }
    }
}

void MainWindow::loadFile(QString filename)
{
    QList<QColor> colors;
    colors << Qt::blue << Qt::green << Qt::yellow << Qt::magenta << Qt::gray << Qt::cyan << Qt::red << Qt::black;

    /*black, white, darkGray, gray, lightGray,
    red, green, blue, cyan, magenta, yellow,
    darkRed, darkGreen, darkBlue, darkCyan, darkMagenta, darkYellow*/

    int nb = 0;

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
            if(items.at(0)=="ORIENTATION"){
                if(!pattern->isValid()){
                    QMessageBox::critical(this,tr("Error"),tr("Invalid pattern on loading"));
                    return;
                }
                pattern->setOrientation( items.at(1).toDouble() );
            }else
            if(items.at(0)=="POINT"){
                if(!pattern->isValid()){
                    QMessageBox::critical(this,tr("Error"),tr("Invalid pattern on loading"));
                    return;
                }
                int id = items.at(1).toInt();

                QPointF point ( items.at(2).toDouble() , items.at(3).toDouble() );
                //pattern->addPoint(id,point);

                MyPoint *pt = new MyPoint(point,pattern,id,nodeMenu);
                connect(this,SIGNAL(gridEnabled(bool)),pt->widget,SLOT(setUseGrid(bool)));

                pattern->addPoint(pt);

                //pattern->setPoint(key,pt);
            }else
            if(items.at(0)=="EDGE"){
                if(!pattern->isValid()){
                    QMessageBox::critical(this,tr("Error"),tr("Invalid pattern on loading"));
                    return;
                }
                int id = items.at(1).toInt();
                int startID =  items.at(2).toInt();
                int endID =  items.at(3).toInt();

                //Use index and not ID
                MyPoint* p1 = pattern->getPoint(startID);
                MyPoint* p2 = pattern->getPoint(endID);
                if(!p1||!p2){
                    qDebug() << "Error, MyPoint doesn't exist";
                    continue;
                }
                MyEdge* e = new MyEdge(p1,p2,pattern,id,edgeMenu);
                pattern->addEdge(e);

                //pattern->addEdge(id,startID,endID);
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
                //pattern->addCurve(id,list);
            }else
            if(items.at(0)=="POLYGON"){
                if(!pattern->isValid()){
                    QMessageBox::critical(this,tr("Error"),tr("Invalid pattern on loading"));
                    return;
                }
                QList<int> list;
                for(int i=1;i<items.size();i++)
                    list << items.at(i).toInt();

                MyPolygon *p = new MyPolygon(pattern,polyMenu);

                for(int i=0;i<list.size();i++){
                    MyPoint *pt = pattern->getPoint(list.at(i));
                    if(pt)
                        p->addPoint( pt );
                }

                p->setColor(colors.at(nb++%colors.size()));

                pattern->setPolygon(p);
            }
            if(items.at(0)=="LINK"){
                if(pattern->isValid())
                    patterns_.push_back(pattern);

                pattern = new MyPattern(-1,"");

                int p1 = items.at(1).toInt();
                int e1 = items.at(2).toInt();
                int p2 = items.at(3).toInt();
                int e2 = items.at(4).toInt();
                bool s = items.at(5)=="true"?true:false;
                if(p1>=patterns_.size() || p2>=patterns_.size()){
                    qDebug() << p1<<">="<<patterns_.size()<<" || "<<p2<<">="<<patterns_.size();
                    qDebug() << "Invalid pattern";
                    continue;
                }
                MyEdge* me1 = patterns_[p1]->getEdge(e1);
                MyEdge* me2 = patterns_[p2]->getEdge(e2);
                if(!me1 || !me2){
                    qDebug() << "Invalid edge";
                    continue;
                }
                MyLink* l = new MyLink(me1,me2,linkMenu);
                l->object->setInverse(s);
                links_.push_back(l);
            }
        }

        if(pattern->isValid())
            patterns_.push_back(pattern);
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
    for(int i=0;i<links_.size();i++){
        out << links_.at(i)->getText();
    }
    file.close();
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
        pts = patterns_.at(k)->getPoints();
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

void MainWindow::actionSwap()
{
    QList<QGraphicsItem *> items = scene->selectedItems();
    MyLink *l = qgraphicsitem_cast<MyLink*>(items[0]);
    if(!l) return;
    l->object->toggle();
    l->update();
}

void MainWindow::actionDelete()
{
    QList<QGraphicsItem *> items = scene->selectedItems();

    //If MyLink
    MyLink *l = qgraphicsitem_cast<MyLink*>(items[0]);
    if(l!=0){
        l->remove();
        links_.removeAll(l);
        delete l;
        return;
    }
    //If MyEdge
    MyPoint *p = qgraphicsitem_cast<MyPoint*>(items[0]);
    if(p!=0){
        if(p->getSrc() && p->getDest()){
            int id = p->getPattern()->getEmptyEdgeID();
            MyEdge *e = new MyEdge(p->getSrc()->getSource(), p->getDest()->getDest(), p->getPattern(),id,edgeMenu);
            p->getPattern()->addEdge(e);
            scene->addItem(e);
        }
        p->remove();
        p->getPattern()->getPoly()->remove(p);

        delete p;
        return;
    }
    //If MyEdge
    MyEdge *e = qgraphicsitem_cast<MyEdge*>(items[0]);
    if(e!=0){
        e->remove();
        delete e;
        return;
    }
    //If MyPolygon
    MyPolygon *po = qgraphicsitem_cast<MyPolygon*>(items[0]);
    if(po!=0){
        po->remove();
        patterns_.removeAll(po->getPattern());
        delete po->getPattern();
        return;
    }
}

void MainWindow::actionRename()
{
    QList<QGraphicsItem *> items = scene->selectedItems();
    //If MyPolygon
    MyPolygon *po = qgraphicsitem_cast<MyPolygon*>(items[0]);
    if(po!=0){
        QString name = QInputDialog::getText(this,tr("New name"),tr("Enter a new same for this pattern"));
        po->getPattern()->setName(name);
    }
}

void MainWindow::actionClose()
{

}

void MainWindow::actionMove()
{

}

void MainWindow::actionTransform()
{

}

void MainWindow::actionSplit()
{
    QList<QGraphicsItem *> items = scene->selectedItems();
    MyEdge *e = qgraphicsitem_cast<MyEdge*>(items[0]);
    if(!e) return;
    MyLink* l = e->removeLink();
    links_.removeAll(l);
    QPointF point = e->selectedPoint();

    int pointID = e->getPattern()->getEmptyPointID();
    MyPoint *pt = new MyPoint(point,e->getPattern(),pointID,nodeMenu);
    connect(this,SIGNAL(gridEnabled(bool)),pt->widget,SLOT(setUseGrid(bool)));

    e->getPattern()->addPoint(pt);
    scene->addItem(pt);

    int edgeID1 = e->getPattern()->getEmptyEdgeID();
    MyEdge *e1 = new MyEdge(e->getSource(),pt,e->getPattern(),edgeID1,edgeMenu);
    e->getPattern()->addEdge(e1);
    scene->addItem(e1);

    int edgeID2 = e->getPattern()->getEmptyEdgeID();
    MyEdge *e2 = new MyEdge(pt,e->getDest(),e->getPattern(),edgeID2,edgeMenu);
    e->getPattern()->addEdge(e2);
    scene->addItem(e2);

    e->getPattern()->getPoly()->insert(e->getSource(),e->getDest(),pt);
    e->remove();

    delete e;
}
