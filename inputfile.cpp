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

            if(element.tagName()=="file"){
                element.attribute("title",tr("empty_title"));
                element.attribute("artist",tr("empty_artist"));
                element.attribute("path","");
                element.attribute("wasOpen","false")=="true";
            }
            node = node.nextSibling();
        }
    }
}

void InputFile::write(QDomDocument *dom, QFileInfo)
{
    QDomElement mainNode = dom->createElement("pattern");
    dom->appendChild(mainNode);

    addNode(dom,&mainNode,"version","0.0.1");
    addNode(dom,&mainNode,"author","me");
    addNode(dom,&mainNode,"title","My Pattern");


    QStringList list;
    list << "Manche" << "Dos" << "Col";

    foreach(QString string, list){
        QDomElement elem = dom->createElement("face");
        elem.setAttribute("name",string);
        elem.setAttribute("color",QColor(qrand()%255,qrand()%255,qrand()%255).name());
        elem.setAttribute("orientation",0.125);

        addNode(dom,&elem,"point1","(0,0)");
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
