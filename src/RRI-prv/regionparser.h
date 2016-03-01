#ifndef REGIONPARSER_H
#define REGIONPARSER_H

#include <QTextStream>
#include <QString>
#include <QStringList>
#include <QMap>

#include "region.h"
#include "dummystreamreader.h"
#include "prv_constants.h"

class RegionParser
{
public:
    RegionParser();
    ~RegionParser();
    void buildRegions(QTextStream stream);
    QMap<QString, Region *> getRegionMap() const;

protected:
    Region* buildRegion(QStringList stringList);
    QMap<QString, Region*> regionMap;

};

#endif // REGIONPARSER_H
