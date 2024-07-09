#ifndef _DRIVER_USART_H_
#define _DRIVER_USART_H_

#include "stm32f1xx_hal.h"

void StartDefaultTask(void *argument);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
#endif
