#ifndef _KEY_H
#define _KEY_H

#include "stm32f1xx_hal.h"
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
/*********************
 * 按键引脚状态定义
**********************/
#define PUSH_DOWN                       GPIO_PIN_RESET
#define SPRING_UP                       GPIO_PIN_set

/*
 * 按键状态读取函数宏定义
*/
#define KEY_UP                  HAL_GPIO_ReadPin(KEY_UP_GPIO_PORT, KEY_UP_GPIO_PIN)
#define KEY_DOWN                HAL_GPIO_ReadPin(KEY_DOWN_GPIO_PORT, KEY_DOWN_GPIO_PIN)
#define KEY_LEFT                HAL_GPIO_ReadPin(KEY_LEFT_GPIO_PORT, KEY_LEFT_GPIO_PIN)
#define KEY_RIGHT               HAL_GPIO_ReadPin(KEY_RIGHT_GPIO_PORT, KEY_RIGHT_GPIO_PIN)

#endif
