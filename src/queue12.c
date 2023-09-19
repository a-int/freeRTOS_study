#include <freertos_study.h>
#include <queue.h>
#include "usart.h"

#define UART USART1

QueueHandle_t queue1;
QueueHandle_t queue2;
QueueSetHandle_t queueSet;

static void vSenderTask1(void* pvParameter){
  char data = (char)pvParameter;
  while(1){
    xQueueSendToBack(queue1, &data, portMAX_DELAY);
    vTaskDelay(100);
  }
}

static void vSenderTask2(void* pvParameter){
  char data = (char)pvParameter;
  while(1){
    xQueueSendToBack(queue2, &data, portMAX_DELAY);
    vTaskDelay(100);
  }
}

static void vReceiverTask(void* pvParameter){
  char data;
  BaseType_t xFlag;
  while(1){
    QueueHandle_t queue = xQueueSelectFromSet(queueSet, 0);
    if(queue != NULL){
      xFlag = xQueueReceive(queue, &data, portMAX_DELAY);
      if(xFlag == pdPASS){
        usart_sendByte(data, UART);
      } else {
        usart_sendByte('2', UART);
      }
    }
    vTaskDelay(1);
  }
}

int main(void) {
  initSW();
  init_clock_100();
  init_SysTick(1000);
  init_usart2_115200();

  queue1 = xQueueCreate(1, sizeof(uint8_t));
  queue2 = xQueueCreate(1, sizeof(uint8_t));
  queueSet = xQueueCreateSet(2);
  xQueueAddToSet(queue1, queueSet);
  xQueueAddToSet(queue2, queueSet);
  xTaskCreate(vSenderTask1, "Task_1", 100, 'A', 2, NULL);  
  xTaskCreate(vSenderTask2, "Task_2", 100, 'B', 2, NULL);  
  xTaskCreate(vReceiverTask, "Task_3", 100, NULL, 1, NULL);  
  vTaskStartScheduler();

  while (1) {}
  return 0;
}
