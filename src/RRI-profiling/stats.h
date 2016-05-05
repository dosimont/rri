#ifndef STATS_H
#define STATS_H

#include <QString>

class Stats
{
public:
    Stats();
    QString getRegion() const;
    void setRegion(const QString &value);

    QString getGroup() const;
    void setGroup(const QString &value);

    int getTotalInstanceNumber() const;
    void setTotalInstanceNumber(int value);
    void setTotalInstanceNumber(const QString &value);

    int getTotalSampleNumber() const;
    void setTotalSampleNumber(int value);
    void setTotalSampleNumber(const QString &value);

    float getTotalMedian() const;
    void setTotalMedian(float value);
    void setTotalMedian(const QString &value);

    float getTotalMad() const;
    void setTotalMad(float value);
    void setTotalMad(const QString &value);

    float getSigmaTimeFactor() const;
    void setSigmaTimeFactor(float value);
    void setSigmaTimeFactor(const QString &value);

    float getSelectionIntervalMin() const;
    void setSelectionIntervalMin(float value);
    void setSelectionIntervalMin(const QString &value);

    float getSelectionIntervalMax() const;
    void setSelectionIntervalMax(float value);
    void setSelectionIntervalMax(const QString &value);

    int getSelectedInstanceNumber() const;
    void setSelectedInstanceNumber(int value);
    void setSelectedInstanceNumber(const QString &value);

    int getSelectedInstanceProportion() const;
    void setSelectedInstanceProportion(int value);
    void setSelectedInstanceProportion(const QString &value);

    float getSelectedInstanceMedian() const;
    void setSelectedInstanceMedian(float value);
    void setSelectedInstanceMedian(const QString &value);

    float getSelectedInstanceMad() const;
    void setSelectedInstanceMad(float value);
    void setSelectedInstanceMad(const QString &value);

private:
    QString region;
    QString group;
    int totalInstanceNumber;
    int totalSampleNumber;
    float totalMedian;
    float totalMad;
    float sigmaTimeFactor;
    float selectionIntervalMin;
    float selectionIntervalMax;
    int selectedInstanceNumber;
    int selectedInstanceProportion;
    float selectedInstanceMedian;
    float selectedInstanceMad;
};

#endif // STATS_H
