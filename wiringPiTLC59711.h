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

#ifndef _WIRINGPI_TLC59711_H
#define _WIRINGPI_TLC59711_H
#include <stdint.h>


class wiringPiTLC59711 {
 public:
  wiringPiTLC59711(void);

  void setPWM(uint8_t chan, uint16_t pwm);
  void setLED(uint8_t lednum, uint16_t r, uint16_t g, uint16_t b);
  void write(void);

 private:
    uint32_t command;
    uint8_t BCr, BCg, BCb;
    unsigned char  rwbuffer[28];
    unsigned char  pwmbuffer[24];

};


#endif
