#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QVector>
#include <QDir>
#include <QFile>
#include <QFileInfo>

#include "argumentmanager.h"
#include "streamset.h"
#include "bin_constants.h"

class FileManager
{
public:
    FileManager(ArgumentManager* argumentManager);
    QVector<QString> getIterationNames() const;

    ArgumentManager *getArgumentManager() const;

    QVector<QString> getCallerDataFileNames() const;

    QString getInputDir() const;

    QString getOutputDir() const;

    QVector<StreamSet *> getStreamSets() const;

protected:
    int init();
    int mkoutputDir();
    int mkoutputs();
    QString inputDir;
    QString outputDir;
    QVector<QString> callerDataFileNames;
    QVector<QString> iterationNames;
    QVector<StreamSet*> streamSets;
    ArgumentManager* argumentManager;
};

#endif // FILEMANAGER_H
