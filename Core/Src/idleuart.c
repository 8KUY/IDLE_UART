#include "main.h"
#include "idleuart.h"
#include "cmsis_os.h"

uint32_t stat1;
osEventFlagsId_t evt_id;
uint8_t RX_Length1;
uint8_t RX_Length2;

void idleuart_init(void) {
  evt_id = osEventFlagsNew(NULL);
}

void HAL_UART_IDLE_Callback (UART_HandleTypeDef *huart) {
	if (huart == &COM7) {
		RX_Length1 = BUFFER_SIZE - COM7.RxXferCount;
	    __HAL_UART_CLEAR_IDLEFLAG(&COM7);
	    HAL_UART_Abort_IT(&COM7);
	    stat1 = osEventFlagsSet(evt_id, 0x00000001U);
	};
	if (huart == &COM6) {
		RX_Length2 = BUFFER_SIZE - COM6.RxXferCount;
    	__HAL_UART_CLEAR_IDLEFLAG(&COM6);
    	HAL_UART_Abort_IT(&COM6);
    	stat1 = osEventFlagsSet(evt_id, 0x00000002U);
	};
}

void idleuart_receive (UART_HandleTypeDef *huart, uint8_t *msg, uint8_t *pt) {
	HAL_UART_Receive_IT(huart, msg, BUFFER_SIZE);

	if (huart == &COM7) {
		osEventFlagsWait(evt_id, 0x00000001U, osFlagsWaitAny, osWaitForever);
		*pt = RX_Length1;
	}
	if (huart == &COM6) {
		osEventFlagsWait(evt_id, 0x00000002U, osFlagsWaitAny, osWaitForever);
		*pt = RX_Length2;
	};  
}

void idleuart_transmit (UART_HandleTypeDef *huart, uint8_t *msg, uint8_t pt) {
	HAL_UART_Transmit_IT(huart, msg, pt);
	// todo: rework tx function
}

