#ifndef RRITIMESLICE_H
#define RRITIMESLICE_H

#include <QVector>
#include <QMap>
#include "rriobject.h"
#include "rriroutineinfo.h"

class RRITimeSlice
{
public:
    RRITimeSlice();

    QVector<RRIObject*> getObjects() const;
    void addObject(RRIObject* object, int routine);
    void finalize();
    QMap<int, RRIRoutineInfo *> getRoutines() const;

private:
    QMap<int, RRIRoutineInfo*> routines;
    QVector<RRIObject*> objects;
    int samples;
};

#endif // RRITIMESLICE_H
