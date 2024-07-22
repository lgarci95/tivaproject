/*
* Flash.h - intializie and enable flash ROM regsters for
* TM4C123gh6pm 
*/
#ifndef FLASH_H
#define FLASH_H

// The TM4C123 has 256 kilobytes of flash memory located at addresses 0 to 0x003FFFF
// Make sure the base address does not overlap with code and data
// Examine the linker's .map file to see where code/data is stored

#define FLASH_BLOCK_SIZE_WORDS 256
//------------------Flash_Enable----------
// Enable the Flash module. Must be called once to Erase
// Inputs: none
// Outputs: none
void Flash_Enable(void);
//-----------------Flash_Erase----------
// Erases a block for Flash memory
// Inputs: blockCOunt - the number of blocks to erase.
//Outputs: none
int Flash_Erase(volatile uint32_t* address, int blockCount);
//----------------Flash_Write--------------
// Writes data to flash memory
// inputs: data - a pointer to the data to write. must
// be a multiple of words in size.
// word count- the number of words of data to write.
int Flash_Write(volatile uint32_t* address, const void* data, int wordCount);
//---------------FLash_Read--------------------
// Reads data from flash memory
// Inputs: data - pointer to the data buffer where Flash Memory will 
// be copied
// WordCOunt - the number of words of data to read
void Flash_Read(volatile uint32_t* address, void* data, int wordCount);

#endif