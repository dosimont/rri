#ifndef RRIMODEL_H
#define RRIMODEL_H

#include <QObject>
#include <QFile>
#include <exception>
#include "microscopicmodel.h"

class RRIModel : public MicroscopicModel
{
public:
    RRIModel();
    void parseFile(QString fileName);
};

#endif // RRIMODEL_H
