#include "argumentmanager.h"

ArgumentManager::ArgumentManager(int argc, char *argv[])
{
    command=QString(argv[0]);
    arguments=QStringList();
    for (int i=1; i<argc; i++){
        arguments.push_back(argv[i]);
    }
    conform=true;
    timeSliceNumber=TSNUMBER;
    threshold=THRESHOLD;
    minprop=MINPROP;
    output="";
    uniqueFile=false;
    novoid=false;
    processArguments();
}

void ArgumentManager::printUsage()
{
    if (!conform){
        qDebug()<<"Error: incorrect command";
    }
    qDebug().nospace()<<"Usage: "<<command<<" [options] <input>";
    qDebug().nospace()<<"\t<input>:\tfolding directory, or callerdata file if --inputfile option is enabled";
    qDebug().nospace()<<"\tOptions:";
    qDebug().nospace()<<"\t\t\t"<<"-i --inputfile <file>: "<<"apply the process on a single callerdata file";
    qDebug().nospace()<<"\t\t\t"<<"-h --help: "<<"print usage";
    qDebug().nospace()<<"\t\t\t"<<"-o --output <directory>: "<<"output directory (rri by default)";
    qDebug().nospace()<<"\t\t\t"<<"-ts --timeslices [integer]: "<<"timeslice number used to discretize the time period ("<<TSNUMBER<<" by default)";
    qDebug().nospace()<<"\t\t\t"<<"-th --threshold [float]: "<<"minimal distance between two parameters p ("<<THRESHOLD<<" by default)";
    qDebug().nospace()<<"\t\t\t"<<"-mp --minprop [float]: "<<"routine minimal proportion ("<<MINPROP<<" by default)";
    //qDebug().nospace()<<"\t\t\t"<<"-nv --novoid: "<<"dynamically reduce the timeslice number to prevent empty timeslices";
}

QStringList ArgumentManager::getArguments() const
{
    return arguments;
}

QString ArgumentManager::getInput() const
{
    return input;
}

QString ArgumentManager::getOutput() const
{
    return output;
}

int ArgumentManager::getTimeSliceNumber() const
{
    return timeSliceNumber;
}

bool ArgumentManager::getUniqueFile() const
{
    return uniqueFile;
}

bool ArgumentManager::getConform() const
{
    return conform;
}

bool ArgumentManager::getHelp() const
{
    return help;
}

void ArgumentManager::processArguments()
{
    if (arguments.size()==0){
        conform=false;
        return;
    }
    for (int i=0; i<arguments.size(); i++){
        if (OPT("-h")||OPT("--help")){
            help=true;
            return;
        }else if(OPT("-ts")||OPT("--timeslices")){
            timeSliceNumber=VAL.toInt();
            i++;
            if (timeSliceNumber<=0){
                conform=false;
                return;
            }
        }else if(OPT("-th")||OPT("--threshold")){
            threshold=VAL.toFloat();
            i++;
            if (threshold<=0||threshold>=1){
                conform=false;
                return;
            }
        }else if(OPT("-mp")||OPT("--minprop")){
            minprop=VAL.toFloat();
            i++;
            if (minprop<0||minprop>1){
                conform=false;
                return;
            }
        }else if (OPT("-nv")||OPT("--novoid")){
            novoid=true;
        }else if (OPT("-o")||OPT("--output")){
            output=VAL;
            i++;
        }else if (OPT("-i")||OPT("--inputfile")){
            uniqueFile=true;
            input=VAL;
            i++;
        }else{
            if (uniqueFile){
                conform=false;
                return;
            }else{
                input=ARG;
            }
        }
    }
    if (input.isEmpty()){
        conform=false;
        return;
    }
}

bool ArgumentManager::getNovoid() const
{
    return novoid;
}

float ArgumentManager::getThreshold() const
{
    return threshold;
}

float ArgumentManager::getMinprop() const
{
    return minprop;
}
