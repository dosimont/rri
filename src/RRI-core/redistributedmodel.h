#ifndef REDISTRIBUTEDMODEL_H
#define REDISTRIBUTEDMODEL_H

#include "microscopicmodel.h"
#include "macroscopicmodel.h"

class RedistributedModel
{
public:
    RedistributedModel();
    RedistributedModel(MicroscopicModel* microscopicModel, MacroscopicModel* macroscopicModel);
    MicroscopicModel *getMicroscopicModel() const;
    void setMicroscopicModel(MicroscopicModel *value);
    MacroscopicModel *getMacroscopicModel() const;
    void setMacroscopicModel(MacroscopicModel *value);
protected:
    MicroscopicModel* microscopicModel;
    MacroscopicModel* macroscopicModel;
};

#endif // REDISTRIBUTEDMODEL_H
