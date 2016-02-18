#include "redistributedmodel.h"

RedistributedModel::RedistributedModel():partsAsStrings(QVector<QString>())
{

}

RedistributedModel::RedistributedModel(MicroscopicModel *microscopicModel, MacroscopicModel *macroscopicModel):microscopicModel(microscopicModel), macroscopicModel(macroscopicModel), partsAsStrings(QVector<QString>())
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
