#include "headfile.h"
#include "menu.h"



struct Menu_Select Menu_name[Number_All];

int startstart=0;       
int memory=0;	//用来记忆第一行按键状态
int runmodeflash[500];   //用来专门存储runmode的flash变量
int data0[500];          //用来专门存储runmode0其余的flash变量
int data1[500];          //用来专门存储runmode1其余的flash变量
int data2[500];          //用来专门存储runmode2其余的flash变量
int data3[500];          //用来专门存储runmode2其余的flash变量
int protcnt=0;

extern uint8_t poflag;
void menu(void)  //菜单
{
static uint8_t hang = 1;
uint8_t final_hang = 0, page = 0, i;
FLASH_Init();
FLASH_ReadByte(179*4096,Number_All*4,(uint8_t*)runmodeflash);
FLASH_ReadByte(180*4096,Number_All*4,(uint8_t*)data0);
FLASH_ReadByte(181*4096,Number_All*4,(uint8_t*)data1);
FLASH_ReadByte(182*4096,Number_All*4,(uint8_t*)data2);
FLASH_ReadByte(183*4096,Number_All*4,(uint8_t*)data3);
runmode=runmodeflash[0];	      
mode_mode=runmodeflash[1];	       
slowstart=runmodeflash[2];	      
protect_stop=runmodeflash[3];	        
huandaocntmax=runmodeflash[4];	        
slopecntmax=runmodeflash[5];	      
blockcntmax=runmodeflash[6];	      
yuzhi=runmodeflash[7];	    
qipaoflag=runmodeflash[8];	
huandao_type[0]=runmodeflash[9];
huandao_type[1]=runmodeflash[10];
huandao_type[2]=runmodeflash[11];
huandao_type[3]=runmodeflash[12];
dianbo_switch=runmodeflash[13];
//数据初始化  更改菜单时需要改！！
if(runmodeflash[0]==1)//runmode1
 {       
dajiao=data1[8];	    
longspeed=data1[9];	     
shortspeed=data1[10];	    
speedstraight=data1[11];	 
speedturn=data1[12];	    

longstraightp=data1[14];	
longstraightd=data1[15];	
straightp=data1[16];	   
straightd=data1[17];	  
smallsp=data1[18];	     
smallsd=data1[19];	   
leftp=data1[20];	     
leftd=data1[21];	    
rightp=data1[22];	    
rightd=data1[23];	      
Ispeed1=data1[24];	   
Ispeed2=data1[25];	
Ispeed3=data1[26];	   
Ispeed4=data1[27];	
Ispeed1dj=data1[28];
Ispeed2dj=data1[29];
Ispeed3dj=data1[30];
Ispeed4dj=data1[31];
 Bigsp=data1[32];      //大S P
 Bigsd=data1[33];      //大S D
 Bigs_dj=data1[34];//大S打角行
 Mid_S_Switch=data1[35];//大S开关
 speedBigs=data1[36]    ;//大S速度
 superspeed=data1[37];
 po_speed=data1[38];
IkP1=data1[39];
IkP2=data1[40];
IkP3=data1[41];
IkP4=data1[42];
IkD1=data1[43];
IkD2=data1[44];
IkD3=data1[45];
IkD4=data1[46];
longSS_speed=data1[47];
blockspeed=data1[48];
}
 
else if(runmodeflash[0]==2)//runmode2
{ 
dajiao=data2[8];	       
longspeed=data2[9];	     
shortspeed=data2[10];	    
speedstraight=data2[11];	 
speedturn=data2[12];	    
longstraightp=data2[14];	
longstraightd=data2[15];	
straightp=data2[16];	   
straightd=data2[17];	  
smallsp=data2[18];	     
smallsd=data2[19];	   
leftp=data2[20];	     
leftd=data2[21];	    
rightp=data2[22];	    
rightd=data2[23];	      
Ispeed1=data2[24];	   
Ispeed2=data2[25];	
Ispeed3=data2[26];	   
Ispeed4=data2[27];	
Ispeed1dj=data2[28];
Ispeed2dj=data2[29];
Ispeed3dj=data2[30];
Ispeed4dj=data2[31];
 Bigsp=data2[32];      //大S P
 Bigsd=data2[33];      //大S D
 Bigs_dj=data2[34];//大S打角行
 Mid_S_Switch=data2[35];//大S开关
 speedBigs=data2[36];    //大S速度
 superspeed=data2[37];         
  po_speed=data2[38];
IkP1=data2[39];
IkP2=data2[40];
IkP3=data2[41];
IkP4=data2[42];
IkD1=data2[43];
IkD2=data2[44];
IkD3=data2[45];
IkD4=data2[46];
longSS_speed=data2[47];
blockspeed=data2[48];
}
else if(runmodeflash[0]==3)//runmode1
 {       
dajiao=data3[8];	    
longspeed=data3[9];	     
shortspeed=data3[10];	    
speedstraight=data3[11];	 
speedturn=data3[12];	    
longstraightp=data3[14];	
longstraightd=data3[15];	
straightp=data3[16];	   
straightd=data3[17];	  
smallsp=data3[18];	     
smallsd=data3[19];	   
leftp=data3[20];	     
leftd=data3[21];	    
rightp=data3[22];	    
rightd=data3[23];	      
Ispeed1=data3[24];	   
Ispeed2=data3[25];	
Ispeed3=data3[26];	   
Ispeed4=data3[27];	
Ispeed1dj=data3[28];
Ispeed2dj=data3[29];
Ispeed3dj=data3[30];
Ispeed4dj=data3[31];
 Bigsp=data3[32];      //大S P
 Bigsd=data3[33];      //大S D
 Bigs_dj=data3[34];//大S打角行
 Mid_S_Switch=data3[35];//大S开关
 speedBigs=data3[36]    ;//大S速度
 superspeed=data3[37];
 po_speed=data3[38];
IkP1=data3[39];
IkP2=data3[40];
IkP3=data3[41];
IkP4=data3[42];
IkD1=data3[43];
IkD2=data3[44];
IkD3=data3[45];
IkD4=data3[46];
longSS_speed=data3[47];
blockspeed=data3[48];
}
else
{

dajiao=data0[8];	       
longspeed=data0[9];	     
shortspeed=data0[10];	    
speedstraight=data0[11];	 
speedturn=data0[12];	    
longstraightp=data0[14];	
longstraightd=data0[15];	
straightp=data0[16];	   
straightd=data0[17];	  
smallsp=data0[18];	     
smallsd=data0[19];	   
leftp=data0[20];	     
leftd=data0[21];	    
rightp=data0[22];	    
rightd=data0[23];	      
Ispeed1=data0[24];	   
Ispeed2=data0[25];	
Ispeed3=data0[26];	   
Ispeed4=data0[27];	
Ispeed1dj=data0[28];
Ispeed2dj=data0[29];
Ispeed3dj=data0[30];
Ispeed4dj=data0[31];	
 Bigsp=data0[32];      //大S P
 Bigsd=data0[33];      //大S D
 Bigs_dj=data0[34];//大S打角行
 Mid_S_Switch=data0[35];//大S开关
 speedBigs=data0[36];    //大S速度
superspeed=data0[37];	         
  po_speed=data0[38];
IkP1=data0[39];
IkP2=data0[40];
IkP3=data0[41];
IkP4=data0[42];
IkD1=data0[43];
IkD2=data0[44];
IkD3=data0[45];
IkD4=data0[46];
longSS_speed=data0[47];
blockspeed=data0[48];
}
		

//菜单显示 名称以及参数 初始化  更改菜单时需要改！！
#if (Number_All>= 1)
  strcpy(Menu_name[0].name, name0);
  Menu_name[0].num = name0_num;
  Menu_name[0].sub = name0_sub;
#endif

#if (Number_All >= 2)
  strcpy(Menu_name[1].name, name1);
  Menu_name[1].num = name1_num;
  Menu_name[1].sub = name1_sub;
#endif

#if (Number_All >= 3)
  strcpy(Menu_name[2].name, name2);
  Menu_name[2].num = name2_num;
  Menu_name[2].sub = name2_sub;
#endif

#if (Number_All >= 4)
  strcpy(Menu_name[3].name, name3);
  Menu_name[3].num = name3_num;
  Menu_name[3].sub = name3_sub;
#endif

#if (Number_All >= 5)
  strcpy(Menu_name[4].name, name4);
  Menu_name[4].num = name4_num;
  Menu_name[4].sub = name4_sub;
#endif

#if (Number_All >= 6)
  strcpy(Menu_name[5].name, name5);
  Menu_name[5].num = name5_num;
  Menu_name[5].sub = name5_sub;
#endif

#if (Number_All >= 7)
  strcpy(Menu_name[6].name, name6);
  Menu_name[6].num = name6_num;
  Menu_name[6].sub = name6_sub;
#endif

#if (Number_All >= 8)
  strcpy(Menu_name[7].name, name7);
  Menu_name[7].num = name7_num;
  Menu_name[7].sub = name7_sub;
#endif

#if (Number_All >= 9)
  strcpy(Menu_name[8].name, name8);
  Menu_name[8].num = name8_num;
  Menu_name[8].sub = name8_sub;
#endif

#if (Number_All >= 10)
  strcpy(Menu_name[9].name, name9);
  Menu_name[9].num = name9_num;
  Menu_name[9].sub = name9_sub;
#endif

#if (Number_All >= 11)
  strcpy(Menu_name[10].name, name10);
  Menu_name[10].num = name10_num;
  Menu_name[10].sub = name10_sub;
#endif

#if (Number_All >= 12)
  strcpy(Menu_name[11].name, name11);
  Menu_name[11].num = name11_num;
  Menu_name[11].sub = name11_sub;
#endif

#if (Number_All >= 13)
  strcpy(Menu_name[12].name, name12);
  Menu_name[12].num = name12_num;
  Menu_name[12].sub = name12_sub;
#endif

#if (Number_All >= 14)
  strcpy(Menu_name[13].name, name13);
  Menu_name[13].num = name13_num;
  Menu_name[13].sub = name13_sub;
#endif

#if (Number_All >= 15)
  strcpy(Menu_name[14].name, name14);
  Menu_name[14].num = name14_num;
  Menu_name[14].sub = name14_sub;
#endif

#if (Number_All >= 16)
  strcpy(Menu_name[15].name, name15);
  Menu_name[15].num = name15_num;
  Menu_name[15].sub = name15_sub;
#endif

#if (Number_All >= 17)
  strcpy(Menu_name[16].name, name16);
  Menu_name[16].num = name16_num;
  Menu_name[16].sub = name16_sub;
#endif

#if (Number_All >= 18)
  strcpy(Menu_name[17].name, name17);
  Menu_name[17].num = name17_num;
  Menu_name[17].sub = name17_sub;
#endif

#if (Number_All >= 19)
  strcpy(Menu_name[18].name, name18);
  Menu_name[18].num = name18_num;
  Menu_name[18].sub = name18_sub;
#endif

#if (Number_All >= 20)
  strcpy(Menu_name[19].name, name19);
  Menu_name[19].num = name19_num;
  Menu_name[19].sub = name19_sub;
#endif

#if (Number_All >= 21)
  strcpy(Menu_name[20].name, name20);
  Menu_name[20].num = name20_num;
  Menu_name[20].sub = name20_sub;
#endif

#if (Number_All >= 22)
  strcpy(Menu_name[21].name, name21);
  Menu_name[21].num = name21_num;
  Menu_name[21].sub = name21_sub;
#endif

#if (Number_All >= 23)
  strcpy(Menu_name[22].name, name22);
  Menu_name[22].num = name22_num;
  Menu_name[22].sub = name22_sub;
#endif

#if (Number_All >= 24)
  strcpy(Menu_name[23].name, name23);
  Menu_name[23].num = name23_num;
  Menu_name[23].sub = name23_sub;
#endif

#if (Number_All >= 25)
  strcpy(Menu_name[24].name, name24);
  Menu_name[24].num = name24_num;
  Menu_name[24].sub = name24_sub;
#endif

#if (Number_All >= 26)
  strcpy(Menu_name[25].name, name25);
  Menu_name[25].num = name25_num;
  Menu_name[25].sub = name25_sub;
#endif

#if (Number_All >= 27)
  strcpy(Menu_name[26].name, name26);
  Menu_name[26].num = name26_num;
  Menu_name[26].sub = name26_sub;
#endif

#if (Number_All >= 28)
 strcpy(Menu_name[27].name, name27);
  Menu_name[27].num = name27_num;
  Menu_name[27].sub = name27_sub;
#endif

#if (Number_All >= 29)
  strcpy(Menu_name[28].name, name28);
  Menu_name[28].num = name28_num;
  Menu_name[28].sub = name28_sub;
#endif

#if (Number_All >= 30)
  strcpy(Menu_name[29].name, name29);
  Menu_name[29].num = name29_num;
  Menu_name[29].sub = name29_sub;
#endif

#if (Number_All >= 31)
  strcpy(Menu_name[30].name, name30);
  Menu_name[30].num = name30_num;
  Menu_name[30].sub = name30_sub;
#endif

#if (Number_All >= 32)
  strcpy(Menu_name[31].name, name31);
  Menu_name[31].num = name31_num;
  Menu_name[31].sub = name31_sub;
#endif
#if (Number_All >= 33)
  strcpy(Menu_name[32].name, name32);
  Menu_name[32].num = name32_num;
  Menu_name[32].sub = name32_sub;
#endif
#if (Number_All >= 34)
  strcpy(Menu_name[33].name, name33);
  Menu_name[33].num = name33_num;
  Menu_name[33].sub = name33_sub;
#endif
#if (Number_All >= 35)
  strcpy(Menu_name[34].name, name34);
  Menu_name[34].num = name34_num;
  Menu_name[34].sub = name34_sub;
#endif

#if (Number_All >= 36)
  strcpy(Menu_name[35].name, name35);
  Menu_name[35].num = name35_num;
  Menu_name[35].sub = name35_sub;
#endif
#if (Number_All >= 37)
  strcpy(Menu_name[36].name, name36);
  Menu_name[36].num = name36_num;
  Menu_name[36].sub = name36_sub;
#endif
#if (Number_All >= 38)
  strcpy(Menu_name[37].name, name37);
  Menu_name[37].num = name37_num;
  Menu_name[37].sub = name37_sub;
#endif
#if (Number_All >= 39)
  strcpy(Menu_name[38].name, name38);
  Menu_name[38].num = name38_num;
  Menu_name[38].sub = name38_sub;
#endif

#if (Number_All >= 40)
  strcpy(Menu_name[39].name, name39);
  Menu_name[39].num = name39_num;
  Menu_name[39].sub = name39_sub;
#endif

#if (Number_All >= 41)
  strcpy(Menu_name[40].name, name40);
  Menu_name[40].num = name40_num;
  Menu_name[40].sub = name40_sub;
#endif
#if (Number_All >= 42)
  strcpy(Menu_name[41].name, name41);
  Menu_name[41].num = name41_num;
  Menu_name[41].sub = name41_sub;
#endif
#if (Number_All >= 43)
  strcpy(Menu_name[42].name, name42);
  Menu_name[42].num = name42_num;
  Menu_name[42].sub = name42_sub;
#endif
#if (Number_All >= 44)
  strcpy(Menu_name[43].name, name43);
  Menu_name[43].num = name43_num;
  Menu_name[43].sub = name43_sub;
#endif
#if (Number_All >= 45)
  strcpy(Menu_name[44].name, name44);
  Menu_name[44].num = name44_num;
  Menu_name[44].sub = name44_sub;
#endif
#if (Number_All >= 46)
  strcpy(Menu_name[45].name, name45);
  Menu_name[45].num = name45_num;
  Menu_name[45].sub = name45_sub;
#endif
#if (Number_All >= 47)
  strcpy(Menu_name[46].name, name46);
  Menu_name[46].num = name46_num;
  Menu_name[46].sub = name46_sub;
#endif
#if (Number_All >= 48)
  strcpy(Menu_name[47].name, name47);
  Menu_name[47].num = name47_num;
  Menu_name[47].sub = name47_sub;
#endif
#if (Number_All >= 49)
  strcpy(Menu_name[48].name, name48);
  Menu_name[48].num = name48_num;
  Menu_name[48].sub = name48_sub;
#endif
#if (Number_All >= 50)
  strcpy(Menu_name[49].name, name49);
  Menu_name[49].num = name49_num;
  Menu_name[49].sub = name49_sub;
#endif
#if (Number_All >= 51)
  strcpy(Menu_name[50].name, name50);
  Menu_name[50].num = name50_num;
  Menu_name[50].sub = name50_sub;
#endif
#if (Number_All >= 52)
  strcpy(Menu_name[51].name, name51);
  Menu_name[51].num = name51_num;
  Menu_name[51].sub = name51_sub;
#endif
#if (Number_All >= 53)
  strcpy(Menu_name[52].name, name52);
  Menu_name[52].num = name52_num;
  Menu_name[52].sub = name52_sub;
#endif
#if (Number_All >= 54)
  strcpy(Menu_name[53].name, name53);
  Menu_name[53].num = name53_num;
  Menu_name[53].sub = name53_sub;
#endif
#if (Number_All >= 55)
  strcpy(Menu_name[54].name, name54);
  Menu_name[54].num = name54_num;
  Menu_name[54].sub = name54_sub;
#endif
#if (Number_All >= 56)
  strcpy(Menu_name[55].name, name55);
  Menu_name[55].num = name55_num;
  Menu_name[55].sub = name55_sub;
#endif
#if (Number_All)
OLED_Clear();
while (1)//主菜单
{
    memory=Menu_name[0].num;
    if (Key_Up == 0) //上移
    {
      DelayMs(100);
      if (Key_Up == 0)
      {
        hang--;
        if (hang == 0)
          hang = Number_All;
        OLED_Clear();
      }
    }

    if (Key_Down == 0) //下移
    {
      DelayMs(100);
      if (Key_Down == 0)
      {
        hang++;
        if (hang == Number_All + 1)
          hang = 1;
        OLED_Clear();
      }
    }

    if (Key_Add == 0) //加
    {
      DelayMs(100);
      if (Key_Add == 0)
        Menu_name[hang - 1].num = Menu_name[hang - 1].num + Menu_name[hang - 1].sub;
			
			
    }

    if (Key_Minus == 0) //减
    {
      DelayMs(100);
      if (Key_Minus == 0)
      {
        if (Menu_name[hang - 1].num - Menu_name[hang - 1].sub >= 0)
        {
          Menu_name[hang - 1].num = Menu_name[hang - 1].num - Menu_name[hang - 1].sub;
        }
        else
        {
          Menu_name[hang - 1].num = 0;
        }
      }
    }

    OLED_Write_Char(0, (hang - 1) % 4 * 2, 43); //箭头
    if ((Number_All - 1) / 4 > (hang - 1) / 4)
    {
      page = (hang - 1) / 4;
      final_hang = 4;
    }

    else
    {
      page = (Number_All - 1) / 4;
      final_hang = Number_All % 4;
      if (final_hang == 0)
        final_hang = 4;
    }
		//改变模式重载参数   更改菜单时需要改！！ 
		if(Menu_name[0].num==0&&hang==1&&(Key_Minus==0||Key_Add==0)&&memory!=Menu_name[0].num)//更改菜单时需要改！！
	   {
runmode=0;	      
//这里的变量的相当于name0_num等 因为define过了
dajiao=data0[8];	       
longspeed=data0[9];	     
shortspeed=data0[10];	    
speedstraight=data0[11];	 
speedturn=data0[12];	    
longstraightp=data0[14];	
longstraightd=data0[15];	
straightp=data0[16];	   
straightd=data0[17];	  
smallsp=data0[18];	     
smallsd=data0[19];	   
leftp=data0[20];	     
leftd=data0[21];	    
rightp=data0[22];	    
rightd=data0[23];	  
Ispeed1=data0[24];	   
Ispeed2=data0[25];	
Ispeed3=data0[26];	   
Ispeed4=data0[27];	
Ispeed1dj=data0[28];
Ispeed2dj=data0[29];
Ispeed3dj=data0[30];
Ispeed4dj=data0[31];
 Bigsp=data0[32];      //大S P
 Bigsd=data0[33];      //大S D
 Bigs_dj=data0[34];//大S打角行
 Mid_S_Switch=data0[35];//大S开关
 speedBigs=data0[36];    //大S速度
  superspeed=data0[37];        
po_speed=data0[38];
 IkP1=data0[39];
 IkP2=data0[40];
 IkP3=data0[41];
 IkP4=data0[42];
 IkD1=data0[43];
 IkD2=data0[44];
 IkD3=data0[45];
 IkD4=data0[46];
longSS_speed=data0[47];
blockspeed=data0[48];
		 }
	 

		if(Menu_name[0].num==1&&hang==1&&(Key_Minus==0||Key_Add==0)&&memory!=Menu_name[0].num)//更改菜单时需要改！！
	   {
runmode=1;	          
dajiao=data1[8];	    
longspeed=data1[9];	     
shortspeed=data1[10];	    
speedstraight=data1[11];	 
speedturn=data1[12];	    
longstraightp=data1[14];	
longstraightd=data1[15];	
straightp=data1[16];	   
straightd=data1[17];	  
smallsp=data1[18];	     
smallsd=data1[19];	   
leftp=data1[20];	     
leftd=data1[21];	    
rightp=data1[22];	    
rightd=data1[23];	      
Ispeed1=data1[24];	   
Ispeed2=data1[25];	
Ispeed3=data1[26];	   
Ispeed4=data1[27];	
Ispeed1dj=data1[28];
Ispeed2dj=data1[29];
Ispeed3dj=data1[30];
Ispeed4dj=data1[31];
 Bigsp=data1[32];      //大S P
 Bigsd=data1[33];      //大S D
 Bigs_dj=data1[34];//大S打角行
 Mid_S_Switch=data1[35];//大S开关
 speedBigs=data1[36];    //大S速度
 superspeed=data1[37];         
 po_speed=data1[38];
 IkP1=data1[39];
 IkP2=data1[40];
 IkP3=data1[41];
 IkP4=data1[42];
 IkD1=data1[43];
 IkD2=data1[44];
 IkD3=data1[45];
 IkD4=data1[46];
longSS_speed=data1[47];
blockspeed=data1[48];

		 }
		if(Menu_name[0].num==2&&hang==1&&(Key_Minus==0||Key_Add==0)&&memory!=Menu_name[0].num)//更改菜单时需要改！！
	   {
runmode=2;	             
dajiao=data2[8];	       
longspeed=data2[9];	     
shortspeed=data2[10];	    
speedstraight=data2[11];	 
speedturn=data2[12];	    
longstraightp=data2[14];	
longstraightd=data2[15];	
straightp=data2[16];	   
straightd=data2[17];	  
smallsp=data2[18];	     
smallsd=data2[19];	   
leftp=data2[20];	     
leftd=data2[21];	    
rightp=data2[22];	    
rightd=data2[23];	      
Ispeed1=data2[24];	   
Ispeed2=data2[25];	
Ispeed3=data2[26];	   
Ispeed4=data2[27];	
Ispeed1dj=data2[28];
Ispeed2dj=data2[29];
Ispeed3dj=data2[30];
Ispeed4dj=data2[31];	
 Bigsp=data2[32];      //大S P
 Bigsd=data2[33];      //大S D
 Bigs_dj=data2[34];//大S打角行
 Mid_S_Switch=data2[35];//大S开关
 speedBigs=data2[36];    //大S速度
 superspeed=data2[37];         
 po_speed=data2[38];
 IkP1=data2[39];
 IkP2=data2[40];
 IkP3=data2[41];
 IkP4=data2[42];
 IkD1=data2[43];
 IkD2=data2[44];
 IkD3=data2[45];
 IkD4=data2[46];
longSS_speed=data2[47];
blockspeed=data2[48];

		 }
    
    if(Menu_name[0].num==3&&hang==1&&(Key_Minus==0||Key_Add==0)&&memory!=Menu_name[0].num)//更改菜单时需要改！！
	   {
runmode=3;	             
dajiao=data3[8];	       
longspeed=data3[9];	     
shortspeed=data3[10];	    
speedstraight=data3[11];	 
speedturn=data3[12];	    
longstraightp=data3[14];	
longstraightd=data3[15];	
straightp=data3[16];	   
straightd=data3[17];	  
smallsp=data3[18];	     
smallsd=data3[19];	   
leftp=data3[20];	     
leftd=data3[21];	    
rightp=data3[22];	    
rightd=data3[23];	      
Ispeed1=data3[24];	   
Ispeed2=data3[25];	
Ispeed3=data3[26];	   
Ispeed4=data3[27];	
Ispeed1dj=data3[28];
Ispeed2dj=data3[29];
Ispeed3dj=data3[30];
Ispeed4dj=data3[31];	
 Bigsp=data3[32];      //大S P
 Bigsd=data3[33];      //大S D
 Bigs_dj=data3[34];//大S打角行
 Mid_S_Switch=data3[35];//大S开关
 speedBigs=data3[36];    //大S速度
 superspeed=data3[37];         
 po_speed=data3[38];
 IkP1=data3[39];
 IkP2=data3[40];
 IkP3=data3[41];
 IkP4=data3[42];
 IkD1=data3[43];
 IkD2=data3[44];
 IkD3=data3[45];
 IkD4=data3[46];
longSS_speed=data3[47];
blockspeed=data3[48];

		 }
    

		 
		 //模式改变，参数重载并显示到菜单上  ：写到一起便于菜单的更改  更改菜单时需要改！！
if(hang==1&&(Key_Minus==0||Key_Add==0)&&memory!=Menu_name[0].num)
{
#if (Number_All>= 1)
  strcpy(Menu_name[0].name, name0);
  Menu_name[0].num = name0_num;
  Menu_name[0].sub = name0_sub;
#endif

#if (Number_All >= 2)
  strcpy(Menu_name[1].name, name1);
  Menu_name[1].num = name1_num;
  Menu_name[1].sub = name1_sub;
#endif

#if (Number_All >= 3)
  strcpy(Menu_name[2].name, name2);
  Menu_name[2].num = name2_num;
  Menu_name[2].sub = name2_sub;
#endif

#if (Number_All >= 4)
  strcpy(Menu_name[3].name, name3);
  Menu_name[3].num = name3_num;
  Menu_name[3].sub = name3_sub;
#endif

#if (Number_All >= 5)
  strcpy(Menu_name[4].name, name4);
  Menu_name[4].num = name4_num;
  Menu_name[4].sub = name4_sub;
#endif

#if (Number_All >= 6)
  strcpy(Menu_name[5].name, name5);
  Menu_name[5].num = name5_num;
  Menu_name[5].sub = name5_sub;
#endif

#if (Number_All >= 7)
  strcpy(Menu_name[6].name, name6);
  Menu_name[6].num = name6_num;
  Menu_name[6].sub = name6_sub;
#endif

#if (Number_All >= 8)
  strcpy(Menu_name[7].name, name7);
  Menu_name[7].num = name7_num;
  Menu_name[7].sub = name7_sub;
#endif

#if (Number_All >= 9)
  strcpy(Menu_name[8].name, name8);
  Menu_name[8].num = name8_num;
  Menu_name[8].sub = name8_sub;
#endif

#if (Number_All >= 10)
  strcpy(Menu_name[9].name, name9);
  Menu_name[9].num = name9_num;
  Menu_name[9].sub = name9_sub;
#endif

#if (Number_All >= 11)
  strcpy(Menu_name[10].name, name10);
  Menu_name[10].num = name10_num;
  Menu_name[10].sub = name10_sub;
#endif

#if (Number_All >= 12)
  strcpy(Menu_name[11].name, name11);
  Menu_name[11].num = name11_num;
  Menu_name[11].sub = name11_sub;
#endif

#if (Number_All >= 13)
  strcpy(Menu_name[12].name, name12);
  Menu_name[12].num = name12_num;
  Menu_name[12].sub = name12_sub;
#endif

#if (Number_All >= 14)
  strcpy(Menu_name[13].name, name13);
  Menu_name[13].num = name13_num;
  Menu_name[13].sub = name13_sub;
#endif

#if (Number_All >= 15)
  strcpy(Menu_name[14].name, name14);
  Menu_name[14].num = name14_num;
  Menu_name[14].sub = name14_sub;
#endif

#if (Number_All >= 16)
  strcpy(Menu_name[15].name, name15);
  Menu_name[15].num = name15_num;
  Menu_name[15].sub = name15_sub;
#endif

#if (Number_All >= 17)
  strcpy(Menu_name[16].name, name16);
  Menu_name[16].num = name16_num;
  Menu_name[16].sub = name16_sub;
#endif

#if (Number_All >= 18)
  strcpy(Menu_name[17].name, name17);
  Menu_name[17].num = name17_num;
  Menu_name[17].sub = name17_sub;
#endif

#if (Number_All >= 19)
  strcpy(Menu_name[18].name, name18);
  Menu_name[18].num = name18_num;
  Menu_name[18].sub = name18_sub;
#endif

#if (Number_All >= 20)
  strcpy(Menu_name[19].name, name19);
  Menu_name[19].num = name19_num;
  Menu_name[19].sub = name19_sub;
#endif

#if (Number_All >= 21)
  strcpy(Menu_name[20].name, name20);
  Menu_name[20].num = name20_num;
  Menu_name[20].sub = name20_sub;
#endif

#if (Number_All >= 22)
  strcpy(Menu_name[21].name, name21);
  Menu_name[21].num = name21_num;
  Menu_name[21].sub = name21_sub;
#endif

#if (Number_All >= 23)
  strcpy(Menu_name[22].name, name22);
  Menu_name[22].num = name22_num;
  Menu_name[22].sub = name22_sub;
#endif

#if (Number_All >= 24)
  strcpy(Menu_name[23].name, name23);
  Menu_name[23].num = name23_num;
  Menu_name[23].sub = name23_sub;
#endif

#if (Number_All >= 25)
  strcpy(Menu_name[24].name, name24);
  Menu_name[24].num = name24_num;
  Menu_name[24].sub = name24_sub;
#endif

#if (Number_All >= 26)
  strcpy(Menu_name[25].name, name25);
  Menu_name[25].num = name25_num;
  Menu_name[25].sub = name25_sub;
#endif

#if (Number_All >= 27)
  strcpy(Menu_name[26].name, name26);
  Menu_name[26].num = name26_num;
  Menu_name[26].sub = name26_sub;
#endif

#if (Number_All >= 28)
  strcpy(Menu_name[27].name, name27);
  Menu_name[27].num = name27_num;
  Menu_name[27].sub = name27_sub;
#endif

#if (Number_All >= 29)
  strcpy(Menu_name[28].name, name28);
  Menu_name[28].num = name28_num;
  Menu_name[28].sub = name28_sub;
#endif

#if (Number_All >= 30)
  strcpy(Menu_name[29].name, name29);
  Menu_name[29].num = name29_num;
  Menu_name[29].sub = name29_sub;
#endif
	  
#if (Number_All >= 31)
  strcpy(Menu_name[30].name, name30);
  Menu_name[30].num = name30_num;
  Menu_name[30].sub = name30_sub;
#endif
#if (Number_All >= 32)
  strcpy(Menu_name[31].name, name31);
  Menu_name[31].num = name31_num;
  Menu_name[31].sub = name31_sub;
#endif
#if (Number_All >= 33)
  strcpy(Menu_name[32].name, name32);
  Menu_name[32].num = name32_num;
  Menu_name[32].sub = name32_sub;
#endif
#if (Number_All >= 34)
  strcpy(Menu_name[33].name, name33);
  Menu_name[33].num = name33_num;
  Menu_name[33].sub = name33_sub;
#endif
#if (Number_All >= 35)
  strcpy(Menu_name[34].name, name34);
  Menu_name[34].num = name34_num;
  Menu_name[34].sub = name34_sub;
#endif

#if (Number_All >= 36)
  strcpy(Menu_name[35].name, name35);
  Menu_name[35].num = name35_num;
  Menu_name[35].sub = name35_sub;
#endif	

#if (Number_All >= 37)
  strcpy(Menu_name[36].name, name36);
  Menu_name[36].num = name36_num;
  Menu_name[36].sub = name36_sub;
#endif
#if (Number_All >= 38)
  strcpy(Menu_name[37].name, name37);
  Menu_name[37].num = name37_num;
  Menu_name[37].sub = name37_sub;
#endif
#if (Number_All >= 39)
  strcpy(Menu_name[38].name, name38);
  Menu_name[38].num = name38_num;
  Menu_name[38].sub = name38_sub;
#endif

#if (Number_All >= 40)
  strcpy(Menu_name[39].name, name39);
  Menu_name[39].num = name39_num;
  Menu_name[39].sub = name39_sub;
#endif
#if (Number_All >= 41)
  strcpy(Menu_name[40].name, name40);
  Menu_name[40].num = name40_num;
  Menu_name[40].sub = name40_sub;
#endif
#if (Number_All >= 42)
  strcpy(Menu_name[41].name, name41);
  Menu_name[41].num = name41_num;
  Menu_name[41].sub = name41_sub;
#endif
#if (Number_All >= 43)
  strcpy(Menu_name[42].name, name42);
  Menu_name[42].num = name42_num;
  Menu_name[42].sub = name42_sub;
#endif
#if (Number_All >= 44)
  strcpy(Menu_name[43].name, name43);
  Menu_name[43].num = name43_num;
  Menu_name[43].sub = name43_sub;
#endif
#if (Number_All >= 45)
  strcpy(Menu_name[44].name, name44);
  Menu_name[44].num = name44_num;
  Menu_name[44].sub = name44_sub;
#endif
#if (Number_All >= 46)
  strcpy(Menu_name[45].name, name45);
  Menu_name[45].num = name45_num;
  Menu_name[45].sub = name45_sub;
#endif
#if (Number_All >= 47)
  strcpy(Menu_name[46].name, name46);
  Menu_name[46].num = name46_num;
  Menu_name[46].sub = name46_sub;
#endif
#if (Number_All >= 48)
  strcpy(Menu_name[47].name, name47);
  Menu_name[47].num = name47_num;
  Menu_name[47].sub = name47_sub;
#endif
#if (Number_All >= 49)
  strcpy(Menu_name[48].name, name48);
  Menu_name[48].num = name48_num;
  Menu_name[48].sub = name48_sub;
#endif
#if (Number_All >= 50)
  strcpy(Menu_name[49].name, name49);
  Menu_name[49].num = name49_num;
  Menu_name[49].sub = name49_sub;
#endif
#if (Number_All >= 51)
  strcpy(Menu_name[50].name, name50);
  Menu_name[50].num = name50_num;
  Menu_name[50].sub = name50_sub;
#endif
#if (Number_All >= 52)
  strcpy(Menu_name[51].name, name51);
  Menu_name[51].num = name51_num;
  Menu_name[51].sub = name51_sub;
#endif
#if (Number_All >= 53)
  strcpy(Menu_name[52].name, name52);
  Menu_name[52].num = name52_num;
  Menu_name[52].sub = name52_sub;
#endif
#if (Number_All >= 54)
  strcpy(Menu_name[53].name, name53);
  Menu_name[53].num = name53_num;
  Menu_name[53].sub = name53_sub;
#endif
#if (Number_All >= 55)
  strcpy(Menu_name[54].name, name54);
  Menu_name[54].num = name54_num;
  Menu_name[54].sub = name54_sub;
#endif
#if (Number_All >= 56)
  strcpy(Menu_name[55].name, name55);
  Menu_name[55].num = name55_num;
  Menu_name[55].sub = name55_sub;
#endif
}
	if(Menu_name[Number_All-1].num==1)//flash快速重置数据  有个bug快速设置flah后不能更改参数值只能先保存退出
		 {
			 for(i=0;i< Number_All-1;i++)
			 {
				 Menu_name[i].num= flash_memory0[i];
			 }
		 }
		 if(Menu_name[Number_All-1].num==2)
		 {
			 for(i=0;i< Number_All-1;i++)
			 {
				 Menu_name[i].num= flash_memory1[i];
			 }
		 }
		if(Menu_name[Number_All-1].num==3)
		 {
			 for(i=0;i< Number_All-1;i++)
			 {
				 Menu_name[i].num= flash_memory2[i];
			 }
		 }
		 		if(Menu_name[Number_All-1].num==4)
		 {
			 for(i=0;i< Number_All-1;i++)
			 {
				 Menu_name[i].num= flash_memory3[i];
			 }
		 }
    for (i = 1; i <= final_hang; i++)
    {
      OLED_Write_String(2, (i - 1) * 2, (uint8_t *)Menu_name[i - 1 + 4 * page].name);
      OLED_Write_String(10, (i - 1) * 2, (uint8_t *)":");
      OLED_Write_Num4(11, (i - 1) * 2, Menu_name[i - 1 + 4 * page].num);
    }
		 if (Key_In == 0)
    {
      DelayMs(100);
      if (Key_In == 0)
      {
        OLED_Clear();
        startstart = 1;
      break;
      }
    }

}



//菜单退出  更改菜单时需要改！！
#endif 
//变量赋值
#if (Number_All >= 1)
  name0_num = Menu_name[0].num;
#endif

#if (Number_All >= 2)
  name1_num = Menu_name[1].num;
#endif

#if (Number_All >= 3)
  name2_num = Menu_name[2].num;
#endif

#if (Number_All >= 4)
  name3_num = Menu_name[3].num;
#endif

#if (Number_All >= 5)
  name4_num = Menu_name[4].num;
#endif

#if (Number_All >= 6)
  name5_num = Menu_name[5].num;
#endif

#if (Number_All >= 7)
  name6_num = Menu_name[6].num;
#endif
#if (Number_All >= 8)
  name7_num = Menu_name[7].num;
#endif

#if (Number_All >= 9)
  name8_num = Menu_name[8].num;
#endif

#if (Number_All >= 10)
  name9_num = Menu_name[9].num;
#endif

#if (Number_All >= 11)
  name10_num = Menu_name[10].num;
#endif

#if (Number_All >= 12)
  name11_num = Menu_name[11].num;
#endif

#if (Number_All >= 13)
  name12_num = Menu_name[12].num;
#endif

#if (Number_All >= 14)
  name13_num = Menu_name[13].num;
#endif

#if (Number_All >= 15)
  name14_num = Menu_name[14].num;
#endif

#if (Number_All >= 16)
  name15_num = Menu_name[15].num;
#endif

#if (Number_All >= 17)
  name16_num = Menu_name[16].num;
#endif

#if (Number_All >= 18)
  name17_num = Menu_name[17].num;
#endif

#if (Number_All >= 19)
  name18_num = Menu_name[18].num;
#endif

#if (Number_All >= 20)
  name19_num = Menu_name[19].num;
#endif

#if (Number_All >= 21)
  name20_num = Menu_name[20].num;
#endif

#if (Number_All >= 22)
  name21_num = Menu_name[21].num;
#endif

#if (Number_All >= 23)
  name22_num = Menu_name[22].num;
#endif

#if (Number_All >= 24)
  name23_num = Menu_name[23].num;
#endif

#if (Number_All >= 25)
  name24_num = Menu_name[24].num;
#endif

#if (Number_All >= 26)
  name25_num = Menu_name[25].num;
#endif

#if (Number_All >= 27)
  name26_num = Menu_name[26].num;
#endif

#if (Number_All >= 28)
  name27_num = Menu_name[27].num;
#endif

#if (Number_All >= 29)
  name28_num = Menu_name[28].num;
#endif
#if (Number_All >= 30)
  name29_num = Menu_name[29].num;
#endif
#if (Number_All >= 31)
  name30_num = Menu_name[30].num;
#endif
#if (Number_All >= 32)
  name31_num = Menu_name[31].num;
#endif
#if (Number_All >= 33)
  name32_num = Menu_name[32].num;
#endif
#if (Number_All >= 34)
  name33_num = Menu_name[33].num;
#endif
#if (Number_All >= 35)
  name34_num = Menu_name[34].num;
#endif
#if (Number_All >= 36)
  name35_num = Menu_name[35].num;
#endif
#if (Number_All >= 37)
  name36_num = Menu_name[36].num;
#endif
#if (Number_All >= 38)
  name37_num = Menu_name[37].num;
#endif
#if (Number_All >= 39)
  name38_num = Menu_name[38].num;
#endif
#if (Number_All >= 40)
  name39_num = Menu_name[39].num;
#endif
#if (Number_All >= 41)
  name40_num = Menu_name[40].num;
#endif
#if (Number_All >= 42)
  name41_num = Menu_name[41].num;
#endif
#if (Number_All >= 43)
  name42_num = Menu_name[42].num;
#endif
#if (Number_All >= 44)
  name43_num = Menu_name[43].num;
#endif
#if (Number_All >= 45)
  name44_num = Menu_name[44].num;
#endif
#if (Number_All >= 46)
  name45_num = Menu_name[45].num;
#endif
#if (Number_All >= 47)
  name46_num = Menu_name[46].num;
#endif
#if (Number_All >= 48)
  name47_num = Menu_name[47].num;
#endif
#if (Number_All >= 49)
  name48_num = Menu_name[48].num;
#endif
#if (Number_All >= 50)
  name49_num = Menu_name[49].num;
#endif
#if (Number_All >= 51)
  name50_num = Menu_name[50].num;
#endif
#if (Number_All >= 52)
  name51_num = Menu_name[51].num;
#endif
#if (Number_All >= 53)
  name52_num = Menu_name[52].num;
#endif
#if (Number_All >= 54)
  name53_num = Menu_name[53].num;
#endif
#if (Number_All >= 55)
  name54_num = Menu_name[54].num;
#endif
#if (Number_All >= 56)
  name55_num = Menu_name[55].num;
#endif
runmodeflash[0]=runmode;	 
runmodeflash[1]=mode_mode;	    
runmodeflash[2]=slowstart;	     
runmodeflash[3]=protect_stop;	   
runmodeflash[4]=huandaocntmax;	 
runmodeflash[5]=slopecntmax;	 
runmodeflash[6]=blockcntmax;	 
runmodeflash[7]=yuzhi;	 
runmodeflash[8]=qipaoflag;
runmodeflash[9]=huandao_type[0];
runmodeflash[10]=huandao_type[1]; 
runmodeflash[11]=huandao_type[2];
runmodeflash[12]=huandao_type[3];
runmodeflash[13]=dianbo_switch;
//flah 从刷  写入 更改菜单时需要改！！
FLASH_EraseSector(179);
FLASH_WriteSector(179,(uint8_t *)runmodeflash,Number_All*4,0);
if(Menu_name[0].num==1)//更改菜单时需要改！！
{
  
data1[8]=dajiao;	       
data1[9]=longspeed;	     
data1[10]=shortspeed;	    
data1[11]=speedstraight;	 
data1[12]=speedturn;	    
data1[14]=longstraightp;	
data1[15]=longstraightd;	
data1[16]=straightp;	   
data1[17]=straightd;	  
data1[18]=smallsp;	     
data1[19]=smallsd;	   
data1[20]=leftp;	     
data1[21]=leftd;	    
data1[22]=rightp;	    
data1[23]=rightd;	
data1[24]=Ispeed1;	
data1[25]=Ispeed2;	
data1[26]=Ispeed3;	   
data1[27]=Ispeed4;		
data1[28]=Ispeed1dj;
data1[29]=Ispeed2dj;
data1[30]=Ispeed3dj;
data1[31]=Ispeed4dj;
data1[32]=Bigsp;      //大S P
 data1[33]=Bigsd ;      //大S D
 data1[34]=Bigs_dj ;//大S打角行
 data1[35]=Mid_S_Switch ;//大S开关
 data1[36]=speedBigs ;    //大S速度
 data1[37]=superspeed;           
 data1[38]=po_speed;
 data1[39]=IkP1;
 data1[40]=IkP2;
 data1[41]=IkP3;
 data1[42]=IkP4;
 data1[43]=IkD1;
 data1[44]=IkD2;
 data1[45]=IkD3;
 data1[46]=IkD4;
data1[47]=longSS_speed;
data1[48]=blockspeed;

FLASH_EraseSector(181);
FLASH_WriteSector(181,(uint8_t *)data1,Number_All*4,0);

	}
else if(Menu_name[0].num==2)//更改菜单时需要改！！
{
      
     
data2[8]=dajiao;	       
data2[9]=longspeed;	     
data2[10]=shortspeed;	    
data2[11]=speedstraight;	 
data2[12]=speedturn;	    
data2[37]=superspeed;   	         
data2[14]=longstraightp;	
data2[15]=longstraightd;	
data2[16]=straightp;	   
data2[17]=straightd;	  
data2[18]=smallsp;	     
data2[19]=smallsd;	   
data2[20]=leftp;	     
data2[21]=leftd;	    
data2[22]=rightp;	    
data2[23]=rightd;	      
data2[24]=Ispeed1;	
data2[25]=Ispeed2;	
data2[26]=Ispeed3;	   
data2[27]=Ispeed4;		
data2[28]=Ispeed1dj;
data2[29]=Ispeed2dj;
data2[30]=Ispeed3dj;
data2[31]=Ispeed4dj;
data2[32]=Bigsp;      //大S P
 data2[33]=Bigsd ;      //大S D
 data2[34]=Bigs_dj ;//大S打角行
 data2[35]=Mid_S_Switch ;//大S开关
 data2[36]=speedBigs;    //大S速度
  data2[37]=superspeed;           
 data2[38]=po_speed;
  data2[39]=IkP1;
 data2[40]=IkP2;
 data2[41]=IkP3;
 data2[42]=IkP4;
 data2[43]=IkD1;
 data2[44]=IkD2;
 data2[45]=IkD3;
 data2[46]=IkD4;
 data2[47]=longSS_speed;
 data2[48]=blockspeed;

FLASH_EraseSector(182);
FLASH_WriteSector(182,(uint8_t *)data2,Number_All*4,0);
	}
else if(Menu_name[0].num==3)//更改菜单时需要改！！
{
      
     
data3[8]=dajiao;	       
data3[9]=longspeed;	     
data3[10]=shortspeed;	    
data3[11]=speedstraight;	 
data3[12]=speedturn;	    
data3[37]=superspeed;   	         
data3[14]=longstraightp;	
data3[15]=longstraightd;	
data3[16]=straightp;	   
data3[17]=straightd;	  
data3[18]=smallsp;	     
data3[19]=smallsd;	   
data3[20]=leftp;	     
data3[21]=leftd;	    
data3[22]=rightp;	    
data3[23]=rightd;	      
data3[24]=Ispeed1;	
data3[25]=Ispeed2;	
data3[26]=Ispeed3;	   
data3[27]=Ispeed4;		
data3[28]=Ispeed1dj;
data3[29]=Ispeed2dj;
data3[30]=Ispeed3dj;
data3[31]=Ispeed4dj;
data3[32]=Bigsp;      //大S P
 data3[33]=Bigsd ;      //大S D
 data3[34]=Bigs_dj ;//大S打角行
 data3[35]=Mid_S_Switch ;//大S开关
 data3[36]=speedBigs;    //大S速度
  data3[37]=superspeed;           
 data3[38]=po_speed;
  data3[39]=IkP1;
 data3[40]=IkP2;
 data3[41]=IkP3;
 data3[42]=IkP4;
 data3[43]=IkD1;
 data3[44]=IkD2;
 data3[45]=IkD3;
 data3[46]=IkD4;
 data3[47]=longSS_speed;
 data3[48]=blockspeed;

FLASH_EraseSector(183);
FLASH_WriteSector(183,(uint8_t *)data3,Number_All*4,0);
	}

else//更改菜单时需要改！！
{
     
data0[8]=dajiao;	       
data0[9]=longspeed;	     
data0[10]=shortspeed;	    
data0[11]=speedstraight;	 
data0[12]=speedturn;	    
data0[37]=superspeed;   	         
data0[14]=longstraightp;	
data0[15]=longstraightd;	
data0[16]=straightp;	   
data0[17]=straightd;	  
data0[18]=smallsp;	     
data0[19]=smallsd;	   
data0[20]=leftp;	     
data0[21]=leftd;	    
data0[22]=rightp;	    
data0[23]=rightd;	      
data0[24]=Ispeed1;	
data0[25]=Ispeed2;	
data0[26]=Ispeed3;	   
data0[27]=Ispeed4;		
data0[28]=Ispeed1dj;
data0[29]=Ispeed2dj;
data0[30]=Ispeed3dj;
data0[31]=Ispeed4dj;
data0[32]=Bigsp;      //大S P
data0[33]=Bigsd ;      //大S D
data0[34]=Bigs_dj ;//大S打角行
data0[35]=Mid_S_Switch ;//大S开关
data0[36]=speedBigs ;    //大S速度
data0[37]=superspeed;         
data0[38]=po_speed;
 data0[39]=IkP1;
 data0[40]=IkP2;
 data0[41]=IkP3;
 data0[42]=IkP4;
 data0[43]=IkD1;
 data0[44]=IkD2;
 data0[45]=IkD3;
 data0[46]=IkD4;
 data0[47]=longSS_speed;
 data0[48]=blockspeed;


FLASH_EraseSector(180);
FLASH_WriteSector(180,(uint8_t *)data0,Number_All*4,0);

}










}

