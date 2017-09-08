/*****************************************************************
                        TELE_PACK.c  file

��Ҫ���ܣ����ݰ����������Ӧ�����룬�������

����ʱ�䣺2015.10.31
*****************************************************************/
/*--------------------------------------------------------------*/
/*----------------------------ͷ�ļ�------------------ ---------*/
/*--------------------------------------------------------------*/
#include "TELE_PACK.h"
#include "TELE_MANAGE.h"
#include "CONFIG.h"
#include "CONTROL.h"
#include "RELAY.h"
#include "SCR.h"
#include "SENSOR_T_H.h"
#include "LUX_LIGHT.h"
#include "TELE_T_R.h"
#include "TELE_PARSE.h"
/*-------------------------------------------------------------*/
/*-------------------------ȫ�ֱ�������------------------------*/
/*-------------------------------------------------------------*/


/*-------------------------------------------------------------*/
/*-----------------ָ��ģ���������������װ����--------------*/
/*--------------------Key_Flag=1ʱ������������-----------------*/
/*-------------------------------------------------------------*/
void tele_pack_key()                                               
{	
	unsigned char Which_Key;
	unsigned int addr;
	Key_Flag=0;                                  //����������־λ���㣬��ֹ������ѭ�����ô˺���
	Which_Key=Key_Value&0x07;                    //��ȡ��������ֵ--��Ӧ��74148�Ķ˿���ֵ
	addr=0x8200+(Which_Key<<9);

	if(Key_Value&0x80)							//�����̰�			
	{
		Key_Value=0;
		order(addr);							//��ָ����
	}	
	else if(Key_Value&0x40)						//��������
	{
		Key_Value=Key_Value&0x0F;				//��⵽������ѱ�־λ���㣬������ֵ���Ա������ɿ�����
		order(addr+64);							//��ָ����
	}
	else 										//��������ֹͣ
	{
		Key_Value=0;
		order(addr+128);						//ָͣ����
	}		
}
/*--------------------------------------------------------------*/
/*--------------ָ��ģ�������������������--------------------*/
/*--------------Switch_Sound_Flag1=1ʱ������������--------------*/
/*--------------------------------------------------------------*/
void tele_pack_sound()                 								//�ݶ�һ·����                             
{	                                           	
//	unsigned char Which_Digital=0;
	unsigned int addr=0x9200;						//��������
//	addr=0x9200+(Which_Digital<<9);

	Sound_Delay[0]=rom_r(addr+9);					//�ĸ�Ŀ��ִ����ͬ����ʱʱ��
//	Sound_Delay[1]=rom_r(addr+25);					//ռʱͬһ��ʱʱ�䣨�����ã�
//	Sound_Delay[2]=rom_r(addr+41);
//	Sound_Delay[3]=rom_r(addr+57);
	if(!Sound_Pack2_Flag)							//����ʱ֮ǰ�ı���
	{					
		order(addr);
		Sound_Delay1_Flag=1;						//����ʱ��־λ����ʼ��ʱ��ʱʱ��
	}
	if(Sound_Pack2_Flag)							//������ʧ��ָͣ����
	{
		order(addr+128);
		Sound_Pack2_Flag=0;		
	}
}
/*--------------------------------------------------------------*/
/*-------------ָ��ģ����մ�������ֵ��������-----------------*/
/*--------------Lux_Low_Pack_Flag=1ʱ������������---------------*/
/*--------------------------------------------------------------*/
void tele_pack_lux()                         	//                    
{	
	unsigned int addr;    
	addr=0xA000;                                           	

	if(Lux_High_Flag)
	{
		Lux_High_Flag=0;
		order(addr);							//��������,��ָ��

	}
	if(Lux_Low_Flag)							//������ʧ��ָͣ����
	{
		Lux_Low_Flag=0;
		order(addr+128);
	}	
}
/*--------------------------------------------------------------*/
/*--------------ָ��ģ��̵������״̬��������----------------*/
/*--------------Switch_Sound_Flag1=1ʱ������������--------------*/
/*--------------------------------------------------------------*/
void tele_pack_relay()                          	//
{		                                          	
//	unsigned char Which_Relay=0;
	unsigned int addr=0;
	addr=0xA800+(Which_Relay<<9);
	
	if(((Relay_Value>>Which_Relay)&0x01)==0x01)
		Relay_On_Flag=1;
	if(((Relay_Value>>Which_Relay)&0x01)==0x00)
		Relay_Off_Flag=1;
	Which_Relay=0;									//���ĳһ·�̵�����ʶ
	if(Relay_On_Flag)								//��������,��ָ��
	{												
		Relay_On_Flag=0;							//�رձ�־λ��ֹ�ٴ���װ
		order(addr);								//��ָ����
		Relay_Check_Flag=1;							//����״̬����־λ
	}
	if(Relay_Off_Flag)								//������ʧ��ָͣ����
	{
		Relay_Off_Flag=0;							//�رձ�־λ��ֹ�ٴ���װ
		order(addr+128);							//ָͣ����
		Relay_Check_Flag=1;							//����״̬����־λ
	}	
}
/*--------------------------------------------------------------*/
/*--------------ָ��ģ��ɿع�1���״̬��������----------------*/
/*--------------Switch_Sound_Flag1=1ʱ������������--------------*/
/*--------------------------------------------------------------*/
void tele_pack_scr1()                          //             ��û�趨����       
{		                                          	
	unsigned int addr;
	addr=0xB800;

	if(SCR1_value==0xF0)	
		Scr_100_Flag=1;	
	if(SCR1_value==0x01)
		Scr_Off_Flag=1;		
	if(Scr_100_Flag)							//��������,��ָ��
	{												
		Scr_100_Flag=0;							//�رձ�־λ��ֹ�ٴ���װ
		order(addr+128);						//ָͣ����
		Scr_Check_Flag=1;						//����״̬����־λ
	}
	if(Scr_Off_Flag)							//������ʧ��ָͣ����
	{
		Scr_Off_Flag=0;							//�رձ�־λ��ֹ�ٴ���װ
		order(addr);							//��ָ����	
		Scr_Check_Flag=1;						//����״̬����־λ
	}	
}
/*--------------------------------------------------------------*/
/*--------------ָ��ģ��ɿع�2���״̬��������----------------*/
/*--------------Switch_Sound_Flag1=1ʱ������������--------------*/
/*--------------------------------------------------------------*/
void tele_pack_scr2()                          //             ��û�趨����       
{		                                          	
	unsigned int addr;
	addr=0xBA00;

	if(SCR2_value==0xF0)	
		Scr_100_Flag=1;	
	if(SCR2_value==0x01)
		Scr_Off_Flag=1;		
	if(Scr_100_Flag)							//��������,��ָ��
	{												
		Scr_100_Flag=0;							//�رձ�־λ��ֹ�ٴ���װ
		order(addr+128);						//ָͣ����
		Scr_Check_Flag=1;						//����״̬����־λ
	}
	if(Scr_Off_Flag)							//������ʧ��ָͣ����
	{
		Scr_Off_Flag=0;							//�رձ�־λ��ֹ�ٴ���װ
		order(addr);							//��ָ����	
		Scr_Check_Flag=1;						//����״̬����־λ
	}	
}
/*-------------------------------------------------------------*/
/*-------------------�������ģ��̵���״̬��Ϣ------------------*/
/*-----------------Relay_Flag=1ʱ������������------------------*/
/*-------------------------------------------------------------*/
void tele_pack_relayval()
{
	unsigned char Relay_Date[7]={0x00,0x00,0x00,0x00,0x00,0x00,0x00};
	Relay_Flag=0;                                                //��ռ̵���������־Ϊ
	Relay_Date[0]=0x84;						//������������֡����������+�̵���״̬����+��������֡4֡��
	Relay_Date[1]=0x00;						//ȺID
	Relay_Date[2]=0x04;						//����ģ��IDΪ����04
	
	Relay_Date[3]=0x70;						//��������֡1
	Relay_Date[4]=0x00;						//��������֡2
	Relay_Date[5]=Relay_Value;				//״̬��Ϣ֡1-----��ʷ״̬----Relay_Value1
	Relay_Date[6]=Relay_Value;				//״̬��Ϣ֡2-----��ǰ״̬
	write_tele_t(Relay_Date,7);
	Relay_Value1=Relay_Value;                                            //���¼̵�������ֵ
}
/*-------------------------------------------------------------*/
/*-----------------�������ģ��ɿع�����ֵ----------------------*/
/*----------SCR1_Flag=1����SCR2_Flag=1ʱ������������-----------*/
/*-------------------------------------------------------------*/
void tele_pack_scrval()
{
	unsigned char SCR_Date[6]={0x00,0x00,0x00,0x00,0x00,0x00};
	if(SCR1_Flag)
	{
		SCR1_Flag=0;
		SCR_Date[0]=0x83;   					//������������֡����������+��1״̬+��������֡3֡��
		SCR_Date[1]=0x00;						//����ȺID
		SCR_Date[2]=0x04;						//����ģ������04
		
		SCR_Date[3]=0x80;						//��ؿ�1����
		SCR_Date[4]=0x00;										
		SCR_Date[5]=SCR1_value;
		write_tele_t(SCR_Date,6);
	}
	if(SCR2_Flag)
	{
		SCR2_Flag=0;
		SCR_Date[0]=0x83;                                 //������������Ϊ10����������
		SCR_Date[1]=0x00;						//����ȺID
		SCR_Date[2]=0x04;						//����ģ������04
		SCR_Date[3]=0x81;						//��ؿ�2����
		SCR_Date[4]=0x00;
															
		SCR_Date[5]=SCR2_value;
		write_tele_t(SCR_Date,6);
	}
}
/*--------------------------------------------------------------*/
/*------------------�������ģ�ID��Ϣ----------------------------*/
/*-----------------ID_Flag=1ʱ������������----------------------*/
/*--------------------------------------------------------------*/
void tele_pack_id()
{
	unsigned char ID_Date[6]={0x00,0x00,0x00,0x00,0x00,0x00};                                                          
	ID_Date[0]=0x83;						//������������֡������+id��ַ+��������֡3֡��
	ID_Date[1]=0x00;						//����ȺID
	ID_Date[2]=0x04;						//����ģ������04
	ID_Date[3]=0x00;						//��������֡1
	ID_Date[4]=0x00;						//��������֡2														
	ID_Date[5]=ID;
	write_tele_t(ID_Date,6);
}
/*-----------------------------------------------------------------*/
/*-------------------�������ģ�ģ�������鱨����Ϣ------------------*/
/*-----------------------------------------------------------------*/
void tele_pack_Module_Contain_Group()
{
	unsigned char Module_Contain_Group[6]={0x00,0x00,0x00,0x00,0x00,0x00};
                                                          //ID��Ϣ���ͱ�־λ����
	Module_Contain_Group[0]=0x83;						//������������֡������+id��ַ+��������֡3֡��												
	Module_Contain_Group[1]=0x00;						//����ȺID
	Module_Contain_Group[2]=0x04;						//����ģ������04
	
	Module_Contain_Group[3]=0x01;						//��������֡1
	Module_Contain_Group[4]=0x00;						//��������֡2														
	Module_Contain_Group[5]=ID_GP_Q[2];
	write_tele_t(Module_Contain_Group,6);
}
/*-------------------------------------------------------------*/
/*-----------------�������ģ�����Ϣ���汨��--------------------*/
/*-----------------��ģ��������Щ����--------------------------*/
/*-------------------------------------------------------------*/
void tele_pack_group()
{
	unsigned char Group[6]={0X00,0X00,0X00,0X00,0X00,0x00};
	Group[0]=0x93;
	Group[1]=0x00;
	Group[2]=0x04;
	
	Group[3]=0x01;
	Group[4]=0x00;
	Group[5]=Group_a;											//�Ϸ�����һ���鷴��
	write_tele_t(Group,6);	
}
/*-------------------------------------------------------------*/
/*----------------�������ģ����նȱ�����װ����-----------------*/
/*-----------------�ɲ�ѯ��װ���ĺ�������----------------------*/
/*-------------------------------------------------------------*/
void tele_pack_luxvalue()
{
	unsigned char Lux_Data[6]={0xFF,0x00,0x00,0x00,0x00,0x00};
	Lux_Data[0]=Lux_Data[0]&0xBF;                                       //������������Ϊ10����������
	Lux_Data[0]=Lux_Data[0]&0xF3;                                    //����������֡��Ϊ3	
	Lux_Data[1]=0x00; 									  //����ȺID
	Lux_Data[2]=0x04;									  //����ģ��IDΪ����04
	
	Lux_Data[3]=0x60;   
	Lux_Data[4]=0x00;                                                   //0Ϊ���նȷ���
	Lux_Data[5]=Lux_Value/10;       //���յ���ֵ��ΧΪ0-2550������һ���ֽڷ���ģ������ֵ                                                             
	write_tele_t(Lux_Data,6);
}
/*--------------------------------------------------------------*/
/*---------------�������ģ��¶ȱ�����װ����--------------------*/
/*--------------------�ɲ�ѯ���ĺ�������-----------------------*/
/*-------------------------------------------------------------*/
void tele_pack_temperature()
{
	unsigned char Temperature_Date[6]={0xFF,0x00,0x00,0x00,0x00,0x00};
	float t;
	Temperature_Date[0]=Temperature_Date[0]&0x8F;                     //������������Ϊ10����������
	Temperature_Date[0]=Temperature_Date[0]&0xF3;                     //����������֡��Ϊ3

	Temperature_Date[1]=0x00;
	Temperature_Date[2]=0x04;
	
	Temperature_Date[3]=0x60;							//��������֡1
	Temperature_Date[4]=0x01;                                               //1Ϊ�¶�ֵ����
	t=Temperature/1;
	if(t<0)
	{
		t=0-t;
		Temperature_Date[5]=(unsigned char)t;
		Temperature_Date[5]=Temperature_Date[3]|0x80;                      //���λ��������Ǹ��¶�
	}
	else
		Temperature_Date[5]=(unsigned char)t;
	write_tele_t(Temperature_Date,6);
}
/*--------------------------------------------------------------*/
/*------------------�������ģ�ʪ�ȱ�����װ����------------------*/
/*----------------Humidity_Flag=1ʱ������������-----------------*/
/*--------------------------------------------------------------*/
void tele_pack_humidity()
{
	unsigned char Humidity_Date[6]={0xFF,0x00,0x00,0x00,0x00,0x00};
	float t;                                             
	Humidity_Date[0]=Humidity_Date[0]&0x8F;                              //������������Ϊ10����������
	Humidity_Date[0]=Humidity_Date[0]&0xF3;                              //������Ϊ3֡

	Humidity_Date[1]=0x00;
	Humidity_Date[2]=0x04;
	
	Humidity_Date[3]=0x60;
	Humidity_Date[4]=0x02;                                                  //2Ϊʪ��ֵ����
	t=Humidity/1;
	if(t<0)                                                              //ʪ��ֵ�϶������Ǹ���
		Humidity_Date[5]=0;
	else
		Humidity_Date[5]=(unsigned char)t;
	write_tele_t(Humidity_Date,6);
}
/*--------------------------------------------------------------*/
/*----------------�������ģ�ָ��������Ϣ���� -------------------*/
/*-----------------------��ѯ���ĺ�������-----------------------*/
/*--------------------------------------------------------------*/
void tele_pack_shortconfig(unsigned int address)				//���ж�ָ���з���
{
	unsigned char i,n;
	unsigned char Config_Date[12]={0xFF,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00};
	Config_Date[0]=Config_Date[0]&0x8F;                  //�������ԣ���������
//	Config_Date[0]=Config_Date[0]&0xF7;                  //�������Ա��������򳤶�Ϊ7
	
	Config_Date[1]=0x00;					//����ȺID
	Config_Date[2]=0x04;					//����ģ��04

	if(Key_Num1)		
		Config_Date[3]=Key_Num1;		//������������֡1
	else if(Digital_Num1)
		Config_Date[3]=Digital_Num1;
	else if(Analog_Num1)
		Config_Date[3]=Analog_Num1;
	else if(Relay_Num1)
		Config_Date[3]=Relay_Num1;
	else if(Scr_Num1)
		Config_Date[3]=Scr_Num1;

	if(rom_r(address+1)!=0xFF)							//Ŀ��1����
	{
		n=(rom_r(address+1)&0x0F)+0x03;			//��������[22 00 08 00 12]   5֡ 
		Config_Date[0]=Config_Date[0]&(0xF0|n+2);                  //�����������Ա��������򳤶�7
		Config_Date[4]=0x00|style;					//��������֡2
		for(i=0;i<n;i++)
		{
			Config_Date[5+i]=rom_r(address+1+i);
		}
		write_tele_t(Config_Date,n+5);						
	}
	if(rom_r(address+17)!=0xff)						//Ŀ��2�ķ���
	{
		n=(rom_r(address+17)&0x0F)+0x03;
		Config_Date[0]=Config_Date[0]&(0xF0|n+2);                  //�����������Ա��������򳤶�7
		Config_Date[4]=0x02|style;					//��������֡2	
		for(i=0;i<n;i++)
		{
			Config_Date[5+i]=rom_r(address+17+i);
		}
		write_tele_t(Config_Date,n+5);
	}
}
/*-----------------------------------------------------------------*/
/*-------------------�������ģ�������Ϣ���óɹ�--------------------*/
/*-----------------------------------------------------------------*/
void config_success()
{
	unsigned char ID_Date[6]={0x00,0x00,0x00,0x00,0x00,0x00};                                                          
	ID_Date[0]=0x83;						//������������֡������+id��ַ+��������֡3֡��												
	ID_Date[1]=0x00;						//����ȺID
	ID_Date[2]=0x04;						//����ģ������04
	ID_Date[3]=0xF0;						//��������֡1
	ID_Date[4]=0x00;						//��������֡2
	ID_Date[5]=0xbb;																				
	write_tele_t(ID_Date,6);	
}
/*--------------------------------------------------------------*/
/*-----------------�������ã�ָ���ȡ-------------------------*/
/*--------------------------------------------------------------*/
void order(unsigned int address)
{
	unsigned char n,i;
	unsigned char Cache[8];
	if(rom_r(address+1)!=0xFF)							//Ŀ��1ָ��
	{
		for(i=0;i<8;i++)
			Cache[i]=rom_r(address+1+i);
		n=(Cache[0]&0x0F)+3;
		write_tele_t(Cache,n);
	}
	if(rom_r(address+17)!=0xff)							//Ŀ��2 ָ��
	{
		for(i=0;i<8;i++)
			Cache[i]=rom_r(address+17+i);
		n=(Cache[0]&0x0F)+3;
		write_tele_t(Cache,n);
	}
	if(rom_r(address+33)!=0xff)							//Ŀ��3ָ��
	{			
		for(i=0;i<8;i++)
			Cache[i]=rom_r(address+33+i);
		n=(Cache[0]&0x0F)+3;
		write_tele_t(Cache,n);
	}
	if(rom_r(address+49)!=0xff)							//Ŀ��4ָ��
	{
		for(i=0;i<8;i++)
			Cache[i]=rom_r(address+49+i);
		n=(Cache[0]&0x0F)+3;
		write_tele_t(Cache,n);
	}	
}