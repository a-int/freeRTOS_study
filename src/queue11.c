#include <freertos_study.h>
#include <queue.h>
#include "usart.h"

#define UART USART1

QueueHandle_t queue;

static void vSenderTask(void* pvParameter){
  char data = (char)pvParameter;
  while(1){
    xQueueSendToBack(queue, &data, portMAX_DELAY);
    vTaskDelay(100);
    taskYIELD();
  }
}

static void vReceiverTask(void* pvParameter){
  char data;
  BaseType_t xFlag;
  while(1){
    xFlag = xQueueReceive(queue, &data, portMAX_DELAY);
    if(xFlag == pdPASS){
      usart_sendByte(data, UART);
    } else {
      usart_sendByte('2', UART);
    }
    vTaskDelay(1);
  }
}

int main(void) {
  initSW();
  init_clock_100();
  init_SysTick(1000);
  init_usart2_115200();

  queue = xQueueCreate(3, sizeof(uint8_t));
  if(queue != NULL){
    xTaskCreate(vSenderTask, "Task_1", 100, (void*)'A', 2, NULL);  
    xTaskCreate(vSenderTask, "Task_2", 100, (void*)'B', 2, NULL);  
    xTaskCreate(vReceiverTask, "Task_3", 100, NULL, 1, NULL);  
    vTaskStartScheduler();
  }

  while (1) {}
  return 0;
}