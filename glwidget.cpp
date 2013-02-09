/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtGui>
#include <QtOpenGL>

#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent, QGLWidget *shareWidget)
    : QGLWidget(parent, shareWidget)
{
    clearColor = Qt::black;
    xRot = 0;
    yRot = 0;
    zRot = 0;
    zoom = 10.0;
}

GLWidget::~GLWidget()
{
}

QSize GLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize GLWidget::sizeHint() const
{
    return QSize(200, 200);
}

void GLWidget::rotateBy(int xAngle, int yAngle, int zAngle)
{
    xRot += xAngle;
    yRot += yAngle;
    zRot += zAngle;
    updateGL();
}

void GLWidget::setClearColor(const QColor &color)
{
    clearColor = color;
    updateGL();
}

void GLWidget::initializeGL()
{

    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
    glDisable(GL_CULL_FACE);

    //gl{Enable,Disable}(GL_CULL_FACE);
    //glCullFace(GL_{FRONT,BACK,FRONT_AND_BACK});
    //glCullFace(GL_FRONT_AND_BACK);

    glEnable(GL_TEXTURE_2D);

    //glEnable(GL_LIGHTING);
    //glShadeModel(GL_SMOOTH);


}

void GLWidget::paintGL()
{
    qglClearColor(clearColor);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -10.0);
    glRotatef(xRot / 16.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot / 16.0f, 0.0f, 1.0f, 0.0f);
    glRotatef(zRot / 16.0f, 0.0f, 0.0f, 1.0f);


    glDisable(GL_TEXTURE_2D);
    glColor3f(0, 0, 0);
    for(int i=0;i<polys_.size();i++){
        QPolygon3F poly = polys_.at(i);
        glBegin(GL_LINES);
        for(int j=0;j<poly.size()-1;j++){
            glVertex3d(poly.at(j).x(),  poly.at(j).y(),  poly.at(j).z());
            glVertex3d(poly.at(j+1).x(),poly.at(j+1).y(),poly.at(j+1).z());
        }
        glEnd();
    }

    glEnable(GL_TEXTURE_2D);
    glColor3f(1.0f, 1.0f, 1.0f);

    glVertexPointer(3, GL_FLOAT, 0, vertices_.constData());
    glTexCoordPointer(2, GL_FLOAT, 0, texCoords_.constData());

    if(textures_.size()>0){
        //qDebug() << "Display texture" << texCoords_.size();
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        /*for (int i = 0; i < textures_.size(); ++i) {
            glBindTexture(GL_TEXTURE_2D, textures_[0]);
            glDrawArrays(GL_TRIANGLE_FAN, i * 3, 3);
        }*/
        glBindTexture(GL_TEXTURE_2D, textures_[0]);
        for(int i=0;i<vertices_.size()/3;i++)
            glDrawArrays(GL_TRIANGLE_FAN, i * 3, 3);
    }
}

void GLWidget::resizeGL(int width, int height)
{
    //int side = qMin(width, height);
    //glViewport((width - side) / 2, (height - side) / 2, side, side);
    glViewport(0,0, width, height);

    double ratio = 1.0;
    if(height!=0){
        ratio = (double)width/(double)height;
    }

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-0.5*ratio, +0.5*ratio, +0.5, -0.5, 4.0, 15.0);
    glMatrixMode(GL_MODELVIEW);
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        rotateBy(8 * dy, 8 * dx, 0);
    } else if (event->buttons() & Qt::RightButton) {
        rotateBy(8 * dy, 0, 8 * dx);
    }
    lastPos = event->pos();
}

void GLWidget::mouseReleaseEvent(QMouseEvent * /* event */)
{
    emit clicked();
}

void GLWidget::wheelEvent(QWheelEvent *event)
{
    //TODO, zoom
    /*zoom = std::max(10.0,zoom + event->delta()/100.0);
    qDebug() << zoom;
    paintGL();*/
}

void  GLWidget::setVertices(QVector<QVector3D> vect)
{
    vertices_ = vect;
}

void  GLWidget::setTextureCoords(QVector<QVector2D> vect)
{
    texCoords_ = vect;
}

void  GLWidget::setTextures(QStringList list)
{
    //TODO, clear GL texture
    textures_.clear();
    foreach(QString texture, list){
        textures_ << bindTexture(QPixmap(texture), GL_TEXTURE_2D);
    }
}

void GLWidget::setPolygons(QList<QPolygon3F> polys)
{
    polys_.clear();
    foreach(QPolygon3F poly, polys){
        if(poly.isEmpty())
            continue;
        if(!poly.isClosed()){
            poly << poly.first();
        }
        polys_ << poly;
    }
}
