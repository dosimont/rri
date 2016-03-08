#include "redistributedmodel.h"

RedistributedModel::RedistributedModel()
{

}

RedistributedModel::RedistributedModel(MicroscopicModel *microscopicModel, MacroscopicModel *macroscopicModel):microscopicModel(microscopicModel), macroscopicModel(macroscopicModel)
{

}

MicroscopicModel *RedistributedModel::getMicroscopicModel() const
{
    return microscopicModel;
}

void RedistributedModel::setMicroscopicModel(MicroscopicModel *value)
{
    microscopicModel = value;
}

MacroscopicModel *RedistributedModel::getMacroscopicModel() const
{
    return macroscopicModel;
}

void RedistributedModel::setMacroscopicModel(MacroscopicModel *value)
{
    macroscopicModel = value;
}
