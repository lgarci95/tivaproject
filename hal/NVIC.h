/*
* NVIC.h
*/

#ifndef NVIC_H
#define NVIC_H

#include <stdint.h>

void NVIC_EnableIRQ(uint8_t irq, uint8_t priority);
void NVIC_Disable(uint8_t irq);

#endif