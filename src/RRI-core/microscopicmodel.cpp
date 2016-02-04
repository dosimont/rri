#include "microscopicmodel.h"

MicroscopicModel::MicroscopicModel():currentFileName(""),matrix(vector< vector< vector<double> > >())
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
