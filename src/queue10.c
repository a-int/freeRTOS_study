#include <freertos_study.h>
#include <queue.h>

#define UART USART1

QueueHandle_t queue;

void vSenderTask(void* pvParameter){
  const uint8_t data = (uint8_t)pvParameter;
  BaseType_t xFlag;
  while(1){
    xFlag = xQueueSendToBack(queue, &data, 0);
    if(xFlag != pdPASS){
      usart_sendString("The queue is full", UART);
    }
    vTaskDelay(500);
  }
}

void vReceiverTask(void* pvParameter){
  uint8_t data;
  BaseType_t xFlag;
  const TickType_t x200ms = pdMS_TO_TICKS(500);
  while(1){
    if(uxQueueMessagesWaiting(queue) != 0){
      usart_sendString("The queue has to be empty", UART);
    }
    xFlag = xQueueReceive(queue, &data, x200ms);
    if(xFlag == pdPASS){
      usart_send((uint8_t*)(&data), sizeof(data), UART);
    }
  }
}

int main(void) {
  initSW();
  init_clock_100();
  init_SysTick(1000);
  init_usart2_115200();

  queue = xQueueCreate(5, sizeof(uint8_t));
  if(queue != NULL){
    xTaskCreate(vSenderTask, "Task_1", 1000, (void*)'A', 1, NULL);  
    xTaskCreate(vSenderTask, "Task_2", 1000, (void*)'B', 1, NULL);  
    xTaskCreate(vReceiverTask, "Task_3", 1000, NULL, 2, NULL);  
    vTaskStartScheduler();
  }

  while (1) {}
  return 0;
}