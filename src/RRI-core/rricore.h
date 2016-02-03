#ifndef RRICORE_H
#define RRICORE_H

#include <QObject>
#include <QFileInfo>
#include "rricore_global.h"
#include "constants.h"
#include "rrimodel.h"

class CORESHARED_EXPORT RRICore
{

public:
    RRICore();
    QString getCurrentFileName() const;
    void setCurrentFileName(const QString &value);
    void parseCurrentFile();
    void parseFile(const QString &value);

private:
    QString currentFileName;
    RRIModel currentModel;
};

#endif // RRICORE_H
