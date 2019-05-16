#ifndef __DATA_H__
#define __DATA_H__
#include "stdint.h"
//舵机中值
extern int zhong;
extern int steerzuo;   
extern int steeryou; 
//菜单里的变量
extern int menu_no;
extern int reload;         //重新赋值
extern int runmode;        //跑车参数
extern int mode_mode;      //模式
extern int slowstart;      //慢速起跑
extern int protect_stop;   //保护
extern int huandaocntmax;     //环岛个数
extern int slopecntmax;       //坡道个数
extern int blockcntmax;       //障碍个数
extern int Mid_S_Switch;//大S开关
extern int yuzhi;          //预值
extern int dajiao;         //打角行
extern int superspeed;      //超长直道速度
extern int longspeed;      //长直道速度
extern int shortspeed;     //短直道速度
extern int speedstraight;  //弯入弯出速度
extern int speedturn;      //弯道速度
extern int speedBigs;    //大S速度
extern int po_speed;    //坡道速度
extern int qipaoflag;       //起跑速度
extern int Ispeed1;         //环岛速度1
extern int Ispeed2;         //环岛速度2
extern int Ispeed3;         //环岛速度3
extern int Ispeed4;         //环岛速度4
extern int Ispeed1dj;         //环岛速度1打角
extern int Ispeed2dj;         //环岛速度2打角
extern int Ispeed3dj;         //环岛速度3打角
extern int Ispeed4dj;         //环岛速度4打角
extern int longstraightp;//长直道P              
extern int longstraightd;//长直道D
extern int straightp;    //入弯P           
extern int straightd;    //入弯D
extern int smallsp;      //小S P
extern int smallsd;      //小S D
extern int leftp;        //左转P
extern int leftd;        //左转D
extern int rightp;       //右转P           
extern int rightd;       //右转D
extern int huandaop;     //环岛P   
extern int huandaod;     //环岛D
extern int Bigsp;      //大S P
extern int Bigsd;      //大S D
extern int Bigs_dj;//大S打角行

extern int huandao_type[4];
extern int flash_memory0[60]; //储存flash
extern int flash_memory1[60]; //储存flash
extern int flash_memory2[60]; //储存flash
extern int flash_memory3[60];
extern uint8_t My_yuzhi[70];
extern int IkP1;
extern int IkP2;
extern int IkP3;
extern int IkP4;
extern int IkD1;
extern int IkD2;
extern int IkD3;
extern int IkD4;
extern int longSS_speed;
extern int blockspeed;
extern int dianbo_switch;
extern int DianjiP;

#endif