#include <FreeRTOS.h>
#include <FreeRTOSConfig.h>
#include <task.h>
#include <llcm.h>
#include <usart.h>

struct sUSART{
  uint8_t rx_buf[256];
  uint8_t rx_count;
  uint32_t rxTimeout;
  const char* rxTimeoutExpireMsg;
  TaskHandle_t taskToNotify;
};

struct sUSART UART2 = {
  .rxTimeout = pdMS_TO_TICKS(5000),
  .rx_count = 0,
  .rxTimeoutExpireMsg = "UART2 RX TIMEOUT IS EXPIRED\r\n"
};

void vIDLETask(void* pvParameter){
  struct sUSART* UART = (struct sUSART*)pvParameter;
  while(1){
    UART->taskToNotify = xTaskGetCurrentTaskHandle();
    if(ulTaskNotifyTake(0, UART->rxTimeout)){
      usart_send(UART->rx_buf, UART->rx_count); //send back the incoming data(echo mode)
      UART->rx_count = 0; // clear the actual buffer data counter after the data is proccessed
    } else {
      usart_sendString(UART->rxTimeoutExpireMsg); //debug message if the timeout is expired
    }
  }
}

int main(void){
  initSW();
  init_clock_100();
  init_SysTick(1000);
  init_usart2_115200();
  NVIC_SetPriority(USART2_IRQn, 14);

  xTaskCreate(vIDLETask, "IDLE TASK", 100, &UART2, 1, 0);
  vTaskStartScheduler();  

  while(1){}
  return 1;
}

void USART2_IRQHandler(void){
  if(isRXNE()){
    UART2.rx_buf[UART2.rx_count++] = USART2->DR;
  }
  if(isIDLE()){
    USART2->DR; // clear IDLE flag        
    BaseType_t xHigherPriorityTaskWoken;
    xHigherPriorityTaskWoken = pdFALSE;
    vTaskNotifyGiveFromISR(UART2.taskToNotify, &xHigherPriorityTaskWoken);
    UART2.taskToNotify = 0;
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
  }
}
