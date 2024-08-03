 /******************************************************************************
 *
 * Module: pwm driver "driver not finished yet"
 *
 * File Name:pwm.c
 *
 * Description: source file for the pwm driver
 *
 * Author: nada
 *
 *******************************************************************************/
#include"pwm.h"
#include<avr/io.h>

/*
 * Description :
 * The function responsible for trigger the Timer0 with the PWM Mode.
 * Setup the PWM mode with Non-Inverting.
 * Setup the prescaler with F_CPU/8.
 * Setup the compare value based on the required input duty cycle
 * Setup the direction for OC0 as output pin through the GPIO driver.
 * The generated PWM signal frequency will be 500Hz to control the DC
Motor speed.
 */
void PWM_Timer0_Init_Start(uint8 duty_cycle)
{/* start from initial value 0*/

	TCNT0=0;

	OCR0=((duty_cycle)*2.55);

	GPIO_setupPinDirection(Enable_PORT_ID, Enable_PIN_ID, PIN_OUTPUT);  /* set direction enable pin
	*/
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS01);
}
