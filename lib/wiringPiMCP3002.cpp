/*************************************************** 
  This is a library to read from a MCP3002 D/A chip
  using SPI, based on using wiringPi

     MCP3002 protocol looks like the following:
    
         Byte        0        1
         ==== ======== ========
         Tx   01MCLxxx xxxxxxxx
         Rx   xxxxx0RR RRRRRRRR for the 3002
    
    The transmit bits start with several preamble "0" bits, the number of
    which is determined by the amount required to align the last byte of
    the result with the final byte of output. A start "1" bit is then
    transmitted, followed by the single/differential bit (M); 1 for
    single-ended read, 0 for differential read. Next comes a single bit
    for channel (M) then the MSBF bit (L) which selects whether the data
    will be read out in MSB form only (1) or whether LSB read-out will
    occur after MSB read-out (0).

    Read-out begins with a null bit (0) followed by the result bits (R).
    All other bits are don't care (x).
    
    Written by Hal Breidenbach.  
    BSD license, all text above must be included in any redistribution

 ****************************************************/


#include "wiringPiMCP3002.h"
#include <wiringPiSPI.h>

#define M 1 // single/differential read
#define L 1 // MSBF read out 

/*
    cs indicates chip select, 0 or 1 for the MCP3002
*/     
wiringPiMCP3002::wiringPiMCP3002(uint8_t cs, uint8_t ch, float rv) {

    v_factor = rv / 1024;
    chip_sel = cs;
    wiringPiSPISetup( (int)chip_sel, 500000);  // SPI speed 500000
    
    // Magic word for write
    command = 0x02;  //  start with 0000 0010

    command |= M;
    command <<= 1;   //  0000 01M0
    command |= ch;
    command <<= 1;  //  0000 10MC0
    command |= L;
    command <<= 3;   //  001M CL00
    
}

float wiringPiMCP3002::getFactor(void) {
    return (v_factor);
}

float wiringPiMCP3002::getVolts(void) {

    uint16_t temp;
    rwbuffer[0] = command;
    rwbuffer[1] = 0;
    rwbuffer[2] = 0;

    wiringPiSPIDataRW(chip_sel, rwbuffer, 3);
    
    temp = rwbuffer[0];
    temp <<= 8;
    temp |= rwbuffer[1];
    return ( v_factor * temp );  //  Multiply by voltage factor.

}

uint16_t wiringPiMCP3002::getRaw(void) {

    uint16_t temp;
    rwbuffer[0] = command;
    rwbuffer[1] = 0;
    rwbuffer[2] = 0;

    wiringPiSPIDataRW(chip_sel, rwbuffer, 3);
        
    temp = rwbuffer[0];
    temp <<= 8;
    temp |= rwbuffer[1];
    return ( temp );  //  2 bytes returned.

}

