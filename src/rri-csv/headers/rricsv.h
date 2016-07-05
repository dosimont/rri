#ifndef RRICSV_H
#define RRICSV_H

#include "rri-csv_global.h"

#include <QTextStream>
#include <QChar>
#include <QStringList>
#include "csv_constants.h"


class RRICSVSHARED_EXPORT RRICsv
{
public:
    RRICsv(QTextStream *stream);
    RRICsv();
    RRICsv(QTextStream *stream, QChar separator);
    RRICsv(QChar separator);

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


#endif // RRICSV_H
