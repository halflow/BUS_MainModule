/*****************************************************************
                          CONFIG.h  file

��Ҫ���ܣ�����ϵͳ�ؼ������ĺ궨���Թ��ܿ���������ز�������

����ʱ�䣺2015.10.31
*****************************************************************/
#ifndef __CONFIG_H__
#define __CONFIG_H__ 
/*--------------------------------------------------------------*/
/*-----------------�ɿع�ģ����ز����ĺ궨��-------------------*/
/*--------------------------------------------------------------*/
#define SCR_TOP_THRESHOLD  80                   //�ɿع������ֵ���ߣ�100Ϊȫ��
#define SCR_BOTTOM_THRESHOLD  05                //�ɿع������ֵ���ߣ�0Ϊȫ��
#define SCR_CHANGE_RATE  1000                   //1000*100us=0.1s��ÿ0.1s�ɿع�ֵ����1���߼���1
#define SCR_TIGGER_TIME  10                     //�ɿع败��ά��ʱ�䣬10*100us=1ms

/*--------------------------------------------------------------*/
/*------------------����ģ����ز����ĺ궨��--------------------*/
/*--------------------------------------------------------------*/
#define KEY_SHAKE_TIME  500                     //��������ʱ�䣬500*100us=50ms
#define KEY_BOUNDARY_TIME  5000                 //���س��̰�����ʱ�䣬5000*100us=0.5s

/*--------------------------------------------------------------*/
/*-----------------�̵���ģ����ز����ĺ궨��-------------------*/
/*--------------------------------------------------------------*/
#define REWRITE_TIME  10                        //�̵�����д����

/*--------------------------------------------------------------*/
/*--------------���ķ��ͺͽ���ģ����ز����ĺ궨��--------------*/
/*--------------------------------------------------------------*/
#define IDLE_TIME  64                           //�϶����߿��е�ʱ�䣬64*52us��16λ���ݳ��ȣ�������9600��
#define OVER_TIME  32                           //���Ľ��ճ�ʱʱ�䣬32*52us����8λ���ݳ���
#define ACK_TIME   40                           //�ȴ�ȷ�ϱ��ĵ�ʱ�䣬40*52us����15λ���ݳ���

/*--------------------------------------------------------------*/
/*-----------------���Ĺ���ģ����ز����ĺ궨��-----------------*/
/*--------------------------------------------------------------*/
#define QUEUE_LENGTH  60                        //���ķ��ͻ������ͽ��ܻ������Ķ��г��ȣ�40Byte

/*--------------------------------------------------------------*/
/*--------------------------ϵͳ��������-----------------------*/
/*--------------------------------------------------------------*/
//#define ID  05                                   //��ģ��ID��ַ
#define ID rom_r(0x8002)

extern unsigned char ID1;                       //����IDת�����м����1
extern unsigned char ID2;                       //����IDת�����м����2
extern unsigned char bdata Temp1;               //����λ������м����1
extern unsigned char bdata Temp2;               //����λ������м����2

extern unsigned char Write_Cache[192];

extern unsigned char ID_GP_Q[3];
extern unsigned char Analog_Threshold[16];
extern unsigned char Sound_Delay[4];


extern  bit Temp1_0;                            //λ��������
extern	bit Temp1_1;
extern	bit Temp1_2;
extern	bit Temp1_3;
extern	bit Temp1_4;
extern	bit Temp1_5;
extern	bit Temp1_6;
extern	bit Temp1_7;
extern	bit Temp2_0;
extern	bit Temp2_1;
extern	bit Temp2_2;
extern	bit Temp2_3;
extern	bit Temp2_4;
extern	bit Temp2_5;
extern	bit Temp2_6;
extern	bit Temp2_7;

/*--------------------------------------------------------------*/
extern bit  Sound_Check_Flag;
extern bit  Sound_Pack_Flag;
extern bit Sound_Delay1_Flag;
extern bit  Sound_Pack2_Flag;
extern unsigned int Sound_Sensor_Counter;
extern unsigned char Sound_Sensor_Counter1;

extern bit Relay1_Alconfig_Flag,Relay2_Alconfig_Flag,Relay3_Alconfig_Flag,Relay4_Alconfig_Flag;
extern bit Scr1_Alconfig_Flag;
extern bit Scr2_Alconfig_Flag;
/*-------------------------------------------------------------*/
/*---------------------------��������--------------------------*/
/*-------------------------------------------------------------*/
void init_config();
void id_chang();
void rom_c(unsigned int addr);
void rom_w(unsigned int addr,unsigned char dat);
unsigned char rom_r(unsigned int addr);
void config_save();
void id_Gp_Q_save();
void delete_all_e2prom();
#endif