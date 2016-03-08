#ifndef REGION_H
#define REGION_H

#include <QString>

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
