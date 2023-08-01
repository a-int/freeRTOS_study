#include <FreeRTOS.h>
#include <llcm.h>
#include <task.h>

void task_blink(void* args __attribute__((unused)));
void init_GPIO();

int main(void) {
  initSW();
  init_clock_100();
  init_SysTick(1000);
  init_GPIO();
  xTaskCreate(task_blink, "blink", 100, NULL, configMAX_PRIORITIES - 1, NULL);
  vTaskStartScheduler();

  while (1) {}
  return 0;
}

void task_blink(void* args __attribute__((unused))) {
  while (1) {
    GPIOC->ODR ^= 1 << 13;
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

void init_GPIO() {
  //set up for GPIOC13 (LED)
  SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOCEN);      //enable GPIOC
  SET_BIT(GPIOC->MODER, GPIO_MODER_MODE13_0);      // set as output
  CLEAR_BIT(GPIOC->OTYPER, GPIO_OTYPER_OT13_Msk);  //select push-pull mode
  CLEAR_BIT(GPIOC->PUPDR, GPIO_PUPDR_PUPD13_Msk);  //select no push no pull mode
}
