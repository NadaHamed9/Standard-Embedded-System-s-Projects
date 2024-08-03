/*
 ================================================================================================
 Name        :hmi_ecu.c
 Author      : nada
 Description : HMI_ECU is just responsible interaction with the user just take inputs through keypad
               and display messages on the LCD.
 Date        : 31/10/2022
 ================================================================================================
 */
#include"keypad.h"
#include"lcd.h"
#include"timer1.h"
#include"uart.h"
#include<util/delay.h>
#include<avr/io.h>
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define matched 0x01
#define unmatched 0x00
#define enter 13
#define ready 0xf
uint8 pressed;
uint8 flag=0;
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Description :
 * Function takes passowrd entered and send it to control_ecu.
 */
void pass(uint8 row, uint8 col);
/*
 * Description :
 * Function to create passowrd and receive checking.
 */
void create_pass(void);
/*
 * Description :
 * Function to take option entered and send it to cotnrol_ecu.
 */
void options(void);
/*
 * Description :
 * Function to open door.
 */
void open(void);
/*
 * Description :
 * Function to chechk login pass with saved.
 */
void login_pass(void);
/*
 * Description :
 * Function to change pass.
 */
void change_pass(void);
/*
 * Description :
 * Function control display of error message.
 */
void error_time(void);
int main(void)
{
	UART_ConfigType info_uart={six_bit,disapled,one_bit,rate7};
	SREG|=(1<<7);    /*         enable I-bit      */
	LCD_init();/*     intialize LCD       */
	UART_init(&info_uart);/*     intialize   UART    */
	create_pass();
	while(1)
	{

	}
}

void pass(uint8 row, uint8 col)
{uint8 password[5];
uint8 i;
LCD_moveCursor(row,col);

for( i=0;i<5;i++)
{
	pressed=KEYPAD_getPressedKey();

	if(pressed>=0 && pressed<=9)
	{
		LCD_displayCharacter('*');
		/*LCD_intgerToString(pressed);*/
		password[i]=pressed;
		_delay_ms(500);

	}
	/*if user entered symbol dont count it*/
	else i--;
}

while(KEYPAD_getPressedKey() != enter)
{
	/*     wait for user to press enter    */
}

for(int i=0;i<5;i++)
{/*    sending pass to control_ECU   */
	UART_sendByte(password[i]);
}
}

void create_pass(void)
{    LCD_clearScreen();
LCD_displayString("Plz enter pass: ");
/*      taking pass1    */
pass(1,0);
LCD_clearScreen();
LCD_displayString("Plz re-enter the ");
LCD_moveCursor(1,0);
LCD_displayString("same pass:  ");
/*      taking pass2    */
pass(1,11);
/*    wait till mc2 till me its matched or not     */

if(UART_receiveByte()==unmatched)
{/*          repeat step1        */
	LCD_clearScreen();
	LCD_displayString("unmatching ");
	_delay_ms(1000);
	create_pass();
}
else
{/*       pass matched      */
	LCD_clearScreen();
	LCD_displayString("matching ");
	_delay_ms(1000);
	/*display main options*/
	options();}
}
void options(void)
{
	LCD_clearScreen();
	LCD_displayString("+ : Open Door  ");
	LCD_moveCursor(1,0);
	LCD_displayString("- : Change Pass  ");

	pressed=KEYPAD_getPressedKey();
	_delay_ms(500);
	/*        Press time      */
	while(pressed!='+' && pressed!='-')
	{
		/*     wait till user choose option     */
		pressed=KEYPAD_getPressedKey();
		_delay_ms(500);
		/*        Press time      */
	}

	while(UART_receiveByte()!=ready)
			{
				/*     wait control_ecu ready to recieve      */
			}
	switch(pressed)
	{


	case'+':


		UART_sendByte('+');
		login_pass();

		break;

	case'-':


		UART_sendByte('-');
		change_pass();
		break;
	}
}
void login_pass(void)
{  static uint8 count=0;
Timer1_ConfigType info_timer1={0,0,FCPU_64,normal};

LCD_clearScreen();
LCD_displayString("Plz enter pass: ");
pass(1,0);

/*    wait till mc2 till me its matched or not     */
if(UART_receiveByte()==unmatched)
{        count++;
if(count==3)
{count=0;

Timer1_init(&info_timer1);/*intialize timer1*/
Timer1_setCallBack(error_time);

LCD_clearScreen();
/*the two passwords are not matched for the third consecutive time*/
LCD_displayString(" ERROR ");
while(!flag)
{
	/*wait for time stop counting*/
}
flag=0;
options();
}

/*     if pass is unmatching       */
login_pass();
}
/*       if pass matched          */
else
{  count=0;
Timer1_init(&info_timer1);/*   intiallize timer1   */
Timer1_setCallBack(open);
LCD_clearScreen();
LCD_displayString("Door is opening");
while(!flag)
{
	/*   wait till timer stop counting   */
}
flag=0;
options();

}}

void change_pass(void)
{Timer1_ConfigType info_timer1={0,0,FCPU_64,normal};
static uint8 count=0;

LCD_clearScreen();
LCD_displayString("Plz enter old pass: ");
pass(1,0);
/*    wait till mc2 till me its matched or not     */
if(UART_receiveByte()==unmatched)
{        count++;
if(count==3)
{count=0;
Timer1_init(&info_timer1);/*intialize timer1*/
Timer1_setCallBack(error_time);
LCD_clearScreen();
LCD_displayString(" ERROR ");
while(!flag)
{
	/*wait for time stop counting*/
}
flag=0;
options();
}
/*     if pass is unmatching       */
change_pass();
}
else
{  count=0;
create_pass();

}
}
void error_time(void)
{flag=0;
static uint8 tick=0;
tick++;
if(tick==120)
{/*display error message for 1min*/
	LCD_clearScreen();
	Timer1_deInit();
	tick=0;
	flag=1;
}
}
void open(void)
{static uint8 tick=0;
flag=0;
tick++;
if(tick==36)
{
	LCD_clearScreen();
	LCD_displayString("Door is Locking");


}
if(tick==66)
{   tick=0;
Timer1_deInit();
flag=1;
}
}
