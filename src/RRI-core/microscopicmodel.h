#ifndef MICROSCOPICMODEL_H
#define MICROSCOPICMODEL_H

#include <QObject>
#include <vector>

using std::vector;

class MicroscopicModel
{
public:
    MicroscopicModel();
    ~MicroscopicModel();

    vector<vector<vector<double> > > getMatrix() const;
    void setMatrix(const vector<vector<vector<double> > > &value);

protected:
    QString currentFileName;
    vector< vector< vector<double> > > matrix;
};

#endif // MICROSCOPICMODEL_H
