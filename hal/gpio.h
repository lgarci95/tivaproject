/*
* GPIO.h - intializaton and config of gpio pins with alternative functions/peripherals
*/
#ifndef GPIO_H_
#define GPIO_H_

#include <stdint.h>

//Names for output drive strength
typedef enum{
    DRIVE_2MA, 
    DRIVE_4MA,
    DRIVE_8MA
}GPIO_Drive_t;

//Names for pull up resistor types
typedef enum{
    PULL_NONE,
    PULL_UP,
    PULL_DOWN
}GPIO_Pull_t;

//Names for the edge detectors
typedef enum{
    INT_TRIGGER_NONE,
    INT_TRIGGER_LOW_LEVEL,
    INT_TRIGGER_HIGH_LEVEL,
    INT_TRIGGER_RISING_EDGE,
    INT_TRIGGER_FALLING_EDGE,
    INT_TRIGGER_BOTH_EDGES,
}GPIO_IntTrigger_t;

//Signature of GPIO callback function
typedef void (*PFN_GPIOCallback)(Ports_t port, uint32_t pinMap);

//--------------GPIO_InitPort------------
//Initializes GPIO port for IO usage
//Inputs: Ports A-F
//Outputs: none
void GPIO_InitPort(Ports_t port);

//------------GPIO_EnableDO---------------
// Enables GPIO pins for digital output
//Inputs: ports, pinmap, drive, and pull
//Outputs: none
void GPIO_EnableDO(Ports_t port, uint8_t pinMap, GPIO_Drive_t drive, GPIO_Pull_t pull);
//------------GPIO_EnableDI
//Enables GPIO pins for digital input
//Inputs: ports, pinMap, pull
//Outputs:none
void GPIO_EnableDI(Ports_t port, uint8_t pinMap, GPIO_Pull_t pull);
//------------GPIO_EnableAltDigital-------------
//Enables a set of pins on a GPIO port for alternate digital function
//Inputs: port, pinmaps
//Outputs: none
void GPIO_EnableAltAnalog(Ports_t port, uint8_t pinMap);

//------------------------- GPIO_GetBitBandIOAddress --------------------
// Gets the bit-band IO address for a pin definition.
// Inputs:  pinDef - pin definition
// Outputs:  pointer with value of bit band address.
volatile uint32_t* GPIO_GetBitBandIOAddress(const PinDef_t* pinDef);

//------------------------- GPIO_EnableInterrupt ----------------------
// Enables an interrupt for the given port.  
// Inputs:
// Outputs: 
int GPIO_EnableInterrupt(const PinDef_t* pinDef, uint8_t priority, GPIO_IntTrigger_t trigger, PFN_GPIOCallback callback);

//------------------------- GPIO_DisarmInterrupt ----------------------
// Disarms an interrupt for the given port after being enabled and armed.  
// Inputs:
// Outputs: 
void GPIO_DisarmInterrupt(const PinDef_t* pinDef); 

//------------------------- GPIO_RearmInterrupt ----------------------
// Rearms an interrupt for the given port after being enabled and disarmed.  
// Inputs:
// Outputs: 
void GPIO_RearmInterrupt(const PinDef_t* pinDef); 



#endif