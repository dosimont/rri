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
protected:
    QString currentFileName;
    vector< vector< vector<double> > > microscopicModel;
};

#endif // MICROSCOPICMODEL_H
