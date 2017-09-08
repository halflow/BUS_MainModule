/*****************************************************************
                        TELE_MANAGE.c  file

��Ҫ���ܣ�����ѭ��������е�ʵ�������

����ʱ�䣺2015.10.31
*****************************************************************/
/*--------------------------------------------------------------*/
/*----------------------------ͷ�ļ�----------------------------*/
/*--------------------------------------------------------------*/
#include "TELE_MANAGE.h"
#include "CONFIG.h"
#include "tele_t_r.h"
#include "tele_parse.h"
#include "control.h"


unsigned char  Tele_T[QUEUE_LENGTH];               //���ͱ��Ļ�����
unsigned char  Tele_R[QUEUE_LENGTH];               //���ձ��Ļ�����

unsigned char *Head_Index_T;                      //���ķ��Ͷ���ͷ��ַ
unsigned char *Tail_Index_T;                      //���ķ��Ͷ���β��ַ
unsigned char *Head_Index_R;                      //���Ľ��ն���ͷ��ַ
unsigned char *Tail_Index_R;                      //���Ľ��ն���β��ַ

bit           Queue_Empty_T;                      //���ķ��Ͷ��пձ�־λ
bit           Queue_Empty_R;                      //���Ľ��ն��пձ�־λ


bit           Tele_Cheak_T;        //���ڱ궨�Ƿ���Ҫ���з��ͻ�����м�飬���������Ƿ��б���
bit           Tele_Cheak_R;        //���ڱ궨�Ƿ���Ҫ���н��ջ�����м�飬���������Ƿ��б���
bit           Tele_Handle_R;       //���ջ��������Ĵ����־λ

/*--------------------------------------------------------------*/
/*------------------------���Ĺ����ʼ��-----------------------*/
/*--------------------------------------------------------------*/
void init_tele_manage()
{
	Head_Index_T=Tele_T;                               //��ʼ�����ķ��Ͷ���ͷ��ַ
	Tail_Index_T=Tele_T;                               //��ʼ�����ķ��Ͷ���β��ַ
	Head_Index_R=Tele_R;                               //��ʼ�����Ľ��ն���ͷ��ַ
	Tail_Index_R=Tele_R;                               //��ʼ�����Ľ��ն���β��ַ
	
	Queue_Empty_T=1;                                   //���ķ��Ͷ���Ϊ��
    Queue_Empty_R=1;                                   //���Ľ��ն���Ϊ��
	
	Tele_Cheak_T=1;								//���ķ��ͻ�����м��λ����ʼ����1���Ա��Ļ��������м��
	Tele_Cheak_R=1;								//���Ľ��ջ�����м��λ����ʼ����1���Ա��Ļ��������м��
}

/*-------------------------------------------------------------*/
/*---------------------д���ķ��ͻ������----------------------*/
/*-------------------------------------------------------------*/
unsigned char write_tele_t(unsigned char date[],unsigned char n)//������ID1��ID2��CRC  3֡
{											
	unsigned char i;			
										//�°�Э����bit3-bit0���������򳤶�
	if((date[0]&0x0f)!=n-3)             //��д�����ݸ�ʽ���м�飬��Ա��Ļ���������ǳ���Ҫ
		return 0;				//�ж�������֡����������װ���ļ�ȥ�ˡ��������ԣ�ȺID��ģ��ID3֡��

	if(Head_Index_T==Tail_Index_T)                     //���ͻ������Ϊ�ջ�����
	{
		if(Queue_Empty_T)                                //����Ϊ��
		{
			for(i=0;i<n;i++)					//��n������д�뵽���ķ��ͻ�������������ID1,ID2��CRC��
			{
				*Head_Index_T=date[i];				//��date[]���ݸ�ָ�����*Head_Index
				Head_Index_T++;
				if((Head_Index_T-Tele_T)==QUEUE_LENGTH)     //ͷ��ַ���   40
					Head_Index_T=Head_Index_T-QUEUE_LENGTH;   //ͷ��ַ������С��ַ��ʵ��ѭ������
			}
			Queue_Empty_T=0;                              //���зǿգ���������
		}
		else                                            //����Ϊ��
			return 0;                                     
	}
	
	else if(Head_Index_T>Tail_Index_T)
	{
		if((QUEUE_LENGTH+Tail_Index_T)>=(n+Head_Index_T))  //����ʣ��ռ�����������±���
		{
			for(i=0;i<n;i++)
			{
				*Head_Index_T=date[i];
				Head_Index_T++;
				if((Head_Index_T-Tele_T)==QUEUE_LENGTH)     //ͷ��ַ���
					Head_Index_T=Head_Index_T-QUEUE_LENGTH;   //ͷ��ַ������С��ַ��ʵ��ѭ������
			}
		}
		else
			return 0;
	}
	
	else
	{
		if((Tail_Index_T-Head_Index_T)>=n)              //����ʣ��ռ�����������±���
		{
			for(i=0;i<n;i++)
			{
				*Head_Index_T=date[i];
				Head_Index_T++;                             //�˴β���Ҫ����ͷ��ַ����ж�
				if((Head_Index_T-Tele_T)==QUEUE_LENGTH)     //ͷ��ַ���
					Head_Index_T=Head_Index_T-QUEUE_LENGTH;   //ͷ��ַ������С��ַ��ʵ��ѭ������
			}
		}
		else
			return 0;
	}
	
	return 1;                                        //���ݳɹ�д��
}

