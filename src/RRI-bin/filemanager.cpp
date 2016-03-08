#include "filemanager.h"

FileManager::FileManager(ArgumentManager *argumentManager)
{
    this->argumentManager=argumentManager;
    init();
}

FileManager::~FileManager()
{
    qDebug().nospace()<<"Delete FileManager";
    for(StreamSet* stream:streamSets){
        delete stream;
    }
    qDebug().nospace()<<"Delete File and Streams";
    delete regionFile;
    delete regionStream;
    delete inputPrvFiles;
    delete outputPrvFiles;
}

int FileManager::init()
{
    mkoutputDir();
    set();
    return 0;
}

int FileManager::mkoutputDir()
{
    if (!argumentManager->getUniqueFile()){
        QDir dir(argumentManager->getInput());
        inputDir=dir.absolutePath();
    }else{
        QFileInfo fileInfo(argumentManager->getInput());
        inputDir=fileInfo.absolutePath();
    }
    if (argumentManager->getOutput().isEmpty()){
        outputDir=inputDir+RRI_DIR_PATTERN;
    }else{
        outputDir=argumentManager->getOutput();
    }
    if (QDir().mkdir(outputDir)){
        return 0;
    }else{
        return 1;
    }
}

int FileManager::set()
{
    if (argumentManager->getUniqueFile()){
        callerDataFileNames.push_back(argumentManager->getInput());
        QFileInfo fileInfo(callerDataFileNames.last());
        QString basename=fileInfo.completeBaseName();
        QStringList iterationNameList=basename.split('.');
        QString iterationName=iterationNameList.last();
        iterationNames.push_back(iterationName);
        QString outputSubDir=outputDir+"/"+iterationName;
        QDir().mkdir(outputSubDir);
        streamSets.push_back(new StreamSet());
        streamSets.last()->setOuputStreams(outputSubDir);
        streamSets.last()->setInputStream(callerDataFileNames.last());
    }else{     
        QDir dir(inputDir);
        dir.setNameFilters(QStringList() << CALLERDATA_FILES);
        dir.setFilter(QDir::Files);
        foreach(QFileInfo fileInfo, dir.entryInfoList())
        {
            QString file=fileInfo.absoluteFilePath();
            callerDataFileNames.push_back(file);
            QString basename=fileInfo.completeBaseName();
            QStringList iterationNameList=basename.split('.');
            QString iterationName=iterationNameList.last();
            iterationNames.push_back(iterationName);
            QString outputSubDir=outputDir+"/"+iterationName;
            QDir().mkdir(outputSubDir);
            streamSets.push_back(new StreamSet());
            streamSets.last()->setOuputStreams(outputSubDir);
            streamSets.last()->setInputStream(file);
        }
        dir.setNameFilters(QStringList() << CALLERDATA_REGIONS_FILE);
        dir.setFilter(QDir::Files);
        regions=dir.entryList().first();
        regionFile=new QFile(dir.path()+"/"+regions);
        if (!regionFile->open(QIODevice::ReadOnly | QIODevice::Text)){
           return 1;
        }
        regionStream=new QTextStream(regionFile);
        dir.setNameFilters(QStringList() << PRV_INPUT_FILE);
        dir.setFilter(QDir::Files);
        inputPrvFiles=new PrvFileManager();
        inputPrvFiles->initStreams(dir.path()+"/"+dir.entryList().first(), QIODevice::ReadOnly | QIODevice::Text);
        QString inputPrvBaseName=inputPrvFiles->getPrv();
        QFileInfo fileInfo=QFileInfo(inputPrvBaseName);
        inputPrvBaseName=fileInfo.completeBaseName();
        QString outputPrv=outputDir+"/"+inputPrvBaseName+RRI_DIR_PATTERN+RRI_PRV_PATTERN;
        PrvFileManager::copyTrace(inputPrvFiles->getPrv(), outputPrv);
        outputPrvFiles=new PrvFileManager();
        outputPrvFiles->initStreams(outputPrv, QIODevice::ReadWrite | QIODevice::Text | QIODevice::Append);
    }
    return 0;
}

QTextStream *FileManager::getRegionStream() const
{
    return regionStream;
}

PrvFileManager *FileManager::getOutputPrvFiles() const
{
    return outputPrvFiles;
}

PrvFileManager *FileManager::getInputPrvFiles() const
{
    return inputPrvFiles;
}


QVector<StreamSet *> FileManager::getStreamSets() const
{
    return streamSets;
}

QString FileManager::getOutputDir() const
{
    return outputDir;
}

QString FileManager::getInputDir() const
{
    return inputDir;
}

QVector<QString> FileManager::getCallerDataFileNames() const
{
    return callerDataFileNames;
}

ArgumentManager *FileManager::getArgumentManager() const
{
    return argumentManager;
}

QVector<QString> FileManager::getIterationNames() const
{
    return iterationNames;
}



