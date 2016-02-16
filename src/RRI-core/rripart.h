#ifndef RRIPART_H
#define RRIPART_H

#include <QVector>
#include <vector>
#include "part.h"
#include "rriobject.h"

using std::vector;

class RRIPart : public Part
{
public:
    RRIPart(Part* part);

    int getRoutineNumber() const;
    void setRoutinesFromMicroscopicModel(vector< vector< vector <double> > > matrix);
    QVector<float> getRoutines() const;

private:
    int routineNumber;
    QVector<float> routines;

};

#endif // RRIPART_H
