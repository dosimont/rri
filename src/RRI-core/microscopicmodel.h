#ifndef MICROSCOPICMODEL_H
#define MICROSCOPICMODEL_H

#include <QObject>

class MicroscopicModel
{
public:
    MicroscopicModel();
    virtual void parseFile(QString fileName)=0;

protected:
    QString currentFileName;
};

#endif // MICROSCOPICMODEL_H
