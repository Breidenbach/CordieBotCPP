/**
 *
 *  cbotLights
 *
 *
 *
 */
 
#include "cbotLights.h"

//#define DEBUG
#ifdef DEBUG
#include <iostream>
#endif

cbotLights::cbotLights(){
    wiringPiTLC59711 cbotTLC59711_;
/*  private variables defined in cbotLights.h:
//    hues_[4][3];  //  [LED# (0,1,2,3)], [color (R, G, B)] 
//    rampInc_[4];
//    rampDelay_[4];
*/
    #ifdef DEBUG
        std::cout << "constructor for cbotLights" << std::endl;
    #endif
    
}

void cbotLights::setHues(int LED, int R, int G, int B){
    hues_[LED][0] = R;
    hues_[LED][1] = G;
    hues_[LED][2] = B;
    cbotTLC59711_.setLED(LED, hues_[LED][0], hues_[LED][1], hues_[LED][2]);
    cbotTLC59711_.write();
    #ifdef DEBUG
        std::cout << "setting LED" << LED << "to (R,G,B): " << 
            hues_[LED][0] << ", " << hues_[LED][1] << ", " << hues_[LED][2] << std::endl;
    #endif
}

void cbotLights::setIncrements(int LED, int number, int delay){
    rampInc_[LED] = number;
    rampDelay_[LED] = delay * 1000;  // delay value in ms.
}

/**
 *  rampOne
 *
 *  Ramp a single LED from one set of RGB values to another 
 *
 */
void cbotLights::rampOne(int LED, int R, int G, int B){
    int previous[3];
    int interval[3];
    previous[0] = hues_[LED][0];
    previous[1] = hues_[LED][1];
    previous[2] = hues_[LED][2];
    interval[0] = (R - previous[0]) / rampInc_[LED];
    interval[1] = (G - previous[1]) / rampInc_[LED];
    interval[2] = (B - previous[2]) / rampInc_[LED];
    #ifdef DEBUG
        std::cout << "rampOne: " << LED << "  input (R,G,B): " << 
            R << ", " << G << ", " << B << std::endl;
        std::cout << "rampOne: " << LED << "  hues_ (R,G,B): " << 
            hues_[LED][0] << ", " << hues_[LED][1] << ", " << hues_[LED][2] << std::endl;
        std::cout << "rampOne: " << LED << " previous (R,G,B): " << 
            previous[0] << ", " << previous[1] << ", " << previous[2] << std::endl;
        std::cout << "rampOne: " << LED << " intervals (R,G,B): " << 
            interval[0] << ", " << interval[1] << ", " << interval[2] << std::endl;
        std::cout << "rampOne: " << LED << " ramp increment: " << 
             rampInc_[LED] << ",  delay:  " << rampDelay_[LED] << std::endl;
    #endif
    for (int ndx = 0; ndx < rampInc_[LED]; ++ndx){
        previous[0] += interval[0];
        previous[1] += interval[1];
        previous[2] += interval[2];
        cbotTLC59711_.setLED(LED, previous[0], previous[1], previous[2]);
        cbotTLC59711_.write();
        usleep(rampDelay_[LED]);       
    }
    hues_[LED][0] = previous[0];
    hues_[LED][1] = previous[1];
    hues_[LED][2] = previous[2];
    #ifdef DEBUG
        std::cout << "rampOne: " << LED << "  hues_ (R,G,B): " << 
            hues_[LED][0] << ", " << hues_[LED][1] << ", " << hues_[LED][2] << std::endl;
    #endif
}

/**
 *  rampPair
 *
 *  Ramp a pair of LEDs from one set of RGB values to another, each set of RGB values
 *  is independent of the other.
 *
 *  Ramp values must be set for the first LED specified. 
 *
 */

