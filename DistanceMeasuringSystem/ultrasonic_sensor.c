 /******************************************************************************
 *
 * Module: Ultrasonic Sensor driver
 *
 * File Name: ultrasonic_sensor.c
 *
 * Description: source file for the Ultrasonic Sensor driver
 *
 * Author: nada
 *
 *******************************************************************************/
#include"ultrasonic_sensor.h"
#include<util/delay.h>
#include"icu.h"
#include<math.h>

/*Initialize the ICU driver as required.
 *Setup the ICU call back function.
 *Setup the direction for the trigger pin as output pin through the
 *GPIO driver.*/

void Ultrasonic_init(void)
{/* Create configuration structure for ICU driver */
	Icu_ConfigType CONFIG ={F_CPU_8,RISING};
	Icu_init(&CONFIG); /*Initialize the ICU drive*/
	Icu_setCallBack(Ultrasonic_edgeProcessing); /*Setup the ICU call back function*/

	/*Setup the direction for trigger pin as output pin*/
	GPIO_setupPinDirection(trigger_PORT_ID, trigger_PIN_ID, PIN_OUTPUT);
}

/*Send the Trigger pulse to the ultrasonic .*/
void Ultrasonic_Trigger(void)
{ /*genrate trigger pulse*/
	GPIO_writePin(trigger_PORT_ID,trigger_PIN_ID , LOGIC_HIGH);
	_delay_us(10);
	GPIO_writePin(trigger_PORT_ID,trigger_PIN_ID , LOGIC_LOW);
}

/* Send the trigger pulse by using Ultrasonic_Trigger function.
 *Start the measurements by the ICU from this moment.*/

uint16 Ultrasonic_readDistance(void)
{ uint16 distance=0;

Ultrasonic_Trigger();
/*  waiting to get value of timeHigh to claculate distance   */
while(g_timeHigh==0);
/*    claculate distance from timeHigh  and diveded by 0.98 to remove error from 30 to above   */
distance= ((g_timeHigh/58.8)/0.98);
g_timeHigh =0; /*reset time*/

 return distance ;
}


