#ifndef INPUTFILE_H
#define INPUTFILE_H

#include "readwritexml.h"
#include <QDesktopServices>
#include <QDir>

#include <QDebug>

class InputFile : public ReadWriteXML
{
    Q_OBJECT
public:
    InputFile(QWidget *parent = 0);

    void load(QString filepath);
    void save(QString filepath);


protected:
    virtual void read(QDomDocument *dom, QFileInfo fileInfo);
    virtual void write(QDomDocument *dom, QFileInfo fileInfo);

private:
};

#endif // INPUTFILE_H
