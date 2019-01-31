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
//ALIENTEKս��STM32������
//������������� ���Դ���  
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾
int j=0;
int k=0;
void IC_test ( void );
u8  RxPayload[32];   //���߽��ջ���
int main(void)
{	 

	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
//	usmart_dev.init(72); 	//��ʼ��USMART	1
	LED_Init();			     //LED�˿ڳ�ʼ��  
	KEY_Init();					//��ʼ������
//	Driver_Init();			//��������ʼ��
//	Driver_Init1();			//��������ʼ��
//	TIM8_OPM_RCR_Init(999,72-1); //1MHz����Ƶ��  ������+�ظ�����ģʽ	   
//	TIM1_OPM_RCR_Init(999,72-1);
  RC522_Init ();
	EXTIX_Init();
	printf("1");
	PcdReset();
  printf("2");
	M500PcdConfigISOType ( 'A' );//���ù�����ʽ
	MSD_Init();
	MSD_Init1();
	MSD_Init2();
	Init_NRF24L01_MB();	        //��ʼ��
	Set_RxMode_MB();	  				//����nRF24L01Ϊ����ģʽ
	TIM3_Int_Init(29999,7199);//10Khz�ļ���Ƶ�ʣ�������5000Ϊ500ms  
  GPIO_ResetBits(GPIOC,GPIO_Pin_4);
  GPIO_ResetBits(GPIOC,GPIO_Pin_2);
  GPIO_ResetBits(GPIOC,GPIO_Pin_3);
	LCD_Init();
	POINT_COLOR=RED;
	#if 1
	while(1) 
	{		 	  
   IC_test ();
				if(NRF24L01_RxPacket_MB(RxPayload) == RX_OK)	//������ճɹ�
		{
			if(RxPayload[0] == 0x30)		
      {
				LED_Toggle(GPIO_NRF24L01_MB_LED,NRF24L01_MB_LED);//NRF24L01ģ��״ָ̬ʾ�Ʒ�ת
				
				printf("shoudao\r\n");
				RxPayload[0] = 0;
				LCD_ShowString(30,40,210,12,12,"Residual parking space"); 
				LCD_ShowString(60,80,210,24,24,"4"); 
      }		
      if(RxPayload[0] == 0x31)		
      {
				LED_Toggle(GPIO_NRF24L01_MB_LED,NRF24L01_MB_LED);//NRF24L01ģ��״ָ̬ʾ�Ʒ�ת
				
				printf("shoudao\r\n");
				RxPayload[0] = 0;
				LCD_ShowString(30,40,210,12,12,"Residual parking space"); 
				LCD_ShowString(60,80,210,24,24,"3"); 
      }
			if(RxPayload[0] == 0x32)		
      {
				LED_Toggle(GPIO_NRF24L01_MB_LED,NRF24L01_MB_LED);//NRF24L01ģ��״ָ̬ʾ�Ʒ�ת
				
				printf("shoudao\r\n");
				RxPayload[0] = 0;
				LCD_ShowString(30,40,210,12,12,"Residual parking space"); 
				LCD_ShowString(60,80,210,24,24,"2"); 
      }	
			if(RxPayload[0] == 0x33)		
      {
				LED_Toggle(GPIO_NRF24L01_MB_LED,NRF24L01_MB_LED);//NRF24L01ģ��״ָ̬ʾ�Ʒ�ת
				
				printf("shoudao\r\n");
				RxPayload[0] = 0;
				LCD_ShowString(30,40,210,12,12,"Residual parking space"); 
				LCD_ShowString(60,80,210,24,24,"1"); 
      }		
			if(RxPayload[0] == 0x34)		
      {
				LED_Toggle(GPIO_NRF24L01_MB_LED,NRF24L01_MB_LED);//NRF24L01ģ��״ָ̬ʾ�Ʒ�ת
				
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
  unsigned char ucArray_ID [ 4 ];  //�Ⱥ���IC�������ͺ�UID(IC�����к�)
	uint8_t ucStatusReturn;          //����״̬
	
//  while ( 1 )
//  { 

       /*Ѱ��*/
		if ( ( ucStatusReturn = PcdRequest ( PICC_REQALL, ucArray_ID ) ) != MI_OK )                                   
			 /*��ʧ���ٴ�Ѱ��*/
      ucStatusReturn = PcdRequest ( PICC_REQALL, ucArray_ID );		   
		if ( ucStatusReturn == MI_OK  )
		{
      /*����ײ�����ж��ſ������д��������Χʱ������ͻ���ƻ������ѡ��һ�Ž��в�����*/
			if ( PcdAnticoll ( ucArray_ID ) == MI_OK )  
			{
				sprintf ( cStr, "The Card ID is: %02X%02X%02X%02X", ucArray_ID [ 0 ], ucArray_ID [ 1 ], ucArray_ID [ 2 ], ucArray_ID [ 3 ] );							
				printf ( "%s\r\n",cStr ); 
				for(j=0;j<4;j++){
				printf("%d\r\n",ucArray_ID [ j ]);
				}
				if(ucArray_ID [ 3 ]==13)GPIO_ResetBits(GPIOE,GPIO_Pin_1);//��
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
