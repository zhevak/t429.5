/**
@file    leds.c
@version 0.0
@date    2019.09.01

@author  alexander
@email   zhevak@mail.ru

@brief   вставьте сюда краткое описание файла
*/


#include "leds.h"


inline void gled_on(void)
{
  HAL_GPIO_WritePin(GLED_GPIO_Port, GLED_Pin, GPIO_PIN_RESET);
}


inline void gled_off(void)
{
  HAL_GPIO_WritePin(GLED_GPIO_Port, GLED_Pin, GPIO_PIN_SET);
}


inline void gled_toggle(void)
{
  HAL_GPIO_TogglePin(GLED_GPIO_Port, GLED_Pin);
}



inline void rled_on(void)
{
  HAL_GPIO_WritePin(RLED_GPIO_Port, RLED_Pin, GPIO_PIN_RESET);
}


inline void rled_off(void)
{
  HAL_GPIO_WritePin(RLED_GPIO_Port, RLED_Pin, GPIO_PIN_SET);
}


inline void rled_toggle(void)
{
  HAL_GPIO_TogglePin(RLED_GPIO_Port, RLED_Pin);
}

