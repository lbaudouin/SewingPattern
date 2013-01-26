#-------------------------------------------------
#
# Project created by QtCreator 2012-12-18T19:31:40
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = Pattern
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    point2d.cpp \
    edge.cpp \
    meshing.cpp \
    patternscene.cpp \
    mypoint.cpp \
    myedge.cpp \
    mypattern.cpp \
    tools.cpp \
    glwidget.cpp \
    mypolygon.cpp \
    graphicsview.cpp \
    engine.cpp

HEADERS  += mainwindow.h \
    point2d.h \
    edge.h \
    meshing.h \
    patternscene.h \
    mypoint.h \
    myedge.h \
    mypattern.h \
    tools.h \
    glwidget.h \
    mypolygon.h \
    graphicsview.h \
    engine.h

FORMS    += mainwindow.ui
