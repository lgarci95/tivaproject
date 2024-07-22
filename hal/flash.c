/*
* Flash.c flash ulities 
*/
#include "hal/hal.h"
#include "tm4c123gh6pm.h"
// This holds the key required for erase and write operations.
// Set it during Enable().
static uint16_t flashkey = 0;

//----------Flash_Enable------------
// Enable the FLASH HAL module. Must be called once prior
// to erase, write and read operations.
// inputs: none
// outputs: none
void Flash_Enable(void){
    // If the key flag (bit 4) is set, then the key is 0xA42.
    // otherwise the key is 0x71D5 (pg.583)
    if (FLASH_BOOTCFG_R & 0x10){
        flashkey = 0xA442;
    }
    else{
        flashkey = 0x71D5;
    }
}

//-------------FLash_Erase----------
// Inputs: block count - number of blocks to erase
// address of words
//Outputs: none
int Flash_Erase(volatile uint32_t* address, int blockCount){
    // Make sure Enable was called
    if (flashkey == 0){
        return -1;
    }
    for(int i = 0; i<blockCount; i++){
        // Clear then set the OFFSET (17:0) with the write address.
        FLASH_FMA_R &= 0xFFFC0000;
        // Blocks are erased on 1 kilobyte boundaries, so multiply the index
        // by 1024 and add this to the base address.
        FLASH_FMA_R |= ((uint32_t)address) + (i*1024);

        // Set teh ERASE command bit.
        FLASH_FMC_R = (flashkey << 16) | 0x2;

        //Poll the ERASE bit until it is cleared.
        while(FLASH_FMC_R & 0x2){}
    }
    return 0;

    
}

//--------------------Flash_Write-----------------
// Writes data to Flash memory
// Inputs: data - a pointer to the data to write. Must be a multiple of words
// in size.
// Outputs: wordCounter - the number of words of data to write.
int Flash_Write(volatile uint32_t* address, const void* data, int wordCount){
    // make sure Enable was called.
    if (flashkey == 0){
        return -1;
    }
    // Must erase the data first. A write may only change a bit from 0 to 1,
    //so if the bit is already zero, the write fails. Erasing will set all bits
    // to 1's. Calculate the number of 1 kilo bytes that the data will span and erase
    //
    int blockCount = (((wordCount * sizeof(uint32_t))+ 1023)/1024);
    Flash_Erase(address, blockCount);
    // Write one word at a time.....
    for (int i = 0; i<wordCount; i++){
        // Set the data register. This the word that will be written.
        FLASH_FMD_R = ((volatile uint32_t*)data)[i];
        // Clear then set the OFFSET address field(17:0) with the write address.
        FLASH_FMA_R &= 0xFFFC0000;
        FLASH_FMA_R |= (uint32_t)address + (i *sizeof(uint32_t));

        // Trigger a write operation....
        FLASH_FMC_R = (flashkey << 16 ) | 0x1;
        // Poll the write bit until it is cleared/
        while(FLASH_FMC_R & 0x1){}

    }
    return 0;


}

//------------------Flash_Read---------------------
// Reads data from FLash memory
// Inputs data - a pointer to the data buffer where flash memory will be copied
// Outputs: wordCount- the number of words of data to read
void Flash_Read(volatile uint32_t* address, void* data, int wordCount){
    // Copy the count of bytes into the target data buffer
    for (int i = 0; i<wordCount; i++){
        ((uint32_t*)data)[i] =  address[i]; 
    }
}