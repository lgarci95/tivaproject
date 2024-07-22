/*
* PWM.h - initialization of registers for pwm peripheral
*/

#ifndef PWM_H
#define PWM_H

#include <stdint.h>

// Name of PWM Channels
typedef enum{
    PWM0=0,
    PWM1=1,
    PWM2=2,
    PWM3=3,
    PWM4=4,
    PWM5=5,
    PWM6=6,
    PWM7=7
}PWMChannel;
// Name of PWM module
typedef enum{
    PWMModule0 = 0,
    PWMModule1 = 1
}PWMModule;

// Make a strucutre for module and channel
typedef struct{
    PWMModule module;
    PWMChannel channel;
}PWMDef_t;

// macro for intializing pwm instance
#define PWMDEF(module, channel) ((PWMDef_t){module,channel})

//-----------PWM_SetClockDivisor-----------
// Sets the PWM Clock Divisor
// Inputs: divisor-values are 1,2,3,4,8,16,32 and 64
// Outputs: none
void PWM_SetClockDivisor(uint8_t divisor);

//-----------PWM_Initialize-------------------
// Initializes the specified PWM module/channel
// Inputes: pwmDef - The PWM module/channel
// Outputs: none
void PWM_Initialize(PWMDef_t pwmDef);

//-----------PWM_Enable-------------------------
// Enables the specified PWM module/channel The channel
// must have been intialized before this.
// Inputs: pwmDef - the PWM module/channel, period, duty cycle
// Outputs: none
void PWM_Enable(PWMDef_t pwmDef, uint16_t period, uint16_t duty);

//-----------PWM_Disable--------------------
// Disables the specified PWM module/channel
// Inputs: pwmDef
// Outputs: none
void PWM_Disable(PWMDef_t pwmDef);

//----------PWM_SetDuty---------------------
// Sets the duty cycle for PWM instance
// Inputs: PWMDef and duty cycle
// Outputs: none
void PWM_SetDuty(PWMDef_t pwmDef, uint16_t duty);

#endif