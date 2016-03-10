#ifndef RRIREDISTRIBUTEDMODEL_H
#define RRIREDISTRIBUTEDMODEL_H

#include <QMap>
#include <QVector>

#include "redistributedmodel.h"
#include "omacroscopicmodel.h"
#include "rrimicroscopicmodel.h"
#include "rripart.h"
#include "rriroutineinfo.h"
#include "rriobject.h"
#include "debug.h"

class RRIRedistributedModel : public RedistributedModel
{
public:
    RRIRedistributedModel();
    RRIRedistributedModel(MicroscopicModel* microscopicModel, MacroscopicModel* macroscopicModel);
    ~RRIRedistributedModel();
    void setMicroscopicModel(MicroscopicModel *value);
    void setMacroscopicModel(MacroscopicModel *value);
    QMap<RRIPart*, RRIRoutineInfo*> generateRoutines(double minPercentage);
    QVector<RRIObject*> generateCodelines();
    QVector<QString> getPartsAsString();
    QVector<int> getPartsAsInteger();
    QVector<RRIPart *> getRRIParts() const;

private:
    RRIMicroscopicModel* rRIMicroscopicModel;
    OMacroscopicModel* oMacroscopicModel;
    QVector<RRIPart*> rRIParts;
    QMap<RRIPart*, RRIRoutineInfo*> mainRoutineMap;
    QVector<QString> partsAsString;
    QVector<int> partsAsInteger;
};

#endif // RRIREDISTRIBUTEDMODEL_H
