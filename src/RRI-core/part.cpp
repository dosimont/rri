#include "part.h"

Part::Part():firstTimeSlice(0), lastTimeSlice(0), totalTimeSlice(1)
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
    return (double) firstRelative/(double) totalTimeSlice;
}

double Part::getLastRelative() const
{
    return (double) (lastRelative+1)/(double) totalTimeSlice;
}

double Part::getSizeRelative() const
{
    return getLastRelative()-getFirstRelative();
}
