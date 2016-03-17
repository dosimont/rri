#include "microscopicmodel.h"

MicroscopicModel::MicroscopicModel():matrix(new vector< vector< vector<double> > >())
{

}

MicroscopicModel::~MicroscopicModel()
{
    delete matrix;
}

vector<vector<vector<double> > > *MicroscopicModel::getMatrix() const
{
    return matrix;
}

void MicroscopicModel::setMatrix(vector<vector<vector<double> > > *value)
{
    matrix = value;
}

