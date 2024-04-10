#include "main.h"
//PWM mode for f=4000Gz
void timer0_init(void){
	TCCR0A |=(1<<COM0A1);
	TCCR0A |=(1<<WGM01)|(1<<WGM00);
	TCCR0B |=(1<<CS01);//8000000/(8*256)=3906Gz
	OCR0A =128;
}
//system timer for 10ms
void timer2_init(void){
	TCCR2A |=(1<<WGM21);
	TCCR2B |=(1<<CS20)|(1<<CS21)|(1<<CS22);
	TIMSK2 |=(1<<OCIE2A);
	OCR2A = 38;//2*1024*(1+38)/8000000=0.01
}
void USART_Init(void){
	UBRR0H=0;
	UBRR0L=51;
	UCSR0B=(1<<RXEN0)|(1<<TXEN0);
	UCSR0C=(1<<USBS0)|(3<<UCSZ00);
}
void USART_Transmit(uint8_t data){
	while(!(UCSR0A&(1<<UDRE0)));
	UDR0=data;
}
ISR (TIMER2_COMPA_vect){
	if(cnt1) cnt1--;
	flagEnc=1;
	flagKey = 1;
}



int main(void)
{cli();
	DDRD |=(1<<6)|(1<<4);
	DDRC|=(1<<4)|(1<<5);
	PORTC&=~((1<<4)|(1<<5));
	timer0_init();
	timer2_init();
	InitEncoder();
	USART_Init();
sei();
    while (1) 
    {
		if (flagEnc) {EncoderState();PORTD^=(1<<4);flagEnc=0;}//check the encoder every 10ms

		if (flagEncRight){
			if(cnt1==0){OCR0A++;cnt1=1;}
			//OCR0A++;
			PORTC|=(1<<4);
			PORTC&=~(1<<5);
			if(OCR0A>250) OCR0A=250;
		}
		if (flagEncLeft){
			if(cnt1==0){OCR0A--;cnt1=1;}
			//OCR0A--;
			PORTC|=(1<<5);
			PORTC&=~(1<<4);			
			if(OCR0A<2) OCR0A=2;
		}
		if(flagEncRight==0) PORTC&=~(1<<4);
		if(flagEncLeft==0) PORTC&=~(1<<5);
		
		if (flagKey) {flagKey=0;GetKeyCode();}//check the button every 10 ms
			if((flagButPress1)&&(PINB&(1<<btn1_pin))){flagButPress1=0;}


    }
}

