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

#ifndef RRITIMESLICE_H
#define RRITIMESLICE_H

#include <QVector>
#include <QMap>
#include "rriobject.h"
#include "rritimeslice.h"
#include "rriroutineinfo.h"

class RRITimeSlice
{
public:
    RRITimeSlice();
    ~RRITimeSlice();
    void addObject(RRIObject* object, int routine);
    void addObject(RRIObject* object);
    void finalize();
    void finalize(int count);
    int getSampleNumber();
    QMap<int, RRIRoutineInfo *> getRoutines() const;
    QVector<RRIObject *> getObjects() const;
    QVector<RRIObject *> getCompatibleObjects(int index) const;
private:
    QMap<int, RRIRoutineInfo*> routines;
    QVector<RRIObject*> objects;
};

#endif // RRITIMESLICE_H
