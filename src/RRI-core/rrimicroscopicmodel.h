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

using std::vector;

class RRIMicroscopicModel : public MicroscopicModel
{
public:
    RRIMicroscopicModel();
    RRIMicroscopicModel(MicroscopicModel);
    ~RRIMicroscopicModel();
    void parseFile(QString fileName, int timeSlices);
private:
    RRIObject* buildRRIObject(QStringList fields);
    void buildWithoutPreAggregation();
    void buildWithPreAggregation(int timeSlices);
    void addToMicroscopicModel(RRIObject* object);
    void addToPreAggregateMicroscopicModel(RRIObject* object, int timeslice);
    QVector<RRIObject*>* objects;
    BiQMap<int, int> routineMap;
};

#endif // RRIMICROSCOPICMODEL_H
