#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QVector>
#include <QDir>
#include <QFile>
#include <QFileInfo>

#include "argumentmanager.h"
#include "streamset.h"
#include "bin_constants.h"
#include "prvfilemanager.h"

class FileManager
{
public:
    FileManager(ArgumentManager* argumentManager);
    ~FileManager();
    QVector<QString> getIterationNames() const;

    ArgumentManager *getArgumentManager() const;

    QVector<QString> getCallerDataFileNames() const;

    QString getInputDir() const;

    QString getOutputDir() const;

    QVector<StreamSet *> getStreamSets() const;

    QTextStream getRegionStream() const;

    PrvFileManager *getInputPrvFiles() const;

    PrvFileManager *getOutputPrvFiles() const;

protected:
    int init();
    int mkoutputDir();
    int set();
    QString inputDir;
    QString outputDir;
    QString regions;
    QFile* regionFile;
    QTextStream* regionStream;
    QVector<QString> callerDataFileNames;
    QVector<QString> iterationNames;
    QVector<StreamSet*> streamSets;
    PrvFileManager* inputPrvFiles;
    PrvFileManager* outputPrvFiles;
    ArgumentManager* argumentManager;
};

#endif // FILEMANAGER_H
