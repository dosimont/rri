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

#ifndef RRIROUTINEINFO_H
#define RRIROUTINEINFO_H

#include <QString>

class RRIRoutineInfo
{
public:
    RRIRoutineInfo();
    //constructor by copy
    RRIRoutineInfo(RRIRoutineInfo* rRIRoutineInfo);
    int getIndex() const;
    void setIndex(int value);

    int getId() const;
    void setId(int value);

    QString getFile() const;
    void setFile(const QString &value);

    QString getName() const;
    void setName(const QString &value);

    double getPercentageDuration() const;
    void initPercentageDuration(double value);
    void addToPercentageDuration(double value);
    void normalizePercentageDuration(double value);
    void setPercentageDuration(double value);

    double getAverageCallStackLevel() const;
    void initAverageCallStackLevel(double value);
    void addToAverageCallStackLevel(double value);
    void normalizeAverageCallStackLevel();
    void setAverageCallStackLevel(double value);

    int getCount() const;
    QString toString();

    static bool CompareByCallStackLvlAsc(const RRIRoutineInfo & rriInfo1 , const RRIRoutineInfo & rriInfo2);

    static bool CompareByCallStackLvlDesc(const RRIRoutineInfo & rriInfo1 , const RRIRoutineInfo & rriInfo2);

private:
    int index;
    int id;
    int count;
    QString file;
    QString name;
    double percentageDuration;
    double averageCallStackLevel;
};

#endif // RRIROUTINEINFO_H
