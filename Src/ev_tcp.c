/**
@file    ev_tcp.c
@version 0.0
@date    2019.10.07

@author  alex
@email   zhevak@mail.ru

@brief   вставьте сюда краткое описание файла
*/


#include <string.h>
#include "sockets.h"
#include "fcntl.h"

#include "FreeRTOS.h"
#include "task.h"

#include "leds.h"

#include "ev_tcp.h"



void ev_tcp(void)
{
  int ser_sfd, cli_sfd;
  int ser_len, cli_len;
  struct sockaddr_in ser_addr, cli_addr;                            // LwIP/src/include/lwip/sockets.h


  // LwIP/src/include/lwip/sockets.h:542:
  //#define socket(domain,type,protocol)  lwip_socket(domain,type,protocol)
  if ((ser_sfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    return;
      
  memset(&ser_addr, 0, sizeof ser_addr); 
  memset(&cli_addr, 0, sizeof cli_addr); 
  
  ser_addr.sin_family = AF_INET;
  ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  ser_addr.sin_port = htons(EV_PORT);
  
  ser_len = sizeof (struct sockaddr_in);
  // LwIP/src/include/lwip/sockets.h:514:#define bind(s,name,namelen)  lwip_bind(s,name,namelen)
  if (bind(ser_sfd, (struct sockaddr*) &ser_addr, ser_len) < 0)
    return;
    
  listen(ser_sfd, 5);
  
  int flags = fcntl(ser_sfd, F_GETFL, 0);
}

