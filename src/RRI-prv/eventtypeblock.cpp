#include "eventtypeblock.h"

EventTypeBlock::EventTypeBlock()
{

}

vector<EventTypeItem *> EventTypeBlock::getItems() const
{
    return items;
}

void EventTypeBlock::setItems(const vector<EventTypeItem *> &value)
{
    items = value;
}

vector<EventTypeValue *> EventTypeBlock::getValues() const
{
    return values;
}

void EventTypeBlock::setValues(const vector<EventTypeValue *> &value)
{
    values = value;
}


QTextStream& operator<<(QTextStream& out, EventTypeBlock block)
{
    out<<endl;
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
