/******************************************************************
                         TELE_PACK.H  file

��Ҫ���ܣ��ӿڶ��塢ȫ�ֱ������弰��������
����ʱ�䣺2015.10.31
*******************************************************************/
/*--------------------------------------------------------------*/
/*-------------------------ȫ�ֱ�������-------------------------*/
/*--------------------------------------------------------------*/
#ifndef __TELE_PACK_H__
#define __TELE_PACK_H__



void tele_pack_key();
void tele_pack_relayval();
void tele_pack_relay();
void tele_pack_scrval();
void tele_pack_scr1();
void tele_pack_scr2();
void tele_pack_id();
void tele_pack_group();
void config_success();

void tele_pack_Module_Contain_Group();


void tele_pack_shortconfig(unsigned int address);				//���ж�ָ���з���
void tele_pack_stopconfig();

void tele_pack_sound();
void tele_pack_temperature();
void tele_pack_humidity();
void tele_pack_luxvalue();

void tele_pack_lux();

void order(unsigned int address);
void long_order();
void stop_order();

#endif