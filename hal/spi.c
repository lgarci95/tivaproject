/*
* SPI.c initali and config of spi modules
*/

#include "hal.h"
#include "tm4c123gh6pm.h"

// Base addresses of ssi module
#define SSI0_REG_BASE ((volatile uint32_t*) 0x40008000)
#define SSI1_REG_BASE ((volatile uint32_t*) 0x40009000)
#define SSI2_REG_BASE ((volatile uint32_t*) 0x4000A000)
#define SSI3_REG_BASE ((volatile uint32_t*) 0x4000B000)

// Register IO memory layout
typedef struct{
    uint32_t CR0;
    uint32_t CR1;
    uint32_t DR;
    uint32_t SR;
    uint32_t CPSR;
    uint32_t IM;
    uint32_t MIS;
    uint32_t ICR;
    uint32_t DMACTL;
    uint32_t RIS;
    uint32_t RESERVED[1000];
    uint32_t CC;
}SSIRegs_t;

// Resolve SSI module name to its base address
const volatile uint32_t* SSIBaseAddress[] = {
    SSI0_REG_BASE,
    SSI1_REG_BASE,
    SSI2_REG_BASE,
    SSI3_REG_BASE
};

//------------SPI_Enable------
// Enable SSI module/channel for SPI
// Inputs: SSI module
// Outputs: none
int SPI_Enable(SSIModule_t module){
    //Bus clock 80MHZ
    if (PLL_GetBusClockFreq() != 80000000){
        return -1;
    }
    //overlay SSIRegs_t on top of SSIBaseaddress
    volatile SSIRegs_t* ssi = (volatile SSIRegs_t*)SSIBaseAddress[module];
    switch(module){
        case SSI0:
            GPIO_EnableAltDigital(PORTA, 0x2C, 0x02);
            break;
        case SSI1:
            GPIO_EnableAltDigital(PORTD, 0x0B, 0x02);
            break;
    }
    uint8_t moduleBit = 0x1 << ((uint8_t)module);
    //Enable clock to SSI module
    SYSCTL_RCGCSSI_R |= moduleBit;

    // wait for SSI peripheral
    while(!(SYSCTL_PPSSI_R & moduleBit)){}

    //SSI module and make it master
    ssi->CR1 = 0;

    // system clock
    ssi->CC= 0;

    //CPOL=0, CPHA=0, SPI format, 16bit data
    ssi->CR0 = SSI_CR0_DSS_8;

    // Prescale = 80 => Bitrate = 1MHz, assuming bus clock is 80 MHz
    ssi->CPSR = 80;

    //Set SSE bit to enable SSI module.
    ssi->CR1 |= SSI_CR1_SSE;

    return 0;

}

//------------SPI_Write------
// Wrties bytes to spi bus
// Inputs: SSI module and data
// Outputs: none
void SPI_Write(SSIModule_t module, uint8_t data){
    //overlay SSIRegs_t on top of SSIBaseaddress
    volatile SSIRegs_t* ssi = (volatile SSIRegs_t*)SSIBaseAddress[module];
    
    //wait until fifo not full
    while((ssi->SR & SSI_SR_TNF) == 0);

    // Transmit 8 bits
    ssi->DR = data;

    // wait until complete transmission
    while (ssi->SR& SSI_SR_BSY);
}