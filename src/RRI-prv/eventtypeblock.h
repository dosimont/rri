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

    QVector<EventTypeItem *> getItems() const;
    void setItems(const QVector<EventTypeItem *> &value);

    QVector<EventTypeValue *> getValues() const;
    void setValues(const QVector<EventTypeValue *> &value);

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
