#include "eventtypeblock.h"

EventTypeBlock::EventTypeBlock()
{

}

EventTypeBlock::~EventTypeBlock()
{
    for (EventTypeItem item:itemMap.values()){
        delete item;
    }
    for (EventTypeValue value:valueMap.values()){
        delete value;
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

void EventTypeBlock::addItem(int gradient, int value, QString label)
{
    EventTypeItem* item = new EventTypeItem(gradient, value, label);
    itemMap.insert(label, item);
}

void EventTypeBlock::addValue(int val, int label)
{
    EventTypeValue* value = new EventTypeValue(val, label);
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
    out<<endl;
    if (!block.getComment().isEmpty()){
        out<<"#"<<block.getComment()<<endl<<endl;
    }
    out<<"EVENT_TYPE"<<endl;
    for(EventTypeItem* item:block.getItems()){
        out<<item<<endl;
    }
    out<<"VALUES"<<endl;
    for(EventTypeValue* value:block.getValues()){
        out<<value<<endl;
    }
    out<<endl;
}
