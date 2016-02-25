#ifndef MICROSCOPICMODEL_H
#define MICROSCOPICMODEL_H

#include <QObject>
#include <QTextStream>
#include <vector>

using std::vector;

class MicroscopicModel
{
public:
    MicroscopicModel();
    virtual ~MicroscopicModel();

    vector<vector<vector<double> > > getMatrix() const;
    void setMatrix(const vector<vector<vector<double> > > &value);

protected:
    QTextStream *stream;
    vector< vector< vector<double> > > matrix;
};

#endif // MICROSCOPICMODEL_H
