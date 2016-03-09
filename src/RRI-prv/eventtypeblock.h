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
