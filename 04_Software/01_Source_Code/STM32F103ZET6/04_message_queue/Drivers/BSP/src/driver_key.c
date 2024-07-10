#include <stdbool.h>

#include "driver_key.h"
#include "driver_led.h"

#include "queue.h"				// 当运用到队列的操作时

extern osThreadId_t KeyTaskHandle;
extern osMessageQueueId_t KeysQueueHandle;

void StartKeyTask(void *argument)
{
	Key_State_t Key_State = KEY_NONE;
  for(;;)
  {
		Key_State = KEY_NONE;
		if(PUSH_DOWN == KEY_UP_PRESS) {
			Key_State = KEY_UP;
		} else if(PUSH_DOWN == KEY_DOWN_PRESS) {
			Key_State = KEY_DOWN;
		} else if(PUSH_DOWN == KEY_LEFT_PRESS) {
			Key_State = KEY_LEFT;
		} else if(PUSH_DOWN == KEY_RIGHT_PRESS) {
			Key_State = KEY_RIGHT;
		}
		
		if(KEY_NONE != Key_State)
		{
			BaseType_t err = xQueueSendToBack(KeysQueueHandle, &Key_State, pdMS_TO_TICKS(50));
			if(err == errQUEUE_FULL)
			{
				xQueueReset(KeysQueueHandle);
			}
			vTaskDelay(pdMS_TO_TICKS(200));				// 可起到一个消抖的作用.
		} else {
			vTaskDelay(pdMS_TO_TICKS(10));					// 每个任务必须需要一定的延时,给其他任务使用cpu的时间
		}
  }
}

