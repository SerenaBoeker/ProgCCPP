#ifndef SECARR_H
#define SECARR_H

class SecArr {
    int *startPtr;
    int *endPtr;
    int *indexPtr;

    public:
        SecArr(int* startptr, int* endptr);
        int& operator*() const;
        const bool outOfBounds(int*) const;
        SecArr& operator++();         //pre-increment
        SecArr  operator++(int);      //post-increment
        SecArr& operator--();         //pre-decrement
        SecArr  operator--(int);      //post-decrement
        int& operator[](int);
};

#endif