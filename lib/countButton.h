// -*- mode: c++ -*-

/**
 *
 *  countButton
 *
 *  Class to process a button input
 *  It assumes that no debouncing or pull-up or pull-down resistors are needed.
 *
 *  It returns the number of button presses where the time of the low-level signal
 *  between presses is less than a specified "gap" time.
 *
 *  If the time the button is pressed exceeds 5 seconds, this process returns 255.
 *
 */
 
#include <wiringPi.h>
#include <ctime>
#include <chrono>
#include <thread>
#include <sys/time.h>
#include <unistd.h>

class countButton{
private:
    int pin_;
    enum switchState {COUNTING_HIGH,COUNTING_LOW} state_;
    double buttonGap_;
    int buttonCount_;
    double timerStart_;
    struct timeval tv_;
    struct timezone tz_ = {0,0};
    double getSeconds(void); 

public:
    countButton(int pin, double gap);
    int read();
};
