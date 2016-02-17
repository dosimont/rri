#include "redistributedmodel.h"

RedistributedModel::RedistributedModel():partMap(QMap<Part*, QString>())
{

}

RedistributedModel::RedistributedModel(MicroscopicModel *microscopicModel, MacroscopicModel *macroscopicModel):microscopicModel(microscopicModel), macroscopicModel(macroscopicModel), partMap(QMap<Part*, QString>())
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
