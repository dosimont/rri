#include "omacroscopicmodel.h"

OMacroscopicModel::OMacroscopicModel()
{

}

void OMacroscopicModel::initializeAggregator()
{
    lpaggreg=OLPAggreg3(microscopicModel->getMicroscopicModel());

}

void OMacroscopicModel::computeQualities(bool normalize)
{
    lpaggreg.computeQualities(normalize);
}

void OMacroscopicModel::computeBestPartitions(float threshold)
{
    parameters=QVector::fromStdVector(lpaggreg.getParameters(threshold));
    qualities=QVector::fromStdVector(lpaggreg.getQualityList());
}

void OMacroscopicModel::computeBestPartition(float parameter)
{
    vector<int>partsTemp=lpaggreg.getParts(parameter);
    parts=QVector<Part*>();
    Part* currentPart=new Part();
    currentPart->setFirstTimeSlice(0);
    int currentPartIndice=0;
    unsigned int i=0;
    for (i=0;i<partsTemp.size()-1;i++){
        if (partsTemp[i+1]!=currentPartIndice){
            currentPart->setLastTimeSlice(i);
            parts.append(currentPart);
            currentPart=new Part();
            currentPart->setFirstTimeSlice(i+1);
            currentPartIndice=partsTemp[i+1];
        }

    }
    currentPart->setLastTimeSlice(i);
    parts.append(currentPart);
}

MicroscopicModel *OMacroscopicModel::getMicroscopicModel() const
{
    return microscopicModel;
}

void OMacroscopicModel::setMicroscopicModel(MicroscopicModel *value)
{
    microscopicModel = value;
}
