#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QVector>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QDebug>

#include "argumentmanager.h"
#include "streamset.h"
#include "bin_constants.h"
#include "prvfilemanager.h"

#define RETURN_OK 0
#define RETURN_ERR_INVALID_INPUT_DIR -1
#define RETURN_ERR_INVALID_INPUT_FILE -2
#define RETURN_ERR_INVALID_OUTPUT_DIR -3
#define RETURN_ERR_EXISTING_OUTPUT_DIR -4
#define RETURN_ERR_INVALID_REGION_FILE -5
#define RETURN_ERR_INVALID_OUTPUT_STREAM -6
#define RETURN_ERR_INVALID_INPUT_STREAM -7
#define RETURN_ERR_INVALID_INPUT_TRACE -8
#define RETURN_ERR_COPY_TRACE -9
#define RETURN_ERR_INVALID_OUTPUT_TRACE -10

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
    PrvFileManager *getInputPrvFiles() const;
    PrvFileManager *getOutputPrvFiles() const;
    QTextStream *getRegionStream() const;

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
