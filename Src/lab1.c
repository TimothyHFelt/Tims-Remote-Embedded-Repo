#include "main.h"
#include <stm32f0xx_hal.h>
#include <hal_gpio.h>

int lab1_main(void){
    HAL_Init();
    SystemClock_Config();
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN;

    GPIO_InitTypeDef initStr = {GPIO_PIN_7, GPIO_MODE_OUTPUT_PP, GPIO_SPEED_FREQ_LOW, GPIO_NOPULL};

    My_HAL_GPIO_Init(GPIOC, &initStr);

    My_HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);

}