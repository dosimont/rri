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
