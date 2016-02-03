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

using std::vector;

class RRIModel : public MicroscopicModel
{
public:
    RRIModel();
    ~RRIModel();
    void parseFile(QString fileName);
private:
    QVector<RRIObject*>* objects;
    BiQMap<int, int> routineMap;
    void addToMicroscopicModel(RRIObject* object);
};

#endif // RRIMODEL_H
