#include "parameters.h"

Parameters::Parameters()
{
    currentFileName="";
    analysisType=rri::DEFAULT;
    normalize=DEFAULT_PARAMETER_NORMALIZE;
    threshold=DEFAULT_PARAMETER_THRESHOLD;
    p=DEFAULT_PARAMETER_PARAMETER;
    timesliceNumber=DEFAULT_PARAMETER_TIMESLICENUMBER;
}

QString Parameters::getCurrentFileName() const
{
    return currentFileName;
}

void Parameters::setCurrentFileName(const QString &value)
{
    currentFileName = value;
}

InputFileType Parameters::getAnalysisType() const
{
    return analysisType;
}

void Parameters::setAnalysisType(const InputFileType &value)
{
    analysisType = value;
}

bool Parameters::getNormalize() const
{
    return normalize;
}

void Parameters::setNormalize(bool value)
{
    normalize = value;
}

float Parameters::getThreshold() const
{
    return threshold;
}

void Parameters::setThreshold(float value)
{
    threshold = value;
}

int Parameters::getTimesliceNumber() const
{
    return timesliceNumber;
}

void Parameters::setTimesliceNumber(int value)
{
    timesliceNumber = value;
}

float Parameters::getP() const
{
    return p;
}

void Parameters::setP(float value)
{
    p = value;
}
