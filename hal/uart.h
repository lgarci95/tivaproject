/* 
* Uart.h - intialization and read / write config 
*/

#ifndef UART_H
#define UART_H

#include <stdint.h>

// Signature of the Receive (RX) character callback function
typedef void (*PFN_RxCallback)(char c);

// IDs for the ports.
typedef enum{
    UART0,
    UART1,
    UART2,
    UART3,
    UART4, 
    UART5,
    UART6,
    UART7
}UART_ID_t;

//--------------UART_Enable-------------
// Enables the specified UART for 8,N,1 and the 
// specified baud rate.
// Inputs: uartId - the ID of the uart.
//          baud - baud rate to configure, e.g 9600, 18200, etc.
// Outputs none
int UART_Enable(UART_ID_t uartId, uint32_t baud);

//----------------UART_WriteChar-----------
// Write a character to a UART.
// Inputs: uartId - the ID of the uart.
//          c - character to write.
// Outputs: none.
void UART_WriteChar(UART_ID_t uartId, char c);

// --------------UART_WriteString------------
// Writes a null terminated string to a UART.
// Inputs: uartId - the ID of the uart.
//          s - null terminated string to write.
// Outputs: none
void UART_WriteString(UART_ID_t uartId, char* s);
//-------------UART_ReadChar------------------
// Reads a character from a UART. THe function  blocks
//until a character is received.
// Inputs: uartId - the ID of the uart.
// outputs none.
char UART_ReadChar(UART_ID_t uartId);
//------------UART_ENABLERXInterrupt----------
// Enables a receive (Rx) interrupt for a given Uart.
// The callback function is invoked whenever a character
// is received and interrupt occurs.
// inputs: uartId- the ID of the uart.
// priority- interrupt priority (0-7) 
// callback- the callback function to invoke.
//outputs: none.
int UART_EnableRxInterrupt(UART_ID_t uartId, uint8_t priority, PFN_RxCallback callback);
#endif




