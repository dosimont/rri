#ifndef MACROSCOPICMODEL_H
#define MACROSCOPICMODEL_H

#include "microscopicmodel.h"
#include <QMap>

class MacroscopicModel
{
public:
    MacroscopicModel();
    MacroscopicModel(MicroscopicModel microscopicModel);
    virtual void computeQualities(bool normalize)=0;
    virtual void computeBestPartitions(float threshold)=0;
    virtual void computeBestPartition(float parameter)=0;
private:
    QMap<float, double> informationLoss;
    QMap<float, double> complexityReduction;
    MicroscopicModel* microscopicModel;
};

#endif // MACROSCOPICMODEL_H
