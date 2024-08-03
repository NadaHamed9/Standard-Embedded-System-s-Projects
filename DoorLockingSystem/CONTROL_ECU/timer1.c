 /******************************************************************************
 *
 * Module: TIMER1 driver
 *
 * File Name: timer1.c
 *
 * Description: source file for the TIMER1 driver
 *
 * Author: nada
 *
 *******************************************************************************/
#include"timer1.h"
#include<avr/interrupt.h>
#include<avr/io.h>
/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_callBackPtr)(void) = NULL_PTR;

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/
ISR(TIMER1_OVF_vect)
{
	if(g_callBackPtr != NULL_PTR)
		{
			/* Call the Call Back function in the application after the edge is detected */
			(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
		}
}
ISR(TIMER1_COMPA_vect)
{
	if(g_callBackPtr != NULL_PTR)
		{
			/* Call the Call Back function in the application after the edge is detected */
			(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
		}
}
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 *Function to initialize the Timer driver
 *
 */
void Timer1_init(const Timer1_ConfigType * Config_Ptr)
{
	TCNT1=Config_Ptr->initial_value;

if(Config_Ptr->mode)
	{
	OCR1A=Config_Ptr->compare_value;
	/*enable interrupt module*/
	TIMSK=(1<<OCIE1A);
	}
else
{/*enable interrupt module*/
	TIMSK=(1<<TOIE1);
}

TCCR1A=(1<<FOC1A);
TCCR1B=(TCCR1B & 0xE7)|((Config_Ptr->mode)<<3);
TCCR1B=(TCCR1B & 0xF8)|((Config_Ptr->prescaler));

}
/*
 * Description :
 * Function to disable the Timer1.
 */
void Timer1_deInit(void)
{
	TCCR1A=0;
	TCCR1B=0;

}
/*
 * Description :
 *  Function to set the Call Back function address.
 */
void Timer1_setCallBack(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr = a_ptr;
}
