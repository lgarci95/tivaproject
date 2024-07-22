#ifndef SPI_H
#define SPI_H

#include <stdint.h>

// The names of the SSI modules
typedef enum{
    SSI0 = 0,
    SSI1 = 1,
    SSI2 = 2,
    SSI3 = 3
}SSIModule_t;

//------SPI_Enable------------------
// Enables the specified SSI module/channel for SPI
//Inputs: module - the SSI module name
//outputs: none
int SPI_Enable(SSIModule_t module);

//----SPI_Write
//Writes a byte of data to the SPI bus
//inputs: module-SSI module
//      : data - the data byte to write
//output: none
void SPI_Write(SSIModule_t module, uint8_t data);


#endif