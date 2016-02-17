#ifndef RRIREDISTRIBUTEDMODEL_H
#define RRIREDISTRIBUTEDMODEL_H

#include <QMap>
#include <QVector>

#include "redistributedmodel.h"
#include "omacroscopicmodel.h"
#include "rrimicroscopicmodel.h"
#include "rripart.h"
#include "debug.h"

class RRIRedistributedModel : public RedistributedModel
{
public:
    RRIRedistributedModel();
    RRIRedistributedModel(MicroscopicModel* microscopicModel, MacroscopicModel* macroscopicModel);
    ~RRIRedistributedModel();
    void setMicroscopicModel(MicroscopicModel *value);
    void setMacroscopicModel(MacroscopicModel *value);
    QMap<RRIPart*, int> generateRoutines(float minPercentage);
    QMap<Part *, QString> getParts();
private:
    RRIMicroscopicModel* rRIMicroscopicModel;
    OMacroscopicModel* oMacroscopicModel;
    QMap<float, int> codelines;
    QVector<RRIPart*> rRIParts;
    QMap<RRIPart*, int> mainRoutineMap;

};

#endif // RRIREDISTRIBUTEDMODEL_H
