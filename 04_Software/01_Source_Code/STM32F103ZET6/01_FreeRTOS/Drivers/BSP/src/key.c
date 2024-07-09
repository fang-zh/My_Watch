/*  Copyright (s) 2019 深圳百问网科技有限公司
 *  All rights reserved
 * 
 * 文件名称：driver_key.c
 * 摘要：
 *  
 * 修改历史     版本号        Author       修改内容
 *--------------------------------------------------
 * 2020.6.6      v01        百问科技      创建文件
 *--------------------------------------------------
*/

#include <stdbool.h>

#include "key.h"
#include "led.h"

/*
 *  函数名：void HAL_GPIO_EXTI_Callback(void)
 *  输入参数：无
 *  输出参数：无
 *  返回值：无
 *  函数作用：外部中断处理函数的回调函数，用以处理不同引脚触发的中断服务最终函数
*/

extern TaskHandle_t LedTaskHandle;
extern volatile bool LED_TASK_RUN_FLAG;

static volatile bool Red_flag = false;    // 定义一个全局静态标志，用以判断按键按下的次数，上下左右键类似  
static volatile bool Green_flag = false;
static volatile bool Blue_flag = false;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	switch(GPIO_Pin)                    // 判断是哪个按键
	{           
		case KEY1_UP_Pin:           // 如果是上键
		{  
			LED_TASK_RUN_FLAG = !LED_TASK_RUN_FLAG;         // 按下一次标志翻转一次
			if(LED_TASK_RUN_FLAG)
			{
				//vTaskResume(LedTaskHandle);
				BaseType_t YieldRequired = pdFALSE;
				YieldRequired=xTaskResumeFromISR(LedTaskHandle);//恢复任务2
				if(YieldRequired==pdTRUE)
				{
					/*如果函数xTaskResumeFromISR()返回值为pdTRUE，那么说明要恢复的这个
					任务的任务优先级等于或者高于正在运行的任务(被中断打断的任务),所以在
					退出中断的时候一定要进行上下文切换！*/
					portYIELD_FROM_ISR(YieldRequired);
				}
			}
			else
			{
				Red_flag = false;
				Green_flag = false;
				Blue_flag = false;
			}
			break;  
		}   
		case KEY2_DOWN_Pin:         // 如果是下键
		{
			if(!LED_TASK_RUN_FLAG)
			{
				Red_flag = !Red_flag;
				RLED(ON);
				GLED(OFF);
				BLED(OFF);
			}
			break;  
		}   
		case KEY3_LEFT_Pin:         // 如果是左键
		{     
			if(!LED_TASK_RUN_FLAG)
			{
				Green_flag = !Green_flag;				
				RLED(OFF);
				GLED(ON);
				BLED(OFF);		
			}
				
			break;
		}
		case KEY4_RIGHT_Pin:        // 如果是右键
		{     
			if(!LED_TASK_RUN_FLAG)
			{
				Blue_flag = !Blue_flag;	
				RLED(OFF);
				GLED(OFF);
				BLED(ON);
			}
			break;
		}
		default:break;
	}
}
