/**
@file    tt_udp.c
@version 0.0
@date    2019.10.01

@author  alex
@email   zhevak@mail.ru

@brief   Передает по запросу от компа время и температуру

*/


#include <string.h>
#include "sockets.h"

#include "FreeRTOS.h"
#include "task.h"

#include "adc.h"
#include "stm32f4xx_it.h"
#include "leds.h"

#include "tt_udp.h"



typedef struct {
  uint32_t start;
  uint32_t length;
} request_t;


#define RXBUFSIZE (4)
static uint8_t rxBuf[RXBUFSIZE];
//#define TXBUFSIZE (512)
//static uint8_t txBuf[TXBUFSIZE];
//static request_t *request = (request_t *) rxBuf;
     

// Температура чипа
uint32_t temperature;


void tt_udp(void)
{
  int sfd;
  socklen_t cli_len, ser_len;
  struct sockaddr_in cli_addr, ser_addr;                 // LwIP/src/include/lwip/sockets.h
  uint32_t value;

  // LwIP/src/include/lwip/sockets.h:542:
  //#define socket(domain,type,protocol)  lwip_socket(domain,type,protocol)
  if ((sfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    return;
      
  memset(&ser_addr, 0, sizeof ser_addr); 
  memset(&cli_addr, 0, sizeof cli_addr); 

  ser_addr.sin_family = AF_INET;
  ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  ser_addr.sin_port = htons(8001);
  ser_len = sizeof (struct sockaddr_in);

 
gled_off();

  // LwIP/src/include/lwip/sockets.h:514:#define bind(s,name,namelen)  lwip_bind(s,name,namelen)
  if (bind(sfd, (struct sockaddr*) &ser_addr, ser_len) < 0)
    return;
    
  while (1)
  {
    if (recvfrom(sfd, rxBuf, RXBUFSIZE, MSG_WAITALL, (struct sockaddr *) &cli_addr, &cli_len) == RXBUFSIZE)
    {
      if (strncmp((const char *) rxBuf, "time", 4) == 0)
      {
        value = (uint32_t) xTaskGetTickCount();  // uint32_t <- TickType_t
        sendto(sfd, (void *) &value, sizeof value, 0, (const struct sockaddr *) &cli_addr, cli_len); 
      }
      else if (strncmp((const char *) rxBuf, "temp", 4) == 0)
      {
gled_on();
        sendto(sfd, (void *) &temperature, sizeof temperature, 0, (const struct sockaddr *) &cli_addr, cli_len); 
gled_off();
      }
    }  
  }  // while(1)
}
