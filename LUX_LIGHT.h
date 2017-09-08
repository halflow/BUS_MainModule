/******************************************************************
                         LUX_LIGHT.H  file

��Ҫ���ܣ����նȴ�����ģ����ȫ�ֱ�������������

����ʱ�䣺2015.10.31
*******************************************************************/

#ifndef __LUX_LIGHT_H__
#define __LUX_LIGHT_H__

#include <STC89C5xRC.h>

/*-------------------------ȫ�ֱ�������--------------------------*/
sbit Lux_Sck=P2^0;
sbit Lux_Data=P2^1;

extern bit      Lux_Start_Flag;                                         //���նȴ�����������־λ
extern bit      Lux_Read_Flag;                                          //���նȴ�������ȡ��־λ
extern bit      Lux_Flag;                                               //ת��ʱ������־λ


extern bit      Lux_Check_Flag;

extern bit		Lux_Low_Flag;									//����ǿ�ȼ���־λ
extern bit		Lux_High_Flag;


extern unsigned int Lux_Value;                                          //���ն�ֵ
extern unsigned int Lux_Counter;                                        //ת��ʱ�������
/*--------------------------��������-----------------------------*/
void init_lux();
void start_lux();
void read_lux();
void lux_judge();

#endif