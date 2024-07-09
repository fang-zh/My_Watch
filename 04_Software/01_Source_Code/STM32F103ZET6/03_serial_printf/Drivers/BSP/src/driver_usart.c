#include "driver_usart.h"

#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

#include "string.h"
#include "stdio.h"

#define Buf_Len		50

extern UART_HandleTypeDef huart1;

// 全局变量
uint8_t rx_cnt = 0;
uint8_t g_ch = '0';
uint8_t rx_buffer[50] = "";

/*
	串口发送任务
*/
void StartDefaultTask(void *argument)
{
	HAL_UART_Receive_IT(&huart1, &g_ch, 1);
	for( ; ; )
	{
		printf("Hello World\r\n");
		osDelay(2000);
	}
}

/* 中断的方式接收数据 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	rx_buffer[rx_cnt] = g_ch;
	if(rx_buffer[rx_cnt] == '\n')
	{
		rx_buffer[rx_cnt++] = '\0';	// 添加字符串结束标准符
		printf("%s\0", rx_buffer);	// printf不会自动不全'\0'
		rx_cnt = 0;
		HAL_UART_Receive_IT(&huart1, &g_ch, 1);
		return;
	}
	rx_cnt++;
	rx_cnt = (rx_cnt >= Buf_Len - 1) ? Buf_Len - 1 : rx_cnt; // 限制最大输入长度 
	HAL_UART_Receive_IT(&huart1, &g_ch, 1);
}

/*
	printf()函数会调用fputc函数实现重定向
*/
int fputc(int ch, FILE *f)
{
	HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 50);
	return ch;
}

/*
	scanf()函数会调用fgetc函数实现
*/
int fgetc(FILE *f)
{
	uint8_t ch = 0;
	HAL_UART_Receive_IT(&huart1, (uint8_t *)&ch, 1);
	return (int)ch;
}

/* 添加以下代码,可不在工程设置种勾选Use MicroLib */
#pragma import(__use_no_semihosting)

struct __FILE
{
	int a;
};

FILE __stdout;
FILE __stdin;

void _sys_exit(int x)
{

}
