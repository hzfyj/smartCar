#include "data.h"
#include "stdint.h"
//�˵�
int menu_no;//�˵��� ����

int zhong=4745;     //�� 4745
int steerzuo=3790 ;   //�� 4305 
int steeryou=5730;     //�� 869 
 
int reload=0;         //���¸�ֵ
int runmode;        //�ܳ�����
int mode_mode;      //ģʽ
int slowstart;      //��������
int protect_stop;   //����
int huandaocntmax;     //��������
int slopecntmax;       //�µ�����
int blockcntmax;       //�ϰ�����
int yuzhi;          //Ԥֵ
int dajiao;         //�����
int superspeed;         //�µ��ٶ�
int longspeed;      //��ֱ���ٶ�
int shortspeed;     //��ֱ���ٶ�
int speedstraight;  //��������ٶ�
int speedturn;      //����ٶ�
int qipaoflag;         //�µ��ٶ�
int Ispeed1;         //�����ٶ�1
int Ispeed2;         //�����ٶ�2
int Ispeed3;         //�����ٶ�3
int Ispeed4;         //�����ٶ�4

int Ispeed1dj;         //�����ٶ�1���
int Ispeed2dj;         //�����ٶ�2���
int Ispeed3dj;         //�����ٶ�3���
int Ispeed4dj;         //�����ٶ�4���
int IkP1;
int IkP2;
int IkP3;
int IkP4;
int IkD1;
int IkD2;
int IkD3;
int IkD4;


int longstraightp;//��ֱ��P              
int longstraightd;//��ֱ��D
int straightp;    //����P           
int straightd;    //����D
int smallsp;      //СS P
int smallsd;      //СS D
int leftp;        //��תP
int leftd;        //��תD
int rightp;       //��תP           
int rightd;       //��תD
int huandaop;     //����P   
int huandaod;     //����D
int Bigsp;      //��S P
int Bigsd;      //��S D
int Bigs_dj;//��S�����
int Mid_S_Switch;//��S����
int speedBigs;    //��S�ٶ�
int po_speed;//�µ��ٶ�
int huandao_type[4];//�洢����˳��
int longSS_speed;//��S�ٶ�
int blockspeed;
int dianbo_switch;
int DianjiP;
int flash_memory0[60]= //����flash
{
	0,1,0,1,
	1,3,1,1,
	126,15,65,50,
	45,40,37,65,
	170,88,283,60,
	170,86,278,91,
	291,13,13,13,
	13,40,41,42,
	43,50,1,14,
	83,252,40,39,
	1,1,1,1,
	101,97,101,111,
	100,109,87,73,
	39,1,0,0,

};


int flash_memory1[60]= //����flash
{
	1,1,0,1,
	1,3,1,1,
	126,15,75,60,
	50,42,39,65,
	170,90,283,60,
	170,91,283,103,
	307,13,13,12,
	12,40,41,42,
	43,50,1,14,
	83,252,40,39,
	1,1,1,1,
	101,97,90,85,
	100,109,85,70,
	39,1,0,0,
};
int flash_memory2[60]= //����flash
{
	2,1,0,1,
	1,3,1,1,
	126,15,70,57,
	48,41,38,65,
	170,90,283,56,
	166,86,279,97,
	302,13,13,12,
	12,40,41,42,
	43,50,1,14,
	83,252,40,39,
	1,1,1,1,
	101,97,101,111,
	100,109,87,73,
	39,1,0,0,

};
int flash_memory3[60]= //����flash
{
	3,1,0,1,
	1,3,1,1,
	126,15,75,65,
	49,44,39,65,
	170,90,283,60,
	170,88,281,103,
	307,13,13,12,
	12,40,41,42,
	43,50,1,14,
	83,252,40,39,
	1,1,1,1,
	101,97,101,111,
	100,109,87,73,
	39,1,0,0,

};
//Ԥֵ����
uint8_t My_yuzhi[70]=
{

3,3,3,3,3,3,3,3,3,3,
5,5,5,5,5,5,5,5,5,5,
8,8,8,8,8,8,8,8,8,8,
13,13,13,13,13,13,13,13,13,13,
15,15,15,15,15,15,15,15,15,15,
16,16,16,16,16,16,16,16,16,16,
18,18,18,18,18,18,18,18,18,18,
	//18,18,18,18,18,18,18,18,18,18,
//20,20,20,20,20,20,20,20,20,20,

};










