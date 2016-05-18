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

#include "eventtypeblock.h"

EventTypeBlock::EventTypeBlock()
{

}

EventTypeBlock::EventTypeBlock(const EventTypeBlock& object)
{
    for (EventTypeItem* item:object.getItemMap().values()){
        itemMap.insert(item->getLabel(), new EventTypeItem(*item));
    }
    for (EventTypeValue* value:object.getValueMap().values()){
        valueMap.insert(value->getLabel(), new EventTypeValue(*value));
    }
    comment=object.getComment();
}

EventTypeBlock::~EventTypeBlock()
{
    for (QString key:itemMap.keys()){
        delete itemMap[key];
    }
    for (QString key:valueMap.keys()){
        delete valueMap[key];
    }
}

QString EventTypeBlock::getComment() const
{
    return comment;
}

void EventTypeBlock::setComment(const QString &value)
{
    comment = value;
}

void EventTypeBlock::addItem(int gradient, int type, QString label)
{
    EventTypeItem* item = new EventTypeItem(gradient, type, label);
    itemMap.insert(label, item);
}

void EventTypeBlock::addValue(QString label)
{
    EventTypeValue* value = new EventTypeValue(valueMap.size(),label);
    valueMap.insert(label, value);
}

void EventTypeBlock::addValue(int val, QString label)
{
    EventTypeValue* value = new EventTypeValue(val,label);
    valueMap.insert(label, value);
}

QMap<QString, EventTypeValue *> EventTypeBlock::getValueMap() const
{
    return valueMap;
}

QMap<QString, EventTypeItem *> EventTypeBlock::getItemMap() const
{
    return itemMap;
}

QTextStream& operator<<(QTextStream& out, EventTypeBlock block)
{
    out<<&block;
    return out;
}

QTextStream& operator<<(QTextStream& out, EventTypeBlock* block)
{
    out<<endl;
    if (!block->getComment().isEmpty()){
        out<<"#"<<block->getComment()<<endl<<endl;
    }
    out<<"EVENT_TYPE"<<endl;
    for(EventTypeItem* item:block->getItemMap().values()){
        out<<item;
    }
    out<<"VALUES"<<endl;
    for(QString key:block->getValueMap().keys()){
        out<<block->getValueMap()[key];
    }
    out<<endl;
    return out;
}
