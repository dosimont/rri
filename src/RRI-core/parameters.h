#ifndef PARAMETERS_H
#define PARAMETERS_H

#include "core_constants.h"
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

    QTextStream *getStream() const;
    void setStream(QTextStream *value);

    float getMinprop() const;
    void setMinprop(float value);

private:
    QTextStream *stream;
    InputFileType analysisType;
    bool normalize;
    float threshold;
    float minprop;
    float p;
    int timesliceNumber;
};

#endif // PARAMETERS_H
