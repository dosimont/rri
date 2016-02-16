#ifndef REDISTRIBUTEDMODEL_H
#define REDISTRIBUTEDMODEL_H

#include "microscopicmodel.h"
#include "macroscopicmodel.h"

class RedistributedModel
{
public:
    RedistributedModel();
    MicroscopicModel *getMicroscopicModel() const;
    void setMicroscopicModel(MicroscopicModel *value);

    MacroscopicModel *getMacroscopicModel() const;
    void setMacroscopicModel(MacroscopicModel *value);

private:
    MicroscopicModel *microscopicModel;
    MacroscopicModel *macroscopicModel;
};

#endif // REDISTRIBUTEDMODEL_H
