/**
 ******************************************************************************
	1. add __HAL_UART_ENABLE_IT(&huart, UART_IT_IDLE); to your Init function
	2. add prototype function in stm32xxxx_hal_uart.h:

	void HAL_UART_IDLE_Callback (UART_HandleTypeDef *huart);

	3. add to the end of HAL_UART_IRQHandler in stm32xxxx_hal_uart.c:

	// UART RX IDLE interrupt --------------------------------------------
  	if (((isrflags & USART_SR_IDLE) != RESET) && ((cr1its & USART_CR1_IDLEIE) != RESET))
  	{
    	HAL_UART_IDLE_Callback(huart);
    	return;
  	}

  	4. change callback function, ex:

  	void HAL_UART_IDLE_Callback (UART_HandleTypeDef *huart) {
	  if (huart == &RX) {
	    Rx_buff_pt = BUFFER_SIZE - RX.RxXferCount;              // amount of data received
	    __HAL_UART_CLEAR_IDLEFLAG(&RX);
	    HAL_UART_Abort_IT(&RX);
	    HAL_UART_Transmit_IT(&TX, foo, 3);                      // do something
	  };
	}

 ******************************************************************************
 */


#ifndef __IDLEUART_H
#define __IDLEUART_H

#include "stm32f4xx_hal.h"
// #include "stm32h7xx_hal.h"

#define USE_GLOBAL_LENGTH

#ifdef USE_GLOBAL_LENGTH
uint8_t RX_buff_length1;
uint8_t RX_buff_length2; 
#endif


#define BUFFER_SIZE (uint8_t)128
#define COM6 huart1
#define COM7 huart2



void HAL_UART_IDLE_Callback (UART_HandleTypeDef *huart);


#endif
