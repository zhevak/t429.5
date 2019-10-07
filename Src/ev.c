/**
@file    ev.c
@version 0.0
@date    2019.10.07

@author  alex
@email   zhevak@mail.ru

@brief   вставьте сюда краткое описание файла
*/


#include "leds.h"
#include "ev.h"


static bool ev1;
static bool ev2;


void ev_clear(void)
{
  ev1 = false;
  ev2 = false;   
  rled_off();
  gled_off();
}


void ev_check(void)
{  
}



bool is_ev1(void)
{
  return ev1;
}



bool is_ev2(void)
{
  return ev2;
}

