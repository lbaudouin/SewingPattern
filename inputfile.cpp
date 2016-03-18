#include "inputfile.h"

InputFile::InputFile(QWidget *parent) : ReadWriteXML(parent)
{
}

void InputFile::read(QDomDocument *dom, QFileInfo)
{
    QDomElement dom_element = dom->documentElement();

    if(dom_element.tagName()=="pattern"){
        QDomNode node = dom_element.firstChild();

        while(!node.isNull())
        {
            QDomElement element = node.toElement();

            if(element.tagName()=="version"){
                qDebug() << "version:" << element.text();
            }
            if(element.tagName()=="author"){
                qDebug() << "author:" << element.text();
            }
            if(element.tagName()=="title"){
                qDebug() << "title:" << element.text();
            }
            if(element.tagName()=="face"){
                qDebug() << element.attribute("name",tr("name"));
                qDebug() << element.attribute("color",QColor(qrand()%255,qrand()%255,qrand()%255).name());
                qDebug() << element.attribute("orientation",QString::number(-1));

                QDomNode childNode = element.firstChild();
                while(!childNode.isNull())
                {
                    QDomElement childElement = childNode.toElement();
                    if(childElement.tagName()=="point"){
                        qDebug() << "point:" << childElement.text();
                    }
                    childNode = childNode.nextSibling();
                }
            }
            node = node.nextSibling();
        }
    }
}

void InputFile::write(QDomDocument *dom, QFileInfo)
{
    QDomElement mainNode = dom->createElement("pattern");
    dom->appendChild(mainNode);

    addNode(dom,&mainNode,"version","1");
    addNode(dom,&mainNode,"author","me");
    addNode(dom,&mainNode,"title","My Pattern");


    QStringList list;
    list << "Manche" << "Dos" << "Col";

    foreach(QString string, list){
        QDomElement elem = dom->createElement("face");
        elem.setAttribute("name",string);
        elem.setAttribute("color",QColor(qrand()%255,qrand()%255,qrand()%255).name());
        elem.setAttribute("orientation",0.125);

        addNode(dom,&elem,"point","(0,0)");
        mainNode.appendChild(elem);
    }
}

void InputFile::load(QString filepath)
{
    /*if(QFile::exists(QDesktopServices::storageLocation(QDesktopServices::DataLocation) + QDir::separator() + filepath))
        parse(QDesktopServices::storageLocation(QDesktopServices::DataLocation) + QDir::separator() + filepath);*/
    parse(filepath);
}

void InputFile::save(QString filepath)
{
    /*QDir dir(QDesktopServices::storageLocation(QDesktopServices::DataLocation));
    if(!dir.exists()){
        dir.mkpath(QDesktopServices::storageLocation(QDesktopServices::DataLocation));
    }
    flush(QDesktopServices::storageLocation(QDesktopServices::DataLocation) + QDir::separator() + filepath);*/
    flush(filepath);
}