/*--------------------------------------------------------------*/
/*---------------------�����ķ��ͻ������-----------------------*/
/*------------���ܣ����ػ��汨�ĵĳ���--------------------------*/
/*--------------------------------------------------------------*/
unsigned char read_tele_t(unsigned char date[])
{
	unsigned char i,n;
	n=0;											//�洢������֡����
	
	if(Head_Index_T==Tail_Index_T)                   //���ͻ������Ϊ�ջ�����
	{
		if(Queue_Empty_T)                              //����Ϊ��,�ޱ���
			return 0;
		else											//���зǿ�
		{
			date[0]=*Tail_Index_T;				//��д���βָ�뿪ʼ��
			Tail_Index_T++;
			n=date[0]&0x0F;					//�жϱ����������򳤶�
	
			for(i=1;i<n+3;i++)					//n+3�����ˡ��������ԣ�ȺID������ID��������ID1��ID2��CRC
			{
				date[i]=*Tail_Index_T;
				Tail_Index_T++;
				if((Tail_Index_T-Tele_T)==QUEUE_LENGTH)     //β��ַ���
					Tail_Index_T=Tail_Index_T-QUEUE_LENGTH;   //β��ַ������С��ַ��ʵ��ѭ������
			}
		}
	}
	
	else if(Head_Index_T>Tail_Index_T)
	{
              
		n=*Tail_Index_T&0x0F;						//�ɱ�������֡��ȡ������������Ŀ		                     
		
		if((Head_Index_T-Tail_Index_T)<(n+3)) //������ʣ��֡��ĿС�ڱ����ĸ��е�֡��Ŀ(�������ڵķ��ͱ���֡��Ŀ�ȱ����������֡��ĿС3)
		{                                      //n+3�����ˡ��������ԣ�ȺID������ID��������ID1��ID2��CRC
			Tail_Index_T=Head_Index_T;       //�����������д��������������
			Queue_Empty_T=1;
			return 0;
		}
		else									//�������ܹ����ɱ��ĵ�֡��
		{
			for(i=0;i<n+3;i++)
			{
				date[i]=*Tail_Index_T;
				Tail_Index_T++;
				if((Tail_Index_T-Tele_T)==QUEUE_LENGTH)     //β��ַ���,,,�˴�����Ҫ���
					Tail_Index_T=Tail_Index_T-QUEUE_LENGTH;   //β��ַ������С��ַ��ʵ��ѭ������
			}
			if(Head_Index_T==Tail_Index_T)
				Queue_Empty_T=1;
		}
	}
	
	else
	{
    
		n=*Tail_Index_T&0x0F;								//�ɱ�������֡��ȡ��������Ŀ
		
		if((Head_Index_T-Tail_Index_T+QUEUE_LENGTH)<(n+3))
		{
			Tail_Index_T=Head_Index_T;                   //�����������д��������������
			Queue_Empty_T=1;
			return 0;
		}
		else
		{
			for(i=0;i<n+3;i++)
			{
				date[i]=*Tail_Index_T;
				Tail_Index_T++;
				if((Tail_Index_T-Tele_T)==QUEUE_LENGTH)     //β��ַ���
					Tail_Index_T=Tail_Index_T-QUEUE_LENGTH;   //β��ַ������С��ַ��ʵ��ѭ������
			}
			if(Head_Index_T==Tail_Index_T)
				Queue_Empty_T=1;
		}
	}
	
	return (n+3);					//n+3�����ˡ��������ԣ�ȺID������ID��������ID1��ID2��CRC
}


