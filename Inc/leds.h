/**
@file    leds.h
@version 0.0
@date    2019.09.01

@author  alexander
@email   zhevak@mail.ru

@brief   вставьте сюда краткое описание файла
*/


#ifndef __LEDS_H__
#define __LEDS_H__


#include <stdbool.h>
#include "main.h"



void gled_on(void);
void gled_off(void);
void gled_toggle(void);
void rled_on(void);
void rled_off(void);
void rled_toggle(void);

bool is_gled(void);
bool is_rled(void);



#endif  // __LEDS_H__
