/**
@file    memvis.c
@version 0.0
@date    2019.09.20

@author  alex
@email   zhevak@mail.ru

@brief   UDP сервер. Передаёт содержимое памяти микроконтроллера клиенту.
*/


#include <string.h>
#include "sockets.h"
//#include "tcp.h"
//#include "ppp_impl.h"

#include "leds.h"


#include "task_memvis.h"


typedef struct {
  uint32_t start;
  uint32_t length;
} request_t;


#define RXBUFSIZE (512)
static uint8_t rxBuf[RXBUFSIZE];
#define TXBUFSIZE (512)
static uint8_t txBuf[TXBUFSIZE];


static request_t *request = (request_t *) rxBuf;
      

/*
    int len, n; 
    n = recvfrom(sockfd, (char *)buffer, MAXLINE,  
                MSG_WAITALL, ( struct sockaddr *) &cliaddr, 
                &len); 
    buffer[n] = '\0'; 
    printf("Client : %s\n", buffer); 
    sendto(sockfd, (const char *)hello, strlen(hello),  
        MSG_CONFIRM, (const struct sockaddr *) &cliaddr, 
            len); 
    printf("Hello message sent.\n");  
      
*/


void memvis(void)
{
  int sfd;
  socklen_t cli_len, ser_len;
  struct sockaddr_in cli_addr, ser_addr;                 // LwIP/src/include/lwip/sockets.h


  // LwIP/src/include/lwip/sockets.h:542:
  //#define socket(domain,type,protocol)  lwip_socket(domain,type,protocol)
  if ((sfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    return;
      
  memset(&ser_addr, 0, sizeof ser_addr); 
  memset(&cli_addr, 0, sizeof cli_addr); 

  ser_addr.sin_family = AF_INET;
  ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  ser_addr.sin_port = htons(8000);
  ser_len = sizeof (struct sockaddr_in);
  
  // LwIP/src/include/lwip/sockets.h:514:#define bind(s,name,namelen)  lwip_bind(s,name,namelen)
  if (bind(sfd, (struct sockaddr*) &ser_addr, ser_len) < 0)
    return;
    
rled_off();

  while (1)
  {
    if (recvfrom(sfd, rxBuf, RXBUFSIZE, MSG_WAITALL, (struct sockaddr *) &cli_addr, &cli_len) == 8)
    {
      uint8_t *p   = (uint8_t *) request->start;
      uint32_t len = request->length;

rled_on();
      if (len <= TXBUFSIZE)
        for (int i = 0; i < len; i++)
          txBuf[i] = *p++;
      else
        memset(txBuf, 0, TXBUFSIZE);

      sendto(sfd, txBuf, len, 0, (const struct sockaddr *) &cli_addr, cli_len); 
rled_off();
    }
  }  // while(1)
}

