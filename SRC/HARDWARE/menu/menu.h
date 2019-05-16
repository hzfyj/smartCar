#ifndef __MENU_H__
#define __MENU_H__
#include "i2c.h"
#include "data.h"
#include "stdint.h"
#define Number_All  56
#define addadd 1

struct Menu_Select
{
	char name[10];
	uint16_t num;
	uint16_t sub;
};

#if(Number_All >= 1)
#define name0     	"RUN"        //�ܳ�ģʽ
#define name0_num    runmode
#define name0_sub    addadd
#endif 

#if(Number_All >= 2)            //ģʽ
#define name1    	"MODE"      
#define name1_num  mode_mode  
#define name1_sub  addadd
#endif   

#if (Number_All >= 3)
#define name2   	"SLOW"            //��������
#define name2_num  slowstart
#define name2_sub  addadd   
#endif    

#if(Number_All >= 4)
#define name3  	"PROT"        // ����
#define name3_num  protect_stop
#define name3_sub  addadd   
#endif  

#if(Number_All >= 5)
#define name4  	"STOP"         //������
#define name4_num  qipaoflag
#define name4_sub  addadd
#endif


#if(Number_All >= 6)     //     ��������
#define name5    	"ICNT"             
#define name5_num   huandaocntmax
#define name5_sub   addadd
#endif   

#if(Number_All >= 7)     //     �µ�����
#define name6     	"PCNT"             
#define name6_num  slopecntmax
#define name6_sub   addadd
#endif   

#if(Number_All >= 8)     //     �ϰ�����
#define name7     	"BCNT"             
#define name7_num  blockcntmax
#define name7_sub   addadd
#endif   


#if(Number_All >= 9)          //     Ԥֵ
#define name8   	"YUZHI"      
#define name8_num  yuzhi
#define name8_sub   addadd
#endif  

#if(Number_All >= 10)           //�����
#define name9    	"DAJIAO"      
#define name9_num  dajiao
#define name9_sub  addadd   
#endif    
  
#if(Number_All >= 11)           //�����
#define name10    	"SUPER"      
#define name10_num  superspeed
#define name10_sub  addadd   
#endif  

#if(Number_All >= 12)
#define name11    	"LSPEED"         //��ֱ���ٶ�
#define name11_num  longspeed
#define name11_sub  addadd
#endif   

#if(Number_All >= 13)
#define name12 	"SSPEED"      //��ֱ���ٶ�
#define name12_num  shortspeed
#define name12_sub  addadd
#endif 

#if(Number_All >= 14)           //��ͨ�ٶ�
#define name13   	"NSPEED"      
#define name13_num  speedstraight
#define name13_sub  addadd
#endif    

#if(Number_All >= 15)
#define name14  	"TSPEED"      //ת���ٶ�
#define name14_num  speedturn
#define name14_sub  addadd
#endif   


#if(Number_All >= 16)      //��P
#define name15  	"LONGP"      
#define name15_num  longstraightp	
#define name15_sub  addadd
#endif  

#if(Number_All >= 17)     // ��D
#define name16  	"LONGD"      
#define name16_num  longstraightd
#define name16_sub  addadd
#endif   

#if(Number_All >= 18)          // ��ͨP
#define name17    	"STP"      
#define name17_num  straightp
#define name17_sub addadd
#endif      

#if(Number_All >= 19)           
#define name18    	"STD"   //  ��ͨD
#define name18_num  straightd
#define name18_sub addadd
#endif    


#if(Number_All >= 20)      //СS P
#define name19   	"SSP"      
#define name19_num  smallsp
#define name19_sub  addadd
#endif  

#if(Number_All >= 21)        //СS D
#define name20   	"SSD"      
#define name20_num  smallsd
#define name20_sub  addadd
#endif    

#if(Number_All >= 22)
#define name21    	"LP"           //��תP
#define name21_num   leftp
#define name21_sub   addadd
#endif   

#if(Number_All >= 23)
#define name22    	"LD"      //��תD
#define name22_num   leftd
#define name22_sub  addadd
#endif  

 #if(Number_All >= 24)             //   ��תP
#define name23  	"RP"      
#define name23_num  rightp
#define name23_sub  addadd
#endif 

 #if(Number_All >= 25)             //��תD
#define name24    	"RD"
#define name24_num  rightd
#define name24_sub  addadd
#endif    

#if(Number_All >= 26)
#define name25    	"IDJ1"      //����1���
#define name25_num  Ispeed1dj
#define name25_sub  addadd
#endif    

#if(Number_All >= 27)
#define name26    	"IDJ2"         //����2���
#define name26_num Ispeed2dj
#define name26_sub  addadd
#endif    

#if(Number_All >= 28)
#define name27    	"IDJ3"     //����3���  
#define name27_num  Ispeed3dj
#define name27_sub  addadd
#endif    

