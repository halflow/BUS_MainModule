/*****************************************************************
                        TELE_PARSE.c  file

��Ҫ���ܣ����ݸ�Ӧ��������߽��յı���������װ����

����ʱ�䣺2015.10.31
*****************************************************************/
/*--------------------------------------------------------------*/
/*----------------------------ͷ�ļ�----------------------------*/
/*--------------------------------------------------------------*/
#include "TELE_PARSE.h"
#include "TELE_MANAGE.h"
#include "CONFIG.h"
#include "RELAY.h"
#include "SCR.h"
#include "TELE_T_R.h"
#include "TELE_PACK.h"
#include "SENSOR_T_H.h"
#include "LUX_LIGHT.h"
#include "CONTROL.h"

/*--------------------------------------------------------------*/
/*--------------------------���Ľ�������-----------------------*/
/*--------------------------------------------------------------*/
unsigned char tele[10];            					//���ڴ�Ŵӽ��ջ��������ȡ���ı���
unsigned char tele_backup[10];						//������ʱ��תָ���
unsigned char tele_backup2[10];						//���ڷ���ʱ��תָ���
unsigned char jump_tele[28]={0};
unsigned char Key_Num1,Digital_Num1,Analog_Num1,Relay_Num1,Scr_Num1;
unsigned int addr;
unsigned char style;								//�������ֳ���ͣ
unsigned char Delay_Time1,Delay_Time2,Delay_Time3,Delay_Time4;							//��תǰ��ʱʱ��
unsigned char Which_One;
bit Delay_Flag1,Delay_Flag2,Delay_Flag3,Delay_Flag4;
unsigned char temper;
void tele_parse()
{
	unsigned char i,Key_Num,Digital_Num,Analog_Num,Relay_Num,Scr_Num;
	unsigned char k;									//ȡ�����ĵĸ���
	Tele_Handle_R=0;                                  	//��ս��ջ��������Ĵ����־λ
	Tele_Cheak_R=0;                                   	//��ͣ���Ľ��ջ�����м��

	k=read_tele_r(tele);								//�����õĺ�������date[]���б���ȡ��������tele[]
	
	/*------------------------*////ģ�����//*-------------------------------------*//
	if(Module_Operate_Flag)
	{	
		Module_Operate_Flag=0;
		 /*-----------------------�������ģ�ָ���---------------------------*/
		if((tele[2]&0xC0)==0x00) //�����ж�֡                   
		{
			if((tele[3]&0xC0)==0x00)								//�ж�Ϊ����תָ��
			{
				//////�̵�������ָ��		
				if((tele[4]&0x0F)==0x00)                      //�̵����ڿ���
				{
					if(rom_r(0xA801)!=0xff)						//�̵���1״̬�����仯�ж��Ƿ��Ѿ����ò�����Ҫ����
						Relay1_Alconfig_Flag=1;					//��ʾ�̵���1���������
					if(rom_r(0xAA01)!=0xff)
						Relay2_Alconfig_Flag=1;					//��ʾ�̵���1���������
					if(rom_r(0xAC01)!=0xff)
						Relay3_Alconfig_Flag=1;					//��ʾ�̵���1���������
					if(rom_r(0xAE01)!=0xff)
						Relay4_Alconfig_Flag=1;					//��ʾ�̵���1���������					
					switch(tele[5]&0x03)                          //���̵�����1��������
					{										   
						case 0x00:	Relay_Value=Relay_Value&0xFE;   //�̵�����1��
												break;
						case 0x01:	Relay_Value=Relay_Value|0x01;   //�̵�����1��
												break;
						case 0x02:	Relay_Value=Relay_Value^0x01;   //�̵�����1״̬�л�
												break;
						default:    break;                          //�̵�����1�����κθı�
					}
					
					switch(tele[5]&0x0C)                          //���̵�����2��������
					{
						case 0x00:	Relay_Value=Relay_Value&0xFD;   //�̵�����2��
												break;
						case 0x04:	Relay_Value=Relay_Value|0x02;   //�̵�����2��
												break;
						case 0x08:	Relay_Value=Relay_Value^0x02;   //�̵�����2״̬�л�
												break;
						default:    break;                          //�̵�����2�����κθı�
					}
					
					switch(tele[5]&0x30)                          //���̵�����3��������
					{
						case 0x00:	Relay_Value=Relay_Value&0xFB;   //�̵�����3��
												break;
						case 0x10:	Relay_Value=Relay_Value|0x04;   //�̵�����3��
												break;
						case 0x20:	Relay_Value=Relay_Value^0x04;   //�̵�����3״̬�л�
												break;
						default:    break;                          //�̵�����3�����κθı�
					}
					
					switch(tele[5]&0xC0)                          //���̵�����4��������
					{
						case 0x00:	Relay_Value=Relay_Value&0xF7;   //�̵�����4��
												break;
						case 0x40:	Relay_Value=Relay_Value|0x08;   //�̵�����4��
												break;
						case 0x80:	Relay_Value=Relay_Value^0x08;   //�̵�����4״̬�л�
												break;
						default:    break;                          //�̵�����4�����κθı�
					}
					
					switch(tele[6]&0x03)                          //���̵�����5��������
					{
						case 0x00:	Relay_Value=Relay_Value&0xEF;   //�̵�����5��
												break;
						case 0x01:	Relay_Value=Relay_Value|0x10;   //�̵�����5��
												break;
						case 0x02:	Relay_Value=Relay_Value^0x10;   //�̵�����5״̬�л�
												break;
						default:    break;                          //�̵�����5�����κθı�
					}
					
					switch(tele[6]&0x0C)                          //���̵�����6��������
					{
						case 0x00:	Relay_Value=Relay_Value&0xDF;   //�̵�����6��
												break;
						case 0x04:	Relay_Value=Relay_Value|0x20;   //�̵�����6��
												break;
						case 0x08:	Relay_Value=Relay_Value^0x20;   //�̵�����6״̬�л�
												break;
						default:    break;                          //�̵�����6�����κθı�
					}
					
					switch(tele[6]&0x30)                          //���̵�����7��������
					{
						case 0x00:	Relay_Value=Relay_Value&0xBF;   //�̵�����7��
												break;
						case 0x10:	Relay_Value=Relay_Value|0x40;   //�̵�����7��
												break;
						case 0x20:	Relay_Value=Relay_Value^0x40;   //�̵�����7״̬�л�
												break;
						default:    break;                          //�̵�����7�����κθı�
					}
					
					switch(tele[6]&0xC0)                          //���̵�����8��������
					{
						case 0x00:	Relay_Value=Relay_Value&0x7F;   //�̵�����8��
												break;
						case 0x40:	Relay_Value=Relay_Value|0x80;   //�̵�����8��
												break;
						case 0x80:	Relay_Value=Relay_Value^0x80;   //�̵�����8״̬�л�
												break;
						default:    break;                          //�̵�����8�����κθı�
					}
					
					relay_handle();                              /*�̵������Ľ�����ϣ����д���*/
				}
				//////��ؿڿ���ָ��
				else if((tele[4]&0x0F)==0x01)                   //��ؿ�1����ָ��
				{
					if(rom_r(0xB801)!=0xff)						//�ɿع�״̬�����仯�ж��Ƿ���Ҫ����
						Scr1_Alconfig_Flag=1;					//��ʾ�ɿع�1������
					switch(tele[4]&0x70)
					{
						case 0x00:  SCR1_value=tele[5];             //bit6-bit4=000//��ؿ�1ֵ�趨
												SCR1_Flag=1;		//��װ�������ı�־λ��1
												break;					
						case 0x10:	if(SCR1_value==0xF0)            //��ؿ�1״̬�л�
										SCR1_value=1;
									else
										SCR1_value=0xF0;								
												SCR1_Flag=1;       //�ɿع��1������־λ��1---->>������
												break;
					  
						case 0x20:	SCR1_control_flag=1;            //��ؿ�1�����Լ�
												SCR1_Flag=1;
												break;
					    case 0x40:  SCR1_control_flag=1;            //��ؿ�1������Xֵ
									
								  				break;
						case 0x50:	SCR1_control_flag=0;            //��ؿ�1�����Լ�ֹͣ
									SCR_control_counter=0;
									SCR1_status=!SCR1_status;
												SCR1_Flag=1;
												break;											
						default:		break;
					}
				}
				else if((tele[4]&0x0F)==0x02)                   //��ؿ�2����ָ��
				{
					if(rom_r(0xBA01)!=0xff)
						Scr2_Alconfig_Flag=1;					//��ʾ�ɿع�2������
					switch(tele[4]&0x70)
					{
						case 0x00:  SCR2_value=tele[5];             //��ؿ�2ֵ�趨
												SCR2_Flag=1;
												break;
						
						case 0x10:	if(SCR2_value==0xF0)            //��ؿ�2״̬�л�
										SCR2_value=1;
									else
										SCR2_value=0xF0;
												SCR2_Flag=1;
												break;
					  
						case 0x20:	SCR2_control_flag=1;            //��ؿ�2�����Լ�
												SCR2_Flag=1;
												break;
					  
						case 0x50:	SCR2_control_flag=0;            //��ؿ�2�����Լ�ֹͣ
									SCR_control_counter=0;
									SCR2_status=!SCR2_status;
												SCR2_Flag=1;
												break;											
						default:break;
					}
				}
			}
			else if((tele[3]&0x80)==0x80)					//��Ϊ��תָ��
			{
				if((tele[3]&0x40)==0x40)					//����תָ�������ʱ
				{
					led0=~led0;
					for(i=0;i<10;i++)
					{
						tele_backup[i]=tele[i];				//�����Ľ��б��ݣ�Ϊ�˷�ֹ����תָ���ƻ���תָ�������
					}
					Which_One=jumptele_write();				//�жϻ���ռ��Ƿ���������д�뻺��			
					switch(Which_One)						//�����˺������ѽ�tele_backup��д��jump_tele����
					{
						case 1:
							switch(jump_tele[6]&0xC0)							//�ж���ʱ��λ
							{
								case 0x00:Delay_Time1=(jump_tele[6]&0x0F);break;	//ȡ����ʱʱ��
								case 0x40:break;
								default:break;
							}
							Delay_Flag1=1;
							break;
						case 2:	
							switch(jump_tele[13]&0xC0)							//�ж���ʱ��λ
							{
								case 0x00:Delay_Time2=(jump_tele[13]&0x0F);break;	//ȡ����ʱʱ��
								case 0x40:break;
								default:break;
							}
							Delay_Flag2=1;
							break;
						case 3:	
							switch(jump_tele[20]&0xC0)							//�ж���ʱ��λ
							{
								case 0x00:Delay_Time3=(jump_tele[20]&0x0F);break;	//ȡ����ʱʱ��
								case 0x40:break;
								default:break;
							}
							Delay_Flag3=1;
							break;
						case 4:							
							switch(jump_tele[26]&0xC0)							//�ж���ʱ��λ
							{
								case 0x00:Delay_Time4=(jump_tele[26]&0x0F);break;	//ȡ����ʱʱ��
								case 0x40:break;
								default:break;
							}
							Delay_Flag4=1;
							break;
						default:break;
					}
				}
				else										//����תָ�������ʱ
				{
					led1=~led1;
					for(i=0;i<10;i++)
					{
						tele_backup2[i]=tele[i];			//�����Ľ��б��ݣ�Ϊ�˷�ֹ����תָ���ƻ���תָ�������
					}
					jump_order2();
				}
			}
		}
		 /*----------------��������Ϊ���ñ���----------------------------*///tele[2]���ԣ�tele[3]����֡1��tele[4]����֡2
		else if((tele[2]&0xC0)==0x40)            			//�жϱ������� �������ñ���
		{
			if((tele[3]&0xF0)==0x00)								/*--------����ģ������------------*/
			{				
				switch(tele[3]&0x0F)
				{
					case 0x00:
					{
						switch(tele[4]&0xF0)
						{
							case 0x00: 	ID_GP_Q[0]=tele[5];			//ȺID
										break;
							case 0x10:	ID_GP_Q[1]=tele[5];			//ģ��ID 
										break;
							case 0x20:	ID_GP_Q[2]=tele[5];			//��ID							 
										break;		
							default: break;					
						}
						id_Gp_Q_save();
						config_success();
					}break;
					case 0x01:	
					{
						switch(tele[4])
						{
							case 0x00:delete_all_e2prom();
								break;
							default:break;
						}
						config_success();
					}break;
					default:break;					
				}
		   }		
			if((tele[3]&0xF0)==0x30)							//ģ����������Ϣ			
			{			
				switch(tele[3]&0x0F)						/*-------����3·ģ�������е���ֵ------*/
				{
					case 0x00:
							switch(tele[4])
							{
								case 0x50:Analog_Threshold[0]=tele[5];		//��һ·����ֵ
											break;
								case 0x60:Analog_Threshold[1]=tele[5];		//��һ·����ֵ
											break;
								default:    break;
								
							}
							break;
					case 0x01:
							switch(tele[4])
							{
								case 0x50:Analog_Threshold[2]=tele[5];		//�ڶ�·����ֵ
											break;
								case 0x60:Analog_Threshold[3]=tele[5];		//�ڶ�·����ֵ
											break;
								default:    break;								
							}					
							break;
					case 0x02:
							switch(tele[4])
							{
								case 0x50:Analog_Threshold[4]=tele[5];		//����·����ֵ	
											break;
								case 0x60:Analog_Threshold[5]=tele[5];		//����·����ֵ
											break;
								default:    break;
							}					
							break;
					default:break;
				}
				id_Gp_Q_save();
				config_success();

			}				
			if((tele[3]&0xF0)==0x10)				/*-----����8·�������ذ�--------*/
			{
				Key_Num=tele[3]&0x0F;						//��ȡ���õ���·����
				for(i=0;i<191;i++)							//����ǰ������Ϣ���浽RAM
				{
					Write_Cache[i]=rom_r(0x8200+(Key_Num<<9)+i);		//�൱��key_num*512
				}
				switch(Key_Num)//tele[3]&0x0F
				{
					case 0x00:key_config();								//��һ·����						
							break;
					case 0x01:key_config();								//�ڶ�·����							
							break;
					case 0x02:key_config();								//����·����
							break;
					case 0x03:key_config();								//����·����
							break;
					case 0x04:key_config();								//����·����
							break;
					case 0x05:key_config();								//����·����//ʹ����
							break;
					case 0x06:key_config();								//����·����//ʹ����
							break;
					case 0x07:key_config();								//�ڰ�·����//ʹ����
							break;
					default:break;
				}
				rom_c(0x8200+(Key_Num<<9));				//�Ȳ�����Ӧ������
				for(i=0;i<191;i++)							//�����浽RAM���޸ĵ�����д��EEPROM
				{
					rom_w((0x8200+(Key_Num<<9)+i),Write_Cache[i]);
				}
				config_success();
			}
	        if((tele[3]&0xF0)==0x20)					/*-------����8·�����������ഫ����---------*/
			{
				for(i=0;i<191;i++)
					Write_Cache[i]=rom_r(0x9200+i);
				switch(tele[3]&0x0F)							//��һ·������
				{			
					case 0x00: key_config();
							   	break;
					default:break;
				}
				rom_c(0x9200);
				for(i=0;i<191;i++)
					rom_w(0x9200+i,Write_Cache[i]);
				config_success();
			}   
			if((tele[3]&0xF0)==0x30)					/*-------����3·ģ����������---------*/
			{
				for(i=0;i<191;i++)
					Write_Cache[i]=rom_r(0xA200+i);
				switch(tele[3]&0x0F)							//��1·������
				{
					case 0x00: key_config();
								break;
					default:break;
				}
				rom_c(0xA200);
				for(i=0;i<191;i++)
					rom_w(0xA200+i,Write_Cache[i]);	
				config_success();			
			}  
			if((tele[3]&0xF0)==0x40)					/*-----����8·�̵���״̬���----------*/
			{
				Relay_Num=tele[3]&0x0F;
				for(i=0;i<191;i++)
					Write_Cache[i]=rom_r(0xA800+(Relay_Num<<9)+i);
				switch(tele[3]&0x0F)							//��1·�̵���/////��������
				{
					case 0x00: key_config();
								break;
					case 0x01: key_config();
								break;
					case 0x02: key_config();
								break;
					case 0x03: key_config();
								break;
					default:break;
				}
				rom_c(0xA800+(Relay_Num<<9));
//				rom_w(0x6800,0xAA);								//��һ·�̵������ñ�־λ
				for(i=0;i<191;i++)
					rom_w(0xA800+(Relay_Num<<9)+i,Write_Cache[i]);
				config_success();	
			}
			if((tele[3]&0xF0)==0x50)					/*--------����2·�ɿع�״̬���-------*/
			{
				Scr_Num=(tele[3]&0x0F);
				for(i=0;i<191;i++)
					Write_Cache[i]=rom_r(0xB800+(Scr_Num<<9)+i);
				switch(Scr_Num)//tele[3]&0x0F							
				{
					case 0x00: key_config();					//��1·�ɿع�����
								break;
					case 0x01: key_config();					//�ڶ�·�ɿع�����
								break;
					default:break;
				}
				rom_c(0xB800+(Scr_Num<<9));
				for(i=0;i<191;i++)
					rom_w(0xB800+(Scr_Num<<9)+i,Write_Cache[i]);
				config_success();	
			}			                    			
		}
		 /*---------------------------��������Ϊ��������------------------------------------*/
		else if((tele[2]&0xC0)==0x80)                      
		{
			//��ģ�鲻����յ��������ģ�ֻ������ģ�����շ�������
		}
		/*----------------------------��������Ϊ��ѯ����-----------------------------------*/
		else if((tele[2]&0xC0)==0xC0)                       
		{				
				switch(tele[3]&0xF0)							//������ĵ�һ֡����λ����ѯ����
				{			
					case 0x00:										/*------��ѯģ������-------*/
						switch(tele[3]&0x0F)
						{
							case 0x00: tele_pack_id();break;					//ģ��ID��ѯ
							case 0x01: tele_pack_Module_Contain_Group();break;	//ģ�����ѯ
							default: break;
						}
						break;	
					case 0x10:										/*--------��ѯ��������-----*/
						Key_Num=tele[3]&0x0F;
						Key_Num1=tele[3];
						Digital_Num1=0;Analog_Num1=0;Relay_Num1=0;Scr_Num1=0;
						addr=0x8200+(Key_Num<<9);

						switch(Key_Num)//tele[3]&0x0F							
						{
							case 0x00: 	key_inquire(addr);								//��1·���ز�ѯ									
									break;
							case 0x01:	key_inquire(addr);								//��2·���ز�ѯ									
									break;
							case 0x02:	key_inquire(addr);								//��3·���ز�ѯ
									break;
							case 0x03:	key_inquire(addr);								//��4·���ز�ѯ	
									break;
							case 0x04:	key_inquire(addr);								//��5·���ز�ѯ
									break;
							case 0x05: 	key_inquire(addr);								//��6·���ز�ѯ
									break;
							case 0x06:	key_inquire(addr);								//��7·���ز�ѯ
									break;
							case 0x07:	key_inquire(addr);								//��8·���ز�ѯ
									break;
							default: break;
						}
						break;
					case 0x20:									/*-----��ѯ����������������----*/
						Digital_Num=tele[3]&0x0F;				//�жϵڼ�·
						Digital_Num1=tele[3];
						Key_Num1=0;Analog_Num1=0;Relay_Num1=0;Scr_Num1=0;
						addr=0x9200+(Digital_Num<<9);

						switch(Digital_Num)//tele[3]&0x0F				
						{
							case 0x00:						//��һ·������������
								switch(tele[4]&0xF0)
								{
									case 0x00:key_inquire(addr);break;		//��������
									case 0x10:key_inquire(addr);break;		//������ʧ
									default: break;
								}break;
							case 0x01:						//�ڶ�·������������
								switch(tele[4]&0xF0)
								{
									case 0x00:key_inquire(addr);break;
									case 0x10:key_inquire(addr);break;
									default: break;
								}break;
							default: break;
						}
						break;
					case 0x30: 									/*-----��ѯģ��������������----*/
							Analog_Num=tele[3]&0x0F;
							Analog_Num1=tele[3];
							Key_Num1=0;Digital_Num1=0;Relay_Num1=0;Scr_Num1=0;
							addr=0xA200+(Analog_Num<<9);
							
							switch(Analog_Num)//tele[3]&0x0F
							{
								case 0x00:
										switch(tele[4])
										{
											case 0x00:key_inquire(addr);					//����ֵ����������Ϣ��ѯ
												break;
											case 0x10:key_inquire(addr);					//����ֵ������Ϣ��ѯ
												break;
											case 0x40:									//������ֵ������Ϣ��ѯ
												break;
											default: break;
										}
									break;
							}
							break;							
					case 0x40:								/*-----��ѯ�̵������״̬����-------*/
							Relay_Num=tele[3]&0x0F;
							Relay_Num1=tele[3];
							Key_Num1=0;Digital_Num1=0;Analog_Num1=0;Scr_Num1=0;
							addr=0xA800+(Relay_Num<<9);
						
							switch(Relay_Num)//tele[3]&0x0F
							{
								case 0x00:					//��һ·�̵������ò�ѯ
										switch(tele[4])
										{
											case 0x00:key_inquire(addr);break;			//�̵����������ò�ѯ
											case 0x01:key_inquire(addr);break;			//�̵����ر����ò�ѯ
											default:break;
										}
										break;
								case 0x01:					//�ڶ�·�̵������ò�ѯ
										switch(tele[4])
										{
											case 0x00:key_inquire(addr);break;			//�̵����������ò�ѯ
											case 0x10:key_inquire(addr);break;			//�̵����ر����ò�ѯ
											default:break;
										}break;
								case 0x02:					//����·�̵������ò�ѯ
										switch(tele[4])
										{
											case 0x00:key_inquire(addr);break;			//�̵����������ò�ѯ
											case 0x10:key_inquire(addr);break;			//�̵����ر����ò�ѯ
											default:break;
										}break;	
								case 0x03:					//����·�̵������ò�ѯ
										switch(tele[4])
										{
											case 0x00:key_inquire(addr);break;			//�̵����������ò�ѯ
											case 0x10:key_inquire(addr);break;			//�̵����ر����ò�ѯ
											default:break;
										}break;								
							}break;
					case 0x50:									/*------��ѯ�ɿع�״̬�������--------*/
							Scr_Num=tele[3]&0x0F;
							Scr_Num1=tele[3];
							Key_Num1=0;Digital_Num1=0;Analog_Num1=0;Relay_Num1=0;
							addr=0xB800+(Scr_Num<<9);
			
							switch(Scr_Num)//tele[3]&0x0f
							{
								case 0x00:						//��һ·�ɿع����ò�ѯ
										switch(tele[4])
										{
											case 0x00:key_inquire(addr);break;	//��ѯ����0%������Ϣ
											case 0x10:key_inquire(addr);break;
											case 0x20:key_inquire(addr);break;	//��ѯ����100%������Ϣ
											default:break;
										}break;
								case 0x01:						//�ڶ�·�ɿع����ò�ѯ
										switch(tele[4])
										{
											case 0x00:key_inquire(addr);break;
											case 0x10:key_inquire(addr);break;
											case 0x20:key_inquire(addr);break;
											default:break;
										}break;
							}break;
					case 0x60:									/*------��ѯģ������Ϣ--------*/
							switch(tele[3]&0x0F)
							{
								case 0x00: tele_pack_luxvalue();			//����ǿ����Ϣ
										break;
								case 0x01: tele_pack_temperature();			//�¶�ֵ��װ����
										break;
								case 0x02: tele_pack_humidity();			//ʪ��ֵ��װ����
										break;
								default: break;
							} 
							break;
					case 0x70:	Relay_Flag=1;					/*-------�̵���״̬��ѯ-------*/
										break;
					case 0x80:	SCR1_Flag=1;					/*--------�ɿع�״̬��ѯ------*/											
								SCR2_Flag=1;
									break;
					default: break;
				}			
		}
	}
	/*---------------------------*///�����////*--------------------------------*/
	else if(Group_Operate_Flag)							
	{
		Group_Operate_Flag=0;
		if((tele[2]&0xC0)==0xC0)				//��ѯ����
		{
				switch(tele[3])			
				{
					case 0x00: 
							switch(tele[4])
							{						
							   case 0x00:Group_a=ID_GP_Q[2];
							   			 tele_pack_group();					//��ģ���������Щ����
							  		     break;
								default: break;
							}
							break;
					default :break;					
				}	
		}
		/*-----------------------�������ģ�ָ���---------------------------*/
		if((tele[2]&0xC0)==0x00)                    
		{
			//////�̵�������ָ��		
			if((tele[4]&0x0F)==0x00)                      //�̵����ڿ���
			{
				switch(tele[5]&0x03)                          //���̵�����1��������
				{										   
					case 0x00:	Relay_Value=Relay_Value&0xFE;   //�̵�����1��
											break;
					case 0x01:	Relay_Value=Relay_Value|0x01;   //�̵�����1��
											break;
					case 0x02:	Relay_Value=Relay_Value^0x01;   //�̵�����1״̬�л�
											break;
					default:    break;                          //�̵�����1�����κθı�
				}
				
				switch(tele[5]&0x0C)                          //���̵�����2��������
				{
					case 0x00:	Relay_Value=Relay_Value&0xFD;   //�̵�����2��
											break;
					case 0x04:	Relay_Value=Relay_Value|0x02;   //�̵�����2��
											break;
					case 0x08:	Relay_Value=Relay_Value^0x02;   //�̵�����2״̬�л�
											break;
					default:    break;                          //�̵�����2�����κθı�
				}
				
				switch(tele[5]&0x30)                          //���̵�����3��������
				{
					case 0x00:	Relay_Value=Relay_Value&0xFB;   //�̵�����3��
											break;
					case 0x10:	Relay_Value=Relay_Value|0x04;   //�̵�����3��
											break;
					case 0x20:	Relay_Value=Relay_Value^0x04;   //�̵�����3״̬�л�
											break;
					default:    break;                          //�̵�����3�����κθı�
				}
				
				switch(tele[5]&0xC0)                          //���̵�����4��������
				{
					case 0x00:	Relay_Value=Relay_Value&0xF7;   //�̵�����4��
											break;
					case 0x40:	Relay_Value=Relay_Value|0x08;   //�̵�����4��
											break;
					case 0x80:	Relay_Value=Relay_Value^0x08;   //�̵�����4״̬�л�
											break;
					default:    break;                          //�̵�����4�����κθı�
				}
				
				switch(tele[6]&0x03)                          //���̵�����5��������
				{
					case 0x00:	Relay_Value=Relay_Value&0xEF;   //�̵�����5��
											break;
					case 0x01:	Relay_Value=Relay_Value|0x10;   //�̵�����5��
											break;
					case 0x02:	Relay_Value=Relay_Value^0x10;   //�̵�����5״̬�л�
											break;
					default:    break;                          //�̵�����5�����κθı�
				}
				
				switch(tele[6]&0x0C)                          //���̵�����6��������
				{
					case 0x00:	Relay_Value=Relay_Value&0xDF;   //�̵�����6��
											break;
					case 0x04:	Relay_Value=Relay_Value|0x20;   //�̵�����6��
											break;
					case 0x08:	Relay_Value=Relay_Value^0x20;   //�̵�����6״̬�л�
											break;
					default:    break;                          //�̵�����6�����κθı�
				}
				
				switch(tele[6]&0x30)                          //���̵�����7��������
				{
					case 0x00:	Relay_Value=Relay_Value&0xBF;   //�̵�����7��
											break;
					case 0x10:	Relay_Value=Relay_Value|0x40;   //�̵�����7��
											break;
					case 0x20:	Relay_Value=Relay_Value^0x40;   //�̵�����7״̬�л�
											break;
					default:    break;                          //�̵�����7�����κθı�
				}
				
				switch(tele[6]&0xC0)                          //���̵�����8��������
				{
					case 0x00:	Relay_Value=Relay_Value&0x7F;   //�̵�����8��
											break;
					case 0x40:	Relay_Value=Relay_Value|0x80;   //�̵�����8��
											break;
					case 0x80:	Relay_Value=Relay_Value^0x80;   //�̵�����8״̬�л�
											break;
					default:    break;                          //�̵�����8�����κθı�
				}
				
				relay_handle();                              /*�̵������Ľ�����ϣ����д���*/
			}
			//////��ؿڿ���ָ��
			else if((tele[4]&0x0F)==0x01)                   //��ؿ�1����ָ��
			{
				switch(tele[4]&0x70)
				{
					case 0x00:  SCR1_value=tele[5];             //bit6-bit4=000//��ؿ�1ֵ�趨
											SCR1_Flag=1;		//��װ�������ı�־λ��1
											break;
					
					case 0x10:	if(SCR1_value==0xF0)            //001//��ؿ�1״̬�л�
									SCR1_value=1;
								else
									SCR1_value=0xF0;								
											SCR1_Flag=1;                    //�ɿع��1������־λ��1
											break;
				  
					case 0x20:	SCR1_control_flag=1;            //��ؿ�1�����Լ�
											SCR1_Flag=1;
											break;
				  
					case 0x50:	SCR1_control_flag=0;            //��ؿ�1�����Լ�ֹͣ
								SCR_control_counter=0;
								SCR1_status=!SCR1_status;
											SCR1_Flag=1;
											break;											
					default:		break;
				}
			}
			else if((tele[4]&0x0F)==0x02)                   //��ؿ�2����ָ��
			{
				switch(tele[5]&0x70)
				{
					case 0x00:  SCR2_value=tele[4];             //��ؿ�2ֵ�趨
								SCR2_Flag=1;
											break;
					
					case 0x10:	if(SCR2_value==0xF0)            //��ؿ�2״̬�л�
									SCR2_value=1;
								else
									SCR2_value=0xF0;
								SCR2_Flag=1;
											break;
				  
					case 0x20:	SCR2_control_flag=1;            //��ؿ�2�����Լ�
								SCR2_Flag=1;
											break;
				  
					case 0x50:	SCR2_control_flag=0;            //��ؿ�2�����Լ�ֹͣ
								SCR_control_counter=0;
								SCR2_status=!SCR2_status;
								SCR2_Flag=1;
											break;										
					default:break;
				}
			}
		}
	}
	Tele_Cheak_R=1;                                   //�ָ����Ľ��ջ�����м��
}
/*-------------------------------------------------------------*/
/*------------------����������Ϣ����Ϣ�洢����-----------------*/
/*-------------------------------------------------------------*/
void key_config()									//��������
{
	unsigned char i,j;
	switch(tele[4]&0xF0)
	{
		case 0x00:							//�̰�����
				switch(tele[4]&0x07)
				{
					case 0x00:					
							for(i=0;i<((tele[5]&0x0F)+3);i++)
							{
								Write_Cache[i+1]=tele[5+i];			//Ŀ��1�̰�����֡����
							}				
							break;
					case 0x01:	
							Write_Cache[9]=tele[5];					//Ŀ��1�̰��������ã��ݶ�һ����ʱʱ�䣩
							break;								
					case 0x02:
							for(i=0;i<((tele[5]&0x0F)+3);i++)
							{
								Write_Cache[i+17]=tele[5+i];		//Ŀ��2�̰�����֡����
							}				
							break;
					case 0x03:	
							Write_Cache[25]=tele[5];				//Ŀ��2�̰���������
							break;
					case 0x04:
							for(i=0;i<((tele[5]&0x0F)+3);i++)
							{
								Write_Cache[i+33]=tele[5+i];		//Ŀ��3�̰�����֡����
							}				
							break;
					case 0x05:	
							Write_Cache[41]=tele[5];				//Ŀ��3�̰���������
							break;
					case 0x06:
							for(i=0;i<((tele[5]&0x0F)+3);i++)
							{
								Write_Cache[i+49]=tele[5+i];		//Ŀ��4�̰�����֡����
							}				
							break;
					case 0x07:	
							Write_Cache[57]=tele[5];				//Ŀ��4�̰���������
							break;
					default:break;
				}
				break;
		case 0x10:										//��������
				switch(tele[4]&0x07)
				{
					case 0x00:									
							for(i=0;i<((tele[5]&0x0F)+3);i++)
							{
								Write_Cache[i+65]=tele[5+i];		//Ŀ��1��������֡����
							}				
							break;
					case 0x01:	
							Write_Cache[73]=tele[5];				//Ŀ��1������������
							break;								
					case 0x02:
							for(i=0;i<((tele[5]&0x0F)+3);i++)
							{
								Write_Cache[i+81]=tele[5+i];		//Ŀ��2��������֡����
							}				
							break;
					case 0x03:	
							Write_Cache[89]=tele[5];				//Ŀ��2������������
							break;
					case 0x04:
							for(i=0;i<((tele[5]&0x0F)+3);i++)
							{
								Write_Cache[i+97]=tele[5+i];		//Ŀ��3��������֡����
							}				
							break;
					case 0x05:	
							Write_Cache[105]=tele[5];				//Ŀ��3������������
							break;
					case 0x06:
							for(i=0;i<((tele[5]&0x0F)+3);i++)
							{
								Write_Cache[i+113]=tele[5+i];		//Ŀ��4��������֡����
							}				
							break;
					case 0x07:	
							Write_Cache[121]=tele[5];				//Ŀ��4������������
							break;
					default:break;
				}
				break;
		case 0x20:								//����ֹͣ����
				switch(tele[4]&0x07)
				{
					case 0x00:									
							for(i=0;i<((tele[5]&0x0F)+3);i++)
							{
								Write_Cache[i+129]=tele[5+i];		//Ŀ��1��ͣ������֡����
							}				
							break;
					case 0x01:	
							Write_Cache[137]=tele[5];				//Ŀ��1��ͣ����������
							break;								
					case 0x02:
							for(i=0;i<((tele[5]&0x0F)+3);i++)
							{
								Write_Cache[i+145]=tele[5+i];		//Ŀ��2��ͣ������֡����
							}				
							break;
					case 0x03:	
							Write_Cache[153]=tele[5];				//Ŀ��2��ͣ����������
							break;
					case 0x04:
							for(i=0;i<((tele[5]&0x0F)+3);i++)
							{
								Write_Cache[i+161]=tele[5+i];		//Ŀ��3��ͣ������֡����
							}				
							break;
					case 0x05:	
							Write_Cache[169]=tele[5];				//Ŀ��3��ͣ����������
							break;
					case 0x06:
							for(i=0;i<((tele[5]&0x0F)+3);i++)
							{
								Write_Cache[i+177]=tele[5+i];		//Ŀ��4��ͣ������֡����
							}				
							break;
					case 0x07:	
							Write_Cache[185]=tele[5];				//Ŀ��4��ͣ����������
							break;
					default:break;
				}
				break;
		case 0x30:
				switch(tele[4]&0x07)								//ɾ��Ŀ������
				{
					case 0x00:										//ɾ��Ŀ��1����
							for(j=0;j<3;j++)
							{
								for(i=0;i<16;i++)
								{
									Write_Cache[i+64*j]=0xff;
								}	
							}break;
					case 0x01:										//ɾ��Ŀ��2����
							for(j=0;j<3;j++)
							{
								for(i=0;i<16;i++)
								{
									Write_Cache[16+i+64*j]=0xff;
								}	
							}break;
					case 0x02:										//ɾ��Ŀ��3����
							for(j=0;j<3;j++)
							{
								for(i=0;i<16;i++)
								{
									Write_Cache[32+i+64*j]=0xff;
								}	
							}break;
					case 0x03:										//ɾ��Ŀ��4����
							for(j=0;j<3;j++)
							{
								for(i=0;i<16;i++)
								{
									Write_Cache[48+i+64*j]=0xff;
								}	
							}break;
					default:	break;									
				}
				break;	
		case 0x40:													//ɾ������Ŀ������
				{
					switch(tele[4]&0x0F)
					{
						case 0x00:
								for(i=0;i<192;i++)
								{
									Write_Cache[i]=0xFF;
								}break;
						default:	break;		
					}
				}break;	
		default:	break;										
	}
}
void key_inquire(unsigned int add)
{
	switch(tele[4]&0xF0)
	{
		case 0x00:  style=0x00;
					tele_pack_shortconfig(add);					//��ָ�������ò�ѯ
					break;						
		case 0x10:  style=0x10;
					tele_pack_shortconfig(add+64); 				//��ָ�������ò�ѯ
					break;
		case 0x20:  style=0x20;
					tele_pack_shortconfig(add+128); 			//ָͣ�������ò�ѯ
					break;
//		case 0x30: key_all();  break;							//��ѯ����ָ����(����)
		default:   break;
	}
}
void jump_order(unsigned char JumpNum)									//��ʱ��ʱ�䵽��ִ��
{
	unsigned char tele_backup3[7];
	unsigned char i;
	for(i=0;i<7;i++)
		tele_backup3[i]=jump_tele[JumpNum+i];

	switch(tele_backup3[4]&0xC0)		//ָ���A--------��Ӧ��8·������ָ������
	{
		case 0x40:								//ָ���A�ġ��̡�ָ����
					if(tele_backup3[5]&0x01)			//ָ���Aָ����1
					{Key_Value=0x80;tele_pack_key();}			
					if(tele_backup3[5]&0x02)
					{Key_Value=0x81;tele_pack_key();}
					if(tele_backup3[5]&0x04)			//ָ���Aָ����3
					{Key_Value=0x82;tele_pack_key();}			
					if(tele_backup3[5]&0x08)
					{Key_Value=0x83;tele_pack_key();}
					if(tele_backup3[5]&0x10)			//ָ���Aָ����5
					{Key_Value=0x84;tele_pack_key();}			
					if(tele_backup3[5]&0x20)
					{Key_Value=0x85;tele_pack_key();}
					if(tele_backup3[5]&0x40)			//ָ���Aָ����7
					{Key_Value=0x86;tele_pack_key();}			
					if(tele_backup3[5]&0x80)
					{Key_Value=0x87;tele_pack_key();}																
				break;
		case 0x80:								//ָ���A�ġ�����ָ����
					if(tele_backup3[5]&0x01)			//ָ���Aָ����1
					{Key_Value=0x40;tele_pack_key();}			
					if(tele_backup3[5]&0x02)
					{Key_Value=0x41;tele_pack_key();}
					if(tele_backup[5]&0x04)			//ָ���Aָ����3
					{Key_Value=0x42;tele_pack_key();}			
					if(tele_backup3[5]&0x08)
					{Key_Value=0x43;tele_pack_key();}
					if(tele_backup3[5]&0x10)			//ָ���Aָ����5
					{Key_Value=0x44;tele_pack_key();}			
					if(tele_backup3[5]&0x20)
					{Key_Value=0x45;tele_pack_key();}
					if(tele_backup3[5]&0x40)			//ָ���Aָ����7
					{Key_Value=0x46;tele_pack_key();}			
					if(tele_backup3[5]&0x80)
					{Key_Value=0x47;tele_pack_key();}																
				break;
		case 0xC0:								//ָ���A�ġ�ͣ��ָ����
					if(tele_backup3[5]&0x01)			//ָ���Aָ����1
					{Key_Value=0x20;tele_pack_key();}			
					if(tele_backup3[5]&0x02)
					{Key_Value=0x21;tele_pack_key();}
					if(tele_backup3[5]&0x04)			//ָ���Aָ����3
					{Key_Value=0x22;tele_pack_key();}			
					if(tele_backup3[5]&0x08)
					{Key_Value=0x23;tele_pack_key();}
					if(tele_backup3[5]&0x10)			//ָ���Aָ����5
					{Key_Value=0x24;tele_pack_key();}			
					if(tele_backup3[5]&0x20)
					{Key_Value=0x25;tele_pack_key();}
					if(tele_backup3[5]&0x40)			//ָ���Aָ����7
					{Key_Value=0x26;tele_pack_key();}		
					if(tele_backup3[5]&0x80)
					{Key_Value=0x27;tele_pack_key();}
				break;
		default :break;
	}
	switch(tele_backup3[4]&0x30)			//ָ���B----��Ӧ��8·��Ӧ����ָ������
	{
		case 0x10:								//ָ���B�Ķ�ָ����
				if(tele_backup3[5]&0x01)				//ָ���Bָ����1
					{Key_Value=0x80;tele_pack_sound();}			
					if(tele_backup3[5]&0x02)
					{Key_Value=0x81;tele_pack_sound();}
					if(tele_backup3[5]&0x04)			//ָ���Bָ����3
					{Key_Value=0x82;tele_pack_sound();}			
					if(tele_backup3[5]&0x08)
					{Key_Value=0x83;tele_pack_sound();}
					if(tele_backup3[5]&0x10)			//ָ���Bָ����5
					{Key_Value=0x84;tele_pack_sound();}			
					if(tele_backup3[5]&0x20)
					{Key_Value=0x85;tele_pack_sound();}
					if(tele_backup3[5]&0x40)			//ָ���Bָ����7
					{Key_Value=0x86;tele_pack_sound();}			
					if(tele_backup3[5]&0x80)
					{Key_Value=0x87;tele_pack_sound();}																
				break;
		case 0x20:								//ָ���B�ġ�����ָ����
					if(tele_backup3[5]&0x01)			//ָ���Bָ����1
					{Key_Value=0x40;tele_pack_sound();}			
					if(tele_backup3[5]&0x02)
					{Key_Value=0x41;tele_pack_sound();}
					if(tele_backup3[5]&0x04)			//ָ���Bָ����3
					{Key_Value=0x42;tele_pack_sound();}			
					if(tele_backup3[5]&0x08)
					{Key_Value=0x43;tele_pack_sound();}
					if(tele_backup3[5]&0x10)			//ָ���Bָ����5
					{Key_Value=0x44;tele_pack_sound();}			
					if(tele_backup3[5]&0x20)
					{Key_Value=0x45;tele_pack_sound();}
					if(tele_backup3[5]&0x40)			//ָ���Bָ����7
					{Key_Value=0x46;tele_pack_sound();}			
					if(tele_backup3[5]&0x80)
					{Key_Value=0x47;tele_pack_sound();}																
				break;	
		case 0x30:								//ָ���B�ġ�ͣ��ָ����
					if(tele_backup3[5]&0x01)			//ָ���Bָ����1
					{Key_Value=0x20;tele_pack_sound();}			
					if(tele_backup3[5]&0x02)
					{Key_Value=0x21;tele_pack_sound();}
					if(tele_backup3[5]&0x04)			//ָ���Bָ����3
					{Key_Value=0x22;tele_pack_sound();}			
					if(tele_backup3[5]&0x08)
					{Key_Value=0x23;tele_pack_sound();}
					if(tele_backup3[5]&0x10)			//ָ���Bָ����5
					{Key_Value=0x24;tele_pack_sound();}			
					if(tele_backup3[5]&0x20)
					{Key_Value=0x25;tele_pack_sound();}
					if(tele_backup3[5]&0x40)			//ָ���Bָ����7
					{Key_Value=0x26;tele_pack_sound();}			
					if(tele_backup3[5]&0x80)
					{Key_Value=0x27;tele_pack_sound();}
				break;
		default :break;				
	}
	switch(tele_backup3[4]&0x0C)				//ָ���C-----��Ӧ��8��6��·�̵�������2·�ɿع裩
	{
		case 0x04:								//ָ���C�Ķ�ָ����
				if(tele_backup3[5]&0x01)				//ָ���Cָ����1
					{Key_Value=0x80;tele_pack_relay();}			
					if(tele_backup3[5]&0x02)
					{Key_Value=0x81;tele_pack_relay();}
					if(tele_backup3[5]&0x04)			//ָ���Cָ����3
					{Key_Value=0x82;tele_pack_relay();}			
					if(tele_backup3[5]&0x08)
					{Key_Value=0x83;tele_pack_relay();}
					if(tele_backup3[5]&0x10)			//ָ���Cָ����5
					{Key_Value=0x84;tele_pack_relay();}			
					if(tele_backup3[5]&0x20)
					{Key_Value=0x85;tele_pack_relay();}
					if(tele_backup3[5]&0x40)			//ָ���Cָ����7
					{Key_Value=0x86;tele_pack_relay();}			
					if(tele_backup3[5]&0x80)
					{Key_Value=0x87;tele_pack_relay();}																
				break;
		case 0x08:								//ָ���C�ġ�����ָ����
					if(tele_backup3[5]&0x01)			//ָ���Cָ����1
					{Key_Value=0x40;tele_pack_relay();}			
					if(tele_backup3[5]&0x02)
					{Key_Value=0x41;tele_pack_relay();}
					if(tele_backup3[5]&0x04)			//ָ���Cָ����3
					{Key_Value=0x42;tele_pack_relay();}			
					if(tele_backup3[5]&0x08)
					{Key_Value=0x43;tele_pack_relay();}
					if(tele_backup3[5]&0x10)			//ָ���Cָ����5
					{Key_Value=0x44;tele_pack_relay();}			
					if(tele_backup3[5]&0x20)
					{Key_Value=0x45;tele_pack_relay();}
					if(tele_backup3[5]&0x40)			//ָ���Cָ����7
					{Key_Value=0x46;tele_pack_relay();}			
					if(tele_backup3[5]&0x80)
					{Key_Value=0x47;tele_pack_relay();}																
				break;	
		case 0x0c:								//ָ���C�ġ�ͣ��ָ����
					if(tele_backup3[5]&0x01)			//ָ���Cָ����1
					{Key_Value=0x20;tele_pack_relay();}			
					if(tele_backup3[5]&0x02)
					{Key_Value=0x21;tele_pack_relay();}
					if(tele_backup3[5]&0x04)			//ָ���Cָ����3
					{Key_Value=0x22;tele_pack_relay();}			
					if(tele_backup3[5]&0x08)
					{Key_Value=0x23;tele_pack_relay();}
					if(tele_backup3[5]&0x10)			//ָ���Cָ����5
					{Key_Value=0x24;tele_pack_relay();}			
					if(tele_backup3[5]&0x20)
					{Key_Value=0x25;tele_pack_relay();}
					if(tele_backup3[5]&0x40)			//ָ���Cָ����7
					{Key_Value=0x26;tele_pack_relay();}			
					if(tele_backup3[5]&0x80)
					{Key_Value=0x27;tele_pack_relay();}
				break;
		default :break;				
	}	
}
void jump_order2()									//����ʱ��ת������ת�����̡�ָ����		
{
	switch(tele_backup2[4]&0xC0)		//ָ���A--------��Ӧ��8·������ָ������
	{
		case 0x40:
		{								//ָ���A�ġ��̡�ָ����
				if(tele_backup2[5]&0x01)			//ָ���Aָ����1
				{Key_Value=0x80;tele_pack_key();}	//led0=~led0;		
				if(tele_backup2[5]&0x02)
				{Key_Value=0x81;tele_pack_key();}//  led1=~led1;
				if(tele_backup2[5]&0x04)			//ָ���Aָ����3
				{Key_Value=0x82;tele_pack_key();}			
				if(tele_backup2[5]&0x08)
				{Key_Value=0x83;tele_pack_key();}
				if(tele_backup2[5]&0x10)			//ָ���Aָ����5
				{Key_Value=0x84;tele_pack_key();}			
				if(tele_backup2[5]&0x20)
				{Key_Value=0x85;tele_pack_key();}
				if(tele_backup2[5]&0x40)			//ָ���Aָ����7
				{Key_Value=0x86;tele_pack_key();}			
				if(tele_backup2[5]&0x80)
				{Key_Value=0x87;tele_pack_key();}																
			
		}break;
		default :break;
	}
	switch(tele_backup2[4]&0x30)			//ָ���B----��Ӧ��8·��Ӧ����ָ������
	{
		case 0x10:								//ָ���B�Ķ�ָ����
		{
					if(tele_backup2[5]&0x01)				//ָ���Bָ����1
					{Key_Value=0x80;tele_pack_sound();}			
					if(tele_backup2[5]&0x02)
					{Key_Value=0x81;tele_pack_sound();}
					if(tele_backup2[5]&0x04)			//ָ���Bָ����3
					{Key_Value=0x82;tele_pack_sound();}			
					if(tele_backup2[5]&0x08)
					{Key_Value=0x83;tele_pack_sound();}
					if(tele_backup2[5]&0x10)			//ָ���Bָ����5
					{Key_Value=0x84;tele_pack_sound();}			
					if(tele_backup2[5]&0x20)
					{Key_Value=0x85;tele_pack_sound();}
					if(tele_backup2[5]&0x40)			//ָ���Bָ����7
					{Key_Value=0x86;tele_pack_sound();}			
					if(tele_backup2[5]&0x80)
					{Key_Value=0x87;tele_pack_sound();}	
		}break;
		default :break;				
	}
	switch(tele_backup2[4]&0x0C)				//ָ���C-----��Ӧ��8��6��·�̵�������2·�ɿع裩
	{
		case 0x04:								//ָ���C�Ķ�ָ����
		{
					if(tele_backup2[5]&0x01)				//ָ���Cָ����1
					{Key_Value=0x80;tele_pack_relay();}			
					if(tele_backup2[5]&0x02)
					{Key_Value=0x81;tele_pack_relay();}
					if(tele_backup2[5]&0x04)			//ָ���Cָ����3
					{Key_Value=0x82;tele_pack_relay();}			
					if(tele_backup2[5]&0x08)
					{Key_Value=0x83;tele_pack_relay();}
					if(tele_backup2[5]&0x10)			//ָ���Cָ����5
					{Key_Value=0x84;tele_pack_relay();}			
					if(tele_backup2[5]&0x20)
					{Key_Value=0x85;tele_pack_relay();}
					if(tele_backup2[5]&0x40)			//ָ���Cָ����7
					{Key_Value=0x86;tele_pack_relay();}			
					if(tele_backup2[5]&0x80)
					{Key_Value=0x87;tele_pack_relay();}	
		}break;																		
		default :break;				
	}	
}
bit jumptele_cache()
{
	unsigned char i;
	bit Tele_Full;
	for(i=0;i<22;i+=7)
	{
		temper=temper<<1;
		if(jump_tele[21-i]==0x00)
			temper=temper|0x01;						//��Temper�ĵ���λ���ж��ĸ��������Ƿ��п�
		else 										//��һλΪ1�����
			temper=temper&0xfe;
		temper&=0x0F;
	}
	if((temper&0x0F)!=0x00)
		Tele_Full=1;								//��ʾ�����п�
	else 
		Tele_Full=0;								//��ʾ��������		
	
	return Tele_Full;
}
unsigned char jumptele_write()
{
	unsigned char i;
	if(jumptele_cache())							//���пգ�������д�뻺����
	{											//�����жϣ����Ȼ���
		if(temper&0x01)
		{	
			for(i=0;i<7;i++)
				jump_tele[i]=tele_backup[i];
			return 1;
		}
		else if(temper&0x02)
		{
			for(i=0;i<7;i++)
				jump_tele[7+i]=tele_backup[i];
			return 2;
		}
		else if(temper&0x04)
		{
			for(i=0;i<7;i++)
				jump_tele[14+i]=tele_backup[i];
			return 3;
		}
		else
		{
			for(i=0;i<7;i++)
				jump_tele[21+i]=tele_backup[i];
			return 4;
		}
	}
	else 
		return 0;
}
