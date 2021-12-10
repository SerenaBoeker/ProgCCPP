#include <iostream>
#include "hellotext.hpp"

/**
 * @brief Construct a new Hellotext:: Hellotext object,
 *        prints out "---start---" when the object
 *        has been initialized 
 */
Hellotext::Hellotext() {
    std::cout << "---start---" << std::endl;
}

/**
 * @brief Destroy the Hellotext:: Hellotext object,
 *        prints out "---end---" when destructor
 *        has been called
 */
Hellotext::~Hellotext() {
    std::cout << "---end---" << std::endl;
}

/**
 * @brief create a new Hellotext object and print out
 *        "---start---" 
 */
Hellotext hi;

int main(void) {
    std::cout << "Hello world!" << std::endl;
    return 0;
}