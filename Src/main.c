#include "main.h"
#include <stm32f0xx_hal.h>
#undef LAB1;
#define SPI;
int main(void)
{
  #if defined(LAB1)
  lab1_main();
  #elif defined(SPI)
  spi_main();
  #else
  #error No valid target specified
  #endif

}
