/******************************************************************
                         TELE_PARSE.H  file

��Ҫ���ܣ��ӿڶ��塢ȫ�ֱ������弰��������

����ʱ�䣺2015.10.31
*******************************************************************/
#ifndef __TELE_PARSE_H__
#define __TELE_PARSE_H__
	
extern unsigned char Key_Num1,Digital_Num1,Analog_Num1,Relay_Num1,Scr_Num1;
extern unsigned char style;									//�������ֳ���ͣ
extern unsigned char Delay_Time1,Delay_Time2,Delay_Time3,Delay_Time4;			//��תǰ��ʱʱ��
extern bit Delay_Flag1,Delay_Flag2,Delay_Flag3,Delay_Flag4;

extern unsigned char tele[10];
extern unsigned char jump_tele[28];


unsigned char jumptele_write();
void tele_parse();
void key_config();
void key_inquire(unsigned int address);
void jump_order(unsigned char JumpNum);
void jump_order2(); 

#endif