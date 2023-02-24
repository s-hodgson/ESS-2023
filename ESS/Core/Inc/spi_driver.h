/**
 *	SPI Driver
 *
 *	@author 	Andrew Markham
 *	@version 	v1.1
 *	@ide		STM32CubeIDE
 *	@license	GNU GPL v3
 */
#ifndef SPI_DRIVER_H
#define SPI_DRIVER_H

#include <stdint.h>

// Initialize the SPI 
void SPIAcc_Init(void);



// Send a byte on SPI 
// @param address address of register to write to 
// @param data to send
// @param send size
void SPIAcc_Send(uint8_t address, uint8_t* data, uint8_t size);

// Receive a byte on SPI 
// @param address address of register to read from 
// @param data to send
// @param read size
void SPIAcc_Get(uint8_t address, uint8_t* data, uint8_t size);

#endif
