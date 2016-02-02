#ifndef BIQMAP_H
#define BIQMAP_H

#include <QMap>

template<typename Key, typename Value>class BiQMap
{
public:
    add(Key key, Value value);
    rmFromKey(Key key);
    rmFromValue(Value value);
    Value getFromKey(Key key);
    Key getFromValue(Value value);
    bool containsKey(Key key);
    bool containsValue(Value value);
private:
    BiQMap();
    ~BiQMap();
    QMap<Key, Value> map1;
    QMap<Value, Key> map2;
};

#endif // BIQMAP_H
