/******************************************************************
                             SCR.H  file

主要功能：接口定义、全局变量定义及函数申明

创建时间：2015.10.31
*******************************************************************/

#ifndef __SCR_H__
#define __SCR_H__

/*--------------------------------------------------------------*/
/*---------------------------头文件-----------------------------*/
/*--------------------------------------------------------------*/
#include <STC89C5xRC.h>

/*--------------------------------------------------------------*/
/*---------------------------接口定义---------------------------*/
/*--------------------------------------------------------------*/
sbit SCR1=P1^0;                                      //可控硅1触发控制端
sbit SCR2=P1^1;                                      //可控硅2触发控制端
/*--------------------------------------------------------------*/

/*--------------------------------------------------------------*/
/*-------------------------全局变量定义-------------------------*/
/*--------------------------------------------------------------*/
extern unsigned char SCR_counter;                           //可控硅延时计数器
extern unsigned char SCR1_value;                            //可控硅1延时导通值
extern unsigned char SCR2_value;                            //可控硅2延迟导通值
extern unsigned char SCR1_timer;                            //可控硅导1通高脉冲时间计数器
extern unsigned char SCR2_timer;                            //可控硅导1通高脉冲时间计数器

extern bit  SCR1_Flag;                                      //可控硅处理标志位
extern bit  SCR2_Flag;
extern bit  SCR1_status;                                    //可控硅口1状态标志位，标志调光的方向
extern bit  SCR2_status;                                    //可控硅口2状态标志位，标志调光的方向
extern bit  SCR1_control_flag;                              //可控硅口1调光标志位
extern bit  SCR2_control_flag;                              //可控硅口2调光标志位
extern unsigned int SCR_control_counter;                    //可控硅调光计数器

extern bit Scr_100_Flag;									//可控硅100%亮度状态触发标志位
extern bit Scr_Off_Flag;									//可控硅0%亮度状态触发标志位
extern bit Scr_Check_Flag;									//可控硅状态检测标志位
extern bit Scr1_Act_Flag;
extern bit Scr2_Act_Flag;
/*--------------------------------------------------------------*/

/*--------------------------------------------------------------*/
/*---------------------------函数声明---------------------------*/
/*--------------------------------------------------------------*/
void init_scr();
//void scr_handle();
/*--------------------------------------------------------------*/
#endif