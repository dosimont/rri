#ifndef PRVFILEMANAGER_H
#define PRVFILEMANAGER_H

#include <QString>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QIODevice>

#include "prv_constants.h"

class PrvFileManager
{
public:
    PrvFileManager();
    int initStreams(QString prvName, QIODevice::OpenMode mode);
    QString getPrv() const;
    QString getPcf() const;
    QString getRow() const;
    QFile *getPrvFile() const;
    QFile *getPcfFile() const;
    QFile *getRowFile() const;
    QTextStream *getPrvStream() const;
    QTextStream *getPcfStream() const;
    QTextStream *getRowStream() const;

protected:
    QString prv;
    QString pcf;
    QString row;
    QFile* prvFile;
    QFile* pcfFile;
    QFile* rowFile;
    QTextStream* prvStream;
    QTextStream* pcfStream;
    QTextStream* rowStream;
};

#endif // PRVFILEMANAGER_H
