#ifndef PARAMETERS_H
#define PARAMETERS_H

#include "constants.h"
#include <QString>
#include <QTextStream>

using rri::InputFileType;

class Parameters
{
public:
    Parameters();

    InputFileType getAnalysisType() const;
    void setAnalysisType(const InputFileType &value);

    bool getNormalize() const;
    void setNormalize(bool value);

    float getThreshold() const;
    void setThreshold(float value);

    int getTimesliceNumber() const;
    void setTimesliceNumber(int value);

    float getP() const;
    void setP(float value);

    QTextStream getStream() const;
    void setStream(const QTextStream &value);

private:
    QTextStream stream;
    InputFileType analysisType;
    bool normalize;
    float threshold;
    float p;
    int timesliceNumber;
};

#endif // PARAMETERS_H
