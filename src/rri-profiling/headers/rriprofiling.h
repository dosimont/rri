#ifndef RRIPROFILING_H
#define RRIPROFILING_H

#include "slopeparser.h"
#include "statsparser.h"
#include "routineprofile.h"
#include "rricore.h"
#include "rripart.h"
#include <QString>
#include <QTextStream>

class RRIProfiling
{
public:
    RRIProfiling();
    ~RRIProfiling();
    void parse();
    void writeStream();
    void computeRoutines(QString region, RRICore *core);
    RRIProfiling(QTextStream* statsStream, QTextStream* slopeStream, QTextStream* profilingStream);
private:
    void parseSlope();
    void parseStats();
    QMap<QString, RoutineProfile*> routineProfiles;
    SlopeParser *slopeParser;
    StatsParser *statsParser;
    QTextStream *statsStream;
    QTextStream *slopeStream;
    QTextStream *profilingStream;
};

#endif // RRIPROFILING_H
