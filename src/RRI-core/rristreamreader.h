#ifndef RRISTREAMREADER_H
#define RRISTREAMREADER_H

#include <QTextStream>
#include <QChar>
#include "core_constants.h"

class RRIStreamReader
{
public:
    RRIStreamReader(QTextStream *stream);
    RRIStreamReader();
    RRIStreamReader(QTextStream *stream, QChar separator);
    RRIStreamReader(QChar separator);

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

#endif // RRISTREAMREADER_H
