#ifndef RRICORE_H
#define RRICORE_H

#include <QObject>
#include <QFileInfo>
#include <QVector>
#include "rricore_global.h"
#include "constants.h"
#include "rrimodel.h"
#include "omacroscopicmodel.h"
#include "parameters.h"
#include "debug.h"
#include "part.h"

using InputData::DataType;

class CORESHARED_EXPORT RRICore
{

public:
    RRICore();
    bool buildMicroscopicModel();
    void initMacroscopicModels();
    void buildMacroscopicModels();
    void selectMacroscopicModel();
    float getCurrentP();
    float nextP();
    float previousP();
    Parameters* getParameters() const;
    QVector<Part*> getParts();
    MacroscopicModel* getMacroscopicModel() const;
    MicroscopicModel* getMicroscopicModel() const;

private:
    Parameters* parameters;
    MicroscopicModel* microscopicModel;
    MacroscopicModel* macroscopicModel;
    int currentPIndex;
};

#endif // RRICORE_H
