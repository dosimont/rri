#ifndef ARGUMENTMANAGER_H
#define ARGUMENTMANAGER_H

#include <QString>
#include <QStringList>
#include <QDebug>

#include "bin_constants.h"

//MACRO

#define OPT(X) arguments[i].compare(X)==0
#define ARG arguments[i]
#define VAL arguments[i+1]

class ArgumentManager
{
public:
    ArgumentManager(int argc, char *argv[]);
    void printUsage();
    QStringList getArguments() const;
    QString getInput() const;
    QString getOutput() const;
    int getTimeSliceNumber() const;
    bool getUniqueFile() const;
    bool getConform() const;
    bool getHelp() const;
    float getMinprop() const;
    float getThreshold() const;
    bool getNovoid() const;

private:
    void processArguments();
    QString command;
    QStringList arguments;
    QString input;
    QString output;
    int timeSliceNumber;
    float threshold;
    float minprop;
    bool uniqueFile;
    bool conform;
    bool help;
    bool novoid;


};

#endif // ARGUMENTMANAGER_H
