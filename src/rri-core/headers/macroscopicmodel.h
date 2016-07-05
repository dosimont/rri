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

#ifndef MACROSCOPICMODEL_H
#define MACROSCOPICMODEL_H

#include "microscopicmodel.h"
#include <lpaggreg/Quality.h>
#include <QVector>

class MacroscopicModel
{
public:
    MacroscopicModel();
    MacroscopicModel(MicroscopicModel* microscopicModel);
    virtual ~MacroscopicModel();
    virtual void initializeAggregator()=0;
    virtual void computeQualities(bool normalize)=0;
    virtual void computeBestPartitions(float threshold)=0;
    virtual void computeBestPartition(float parameter)=0;
    MicroscopicModel *getMicroscopicModel() const;
    void setMicroscopicModel(MicroscopicModel *value);
    QVector<Quality *> getQualities() const;
    QVector<float> getPs() const;
    double getAggregationScore();

protected:
    QVector<Quality*> qualities;
    QVector<float> ps;
    MicroscopicModel* microscopicModel;
};

#endif // MACROSCOPICMODEL_H
