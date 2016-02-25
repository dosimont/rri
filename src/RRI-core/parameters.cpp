#include "parameters.h"

Parameters::Parameters()
{
    analysisType=rri::DEFAULT;
    normalize=DEFAULT_PARAMETER_NORMALIZE;
    threshold=DEFAULT_PARAMETER_THRESHOLD;
    p=DEFAULT_PARAMETER_PARAMETER;
    timesliceNumber=DEFAULT_PARAMETER_TIMESLICENUMBER;
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

QTextStream Parameters::getStream() const
{
    return stream;
}

void Parameters::setStream(const QTextStream &value)
{
    stream = value;
}
