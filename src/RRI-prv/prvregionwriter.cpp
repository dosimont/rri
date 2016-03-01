#include "prvregionwriter.h"

PrvRegionWriter::PrvRegionWriter():parser(new RegionParser()), routineValueCounter(0)
{

}

void PrvRegionWriter::setEventTypeBlockItems()
{
    int i=0;
    for (Region region:parser->getRegionMap().values){
        QString basename=BASENAME_RRI+i++;
        block.addItem(0, basename, region.getName());
        mapBaseName.insert(region.getName(), basename);
    }
    block.getValues().push_back(new EventTypeValue(routineValueCounter, "End"));
}

void PrvRegionWriter::pushRRIRegion(QString region, RRICore *core)
{
    QTextStream* output=outputPrvFile->getPrvStream();
    QVector<Part*> parts=core->getParts();
    for (int i=0; i< parts.size(); i++){
        if (block.getValues()(core->getRedistributedModel()->getPartsAsStrings()[j]
    }
}

void PrvRegionWriter::parseRegions(QTextStream regionStream)
{
    parser->buildRegions(regionStream);
}

PrvFileManager *PrvRegionWriter::getInputPrvFile() const
{
    return inputPrvFile;
}

void PrvRegionWriter::setInputPrvFile(PrvFileManager *value)
{
    inputPrvFile = value;
}

PrvFileManager *PrvRegionWriter::getOutputPrvFile() const
{
    return outputPrvFile;
}

void PrvRegionWriter::setOutputPrvFile(PrvFileManager *value)
{
    outputPrvFile = value;
}
