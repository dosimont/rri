#include "eventtypeblock.h"

EventTypeBlock::EventTypeBlock()
{

}

EventTypeBlock::~EventTypeBlock()
{
    for (EventTypeItem* item:itemMap.values()){
        delete item;
    }
    for (EventTypeValue* value:valueMap.values()){
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
    for(EventTypeItem* item:block.getItemMap().values()){
        out<<item<<endl;
    }
    out<<"VALUES"<<endl;
    for(EventTypeValue* value:block.getValueMap().values()){
        out<<value<<endl;
    }
    out<<endl;
    return out;
}
