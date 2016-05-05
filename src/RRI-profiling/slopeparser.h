#ifndef SLOPEPARSER_H
#define SLOPEPARSER_H

#include <QMap>
#include <QString>
#include <QTextStream>
#include "slope.h"
#include "profiling_constants.h"
#include "rricsv.h"


class SlopeParser
{
public:
    SlopeParser();
    ~SlopeParser();
    int buildSlopes(QTextStream* stream);
private:
    int addToSlope(QStringList stringList);
    QMap<QString,QMap<QString, Slope*>> slopes;
};

#endif // SLOPEPARSER_H
