/*****************************************************************
                             KEY.C  file

��Ҫ���ܣ�����Կ���ģ�鿪�ض�������Ӧ�����ֶ̰���������ֹͣ������
          ������λ��Ӧ��־λ

����ʱ�䣺2013.7.30
*****************************************************************/

/*--------------------------------------------------------------*/
/*---------------------------ͷ�ļ�-----------------------------*/
/*--------------------------------------------------------------*/
#include <STC89C5xRC.h>
#include "KEY.h"
#include "SCR.h"
#include "Sensor_T_H.h"
#include "LUX_LIGHT.h"
#include "CONFIG.h"
/*--------------------------------------------------------------*/



/*--------------------------------------------------------------*/
/*-------------------------ȫ�ֱ�������-------------------------*/
/*--------------------------------------------------------------*/
bit  Key_Cheak;                                      //��־������2����;���������
unsigned int Key_Counter;                            //���ذ��µ�ʱ�������
bit  Long_Cheak;                                     //���ڳ���ʱ������ֹͣ����
bit  Key_Shake;
unsigned char Key_Value;
bit  Key_Flag;


/*--------------------------------------------------------------*/
/*--------------------------���س�ʼ��--------------------------*/
/*--------------------------------------------------------------*/
void init_key()
{
	A0=1;                                              //A0��A1��A2Ϊ74hc148����˿ڣ���Ҫд��1
	A1=1;
	A2=1;
	Key_Cheak=0;                                       //��������ʼ��Ϊ��
	Key_Counter=0x0000;                                //��������ʼ������
	Long_Cheak=0;
	Key_Shake=0;
	Key_Value=0;
	Key_Flag=0;

	
	T2CON=0x00;T2MOD=0x00;                             //���ö�ʱ��2Ϊ16λ�Զ���װ��ģʽ
	RCAP2H=0xFF;RCAP2L=0x0A;                           //���ö�ʱ���Ķ�ʱʱ��Ϊ100us
	TH2=0xFF;TL2=0x0A;
	TR2=1;                                             //������ʱ��T2
	ET2=1;                                             //����ʱ��T2�ж�
//���ж�1��ʼ��
	IE0=0;                                             //���ж�֮ǰ�����һ���жϱ�־λ
	EX0=1;                                             //�����ⲿ�ж�0�����ж�
	IT0=1;                                             //�ⲿ�ж�0Ϊ���ش�����ʽ

}
/*--------------------------------------------------------------*/

/*--------------------------------------------------------------*/
/*-------------------------�ⲿ�ж�0����------------------------*/
/*--------------------------------------------------------------*/
void interrupt_INT0() interrupt 0                    //�ⲿ�ж�0���жϺ�Ϊ0
{
	Key_Cheak=1;                       //����������⣬������ʹ�������ڶ�ʱ��2�жϳ��������
	Key_Counter=0x0000;
	Key_Value=0;
	EX0=0;                                     //�ر��ⲿ�ж�0����ֹ������������ظ������ж�
	IE0=0;	                     //                //Ϊ����������ٴ�����ⲿ�ж�����λ
}
/*--------------------------------------------------------------*/

