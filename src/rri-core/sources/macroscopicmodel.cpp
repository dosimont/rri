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

#include "macroscopicmodel.h"

MacroscopicModel::MacroscopicModel()
{

}

MacroscopicModel::MacroscopicModel(MicroscopicModel* microscopicModel):
    microscopicModel(microscopicModel)
{

}

MacroscopicModel::~MacroscopicModel()
{

}

MicroscopicModel *MacroscopicModel::getMicroscopicModel() const
{
    return microscopicModel;
}

void MacroscopicModel::setMicroscopicModel(MicroscopicModel *value)
{
    microscopicModel = value;
}

QVector<Quality *> MacroscopicModel::getQualities() const
{
    return qualities;
}

QVector<float> MacroscopicModel::getPs() const
{
    return ps;
}

double MacroscopicModel::getAggregationScore()
{
    double score=0.0;
    for (int i=0; i<getPs().size()-1; i++){
        score+=(getQualities().at(i+1)->getGain()-getQualities().at(i)->getGain())*(getQualities().at(i+1)->getLoss()+getQualities().at(i)->getLoss())/2;
    }
    return score;
}
