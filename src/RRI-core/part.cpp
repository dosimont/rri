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

#include "part.h"

Part::Part():firstTimeSlice(0), lastTimeSlice(0), totalTimeSlice(1)
{

}

Part::Part(int totalTimeSlice):firstTimeSlice(0), lastTimeSlice(0), totalTimeSlice(totalTimeSlice)
{

}

int Part::getFirstTimeSlice() const
{
    return firstTimeSlice;
}

void Part::setFirstTimeSlice(int value)
{
    firstTimeSlice = value;
}

int Part::getLastTimeSlice() const
{
    return lastTimeSlice;
}

void Part::setLastTimeSlice(int value)
{
    lastTimeSlice = value;
}

int Part::getSizeTimeSlice() const
{
    return lastTimeSlice-firstTimeSlice+1;
}

int Part::getTotalTimeSlice() const
{
    return totalTimeSlice;
}

void Part::setTotalTimeSlice(int value)
{
    totalTimeSlice = value;
}

double Part::getFirstRelative() const
{
    return (double) firstTimeSlice/(double) totalTimeSlice;
}

double Part::getLastRelative() const
{
    return (double) (lastTimeSlice+1)/(double) totalTimeSlice;
}

double Part::getSizeRelative() const
{
    return getLastRelative()-getFirstRelative();
}
