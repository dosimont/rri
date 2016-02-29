#ifndef RRICORE_H
#define RRICORE_H

#include <QObject>
#include <QFileInfo>
#include <QVector>
#include <QDebug>

#include "rricore_global.h"
#include "core_constants.h"
#include "rrimicroscopicmodel.h"
#include "omacroscopicmodel.h"
#include "redistributedmodel.h"
#include "rriredistributedmodel.h"
#include "parameters.h"
#include "debug.h"
#include "part.h"

using rri::InputFileType;

class CORESHARED_EXPORT RRICore
{

public:
    RRICore();
    ~RRICore();
    bool buildMicroscopicModel();
    void initMacroscopicModels();
    void buildMacroscopicModels();
    void selectMacroscopicModel();
    void buildRedistributedModel();
    Parameters* getParameters() const;
    QVector<Part*> getParts();
    MacroscopicModel* getMacroscopicModel() const;
    MicroscopicModel* getMicroscopicModel() const;
    RedistributedModel *getRedistributedModel() const;

    float getCurrentP();
    float nextP();
    float previousP();
    int getCurrentPIndex() const;
    void setCurrentPIndex(int value);
    void setP(rri::PDefaultValue defaultValue);
    void setP(float value);
    QVector<float> getPs() const;

private:
    void setNormInflect();

    Parameters* parameters;
    MicroscopicModel* microscopicModel;
    MacroscopicModel* macroscopicModel;
    RedistributedModel* redistributedModel;
    bool microscopicModelAllocated;
    bool macroscopicModelAllocated;
    bool redistributedModelAllocated;
    int currentPIndex;
};

#endif // RRICORE_H
