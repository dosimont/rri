#ifndef RRIMICROSCOPICMODEL_H
#define RRIMICROSCOPICMODEL_H

#include <QObject>
#include <QFile>
#include <QVector>
#include <QString>
#include <QStringList>
#include <vector>
#include "microscopicmodel.h"
#include "rriobject.h"
#include "csv.h"
#include "biqmap.h"
#include "constants.h"
#include "debug.h"
#include "rritimeslice.h"

using std::vector;

class RRIMicroscopicModel : public MicroscopicModel
{
public:
    RRIMicroscopicModel();
    RRIMicroscopicModel(MicroscopicModel);
    ~RRIMicroscopicModel();
    void parseFile(QString fileName, int timeSlices);
    BiQMap<int, int> getMatrixIndexToRoutineId() const;
    QVector<RRITimeSlice*> getTimeSlices() const;

private:
    RRIObject* buildRRIObject(QStringList fields);
    void buildWithoutPreAggregation();
    void buildWithPreAggregation(int timeSlices);
    void addToMicroscopicModel(RRIObject* object);
    void addToPreAggregateMicroscopicModel(RRIObject* object, int timeslice);
    QVector<RRIObject*> objects;
    QVector<RRITimeSlice*> timeSlices;
    BiQMap<int, int> matrixIndexToRoutineId;
};

#endif // RRIMICROSCOPICMODEL_H
