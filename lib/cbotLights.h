/**
 *
 *  cbotLights
 *
 */
 
#ifndef CBOT_LIGHTS_H
#define CBOT_LIGHTS_H

#include "wiringPiTLC59711.h"
#include <unistd.h>

class cbotLights{
private:
    wiringPiTLC59711 cbotTLC59711_;
    int hues_[4][3] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int rampInc_[4] = {0, 0, 0, 0};
    int rampDelay_[4] = {0, 0, 0, 0};    
public:
    cbotLights();
    void setHues(int LED, int R, int G, int B);
    void setIncrements(int LED, int number, int delay);
    void rampOne(int LED, int R, int G, int B);
    void rampPair(int LED1, int LED2, int R1, int G1, int B1, int R2, int G2, int B2);
    void clear(int LED);
    void write();
    void test();
} ;
 
#endif
 