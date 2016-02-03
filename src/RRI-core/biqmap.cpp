#include "biqmap.h"

template<typename Key, typename Value>
BiQMap<Key,Value>::BiQMap() : map1(QMap<Key,Value>()),map2(QMap<Value,Key>())
{

}
template<typename Key, typename Value>
BiQMap<Key,Value>::~BiQMap()
{

}

template<typename Key, typename Value>
void BiQMap<Key,Value>::add(Key key, Value value)
{
    if (!map1.contains(key)||!map2.contains(value)){
        map1.insert(key, value);
        map2.insert(value, key);
    }
}

template<typename Key, typename Value>
void BiQMap<Key,Value>::rmFromKey(Key key)
{
    if (map1.contains(key)){
        Value value=map1[key];
        map1.remove(key);
        map2.remove(value);
    }
}

template<typename Key, typename Value>
void BiQMap<Key,Value>::rmFromValue(Value value)
{
    if (map2.contains(value)){
        Key key=map2[value];
        map1.remove(key);
        map2.remove(value);
    }
}

template<typename Key, typename Value>
Value BiQMap<Key,Value>::getFromKey(Key key)
{
    return map1[key];
}

template<typename Key, typename Value>
Key BiQMap<Key,Value>::getFromValue(Value value)
{
    return map2[value];
}

template<typename Key, typename Value>
bool BiQMap<Key,Value>::containsKey(Key key)
{
    return map1.contains(key);
}

template<typename Key, typename Value>
bool BiQMap<Key,Value>::containsValue(Value value)
{
    return map2.contains(value);
}