#if(Number_All >= 29)
#define name28    	"IDJ4"       //����4���
#define name28_num  Ispeed4dj
#define name28_sub  addadd
#endif    

#if(Number_All >= 30)
#define name29    	"ISPEED1"      //����1�ٶ�
#define name29_num  Ispeed1
#define name29_sub  addadd
#endif    

#if(Number_All >= 31)           //����2�ٶ�
#define name30    	"ISPEED2"
#define name30_num Ispeed2
#define name30_sub  addadd
#endif   
#if(Number_All >= 32)           //����3�ٶ�
#define name31    	"ISPEED3"     
#define name31_num  Ispeed3
#define name31_sub  addadd
#endif   
#if(Number_All >= 33)           //����4�ٶ�
#define name32    	"ISPEED4"      
#define name32_num Ispeed4
#define name32_sub  addadd
#endif   
#if(Number_All >= 34)         //��  
#define name33    	"LSS-SPEED"      
#define name33_num   longSS_speed
#define name33_sub addadd
#endif  
#if(Number_All >= 35)   //��S����
#define name34    	"BigS-OP"      
#define name34_num  Mid_S_Switch  
#define name34_sub  addadd
#endif   
#if(Number_All >= 36)   //��S���
#define name35    	"BS-DJ"      
#define name35_num  Bigs_dj  
#define name35_sub  addadd
#endif   
#if(Number_All >= 37)  //��Sp
#define name36    	"BsP"      
#define name36_num  Bigsp  
#define name36_sub  addadd
#endif   
#if(Number_All >= 38)//��SD
#define name37    	"BsD"      
#define name37_num  Bigsd  
#define name37_sub  addadd
#endif   
#if(Number_All >= 39) //��S�ٶ�
#define name38    	"BSspeed"      
#define name38_num  speedBigs  
#define name38_sub  addadd 
#endif    
#if(Number_All >= 40) //�µ��ٶ�
#define name39    	"Pospeed"      
#define name39_num  po_speed  
#define name39_sub  addadd 
#endif   
#if(Number_All >= 41) 
#define name40    	"1Huan "    //����Խ��Խ��
#define name40_num  huandao_type[0]  
#define name40_sub  addadd 
#endif   
#if(Number_All >= 42) 
#define name41    	"2Huan"      
#define name41_num  huandao_type[1]  
#define name41_sub  addadd 
#endif   
#if(Number_All >= 43) 
#define name42    	"3Huan"      
#define name42_num  huandao_type[2]  
#define name42_sub  addadd 
#endif   
#if(Number_All >= 44) 
#define name43    	"4Huan"      
#define name43_num  huandao_type[3]  
#define name43_sub  addadd 
#endif   
#if(Number_All >= 45) 
#define name44    	"IP1"      
#define name44_num  IkP1  
#define name44_sub  addadd 
#endif 
#if(Number_All >= 46) 
#define name45    	"IP2"      
#define name45_num  IkP2 
#define name45_sub  addadd 
#endif 
#if(Number_All >= 47) 
#define name46    	"IP3"      
#define name46_num  IkP3
#define name46_sub  addadd 
#endif 
#if(Number_All >= 48) 
#define name47    	"IP4"      
#define name47_num  IkP4
#define name47_sub  addadd 
#endif 
#if(Number_All >= 49) 
#define name48    	"ID1"      
#define name48_num  IkD1 
#define name48_sub  addadd 
#endif 
#if(Number_All >= 50) 
#define name49    	"ID2"      
#define name49_num  IkD2 
#define name49_sub  addadd 
#endif 
#if(Number_All >= 51) 
#define name50    	"ID3"      
#define name50_num  IkD3
#define name50_sub  addadd 
#endif 
#if(Number_All >= 52) 
#define name51    	"ID4"      
#define name51_num  IkD4  
#define name51_sub  addadd 
#endif 
#if(Number_All >= 53) 
#define name52    	"BLKSPEED"      
#define name52_num  blockspeed  
#define name52_sub  addadd 
#endif 
#if(Number_All >= 54) 
#define name53    	"OPdianbo"      
#define name53_num  dianbo_switch  
#define name53_sub  addadd 
#endif 
#if(Number_All >= 55) 
#define name54    	" "      
#define name54_num  DianjiP  
#define name54_sub  addadd 
#endif 
#if(Number_All >= 56)//���¼��� ʼ�շ������һ�� ���洢FLASH  ���Ĳ˵�ʱ��Ҫ����
#define name55    	"ReLoad"      
#define name55_num  reload  
#define name55_sub  addadd 
#endif   

void menu(void);



extern int startstart;
void flash(void);
void mode3(void);
void mode2(void);
void mode1(void);
void mode4(void);
void mode5(void);
void mode6(void);



#endif
