/**
@file    bl.c
@version 0.0
@date    2019.09.12

@author  alex
@email   zhevak@mail.ru

@brief   вставьте сюда краткое описание файла
*/



#include "sockets.h"
#include "ppp_impl.h"
#include "cmsis_os.h"

#include "leds.h"
#include "bl.h"


//#define SVRIP     "172.16.27.179"
//#define BUFSIZE   (512)
#define PORT      (4840)


void bl(void)
{
  int cli_sfd, ser_sfd;
  socklen_t cli_len, ser_len;
  struct sockaddr_in cli_addr, ser_addr;
  
  ser_sfd = socket(AF_INET, SOCK_STREAM, 0);

  ser_addr.sin_family = AF_INET;
  ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  ser_addr. sin_port = htons(4840);
  
  ser_len = sizeof (struct sockaddr_in);
  cli_len = sizeof (struct sockaddr_in);
  
  bind(ser_sfd, (struct sockaddr *) &ser_addr, ser_len);
  listen(ser_sfd, 1);
  
//  int flags = fcntl(ser_sockfd, F_GETFL, 0);
//  fcntl(ser_sockfd, F_SETFL, flags | O_NONBLOCK);

//gled_off();
//rled_off();

  while (true)
  {
    cli_sfd = accept(ser_sfd, (struct sockaddr *) &cli_addr, &cli_len);
    if (cli_sfd != -1)
    {
      int8_t cmd;
      
      read(cli_sfd, &cmd, 1);
      switch (cmd)
      {
        case 'g':
          gled_off();
          break;
          
        case 'G':
          gled_on();
          break;
          
        case 'r':
          rled_off();
          break;
          
        case 'R':
          rled_on();
          break;
      }

      close(cli_sfd);
    }
    
    osDelay(100);    
  }
}



/*
  char message[] = "Hello!\n";
  struct sockaddr_in srv, cli;
  int srvfd;
  socklen_t cli_len = sizeof (cli);
  int recv_len;
  char buf[BUFSIZE];
  srvfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

  srv.sin_family = AF_INET;
  srv.sin_addr.s_addr = htonl(INADDR_ANY);
  srv.sin_port = htons(PORT);
  
  bind(srvfd, (struct sockaddr *) &srv, sizeof (srv));

  for(;;)
  {
    if ((recv_len = recvfrom(srvfd, buf, BUFSIZE, 0, (struct sockaddr *) &cli, &cli_len)) > 0)
    {
      buf[recv_len] = '\0';	
      
      switch (buf[0])
      {
        case 'g': gled_off(); break;
        case 'r': rled_off(); break;
        case 'G': gled_on(); break;
        case 'R': rled_on(); break;
      }
    }
    sendto(srvfd, message, sizeof message, 0, (struct sockaddr *) &cli, cli_len);
    osDelay(500);
  }
*/
