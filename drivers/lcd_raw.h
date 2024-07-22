// File: LCD_Raw.h
// Purpose: LCD Driver for hitachi HD44780 series

#ifndef LCDRAW_H
#define LCDRAW_H

#include "hal/hal.h"
typedef enum{
    LCD_DATALEN_4 = 0,
    LCD_DATALEN_8 = 1
}LCDDataLen_t;

typedef enum{
    LCD_LINEMODE_1 = 0,
    LCD_LINEMODE_2 = 1
}LCDLineMode_t;

typedef enum{
    LCD_FONTMODE_5X8 = 0,
    LCD_FONTMODE_5X10 = 1
}LCDFontMode_t;

typedef struct{
    PinDef_t rsPin;
    PinDef_t rwPin;
    PinDef_t enablePin;

    // For 8-bit data length, set all data pins 0-7.
    // For 4-bit data length, only pin definitions for data pins 4-7 are required.

    LCDDataLen_t dataLen;
    PinDef_t dataPins[8];
    
    TimerBlock_t waitTimer;

    uint8_t initByInstruction;

    int rows;
    int columns;
}LCDPinConfig_t;

// This structure holds the internal state of the display. Its contents 
// can be ignored outside the driver. LCD_RawInitialize will take care of initializing it after
//which it must be passed into every subsequent raw function.

typedef struct{
    LCDPinConfig_t pinConfig;

    enum DataDirection_t{
        DATA_UNCONFIGURED = -1,
        DATA_WRITE = 0,
        DATA_READ = 1
    } dataDirection;
    volatile uint32_t* dataPinAddresses[8];
    volatile uint32_t* rsPinAddress;
    volatile uint32_t* rwPinAddress;
    volatile uint32_t* enablePinAddress;
}LCDRawDisplay_t;



#endif