/*--------------------------------------------------------------*/
/*---------------------д���Ľ��ջ������----------------------*/
/*--------------------------------------------------------------*/
unsigned char write_tele_r(unsigned char date[],unsigned char n)
{
	unsigned char i;
										      //n�к��С�ID1,ID2,����,�����򡿣�ȱ�١�ȺID������ģ��,CRC 3֡��
	if((date[2]&0x0F)!=n-3)                            //��д�����ݸ�ʽ���м�飬��Ա��Ļ���������ǳ���Ҫ
		return 0;

	if(Head_Index_R==Tail_Index_R)                     //���ջ������Ϊ�ջ�����
	{
		if(Queue_Empty_R)                                //����Ϊ��
		{
			for(i=0;i<n;i++)
			{
				*Head_Index_R=date[i];
				Head_Index_R++;
				if((Head_Index_R-Tele_R)==QUEUE_LENGTH)     //ͷ��ַ���
					Head_Index_R=Head_Index_R-QUEUE_LENGTH;   //ͷ��ַ������С��ַ��ʵ��ѭ������
			}
			Queue_Empty_R=0;                              //���зǿ�
		}
		else                                            //����Ϊ��
			return 0;                                     
	}
	
	else if(Head_Index_R>Tail_Index_R)
	{
		if((QUEUE_LENGTH+Tail_Index_R)>=(n+Head_Index_R))  //����ʣ��ռ�����������±���
		{
			for(i=0;i<n;i++)
			{
				*Head_Index_R=date[i];
				Head_Index_R++;
				if((Head_Index_R-Tele_R)==QUEUE_LENGTH)     //ͷ��ַ���
					Head_Index_R=Head_Index_R-QUEUE_LENGTH;   //ͷ��ַ������С��ַ��ʵ��ѭ������
			}
		}
		else
			return 0;
	}
	
	else
	{
		if((Tail_Index_R-Head_Index_R)>=n)             //����ʣ��ռ�����������±���
		{
			for(i=0;i<n;i++)
			{
				*Head_Index_R=date[i];
				Head_Index_R++;                            //�˴β���Ҫ����ͷ��ַ����ж�
				if((Head_Index_R-Tele_R)==QUEUE_LENGTH)     //ͷ��ַ���
					Head_Index_R=Head_Index_R-QUEUE_LENGTH;   //ͷ��ַ������С��ַ��ʵ��ѭ������
			}
		}
		else
			return 0;
	}
	
	return 1;                                        //���ݳɹ�д��
}

