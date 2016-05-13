#include "rriprofiling.h"

RRIProfiling::RRIProfiling():slopeParser(new slopeParser()), statsParser(new statsParser())
{

}

void RRIProfiling::parseSlope(QTextStream *stream)
{
    slopeParser->buildSlopes(stream);
}

void RRIProfiling::parseStats(QTextStream *stream)
{
    statsParser->buildStats(stream);
}

void RRIProfiling::writeStream(QTextStream *stream)
{
    for (RoutineProfile routineProfile:routineProfiles.values()){
        stream<<routineProfile;
    }
}
