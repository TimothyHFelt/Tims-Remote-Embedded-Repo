#include <stdint.h>
#include <stm32f0xx_hal.h>
#include <stm32f0xx_hal_gpio.h>

void My_HAL_GPIO_Init(GPIO_TypeDef  *GPIOx, GPIO_InitTypeDef *GPIO_Init)
{
    if (GPIOx == GPIOA)
    {
        GPIOx->MODER &=~(GPIO_MODER_MODER0);
        GPIOx->OSPEEDR &=~(GPIO_OSPEEDR_OSPEEDR0);
        GPIOx->PUPDR |=(GPIO_PUPDR_PUPDR0_1);
    }
    if (GPIOx == GPIOC)
    {
        GPIOx->MODER |=(GPIO_MODER_MODER7_0 | GPIO_MODER_MODER6_0|GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0);
    }
}



void My_HAL_GPIO_DeInit(GPIO_TypeDef  *GPIOx, uint32_t GPIO_Pin)
{
}



GPIO_PinState My_HAL_GPIO_ReadPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    uint16_t ReadBit = GPIOx->IDR & GPIO_Pin;
    if (ReadBit == 0){
        return 0;
    }
    else {
        return 1;
    }
}



void My_HAL_GPIO_WritePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState)
{
    if(PinState == GPIO_PIN_SET){
        GPIOx->BSRR = GPIO_Pin;
    }
    else {
        GPIOx->BRR = GPIO_Pin;
    }
}



void My_HAL_GPIO_TogglePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    uint16_t temp = GPIOx->ODR;
    GPIOx->BRR = GPIO_Pin;
    GPIOx->BSRR = temp ^ GPIO_Pin;
}
//This function sets up SPI on PA5-7
void SetUpSpi(void){
    //The following 3 lines of code set GPIOA to Alternative function mode, 
    //specifically spi, MISO, MOSI and SCK. Already configured in AFRL by default.
    GPIOA->MODER &= ~(63 << 10);
    GPIOA->MODER |= (0x26 << 10); 
    GPIOA->PUPDR &= ~(0x3 << 12);   // Clear bits 13:12 for PA6
    GPIOA->PUPDR |= (0x1 << 12); //pullup PA6
    My_HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
    //PA5 = SCK, PA6 = CS (pullup), PA7 = MOSI.
    SPI1->CR1 |= SPI_CR1_BIDIOE;   //disable the receive line

    SPI1->CR1 |= SPI_CR1_MSTR; //set peripheral to master mode.
    SPI1->CR2 |= (0x7 << 8);  //set FIFO threshold to 8 bits
    SPI1->CR1 |= (0x2 << 3);  //set baud rate to 6 MHZ
    SPI1->CR1 |= SPI_CR1_SPE;  //enable SPI

}

//Function that writes an address and data to SPI 
void WriteToDevice(uint8_t address, uint8_t data){
    My_HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
    while (!(SPI1->SR & SPI_SR_TXE));
    SPI1->DR = address;
    while (!(SPI1->SR & SPI_SR_TXE));
    SPI1->DR = data;
    while (SPI1->SR & SPI_SR_BSY);
    My_HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
}
