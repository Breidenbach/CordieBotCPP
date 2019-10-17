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

#ifndef _WIRINGPI_MCP3002_H
#define _WIRINGPI_MCP3002_H
#include <stdint.h>


class wiringPiMCP3002 {
  public:
    wiringPiMCP3002(uint8_t chip_select, uint8_t MCP3002_channel, float rv = 3.3);

    float getVolts(void);
    uint16_t getRaw(void);
    float getFactor(void);
    
  private:
    float v_factor;  // for the MCP3002 this is Vref / 1024, Vref = Vdd
    uint32_t command;
    uint8_t chip_sel;
    unsigned char  rwbuffer[3];

};


#endif
