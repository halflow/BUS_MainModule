/******************************************************************
                             SCR.H  file

��Ҫ���ܣ��ӿڶ��塢ȫ�ֱ������弰��������

����ʱ�䣺2015.10.31
*******************************************************************/

#ifndef __SCR_H__
#define __SCR_H__

/*--------------------------------------------------------------*/
/*---------------------------ͷ�ļ�-----------------------------*/
/*--------------------------------------------------------------*/
#include <STC89C5xRC.h>

/*--------------------------------------------------------------*/
/*---------------------------�ӿڶ���---------------------------*/
/*--------------------------------------------------------------*/
sbit SCR1=P1^0;                                      //�ɿع�1�������ƶ�
sbit SCR2=P1^1;                                      //�ɿع�2�������ƶ�
/*--------------------------------------------------------------*/

/*--------------------------------------------------------------*/
/*-------------------------ȫ�ֱ�������-------------------------*/
/*--------------------------------------------------------------*/
extern unsigned char SCR_counter;                           //�ɿع���ʱ������
extern unsigned char SCR1_value;                            //�ɿع�1��ʱ��ֵͨ
extern unsigned char SCR2_value;                            //�ɿع�2�ӳٵ�ֵͨ
extern unsigned char SCR1_timer;                            //�ɿع赼1ͨ������ʱ�������
extern unsigned char SCR2_timer;                            //�ɿع赼1ͨ������ʱ�������

extern bit  SCR1_Flag;                                      //�ɿع账����־λ
extern bit  SCR2_Flag;
extern bit  SCR1_status;                                    //�ɿع��1״̬��־λ����־����ķ���
extern bit  SCR2_status;                                    //�ɿع��2״̬��־λ����־����ķ���
extern bit  SCR1_control_flag;                              //�ɿع��1�����־λ
extern bit  SCR2_control_flag;                              //�ɿع��2�����־λ
extern unsigned int SCR_control_counter;                    //�ɿع���������

extern bit Scr_100_Flag;									//�ɿع�100%����״̬������־λ
extern bit Scr_Off_Flag;									//�ɿع�0%����״̬������־λ
extern bit Scr_Check_Flag;									//�ɿع�״̬����־λ
extern bit Scr1_Act_Flag;
extern bit Scr2_Act_Flag;
/*--------------------------------------------------------------*/

/*--------------------------------------------------------------*/
/*---------------------------��������---------------------------*/
/*--------------------------------------------------------------*/
void init_scr();
//void scr_handle();
/*--------------------------------------------------------------*/
#endif