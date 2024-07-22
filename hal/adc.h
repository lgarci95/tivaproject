/*
* ADC.h initialization and config for adc modules
*/
#ifndef ADC_H
#define ADC_H

#include <stdint.h>

// TM4c analog input channels
typedef enum{
    AIN0 = 0,
    AIN1 = 1,
    AIN2 = 2,
    AIN3 = 3,
    AIN4 = 4,
    AIN5 = 5,
    AIN6 = 6,
    AIN7 = 7,
    AIN8 = 8,
    AIN9 = 9,
    AIN10 = 10,
    AIN11 = 11
}ADCChannel;

// TM4C has 2 ADC modules
typedef enum{
    ADC0 = 0,
    ADC1 = 1
}ADCModule;

// ADC module and channel strucuture
typedef struct{
    ADCChannel channel;
    ADCModule module;
}AnalogDef_t;

// A macro for initializing and ADC instance
#define ANALOGDEF(module, channel) ((AnalogDef_t){channel, module})

//----------------==ADC_Enable------------
// Enables hardware and other things for ADC instance
// Inputs: ADC module and channel
// Outputs: none
void ADC_Enable(ADCModule module, ADCChannel channel);

//----------------ADC_Sample--------------
//Reads the digital output of the enabled ADC module
//Inputs: module - the ADC module 
// Outpus: none
uint32_t ADC_Sample(ADCModule module);
#endif