void cbotLights::rampPair(int LED1, int LED2,
                 int R1, int G1, int B1, int R2, int G2, int B2){
    int previous[2][3];
    int interval[2][3];
    previous[0][0] = hues_[LED1][0];
    previous[0][1] = hues_[LED1][1];
    previous[0][2] = hues_[LED1][2];
    previous[1][0] = hues_[LED2][0];
    previous[1][1] = hues_[LED2][1];
    previous[1][2] = hues_[LED2][2];
    interval[0][0] = (R1 - previous[0][0]) / rampInc_[LED1];
    interval[0][1] = (G1 - previous[0][1]) / rampInc_[LED1];
    interval[0][2] = (B1 - previous[0][2]) / rampInc_[LED1];
    interval[1][0] = (R2 - previous[1][0]) / rampInc_[LED2];
    interval[1][1] = (G2 - previous[1][1]) / rampInc_[LED2];
    interval[1][2] = (B2 - previous[1][2]) / rampInc_[LED2];
    #ifdef DEBUG
        std::cout << "rampPair: " << LED1 << "  input (R1,G1,B1): " << 
            R1 << ", " << G1 << ", " << B1 << std::endl;
        std::cout << "rampPair: " << LED1 << "  hues_ (R,G,B): " << 
            hues_[LED1][0] << ", " << hues_[LED1][1] << ", " << hues_[LED1][2] << std::endl;
        std::cout << "rampPair: " << LED1 << " previous (R,G,B): " << 
            previous[0][0] << ", " << previous[0][1] << ", " << previous[0][2] << std::endl;
        std::cout << "rampPair: " << LED1 << " intervals (R,G,B): " << 
            interval[0][0] << ", " << interval[0][1] << ", " << interval[0][2] << std::endl;
        std::cout << "rampPair: " << LED2 << "  input (R2,G2,B2): " << 
            R2 << ", " << G2 << ", " << B2 << std::endl;
        std::cout << "rampPair: " << LED2 << "  hues_ (R,G,B): " << 
            hues_[LED2][0] << ", " << hues_[LED2][1] << ", " << hues_[LED2][2] << std::endl;
        std::cout << "rampPair: " << LED2 << " previous (R,G,B): " << 
            previous[1][0] << ", " << previous[1][1] << ", " << previous[1][2] << std::endl;
        std::cout << "rampPair: " << LED2 << " intervals (R,G,B): " << 
            interval[1][0] << ", " << interval[1][1] << ", " << interval[1][2] << std::endl;
        std::cout << "rampPair: " << LED1 << " ramp increment: " << 
             rampInc_[LED1] << ",  delay:  " << rampDelay_[LED1] << std::endl;
    #endif
    for (int ndx = 0; ndx < rampInc_[LED1]; ++ndx){
        previous[0][0] += interval[0][0];
        previous[0][1] += interval[0][1];
        previous[0][2] += interval[0][2];
        cbotTLC59711_.setLED(LED1, previous[0][0], previous[0][1], previous[0][2]);
        previous[1][0] += interval[1][0];
        previous[1][1] += interval[1][1];
        previous[1][2] += interval[1][2];
        cbotTLC59711_.setLED(LED2, previous[1][0], previous[1][1], previous[1][2]);
        cbotTLC59711_.write();
        usleep(rampDelay_[LED1]);       
    }
    hues_[LED1][0] = previous[0][0];
    hues_[LED1][1] = previous[0][1];
    hues_[LED1][2] = previous[0][2];
    hues_[LED2][0] = previous[1][0];
    hues_[LED2][1] = previous[1][1];
    hues_[LED2][2] = previous[1][2];
}

void cbotLights::clear(int LED){
    cbotTLC59711_.setLED(LED, 0, 0, 0);
    cbotTLC59711_.write();
}

void cbotLights::write(){
    cbotTLC59711_.write();
}

void cbotLights::test(){
    cbotTLC59711_.setLED(0, 32767, 0, 0);
    cbotTLC59711_.setLED(1, 32767, 0, 0);
    cbotTLC59711_.setLED(2, 32767, 0, 0);
    cbotTLC59711_.setLED(3, 32767, 0, 0);
    cbotTLC59711_.write();
    usleep(1000000);  // 1 second

    cbotTLC59711_.setLED(0, 0, 32767, 0);
    cbotTLC59711_.setLED(1, 0, 32767, 0);
    cbotTLC59711_.setLED(2, 0, 32767, 0);
    cbotTLC59711_.setLED(3, 0, 32767, 0);
    cbotTLC59711_.write();
    usleep(1000000);  // 1 second

    cbotTLC59711_.setLED(0, 0, 0, 32767);
    cbotTLC59711_.setLED(1, 0, 0, 32767);
    cbotTLC59711_.setLED(2, 0, 0, 32767);
    cbotTLC59711_.setLED(3, 0, 0, 32767);
    cbotTLC59711_.write();
    usleep(1000000);  // 1 second

    cbotTLC59711_.setLED(0, 0, 0, 0);
    cbotTLC59711_.setLED(1, 0, 0, 0);
    cbotTLC59711_.setLED(2, 0, 0, 0);
    cbotTLC59711_.setLED(3, 0, 0, 0);
    cbotTLC59711_.write();
    usleep(1000000);  // 1 second

}/*
void cbotEyes::open(){
    int ndx = 0;
    #ifdef DEBUG
        std::cout << "cbotEyes.open()" << std::endl;
    #endif
    while (ndx < 32767){
        myArray_.setLED(channel1_, 0, ndx, ndx*2);
        myArray_.setLED(channel2_, 0, ndx, ndx*2);
        myArray_.write();
        usleep(5000);
        ndx += myBlink_;
        }
}

void cbotEyes::close(){
    int ndx = 32767;
    while (ndx > 0){
        myArray_.setLED(channel1_, 0, ndx, ndx*2);
        myArray_.setLED(channel2_, 0, ndx, ndx*2);
        myArray_.write();
        usleep(5000);
        ndx -= myBlink_;
        }
    clear();
}

void cbotEyes::clear(){
    myArray_.setLED(channel1_, 0, 0, 0);
    myArray_.setLED(channel2_, 0, 0, 0);
    myArray_.write();
}

void cbotEyes::setLight(int LED, int R, int G, int B){
    myArray_.setLED(LED, R, G, B);
    myArray_.write();
}

void cbotEyes::setOn(){
    myArray_.setLED(1,32000,0,0);
}

void cbotEyes::test(){
    myArray_.setLED(channel1_, 32767, 0, 0);
    myArray_.setLED(channel2_, 32767, 0, 0);
    myArray_.write();
    usleep(1000000);  // 1 second

    myArray_.setLED(channel1_, 0, 32767, 0);
    myArray_.setLED(channel2_, 0, 32767, 0);
    myArray_.write();
    usleep(1000000);  // 1 second

    myArray_.setLED(channel1_, 0, 0, 32767);
    myArray_.setLED(channel2_, 0, 0, 32767);
    myArray_.write();
    usleep(1000000);  // 1 second

    myArray_.setLED(channel1_, 0, 0, 0);
    myArray_.setLED(channel2_, 0, 0, 0);
    myArray_.write();
    usleep(1000000);  // 1 second
}
*/
