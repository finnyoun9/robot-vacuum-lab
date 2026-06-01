#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "LED.h"
#include "Timer.h"
#include "Key.h"
#include "MPU6050.h"
#include "Motor.h"
#include "Encoder.h"
#include "Serial.h"
#include "BlueSerial.h"
#include <math.h>

/*定义全局变量*/
int16_t AX, AY, AZ, GX, GY, GZ;		//读取MPU6050的原始数据
uint8_t TimerErrorFlag;	//定时器错误标志位，如果定时中断函数执行时间超过了定时时间，则此标志位置1
uint16_t TimerCount;	//定时器计数值，此值可用于计算定时中断函数具体的执行时间

float AngleAcc;			//由加速度计得到的角度值
float AngleGyro;		//由陀螺仪得到的角度值，执行互补滤波后，此值基本与Angle相等
float Angle;			//互补滤波后的角度值，准确且无漂移

int main(void)
{
	/*模块初始化*/
	OLED_Init();		//OLED初始化
	MPU6050_Init();		//MPU6050初始化
	BlueSerial_Init();	//蓝牙串口初始化
	
	Timer_Init();		//定时器初始化，定时中断时间1ms
	
	while (1)
	{
		/*OLED显示*/
		OLED_Printf(0, 0, OLED_8X16, "%+06d", AX);		//显示AX
		OLED_Printf(0, 16, OLED_8X16, "%+06d", AY);		//显示AY
		OLED_Printf(0, 32, OLED_8X16, "%+06d", AZ);		//显示AZ
		OLED_Printf(64, 0, OLED_8X16, "%+06d", GX);		//显示GX
		OLED_Printf(64, 16, OLED_8X16, "%+06d", GY);	//显示GY
		OLED_Printf(64, 32, OLED_8X16, "%+06d", GZ);	//显示GZ
		OLED_Printf(0, 48, OLED_8X16, "Flag:%1d", TimerErrorFlag);	//显示TimerErrorFlag
		OLED_Printf(64, 48, OLED_8X16, "C:%05d", TimerCount);		//显示TimerCount
		OLED_Update();									//OLED更新
		
		/*蓝牙串口打印波形，需配合蓝牙串口小程序实现波形绘制*/
		BlueSerial_Printf("[plot,%f,%f,%f]", AngleAcc, AngleGyro, Angle);	//绘制AngleAcc、AngleGyro和Angle的波形
	}
}

void TIM1_UP_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) == SET)
	{
		/*定时中断函数1ms自动执行一次*/
		
		/*进入中断函数后，立刻清标志位*/
		/*如果中断函数退出前，标志位又置1了，说明中断函数执行时间超过了定时时间（1ms）*/
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
		
		/*在中断里读取MPU6050，可以保证读取间隔严格为1ms*/
		/*但要保证MPU6050_GetData执行时间不超过1ms*/
		MPU6050_GetData(&AX, &AY, &AZ, &GX, &GY, &GZ);
		
		/*校准陀螺仪Y轴零漂*/
		/*此值需实测确定，不同的设备零漂一般不同*/
		/*实测方法是，在完全静止时，观察OLED显示的GY值，即为零漂值*/
		/*然后在此处将零漂值减去，使得完全静止时，GY值为0*/
		GY -= 16;
		
		/*由加速度计计算得到角度值*/
		/*atan2计算反正切，得到角度（弧度制）， / 3.14159 * 180可将弧度制转为角度值*/
		AngleAcc = -atan2(AX, AZ) / 3.14159 * 180;
		
		/*由陀螺仪积分得到角度值*/
		/*互补滤波下，角度积分要在上次滤波后的Angle上进行*/
		/*公式中32768是int16_t变量的最大值，2000是陀螺仪配置的满量程2000度每秒，0.001是定时时间1ms*/
		AngleGyro = Angle + GY / 32768.0 * 2000 * 0.001;
		
		/*执行互补滤波*/
		float Alpha = 0.001;		//互补滤波系数，值越大，越偏向于加速度计，值越小，越偏向于陀螺仪
		Angle = Alpha * AngleAcc + (1 - Alpha) * AngleGyro;		//互补滤波计算，得到稳定的角度值
		
		/*中断函数退出前，再次检查标志位*/
		if (TIM_GetITStatus(TIM1, TIM_IT_Update) == SET)
		{
			/*标志位又置1了，说明中断函数执行时间超过了定时时间（1ms）*/
			/*置TimerErrorFlag为1，表示定时中断错误*/
			TimerErrorFlag = 1;
			
			/*清标志位，避免中断连续触发，导致主函数完全无法执行*/
			TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
		}
		
		/*中断函数退出前，读取计数器的值，此值可用于测量中断函数的具体执行时间*/
		TimerCount = TIM_GetCounter(TIM1);
	}
}
