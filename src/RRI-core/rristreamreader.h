#ifndef RRISTREAMREADER_H
#define RRISTREAMREADER_H

#include <QTextStream>
#include <QChar>
#include "constants.h"

class RRIStreamReader
{
public:
    RRIStreamReader(QTextStream stream);
    RRIStreamReader();
    RRIStreamReader(QTextStream stream, QChar separator);
    RRIStreamReader(QChar separator);

    QTextStream getStream() const;
    void setStream(const QTextStream &value);

    QChar getSeparator() const;
    void setSeparator(const QChar &value);

    QStringList readline();
    bool isEnd();

private:
    QTextStream stream;
    QChar separator;
    QString line;
};

#endif // RRISTREAMREADER_H
