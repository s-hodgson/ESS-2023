#include "stm32f4xx.h"
#include "stm32f4xx_hal_rcc.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_tim.h"
#include "stm32f4xx_it.h"
#include "stm32f4xx_hal_adc.h"
SPI_HandleTypeDef hspi1;


void SPIAcc_Init(void){
            GPIO_InitTypeDef GPIO_InitTypeDefStruct;
            // Enable clock to SPI1
            hspi1.Instance = SPI1;
            __HAL_RCC_SPI1_CLK_ENABLE();
            // Setup SPI to be master
            hspi1.Init.Direction = SPI_DIRECTION_2LINES;
            hspi1.Init.Mode = SPI_MODE_MASTER;
            hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
            hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
            hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
            hspi1.Init.NSS = SPI_NSS_SOFT;
            hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
            hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
            hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
            hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
            hspi1.Init.CRCPolynomial = 10;
            HAL_SPI_Init(&hspi1);
            // Enable clocks to Ports A and E
            __HAL_RCC_GPIOA_CLK_ENABLE();
            __HAL_RCC_GPIOE_CLK_ENABLE();
            //RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOE , ENABLE);
            // Set SPI pins on PortA (A5,A6,A7) to Alternate Function Mode
            GPIO_InitTypeDefStruct.Pin = GPIO_PIN_5 | GPIO_PIN_7 | GPIO_PIN_6;
            GPIO_InitTypeDefStruct.Mode = GPIO_MODE_AF_PP;
            GPIO_InitTypeDefStruct.Speed = GPIO_SPEED_FREQ_HIGH;
            // Connect the PortA pins to the alternate function
            GPIO_InitTypeDefStruct.Alternate = GPIO_AF5_SPI1;
            //GPIO_InitTypeDefStruct.GPIO_OType = GPIO_OType_PP;
            GPIO_InitTypeDefStruct.Pull = GPIO_NOPULL;
            HAL_GPIO_Init(GPIOA, &GPIO_InitTypeDefStruct);
            // Pin E3 is SPI_CS (chip select) 
            GPIO_InitTypeDefStruct.Pin = GPIO_PIN_3;
            GPIO_InitTypeDefStruct.Mode = GPIO_MODE_OUTPUT_PP;
            GPIO_InitTypeDefStruct.Speed = GPIO_SPEED_FREQ_HIGH;
            GPIO_InitTypeDefStruct.Pull = GPIO_PULLUP;
            HAL_GPIO_Init(GPIOE, &GPIO_InitTypeDefStruct);
            // Hold CS high 
            HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_SET);
            // Enable the SPI module
            __HAL_SPI_ENABLE(&hspi1);
}
 

void SPIAcc_Send(uint8_t address, uint8_t* data, uint8_t size){

	uint8_t spiReg = address;
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_RESET);

    HAL_SPI_Transmit(&hspi1, &spiReg, 1, 10);

    HAL_SPI_Transmit(&hspi1, data, size, 10);

    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_SET);
}
 

void SPIAcc_Get(uint8_t address, uint8_t* data, uint8_t size){

	uint8_t spiBuf[4];
	spiBuf[0] = address | 0x80;
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_RESET);

    HAL_SPI_Transmit(&hspi1, spiBuf, 1, 100);
    HAL_SPI_Receive(&hspi1, spiBuf, size, 100);


    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_SET);

	for(uint8_t i=0; i<(size&0x3); i++)
	{
		data[i] = spiBuf[i];
	}

}
