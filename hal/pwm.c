/*
* PWM.c - PWM functions for TM4C123gh6pm
*/

#include <stdint.h>
#include <assert.h>
#include "hal.h"
#include "tm4c123gh6pm.h"

// These are base I/O addresses of the PWM Modules.
#define PWM0_REG_BASE ((volatile uint32_t *)0x40028000)
#define PWM1_REG_BASE ((volatile uint32_t *)0x40029000)

// This structure represents the registers associated with a PWM generator
typedef struct{
    uint32_t _CTL;
    uint32_t _INTEN;
    uint32_t _RIS;
    uint32_t _ISC;
    uint32_t _LOAD;
    uint32_t _COUNT;
    uint32_t _CMPA;
    uint32_t _CMFB;
    uint32_t _GENB;
    uint32_t _GENA;
    uint32_t _DBCTL;
    uint32_t _DBRISE;
    uint32_t _DBFALL;
    uint32_t _FLTSRC0;
    uint32_t _FLTSRC1;
    uint32_t _MINFLTPER;
} PWMGenRegs_t;

// This structure represents the registers associated with a PWM module.
// It will be overlayed on top of I/O memory so that the structure fields
// map to the registers. 

typedef struct {
    uint32_t CTL;
    uint32_t SYNC;
    uint32_t ENABLE;
    uint32_t INVERT;
    uint32_t FAULT;
    uint32_t INTEN;
    uint32_t RIS;
    uint32_t ISC;
    uint32_t STATUS;
    uint32_t FAULTVAL;
    uint32_t ENUPD;
    uint32_t RESERVED[5];

    // Generator overlays
    PWMGenRegs_t gen[4];

    uint32_t RESERVED1[432];
    uint32_t _0_FLTSEN;
    uint32_t _0_FLTSTAT0;
    uint32_t _0_FLTSTAT1;
    uint32_t RESERVED2[29];
    uint32_t _1_FLTSEN;
    uint32_t _1_FLTSTAT0;
    uint32_t _1_FLTSTAT1;
    uint32_t RESERVED3[30];
    uint32_t _2_FLTSTAT0;
    uint32_t _2_FLTSTAT1;
    uint32_t RESERVED4[30];
    uint32_t _3_FLTSTAT0;
    uint32_t _3_FLTSTAT1;
    uint32_t RESERVED5[397];
    uint32_t PP;
}PWMRegs_t;

// This array is a look up table to resolve the PWM module name to its base address.
const volatile uint32_t* PWMBaseAddress[] = {
    PWM0_REG_BASE,
    PWM1_REG_BASE,
};

void PWM_SetClockDivisor(uint8_t divisor){
    // Must Enable the PWM Clock before setting the divisor, otherwise a
    // fault exception will get raised while configuring the PWM Channel.
    SYSCTL_RCGCPWM_R |= 1;
    // Find the right-most, non zero bit.
    uint8_t value = 0;
    for (; value < 8 && !(divisor & 0x1); value++, divisor >>=1);

    if (value > 0){
        // Clear then set the PWMDIV field. The divisor bits are D19-D17
        SYSCTL_RCC_R &= ~SYSCTL_RCC_PWMDIV_M;
        SYSCTL_RCC_R |= ((uint32_t)(value-1)<<17);

        // Enable the PWM Clock divisor.
        SYSCTL_RCC_R |= SYSCTL_RCC_USEPWMDIV; 
    }
    else{
        // Disable the PWMclock divisor. PWM modules will now be fed the system clock.
        SYSCTL_RCC_R &= ~SYSCTL_RCC_USEPWMDIV;
    }
}

