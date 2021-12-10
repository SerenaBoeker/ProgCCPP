#include "stack.hpp"
#include <iostream>
#include <string.h>

/**
 * @brief The constructor for a new Stack:: Stack object
 * that consists in an array of integers of the passed
 * size argument (default size value is 10). Heap memory
 * space is being allocated for the array, the size is set
 * to the passed value (10 by default), arrayPtr points to
 * the beginning of the array and the count value is initialized
 * to 0, since the array has no elements at the beginning.
 * 
 * @param size the number of integers the array has to hold
 */
Stack::Stack(unsigned int size) {
    std::cout << "Ctor: I am allocating space for " << size << " integers" << std::endl;
    this->size = size;
    arrayPtr = new int[size];
    count = 0;
}

/**
 * @brief The destructor of the Stack:: Stack object, clears up
 * the memory space that has been allocated for the integer array
 * of the Stack object by "uninitializing" the pointer of the array
 * through the "delete[]" instruction. In order to prevent undefined 
 * behavior the array pointer is tested against null before the
 * deleting operation and set to null afterwards. 
 * 
 */
Stack::~Stack() {
    std::cout << "Dtor: I am deallocating space for " << size << " integers filled with "
              << count << " values." << std::endl;
    if (arrayPtr != NULL) {
        delete[] arrayPtr;
        arrayPtr = NULL;
    }
}

/**
 * @brief The Copy Constructor of a Stack object, that is called
 * by the compiler when an object is copied to another. In the
 * initializer list the values of size and count of the object to
 * be copied from are being assigned to the object to be copied to.
 * To copy the integer array from one object to another, the memcpy() 
 * function is used, this copies the values of sizeof(int)*count bytes 
 * (size of the elements * number of elements) from the memory pointed to by
 * the array pointer of the to-be-copied-from object to the memory block
 * pointed to by the array pointer of the to-be-copied-to object (binary copy).
 * The function returns a pointer to the copy destination.
 * 
 * @param toBeCopied the Stack object from which to copy the values. 
 *                   const because the passed object shall not be modified
 */
Stack::Stack(const Stack& toBeCopied)
            : size(toBeCopied.size), count(toBeCopied.count) {
    std::cout << "Cctor called" << std::endl;
    this->arrayPtr = (int*) memcpy(new int[size], toBeCopied.arrayPtr, sizeof(int)*count);
}

/**
 * @brief Copy operator=, that is called when assigning an object
 * to another object that has already been initialized. Works like
 * the copy constructor except that it checks if the passed Stack object
 * is not the same as the one to copy to (otherwise the object would get
 * deleted) and deletes the array like the destructor before copying.
 * 
 * @param toBeCopied the Stack object from which to copy the values (rvalue).
 *                   const because the passed object shall not be modified
 * @return Stack& the Stack object that has been copied to (lvalue)
 */
Stack& Stack::operator=(const Stack& toBeCopied) {
    std::cout << "Cop= called" << std::endl;
    if (this != &toBeCopied) {
        if (arrayPtr != NULL) {
            delete[] arrayPtr;
            arrayPtr = NULL;
        }
        this->size = toBeCopied.size;
        this->count = toBeCopied.count;
        this->arrayPtr = (int*) memcpy(new int[size], toBeCopied.arrayPtr, sizeof(int)*count);
    }
    return *this;
}

/**
 * @brief The Move Constructor of a new Stack object used when copying
 * from a temporary object, that is to be destructed soon. The values
 * of the temporary object are assigned to the new object and then
 * set to 0 and NULL respectively (so the destructor would not free
 * the memory with the integer array (destructor checks if pointer 
 * not null!) ).
 * 
 * @param toBeMoved the temporary Stack object from which to move the values.
 *                  not const because the object has to be modified
 */
Stack::Stack(Stack&& toBeMoved)
            : size(toBeMoved.size), count(toBeMoved.count), arrayPtr(toBeMoved.arrayPtr) {
    std::cout << "Mctor called" << std::endl;
    toBeMoved.size = toBeMoved.count = 0;
    toBeMoved.arrayPtr = NULL;
}

/**
 * @brief Move operator=, used when assigning a temporary object 
 * to another object that has already been initialized. Checks if the
 * passed Stack object is the same as the to-move-to object (otherwise
 * the object would be lost), deletes the array pointer of the to-
 * move-to object, assigns the values of the to-move-from object to it
 * and sets the values of the to-move-from object to 0 and NULL
 * respectively.
 * 
 * @param toBeMoved the temporary Stack object from which to move the values.
 *                  not const because the object has to be modified
 * @return Stack& the Stack object that has been copied to
 */
Stack& Stack::operator=(Stack&& toBeMoved) {
    std::cout << "Mop= called" << std::endl;
    if (this != &toBeMoved) {
        if (arrayPtr != NULL) {
            delete[] arrayPtr;
            arrayPtr = NULL;
        }
        this->size = toBeMoved.size;
        this->count = toBeMoved.count;
        arrayPtr = toBeMoved.arrayPtr;
        toBeMoved.size = toBeMoved.count = 0;
        toBeMoved.arrayPtr = NULL;
    }
    return *this;
}

/**
 * @brief Checks if the number of elements in the array (count) is equal 
 * to the size of the array (size) (in other words, if the array is full)
 * 
 * @return true  the array is full 
 * @return false the array is not full
 */
bool Stack::is_full() {
    if (count == size) {
        return true;
    } else {
        return false;
    }
}

/**
 * @brief Checks if the number of elements in the array is equal to 0
 * (if the array is empty)
 * 
 * @return true  the array is empty
 * @return false the array is not empty
 */
bool Stack::is_empty() {
    return count == 0;
}

/**
 * @brief Unless the array is full, writes the passed integer value 
 * in the array at position count (after the last element) and 
 * increments count by 1, otherwise it prints "The stack is full" 
 * and the passed value cannot be written to the array.
 * 
 * @param x the integer value to be written to the array
 */
void Stack::push(int x) {
    if (is_full()) {
        std::cout << "The stack is full" << std::endl;
        return;
    }
    arrayPtr[count++] = x;
    return;
}

/**
 * @brief Unless the array is empty, returns the last written value 
 * of the array (at position count) and decrements count by 1, otherwise
 * it prints "The stack is empty" and returns 0.
 * 
 * @return int the last array value of 0 if array empty
 */
int Stack::pop() {
    if (is_empty()) {
        std::cout<< "The stack is empty" << std::endl;
        return 0;
    }
    return arrayPtr[--count];
}

/**
 * @brief Prints all elements of the array.
 * 
 */
void Stack::show() const {
    if (count == 0) {
        std::cout << std::endl;
    }
    for (int i = 0; i < count; i++) {
        std::cout << arrayPtr[i] << " ";
        if (i == (count-1) ) {
            std::cout << std::endl;
        }
    }
}

/**
 * @brief Returns the capacity (size) of the array
 * 
 * @return int the size of the array
 */
int Stack::capacity() const {
    return size;
}

/**
 * @brief Returns the number of elements (count) in the array
 * 
 * @return int the number of elements in the array
 */
int Stack::length() const {
    return count;
}