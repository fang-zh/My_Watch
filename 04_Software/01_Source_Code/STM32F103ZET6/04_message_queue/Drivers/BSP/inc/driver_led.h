/*
板子LED灯为三色合一灯,不同的排列组合可以呈现不同灯
*/
#ifndef _DRIVER_LED_H
#define _DRIVER_LED_H

#include "stm32f1xx_hal.h"
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
/*********************
 * 引脚宏定义
**********************/
/*
 * LED亮灭函数宏定义
*/
#define LED_ON  GPIO_PIN_RESET
#define LED_OFF GPIO_PIN_SET

#define RLED_Ctrl(flag)        HAL_GPIO_WritePin(RedLed_GPIO_Port, RedLed_Pin, flag)
#define GLED_Ctrl(flag)        HAL_GPIO_WritePin(GreenLed_GPIO_Port, GreenLed_Pin, flag)
#define BLED_Ctrl(flag)        HAL_GPIO_WritePin(BlueLed_GPIO_Port, BlueLed_Pin, flag)

void Led_Init(void);		// LED初始化״̬
void StartLedTask(void *argument);	// LED任务

#endif

