#include "led.h"

volatile bool LED_TASK_RUN_FLAG = true;

extern osThreadId_t LedTaskHandle;

/*
 *  函数名：void Led_Init(void)
 *  输入参数：无
 *  输出参数：无
 *  返回值：无
 *  函数作用：初始化LED任务初始化状态
*/
void Led_Init(void)
{
	// GPIO引脚配置由MX_GPIO_Init()函数调用
	
    // 默认LED灭:OFF-灭，ON-亮
    RLED(OFF);
    GLED(OFF);
    BLED(OFF);
}

void StartLedTask(void *argument)
{
  for(;;)
  {
		if(LED_TASK_RUN_FLAG)
		{
			RLED(ON);
			GLED(ON);
			BLED(ON);
			osDelay(500);
			RLED(OFF);
			GLED(OFF);
			BLED(OFF);
			osDelay(500);
			RLED(ON);
			GLED(OFF);
			BLED(OFF);
			osDelay(500);
			RLED(OFF);
			GLED(ON);
			BLED(OFF);
			osDelay(500);
			RLED(OFF);
			GLED(OFF);
			BLED(ON);
			osDelay(500);	
		}
		else
		{
			RLED(OFF);
			GLED(OFF);
			BLED(OFF);
			vTaskSuspend(LedTaskHandle);
		}
  }

}

