 /******************************************************************************
 *
 * Module: DcMotor driver
 *
 * File Name: dc_motor.h
 *
 * Description: header file for the DcMotor driver
 *
 * Author: nada
 *
 *******************************************************************************/

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_
#include"gpio.h"
#include"common_macros.h"
#include"std_types.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define DCMOTOR_IN1_PORT_ID          PORTB_ID
#define DCMOTOR_IN1_PIN_ID           PIN0_ID
#define DCMOTOR_IN2_PORT_ID          PORTB_ID
#define DCMOTOR_IN2_PIN_ID           PIN1_ID

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef enum
{
	Stop,Anti_clockwise,Clockwise
}DcMotor_State;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for initialize the DC MOTOR driver.
 */
void DcMotor_init(void);
/*
 * Description :
 * The function responsible for rotate the DC Motor CW/ or A-CW or
 * stop the motor based on the state input state value.
 * Send the required duty cycle to the PWM driver based on the
 * required speed value.
 */
void DcMotor_Rotate( DcMotor_State state,uint8 speed);


#endif /* DC_MOTOR_H_ */