/*--------------------------------------------------------------*/
/*------------------------��ʱ��2�жϳ���-----------------------*/
/*--------------------------------------------------------------*/
void interrupt_timer2() interrupt 5                    //��ʱʱ��Ϊ100us
{
	TF2=0;                         //��ն�ʱ��2���ж������־λ��T2���ж������־λ��Ҫ�������

/*-----------------------�ɿع败�������������-------------------------*/	
	SCR_counter++;
	if(SCR_counter==SCR1_value)				//�ɿع����ʱ��ֵͨ
	{
		SCR1=0;								//����SCR1���Ƶ�����
		SCR1_timer=SCR1_value;				//
	}
	if(SCR_counter==SCR2_value)				//�ɿع����ʱ��ֵͨ
	{
		SCR2=0;								//����SCR2���Ƶ�����
		SCR2_timer=SCR2_value;
	}
	if(SCR_counter==(SCR1_timer+SCR_TIGGER_TIME))          //ʹ��ͨ������ά��1ms
		SCR1=1;							
	if(SCR_counter==(SCR2_timer+SCR_TIGGER_TIME))
		SCR2=1;
/*---------------------------------------------------------------*/
	
/*-----------------------�ɿع��������������-------------------------*/	
	if(SCR1_control_flag||SCR2_control_flag)               //��������ʱ�ɿع�Ŀ���
	{
		SCR_control_counter++;                             //�ɿع���Ƽ�������1
		if(SCR_control_counter==SCR_CHANGE_RATE)//0.1s�ɿع���ʱ��ֵͨ���ӻ��߼���1�Σ�����ʱ�����������Ҫ7s��
		{
			if(SCR1_control_flag)                            //��ؿ�1
			{
				if(SCR1_value>SCR_TOP_THRESHOLD)             //ѭ�����ƣ������ʱ��������
				{
					SCR1_status=0;
					SCR1_value=SCR_TOP_THRESHOLD;
				}
				else if(SCR1_value<SCR_BOTTOM_THRESHOLD)       //ѭ�����ƣ���������ʱ���𽥱䰵
				{
					SCR1_status=1;
					SCR1_value=SCR_BOTTOM_THRESHOLD;
				}
				if(SCR1_status)
					SCR1_value++;
				else
					SCR1_value--;
				if(SCR1_value%10==0)                           //���������ʵʱ��������ֵ
					SCR1_Flag=1;
			}
			
			if(SCR2_control_flag)                            //��ؿ�2
			{
				if(SCR2_value>SCR_TOP_THRESHOLD)
				{
					SCR2_status=0;
					SCR2_value=SCR_TOP_THRESHOLD;
				}
				else if(SCR2_value<SCR_BOTTOM_THRESHOLD)       //ѭ�����ƣ���������ʱ���𽥱䰵
				{
					SCR2_status=1;
					SCR2_value=SCR_BOTTOM_THRESHOLD;
				}
				
				if(SCR2_status)
					SCR2_value++;
				else
					SCR2_value--;
				if(SCR2_value%10==0)
					SCR2_Flag=1;
			}
			
			SCR_control_counter=0;

		}
	}
/*-----------------------------------------------------------*/

/*--------�����Ķ�ȡ���̰���������ֹͣ���Ƶ��жϣ�����-------*/	
	if(Key_Cheak)				//����ʹ83�������������崥���ж�1--keycheak=1;
	{
		Key_Counter++;
//1		
		if(Key_Counter==KEY_SHAKE_TIME) 		  //��������ʱ��KEY_SHAKE_TIME =500,�൱��50ms	
								//�ӳ�50ms���ȡ������ֵ����ֹ�����������ȡֵ���󣬰���ǰ����
		{	
			
			if(!INT0)		//���������ڰ���		//�ж��ⲿ�ж�0��P32�ڰ����Ƿ��ڰ���
			{
				//3��if�����ж�
				if(A0)			//sbit A0=P2^4;8-3���������λ
					Key_Value=Key_Value|0x01;			
				if(A1)			//sbit A1=P2^5; 8-3�������ڶ�λ
					Key_Value=Key_Value|0x02;		
				if(A2)			//sbit A2=P2^6; 8-3���������λ
					Key_Value=Key_Value|0x04;	
					
				Key_Value=~Key_Value;          //74148�ı���Ϊ����
				Key_Value=Key_Value&0x07;	   //�õ��˰�������74148�Ķ˿���
			}
			else		//�����ɿ�������Ϊ�����
			{
				Key_Cheak=0;
				Key_Counter=0;
				Key_Shake=1;
			}
		}
//2		
		if(Key_Counter>KEY_SHAKE_TIME)               //����ǰ����֮��ʼ�жϰ����ǳ������Ƕ̰�
		{
			if(INT0)             //�����ɿ�          //�̰�//
			{
				Key_Value=Key_Value|0x80;
				Key_Shake=1;
				Key_Cheak=0;
				Key_Counter=0;
				Key_Flag=1;
			}
			else if(Key_Counter==KEY_BOUNDARY_TIME) //����δ�ɿ�  //����
			{										//KEY_BOUNDARY_TIME�൱��0.5S���̰�����ֵ
				Key_Value=Key_Value|0x40;
				Long_Cheak=1;
				Key_Cheak=0;
				Key_Counter=0;
				Key_Flag=1;
			}
		}
	}
	
	if(Long_Cheak)                                       //ֹͣ���Ƽ��
	{
		if(INT0)								//�����ɿ�
		{
			Key_Value=Key_Value|0x20;
			Key_Shake=1;
			Long_Cheak=0;
			Key_Flag=1;
		}
	}
	
	if(Key_Shake)                         //��������������ֹ�ɿ������Ķ�����ɴ���İ���������Ӧ
	{
		Key_Counter++;
		if(Key_Counter==KEY_SHAKE_TIME)			//��������ʱ�䣬500*100us=50ms
		{
			Key_Shake=0;
			Key_Counter=0;
			IE0=0;            //���ж�0�������־λ          //���ⲿ�ж�֮ǰ�������һ���жϱ�־λ
			EX0=1;                                           //���ⲿ�ж�
		}
	}
/*-------------------------------------------------------------*/

/*--------------------�����ഫ�����ӳٿ���---------------------*/	
	if(Sound_Sensor_Flag2)
	{
		Sound_Sensor_Counter++;
		if(Sound_Sensor_Counter==10000)
		{
			Sound_Sensor_Counter=0;
			Sound_Sensor_Counter1++;
			if(Sound_Sensor_Counter1==Switch_Sensor_Config[2])
			{
				Sound_Sensor_Counter=0;
				Sound_Sensor_Counter1=0;
				Sound_Check_Flag=1;
				Sound_Pack_Flag=1;
				Sound_Sensor_Flag2=0;
			}
		}
	}

/*-------------------��ʪ�Ȳ��Լ��ʱ�����--------------------*/
	Sensor_T_H_Counter++;
	if(Sensor_T_H_Counter==20000)                            //ÿ��2s����һ���¶Ⱥ�ʪ��
	{
		Sensor_T_H_Flag=1;
		Sensor_T_H_Counter=0;
		Lux_Start_Flag=1;                                      //ÿ��2s����һ�ι��ն�ֵ
	}
/*-------------------���ղ��Լ��ʱ�����--------------------*/		
	if(Lux_Flag)                                   //�������նȴ�������200ms��ʼ��ȡ���ն�ֵ
	{
		Lux_Counter++;
		if(Lux_Counter==2000)
		{
			Lux_Read_Flag=1;
			Lux_Counter=0;
			Lux_Flag=0;
		}
	}
}