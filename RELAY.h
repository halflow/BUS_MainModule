/******************************************************************
                             RELAY.H  file

主要功能：接口定义、全局变量定义及函数申明

创建时间：2015.10.31
*******************************************************************/

#ifndef __RELAY_H__
#define __RELAY_H__

/*--------------------------------------------------------------*/
/*---------------------------头文件-----------------------------*/
/*--------------------------------------------------------------*/
#include <STC89C5xRC.h>
#include "intrins.h"
/*--------------------------------------------------------------*/
/*---------------------------接口定义---------------------------*/
/*--------------------------------------------------------------*/
sbit STR = P2^7;
sbit DATA= P2^6;
sbit CLK = P2^5;
/*--------------------------------------------------------------*/

/*--------------------------------------------------------------*/
/*-------------------------全局变量定义-------------------------*/
/*--------------------------------------------------------------*/
extern bit Relay_Check_Flag;
extern bit Relay_On_Flag;
extern bit Relay_Off_Flag;
extern bit Relay1_Act_Flag,Relay2_Act_Flag,Relay3_Act_Flag,Relay4_Act_Flag;
extern bit  Relay_Flag;                                      //继电器处理标志位
extern unsigned char Relay_Value;                            //继电器控制值
extern unsigned char Relay_Value1;                           //继电器控制值备份
extern unsigned char Which_Relay;
/*--------------------------------------------------------------*/

/*--------------------------------------------------------------*/
/*---------------------------函数声明---------------------------*/
/*--------------------------------------------------------------*/
void init_relay();
void relay_handle();
/*--------------------------------------------------------------*/
#endif