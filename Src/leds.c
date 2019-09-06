/**
@file    leds.c
@version 0.0
@date    2019.09.01

@author  alexander
@email   zhevak@mail.ru

@brief   вставьте сюда краткое описание файла
*/


#include "leds.h"


void gled_on(void)
{
  GLED_GPIO_Port->BSRR = GLED_Pin << 16;
}


void gled_off(void)
{
  GLED_GPIO_Port->BSRR = GLED_Pin;
}


void gled_toggle(void)
{
  if ((GLED_GPIO_Port->ODR & GLED_Pin) == 0)
    GLED_GPIO_Port->BSRR = GLED_Pin;
  else
    GLED_GPIO_Port->BSRR = GLED_Pin << 16;
}



void rled_on(void)
{
  RLED_GPIO_Port->BSRR = RLED_Pin << 16;
}


void rled_off(void)
{
  RLED_GPIO_Port->BSRR = RLED_Pin;
}


void rled_toggle(void)
{
  if ((RLED_GPIO_Port->ODR & RLED_Pin) == 0)
    RLED_GPIO_Port->BSRR = RLED_Pin;
  else
    RLED_GPIO_Port->BSRR = RLED_Pin << 16;
}




bool is_gled(void)
{
  return ((GLED_GPIO_Port->ODR & GLED_Pin) == 0);
}


bool is_rled(void)
{
  return ((RLED_GPIO_Port->ODR & RLED_Pin) == 0);
}

