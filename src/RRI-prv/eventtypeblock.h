#ifndef EVENTTYPEBLOCK_H
#define EVENTTYPEBLOCK_H

#include <QVector>
#include <QString>

#include "eventtypeitem.h"
#include "eventtypevalue.h"

class EventTypeBlock
{
public:
    EventTypeBlock();
    ~EventTypeBlock();
    friend QTextStream& operator<<(QTextStream& out, EventTypeBlock block);

    QString getComment() const;
    void setComment(const QString &value);

    void addItem(int gradient, int type, QString label);
    void addValue(QString label);

    QMap<QString, EventTypeValue *> getValueMap() const;
    QMap<QString, EventTypeItem *> getItemMap() const;

protected:
    QString comment;
    QMap<QString,EventTypeItem*> itemMap;
    QMap<QString,EventTypeValue*> valueMap;
};

#endif // EVENTTYPEBLOCK_H
