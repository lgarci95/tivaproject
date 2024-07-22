/*
*
*/
#ifndef PLL_H
#define PLL_H

#include <stdint.h>

//holds current bus frequency
extern uint32_t PLL_BusClockFreq;

// stores ticks for 10us 100ns and 10ms based on clock frequency
extern uint32_t PLL_NumTicksPer10ms;
extern uint32_t PLL_NumTicksPer10us;
extern uint32_t PLL_NumTicksPer100ns;

//-------PLL_Init80MHz
// Sets PLL to bus clock freq 80MHz
//Inputs:none
//Outputs:none
void PLL_Init80MHz(void);
#endif