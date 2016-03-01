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

int Region::getStart() const
{
    return start;
}

void Region::setStart(int value)
{
    start = value;
}

void Region::setStart(QString value)
{
    start = value.toInt();
}

int Region::getEnd() const
{
    return end;
}

void Region::setEnd(int value)
{
    end = value;
}

void Region::setEnd(QString value)
{
    end = value.toInt();
}

int Region::getDuration()
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

int Region::getEnd() const
{
    return end;
}
