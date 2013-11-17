#include "readwritexml.h"

ReadWriteXML::ReadWriteXML(QWidget *parent) :
    QWidget(parent)
{
}

bool ReadWriteXML::parse(QString filepath)
{
    if(!QFile::exists(filepath)){
        QMessageBox::critical(this,"error",tr("This file doesn't exists: %1").arg(filepath));
        return false;
    }

    QFileInfo fileInfo(filepath);

    if(filepath.endsWith(".txt",Qt::CaseInsensitive)){
        this->readTXT(fileInfo);
        return true;
    }

    QFile xml_doc(filepath);

    if(!xml_doc.open(QIODevice::ReadOnly)){
        QMessageBox::warning(this,tr("Failed to open XML document"),tr("The XML document '%1' could not be opened. Verify that the name is correct and that the document is well placed.").arg(xml_doc.fileName()));
        return false;
    }

    QDomDocument *dom = new QDomDocument("docXML");
    if(!dom->setContent(&xml_doc)){
        xml_doc.close();
        QMessageBox::warning(this,tr("Error opening the XML document"),tr("The XML document could not be assigned to the object QDomDocument."));
        return false;
    }

    this->read(dom,fileInfo);
    return true;
}


void ReadWriteXML::save(QString filepath)
{
    QFileInfo fileInfo(filepath);

    if(!this->checkFileName(fileInfo)){
        return;
    }

    if(filepath.endsWith(".txt",Qt::CaseInsensitive)){
        this->writeTXT(fileInfo);
        return;
    }

    QFile file(filepath);
    file.open(QFile::WriteOnly);


    QTextStream stream(&file);
    stream.setCodec("UTF-8");


    QDomDocument *dom = new QDomDocument;

    this->write(dom,fileInfo);

    stream << dom->toString();

    file.close();
}

bool ReadWriteXML::checkFileName(QFileInfo fileInfo)
{
    QFile file(fileInfo.absoluteFilePath());
    if(file.open(QFile::WriteOnly)){
        return true;
    }else{
        QMessageBox::critical(this,tr("Error"),tr("This file is not writable: %1").arg(fileInfo.absoluteFilePath()));
        return false;
    }
}

void ReadWriteXML::addNode(QDomDocument *dom, QDomElement *parent, QString tag, QString data)
{
    QDomElement node = dom->createElement(tag);
    parent->appendChild(node);

    QDomText textNode = dom->createTextNode(data);
    node.appendChild(textNode);
}

void ReadWriteXML::addNode(QDomDocument *dom, QDomElement *parent, QString tag, int data)
{
    addNode(dom,parent,tag,QString::number(data));
}
