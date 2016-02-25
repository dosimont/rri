#include "microscopicmodel.h"

MicroscopicModel::MicroscopicModel():matrix(vector< vector< vector<double> > >())
{

}

MicroscopicModel::~MicroscopicModel()
{

}

vector<vector<vector<double> > > MicroscopicModel::getMatrix() const
{
    return matrix;
}

void MicroscopicModel::setMatrix(const vector<vector<vector<double> > > &value)
{
    matrix = value;
}
