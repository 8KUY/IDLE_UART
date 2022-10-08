#include <idleuart.h>
#include "cmsis_os.h"

osEventFlagsId_t evt_id;
evt_id = osEventFlagsNew(NULL);

void HAL_UART_IDLE_Callback (UART_HandleTypeDef *huart) {
  if (huart == &COM6) {
    RX_buff_length1 = BUFFER_SIZE - COM6.RxXferCount;              // amount of data received
    __HAL_UART_CLEAR_IDLEFLAG(&COM6);
    HAL_UART_Abort_IT(&COM6);
    osEventFlagsSet(evt_id, 1);
  };
  if (huart == &COM7) {
    RX_buff_length2 = BUFFER_SIZE - COM7.RxXferCount;              // amount of data received
    __HAL_UART_CLEAR_IDLEFLAG(&COM7);
    HAL_UART_Abort_IT(&COM7);
    osEventFlagsSet(evt_id, 2);
}

void uart_receive (UART_HandleTypeDef *huart, uint8_t *msg) {
	HAL_UART_Receive_IT(huart, msg, 128);
	osEventFlagsWait()
}