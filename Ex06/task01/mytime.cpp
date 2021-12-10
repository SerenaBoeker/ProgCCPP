#include "mytime.hpp"

/**
 * @brief Construct a new MyTime object with the passed values for hour, minute
 * and second (default value is 0). If the passed value for "second" and/or "minute"
 * is greater than 59, it is passed accordingly to fit the range of 0-59 by increasing
 * the next element. The value of "hour" has no restriction.
 * 
 * @param hour   an integer for the hour
 * @param minute an integer for the minute
 * @param second an integer for the second
 */
MyTime::MyTime(int hour, int minute, int second)
            : hour(hour), minute(minute), second(second) {
    adjustValues(*this);
}

/**
 * @brief Adjust values of second and minute of an MyTime object to fit
 * the range of 0-59 by increasing the next element.
 * 
 * @param obj     MyTime object of which values to adjust
 * @return obj MyTime object with adjusted values
 */
MyTime MyTime::adjustValues(MyTime& obj) {
    if ( (obj.second/60) >= 1 ) {
        obj.minute += obj.second / 60;
        obj.second  = obj.second % 60;
    }
    if ( (obj.minute/60) >= 1 ) {
        obj.hour   += obj.minute / 60;
        obj.minute  = obj.minute % 60;  
    }
    return obj;
}

/**
 * @brief Return hour(s) of MyTime object
 * 
 * @param obj MyTime object
 * @return hour an integer, the hours 
 */
int MyTime::getHour() const {
    return hour;
}

/**
 * @brief Return minute(s) of MyTime object
 * 
 * @param obj MyTime object
 * @return minute an integer, the minutes 
 */
int MyTime::getMinute() const {
    return minute;
}

/**
 * @brief Return second(s) of MyTime object
 * 
 * @param obj MyTime object
 * @return second an integer, the seconds 
 */
int MyTime::getSecond() const {
    return second;
}

/**
 * @brief Overload operator<< to enable printing out a MyTime object
 * in the format hh:mm:ss (hour, minutes, seconds)
 * 
 * @param os  std::ostream the standard output stream
 * @param obj MyTime object
 * @return std::ostream& the standard output stream
 */
std::ostream& operator<<(std::ostream& os, const MyTime& obj) {
    if (obj.hour < 10) {
        os << "0" << obj.hour << ":";
    } else {
        os << obj.hour << ":";
    }
    if (obj.minute < 10) {
        os << "0" << obj.minute << ":";
    } else {
        os << obj.minute << ":";
    }
    if (obj.second < 10) {
        os << "0" << obj.second;
    } else {
        os << obj.second;
    }
    return os;
}

/**
 * @brief Enable type conversion of a MyTime object to an integer.
 * 
 * @return int total number of seconds of the MyTime object
 */
MyTime::operator int() const {
    return second + (minute * 60) + (hour * 60 * 60);
}

/**
 * @brief Overload operator+ to allow addition of a MyTime object
 * to an integer number.
 * 
 * @param seconds number of seconds to add to the MyTime object
 * @param obj MyTime object to which to add the seconds to
 * @return const MyTime new MyTime object with adjusted values
 */
MyTime operator+(int seconds, const MyTime& obj) {
    return MyTime(obj.getHour(), obj.getMinute(), obj.getSecond() + seconds);
}

/**
 * @brief Overload operator+ to allow addition of an integer number 
 * to a MyTime object.
 * 
 * @param obj MyTime object to which to add the seconds to
 * @param seconds number of seconds to add to the MyTime object
 * @return const MyTime new MyTime object with adjusted values
 */
MyTime operator+(const MyTime& obj, int seconds) {
    return MyTime(obj.getHour(), obj.getMinute(), obj.getSecond() + seconds);
}

/**
 * @brief Overload operator+ to allow addition of a MyTime object
 * to another MyTime object.
 * 
 * @param obj MyTime object of which values to add to existing MyTime object
 * @return const MyTime new MyTime object with adjusted values
 */
MyTime MyTime::operator+(const MyTime& obj) const{
    return MyTime(this->hour   + obj.hour, 
                  this->minute + obj.minute, 
                  this->second + obj.second);
}

/**
 * @brief Overload operator+= to allow addition of a MyTime object
 * to another MyTime object.
 * 
 * @param obj MyTime object of which values to add to existing MyTime object
 * @return const MyTime& existing MyTime object with adjusted values
 */
MyTime& MyTime::operator+=(const MyTime& obj){
    hour   += obj.hour;
    minute += obj.minute;
    second += obj.second;
    adjustValues(*this);
    return *this;
}

/**
 * @brief Overload operator+= to allow addition of an integer
 * to a MyTime object.
 * 
 * @param seconds number of seconds to add to the MyTime object
 * @return const MyTime& existing MyTime object with adjusted values
 */
MyTime& MyTime::operator+=(int seconds){
    second += seconds;
    adjustValues(*this);
    return *this;
}