/*
 ================================================================================================
 Name        : mini_project3.c
 Author      : nada
 Description : Fan Controller system
  Date        : 7/10/2022
 ================================================================================================
 */

#include"lm35_sensor.h"
#include"lcd.h"
#include"adc.h"
#include"dc_motor.h"


int main(void)
{uint8 temp;
/*Configure ADC Driver to operate using the internal reference voltage 2.56
 *voltage and prescaler F_CPU/8.
 */
Config.prescaler=divisionFactor_8;
Config.ref_volt=INTERNAL;

DcMotor_init(); /* initialize DC motor driver */
LCD_init(); /* initialize LCD driver */
ADC_init(&Config); /* initialize ADC driver */

/* Display this string "FAN is  " only once on LCD at the first row */
LCD_displayStringRowColumn(0,4,"FAN is    ");
/* Display this string "Temp =     c " only once on LCD at the second row */
LCD_displayStringRowColumn(1,4,"Temp =    c");
while(1)
{
	temp=LM35_getTemperature();
	if(temp <30)
	{
		DcMotor_Rotate(Stop,0);
		/* Display the Fan state at row 1 col. 11 */
		LCD_moveCursor(0,11);
		LCD_displayString("OFF");
		/* Display the temperature value at second row col. 11 */
		LCD_moveCursor(1,11);

		LCD_intgerToString(temp);
		/* In case the digital value is two or one digits print space in the next digit place */
		LCD_displayCharacter(' ');

	}
	else if(temp>=30 && temp<60)
	{
		DcMotor_Rotate(Clockwise,25);
		/* Display the Fan state at row 1 col. 11 */
		LCD_moveCursor(0,11);
		LCD_displayString("ON");
		/* In case the digital value is two or one digits print space in the next digit place */
		LCD_displayCharacter(' ');

		/* Display the temperature value at second row col. 11 */
		LCD_moveCursor(1,11);
		LCD_intgerToString(temp);
		/* In case the digital value is two or one digits print space in the next digit place */
		LCD_displayCharacter(' ');
	}
	else if(temp>=60 && temp<90)
	{
		DcMotor_Rotate(Clockwise,50);
		/* Display the Fan state at row 1 col. 11 */
		LCD_moveCursor(0,11);
		LCD_displayString("ON");
		/* In case the digital value is two or one digits print space in the next digit place */
		LCD_displayCharacter(' ');

		/* Display the temperature value at second row col. 11 */
		LCD_moveCursor(1,11);
		LCD_intgerToString(temp);
		/* In case the digital value is two or one digits print space in the next digit place */
		LCD_displayCharacter(' ');
	}
	else if(temp>=90 && temp<120)
	{
		DcMotor_Rotate(Clockwise,75);
		/* Display the Fan state at row 1 col. 11 */
		LCD_moveCursor(0,11);
		LCD_displayString("ON");
		/* In case the digital value is two or one digits print space in the next digit place */
		LCD_displayCharacter(' ');

		/* Display the temperature value at second row col. 11 */
		LCD_moveCursor(1,11);
		if(temp>=100)
		{
			LCD_intgerToString(temp);}
		else {
	   /* In case the digital value is two or one digits print space in the next digit place */
			LCD_intgerToString(temp);
			LCD_displayCharacter(' ');
		}
	}
	else if(temp>=120)
	{
		DcMotor_Rotate(Clockwise,100);
		/* Display the Fan state at row 1 col. 11 */
		LCD_moveCursor(0,11);
		LCD_displayString("ON");
		/* In case the digital value is two or one digits print space in the next digit place */
		LCD_displayCharacter(' ');

		/* Display the temperature value at second row col. 11 */
		LCD_moveCursor(1,11);
		LCD_intgerToString(temp);
	}
}
}


