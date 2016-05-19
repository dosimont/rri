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

#ifndef RRIOBJECT_H
#define RRIOBJECT_H

#include <QString>
#include <QStringList>
#include <QRegExp>
#include <QTextStream>

class RRIObject
{
public:
    RRIObject();

    int getId() const;
    void setId(int value);
    void setId(QString value);

    int getSample() const;
    void setSample(int value);
    void setSample(QString value);

    double getTsPercentage() const;
    void setTsPercentage(double value);
    void setTsPercentage(QString value);

    int getTsAbsolute() const;
    void setTsAbsolute(int value);
    void setTsAbsolute(QString value);

    int getCallstackLvl() const;
    void setCallstackLvl(int value);
    void setCallstackLvl(QString value);

    int getRoutineId() const;
    void setRoutineId(int value);
    void setRoutineId(QString value);

    QString getRoutineName() const;
    void setRoutineName(QString value);

    int getCodelineId() const;
    void setCodelineId(int value);
    void setCodelineId(QString value);

    int getCodeline() const;
    void setCodeline(int value);
    void setCodeline(QString value);

    QString getFileName() const;
    void setFileName(const QString &value);


    QString getRoutineIdAndCallStack();

    friend QTextStream& operator<<(QTextStream& out, RRIObject object);
    friend QTextStream& operator<<(QTextStream& out, RRIObject *object);

    QString toString();

    int getIndex() const;
    void setIndex(int value);

    void setFilteredFileName(QString value);
    void setFilteredRoutineName(QString value);

private:
    int id;
    int sample;
    double tsPercentage;
    int tsAbsolute;
    int callstackLvl;
    int routineId;
    int index;
    QString routineName;
    int codelineId;
    QString fileName;
    int codeline;
};

#endif // RRIOBJECT_H
