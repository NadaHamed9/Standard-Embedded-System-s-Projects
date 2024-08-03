 /******************************************************************************
 *
 * Module: DcMotor driver
 *
 * File Name: dc_motor.c
 *
 * Description: source file for the DcMotor driver
 *
 * Author: nada
 *
 *******************************************************************************/


#include"dc_motor.h"
#include"avr/io.h"
#include"pwm.h"

/*
 * Description :
 * Function responsible for initialize the DC MOTOR driver.
 */

void DcMotor_init(void)
{
	/* setup the direction for the two
motor pins */
	GPIO_setupPinDirection(DCMOTOR_IN1_PORT_ID ,DCMOTOR_IN1_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(DCMOTOR_IN2_PORT_ID ,DCMOTOR_IN2_PIN_ID, PIN_OUTPUT);
/*   stop DcMotorn  */
	GPIO_writePin(DCMOTOR_IN1_PORT_ID ,DCMOTOR_IN1_PIN_ID, LOGIC_LOW);
	GPIO_writePin(DCMOTOR_IN2_PORT_ID ,DCMOTOR_IN2_PIN_ID, LOGIC_LOW);

}

/*
 * Description :
 * The function responsible for rotate the DC Motor CW/ or A-CW or
 * stop the motor based on the state input state value.
 * Send the required duty cycle to the PWM driver based on the
 * required speed value.
 */
void DcMotor_Rotate(DcMotor_State state,uint8 speed)
{/*          select state of DcMotor by setting or clearing IN1 and IN2          */
	GPIO_writePin(DCMOTOR_IN1_PORT_ID ,DCMOTOR_IN1_PIN_ID, GET_BIT(state, DCMOTOR_IN1_PIN_ID));
	GPIO_writePin(DCMOTOR_IN2_PORT_ID ,DCMOTOR_IN2_PIN_ID, GET_BIT(state, DCMOTOR_IN2_PIN_ID));


/*          control speed of DcMotor using pwm timer0         */
	PWM_Timer0_Init_Start(speed);
}
