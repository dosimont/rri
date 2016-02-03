#include "rricore.h"

RRICore::RRICore()
{

}

QString RRICore::getCurrentFileName() const
{
    return currentFileName;
}

void RRICore::setCurrentFileName(const QString &value)
{
    currentFileName = value;
}

void RRICore::parseCurrentFile()
{
    QFileInfo fileInfo(currentFileName);
    if (fileInfo.completeSuffix().compare(RRI_FILE_EXT)){
       currentModel=RRIModel();
       currentModel.parseFile(currentFileName);
    }
}

void RRICore::parseFile(const QString &value)
{
    setCurrentFileName(value);
    parseCurrentFile();
}
