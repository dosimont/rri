#ifndef EVENTTYPEBLOCK_H
#define EVENTTYPEBLOCK_H

#include <vector>

#include "eventtypeitem.h"
#include "eventtypevalue.h"

class EventTypeBlock
{
public:
    EventTypeBlock();
    friend QTextStream& operator<<(QTextStream& out, EventTypeBlock block);

    vector<EventTypeItem *> getItems() const;
    void setItems(const vector<EventTypeItem *> &value);

    vector<EventTypeValue *> getValues() const;
    void setValues(const vector<EventTypeValue *> &value);

protected:
    vector<EventTypeItem*> items;
    vector<EventTypeValue*> values;
};

#endif // EVENTTYPEBLOCK_H
