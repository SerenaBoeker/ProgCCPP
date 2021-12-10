#include "secarr.hpp"
#include <iostream>

/**
 * @brief Construct a new SecArr object, checks if passed pointers
 * are valid, else the end pointer is set to the start pointer.
 * Index pointer points to the current element and is initially
 * set to the start pointer.
 * 
 * @param startptr pointer to beginning of array (first element)
 * @param endptr pointer to ending of array (last element)
 */
SecArr::SecArr(int* startptr, int* endptr) {
    if (endptr < startptr) {
        std::cerr << "Warning: end pointer is before start pointer, setting end pointer to the start pointer." << std::endl;
        endPtr = startptr;
    } else {
        endPtr = endptr;
    }
    startPtr = startptr;
    indexPtr = startPtr; 
}

/**
 * @brief Overload operator*, dereferences the index pointer,
 * returns the current element
 * 
 * @return int& current element in the array the index pointer points to
 */
int& SecArr::operator*() const {
    return *indexPtr;
}

/**
 * @brief Check if the passed pointer if out of the array bounds,
 * prints "Invalid index" error if true
 * 
 * @param tempPtr pointer to be checked
 * @return true pointer is out of bounds
 * @return false pointer is not out of bounds
 */
const bool SecArr::outOfBounds(int* tempPtr) const {
    bool expr = (tempPtr < startPtr) || (tempPtr > endPtr );
    if (expr) std::cerr << "Invalid index" << std::endl;
    return expr;
}

/**
 * @brief Overload operator++ (pre-increment), if the index pointer
 * is not out of bounds after incrementing, it will point to the
 * next element in the array.
 * 
 * @return SecArr& the SecArr object with updated index pointer
 */
SecArr& SecArr::operator++() {
    int* temp = indexPtr + 1;
    if (!outOfBounds(temp))
        indexPtr += 1;
    return *this;
}

/**
 * @brief Overload operator++ (post-increment), if the index pointer
 * is not out of bounds after incrementing, it will point to the
 * next element in the array.
 * 
 * @param int dummy parameter, for distinguishing the overload function
 * signature
 * @return SecArr new SecArr object with updated index pointer
 */
SecArr SecArr::operator++(int) {
    SecArr tempArr(startPtr, endPtr);
    tempArr.indexPtr = indexPtr;
    int* temp = indexPtr + 1;
    if (!outOfBounds(temp)) 
        indexPtr += 1;
    return tempArr;
}

/**
 * @brief Overload operator-- (pre-decrement), if the index pointer
 * is not out of bounds after decrementing, it will point to the
 * previous element in the array.
 * 
 * @return SecArr& the SecArr object with updated index pointer
 */
SecArr& SecArr::operator--() {
    int* temp = indexPtr - 1;
    if(!outOfBounds(temp))
        indexPtr -= 1;
    return *this;
}

/**
 * @brief Overload operator-- (post-decrement), if the index pointer
 * is not out of bounds after decrementing, it will point to the
 * previous element in the array.
 * 
 * @param int dummy parameter, for distinguishing the overload function
 * signature
 * @return SecArr new SecArr object with updated index pointer
 */
SecArr SecArr::operator--(int) {
    SecArr tempArr(startPtr, endPtr);
    tempArr.indexPtr = indexPtr;
    int* temp = indexPtr - 1;
    if(!outOfBounds(temp)) {
        indexPtr -= 1;
    }
    return tempArr;
}

/**
 * @brief Overload operator[] to access an element relative
 * to the current position of the index pointer. If the element
 * would be out of bounds, the last element of the array in
 * the direction of the iteration is printed out.
 * 
 * @param offset an integer, acts like offset to the index pointer
 * @return int& either the accessed element, or the last/first element
 *              of the array
 */
int& SecArr::operator[](int offset) {
    int *temp = indexPtr + offset;
    if (outOfBounds(temp)) {
        if (offset < 0) return *startPtr;   
        else if (offset > 0) return *endPtr; 
    } else {
        return *temp;
    }
}