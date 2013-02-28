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
    meshing/meshing.cpp \
    patternscene.cpp \
    mypoint.cpp \
    myedge.cpp \
    mypattern.cpp \
    tools.cpp \
    glwidget.cpp \
    mypolygon.cpp \
    graphicsview.cpp \
    engine.cpp \
    grid.cpp \
    meshing/mymeshingedge.cpp \
    meshing/mymeshingpoint.cpp \
    meshing/mymeshingpolygon.cpp \
    meshing/mymeshingtriangle.cpp \
    mylink.cpp \
    mycurve.cpp

HEADERS  += mainwindow.h \
    meshing/meshing.h \
    patternscene.h \
    mypoint.h \
    myedge.h \
    mypattern.h \
    tools.h \
    glwidget.h \
    mypolygon.h \
    graphicsview.h \
    engine.h \
    grid.h \
    meshing/mymeshingedge.h \
    meshing/mymeshingpoint.h \
    meshing/mymeshingpolygon.h \
    meshing/mymeshingtriangle.h \
    mylink.h \
    mycurve.h

FORMS    += mainwindow.ui

OTHER_FILES += test.txt
