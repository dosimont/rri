#include "eventtypeitem.h"

EventTypeItem::EventTypeItem()
{
}

EventTypeItem::EventTypeItem(int gradientColor, int type, QString label):gradientColor(gradientColor), type(type), label(label)
{

}

int EventTypeItem::getGradientColor() const
{
    return gradientColor;
}

void EventTypeItem::setGradientColor(int value)
{
    gradientColor = value;
}

int EventTypeItem::getType() const
{
    return Type;
}

void EventTypeItem::setType(int value)
{
    Type = value;
}

QString EventTypeItem::getLabel() const
{
    return Label;
}

void EventTypeItem::setLabel(const QString &value)
{
    Label = value;
}

QTextStream& operator<<(QTextStream& out, EventTypeItem item)
{
    out << item.getGradientColor() << " " << item.getType() << " " << item.getLabel() << endl;
    return out;
}
