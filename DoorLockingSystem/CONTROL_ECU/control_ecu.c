/*
 ================================================================================================
 Name        : control_ecu.c
 Author      : nada
 Description : CONTROL_ECU is responsible for all the processing and decisions in the system like password
               checking, open the door and activate the system alarm.
 Date        : 31/10/2022
 ================================================================================================
 */

#include"dc_motor.h"
#include"pwm_timer0.h"
#include"external_eeprom.h"
#include"uart.h"
#include"timer1.h"
#include"buzzer.h"
#include<util/delay.h>
#include<avr/io.h>
#include"twi.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define matched 0x01
#define unmatched 0x00
#define enter 13
#define ready 0xf
#define address 0x0311

uint8 pass1[5];
uint8 pass2[5];
uint8 flag=0;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function control DCMOTOR state.
 */
void control_dcmotor(void);
/*
 * Description :
 * Function receive 2 passowrds from HMI_ECU
 */
void save_pass(void);
/*
 * Description :
 * Function check matching of the two pass.
 */
void check_matching(uint8 *pass1,uint8 *pass2);
/*
 * Description :
 * Function receive option entered from user.
 */
void detect_option(void);
/*
 * Description :
 * Function check login pass with saved pass.
 */
void check_login_pass(void);
/*
 * Description :
 * Function change pass saved in EEPROM.
 */
void change_pass(void);
/*
 * Description :
 * Function deactivate buzzer after 1min.
 */
void deactivate_buzzer(void);
/*
 * Description :
 * Function store pass if matched in EEPROM.
 */
void store_memory(uint8*pass1);


int main(void)
{
	TWI_ConfigType info_twi={my_address,fast_mode};
	UART_ConfigType info_uart={six_bit,disapled,one_bit,rate7};
	SREG|=(1<<7);     /*         enable I-bit           */
	DcMotor_Init();  /*       intialize DCMOTOR        */
	Buzzer_init();  /*       intialize Buzzer         */
	TWI_init(&info_twi);/*       intialize TWI       */
	UART_init(&info_uart);/*       intialize UART   */


	while(1)
	{

		save_pass();

	}
}

void save_pass(void)
{
	for(int i=0;i<5;i++)
	{/*       receive pass1        */
		pass1[i]=UART_receiveByte();

	}
	for(int i=0;i<5;i++)
	{/*       receive pass2        */
		pass2[i]=UART_receiveByte();

	}/*       check two passwords       */
	check_matching(pass1,pass2);

}


void check_matching(uint8 *pass1,uint8 *pass2)
{
	for(int i=0;i<5;i++)
	{
		if(pass1[i]!=pass2[i])
		{/*if two pass unmatched recieve again 2 pass      */
			UART_sendByte(unmatched);
			save_pass();
			return;
		}

	}

	/*    store pass in eeprom   */
	store_memory(pass1);

	UART_sendByte(matched);
	detect_option();
}

void store_memory(uint8*pass1)
{uint8 write;
for(int i=0;i<5;i++)
{/*    store pass in eeprom   */
	write=pass1[i];
	EEPROM_writeByte((address+i),write);
	_delay_ms(10);
}
}



void detect_option(void)
{

	UART_sendByte(ready);
	if(	UART_receiveByte()=='+')
	{/*open door*/
		check_login_pass();
	}
	else
	{/*   change passowrd */
		change_pass();
	}
}


void check_login_pass(void)
{static uint8 count=0;
Timer1_ConfigType info_timer1={0,0,FCPU_64,normal};
uint8 read;
/*    check on 3 trials to enter login pass     */

for(int i=0;i<5;i++)
{/*receive login passowrd*/
	pass1[i]=UART_receiveByte();

}
for(int i=0;i<5;i++)
{
	EEPROM_readByte((address+i),&read);
	if(read!=pass1[i])
	{
		UART_sendByte(unmatched);
		count++;
		if(count==3)
		{/*         exceeds three consectuive times    activate buzzer for 1min    */
			count=0;
			Buzzer_on();
			Timer1_init(&info_timer1);/*  intiallize timer1   */
			Timer1_setCallBack(deactivate_buzzer);
			while(!flag)
			{
				/*   wait till timer stop counting  */
			}
			flag=0;
			/*   return to options    */
			detect_option();
		}
		/*   recall funtion   */
		check_login_pass();
	}

}
/*    pass enterred matched with save    */
UART_sendByte(matched);
count=0;
Timer1_init(&info_timer1);/*   intiallize timer1   */

Timer1_setCallBack(control_dcmotor);
/*    locking door     */
DcMotor_Rotate(DC_MOTOR_CW,100);
while(!flag)
{
	/* wait till timer stop counting    */
}
flag=0;
detect_option();
}

void change_pass(void)
{static uint8 count=0;
Timer1_ConfigType info_timer1={0,0,FCPU_64,normal};
uint8 read;
/*    check on 3 trials to enter login pass     */

for(int i=0;i<5;i++)
{/*   receive old saved  pass   */
	pass1[i]=UART_receiveByte();

}
for(int i=0;i<5;i++)
{
	EEPROM_readByte((address+i),&read);
	if(read!=pass1[i])
	{
		UART_sendByte(unmatched);
		count++;
		if(count==3)
		{/*         exceeds three consectuive times    activate buzzer for 1min    */
			count=0;
			Buzzer_on();
			Timer1_init(&info_timer1);/*    intiallize timer1   */
			Timer1_setCallBack(deactivate_buzzer);
			while(!flag)
			{
				/*    wait till timer1 stop counting   */
			}
			flag=0;
			detect_option();
		}
		change_pass();
	}

}
/*    pass enterred matched with save    */
UART_sendByte(matched);
count=0;

save_pass();
}

void deactivate_buzzer(void)
{flag=0;
static uint8 tick=0;
tick++;
if(tick==120)
{
	Buzzer_off();
	tick=0;
	Timer1_deInit();
	flag=1;
}
}

void control_dcmotor(void)
{static uint8 tick=0;
flag=0;
tick++;
if(tick==30)
{/*   hold motor for 3sec   */
	DcMotor_Rotate(DC_MOTOR_STOP,0);
}
if(tick==36)
{/*     door is unlocking   */
	DcMotor_Rotate(DC_MOTOR_ACW,100);

}
if(tick==66)
{tick=0;
/*   return DCMOTOR to its intiall state   */
DcMotor_Rotate(DC_MOTOR_STOP,0);
Timer1_deInit();
flag=1;
}

}

