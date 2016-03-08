#include "eventtypeitem.h"

EventTypeItem::EventTypeItem()
{
}

EventTypeItem::EventTypeItem(const EventTypeItem &object)
{
    gradientColor=object.getGradientColor();
    type=object.getType();
    label=object.getLabel();
}

EventTypeItem::~EventTypeItem()
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
    return type;
}

void EventTypeItem::setType(int value)
{
    type = value;
}

QString EventTypeItem::getLabel() const
{
    return label;
}

void EventTypeItem::setLabel(const QString &value)
{
    label = value;
}

QTextStream& operator<<(QTextStream& out, EventTypeItem item)
{
    out << item.getGradientColor() << "\t" << item.getType() << "\t" << item.getLabel() << endl;
    return out;
}

QTextStream& operator<<(QTextStream& out, EventTypeItem* item)
{
    out << item->getGradientColor() << "\t" << item->getType() << "\t" << item->getLabel() << endl;
    return out;
}
