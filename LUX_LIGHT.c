/*****************************************************************
                        LUX_LIGHT.C  file

��Ҫ���ܣ���������նȴ��п��ƺ����Լ���Ӧ����

����ʱ�䣺2015.10.31
*****************************************************************/


#include "LUX_LIGHT.h"
#include "STC89C5xRC.h"
#include <intrins.h>

//#define  SlaveAddress  0x46                                      //ADD���Žӵ�ʱ���ӵ�ַΪ0x46������ӵ�Դ����Ϊ0xB8

bit      Lux_Start_Flag;                                         //���նȴ�����������־λ
bit      Lux_Read_Flag;                                          //���նȴ�������ȡ��־λ
bit      Lux_Flag;                                               //ת��ʱ������־λ

bit      Lux_Check_Flag;										//������־λ

bit		Lux_Low_Flag;											//�͹���ǿ�ȱ�־λ
bit		Lux_High_Flag;											//�͹���ǿ�ȱ�־λ

unsigned int Lux_Value;                                          //���ն�ֵ
unsigned int Lux_Counter;                                        //ת��ʱ�������


/*--------------------------------------------------------------*/
/*-----------------------IIC��ز�������-----------------------*/
/*--------------------------------------------------------------*/

/*------------------IIC��ʼ�ź�--------------------*/
void IIC_start()
{
	Lux_Data=1;
	Lux_Sck=1;
	_nop_();
	_nop_();
	_nop_();
	Lux_Data=0;
	_nop_();
	_nop_();
	_nop_();
	Lux_Sck=0;
	_nop_();
	_nop_();
	_nop_();
}
/*------------------IICֹͣ�ź�--------------------*/
void IIC_stop()
{
	Lux_Data=0;
	Lux_Sck=1;
	_nop_();
	_nop_();
	_nop_();
	Lux_Data=1;
	_nop_();
	_nop_();
	_nop_();
}
/*----------------IICӦ���źŷ���------------------*/
void IIC_sendack(bit ack)
{
	Lux_Data=ack;                                //0ΪӦ��1Ϊ��Ӧ��
	Lux_Sck=1;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	Lux_Sck=0;
	_nop_();
	_nop_();
	_nop_();
}
/*----------------IICӦ���źŽ���------------------*/
bit IIC_recvack()
{
	Lux_Sck=1;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	CY=Lux_Data;
	Lux_Sck=0;
	_nop_();
	_nop_();
	_nop_();
	
	return CY;
}
/*---------------��IIC����һ�ֽ�����---------------*/
void IIC_sendbyte(unsigned char dat)
{
	unsigned char i;
	
	for(i=0;i<8;i++)
	{
		dat<<=1;
		Lux_Data=CY;
		Lux_Sck=1;
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		Lux_Sck=0;
		_nop_();
		_nop_();
		_nop_();
	}
	IIC_recvack();
}
/*---------------��IIC����һ�ֽ�����---------------*/
unsigned char IIC_recvbyte()
{
	unsigned char i;
	unsigned char dat=0;
	
	Lux_Data=1;
	for(i=0;i<8;i++)
	{
		dat<<=1;
		Lux_Sck=1;
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		dat|=Lux_Data;
		Lux_Sck=0;
		_nop_();
		_nop_();
		_nop_();
	}
	return dat;
}


/*--------------------------------------------------------------*/
/*---------------------���նȴ�������ʼ��----------------------*/
/*-------------------------------------------------------------*/
void init_lux()
{
	Lux_Start_Flag=0;
	Lux_Read_Flag=0;
	Lux_Flag=0;
	Lux_Counter=0;
	Lux_Check_Flag=1;
	Lux_Low_Flag=0;
	Lux_High_Flag=0;
}

/*--------------------------------------------------------------*/
/*----------------------�������նȴ�����-----------------------*/
/*--------------------------------------------------------------*/
void start_lux()
{
	Lux_Start_Flag=0;                                       //������նȴ�����������־λ
	
	IIC_start();
	IIC_sendbyte(0x46);                      //Addr���Žӵ�      //�����豸��ַ��0110 011��+д�źţ�0��
	IIC_sendbyte(0x01);                                     //������ͨ������
	IIC_stop();
	
	IIC_start();
	IIC_sendbyte(0x46);
	IIC_sendbyte(0x20);                                     //����һ�θ߷ֱ��ʲ�������
	IIC_stop();
	
	Lux_Flag=1;                         //��ʱ��־λ       //���նȴ���������ʱ�������־λ��λ
}

/*--------------------------------------------------------------*/
/*----------------------��ȡ���նȴ�����-----------------------*/
/*--------------------------------------------------------------*/
void read_lux()
{
	unsigned char j;
	unsigned int k=0;
	
	Lux_Read_Flag=0;                                         //������նȴ�������ȡ��־λ
	
	IIC_start();
	IIC_sendbyte(0x47);                                      //�����豸��ַ��0100 011��+���źţ�1��
	
	j=IIC_recvbyte();                                        //��ȡ�߰�λ����
	IIC_sendack(0);                                          //����0Ӧ�𣬼�����ȡ����
	k=j;
	
	j=IIC_recvbyte();                                        //��ȡ�Ͱ�λ����
	IIC_sendack(1);                                          //����1Ӧ�𣬽������ݶ�ȡ
	Lux_Value=(k<<8)+j;
	
	IIC_stop();                                              //IICֹͣ
	
	Lux_Value=(float)Lux_Value/1.2;                          //׼ȷ�Ĺ��ն�ֵ
	
	//������
	//Lux_Pack_Flag=1;
	//������
//	lux_judge();
}