/*--------------------------------------------------------------*/
/*---------------------�����Ľ��ջ������-----------------------*/
/*                 ����:����ȡ�����ձ��ĵĸ���ֵ                */
/*--------------------------------------------------------------*/
unsigned char read_tele_r(unsigned char date[])
{
	unsigned char i,n;
	n=0;
	
	if(Head_Index_R==Tail_Index_R)                   //���ͻ������Ϊ�ջ�����
	{
		if(Queue_Empty_R)                              //���п�
			return 0;
		else										   //���зǿ�
		{
			if(Tail_Index_R-Tele_R>=QUEUE_LENGTH-2)			//
			{
					n=*(Tail_Index_R+2-QUEUE_LENGTH)&0x0F;				//nΪ��������������
			}
			else
			{
					n=*(Tail_Index_R+2)&0x0F;
			}
			for(i=0;i<n+3;i++)						//������+��ID1,ID2,���ԡ�
			{
				date[i]=*Tail_Index_R;
				Tail_Index_R++;
				if((Tail_Index_R-Tele_R)==QUEUE_LENGTH)     //β��ַ���
					Tail_Index_R=Tail_Index_R-QUEUE_LENGTH;   //β��ַ������С��ַ��ʵ��ѭ������
			}
		}
	}
	
	else if(Head_Index_R>Tail_Index_R)
	{
		if(Tail_Index_R-Tele_R>=QUEUE_LENGTH-2)         
		{
				n=*(Tail_Index_R+2-QUEUE_LENGTH)&0x0F;		  //�ɱ�������֡��ȡ������������Ŀ
		}
		else
		{
				n=*(Tail_Index_R+2)&0x0F;					//�ɱ�������֡��ȡ������������Ŀ
		}             
		
		if((Head_Index_R-Tail_Index_R)<(n+3))//������ʣ��֡��ĿС�ڱ����ĸ��е�֡��Ŀ(�������ڵķ��ͱ���֡��Ŀ�ȱ����������֡��ĿС3)
		{                                              //����ȺID������ģ��ID��CRC֡
			Tail_Index_R=Head_Index_R;                   //�����������д��������������
			Queue_Empty_R=1;
			return 0;
		}
		else
		{
			for(i=0;i<n+3;i++)
			{
				date[i]=*Tail_Index_R;
				Tail_Index_R++;
				if((Tail_Index_R-Tele_R)==QUEUE_LENGTH)     //β��ַ���,,,�˴�����Ҫ���
					Tail_Index_R=Tail_Index_R-QUEUE_LENGTH;   //β��ַ������С��ַ��ʵ��ѭ������
			}
			if(Head_Index_R==Tail_Index_R)
				Queue_Empty_R=1;
		}
	}
	
	else
	{
		if(Tail_Index_R-Tele_R>=QUEUE_LENGTH-2)         //�ɱ�������֡��ȡ����֡��Ŀ
		{
				n=*(Tail_Index_R+2-QUEUE_LENGTH)&0x0F;
		}
		else
		{
				n=*(Tail_Index_R+2)&0x0F;
		}                      
		
		if((Head_Index_R-Tail_Index_R+QUEUE_LENGTH)<(n+3))
		{
			Tail_Index_R=Head_Index_R;                   //�����������д��������������
			Queue_Empty_R=1;
			return 0;
		}
		else
		{
			for(i=0;i<n+3;i++)
			{
				date[i]=*Tail_Index_R;
				Tail_Index_R++;
				if((Tail_Index_R-Tele_R)==QUEUE_LENGTH)     //β��ַ���
					Tail_Index_R=Tail_Index_R-QUEUE_LENGTH;   //β��ַ������С��ַ��ʵ��ѭ������
			}
			if(Head_Index_R==Tail_Index_R)
				Queue_Empty_R=1;
		}
	}
	
	return (n+3);							//���ء�ID1��ID2�����ԣ������򡿲����С�ȺID������ģ��ID��CRC��
}

/*-------------------------------------------------------------*/
/*----------------------���Ļ�����м��-----------------------*/
/*-------------------------------------------------------------*/
void tele_cheakt()
{
	unsigned char i;
	if(Queue_Empty_T==0)								//���зǿգ���������
	{
		Frame_Num_T=read_tele_t(t); //���������ı��Ķ�ȡ��t[]������������+���������ԣ�ȺID������ID��������ID1��ID2��CRC
		if(Frame_Num_T)							//
		{		
			if(t[2]==ID)
			{
				if(t[0]&0x10)
					  Group_Operate_Flag=1;
				else  Module_Operate_Flag=1;

				tele[2]=t[0];
				for(i=3;i<10;i++)
					tele[i]=t[i];				
				Tele_Handle_R=1;
//				led0=~led0;  	
			}
			else 
			{
				Tele_TF=1;							//�б���Ҫ������1--->>��������ȡ���ķ��ͺ���
				Tele_Cheak_T=0;                                        //ֹͣ���ͻ�����м��
			}
		}
	}
}

void tele_cheakr()
{
	if(Queue_Empty_R==0)							////���зǿգ���������
		Tele_Handle_R=1;				    //���ջ��������Ĵ����־λ��1--->>���������б��Ľ���
}