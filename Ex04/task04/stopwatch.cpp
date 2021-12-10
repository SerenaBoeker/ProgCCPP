#include <iostream>
#include <ctime>


/**
 * @brief A class for a stopwatch with two methods, for starting
 *  and stoping the stopwatch, respectively, using ctime C++ Library
 */
class StopWatch {

private:
    clock_t myStopwatch;
    bool running;

public:
    StopWatch() {
        running = 0;
        duration = 0.00;
    }
    double duration;
    
    /**
     * @brief starts the stopwatch if it is not running already    
     */
    void start(void) {
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
    double stop(void) {
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

};