/*************************************************** 
  This is a library for our Adafruit 24-channel PWM/LED driver

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/1455

  These drivers uses SPI to communicate, 3 pins are required to  
  interface: Data, Clock and Latch. The boards are chainable

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
  
  Adapted to wiringPi by Hal Breidenbach
  
 ****************************************************/


#include "wiringPiTLC59711.h"
#include <wiringPiSPI.h>


wiringPiTLC59711::wiringPiTLC59711(void) {

    wiringPiSPISetup(0, 500000);  // SPI chip select 0, speed 500000
    BCr = BCg = BCb = 0x7F;

    // Magic word for write
    command = 0x25;

    command <<= 5;
    //OUTTMG = 1, EXTGCK = 0, TMGRST = 1, DSPRPT = 1, BLANK = 0 -> 0x16
    command |= 0x16;

    command <<= 7;
    command |= BCr;

    command <<= 7;
    command |= BCg;

    command <<= 7;
    command |= BCb;

    for (uint8_t n=0;n<25;n++) {
        pwmbuffer[n] = 0;
    }
    // rwbuffer[14]      workspace to write one board of settings
    // Note that rwbuffer is required since wiringPi SPI write is full duplex and
    // therefore the data in the buffer is lost.

}


void wiringPiTLC59711::write(void) {


    rwbuffer[0] = command >> 24;
    rwbuffer[1] = command >> 16;
    rwbuffer[2] = command >> 8;
    rwbuffer[3] = command;

    // 12 channels per TLC59711
    for (int8_t c=23; c >= 0 ; c--) {
      // 16 bits per channel
      rwbuffer[c+4] = pwmbuffer[c];
    }
    wiringPiSPIDataRW(0, rwbuffer, 28);   //  CS 0, size of rwbuffer

}



void wiringPiTLC59711::setPWM(uint8_t chan, uint16_t pwm) {
  if (chan > 12) return;
  pwmbuffer[chan*2] = pwm >> 8;  
  pwmbuffer[chan*2+1] = pwm;  
}


void wiringPiTLC59711::setLED(uint8_t lednum, uint16_t r, uint16_t g, uint16_t b) {
  setPWM(lednum*3, b);
  setPWM(lednum*3+1, g);
  setPWM(lednum*3+2, r);
}