void mode1(void)     //无图
{

	  SonyCCD_Init();	
		DelayMs(200);

	while(1)
	{
		
	if(CCD_flag==1)
		{
		 OLED_Write_Num4(0,0,speed);
    steercontrol();
		 CCD_flag=0;
		}
		
	if( protect_stop==1&&protcnt>35)
	{
	if(protcnt<40)
	{
		protcnt++;
	}
		if((cutline<5)&&poflag==0&&huandaoflag==1)
		{
			FTM_PWM_ChangeDuty(Motorup_port,Motorup_ch,0);
     FTM_PWM_ChangeDuty(Motordown_port,Motordown_ch,0);
			DelayMs(100000);
		}
		if((cutline<5)&&poflag==0&&huandaoflag==0&&P_Pixels[1][LCenter[1]] == 0)
		{
			FTM_PWM_ChangeDuty(Motorup_port,Motorup_ch,0);
     FTM_PWM_ChangeDuty(Motordown_port,Motordown_ch,0);
			DelayMs(100000);
		}
	}
	}
}


void mode2(void)     //有图无电机
{
	SonyCCD_Init();	
	while(1)
	{
		if(CCD_flag==1)
		{
		 speed=0;
    //  SignalProcess();

	  DisplayImage_WithOLED();
	 CCD_flag=0;
		}
	}
}
void mode3(void)    //录图
{
	SonyCCD_Init();	
My_SdCard_Init(sd_save);
		OLED_Write_String(6, 2,(uint8_t*) "transfer");
	DelayMs(20);
	OLED_Clear();
	while(1)
	{
  	if(CCD_flag==1)
		{
     steercontrol();
			My_SdCard_Save();
	//	DisplayImage_WithOLED();
		 CCD_flag=0;
		}
	if(protcnt<40)
	{
		protcnt++;
	}		
	if( protect_stop==1&&protcnt>35)
	{
		if((cutline<5)&&poflag==0&&huandaoflag==1)
		{
			FTM_PWM_ChangeDuty(Motorup_port,Motorup_ch,0);
     FTM_PWM_ChangeDuty(Motordown_port,Motordown_ch,0);
			DelayMs(100000);
		}
		if((cutline<5)&&poflag==0&&huandaoflag==0&&P_Pixels[1][LCenter[1]] == 0)
		{
			FTM_PWM_ChangeDuty(Motorup_port,Motorup_ch,0);
     FTM_PWM_ChangeDuty(Motordown_port,Motordown_ch,0);
			DelayMs(100000);
		}
	}
	}
}

