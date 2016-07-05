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

#ifndef REGION_H
#define REGION_H

#include <QString>
#include <QDebug>

class Region
{
public:
    Region();
    int getApplication() const;
    void setApplication(int value);
    void setApplication(QString value);

    int getTask() const;
    void setTask(int value);
    void setTask(QString value);

    int getProcess() const;
    void setProcess(int value);
    void setProcess(QString value);

    int getThread() const;
    void setThread(int value);
    void setThread(QString value);

    long getStart() const;
    void setStart(long value);
    void setStart(QString value);

    long getEnd() const;
    void setEnd(long value);
    void setEnd(QString value);

    long getDuration();

    QString getName() const;
    void setName(const QString &value);

protected:
    QString name;
    int application;
    int task;
    int process;
    int thread;
    long start;
    long end;
};

#endif // REGION_H
