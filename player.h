/*
* player.h
*/

#ifndef PLAYER_H
#define PLAYER_H

#include <stdint.h>
#include "hal/hal.h"
#include "drivers/lcd.h"

typedef struct{
    PinDef_t playButton;
    PinDef_t nextButton;
    PinDef_t prevButton;

    PWMDef_t trackPWM[4];
    PinDef_t trackLED[4];

    UART_ID_t uart;

    LCDPinConfig_t lcd;
    volatile uint32_t* flashBaseAddress;
    uint32_t       flashBlocks;
    TimerBlock_t   noiseTimer;

} MusicPlayer_Config_t;

//--------MusicPlayer_Run-------------
// Run the player. Main entry point
//inputs: pconfig - a pointer to the configuration that the 
// player should use
//outputs: none
void MusicPlayer_Run(MusicPlayer_Config_t* pConfig);

#endif