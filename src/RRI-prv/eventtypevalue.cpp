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
#include "eventtypevalue.h"

EventTypeValue::EventTypeValue()
{

}

EventTypeValue::EventTypeValue(const EventTypeValue &object)
{
    value=object.getValue();
    label=object.getLabel();
}

EventTypeValue::~EventTypeValue()
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
    out << &value;
    return out;
}

QTextStream& operator<<(QTextStream &out, EventTypeValue* value)
{
    out << value->getValue() << "\t" << value->getLabel() << endl;
    return out;
}
