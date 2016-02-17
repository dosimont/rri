#ifndef REDISTRIBUTEDMODEL_H
#define REDISTRIBUTEDMODEL_H

#include <QMap>
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
    virtual QMap<Part*, QString> getParts()=0;
protected:
    MicroscopicModel* microscopicModel;
    MacroscopicModel* macroscopicModel;
    QMap<Part*, QString> partMap;
};

#endif // REDISTRIBUTEDMODEL_H
