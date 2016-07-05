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
#include "region.h"

Region::Region():
    application(1),
    task(1),
    process(1),
    thread(1),
    start(0),
    end(1)
{

}

int Region::getApplication() const
{
    return application;
}

void Region::setApplication(int value)
{
    application = value;
}

void Region::setApplication(QString value)
{
    application = value.toInt();
}

int Region::getTask() const
{
    return task;
}

void Region::setTask(int value)
{
    task = value;
}

void Region::setTask(QString value)
{
    task = value.toInt();
}

int Region::getProcess() const
{
    return process;
}

void Region::setProcess(int value)
{
    process = value;
}

void Region::setProcess(QString value)
{
    process = value.toInt();
}

int Region::getThread() const
{
    return thread;
}

void Region::setThread(int value)
{
    thread = value;
}

void Region::setThread(QString value)
{
    thread = value.toInt();
}

long Region::getStart() const
{
    return start;
}

void Region::setStart(long value)
{
    start = value;
}

void Region::setStart(QString value)
{
    start = value.toLong();
}

long Region::getEnd() const
{
    return end;
}

void Region::setEnd(long value)
{
    end = value;
}

void Region::setEnd(QString value)
{
    end = value.toLong();
}

long Region::getDuration()
{
    return end-start;
}

QString Region::getName() const
{
    return name;
}

void Region::setName(const QString &value)
{
    name = value;
}
