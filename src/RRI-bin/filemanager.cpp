#include "filemanager.h"

FileManager::FileManager(ArgumentManager *argumentManager)
{
    this->argumentManager=argumentManager;
}

int FileManager::init()
{
    mkoutputDir();
    setCallerDataFileNames();
}

int FileManager::mkoutputDir()
{
    if (!argumentManager->getUniqueFile()){
        inputDir=argumentManager->getInput();
        if (argumentManager->getOutput().isEmpty()){
            outputDir=inputDir+RRI_DIR_PATTERN;
        }else{
            outputDir=argumentManager->getOutput();
        }
    }else{
        QFileInfo fileInfo(argumentManager->getInput());
        inputDir=fileInfo.absolutePath();
        if (argumentManager->getOutput().isEmpty()){
            outputDir=inputDir+RRI_DIR_PATTERN;
        }else{
            outputDir=argumentManager->getOutput();
        }
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
    }else{
        QDir dir(inputDir);
        dir.setNameFilters(QStringList() << "*.callerdata");
        dir.setFilter(QDir::Files);
        foreach(QFileInfo fileInfo, dir.entryInfoList())
        {
            QString file=fileInfo.absoluteFilePath();
            callerDataFileNames.push_back(file);
            file=fileInfo.completeBaseName();
            QStringList iterationNameList=file.split('.');
            QString iterationName=iterationNameList.last();
            iterationNames.push_back(iterationName);
            QString outputSubDir=outputDir+"/"+iterationName;
            (QDir().mkdir(outputSubDir);
            streamSets.append(StreamSet());
            streamSets.last().setStreams(outputSubDir);
        }
    }
    return 0;
}



