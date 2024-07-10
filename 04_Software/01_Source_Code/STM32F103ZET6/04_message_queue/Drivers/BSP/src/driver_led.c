#include "driver_led.h"

#include "queue.h"
#include "driver_key.h"

#include <stdbool.h>

extern osThreadId_t LedTaskHandle;
extern osMessageQueueId_t KeysQueueHandle;
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
    RLED_Ctrl(LED_OFF);
    GLED_Ctrl(LED_OFF);
    BLED_Ctrl(LED_OFF);
}

void StartLedTask(void *argument)
{
	Led_Init();
	Key_State_t Key_State = KEY_NONE;
	bool RLED_Flag = false;
	bool GLED_Flag = false;
	bool BLED_Flag = false;
	
  for(;;)
  {
		if(pdTRUE != xQueueReceive(KeysQueueHandle, &Key_State, pdMS_TO_TICKS(50)))
		{
			continue;
		}
		
		if(Key_State == KEY_UP) {
			// 暂无任何现象
		} else if(Key_State == KEY_DOWN) {
			// 打开绿灯
			GLED_Flag = !GLED_Flag;
			GLED_Flag ? GLED_Ctrl(LED_ON) : GLED_Ctrl(LED_OFF);
		} else if(Key_State == KEY_LEFT) {
			// 打开红灯
			RLED_Flag = !RLED_Flag;
			RLED_Flag ? RLED_Ctrl(LED_ON) : RLED_Ctrl(LED_OFF);
		} else if(Key_State == KEY_RIGHT) {
			// 打开蓝灯
			BLED_Flag = !BLED_Flag;
			BLED_Flag ? BLED_Ctrl(LED_ON) : BLED_Ctrl(LED_OFF);
		}
		vTaskDelay(pdMS_TO_TICKS(400));
  }
}

