#ifndef Fuzzy_control_h
#define Fuzzy_control_h

#include "stdint.h"

#define byte uint8_t


float MyFuzzy2(int Error, int DError, byte PD_Flag);//���ģ��
 float MyFuzzy1(int Error, int DError, byte PD_Flag); //���ģ�� 


#endif