void PWM_Initialize(PWMDef_t pwmDef){
    // NOTES: 
    // In the datasheet, the RCGC0 register is mentioned as a legacy way
    // to enable/disable clocking to the PWM modules. RCGCPWM should 
    // be used instead.
    //Don't confuse SYSCTL_PRRPWM_R with SYSCTL_PPPWM_R. 
    // may be used to determine which PWM modules are implemented on the
    // microcontroller. PRPWM should be used here to check when the PWM modules
    // are ready after their clocks are enabled.

    // Overlay the PWM register structure on top of the PWMx memory region
    volatile PWMRegs_t* pwm = (volatile PWMRegs_t*)PWMBaseAddress[pwmDef.module];

    // Right-shift the channel to obtain the generator number.
    // PWM0/1 -> GEN0, PWM2/3 -> GEN1, PWM4/5 -> GEN2, PWM6/7 -> GEN3
    volatile PWMGenRegs_t* gen = &pwm->gen[(int)pwmDef.channel >> 1];

    switch(pwmDef.module){
        // Enable the module's clock and wait until its ready
        case PWMModule0:

            SYSCTL_RCGCPWM_R |= 1;
            while (!(SYSCTL_PRPWM_R &1)) {};

            // Disable the generator.
            gen->_CTL = 0;

            switch(pwmDef.channel){
                // Generator 0
                case PWM0: //PB6
                    // Set PCTL field for PB6 to 0x4 for PWM.
                    GPIO_EnableAltDigital(PORTB, 0x40, 0x4);
                    // Drive PWM0 HIGH when counter matches comparator a while counting down
                    // and drive LOW when counter reaches zero.
                    gen->_GENA = PWM_0_GENA_ACTCMPAD_ONE | PWM_0_GENA_ACTLOAD_ZERO;
                    break;
                // Genearator 1
                case PWM3: // PB5
                    // SET PCTL field for PB5 to 0x4 for PWM.
                    GPIO_EnableAltDigital(PORTB, 0x20, 0x4);

                    // Drive PWM3 HIGH when counter matches comparator A while counting down
                    // and drive LOW when counter reaches zero.
                    gen->_GENB = PWM_1_GENB_ACTCMPAD_ONE | PWM_2_GENA_ACTLOAD_ZERO;
                    break;
                case PWM4: // PE4
                    // SET PCTL field for PE4 to 0x4 for PWM
                    GPIO_EnableAltDigital(PORTE, 0x10, 0x4);

                    // Drive PWM4 HIGH when counter matches comparator A while counting down
                    // and drive LOW when counter reaches zero.
                    gen->_GENA = PWM_2_GENA_ACTCMPAD_ONE | PWM_2_GENA_ACTLOAD_ZERO;



            }

    }

}

void PWM_Enable(PWMDef_t pwmDef, uint16_t period, uint16_t duty){
    // Overlay the PWM register structure on top of the PWMx memory region
    volatile PWMRegs_t* pwm = (volatile PWMRegs_t*)PWMBaseAddress[pwmDef.module];
    // Right shift the channel to obtain the generator number.
    volatile PWMGenRegs_t* gen = &pwm->gen[(int)pwmDef.channel>>1];
    // Disable the generator.
    gen->_CTL = 0;

    // Set the count preset which will determine the period.
    gen->_LOAD = period - 1;
    // Set the duty cycle count.
    gen->_CMPA = duty -1;
    // Enable the generator
    gen->_CTL |= 0x01;
    //Start the PWM
    pwm->ENABLE |= (0x1 << (int)pwmDef.channel);
}

void PWM_Disable(PWMDef_t pwmDef){
    // Overlay the PWM REGSITER structure on top of the PWMx memory region...
    volatile PWMRegs_t* pwm = (volatile PWMRegs_t*)PWMBaseAddress[pwmDef.module];
    pwm->ENABLE &= ~(0x1 << (int)pwmDef.channel);

}

void PWM_SetDuty(PWMDef_t pwmDef, uint16_t duty){
    // Overlay the PWM Register strucutre on top of the PWMx memeory region....
    volatile PWMRegs_t* pwm = (volatile PWMRegs_t*)PWMBaseAddress[pwmDef.module];

    // Right shift the channel to obtain the generator number
    volatile PWMGenRegs_t* gen = &pwm->gen[(int)pwmDef.channel >> 1];

    gen->_CMPA = duty -1;
}