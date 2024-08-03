 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the UART AVR driver
 *
 * Author: nada
 *
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "std_types.h"
/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
#define F_CPU 8000000

typedef enum
{	one_bit,two_bit
}UART_StopBit;

typedef enum
{rate1=10,rate2=300,rate3=600,rate4=1200,rate5=2400,rate6=4800,rate7=9600,
	rate8=14400,rate9=19200,rate10=38400
}UART_BaudRate;


typedef enum
{five_bit,six_bit,seven_bit,eight_bit,nine_bit=0x7
}UART_BitData;

typedef enum
{disapled,even=0x2,odd
}UART_Parity;

typedef struct{
 UART_BitData bit_data;
 UART_Parity parity;
 UART_StopBit stop_bit;
 UART_BaudRate baud_rate;
}UART_ConfigType;


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(const UART_ConfigType * Config_Ptr);

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_receiveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str);

/*
 * Description :
 * Receive the required string until the '=' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str); // Receive until =

#endif /* UART_H_ */
