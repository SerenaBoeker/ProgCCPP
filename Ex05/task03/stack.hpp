#ifndef STACK_H
#define STACK_H

/**
 * @brief Definition of the Stack class
 * 
 */
class Stack {
    int size;
    int *arrayPtr;
    int count;

    public:
        explicit Stack(unsigned int size = 10); // constructor with default value
        ~Stack();                               // destructor
        Stack(const Stack&);                    // copy ctor
        Stack& operator=(const Stack&);         // copy operator=
        Stack(Stack&&);                         // move ctor
        Stack& operator=(Stack&&);              // move operator=
        bool is_full();                         // if stack is full
        bool is_empty();                        // if stack is empty
        void push(int);                         // adding an element to the stack
        int pop();                              // removing an element from the stack (LIFO)
        void show() const;                      // prints the stack's content
        int capacity() const;                   // returns the stack size
        int length() const;                     // returns the stack element count
        Stack& operator=(const int&) = delete;  // no assignment of a single integer to a stack variable possible
        // Stack createNewStack(unsigned int);        // creates new stack and fills it with random numbers
};

#endif