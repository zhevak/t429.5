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
//#include "semphr.h"
#include "task.h"

#include "main.h"
#include "leds.h"
#include "bl.h"


//#define SVRIP     "172.16.27.179"
//#define BUFSIZE   (512)
#define PORT      (4840)

#define MAX_TCPCLIENTS 3


// Семафор количества подключенных клиентов
// SemaphoreHandle_t mutexTcp;
// static int clients = 0;


/**
* Обслуживаение клиентского соединения по TCP
*
*
*

void client(void *pSfd)
{
  int8_t cmd;

  //rled_on();
  while (1)
  {
    read(*((int *) pSfd), &cmd, 1);
    
    switch (cmd)
    {
      case 'g':
        // gled_off();
        break;
          
      case 'G':
        // gled_on();
        break;
          
      case 'r':
        // gled_on();
        // rled_off();
        break;
          
      case 'R':
        // rled_on();
        break;
    } // switch
  }

  close(*((int *) pSfd));

  xSemaphoreTake(mutexTcp, 0);
  clients--;
  xSemaphoreGive(mutexTcp);     

  vTaskDelete(NULL);
  rled_off();
}
*/



void tcpClient(void *pSfd)
{
  int sfd = (int)*(int *)pSfd;
  
  for (int i = 0; i < sfd; i++)
  {
    rled_on();
    vTaskDelay(200);
    rled_off();
    vTaskDelay(200);
  }
  
  int8_t cmd;
  read(*((int *) pSfd), &cmd, 1);
  
  for (int i = 0; i < sfd; i++)
  {
    gled_on();
    vTaskDelay(200);
    gled_off();
    vTaskDelay(200);
  }
  
  close(sfd);
  vTaskDelete(NULL);
}



void bl(void)
{
  int cli_sfd, ser_sfd;
  socklen_t cli_len, ser_len;
  struct sockaddr_in cli_addr, ser_addr;
  
  // mutexTcp = xSemaphoreCreateMutex();

  ser_sfd = socket(AF_INET, SOCK_STREAM, 0);

  ser_addr.sin_family = AF_INET;
  ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  ser_addr. sin_port = htons(EV_PORT);
  
  ser_len = sizeof (struct sockaddr_in);
  cli_len = sizeof (struct sockaddr_in);
  
  
  bind(ser_sfd, (struct sockaddr *) &ser_addr, ser_len);
  listen(ser_sfd, 4);
  
  while (true)
  {    
    rled_off();
    cli_sfd = accept(ser_sfd, (struct sockaddr *) &cli_addr, &cli_len);    
    if (cli_sfd != -1)
    {
      xTaskCreate(tcpClient, "Client", configMINIMAL_STACK_SIZE, &cli_sfd, (tskIDLE_PRIORITY + 1), NULL);
      /*
      xSemaphoreTake(mutexTcp, 0);
      if (clients < MAX_TCPCLIENTS)
      {
        clients++;
      }  
      xSemaphoreGive(mutexTcp);
      */
    }
    else
    {
      gled_toggle();
    }
  }
  
}

