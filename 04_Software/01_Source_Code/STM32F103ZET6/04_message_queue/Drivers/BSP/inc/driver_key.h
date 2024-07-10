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
#define KEY_UP_PRESS                  (HAL_GPIO_ReadPin(Key1Up_GPIO_Port, Key1Up_Pin))
#define KEY_DOWN_PRESS               	(HAL_GPIO_ReadPin(Key2Down_GPIO_Port, Key2Down_Pin))
#define KEY_LEFT_PRESS                (HAL_GPIO_ReadPin(Key3Left_GPIO_Port, Key3Left_Pin))
#define KEY_RIGHT_PRESS               (HAL_GPIO_ReadPin(Key4Right_GPIO_Port, Key4Right_Pin))

typedef enum {
	KEY_NONE = 0,
	KEY_UP,
	KEY_DOWN,
	KEY_LEFT,
	KEY_RIGHT
} Key_State_t;

void StartKeyTask(void *argument);

#endif
