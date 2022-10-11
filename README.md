# IDLE_UART
Реализация функции HAL_UART_Receive_ToIdle для FreeRTOS

Инструкция по запуску:

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

  	4. change callback function
	
    
Для работы необходимо отредактировать стандартные файлы HAL драйвера
### ОНИ БУДУТ СЛЕТАТЬ ПРИ КАЖДОМ ПЕРЕСБОРЕ ЧЕРЕЗ CubeMX


