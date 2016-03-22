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
    QVector<int> getPartsAsIndex();
    bool hasVoid();
    QVector<RRIPart *> getRRIParts() const;

private:
    RRIMicroscopicModel* rRIMicroscopicModel;
    OMacroscopicModel* oMacroscopicModel;
    QVector<RRIPart*> rRIParts;
    QMap<RRIPart*, RRIRoutineInfo*> mainRoutineMap;
    QVector<QString> partsAsString;
    QVector<int> partsAsInteger;
    QVector<int> partsAsIndex;
    bool hv;
};

#endif // RRIREDISTRIBUTEDMODEL_H
