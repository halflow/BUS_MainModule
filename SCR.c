/*****************************************************************
                             SCR.C  file

��Ҫ���ܣ�����ɿع�ģ��Ŀ��Ƽ���ʼ��

����ʱ�䣺2015.10.31
*****************************************************************/
/*--------------------------------------------------------------*/
/*---------------------------ͷ�ļ�-----------------------------*/
/*--------------------------------------------------------------*/
#include <STC89C5xRC.h>
#include "SCR.h"
/*--------------------------------------------------------------*/



/*--------------------------------------------------------------*/
/*-------------------------ȫ�ֱ�������-------------------------*/
/*--------------------------------------------------------------*/
unsigned char SCR_counter;                           //�ɿع���ʱ������
unsigned char SCR1_value;                            //�ɿع�1��ʱ��ֵͨ,����ʵ�ʵ�����ֵ������ֵΪ100-value
unsigned char SCR2_value;                            //�ɿع�2�ӳٵ�ֵͨ
unsigned char SCR1_timer;                            //�ɿع�1��ͨ������ʱ�������
unsigned char SCR2_timer;                            //�ɿع�2��ͨ������ʱ�������

bit  SCR1_Flag;                                      //�ɿع��1״̬�ı��־λ
bit  SCR2_Flag;                                      //�ɿع��2״̬�ı��־λ
bit  SCR1_status;                                    //�ɿع��1״̬��־λ����־����ķ���
bit  SCR2_status;                                    //�ɿع��2״̬��־λ����־����ķ���
bit  SCR1_control_flag;                              //�ɿع��1�����־λ
bit  SCR2_control_flag;                              //�ɿع��2�����־λ
unsigned int SCR_control_counter;                    //�ɿع���������

bit Scr_100_Flag;									//�ɿع�100%����״̬������־λ
bit Scr_Off_Flag;									//�ɿع�0%����״̬������־λ
bit Scr_Check_Flag;									//�ɿع�״̬����־λ
bit Scr1_Act_Flag;									//�ɿع����������־λ
bit Scr2_Act_Flag;
/*--------------------------------------------------------------*/
/*--------------------------------------------------------------*/
/*-------------------------�ɿع��ʼ��------------------------*/
/*--------------------------------------------------------------*/

void init_scr()
{
	SCR_counter=0;
	SCR1_value=0xF0;
	SCR2_value=0xF0;
	SCR1_timer=0;
	SCR2_timer=0;
	
	SCR1_Flag=0;
	SCR2_Flag=0;
	SCR1_status=0;
	SCR2_status=0;
	SCR1_control_flag=0;
	SCR2_control_flag=0;
	SCR_control_counter=0;
	
	Scr_Check_Flag=1;
	
	IE1=0;                                             //���ж�֮ǰ�����һ���жϱ�־λ
	EX1=1;
	IT1=1;                                             //�ⲿ�ж�����Ϊ�����ش���ģʽ
}
/*--------------------------------------------------------------*/
/*--------------------------------------------------------------*/
/*-------------------------�ⲿ�ж�1����- ----------------------*/
/*             ���ܣ��������·�����ж�                       */
/*--------------------------------------------------------------*/
void interrupt_INT1() interrupt 2                    //�ⲿ�ж�1���жϺ�Ϊ2
{
	TH2=0xFF;TL2=0x0A;                                 //����У׼������2,��ֹ�ƹⶶ��
	SCR_counter=0;                                     //����SCR������
	TF2=0;                                             //��ռ�����2���жϱ�־λ
}
/*--------------------------------------------------------------*/

/*--------------------------------------------------------------*/
/*------------------------�ɿع账������------------------------*/
/*--------------------------------------------------------------*/
//void scr_handle()
//{
	
//}