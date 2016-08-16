/*  RRI - Relevant Routine Identifier
*  Copyright (C) 2016  Damien Dosimont
*  
*  This file is part of RRI.
*  
*  RRI is free software: you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation, either version 3 of the License, or
*  (at your option) any later version.
*  
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*  
*  You should have received a copy of the GNU General Public License
*  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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
    bool hasVoid();

private:
    void setNormInflect();
    void setNormInflect2();
    void setNormBest();
    Parameters* parameters;
    MicroscopicModel* microscopicModel;
    MacroscopicModel* macroscopicModel;
    RedistributedModel* redistributedModel;
    int currentPIndex;
};

#endif // RRICORE_H
