#ifndef BIQMAP_H
#define BIQMAP_H

#include <QMap>

template<typename Key, typename Value>class BiQMap
{
public:
    BiQMap();
    ~BiQMap();
    void add(Key key, Value value);
    void rmFromKey(Key key);
    void rmFromValue(Value value);
    Value getFromKey(Key key);
    Key getFromValue(Value value);
    bool containsKey(Key key);
    bool containsValue(Value value);
private:
    QMap<Key, Value> map1;
    QMap<Value, Key> map2;
};

#endif // BIQMAP_H
