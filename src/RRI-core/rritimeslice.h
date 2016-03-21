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
