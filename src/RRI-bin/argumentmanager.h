#ifndef ARGUMENTMANAGER_H
#define ARGUMENTMANAGER_H

#include <QString>
#include <QStringList>

#include "bin_constants.h"

//MACRO

#define OPT(X) arguments[i].compare(X)==0
#define ARG arguments[i]
#define VAL arguments[i+1]

class ArgumentManager
{
public:
    ArgumentManager(int argc, char *argv);

    void printUsage();

    QStringList getArguments() const;

    QString getInput() const;

    QString getOutput() const;

    int getTimeSliceNumber() const;

    bool getUniqueFile() const;

    bool getConform() const;

    bool getHelp() const;

private:
    void processArguments();
    QString command;
    QStringList arguments;
    QString input;
    QString output;
    int timeSliceNumber;
    bool uniqueFile;
    bool conform;
    bool help;


};

#endif // ARGUMENTMANAGER_H
