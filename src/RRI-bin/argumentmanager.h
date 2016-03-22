/*  RRI - Relevant Routine Identifier
*   Copyright (C) 2016  Damien Dosimont
*
*   This file is part of RRI.
*
*   RRI is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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
