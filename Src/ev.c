/**
@file    ev.c
@version 0.0
@date    2019.10.07

@author  alex
@email   zhevak@mail.ru

@brief   вставьте сюда краткое описание файла
*/


#include "FreeRTOS.h"
#include "queue.h"

#include "leds.h"
#include "ev.h"



QueueHandle_t queueEv;


static bool ev1;
static bool ev2;



void ev_init(void)
{
  ev1 = false;
  ev2 = false;   
  gled_off();
  rled_off();
}



void ev_run(void)
{
  int32_t msg;

  if (xQueueReceive(queueEv, &msg, portMAX_DELAY) == pdPASS)
  {
    switch ((event_t) msg)
    {
      case ev1_raise:
        ev1 = true;
        gled_on();
        break;
        
      case ev1_reset:
        ev1 = true;
        gled_off();
        break;

      case ev2_raise:
        ev2 = true;
        rled_on();
        break;
        
      case ev2_reset:
        ev2 = true;
        gled_off();
        break;
        
      default:
        break;
    }
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

