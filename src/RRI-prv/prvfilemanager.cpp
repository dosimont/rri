#include "prvfilemanager.h"

PrvFileManager::PrvFileManager()
{
}

PrvFileManager::~PrvFileManager()
{
    qDebug()<<"delete PrvFileManager";
    delete prvFile;
    delete pcfFile;
    delete rowFile;
    delete prvStream;
    delete pcfStream;
    delete rowStream;
}

int PrvFileManager::initStreams(QString prvPath, QIODevice::OpenMode mode)
{
    prv=prvPath;
    QFileInfo fileInfo=QFileInfo(prv);
    QString baseName=fileInfo.completeBaseName();
    QString path=fileInfo.absolutePath();
    pcf=path+"/"+baseName+EXT_PCF;
    row=path+"/"+baseName+EXT_ROW;
    prvFile=new QFile(prv);
    pcfFile=new QFile(pcf);
    rowFile=new QFile(row);
    if (!prvFile->open(mode)){
       return 1;
    }
    if (!pcfFile->open(mode)){
       return 2;
    }
    if (rowFile->open(mode)){
        rowStream=new QTextStream(rowFile);
        //rowStreamFound=true;
    }else{
        //rowStreamFound=false;
        rowStream=new QTextStream();
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

void PrvFileManager::copyTrace(QString prvInputPath, QString prvOutputPath)
{
    QString prv1=prvInputPath;
    QFileInfo fileInfo1=QFileInfo(prv1);
    QString baseName1=fileInfo1.completeBaseName();
    QString path1=fileInfo1.absolutePath();
    QString pcf1=path1+"/"+baseName1+EXT_PCF;
    QString row1=path1+"/"+baseName1+EXT_ROW;
    QString prv2=prvOutputPath;
    QFileInfo fileInfo2=QFileInfo(prv2);
    QString baseName2=fileInfo2.completeBaseName();
    QString path2=fileInfo2.absolutePath();
    QString pcf2=path2+"/"+baseName2+EXT_PCF;
    QString row2=path2+"/"+baseName2+EXT_ROW;
    QFile::copy(prv1, prv2);
    QFile::copy(pcf1, pcf2);
    QFile::copy(row1, row2);
}
