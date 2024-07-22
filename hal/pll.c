/*
* PLL.c phase locked loop oscillators and clocks
*/
#include <stdint.h>
#include "hal.h"
#include "tm4c123gh6pm.h"

// current bus frequency
uint32_t PLL_BusClockFreq;

// stores ticks for 10us 100ns and 10ms based on clock frequency
uint32_t PLL_NumTicksPer10ms;
uint32_t PLL_NumTicksPer10us;
uint32_t PLL_NumTicksPer100ns;

//--------------PLL_Init80MHz
//Intializes pll to bus clock freq of 80MHz
//Inputs: none
//Outputs: none

void PLL_Init80MHz(void){
    // 0) Set USERCC2 bit in order to use RCC2
    SYSCTL_RCC2_R |= SYSCTL_RCC2_USERCC2;

    //1) Set bypass bit to pll for intializing
    SYSCTL_RCC2_R |= SYSCTL_RCC2_BYPASS2;

    // Clear and set the XTAL bits to 16 MHZ 
    SYSCTL_RCC2_R &= ~SYSCTL_RCC2_OSCSRC2_M;

    // Clear PWRDN for PLL
    SYSCTL_RCC2_R &= ~SYSCTL_RCC2_PWRDN2;

    //400 MHz PLL
    SYSCTL_RCC2_R &= ~SYSCTL_RCC2_DIV400;

    //Clear the SYSDIV2 bits and set to 0x4 (80 Mhz)
    SYSCTL_RCC2_R = (SYSCTL_RCC2_R & ~(SYSCTL_RCC2_SYSDIV2_M | SYSCTL_RCC2_SYSDIV2LSB)) | (0x4 << 22);

    // wait for pll to lock
    while((SYSCTL_RIS_R & SYSCTL_RIS_PLLLRIS) == 0);

    //Clear bypass
    SYSCTL_RCC2_R &= ~SYSCTL_RCC2_BYPASS2;

    // The bus frequency will be 80MHz
    PLL_BusClockFreq = 800000000;

    // Establish num ticks in 100ns for later
    PLL_NumTicksPer10ms = PLL_BusClockFreq * 0.01;

    // Establish num ticks in 100ns for later
    PLL_NumTicksPer10us = PLL_BusClockFreq * 0.00001;

    // Establish num ticks in 100ns for later
    PLL_NumTicksPer100ns = PLL_BusClockFreq * 0.0000001;
}