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

#include "biqmap.h"

template<typename Key, typename Value>
BiQMap<Key,Value>::BiQMap()
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

template class BiQMap<int, int>;
template class BiQMap<int, QString>;
