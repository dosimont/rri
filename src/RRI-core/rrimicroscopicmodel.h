#ifndef RRIMICROSCOPICMODEL_H
#define RRIMICROSCOPICMODEL_H

#include <QObject>
#include <QFile>
#include <QVector>
#include <QString>
#include <QStringList>
#include <QTextStream>
#include <vector>
#include "microscopicmodel.h"
#include "rriobject.h"
#include "rristreamreader.h"
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
    void generate(QTextStream stream, int timeSlices);
    BiQMap<int, int> getMatrixIndexToRoutineId() const;
    QVector<RRITimeSlice*> getTimeSlices() const;

private:
    RRIObject* buildRRIObject(QStringList fields);
    RRIObject* buildRRIObject(QStringList fields, int line);
    void build(int timeSlices);
    void addToMicroscopicModel(RRIObject* object, int timeSlice);
    QVector<RRIObject*> objects;
    QVector<RRITimeSlice*> timeSlices;
    BiQMap<int, int> matrixIndexToRoutineId;
};

#endif // RRIMICROSCOPICMODEL_H
