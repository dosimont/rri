#ifndef MACROSCOPICMODEL_H
#define MACROSCOPICMODEL_H

#include "microscopicmodel.h"
#include <lpaggreg/Quality.h>
#include <QVector>

class MacroscopicModel
{
public:
    MacroscopicModel(MicroscopicModel* microscopicModel);
    virtual ~MacroscopicModel();
    virtual void initializeAggregator()=0;
    virtual void computeQualities(bool normalize)=0;
    virtual void computeBestPartitions(float threshold)=0;
    virtual void computeBestPartition(float parameter)=0;
    MicroscopicModel *getMicroscopicModel() const;
    void setMicroscopicModel(MicroscopicModel *value);
    QVector<Quality *> getQualities() const;
    QVector<float> getPs() const;

protected:
    QVector<Quality*> qualities;
    QVector<float> ps;
    MicroscopicModel* microscopicModel;
};

#endif // MACROSCOPICMODEL_H
