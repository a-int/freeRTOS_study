#include <freertos_study.h>
#include <timers.h>
#include "llcm.h"
#include "portmacro.h"
#include "usart.h"

#define UART USART1
#define USART_BAUD_RATE 115200

static TickType_t mainAutoReload1 = pdMS_TO_TICKS(1000);
static TickType_t mainAutoReload2 = pdMS_TO_TICKS(1000);

static const uint32_t timer1Id = 1;
static const uint32_t timer2Id = 2;

void vOneShotTimerTask(TimerHandle_t timer);
void vAutoReloadTimerTask(TimerHandle_t timer);

int main() {
  initSW();
  init_clock_100();
  init_SysTick(1000);
  init_usart1(USART_BAUD_RATE);

  TimerHandle_t xAutoReloadTimer1 = xTimerCreate("Auto Reload", mainAutoReload1, pdTRUE, timer1Id, vAutoReloadTimerTask);
  TimerHandle_t xAutoReloadTimer2 = xTimerCreate("Auto Reload", mainAutoReload2, pdTRUE, timer2Id, vAutoReloadTimerTask);

  BaseType_t xAutoReloadTimerStarted1 = pdFALSE;
  BaseType_t xAutoReloadTimerStarted2 = pdFALSE;

  if ((xAutoReloadTimer1 != NULL) && (xAutoReloadTimer2 != NULL)) {
    xAutoReloadTimerStarted1 = xTimerStart(xAutoReloadTimer1, 0);
    xAutoReloadTimerStarted2 = xTimerStart(xAutoReloadTimer2, 0);
  }
  if ((xAutoReloadTimerStarted1 == pdPASS) && (xAutoReloadTimerStarted2 == pdPASS)) {
    vTaskStartScheduler();
  }

  while (1) {}
  return 0;
}

void vAutoReloadTimerTask(TimerHandle_t timer) {
  const uint32_t id = pvTimerGetTimerID(timer);
  if(id == timer1Id){
    usart_sendString("The timer 1 is done\r\n", UART);
  } else if(id == timer2Id){
    usart_sendString("The timer 2 is done\r\n", UART);
  }
}
