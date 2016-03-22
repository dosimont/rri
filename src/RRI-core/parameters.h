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

#ifndef PARAMETERS_H
#define PARAMETERS_H

#include "core_constants.h"
#include <QString>
#include <QTextStream>

using rri::InputFileType;

class Parameters
{
public:
    Parameters();

    InputFileType getAnalysisType() const;
    void setAnalysisType(const InputFileType &value);

    bool getNormalize() const;
    void setNormalize(bool value);

    float getThreshold() const;
    void setThreshold(float value);

    int getTimesliceNumber() const;
    void setTimesliceNumber(int value);

    float getP() const;
    void setP(float value);

    QTextStream *getStream() const;
    void setStream(QTextStream *value);

    float getMinprop() const;
    void setMinprop(float value);

private:
    QTextStream *stream;
    InputFileType analysisType;
    bool normalize;
    float threshold;
    float minprop;
    float p;
    int timesliceNumber;
};

#endif // PARAMETERS_H
