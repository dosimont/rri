#ifndef REDISTRIBUTEDMODEL_H
#define REDISTRIBUTEDMODEL_H

#include <QVector>
#include <QString>

#include "microscopicmodel.h"
#include "macroscopicmodel.h"
#include "part.h"

class RedistributedModel
{
public:
    RedistributedModel();
    RedistributedModel(MicroscopicModel* microscopicModel, MacroscopicModel* macroscopicModel);
    virtual ~RedistributedModel() {}
    MicroscopicModel *getMicroscopicModel() const;
    void setMicroscopicModel(MicroscopicModel *value);
    MacroscopicModel *getMacroscopicModel() const;
    void setMacroscopicModel(MacroscopicModel *value);
    virtual QVector<QString> getPartsAsString()=0;
    virtual QVector<int> getPartsAsInteger()=0;
    virtual QVector<int> getPartsAsIndex()=0;
    virtual bool hasVoid()=0;
protected:
    MicroscopicModel* microscopicModel;
    MacroscopicModel* macroscopicModel;
};

#endif // REDISTRIBUTEDMODEL_H
