#include "key.h"
#include "main.h"
void BtnInit(void){
	DDRB &=~(1<<btn1_pin);
	PORTB |=(1<<btn1_pin);
	keyTemp1=0x00;
	keyTemp2=0x00;

}

uint8_t GetKeyCode(void){
	uint8_t ret = 0;
	static uint8_t lev = 0;
	
	if( lev == 0){
		(!(PINB & (1<<btn1_pin)))?(keyTemp1 |=(1<<0)):(keyTemp1 &=~(1<<0));
		lev = 1;
		}else if (lev == 1){
		(!(PINB & (1<<btn1_pin)))?(keyTemp2 |=(1<<0)):(keyTemp2 &=~(1<<0));
		if ((keyTemp1==1)&&(keyTemp2==1)){
			flagButPress1 = 1;
		}
		lev = 0;
	}
	
	return ret;
}