void mode4(void)  //传图
{
	My_Tranfer_Init();
	My_SdCard_Init(sd_read);
	OLED_Write_String(6, 4,(uint8_t*) "jktransfer");
	DelayMs(1000);
  while (1)
  {
My_SdCard_Read();
 DisplayImage_WithOLED();
	DelayMs(50);	
  }
	OLED_Write_String(6, 2,(uint8_t*) "finished");
}
void mode5()//实时传输
{
	My_Tranfer_Init();//初始化uart dma
	SonyCCD_Init();	
	while(1)
	{
		if(CCD_flag==1)
		{
    SignalProcess();
    My_LiveTransfer();//实时传输一场图片及参数
		DisplayImage_WithOLED();
	  CCD_flag=0;
		}
	}
}


void mode6()//舵机范围
{
	int i,j;
	OLED_Clear();
	j=5;

	i=zhong;
OLED_Write_String(1, 0, (uint8_t*)"ADD-HowMuch");
OLED_Write_String(1, 2, (uint8_t*)"FTM");

while(1)
{

if(Key_Up==0)
	{
	DelayMs(100); 
if(Key_Up==0)		
		i+=j; 
	}
	if(Key_Down==0)
			{	
				DelayMs(100);
	if(Key_Down==0)
				i-=j;
			}
			
if(Key_Minus==0)
	{
	DelayMs(100); 
if(Key_Minus==0&&j>1)		
		j-=2; 
	}
	if(Key_Add==0)
	{
	DelayMs(100); 
if(Key_Add==0)		
		j+=2; 
	}

FTM_PWM_ChangeDuty(Steer_port,Steer_ch,i);					

OLED_Write_Num4(1,1,j);
OLED_Write_Num4(1,3,i);

	if(i<3500)
		i=3500;
	if(i>6500)
		i=6500;
			
}//300HZ ：  4980 5860 4100

}







