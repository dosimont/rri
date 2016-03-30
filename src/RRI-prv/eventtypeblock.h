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

#ifndef EVENTTYPEBLOCK_H
#define EVENTTYPEBLOCK_H

#include <QVector>
#include <QString>
#include <QtAlgorithms>
#include <QDebug>

#include "eventtypeitem.h"
#include "eventtypevalue.h"

class EventTypeBlock
{
public:
    EventTypeBlock();
    EventTypeBlock(const EventTypeBlock& object);
    ~EventTypeBlock();
    friend QTextStream& operator<<(QTextStream& out, EventTypeBlock block);
    friend QTextStream& operator<<(QTextStream& out, EventTypeBlock* block);

    QString getComment() const;
    void setComment(const QString &value);

    void addItem(int gradient, int type, QString label);
    void addValue(QString label);
    void addValue(int val, QString label);
    QMap<QString, EventTypeValue *> getValueMap() const;
    QMap<QString, EventTypeItem *> getItemMap() const;

protected:
    QString comment;
    QMap<QString,EventTypeItem*> itemMap;
    QMap<QString,EventTypeValue*> valueMap;
};

#endif // EVENTTYPEBLOCK_H
