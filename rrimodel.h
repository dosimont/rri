#ifndef RRIMODEL_H
#define RRIMODEL_H

#include <QObject>
#include <QFile>
#include <QVector>
#include <QStringList>
#include <vector>
#include "microscopicmodel.h"
#include "rriobject.h"
#include "csv.h"
#include "biqmap.h"

using std::vector;

class RRIModel : public MicroscopicModel
{
public:
    RRIModel();
    void parseFile(QString fileName);
private:
    QVector<RRIObject*>* objects;
    vector< vector<double> > microscopicModel;
    BiQMap<int, int> routineMap;
    void addToMicroscopicModel(RRIObject* object);
    //TODO destructor
};

#endif // RRIMODEL_H
