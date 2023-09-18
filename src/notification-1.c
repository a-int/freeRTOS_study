#include <FreeRTOS.h>
#include <FreeRTOSConfig.h>
#include <task.h>
#include <llcm.h>
#include <usart.h>
#include "projdefs.h"

const char* NotifyString = "String for xTaskNotify method\r\n";
uint32_t RxTimeout = pdMS_TO_TICKS(5000);
TaskHandle_t CurrentTaskNotification = 0;

void vIDLETask(void* pvParameter){
  while(1){
    if(ulTaskNotifyTake(0, RxTimeout)){
      usart_sendString(NotifyString);
    } else {
      usart_sendString("RX TIMEOUT IS EXPIRED\r\n");
    }
  }
}

int main(void){
  initSW();
  init_clock_100();
  init_SysTick(1000);
  init_usart2_115200();
  NVIC_SetPriority(USART2_IRQn, 14);
  xTaskCreate(vIDLETask, "IDLE TASK", 100, 0, 1, &CurrentTaskNotification);
  vTaskStartScheduler();  

  while(1){}
  return 1;
}

void USART2_IRQHandler(void){
  if(isRXNE()){
    USART2->DR;
  }
  if(isIDLE()){
    USART2->DR; // clear IDLE flag        
    BaseType_t xHigherPriorityTaskWoken;
    xHigherPriorityTaskWoken = pdFALSE;
    vTaskNotifyGiveFromISR(CurrentTaskNotification, &xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
  }
}
