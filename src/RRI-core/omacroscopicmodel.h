#ifndef OMACROSCOPICMODEL_H
#define OMACROSCOPICMODEL_H

#include "macroscopicmodel.h"
#include <lpaggreg/OLPAggreg3.h>

class OMacroscopicModel : public MacroscopicModel
{
public:
    OMacroscopicModel();
    OMacroscopicModel(MicroscopicModel microscopicModel);
private:
    OLPAggreg3 lpaggreg;
};

#endif // OMACROSCOPICMODEL_H
