#ifndef RRIREDISTRIBUTEDMODEL_H
#define RRIREDISTRIBUTEDMODEL_H

#include <QMap>
#include <QVector>

#include "redistributedmodel.h"
#include "omacroscopicmodel.h"
#include "rrimicroscopicmodel.h"
#include "rripart.h"

class RRIRedistributedModel : public RedistributedModel
{
public:
    RRIRedistributedModel();
    RRIRedistributedModel(MicroscopicModel* microscopicModel, MacroscopicModel* macroscopicModel);
    void setMicroscopicModel(MicroscopicModel *value);
    void setMacroscopicModel(MacroscopicModel *value);
    void generateRoutines(float minPercentage);
private:
    RRIMicroscopicModel* rRIMicroscopicModel;
    OMacroscopicModel* oMacroscopicModel;
    QMap<float, int> codelines;
    QVector<RRIPart*> rRIParts;
    QMap<RRIPart*, int> mainRoutineMap;

};

#endif // RRIREDISTRIBUTEDMODEL_H
