#include "argumentmanager.h"

ArgumentManager::ArgumentManager(int argc, char *argv[])
{
    command=QString(argv[0]);
    arguments=QStringList();
    for (int i=1; i<argc; i++){
        arguments.push_back(argv[i]);
    }
    conform=true;
    timeSliceNumber=TS_NUMBER;
    output="";
    uniqueFile=false;
    processArguments();
}

void ArgumentManager::printUsage()
{
    if (!conform){
        qDebug()<<"Error: incorrect command"<<endl<<endl;
    }
    qDebug()<<"Usage: "<<command<<" [options] <input>"<<endl<<endl;
    qDebug()<<"\t<input>:\t\tfolding directory, or callerdata file if --inputfile option is enabled"<<endl;
    qDebug()<<"\tOptions"<<endl;
    qDebug()<<"\t\t\t"<<"-i --inputfile <file>: "<<"apply the process on a single callerdata file"<<endl;
    qDebug()<<"\t\t\t"<<"-h --help: "<<"print usage"<<endl;
    qDebug()<<"\t\t\t"<<"-o --output <directory>: "<<"output directory (rri by default)"<<endl;
    qDebug()<<"\t\t\t"<<"-t --timeslices [number]: "<<"timeslice number used to discretize the time period (200 by default)"<<endl;
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
        }else if(OPT("-t")||OPT("--timeslices")){
            timeSliceNumber=VAL.toInt();
            i++;
            if (timeSliceNumber==0){
                conform=false;
                return;
            }
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
