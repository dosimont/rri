#include "biqmap.h"

BiQMap::BiQMap() : map1(QMap<Key,Value>()),map2(QMap<Value,Key>())
{

}

BiQMap::~BiQMap()
{

}

BiQMap::add(Key key, Value value)
{
    if (!map1.contains(key)||!map2.contains(value)){
        map1.insert(key, value);
        map2.insert(value, key);
    }
}

BiQMap::rmFromKey(Key key)
{
    if (map1.contains(key)){
        Value value=map1[key];
        map1.remove(key);
        map2.remove(value);
    }
}

BiQMap::rmFromValue(Value value)
{
    if (map2.contains(value)){
        Key key=map2[value];
        map1.remove(key);
        map2.remove(value);
    }
}

Value BiQMap::getFromKey(Key key)
{
    return map1[key];
}

Key BiQMap::getFromValue(Value value)
{
    return map2[value];
}

bool BiQMap::containsKey(Key key)
{
    return map1.contains(key);
}

bool BiQMap::containsValue(Value value)
{
    return map2.contains(value);
}
