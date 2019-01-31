#include "sys.h"
#include "usart.h"
#include "delay.h"
#include "key.h"
#include "led.h"	 
//#include "usmart.h"	
#include "stdlib.h"
#include "string.h"
#include "rc522_function.h"
#include "rc522_config.h"
#include "exti.h"
#include "MicroStepDriver.h"
#include "MicroStepDriver1.h"
#include "MicroStepDriver2.h"
#include "timer.h"
#include "lcd.h"
#include "nRF24l01P.h"
extern signed int stepPosition;
extern signed int stepPosition1;
extern signed int stepPosition2;
//ALIENTEK战舰STM32开发板
//步进电机驱动器 测试代码  
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司
int j=0;
int k=0;
void IC_test ( void );
u8  RxPayload[32];   //无线接收缓存
int main(void)
{	 

	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);	 	//串口初始化为115200
//	usmart_dev.init(72); 	//初始化USMART	1
	LED_Init();			     //LED端口初始化  
	KEY_Init();					//初始化按键
//	Driver_Init();			//驱动器初始化
//	Driver_Init1();			//驱动器初始化
//	TIM8_OPM_RCR_Init(999,72-1); //1MHz计数频率  单脉冲+重复计数模式	   
//	TIM1_OPM_RCR_Init(999,72-1);
  RC522_Init ();
	EXTIX_Init();
	printf("1");
	PcdReset();
  printf("2");
	M500PcdConfigISOType ( 'A' );//设置工作方式
	MSD_Init();
	MSD_Init1();
	MSD_Init2();
	Init_NRF24L01_MB();	        //初始化
	Set_RxMode_MB();	  				//配置nRF24L01为发送模式
	TIM3_Int_Init(29999,7199);//10Khz的计数频率，计数到5000为500ms  
  GPIO_ResetBits(GPIOC,GPIO_Pin_4);
  GPIO_ResetBits(GPIOC,GPIO_Pin_2);
  GPIO_ResetBits(GPIOC,GPIO_Pin_3);
	LCD_Init();
	POINT_COLOR=RED;
	#if 1
	while(1) 
	{		 	  
   IC_test ();
				if(NRF24L01_RxPacket_MB(RxPayload) == RX_OK)	//如果接收成功
		{
			if(RxPayload[0] == 0x30)		
      {
				LED_Toggle(GPIO_NRF24L01_MB_LED,NRF24L01_MB_LED);//NRF24L01模块状态指示灯翻转
				
				printf("shoudao\r\n");
				RxPayload[0] = 0;
				LCD_ShowString(30,40,210,12,12,"Residual parking space"); 
				LCD_ShowString(60,80,210,24,24,"4"); 
      }		
      if(RxPayload[0] == 0x31)		
      {
				LED_Toggle(GPIO_NRF24L01_MB_LED,NRF24L01_MB_LED);//NRF24L01模块状态指示灯翻转
				
				printf("shoudao\r\n");
				RxPayload[0] = 0;
				LCD_ShowString(30,40,210,12,12,"Residual parking space"); 
				LCD_ShowString(60,80,210,24,24,"3"); 
      }
			if(RxPayload[0] == 0x32)		
      {
				LED_Toggle(GPIO_NRF24L01_MB_LED,NRF24L01_MB_LED);//NRF24L01模块状态指示灯翻转
				
				printf("shoudao\r\n");
				RxPayload[0] = 0;
				LCD_ShowString(30,40,210,12,12,"Residual parking space"); 
				LCD_ShowString(60,80,210,24,24,"2"); 
      }	
			if(RxPayload[0] == 0x33)		
      {
				LED_Toggle(GPIO_NRF24L01_MB_LED,NRF24L01_MB_LED);//NRF24L01模块状态指示灯翻转
				
				printf("shoudao\r\n");
				RxPayload[0] = 0;
				LCD_ShowString(30,40,210,12,12,"Residual parking space"); 
				LCD_ShowString(60,80,210,24,24,"1"); 
      }		
			if(RxPayload[0] == 0x34)		
      {
				LED_Toggle(GPIO_NRF24L01_MB_LED,NRF24L01_MB_LED);//NRF24L01模块状态指示灯翻转
				
				printf("shoudao\r\n");
				RxPayload[0] = 0;
				LCD_ShowString(30,40,210,12,12,"Residual parking space"); 
				LCD_ShowString(60,80,210,24,24,"0"); 
      }		
		}
	LED_Toggle(GPIOE,GPIO_Pin_5);
	delay_ms(500);
	}			
	#endif
}
void IC_test ( void )
{
	char cStr [ 30 ];
	char str1[] = "D489990D";
	char str2[] = "E70FDCD9";
  unsigned char ucArray_ID [ 4 ];  //先后存放IC卡的类型和UID(IC卡序列号)
	uint8_t ucStatusReturn;          //返回状态
	
//  while ( 1 )
//  { 

       /*寻卡*/
		if ( ( ucStatusReturn = PcdRequest ( PICC_REQALL, ucArray_ID ) ) != MI_OK )                                   
			 /*若失败再次寻卡*/
      ucStatusReturn = PcdRequest ( PICC_REQALL, ucArray_ID );		   
		if ( ucStatusReturn == MI_OK  )
		{
      /*防冲撞（当有多张卡进入读写器操作范围时，防冲突机制会从其中选择一张进行操作）*/
			if ( PcdAnticoll ( ucArray_ID ) == MI_OK )  
			{
				sprintf ( cStr, "The Card ID is: %02X%02X%02X%02X", ucArray_ID [ 0 ], ucArray_ID [ 1 ], ucArray_ID [ 2 ], ucArray_ID [ 3 ] );							
				printf ( "%s\r\n",cStr ); 
				for(j=0;j<4;j++){
				printf("%d\r\n",ucArray_ID [ j ]);
				}
				if(ucArray_ID [ 3 ]==13)GPIO_ResetBits(GPIOE,GPIO_Pin_1);//卡
				if(ucArray_ID [ 3 ]==217)GPIO_ResetBits(GPIOE,GPIO_Pin_2);
		//		if(strcmp(cStr, str1) == 0) LED0=!LED0;
				   
  //      LCD_DispString_EN(10,200,cStr,BLACK,RED,FONT_24);                    
      }       
		}	
/*		LCD_ShowString(30,40,210,8,8,"A parking device based on the rotation of the concentric ring of the Internet of things"); 
		LCD_ShowString(100,80,200,12,12,"--Hebei University of Technology");
		LCD_ShowString(20,120,200,12,12,"Producer:SDH,WQ,CSH,MS,DRY !");
		LCD_ShowString(240,160,200,12,12,"2018/4/6");
		LCD_ShowString(100,180,200,12,12,"Residual space vehicle:");
		*/
//		delay_ms(100);
  

}
