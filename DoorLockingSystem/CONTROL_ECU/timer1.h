 /******************************************************************************
 *
 * Module: TIMER1 driver
 *
 * File Name: timer1.h
 *
 * Description: header file for the TIMER1 driver
 *
 * Author: nada
 *
 *******************************************************************************/

#ifndef TIMER1_H_
#define TIMER1_H_
#include"std_types.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum
{	FCPU_0,FCPU_1,FCPU_8,FCPU_64,FCPU_256,FCPU_1024
}Timer1_Prescaler;

/*
 * compare_match_op1: Toggle OC1A/OC1B on compare match
 * compare_match_op2: Clear OC1A/OC1B on compare match
 * compare_match_op3: Set OC1A/OC1B on compare match
 * */

typedef enum
{
	normal,ctc
}Timer1_Mode;


typedef struct {
 uint16 initial_value;
 uint16 compare_value; // it will be used in compare mode only.
 Timer1_Prescaler prescaler;
 Timer1_Mode mode;
} Timer1_ConfigType;


/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description :
 *Function to initialize the Timer driver
 *
 */
void Timer1_init(const Timer1_ConfigType * Config_Ptr);

/*
 * Description :
 * Function to disable the Timer1.
 */
void Timer1_deInit(void);

/*
 * Description :
 *  Function to set the Call Back function address.
 */
void Timer1_setCallBack(void(*a_ptr)(void));



#endif /* TIMER1_H_ */
