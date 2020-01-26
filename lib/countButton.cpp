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
 
#include "countButton.h"

//#define DEBUG
#ifdef DEBUG
#include <iostream>
#endif

countButton::countButton(int pin, double gap){
    pin_ = pin;
    state_ = COUNTING_LOW;
    buttonGap_ = gap;
    buttonCount_ = 0;
    timerStart_ = 0;
};

double countButton::getSeconds() {
        gettimeofday(&tv_, &tz_);
        return (double)tv_.tv_sec + ((double)tv_.tv_usec / 1E6);
}

int countButton::read(){
    if (digitalRead(pin_) == 0) {
        return 0;
    }
    state_ = COUNTING_HIGH; 
    gettimeofday(&tv_, &tz_);
    timerStart_  = getSeconds();
    #ifdef DEBUG
        std::cout << "after if:  " << (getSeconds() - timerStart_) << std::endl; 
        std::cout << "state: " << state_ << ", " << timerStart_ << std::endl;
    #endif
    buttonCount_ = 1;
    while ((getSeconds() - timerStart_) < buttonGap_ ) {
        #ifdef DEBUG
            std::cout << "first:  " << (getSeconds() - timerStart_) << std::endl; 
            std::cout << "state: " << state_ << std::endl;
        #endif
        while (state_ == COUNTING_HIGH){
            #ifdef DEBUG
                std::cout << "high:  " << (getSeconds() - timerStart_) << std::endl; 
            #endif
            usleep(50*1000);
            if (digitalRead(pin_) == 0){
                state_ = COUNTING_LOW;
            }
            if ((getSeconds() - timerStart_) > 5) {
                buttonCount_ = 255;
                break;
            }
        }
        if ((getSeconds() - timerStart_) < (buttonGap_ / 4) ) {
            buttonCount_ = 0;
        }
        timerStart_ = getSeconds();
        while ((state_ == COUNTING_LOW) &&
                         ((getSeconds() - timerStart_) < buttonGap_ )){
            #ifdef DEBUG
                std::cout << "low:  " << (getSeconds() - timerStart_) << std::endl; 
            #endif
            usleep(100*1000);
            if (digitalRead(pin_) == 1){
                state_ = COUNTING_HIGH;
                ++buttonCount_;
            }
        }
    }
    return buttonCount_;
};
