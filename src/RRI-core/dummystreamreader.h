#ifndef DUMMYSTREAMREADER_H
#define DUMMYSTREAMREADER_H

#include <QTextStream>
#include <QChar>
#include "core_constants.h"

class DummyStreamReader
{
public:
    DummyStreamReader(QTextStream *stream);
    DummyStreamReader();
    DummyStreamReader(QTextStream *stream, QChar separator);
    DummyStreamReader(QChar separator);

    QChar getSeparator() const;
    void setSeparator(const QChar &value);

    QStringList readline();
    bool isEnd();

    QTextStream *getStream() const;
    void setStream(QTextStream *value);

private:
    QTextStream *stream;
    QChar separator;
    QString line;
};

#endif // DUMMYSTREAMREADER_H
