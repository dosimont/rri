#include "filemanager.h"

FileManager::FileManager(ArgumentManager *argumentManager)
{
    this->argumentManager=argumentManager;
}

FileManager::~FileManager()
{
    for(StreamSet* stream:streamSets){
        delete stream;
    }
    if (regionFile!=NULL){
        delete regionFile;
    }
    if (regionStream!=NULL){
        delete regionStream;
    }
    if (inputPrvFiles!=NULL){
        delete inputPrvFiles;
    }
    if (outputPrvFiles!=NULL){
        delete outputPrvFiles;
    }
}

int FileManager::init()
{
    int error;
    if ((error=mkoutputDir())!=RETURN_OK){
        return error;
    }
    if ((error=set())!=RETURN_OK){
        return error;
    }
    return RETURN_OK;
}

int FileManager::mkoutputDir()
{
    if (!argumentManager->getUniqueFile()){
        QDir dir(argumentManager->getInput());
        if (!dir.exists()){
            qWarning().nospace()<<"Invalid input directory";
            return RETURN_ERR_INVALID_INPUT_DIR;
        }
        inputDir=dir.absolutePath();
    }else{
        QFileInfo fileInfo(argumentManager->getInput());
        if (!fileInfo.exists()){
            qWarning().nospace()<<"Invalid input file";
            return RETURN_ERR_INVALID_INPUT_FILE;
        }
        inputDir=fileInfo.absolutePath();
    }
    if (argumentManager->getOutput().isEmpty()){
        outputDir=inputDir+RRI_DIR_PATTERN;
    }else{
        outputDir=argumentManager->getOutput();
    }
    if (QDir(outputDir).exists()){
        qWarning().nospace()<<"Output directory already exists";
        return RETURN_ERR_EXISTING_OUTPUT_DIR;
    }
    if (QDir().mkdir(outputDir)){
        return RETURN_OK;
    }else{
        qWarning().nospace()<<"Unable to create output directory";
        return RETURN_ERR_INVALID_OUTPUT_DIR;
    }
}

int FileManager::set()
{
    int error=RETURN_OK;
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
        if ((error=streamSets.last()->setOuputStreams(outputSubDir))!=RETURN_OK){
            qWarning().nospace()<<"Unable to set output streams";
            return RETURN_ERR_INVALID_OUTPUT_STREAM;
        }
        if ((error=streamSets.last()->setInputStream(callerDataFileNames.last()))!=RETURN_OK){
            qWarning().nospace()<<"Unable to set input streams";
            return RETURN_ERR_INVALID_INPUT_STREAM;
        }
    }else{     
        QDir dir(inputDir);
        dir.setNameFilters(QStringList() << CSV_FILES);
        dir.setFilter(QDir::Files);
        foreach(QFileInfo fileInfo, dir.entryInfoList())
        {
            bool error;
            QString name=fileInfo.fileName();
            QString destFile=outputDir+"/"+name;
            QFile::remove(destFile);
            error=QFile::copy(fileInfo.filePath(), destFile);
            if (!error){
                return RETURN_ERR_COPY_CSV;
            }
        }
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
            if ((error=streamSets.last()->setOuputStreams(outputSubDir))!=RETURN_OK){
                qWarning().nospace()<<"Unable to set output streams";
                return RETURN_ERR_INVALID_OUTPUT_STREAM;
            }
            if ((error=streamSets.last()->setInputStream(file))!=RETURN_OK){
                qWarning().nospace()<<"Unable to set input streams";
                return RETURN_ERR_INVALID_INPUT_STREAM;
            }
        }
        dir.setNameFilters(QStringList() << CALLERDATA_REGIONS_FILE);
        dir.setFilter(QDir::Files);
        regions=dir.entryList().first();
        regionFile=new QFile(dir.path()+"/"+regions);
        if (!regionFile->open(QIODevice::ReadOnly | QIODevice::Text)){
           qWarning().nospace()<<"Unable to open region file";
           return RETURN_ERR_INVALID_REGION_FILE;
        }
        regionStream=new QTextStream(regionFile);

        dir.setNameFilters(QStringList() << STATS_FILE);
        dir.setFilter(QDir::Files);
        stats=dir.entryList().first();
        statsFile=new QFile(dir.path()+"/"+statss);
        if (!statsFile->open(QIODevice::ReadOnly | QIODevice::Text)){
           qWarning().nospace()<<"Unable to open stats file";
           return RETURN_ERR_INVALID_STATS_FILE;
        }
        statsStream=new QTextStream(statsFile);

        dir.setNameFilters(QStringList() << SLOPE_FILE);
        dir.setFilter(QDir::Files);
        slopes=dir.entryList().first();
        slopeFile=new QFile(dir.path()+"/"+slopes);
        if (!slopeFile->open(QIODevice::ReadOnly | QIODevice::Text)){
           qWarning().nospace()<<"Unable to open slope file";
           return RETURN_ERR_INVALID_SLOPE_FILE;
        }
        slopeStream=new QTextStream(slopeFile);

        profiling=outputDir+"/"+PROFILING_FILE;
        profilingFile=new QFile(profiling);
        if (!profilingFile->open(QIODevice::ReadWrite | QIODevice::Text)){
           qWarning().nospace()<<"Unable to open profiling file";
           return RETURN_ERR_INVALID_PROFILING_FILE;
        }
        profilingStream=new QTextStream(profilingFile);

        dir.setNameFilters(QStringList() << PRV_INPUT_FILE);
        dir.setFilter(QDir::Files);
        inputPrvFiles=new PrvFileManager();
        if ((error=inputPrvFiles->initStreams(dir.path()+"/"+dir.entryList().first(), QIODevice::ReadOnly | QIODevice::Text))!=RETURN_OK){
            qWarning().nospace()<<"Unable to open input trace file";
            return RETURN_ERR_INVALID_INPUT_TRACE;
        }
        QString inputPrvBaseName=inputPrvFiles->getPrv();
        QFileInfo fileInfo=QFileInfo(inputPrvBaseName);
        inputPrvBaseName=fileInfo.completeBaseName();
        QString outputPrv=outputDir+"/"+inputPrvBaseName+RRI_DIR_PATTERN+RRI_PRV_PATTERN;
        if ((error=PrvFileManager::copyTrace(inputPrvFiles->getPrv(), outputPrv))!=RETURN_OK){
            qWarning().nospace()<<"Unable to generate output trace file";
            return RETURN_ERR_COPY_TRACE;
        }
        outputPrvFiles=new PrvFileManager();
        if ((error=outputPrvFiles->initStreams(outputPrv, QIODevice::ReadWrite | QIODevice::Text | QIODevice::Append))!=RETURN_OK){
            qWarning().nospace()<<"Unable to open output trace file";
            return RETURN_ERR_INVALID_OUTPUT_TRACE;
        }
    }
    return RETURN_OK;
}

QTextStream *FileManager::getProfilingStream() const
{
    return profilingStream;
}

QTextStream *FileManager::getSlopeStream() const
{
    return slopeStream;
}

QTextStream *FileManager::getStatsStream() const
{
    return statsStream;
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



