#ifndef __PROCESS_H__
#define __PROCESS_H__
#include "stdint.h"
extern uint8_t L_black[70];
extern uint8_t R_black[70];
extern uint8_t LCenter[70];
extern uint8_t cutline;
extern uint8_t RowNum;
extern int speed;
extern int midleline;
extern   int aim;
void ImageProcess();
void steercontrol();
void Image_Init();
void FieldProcess();
void SignalProcess();
extern uint8_t crossflag;
extern int jiance;
extern uint8_t huandaoflag;
extern int zuo;
extern int you;
extern int motorpwm;
//改变预值
extern uint8_t longstraightflag;         //长直道
extern uint8_t huandaoyouflag1;
extern uint8_t huandaoyouflag2;
extern uint8_t huandaoyouflag3;
extern uint8_t huandaozuoflag1;
extern uint8_t huandaozuoflag2;
extern uint8_t huandaozuoflag3;
extern uint8_t huandaowanflag;
extern uint8_t huandaochu1;
extern uint8_t huandaochu;
extern double doub_temp;
#endif
