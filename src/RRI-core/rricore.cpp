#include "rricore.h"

RRICore::RRICore():parameters(new Parameters())
{

}

void RRICore::buildMicroscopicModel()
{
    QFileInfo fileInfo(parameters->getCurrentFileName());
    if (fileInfo.completeSuffix().compare(FILE_EXT_RRI)){
        parameters->setAnalysisType(InputData::RRI);
        microscopicModel=new RRIModel();
        RRIModel *castModel=dynamic_cast<RRIModel*>(microscopicModel);
        castModel->parseFile(parameters->getCurrentFileName());
    }
}

void RRICore::initMacroscopicModels()
{
    switch (parameters->getAnalysisType()){
       case InputData::RRI:macroscopicModel=new OMacroscopicModel(microscopicModel);
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

MacroscopicModel *RRICore::getMacroscopicModel() const
{
    return macroscopicModel;
}

MicroscopicModel *RRICore::getMicroscopicModel() const
{
    return microscopicModel;
}
