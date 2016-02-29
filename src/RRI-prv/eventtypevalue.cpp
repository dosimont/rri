#include "eventtypevalue.h"

EventTypeValue::EventTypeValue()
{

}

EventTypeValue::EventTypeValue(int value, QString label):value(value), label(label)
{

}

int EventTypeValue::getValue() const
{
    return value;
}

void EventTypeValue::setValue(int value)
{
    value = value;
}

QString EventTypeValue::getLabel() const
{
    return label;
}

void EventTypeValue::setLabel(const QString &value)
{
    label = value;
}

QTextStream& operator<<(QTextStream &out, EventTypeValue value)
{
    out << value.getValue() << " " << value.getLabel() << endl;
    return out;
}

int EventTypeValue::getValue() const
{
    return value;
}

QString EventTypeValue::getLabel() const
{
    return label;
}