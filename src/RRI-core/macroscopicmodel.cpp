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

double MacroscopicModel::getAggregationScore()
{
    double score=0.0;
    for (int i=0; i<getPs().size()-1; i++){
        score+=(getQualities.at(i+1)->getGain()-getQualities.at(i)->getGain())*(getQualities.at(i+1)->getLoss()+getQualities.at(i)->getLoss())/2;
    }
    return 1.0-score;
}
