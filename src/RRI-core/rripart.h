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
