/*
板子LED灯为三色合一灯,不同的排列组合可以呈现不同灯
*/
#ifndef _LED_H
#define _LED_H

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
#define ON  GPIO_PIN_RESET
#define OFF GPIO_PIN_SET

#define RLED(flag)        HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, flag)   
#define GLED(flag)        HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, flag)    
#define BLED(flag)        HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, flag)     

void Led_Init(void);		// LED初始化״̬
void StartLedTask(void *argument);	// LED任务

#endif

