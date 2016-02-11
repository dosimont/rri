#include "rricore.h"

RRICore::RRICore():parameters(new Parameters())
{

}

bool RRICore::buildMicroscopicModel()
{
    QFileInfo fileInfo(parameters->getCurrentFileName());
    if (fileInfo.suffix().compare(FILE_EXT_RRI)){
        RRILOG("Extension Type is RRI");
        parameters->setAnalysisType(InputData::RRI);
        RRILOG("Analysis Type has been set");
        microscopicModel=new RRIModel();
        RRILOG("RRIModel has been instancied");
        RRIModel *castModel=dynamic_cast<RRIModel*>(microscopicModel);
        RRILOG("RRIModel dynamic cast");
        castModel->parseFile(parameters->getCurrentFileName());
        RRILOG("Parsing has been done");
    }else{
        RRILOG("Extension Type is unknown");
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

MacroscopicModel *RRICore::getMacroscopicModel() const
{
    return macroscopicModel;
}

MicroscopicModel *RRICore::getMicroscopicModel() const
{
    return microscopicModel;
}
