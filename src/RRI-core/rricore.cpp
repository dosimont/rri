#include "rricore.h"

RRICore::RRICore()
{

}

void RRICore::buildMicroscopicModel()
{
    QFileInfo fileInfo(parameters.getCurrentFileName());
    if (fileInfo.completeSuffix().compare(FILE_EXT_RRI)){
        parameters.setAnalysisType(RRI);
        microscopicModel=RRIModel();
        ((RRIModel) microscopicModel).parseFile(parameters.getCurrentFileName());
    }
}

void RRICore::initMacroscopicModels()
{
    switch (analysisType){
       case RRI:macroscopicModel=OMacroscopicModel(microscopicModel);
        break;
       case DEFAULT:;
    }
}

void RRICore::buildMacroscopicModels()
{
    macroscopicModel.computeQualities(parameters.getNormalize());
    macroscopicModel.computeBestPartitions(parameters.getThreshold());
}

Parameters RRICore::getParameters() const
{
    return parameters;
}
