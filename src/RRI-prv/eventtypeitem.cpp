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
    out << &item;
    return out;
}

QTextStream& operator<<(QTextStream& out, EventTypeItem* item)
{
    out << item->getGradientColor() << "\t" << item->getType() << "\t" << item->getLabel() << endl;
    return out;
}
