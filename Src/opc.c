/**
@file    task_opc.c
@version 0.0
@date    2019.09.20

@author  alex
@email   zhevak@mail.ru

@brief   opc-сервер
*/



#include "leds.h"
#include "open62541.h"

#include "opc.h"


void opc(void)
{
  /* USER CODE BEGIN StartTask02 */

/*
  UA_Int32 i = 5;
  UA_Int32 j;
  UA_Int32_copy(&i, &j);
*/
  static volatile UA_Boolean running = true;

  UA_Server *server = UA_Server_new();
  UA_ServerConfig_setDefault(UA_Server_getConfig(server));


  UA_ServerConfig *config = UA_Server_getConfig(server);
  // TODO 2019.09.18 задать IP для сервера
  char ip[] = "172.16.27.126";
  UA_String ua_ip;
  ua_ip.length = strlen(ip);
  ua_ip.data = (UA_Byte *) ip;
  UA_ServerConfig_setCustomHostname(config, ua_ip);
  
  UA_ServerConfig_setDefault(config);
  


  UA_StatusCode retval = UA_Server_run(server, &running);
  if (retval == 0)
    gled_on();

  while (true)
  {
    rled_toggle();
    osDelay(200);
  }

  UA_Server_delete(server);

/*
#define SVRIP     "172.16.27.179"
#define BUFSIZE   (512)
#define PORT      (8001)

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
  /* USER CODE END StartTask02 */
}

