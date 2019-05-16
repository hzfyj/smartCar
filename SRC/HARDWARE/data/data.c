#include "data.h"
#include "stdint.h"
//菜单
int menu_no;//菜单空 变量

int zhong=4745;     //于 4745
int steerzuo=3790 ;   //于 4305 
int steeryou=5730;     //于 869 
 
int reload=0;         //重新赋值
int runmode;        //跑车参数
int mode_mode;      //模式
int slowstart;      //慢速起跑
int protect_stop;   //保护
int huandaocntmax;     //环岛个数
int slopecntmax;       //坡道个数
int blockcntmax;       //障碍个数
int yuzhi;          //预值
int dajiao;         //打角行
int superspeed;         //坡道速度
int longspeed;      //长直道速度
int shortspeed;     //短直道速度
int speedstraight;  //弯入弯出速度
int speedturn;      //弯道速度
int qipaoflag;         //坡道速度
int Ispeed1;         //环岛速度1
int Ispeed2;         //环岛速度2
int Ispeed3;         //环岛速度3
int Ispeed4;         //环岛速度4

int Ispeed1dj;         //环岛速度1打角
int Ispeed2dj;         //环岛速度2打角
int Ispeed3dj;         //环岛速度3打角
int Ispeed4dj;         //环岛速度4打角
int IkP1;
int IkP2;
int IkP3;
int IkP4;
int IkD1;
int IkD2;
int IkD3;
int IkD4;


int longstraightp;//长直道P              
int longstraightd;//长直道D
int straightp;    //入弯P           
int straightd;    //入弯D
int smallsp;      //小S P
int smallsd;      //小S D
int leftp;        //左转P
int leftd;        //左转D
int rightp;       //右转P           
int rightd;       //右转D
int huandaop;     //环岛P   
int huandaod;     //环岛D
int Bigsp;      //大S P
int Bigsd;      //大S D
int Bigs_dj;//大S打角行
int Mid_S_Switch;//大S开关
int speedBigs;    //大S速度
int po_speed;//坡道速度
int huandao_type[4];//存储环岛顺序
int longSS_speed;//长S速度
int blockspeed;
int dianbo_switch;
int DianjiP;
int flash_memory0[60]= //储存flash
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


int flash_memory1[60]= //储存flash
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
int flash_memory2[60]= //储存flash
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
int flash_memory3[60]= //储存flash
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
//预值数组
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










