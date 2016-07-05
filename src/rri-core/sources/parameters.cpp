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

#include "parameters.h"

Parameters::Parameters()
{
    analysisType=rri::DEFAULT;
    normalize=DEFAULT_PARAMETER_NORMALIZE;
    threshold=DEFAULT_PARAMETER_THRESHOLD;
    p=DEFAULT_PARAMETER_PARAMETER;
    timesliceNumber=DEFAULT_PARAMETER_TIMESLICENUMBER;
}

InputFileType Parameters::getAnalysisType() const
{
    return analysisType;
}

void Parameters::setAnalysisType(const InputFileType &value)
{
    analysisType = value;
}

bool Parameters::getNormalize() const
{
    return normalize;
}

void Parameters::setNormalize(bool value)
{
    normalize = value;
}

float Parameters::getThreshold() const
{
    return threshold;
}

void Parameters::setThreshold(float value)
{
    threshold = value;
}

int Parameters::getTimesliceNumber() const
{
    return timesliceNumber;
}

void Parameters::setTimesliceNumber(int value)
{
    timesliceNumber = value;
}

float Parameters::getP() const
{
    return p;
}

void Parameters::setP(float value)
{
    p = value;
}

QTextStream *Parameters::getStream() const
{
    return stream;
}

void Parameters::setStream(QTextStream *value)
{
    stream = value;
}

float Parameters::getMinprop() const
{
    return minprop;
}

void Parameters::setMinprop(float value)
{
    minprop = value;
}
