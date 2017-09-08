#include <STC89C5xRC.h>
#include "CONTROL.h"
#include "TELE_MANAGE.h"
#include "TELE_T_R.h"
#include "TELE_PARSE.h"
#include "TELE_PACK.h"
#include "RELAY.h"
#include "SCR.h"
#include "Sensor_T_H.h"
#include "LUX_LIGHT.h"
#include <intrins.h>

sbit sound=P1^5;
void main()
{
	unsigned char i;
	
	init_tele_t_r();				//���ķ��������ģ���ʼ��
	init_config();					//��ʼ������
	init_tele_manage();				//���Ĺ����ʼ��
	init_scr();						//�ɿع��ʼ��
	init_sensor_t_h();				//��ʪ�ȴ�������ʼ��
	init_lux();						//���նȴ�������ʼ��
	init_key();						//���س�ʼ��
	init_relay();					//�̵�����ʼ��
	SM2=1;			         //���нڵ㴦�ڼ���״̬		
	
	sound=1;				//���˿�ǰ����1

	for(i=0;i<255;i++)				//��ʱ��Լ6us
		_nop_();
	for(i=0;i<255;i++)				//��ʱ��Լ6us
		_nop_();
	for(i=0;i<255;i++)				//��ʱ��Լ6us
		_nop_();
	for(i=0;i<255;i++)				//��ʱ��Լ6us
		_nop_();
	RI=0;									//���ڽ��ձ�־λ����
	TI=0;									//���ڷ��ͱ�־λ����
	EA=1;                                             //�����ж�
	ES=1;                                             //�������ж�
	REN=1;                                            //�����������
	WDT_CONTR=0x3F;									//���Ź��Ĵ�������
	
	while(1)
	{
		if(Tele_Cheak_T)	//���ͻ�����м���־λ�����������Ƿ��б��ģ�����ֵΪ1��һֱ�ڼ��
			tele_cheakt();					//���Ļ�����м�麯��
		if(Tele_Cheak_R)					//���ջ�����м���־λ�����������Ƿ��б���
			tele_cheakr();					//���Ļ�����м�麯��
			
		if(Tele_TF)							//���ķ��ͱ�־λ����tele_cheakt()����1
			telegram_t();					//���ķ��ͳ���
		if(Tele_Handle_R)					//���ջ��������Ĵ����־λ,tele_cheakr()����1
			tele_parse();					//���Ľ�������
			
		if(Key_Flag)						//����������־λ
		{
			tele_pack_key();				//��������������װ����
		}
		if(Relay_Flag)						//�̵���������־λ
			tele_pack_relayval();			//�̵���״̬����
		if(SCR1_Flag)						//�ɿع��1״̬�ı��־λ
		{
			tele_pack_scrval();				//�ɿع�״̬��������
			Scr1_Act_Flag=1;
		}	
		if(SCR2_Flag)						//�ɿع��2״̬�ı��־λ
		{
			tele_pack_scrval();				//�ɿع�״̬��������
			Scr2_Act_Flag=1;
		}
				
		if(Sound_Check_Flag)				//������������־λ
		{
			if(sound==0)					//��⵽������
			{
				Sound_Check_Flag=0;
				Sound_Pack_Flag=1;			//����������װ��־λ
			}
		}	
		if(Sound_Pack_Flag)
			tele_pack_sound();				//������������������ 
		
		if(Sensor_T_H_Flag)					//��ʱ��2��ÿ��2s
			star_sensor_t_h();				//������ʪ�ȴ�����
		if(Sensor_T_H_Flag1&&T_H_Data==0)	//��ʪ�ȴ�����IICͨ�������ź�
			read_sensor_t_h();				//��ȡ��ʪ�ȴ�����

		if(Lux_Start_Flag)				
			start_lux();					//�������նȴ�����
		if(Lux_Read_Flag)					//���ն�ȡ��־λ����ʱ��1ÿ200ms��ȡһ��
			read_lux();						//��ȡ���նȴ�����					
			
		if(Lux_Check_Flag)														//����ǿ�ȼ���־λ
		{
			if(Lux_Value>=Analog_Threshold[0])
			{
				Lux_Check_Flag=0;
				Lux_High_Flag=1;
				tele_pack_lux();
			}
			else if(Lux_Value<=Analog_Threshold[3])
			{
				Lux_Check_Flag=0;
				Lux_Low_Flag=1;
				tele_pack_lux();
			}
		}
		if((Lux_Value<Analog_Threshold[0])&&(Lux_Value>Analog_Threshold[3]))	//ֱ������ֵ���ʲŻָ����
		{
			Lux_Check_Flag=1;
		}	
		
		if(Relay_Check_Flag)													//�̵���״̬����־λ
		{
			if(Relay1_Alconfig_Flag&&Relay1_Act_Flag)								//�Ѿ����ù����Ҽ̵����ж���
			{
				Relay1_Act_Flag=0;												//��ձ��ζ�����־λ
				Relay_Check_Flag=0;
				Which_Relay=0;
				tele_pack_relay();	
			}
			else if(Relay2_Alconfig_Flag&&Relay2_Act_Flag)								//�Ѿ����ù����Ҽ̵����ж���
			{
				Relay2_Act_Flag=0;												//��ձ��ζ�����־λ
				Relay_Check_Flag=0;
				Which_Relay=1;
				tele_pack_relay();	
			}
			else if(Relay3_Alconfig_Flag&&Relay3_Act_Flag)								//�Ѿ����ù����Ҽ̵����ж���
			{
				Relay3_Act_Flag=0;												//��ձ��ζ�����־λ
				Relay_Check_Flag=0;
				Which_Relay=2;
				tele_pack_relay();	
			}
			else if(Relay4_Alconfig_Flag&&Relay4_Act_Flag)								//�Ѿ����ù����Ҽ̵����ж���
			{
				Relay4_Act_Flag=0;												//��ձ��ζ�����־λ
				Relay_Check_Flag=0;
				Which_Relay=3;
				tele_pack_relay();	
			}
		}
		if(Scr_Check_Flag)
		{
			if((Scr1_Alconfig_Flag&&Scr1_Act_Flag)||(Scr2_Alconfig_Flag&&Scr2_Act_Flag))							//�Ѿ����ù����Ҽ̵����ж���
			{
				Scr_Check_Flag=0;											//ֹͣ���
				if(Scr1_Act_Flag)
				{
					Scr1_Act_Flag=0;												//��ձ��ζ�����־λ				
					tele_pack_scr1();					
				}
				if(Scr2_Act_Flag)
				{
					Scr2_Act_Flag=0;												//��ձ��ζ�����־λ				
					tele_pack_scr2();						
				}

			}
		}
//��ʱ��תָ��ʱ�䵽		
		if(Time_Up1)
		{					
			Delay_Flag1=0;
			jump_order(0);
			jump_tele[0]=0;
			Time_Up1=0;
		}
		if(Time_Up2)
		{					
			Delay_Flag2=0;
			jump_order(7);
			jump_tele[7]=0;
			Time_Up2=0;
		}
		if(Time_Up3)
		{					
			Delay_Flag3=0;
		 	jump_order(14);
			jump_tele[14]=0;
			Time_Up3=0;
		}	
		if(Time_Up4)
		{					
			Delay_Flag4=0;
			jump_order(21);
			jump_tele[21]=0;
			Time_Up4=0;
		}	
		WDT_CONTR=0x3F;
	}
}