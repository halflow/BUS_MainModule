/*****************************************************************
                           CONFIG.C  file

��Ҫ���ܣ���ģ��������ù���ʵ��

����ʱ�䣺2015.10.31
*****************************************************************/
/*--------------------------------------------------------------*/
/*-----------------------------ͷ�ļ�---------------------------*/
/*--------------------------------------------------------------*/
#include "CONFIG.h"
#include <intrins.h>
#include <STC89C5xRC.h>

unsigned char bdata Temp1;					//��ŵ�λѰַ��
unsigned char bdata Temp2;

sbit Temp1_0=Temp1^0;
sbit Temp1_1=Temp1^1;
sbit Temp1_2=Temp1^2;
sbit Temp1_3=Temp1^3;
sbit Temp1_4=Temp1^4;
sbit Temp1_5=Temp1^5;
sbit Temp1_6=Temp1^6;
sbit Temp1_7=Temp1^7;
sbit Temp2_0=Temp2^0;
sbit Temp2_1=Temp2^1;
sbit Temp2_2=Temp2^2;
sbit Temp2_3=Temp2^3;
sbit Temp2_4=Temp2^4;
sbit Temp2_5=Temp2^5;
sbit Temp2_6=Temp2^6;
sbit Temp2_7=Temp2^7;

unsigned char ID1,ID2;

unsigned char ID_GP_Q[3];					//Ⱥ��ַ,ID��ַ������
unsigned char Analog_Threshold[16];
unsigned char Write_Cache[192];
unsigned char Sound_Delay[4];               //����ʱʱ����������������ֹ��ʱʱ���ڻ�����ռ��     
bit Sound_Delay1_Flag;						//Ŀ��1����ʱ��־λ
//	bit Sound_Delay2_Flag;
//	bit Sound_Target3_Flag;
//	bit Sound_Target4_Flag;
bit  Sound_Check_Flag=1;					//��������־λ����ʼ��Ϊ1��������
bit  Sound_Pack_Flag=0;						//��⵽�����󣬱�����װ��־λ
bit  Sound_Pack2_Flag=0;					//��ʱ����װ�ı��ı�־λ
unsigned int Sound_Sensor_Counter=0;
unsigned char Sound_Sensor_Counter1=0;


bit Relay1_Alconfig_Flag,Relay2_Alconfig_Flag,Relay3_Alconfig_Flag,Relay4_Alconfig_Flag;
bit Scr1_Alconfig_Flag;
bit Scr2_Alconfig_Flag;
/*--------------------------------------------------------------*/
/*--------------------------��ʼ������--------------------------*/
/*--------------------------------------------------------------*/
void init_config()
{
	unsigned char i;
	
	i=rom_r(0x8000);	                                   
	if(i!=0xAA)          			        //�ж�EEPROM�Ƿ��Ѿ����ù���������ù���0x8000��ֵΪ0xAA
	{
		rom_c(0x8000);                                   //��յ�һ������׼��д��ȱʡ����   
		
		rom_w(0x8001,0);                                  //ȺID    ȱʡΪ0
		rom_w(0x8002,5);                                 //ģ��ID  ȱʡΪ5
		rom_w(0x8003,0x00);                               //��ID��8λ 	ȱʡΪ0	
		rom_w(0x8004,0x00);                               //��ID��8λ 	ȱʡΪ0	
		for(i=0;i<3;i++)								  //3·ģ��������ֵ  ȱʡ0xFF
		{
			rom_w(0x8010+i,0xFF);
			i=i+1;
		}
		for(i=0;i<3;i++)								  //3·ģ��������ֵ ȱʡ0x00
		{
			rom_w(0x8013+i,0x00);
			i=i+1;
		}		                       				
		rom_w(0x8000,0xAA);                                //��0x8000��ֵдΪ0xAA����־��һ�����Ѿ����й�����
	}	
	for(i=0;i<3;i++)				/*��EEPROM֮ǰ���ö��뵽RAM��*/					
	{
		ID_GP_Q[i]=rom_r(0x8001+i);
	}
	for(i=0;i<6;i++)				/*��EEPROM֮ǰ���ö��뵽RAM��*/
	{
		Analog_Threshold[i]=rom_r(0x8010+i);
	}	
	id_chang();												//����ģ���ID���ת��
}
/*--------------------------------------------------------------*/
/*--------------------------IDת������--------------------------*/
/*------�����ܣ���һ֡�����ȷ�ת��Ȼ���ڽ�һ֡������չ������--*/
/*--------------------------------------------------------------*/
void id_chang()
{
	Temp1=ID;
	Temp2_0=Temp1_7;					//�ߵ�λת��
	Temp2_1=Temp1_6;
	Temp2_2=Temp1_5;
	Temp2_3=Temp1_4;
	Temp2_4=Temp1_3;
	Temp2_5=Temp1_2;
	Temp2_6=Temp1_1;
	Temp2_7=Temp1_0;
	Temp1=Temp2;
	Temp2=0xFF;
	Temp2_7=Temp1_7;					
	Temp2_5=Temp1_6;
	Temp2_3=Temp1_5;
	Temp2_1=Temp1_4;
	ID2=Temp2;							//ID2Ϊȡ���ĵ�4λ
	Temp2=0xFF;
	Temp2_7=Temp1_3;
	Temp2_5=Temp1_2;
	Temp2_3=Temp1_1;
	Temp2_1=Temp1_0;
	ID1=Temp2;							//ID1Ϊȡ���ĸ�4λ
}

