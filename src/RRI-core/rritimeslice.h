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
    ~RRITimeSlice();
    void addObject(RRIObject* object, int routine);
    void finalize();
    void finalize(int count);
    QMap<int, RRIRoutineInfo *> getRoutines() const;
    QVector<RRIObject *> getObjects() const;

private:
    QMap<int, RRIRoutineInfo*> routines;
    QVector<RRIObject*> objects;
    int samples;
};

#endif // RRITIMESLICE_H
