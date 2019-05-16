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
#define name0     	"RUN"        //跑车模式
#define name0_num    runmode
#define name0_sub    addadd
#endif 

#if(Number_All >= 2)            //模式
#define name1    	"MODE"      
#define name1_num  mode_mode  
#define name1_sub  addadd
#endif   

#if (Number_All >= 3)
#define name2   	"SLOW"            //慢速起跑
#define name2_num  slowstart
#define name2_sub  addadd   
#endif    

#if(Number_All >= 4)
#define name3  	"PROT"        // 保护
#define name3_num  protect_stop
#define name3_sub  addadd   
#endif  

#if(Number_All >= 5)
#define name4  	"STOP"         //起跑线
#define name4_num  qipaoflag
#define name4_sub  addadd
#endif


#if(Number_All >= 6)     //     环岛计数
#define name5    	"ICNT"             
#define name5_num   huandaocntmax
#define name5_sub   addadd
#endif   

#if(Number_All >= 7)     //     坡道计数
#define name6     	"PCNT"             
#define name6_num  slopecntmax
#define name6_sub   addadd
#endif   

#if(Number_All >= 8)     //     障碍计数
#define name7     	"BCNT"             
#define name7_num  blockcntmax
#define name7_sub   addadd
#endif   


#if(Number_All >= 9)          //     预值
#define name8   	"YUZHI"      
#define name8_num  yuzhi
#define name8_sub   addadd
#endif  

#if(Number_All >= 10)           //打角行
#define name9    	"DAJIAO"      
#define name9_num  dajiao
#define name9_sub  addadd   
#endif    
  
#if(Number_All >= 11)           //打角行
#define name10    	"SUPER"      
#define name10_num  superspeed
#define name10_sub  addadd   
#endif  

#if(Number_All >= 12)
#define name11    	"LSPEED"         //长直道速度
#define name11_num  longspeed
#define name11_sub  addadd
#endif   

#if(Number_All >= 13)
#define name12 	"SSPEED"      //短直道速度
#define name12_num  shortspeed
#define name12_sub  addadd
#endif 

#if(Number_All >= 14)           //普通速度
#define name13   	"NSPEED"      
#define name13_num  speedstraight
#define name13_sub  addadd
#endif    

#if(Number_All >= 15)
#define name14  	"TSPEED"      //转弯速度
#define name14_num  speedturn
#define name14_sub  addadd
#endif   


#if(Number_All >= 16)      //长P
#define name15  	"LONGP"      
#define name15_num  longstraightp	
#define name15_sub  addadd
#endif  

#if(Number_All >= 17)     // 长D
#define name16  	"LONGD"      
#define name16_num  longstraightd
#define name16_sub  addadd
#endif   

#if(Number_All >= 18)          // 普通P
#define name17    	"STP"      
#define name17_num  straightp
#define name17_sub addadd
#endif      

#if(Number_All >= 19)           
#define name18    	"STD"   //  普通D
#define name18_num  straightd
#define name18_sub addadd
#endif    


#if(Number_All >= 20)      //小S P
#define name19   	"SSP"      
#define name19_num  smallsp
#define name19_sub  addadd
#endif  

#if(Number_All >= 21)        //小S D
#define name20   	"SSD"      
#define name20_num  smallsd
#define name20_sub  addadd
#endif    

#if(Number_All >= 22)
#define name21    	"LP"           //左转P
#define name21_num   leftp
#define name21_sub   addadd
#endif   

#if(Number_All >= 23)
#define name22    	"LD"      //左转D
#define name22_num   leftd
#define name22_sub  addadd
#endif  

 #if(Number_All >= 24)             //   右转P
#define name23  	"RP"      
#define name23_num  rightp
#define name23_sub  addadd
#endif 

 #if(Number_All >= 25)             //右转D
#define name24    	"RD"
#define name24_num  rightd
#define name24_sub  addadd
#endif    

#if(Number_All >= 26)
#define name25    	"IDJ1"      //环岛1打角
#define name25_num  Ispeed1dj
#define name25_sub  addadd
#endif    

#if(Number_All >= 27)
#define name26    	"IDJ2"         //环岛2打角
#define name26_num Ispeed2dj
#define name26_sub  addadd
#endif    

#if(Number_All >= 28)
#define name27    	"IDJ3"     //环岛3打角  
#define name27_num  Ispeed3dj
#define name27_sub  addadd
#endif    

#if(Number_All >= 29)
#define name28    	"IDJ4"       //环岛4打角
#define name28_num  Ispeed4dj
#define name28_sub  addadd
#endif    

#if(Number_All >= 30)
#define name29    	"ISPEED1"      //环岛1速度
#define name29_num  Ispeed1
#define name29_sub  addadd
#endif    

#if(Number_All >= 31)           //环岛2速度
#define name30    	"ISPEED2"
#define name30_num Ispeed2
#define name30_sub  addadd
#endif   
#if(Number_All >= 32)           //环岛3速度
#define name31    	"ISPEED3"     
#define name31_num  Ispeed3
#define name31_sub  addadd
#endif   
#if(Number_All >= 33)           //环岛4速度
#define name32    	"ISPEED4"      
#define name32_num Ispeed4
#define name32_sub  addadd
#endif   
#if(Number_All >= 34)         //无  
#define name33    	"LSS-SPEED"      
#define name33_num   longSS_speed
#define name33_sub addadd
#endif  
#if(Number_All >= 35)   //大S开关
#define name34    	"BigS-OP"      
#define name34_num  Mid_S_Switch  
#define name34_sub  addadd
#endif   
#if(Number_All >= 36)   //大S打角
#define name35    	"BS-DJ"      
#define name35_num  Bigs_dj  
#define name35_sub  addadd
#endif   
#if(Number_All >= 37)  //大Sp
#define name36    	"BsP"      
#define name36_num  Bigsp  
#define name36_sub  addadd
#endif   
#if(Number_All >= 38)//大SD
#define name37    	"BsD"      
#define name37_num  Bigsd  
#define name37_sub  addadd
#endif   
#if(Number_All >= 39) //大S速度
#define name38    	"BSspeed"      
#define name38_num  speedBigs  
#define name38_sub  addadd 
#endif    
#if(Number_All >= 40) //坡道速度
#define name39    	"Pospeed"      
#define name39_num  po_speed  
#define name39_sub  addadd 
#endif   
#if(Number_All >= 41) 
#define name40    	"1Huan "    //号码越大环越大
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
#if(Number_All >= 56)//重新加载 始终放在最后一行 不存储FLASH  更改菜单时需要更改
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
