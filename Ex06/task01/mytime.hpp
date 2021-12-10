#ifndef MYTIME_H
#define MYTIME_H
#include <iostream>

class MyTime {
    private:
        int hour;
        int minute;
        int second;
        MyTime adjustValues(MyTime& obj);

    public:
        MyTime(int hour = 0, int minute = 0, int second = 0);
        int getHour() const;
        int getMinute() const;
        int getSecond() const;
        friend std::ostream& operator<<(std::ostream& os, const MyTime& obj);
        operator int() const;
        MyTime operator+(const MyTime& obj) const;
        friend MyTime operator+(const MyTime& obj, int seconds);
        friend MyTime operator+(int seconds, const MyTime& obj);
        MyTime& operator+=(const MyTime&obj);
        MyTime& operator+=(int seconds);
};

#endif