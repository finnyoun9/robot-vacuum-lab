#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Timer.h"
#include "Key.h"
#include "AD.h"
#include "NRF24L01.h"

/*OLED测试*/
/*下载此段程序后，OLED屏幕上会显示一些测试内容*/
//int main(void)
//{
//	/*模块初始化*/
//	OLED_Init();	//OLED初始化
//	
//	/*显示测试字符串*/
//	/*此OLED模块与STM32入门教程中的OLED模块不一样，不能通用*/
//	/*OLED模块教程，可以参考链接：https://www.bilibili.com/video/BV1EN41177Pc*/
//	OLED_Printf(0, 0, OLED_8X16, "Hello World!");
//	OLED_Printf(0, 16, OLED_6X8, "Hello World!");
//	
//	/*调用OLED功能函数后，必须调用OLED_Update，否则OLED将不会收到任何数据*/
//	OLED_Update();
//	
//	while (1)
//	{
//		
//	}
//}

/*定时中断和非阻塞式按键测试*/
/*下载此段程序后，OLED显示变量Count会1ms自增一次*/
/*按下按键，OLED显示的变量Num变为对应的键码*/
//uint16_t Count;
//uint8_t KeyNum, Num;

//int main(void)
//{
//	/*模块初始化*/
//	OLED_Init();		//OLED初始化
//	Key_Init();			//非阻塞式按键初始化
//	
//	Timer_Init();		//定时器初始化，1ms定时中断一次
//	
//	while (1)
//	{
//		KeyNum = Key_GetNum();		//获取键码
//		if (KeyNum)					//如果按键按下
//		{
//			Num = KeyNum;			//把KeyNum赋值给Num
//		}
//		
//		/*OLED显示*/
//		OLED_Printf(0, 0, OLED_8X16, "Count:%05d", Count);	//显示变量Count
//		OLED_Printf(0, 16, OLED_8X16, "Num:%03d", Num);		//显示变量Num
//
//		/*OLED更新*/
//		OLED_Update();
//	}
//}

//void TIM1_UP_IRQHandler(void)
//{
//	if (TIM_GetITStatus(TIM1, TIM_IT_Update) == SET)
//	{
//		/*定时中断函数1ms自动执行一次*/
//
//		Count ++;			//测试变量Count自增
//		
//		Key_Tick();			//调用按键模块的Tick函数，用于驱动按键模块工作
//		
//		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
//	}
//}

/*摇杆测试*/
/*下载此程序后，OLED显示的4个AD值，分别对应左右摇杆的4个摇动方向*/
//int main(void)
//{
//	/*模块初始化*/
//	OLED_Init();		//OLED初始化
//	AD_Init();			//AD初始化
//	
//	while (1)
//	{
//		/*读取摇杆对应4个引脚的AD值并显示在OLED上*/
//		OLED_Printf(0, 0, OLED_8X16, "AD0:%04d", AD_GetValue(ADC_Channel_0));		//显示PA0引脚AD值
//		OLED_Printf(0, 16, OLED_8X16, "AD1:%04d", AD_GetValue(ADC_Channel_1));		//显示PA1引脚AD值
//		OLED_Printf(0, 32, OLED_8X16, "AD2:%04d", AD_GetValue(ADC_Channel_2));		//显示PA2引脚AD值
//		OLED_Printf(0, 48, OLED_8X16, "AD3:%04d", AD_GetValue(ADC_Channel_3));		//显示PA3引脚AD值
//		
//		/*OLED更新*/
//		OLED_Update();
//	}
//}

/*NRF24L01测试*/
/*下载此程序后，OLED第1行显示的TestData应为A5*/
/*按下K1，NRF24L01会发出一个数据包，并将发送的数据显示在OLED第2行*/
/*NRF24L01收到一个数据包后，会在OLED第3行显示接收到的数据*/
/*无线数据收发需要配合平衡车程序（07-基础驱动代码+NRF24L01）*/
uint8_t KeyNum;

int main(void)
{
	/*模块初始化*/
	OLED_Init();		//OLED初始化
	NRF24L01_Init();	//NRF24L01初始化
	Key_Init();			//非阻塞式按键初始化
	
	Timer_Init();		//定时器初始化，1ms定时中断一次
	
	/*给NRF24L01寄存器里随便写一个数据（0xA5），再读回来*/
	/*观察读出和写入是否一致，以此判断SPI通信是否正常*/
	NRF24L01_WriteReg(NRF24L01_SETUP_RETR, 0xA5);				//给SETUP_RETR寄存器写入0xA5
	uint8_t TestData = NRF24L01_ReadReg(NRF24L01_SETUP_RETR);	//读取SETUP_RETR寄存器的值，存入TestData
	
	/*OLED显示*/
	OLED_Printf(0, 0, OLED_8X16, "TestData:%02X", TestData);	//%02X，以十六进制显示TestData
	OLED_Update();
	
	while (1)
	{
		KeyNum = Key_GetNum();		//获取键码
		if (KeyNum == 1)			//如果K1按下
		{
			/*随便变换一下测试数据，便于观察现象，此处用自增来变换测试数据*/
			NRF24L01_TxPacket[0] ++;
			NRF24L01_TxPacket[1] += 2;
			NRF24L01_TxPacket[2] += 3;
			NRF24L01_TxPacket[3] += 4;
			
			/*NRF24L01发送数据包*/
			NRF24L01_Send();
			
			/*OLED显示发送的数据*/
			OLED_Printf(0, 16, OLED_8X16, "T:%02X %02X %02X %02X", 
				NRF24L01_TxPacket[0], NRF24L01_TxPacket[1], NRF24L01_TxPacket[2], NRF24L01_TxPacket[3]);
			OLED_Update();
		}
		
		if (NRF24L01_Receive() == 1)		//NRF24L01收到一个数据包
		{
			/*OLED显示收到的数据*/
			OLED_Printf(0, 32, OLED_8X16, "R:%02X %02X %02X %02X", 
				NRF24L01_RxPacket[0], NRF24L01_RxPacket[1], NRF24L01_RxPacket[2], NRF24L01_RxPacket[3]);
			OLED_Update();
		}
	}
}

void TIM1_UP_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) == SET)
	{
		/*定时中断函数1ms自动执行一次*/
		
		Key_Tick();				//调用按键模块的Tick函数，用于驱动按键模块工作
		
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
	}
}
