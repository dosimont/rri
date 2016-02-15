#include "macroscopicmodel.h"

MacroscopicModel::MacroscopicModel()
{

}

MacroscopicModel::MacroscopicModel(MicroscopicModel* microscopicModel):
    microscopicModel(microscopicModel)
{

}

MacroscopicModel::~MacroscopicModel()
{

}

MicroscopicModel *MacroscopicModel::getMicroscopicModel() const
{
    return microscopicModel;
}

void MacroscopicModel::setMicroscopicModel(MicroscopicModel *value)
{
    microscopicModel = value;
}

QVector<Quality *> MacroscopicModel::getQualities() const
{
    return qualities;
}

QVector<float> MacroscopicModel::getPs() const
{
    return ps;
}
