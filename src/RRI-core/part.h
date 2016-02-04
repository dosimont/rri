#ifndef PART_H
#define PART_H


class Part
{
public:
    Part();
    int getFirstTimeSlice() const;
    void setFirstTimeSlice(int value);

    int getLastTimeSlice() const;
    void setLastTimeSlice(int value);

    int getSizeTimeSlice() const;

    int getTotalTimeSlice() const;
    void setTotalTimeSlice(int value);

    double getFirstRelative() const;

    double getLastRelative() const;

    double getSizeRelative() const;

private:
    int firstTimeSlice;
    int lastTimeSlice;
    int sizeTimeSlice;
    int totalTimeSlice;
    double firstRelative;
    double lastRelative;
    double sizeRelative;
};

#endif // PART_H
