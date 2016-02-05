#ifndef PARAMETERS_H
#define PARAMETERS_H

#include "constants.h"
#include <QString>

using InputData::DataType;

class Parameters
{
public:
    Parameters();
    QString getCurrentFileName() const;
    void setCurrentFileName(const QString &value);

    DataType getAnalysisType() const;
    void setAnalysisType(const DataType &value);

    bool getNormalize() const;
    void setNormalize(bool value);

    float getThreshold() const;
    void setThreshold(float value);

    int getTimesliceNumber() const;
    void setTimesliceNumber(int value);

    float getParameter() const;
    void setParameter(float value);

private:
    QString currentFileName;
    DataType analysisType;
    bool normalize;
    float threshold;
    float parameter;
    int timesliceNumber;
};

#endif // PARAMETERS_H
