#include "stack.hpp"
#include "stopwatch.hpp"
#include <iostream>

double duration;
StopWatch stopWatch;

/**
 * @brief Macro that measures the time in seconds the CPU needs to
 * perform the passed instructions for a given number of times.
 * 
 * @param description the description of the instructions
 * @param repetitions number of times the instructions are repeated
 * @param instructions2test the instructions to be executed
 */
#define MEASURETIME(description, repetitions, instructions2test) \
stopWatch.start(); \
for (int i = 0; i < repetitions; i++) { instructions2test; }; \
duration = stopWatch.stop(); \
std::cout << "My computer requires " << duration << " seconds to execute " \
<< description << " " << repetitions << " times" << std::endl;

/**
 * @brief Create a new Stack object of given size and fill it
 * with pseudo-random numbers between 0 and 99.
 * 
 * @param size the size of the stack
 * @return Stack the created and filled stack
 */
Stack createNewStack(unsigned int size){
    Stack tempStack(size);
    for (int i = 0; i < tempStack.capacity(); i++) {
        tempStack.push(rand() % 100);
    }
    return tempStack;
}


int main() {

    // create a new stack object and fill it with pseudo-random
    // numbers between 0 and 99
    Stack stack1(100000);
    srand(123456);
    for(int i = 0; i < stack1.capacity(); i++) {
        stack1.push(rand() % 100);
    }

    // print the time it takes the CPU to perform 10000 copy
    // operations using the copy operator=
    MEASURETIME("Copy assignment test", 10000, 
            Stack stack2(100000); 
            for (int j = 0; j < stack2.capacity(); j++) {
                stack2.push(rand() % 100);
            }
            stack1 = stack2;
    );

    // print the time it takes the CPU to perform 10000 move
    // operations using the move operator=
    MEASURETIME("Move assignment test", 10000, stack1 = createNewStack(100000));

}
