#include "stats.h"

Stats::Stats()
{

}

QString Stats::getRegion() const
{
    return region;
}

void Stats::setRegion(const QString &value)
{
    region = value;
}

QString Stats::getGroup() const
{
    return group;
}

void Stats::setGroup(const QString &value)
{
    group = value;
}

int Stats::getTotalInstanceNumber() const
{
    return totalInstanceNumber;
}

void Stats::setTotalInstanceNumber(int value)
{
    totalInstanceNumber = value;
}

void Stats::setTotalInstanceNumber(const QString &value)
{
    totalInstanceNumber = value.toInt();
}

int Stats::getTotalSampleNumber() const
{
    return totalSampleNumber;
}

void Stats::setTotalSampleNumber(int value)
{
    totalSampleNumber = value;
}

void Stats::setTotalSampleNumber(const QString &value)
{
    totalSampleNumber = value.toInt();
}

float Stats::getTotalMedian() const
{
    return totalMedian;
}

void Stats::setTotalMedian(float value)
{
    totalMedian = value;
}

void Stats::setTotalMedian(const QString &value)
{
    totalMedian = value.toFloat();
}

float Stats::getTotalMad() const
{
    return totalMad;
}

void Stats::setTotalMad(float value)
{
    totalMad = value;
}

void Stats::setTotalMad(const QString &value)
{
    totalMad = value.toFloat();
}

float Stats::getSigmaTimeFactor() const
{
    return sigmaTimeFactor;
}

void Stats::setSigmaTimeFactor(float value)
{
    sigmaTimeFactor = value;
}

void Stats::setSigmaTimeFactor(const QString &value)
{
    sigmaTimeFactor = value.toFloat();
}

float Stats::getSelectionIntervalMin() const
{
    return selectionIntervalMin;
}

void Stats::setSelectionIntervalMin(float value)
{
    selectionIntervalMin = value;
}

void Stats::setSelectionIntervalMin(const QString &value)
{
    selectionIntervalMin = value.toFloat();
}

float Stats::getSelectionIntervalMax() const
{
    return selectionIntervalMax;
}

void Stats::setSelectionIntervalMax(float value)
{
    selectionIntervalMax = value;
}

void Stats::setSelectionIntervalMax(const QString &value)
{
    selectionIntervalMax = value.toFloat();
}

int Stats::getSelectedInstanceNumber() const
{
    return selectedInstanceNumber;
}

void Stats::setSelectedInstanceNumber(int value)
{
    selectedInstanceNumber = value;
}

void Stats::setSelectedInstanceNumber(const QString &value)
{
    selectedInstanceNumber = value.toInt();
}

int Stats::getSelectedInstanceProportion() const
{
    return selectedInstanceProportion;
}

void Stats::setSelectedInstanceProportion(int value)
{
    selectedInstanceProportion = value;
}

void Stats::setSelectedInstanceProportion(const QString &value)
{
    selectedInstanceProportion = value.toInt();
}

float Stats::getSelectedInstanceMedian() const
{
    return selectedInstanceMedian;
}

void Stats::setSelectedInstanceMedian(float value)
{
    selectedInstanceMedian = value;
}

void Stats::setSelectedInstanceMedian(const QString &value)
{
    selectedInstanceMedian = value.toFloat();
}

float Stats::getSelectedInstanceMad() const
{
    return selectedInstanceMad;
}

void Stats::setSelectedInstanceMad(float value)
{
    selectedInstanceMad = value;
}

void Stats::setSelectedInstanceMad(const QString &value)
{
    selectedInstanceMad = value.toFloat();
}
