#include <FreeRTOS.h>
#include <FreeRTOSConfig.h>
#include <task.h>
#include <llcm.h>
#include <usart.h>

struct sUSART{
  USART_TypeDef* USARTx;
  uint8_t rx_buf[256];
  uint8_t rx_count;
  uint32_t rxTimeout;
  const char* rxTimeoutExpireMsg;
  TaskHandle_t taskToNotify;
};

struct sUSART UART = {
  .USARTx = USART1,
  .rxTimeout = pdMS_TO_TICKS(5000),
  .rx_count = 0,
  .rxTimeoutExpireMsg = "UART2 RX TIMEOUT IS EXPIRED\r\n"
};

void vIDLETask(void* pvParameter){
  struct sUSART* UART = (struct sUSART*)pvParameter;
  while(1){
    UART->taskToNotify = xTaskGetCurrentTaskHandle();
    if(ulTaskNotifyTake(0, UART->rxTimeout)){
      usart_send(UART->rx_buf, UART->rx_count, UART->USARTx); //send back the incoming data(echo mode)
      UART->rx_count = 0; // clear the actual buffer data counter after the data is proccessed
    } else {
      usart_sendString(UART->rxTimeoutExpireMsg, UART->USARTx); //debug message if the timeout is expired
    }
  }
}

int main(void){
  initSW();
  init_clock_100();
  init_SysTick(1000);
  init_usart1(115200);
  NVIC_SetPriority(USART1_IRQn, 14);

  xTaskCreate(vIDLETask, "IDLE TASK", 100, &UART, 1, 0);
  vTaskStartScheduler();  

  while(1){}
  return 1;
}

void USART1_IRQHandler(void){
  if(isRXNE(UART.USARTx)){
   UART.rx_buf[UART.rx_count++] = UART.USARTx->DR;
  }
  if(isIDLE(UART.USARTx)){
    UART.USARTx->DR; // clear IDLE flag        
    BaseType_t xHigherPriorityTaskWoken;
    xHigherPriorityTaskWoken = pdFALSE;
    vTaskNotifyGiveFromISR(UART.taskToNotify, &xHigherPriorityTaskWoken);
    UART.taskToNotify = 0;
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
  }
}
