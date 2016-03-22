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

#ifndef RRIPART_H
#define RRIPART_H

#include <QMap>
#include "part.h"
#include "rriobject.h"
#include "rritimeslice.h"
#include "debug.h"

using std::vector;

class RRIPart : public Part
{
public:
    RRIPart(Part* part);
    ~RRIPart();
    void setRoutines(QVector<RRITimeSlice*> tS);
    QMap<int, RRIRoutineInfo*> getRoutines() const;
    QVector<RRIObject*> getCompatibleObjects(int index);

private:
    QVector<RRITimeSlice*> timeSlices;
    int routineNumber;
    QMap<int, RRIRoutineInfo*> routines;

};

#endif // RRIPART_H
