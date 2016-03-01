#ifndef PRVREGIONWRITER_H
#define PRVREGIONWRITER_H

#include <QString>
#include <QTextStream>
#include <QMap>

#include "prvfilemanager.h"
#include "regionparser.h"
#include "eventtypeblock.h"
#include "prv_constants.h"

#include "rriroutineinfo.h"

class PrvRegionWriter
{
public:
    PrvRegionWriter();
    void setEventTypeBlockItems();
    void pushRRIRegion(QString region, RRICore* core);
    void pushRRIEventTypeBlock();
    void parseRegions(QTextStream regionStream);
    PrvFileManager *getInputPrvFile() const;
    void setInputPrvFile(PrvFileManager *value);
    PrvFileManager *getOutputPrvFile() const;
    void setOutputPrvFile(PrvFileManager *value);

protected:
    PrvFileManager* inputPrvFile;
    PrvFileManager* outputPrvFile;
    RegionParser* parser;
    QMap<QString, int> mapBaseName;
    EventTypeBlock block;
    QMap<int,QString>routineValues;
    int routineValueCounter;


};

#endif // PRVREGIONWRITER_H
