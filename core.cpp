#include "core.h"

Core::Core()
{

}

QString Core::getCurrentFileName() const
{
    return currentFileName;
}

void Core::setCurrentFileName(const QString &value)
{
    currentFileName = value;
}

void Core::parseCurrentFile()
{
    QFileInfo fileInfo(currentFileName);
    if (fileInfo.completeSuffix().compare(RRI_FILES_EXT)){
       // model=parseRRIFile(currentFileName);
    }
}
