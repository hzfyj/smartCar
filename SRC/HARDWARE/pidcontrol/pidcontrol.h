#ifndef __PIDCONTROL_H__
#define __PIDCONTROL_H__


int straightpid();
int turnpidzuo();
int turnpidyou();
int dianjicha();
int huandaopid();  
int longstraightpid();
extern int pwm;
extern int ZhanKongBi;
extern int FTM_BiHuan;
void IncPIDInit();
void motorOut();
int blockpid();
void motorPIDOut();
int Motor_PID(int SetPoint,int NextPoint);
int bigspid();
int lianwanyou(); 
int lianwanzuo();  

extern float motorp;

int smallspid();
extern float bianmap;
extern float bianmai;
extern float bianmad;
extern  float CESHI_bianmai;
#endif


