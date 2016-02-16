#include "redistributedmodel.h"

RedistributedModel::RedistributedModel()
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
