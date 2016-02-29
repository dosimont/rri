#include "prvfilemanager.h"

PrvFileManager::PrvFileManager()
{
}

int PrvFileManager::initStreams(QString prvName, QIODevice::OpenMode mode)
{
    prv=prvName;
    QFileInfo fileInfo=QFileInfo(prv);
    QString baseName=fileInfo.completeBaseName();
    QString path=fileInfo.absolutePath();
    pcf=path+"/"+baseName+EXT_PCF;
    row=path+"/"+baseName+EXT_ROW;
    prvFile=new QFile(prv);
    pcfFile=new QFile(pcf);
    rowFile=new QFile(row);
    file = new QFile(path);
    if (!prvFile->open(mode)){
       return 1;
    }
    if (!pcfFile->open(mode)){
       return 2;
    }
    if (rowFile->open(mode)){
        rowStream=new QTextStream(rowFile);
        rowStreamFound=true;
    }else{
        rowStreamFound=false;
    }
    prvStream=new QTextStream(prvFile);
    pcfStream=new QTextStream(pcfFile);
    return 0;
}

QString PrvFileManager::getPrv() const
{
    return prv;
}

QString PrvFileManager::getPcf() const
{
    return pcf;
}

QString PrvFileManager::getRow() const
{
    return row;
}

QFile *PrvFileManager::getPrvFile() const
{
    return prvFile;
}

QFile *PrvFileManager::getPcfFile() const
{
    return pcfFile;
}

QFile *PrvFileManager::getRowFile() const
{
    return rowFile;
}

QTextStream *PrvFileManager::getPrvStream() const
{
    return prvStream;
}

QTextStream *PrvFileManager::getPcfStream() const
{
    return pcfStream;
}

QTextStream *PrvFileManager::getRowStream() const
{
    return rowStream;
}
