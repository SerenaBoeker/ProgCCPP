#ifndef STOPWATCH_H
#define STOPWATCH_H
#include <ctime>

/**
 * @brief A class for a stopwatch with two methods, for starting
 *  and stoping the stopwatch, respectively, using ctime C++ Library
 */
class StopWatch {
    private:
        clock_t myStopwatch;
        bool running;
        double duration;

    public:
        StopWatch();        // constructor
        void start();       // starts the stopwatch
        double stop();      // stops the stopwatch
        
};

#endif