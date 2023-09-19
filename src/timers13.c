#include <freertos_study.h>
#include <timers.h>
#include "llcm.h"
#include "portmacro.h"
#include "usart.h"

#define UART USART1
#define USART_BAUD_RATE 115200

static TickType_t mainOneShotTimer = pdMS_TO_TICKS(3333);
static TickType_t mainAutoReload = pdMS_TO_TICKS(1000);
static uint8_t uiAutoreloadCound = 0;

void vOneShotTimerTask(TimerHandle_t timer);
void vAutoReloadTimerTask(TimerHandle_t timer);

int main() {
  initSW();
  init_clock_100();
  init_SysTick(1000);
  init_usart1(USART_BAUD_RATE);

  TimerHandle_t xOneShotTimer = xTimerCreate("One shot", mainOneShotTimer, pdFALSE, 0, vOneShotTimerTask);
  TimerHandle_t xAutoReloadTimer = xTimerCreate("Auto Reload", mainAutoReload, pdTRUE, 0, vAutoReloadTimerTask);

  BaseType_t xOneShotTimerStarted = pdFALSE;
  BaseType_t xAutoReloadTimerStarted = pdFALSE;

  if ((xOneShotTimer != NULL) && (xAutoReloadTimer != NULL)) {
    xOneShotTimerStarted = xTimerStart(xOneShotTimer, 0);
    xAutoReloadTimerStarted = xTimerStart(xAutoReloadTimer, 0);
  }
  if ((xOneShotTimerStarted == pdPASS) && (xAutoReloadTimerStarted == pdPASS)) {
    vTaskStartScheduler();
  }

  while (1) {}
  return 0;
}

void vOneShotTimerTask(TimerHandle_t timer) {
  usart_sendString("One shot is done\r\n", UART);
}

void vAutoReloadTimerTask(TimerHandle_t timer) {
  usart_sendString("Auto reloaded: ", UART);
  usart_sendByte(uiAutoreloadCound + '0', UART);
  uiAutoreloadCound++;
  usart_sendString("\r\n", UART);
}
