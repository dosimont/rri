#ifndef CORE_H
#define CORE_H

#include <QObject>
#include <QFileInfo>
#include "constants.h"

class Core
{

public:
    Core();
    QString getCurrentFileName() const;
    void setCurrentFileName(const QString &value);
    void parseCurrentFile();

private:
    QString currentFileName;
};

#endif // CORE_H
