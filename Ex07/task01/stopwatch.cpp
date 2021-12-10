#include <iostream>
#include "stopwatch.hpp"

/**
 * @brief Constructor of a new StopWatch object that
 * initializes it with 0 values 
 */
StopWatch::StopWatch() : running(0), duration(0.00) { }


/**
 * @brief starts the stopwatch if it is not running already    
 */
void StopWatch::start(void) {
    if (running) {
        std::cout << "StopWatch already running!" << std::endl;
    } else {
        myStopwatch = clock();
        running = 1;
    }
}

/**
 * @brief stops the stopwatch if it is running and returns the 
 *        the measured time in seconds.
 * 
 * @return double duration - the measured time in seconds
 *         
 */
double StopWatch::stop(void) {
    if (!running) {
        std::cout << "StopWatch not started yet!" << std::endl;
        return 0;
    } else {
        myStopwatch = clock() - myStopwatch;
        duration = myStopwatch / (double) CLOCKS_PER_SEC;
        running = 0;
    }
    return duration;
}

