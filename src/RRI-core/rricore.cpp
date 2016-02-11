#include "rricore.h"

RRICore::RRICore():parameters(new Parameters())
{

}

bool RRICore::buildMicroscopicModel()
{
    QFileInfo fileInfo(parameters->getCurrentFileName());
    if (fileInfo.suffix().compare(FILE_EXT_RRI)==0){
        parameters->setAnalysisType(InputData::RRI);
        microscopicModel=new RRIModel();
        RRIModel *castModel=dynamic_cast<RRIModel*>(microscopicModel);
        castModel->parseFile(parameters->getCurrentFileName(), parameters->getTimesliceNumber());
        return true;
    }else{
        return false;
    }
}

void RRICore::initMacroscopicModels()
{
    switch (parameters->getAnalysisType()){
       case InputData::RRI:macroscopicModel=new OMacroscopicModel(microscopicModel);
        macroscopicModel->initializeAggregator();
        break;
       case InputData::DEFAULT:;
    }
}

void RRICore::buildMacroscopicModels()
{
    macroscopicModel->computeQualities(parameters->getNormalize());
    macroscopicModel->computeBestPartitions(parameters->getThreshold());
}

void RRICore::selectMacroscopicModel()
{
    macroscopicModel->computeBestPartition(parameters->getParameter());
}

Parameters* RRICore::getParameters() const
{
    return parameters;
}

QVector<Part*> RRICore::getParts()
{
    return dynamic_cast<OMacroscopicModel*>(macroscopicModel)->getParts();
}

MacroscopicModel *RRICore::getMacroscopicModel() const
{
    return macroscopicModel;
}

MicroscopicModel *RRICore::getMicroscopicModel() const
{
    return microscopicModel;
}
