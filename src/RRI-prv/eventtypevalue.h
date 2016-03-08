#ifndef EVENTTYPEVALUE_H
#define EVENTTYPEVALUE_H

#include <QString>
#include <QTextStream>
#include <QDebug>

class EventTypeValue
{
public:
    EventTypeValue();
    EventTypeValue(const EventTypeValue& object);
    ~EventTypeValue();
    EventTypeValue(int value, QString label);
    int getValue() const;
    void setValue(int value);
    QString getLabel() const;
    void setLabel(const QString &value);

    friend QTextStream& operator<<(QTextStream& out, EventTypeValue value);
    friend QTextStream& operator<<(QTextStream& out, EventTypeValue* value);

protected:
    int value;
    QString label;
};

#endif // EVENTTYPEVALUE_H
