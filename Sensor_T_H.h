/******************************************************************
                             SENSOR_T_H.H  file

��Ҫ���ܣ���ʪ�ȴ�����ģ����ȫ�ֱ�������������

����ʱ�䣺2015.10.31
*******************************************************************/

#ifndef __SENSOR_T_H_H__
#define __SENSOR_T_H_H__

#include <STC89C5xRC.h>

/*-------------------------ȫ�ֱ�������--------------------------*/

sbit T_H_Sck=P1^6;                                                      //��ʪ�ȴ�����IICͨ��ʱ���ź�
sbit T_H_Data=P1^7;                                                  //��ʪ�ȴ�����IICͨ�������ź�

extern bit      Sensor_T_H_Flag;                                        //��ʪ�ȴ�����������־λ
extern bit      Sensor_T_H_Flag1;                                       //��ʪ�ȴ�������ȡ��־λ
extern bit      T_Or_H;                                                 //0Ϊ�¶Ȳ�����1Ϊʪ�Ȳ���


extern float Temperature;                                               //�¶Ȳ���ֵ��-40--123.8(���϶�)
extern float Humidity;                                                  //ʪ�Ȳ���ֵ��0--100��%RH��
extern unsigned int Sensor_T_H_Counter;                                 //��ʪ�ȴ�������������ÿ��4s����һ���¶Ȳ�����һ��ʪ�Ȳ���


/*--------------------------��������-----------------------------*/

void init_sensor_t_h();
void star_sensor_t_h();
void read_sensor_t_h();

#endif