/*--------------------------------------------------------------*/
/*--------------------------������������-----------------------*/
/*--------------------------------------------------------------*/
void rom_c(unsigned int addr)                         //EEPROMд���κ�����֮ǰ���뽫��������������addr=ĳһ�����׵�ַ
{	
	ISP_CONTR = 0x80;                                 //��IAP���ܣ������̸ı�EEPROM�����ñ�̲����ȴ�ʱ��
	ISP_CMD   = 0x03;		                          //��EEPROM�������в������� 
	ISP_ADDRL = addr;                                 //ISP/IAP������ַ��8λ	
	ISP_ADDRH = addr>>8;                              //ISP/IAP������ַ��8λ	   
	ISP_TRIG = 0x46;          
	ISP_TRIG = 0xB9;                                  //��д��0x46����д��0xB9������ISP/IAP������Ч 
	_nop_();
	ISP_CONTR=0;                                      //�ر�ISP/IAP
	ISP_CMD=0;                                        //����ģʽ����ISP����
	ISP_TRIG=0;	                                      //�����ISP�йص����⹦�ܼĴ���
}

/*--------------------------------------------------------------*/
/*--------------------��EEPROM��д��һ���ֽ�-------------------*/
/*--------------------------------------------------------------*/
void rom_w(unsigned int addr,unsigned char dat)    //addr=������Ԫ��ַ��dat=��д�������
{
	ISP_CONTR = 0x80;		                           //��IAP���ܣ������̸ı�EEPROM�����ñ�̲����ȴ�ʱ��
	ISP_CMD   = 0x02;	                               //��EEPROM�����ֽڱ��   
	ISP_ADDRL = addr;        
	ISP_ADDRH = addr>>8;      
	ISP_DATA  = dat;          
	ISP_TRIG = 0x46;          
	ISP_TRIG = 0xB9;          
	_nop_();
	ISP_CONTR=0;                                      //�ر�ISP/IAP
	ISP_CMD=0;                                        //����ģʽ����ISP����
	ISP_TRIG=0;	                                      //�����ISP�йص����⹦�ܼĴ���
}
/*--------------------------------------------------------------*/
/*--------------------��EEPROM�ж���һ���ֽ�-------------------*/
/*--------------------------------------------------------------*/
unsigned char rom_r(unsigned int addr)              //addr=������Ԫ��ַ
{   
	unsigned char dat;
	ISP_CONTR = 0x80;		  
	ISP_CMD   = 0x01;                               //��EEPROM�����ֽڶ�����
	ISP_ADDRL = addr;         
	ISP_ADDRH = addr>>8;      
	ISP_TRIG = 0x46;          
	ISP_TRIG = 0xB9;          
	_nop_();
	dat = ISP_DATA;			  
	ISP_CONTR=0;                                      //�ر�ISP/IAP
	ISP_CMD=0;                                        //����ģʽ����ISP����
	ISP_TRIG=0;	                                      //�����ISP�йص����⹦�ܼĴ���		       
	return dat;
}

/*--------------------------------------------------------------*/
/*-------------------�����ò������浽EEPROM��-------------------*/
/*--------------------------------------------------------------*/
void id_Gp_Q_save() 									//ȺID,ģ��ID��������������
{
	unsigned char i;
	rom_c(0x8000);
	for(i=0;i<3;i++)
	{
		rom_w(0x8001+i,ID_GP_Q[i]);
	}
	for(i=0;i<16;i++)
	{
		rom_w(0x8010+i,Analog_Threshold[i]);
	}
	rom_w(0x8000,0xAA);
	id_chang(); 										//�������ú��ٴβ��ת�������»�����Ram������
}
void delete_all_e2prom()
{
	unsigned char i;
	for(i=0;i<30;i++)
	{
		rom_c(0x8200+(i<<9));
	}
}