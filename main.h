


#ifndef MAIN_H_
#define MAIN_H_

#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "key.h"
#include "encoder.h"

uint8_t cnt1;
uint8_t flagKey ;
uint8_t flagEnc;
//uint8_t flag_R;
//uint8_t flag_L;
//uint8_t cnt_R;
//uint8_t cnt_L;

#endif /* MAIN_H_ */