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

#include "eventtypeitem.h"
#ifndef EVENTTYPEITEM_H
#define EVENTTYPEITEM_H

#include <QString>
#include <QTextStream>
#include <QDebug>

class EventTypeItem
{
public:
    EventTypeItem();
    EventTypeItem(const EventTypeItem& object);
    ~EventTypeItem();
    EventTypeItem(int gradientColor, int type, QString label);
    int getGradientColor() const;
    void setGradientColor(int value);

    int getType() const;
    void setType(int value);

    QString getLabel() const;
    void setLabel(const QString &value);

    friend QTextStream& operator<<(QTextStream& out, EventTypeItem item);
    friend QTextStream& operator<<(QTextStream& out, EventTypeItem* item);

protected:
    int gradientColor;
    int type;
    QString label;
};

#endif // EVENTTYPEITEM_H
