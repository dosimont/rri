/*  RRI - Relevant Routine Identifier
*  Copyright (C) 2016  Damien Dosimont
*  
*  This file is part of RRI.
*  
*  RRI is free software: you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation, either version 3 of the License, or
*  (at your option) any later version.
*  
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*  
*  You should have received a copy of the GNU General Public License
*  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "eventtypeitem.h"
#include "prvregionwriter.h"

PrvRegionWriter::PrvRegionWriter():parser(new RegionParser()), block(new EventTypeBlock())
{

}

PrvRegionWriter::~PrvRegionWriter()
{
    delete block;
    delete parser;
}

void PrvRegionWriter::setEventTypeBlockItems()
{
    //int i=0;
    int basename=BASENAME_RRI;
    for (Region* region : parser->getRegionMap().values()){
        mapBaseName.insert(region->getName(), basename);
    }
    block->addItem(0, basename, "RRI functions");
    block->addValue("End");
}

void PrvRegionWriter::pushRRIRegionHeader()
{
    QTextStream* output=outputPrvFile->getPrvStream();
    *output<<"#RRI"<<endl;
}

void PrvRegionWriter::pushRRIRegion(QString region, RRICore *core)
{
    QTextStream* output=outputPrvFile->getPrvStream();
    QVector<Part*> parts=core->getParts();
    for (int i=0; i< parts.size(); i++){
        if (core->getRedistributedModel()->getPartsAsString()[i].compare("void")!=0){
            if (!block->getValueMap().contains(core->getRedistributedModel()->getPartsAsString()[i])){
                block->addValue(core->getRedistributedModel()->getPartsAsInteger()[i],core->getRedistributedModel()->getPartsAsString()[i]);
            }
            *output<<"2:"<<parser->getRegionMap()[region]->getTask()<<
                ":"<<parser->getRegionMap()[region]->getApplication()<<
                ":"<<parser->getRegionMap()[region]->getProcess()<<
                ":"<<parser->getRegionMap()[region]->getThread()<<
                ":"<<parser->getRegionMap()[region]->getStart()+(long)(parser->getRegionMap()[region]->getDuration()*parts[i]->getFirstRelative())<<
                ":"<<mapBaseName[region]<<
                ":"<<block->getValueMap()[core->getRedistributedModel()->getPartsAsString()[i]]->getValue()<<endl;
            *output<<"2:"<<parser->getRegionMap()[region]->getTask()<<
                ":"<<parser->getRegionMap()[region]->getApplication()<<
                ":"<<parser->getRegionMap()[region]->getProcess()<<
                ":"<<parser->getRegionMap()[region]->getThread()<<
                ":"<<parser->getRegionMap()[region]->getStart()+(long)(parser->getRegionMap()[region]->getDuration()*parts[i]->getLastRelative())<<
                ":"<<mapBaseName[region]<<
                ":"<<0<<endl;
        }
    }
}

void PrvRegionWriter::pushRRIEventTypeBlock()
{
    QTextStream* output=outputPrvFile->getPcfStream();
    *output<<*block;
}

void PrvRegionWriter::parseRegions(QTextStream* regionStream)
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
