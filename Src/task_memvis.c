/**
@file    memvis.c
@version 0.0
@date    2019.09.20

@author  alex
@email   zhevak@mail.ru

@brief   TCP/IP сервер. Передаёт содержимое памяти микроконтроллера клиенту.
*/


#include "sockets.h"
//#include "tcp.h"
//#include "ppp_impl.h"

#include "leds.h"


#include "task_memvis.h"




typedef struct {
  uint32_t start;
  uint32_t length;
} request_t;

static request_t request;

#define TXBUFSIZE (1024)
static uint8_t txBuf[TXBUFSIZE];


void memvis(void)
{
  int cli_sfd, ser_sfd;
  socklen_t cli_len, ser_len;
  struct sockaddr_in cli_addr, ser_addr;                 // LwIP/src/include/lwip/sockets.h
  
  // LwIP/src/include/lwip/sockets.h:542:#define socket(domain,type,protocol)  lwip_socket(domain,type,protocol)
  ser_sfd = socket(AF_INET, SOCK_STREAM, 0);
  ser_addr.sin_family = AF_INET;
  ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  ser_addr.sin_port = htons(8000);
  ser_len = sizeof (struct sockaddr_in);
  
  // LwIP/src/include/lwip/sockets.h:514:#define bind(s,name,namelen)  lwip_bind(s,name,namelen)
  bind(ser_sfd, (struct sockaddr*) &ser_addr, ser_len);
  listen(ser_sfd, 5);
  
rled_off();

  while (1)
  {
    cli_len = sizeof (struct sockaddr_in);
    cli_sfd = accept(ser_sfd, (struct sockaddr *) &cli_addr, &cli_len);

    if (cli_sfd != -1)
    {
    
      while (1)
      {
        int len = read(cli_sfd, &request, sizeof (request_t));
      
        if (len == 8)
        {
          uint8_t *p = (uint8_t *) request.start;
          uint32_t len = request.length;
        
          // Большой кусок посылаем несколькими порциями
          while (len > TXBUFSIZE)
          {

            for (int i = 0; i < TXBUFSIZE; i++)
              txBuf[i] = *p++;

rled_on();
            write(cli_sfd, txBuf, TXBUFSIZE);
rled_off();

            len -= TXBUFSIZE;
          }               

          // Последняя порция
          if (len > 0)
          {
            for (int i = 0; i < len; i++)
              txBuf[i] = *p++;
gled_on();
            write(cli_sfd, txBuf, len);
gled_off();            
          }
        }
      }  
    }  

    close(cli_sfd);
  }
}

