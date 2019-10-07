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
  gled_off();
  rled_off();
}


/**
 * ev_checking()
 * Проверка состояния кнопок (Кнопки эмулируют события)
*/
void ev_checking(void)
{
  if (HAL_GPIO_ReadPin(BTN2_GPIO_Port, BTN2_Pin) == GPIO_PIN_RESET)
  {
    ev1 = true;
    gled_on();
  }
  
  if (HAL_GPIO_ReadPin(BTN3_GPIO_Port, BTN3_Pin) == GPIO_PIN_RESET)
  {
    ev2 = true;
    rled_on();
  }
}


bool ev_is1(void)
{
  return ev1;
}



bool ev_is2(void)
{
  return ev2;
}

