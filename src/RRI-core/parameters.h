#ifndef PARAMETERS_H
#define PARAMETERS_H

#include "constants.h"
#include <QString>

using rri::InputFileType;

class Parameters
{
public:
    Parameters();
    QString getCurrentFileName() const;
    void setCurrentFileName(const QString &value);

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

private:
    QString currentFileName;
    InputFileType analysisType;
    bool normalize;
    float threshold;
    float p;
    int timesliceNumber;
};

#endif // PARAMETERS_H
