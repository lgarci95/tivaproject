/*
*   HAL.h - Hardware abstraction layer for TM4C123gh6pm
*/

#ifndef HAL_H
#define HAL_H

#include "NVIC.h"
#include "PLL.h"
#include "SysTick.h"
#include "uart.h"
#include "GPIO.h"
#include "ADC.h"
#include "pwm.h"
#include "timers.h"
#include "SPI.h"
#include "flash.h"

#include <stdint.h>
// TM4C123 I/O PORTS A-F
typedef enum {
    PORTA = 0,
    PORTB = 1,
    PORTC = 2,
    PORTD = 3,
    PORTE = 4,
    PORTF = 5
}Ports_t;
// TM4C123 I/O pins. bit flags and OR'd together pin maps

typedef enum {
    PIN0 = 0x01,
    PIN1 = 0x02,
    PIN2 = 0x04,
    PIN3 = 0x08,
    PIN4 = 0x10,
    PIN5 = 0x20,
    PIN6 = 0x40,
    PIN7 = 0x80
} Pins_t;

// This is an abstract definition for a port/ pin combination
typedef struct {
    Ports_t         port;
    Pins_t          pin;
} PinDef_t;

// Convenience macro to intialize a PinDef_t instance
#define PINDEF(port,pin)               ((PinDef_t) {port, pin})

#endif
