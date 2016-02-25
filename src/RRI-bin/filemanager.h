#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QVector>
#include "argumentmanager.h"

#define FOLDING_DIR_PATTERN ".folding"
#define FOLDING_FILES_PATTERN ".codeblocks.fused."
#define FOLDING_CALLERDATA_EXT ".callerdata"

class FileManager
{
public:
    FileManager(ArgumentManager argumentManager);
protected:
    QString inputDir;
    QString inputBasePattern;
    QVector<QString> callerDataFileNames;
    QVector<QString> iterationNames;
};

#endif // FILEMANAGER_H
