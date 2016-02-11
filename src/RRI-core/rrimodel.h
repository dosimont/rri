#ifndef RRIMODEL_H
#define RRIMODEL_H

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

class RRIModel : public MicroscopicModel
{
public:
    RRIModel();
    RRIModel(MicroscopicModel);
    ~RRIModel();
    void parseFile(QString fileName, int timeSlices);
private:
    RRIObject* buildRRIObject(QStringList fields);
    void buildWithoutPreAggregation();
    void buildWithPreAggregation(int timeSlices);
    QVector<RRIObject*>* objects;
    BiQMap<int, int> routineMap;
    void addToMicroscopicModel(RRIObject* object);
    void addToPreAggregateMicroscopicModel(RRIObject* object, int timeslice);
};

#endif // RRIMODEL_H
