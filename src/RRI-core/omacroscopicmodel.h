#ifndef OMACROSCOPICMODEL_H
#define OMACROSCOPICMODEL_H

#include "macroscopicmodel.h"
#include "part.h"
#include <lpaggreg/OLPAggreg3.h>

class OMacroscopicModel : public MacroscopicModel
{
public:
    OMacroscopicModel();
    OMacroscopicModel(MicroscopicModel* microscopicModel);
    void initializeAggregator();
    void computeQualities(bool normalize);
    void computeBestPartitions(float threshold);
    void computeBestPartition(float parameter);

private:
    OLPAggreg3 lpaggreg;
    QVector<Part*> parts;
};

#endif // OMACROSCOPICMODEL_H
