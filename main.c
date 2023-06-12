/*
 * ATMega16_ADC.c
 *
 * Created: 2023-06-10 7:42:01 PM
 * Author : a_shi
 */ 

#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

unsigned int i;

//Separate ADC Conversion function
/*
int ADC_read(int x)
{
	ADMUX=x|0x40;
	ADCSRA=0xd7;
	while((ADCSRA & 0x10)==0x00);
	return ADC;
}
*/

int main(void)
{
	//Set mode of the Timer1
	TCCR1B &= ~(1<<WGM13);
	TCCR1B |= (1<<WGM12);
	TCCR1A |= (1<<WGM10) | (1<<WGM11);		//FAST PWM 10 BIT MODE
	
	//Set PWM Mode
	TCCR1A |= (1<<COM1A1);
	TCCR1A &= ~(1<<COM1A0);				//PWM in Non Inverting Mode
	
	//Clock is 8MHz and prescaler is 256. So, 8000000/256 =31250
	TCCR1B |= (1<<CS12);
	
	//Configure the Output compare pin as O/P
	DDRD |= (1<<DDD5);
	
	//ADC Conversion Code 
	
	//Enable the Global Interrupt bit
	sei();
	
	//Enable ADC Interrupt
	ADCSRA |= (1<<ADIE);
	
	//Set reference to NO AVCC and input to ADC0
	//Set data alignment in data register
	ADMUX = 0x00;
	
	//Enable ADC
	ADCSRA |= (1<<ADEN) | (1<<ADATE);
	
	//Set frequency of ADC Conversion
	ADCSRA |= (1<<ADPS2);
	ADCSRA &= (~(1<<ADPS1)) & (~(1<<ADPS0));		//Prescaler 16 | Clock = 16MHz/16 = 1MHz
	
	//Start the conversion
	ADCSRA |= (1<<ADSC);
	
	
	while (1)
	{
				
	}
}

//ISR Function
ISR(ADC_vect)
{
	OCR1A = ADC;
}
