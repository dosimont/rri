#include "filemanager.h"

FileManager::FileManager(ArgumentManager *argumentManager)
{
    this->argumentManager=argumentManager;
    init();
}

int FileManager::init()
{
    mkoutputDir();
    mkoutputs();
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

int FileManager::mkoutputs()
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
    }
    return 0;
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



