/*
 * mini_project_2.c
 *
 *  Created on: Sep 16, 2022
 *      Author: NADA
 */

#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>

 unsigned char sec1=0;
 unsigned char min1=0;
 unsigned char hr1=0;
 unsigned char sec2=0;
 unsigned char min2=0;
 unsigned char hr2 =0;


void TIMER1_CTC_Init(void)
{TCNT1=0;
OCR1A=1000;

TIMSK |= (1<<OCIE1A); //enable interrupt module
	TCCR1A=(1<<FOC1A);
	TCCR1B=(1<<WGM12)|(1<<CS10)|(1<<CS12);
	SREG|=(1<<7); // enable i-bit

}


ISR(TIMER1_COMPA_vect)
{
sec1++;
if(sec1==10)
{ sec2++;
sec1=0;
if(sec2==6)
{
	sec2=0;
	min1++;
	if(min1==10)
	{
		min2++;
		min1=0;
	}
	if(min2==6)
	{
		hr1++;
		min2=0;
	}
	if(hr1==10)
		{
			hr2++;
			hr1=0;
		}
}

}
if(hr2==10)
{
	hr2=0; //overflow occurs starts over
}

}


void INT0_Init(void)
{ //ACTIVATE INTERNAL PULL UP
	DDRD&=~(1<<PD2);
	PORTD|=(1<<PD2);
	//ACTIVATE INTERRUPT ENABLE
	GICR|=(1<<INT0);
	//FALLING EDGE
	MCUCR|=(1<<ISC01);
	//ENABLE I-BIT
	SREG|=(1<<7);
}
ISR(INT0_vect)
{
	sec1=0; hr1=0; min1=0;
	sec2=0; hr2=0; min2=0;

}
void INT1_Init(void)
{//external pull down button
	DDRD&=~(1<<PD3);
//ACTIVATE INTERRUPT ENABLE
GICR|=(1<<INT1);
//RISING EDGE
MCUCR|=(1<<ISC10);  MCUCR|=(1<<ISC11);
//ENABLE I-BIT
SREG|=(1<<7);
}
ISR(INT1_vect)
{
	TCCR1A=0;
	TCCR1B=0;

}
void INT2_Init(void)
{
	//ACTIVATE INTERNAL PULL UP
		DDRB&=~(1<<PB2);
		PORTB|=(1<<PB2);
		//ACTIVATE INTERRUPT ENABLE
		GICR|=(1<<INT2);
		//FALLING EDGE
		MCUCSR=MCUCSR&~(1<<ISC2);
		//ENABLE I-BIT
		SREG|=(1<<7);
}
ISR(INT2_vect)
{TIMER1_CTC_Init();

}
int main(void)
{
	DDRC|=0x0F; //out pins decoder
	DDRA|=0x3F; //out pins enables
  PORTA |=(0xFF); //enable 6 7seg
	PORTC&=(0xF0); //display 0
	INT0_Init();
	INT1_Init();
	INT2_Init();
	TIMER1_CTC_Init();
	while(1)
	{
		PORTA=(1<<PA0)	;	//enable sec1

		PORTC=(PORTC& 0xE0) | (sec1 & 0x0F);

		_delay_ms(5);

		PORTA=(1<<PA1);	//enable sec2

		PORTC=(PORTC& 0xE0) | (sec2 & 0x0F);
		_delay_ms(5);

		PORTA=(1<<PA2);	//enable min1

		PORTC=(PORTC& 0xE0) | (min1 & 0x0F);
		_delay_ms(5);

		PORTA=(1<<PA3);	//enable min2

		PORTC=(PORTC& 0xE0) | (min2 & 0x0F);
		_delay_ms(5);

		PORTA=(1<<PA4);	//enable hr1

		PORTC=(PORTC& 0xE0) | (hr1& 0x0F);
		_delay_ms(5);

		PORTA=(1<<PA5);	//enable hr2

		PORTC=(PORTC& 0xE0) | (hr2 & 0x0F);
		_delay_ms(5);


		}
	}






