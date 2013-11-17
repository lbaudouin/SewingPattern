#ifndef READWRITEXML_H
#define READWRITEXML_H

#include <QWidget>
#include <QMessageBox>
#include <QDomDocument>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QTextCodec>

class ReadWriteXML : public QWidget
{
    Q_OBJECT
public:
    explicit ReadWriteXML(QWidget *parent = 0);

    bool parse(QString filepath);
    void save(QString filepath);
    void flush(QString filepath) { save(filepath); }
    
protected:
    virtual void read(QDomDocument *dom, QFileInfo fileInfo = QFileInfo()) = 0;
    virtual void write(QDomDocument *dom, QFileInfo fileInfo = QFileInfo()) = 0;
    virtual void readTXT(QFileInfo) {}
    virtual void writeTXT(QFileInfo) {}
    virtual bool checkFileName(QFileInfo fileInfo);

    void addNode(QDomDocument *dom, QDomElement *parent, QString tag, QString data);
    void addNode(QDomDocument *dom, QDomElement *parent, QString tag, int data);

signals:
    
public slots:
    
};

#endif // READWRITEXML_H
