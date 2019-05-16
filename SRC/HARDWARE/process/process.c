#include "process.h"
#include "data.h"
#include "key.h"
#include "ftm.h"
#include "SEEKFREE_MT9V032.h"
#include "dmacnt.h"
#include "Fuzzy_control.h"

#define byte uint8_t


/*

超级直道 1
长直道   2
短直道   3
入弯     4
左弯道   5
右弯道   6
小S      7
大S      8
连弯     9
障碍     10
坡道     11
起跑线   12

*/


uint8_t kaiqi=0;
uint8_t kaiqiflag=0;
int qipaocnt=0;
int motorpwm=0;
int aim=0;
int jiance;
int midleline;
int speed=0;
int speedlast=0;
int fuzhiup=5000;
int zuo=0;
int you=0;
double doub_temp=0;
void kind();
int fabss();
int Dianji_Ftm;
int Huandao_type;
double Huandao_pp,Huandao_dd;
uint8_t dajiao_ceshi;
uint8_t qipao_cnt=0;//起跑线场数延时 
uint8_t Diaobo_flag=0;//颠簸
int Dianbo_cnt=0;
uint8_t Lastroadtype;
uint8_t fixValue[]=
{
    129,127,126,125,123,121,121,119,117,116,
    114,112,111,109,108,106,105,104,101,101,
    99,98,97,95,93,92,90,89,87,85,
    84,83,81,80,79,77,75,73,73,71,
    70,69,67,66,64,63,62,60,58,56,
    55,54,52,50,49,48,46,44,42,42,
    40,39,36,35,33,32,31,28,27,0,
};

        uint8_t L_black[70];
        uint8_t R_black[70];
        uint8_t LCenter[70];
       int dajiaochange(dajiao)
			 {
				 if(fabss(speedlast,speed)<40)
				 {
				 if(aim>speed)
				 {
					 if(aim-speed<40){ return dajiao;}
					else if(aim-speed>=120){ return dajiao-3;}
					else if(aim-speed>=80){ return dajiao-2;}
					else if(aim-speed>=40){ return dajiao-1;}
		
				 }
				 else
				 {
					if(speed-aim<20){ return dajiao;}									
					else if(speed-aim>=60){ return dajiao+3;}			
					else if(speed-aim>=40){ return dajiao+2;}			
					else if(speed-aim>=20){ return dajiao+1;}			
					 
				 }
			 }
				 else
				 {
					if(aim>speed)
				 {
					 if(aim-speed<80){ return dajiao;}
					else if(aim-speed>=160){ return dajiao-2;}
					else if(aim-speed>=80){ return dajiao-1;}
		
				 }
				 else
				 {
					if(speed-aim<80){ return dajiao;}			
					else if(speed-aim>=160){ return dajiao+2;}			
					else if(speed-aim>=80){ return dajiao+1;}			
					 
				 }
				 }
			
			 }
			 /***********判定************/


/********************一下上位机程序**********************/
  byte superfastflag = 0;            //F1超引擎超级加速
        byte longstraightflag = 0;         //长直道
        byte shortstraightflag = 0;        //短直道
        byte notstraightflag = 0;           //没有摆正的长直道或者短直道
        byte turnflag = 0;                 //拐弯标志位
        byte leftflag = 0;                 //左转
        byte rightflag = 0;                //右转
        byte smallsflag = 0;               //小s
        byte longstraightline = 60;         //长直道判断行
        byte shortstraightline = 40;        //短直道判断行
        /**************一般变量**********************/
        byte leftmax = 0, leftmin = 0, rightmax = 0, rightmin = 0;
        byte center = 100;

        double kzhi = 0;
        byte i = 0, e = 0, RowNum = 0;
        byte cutline = 69, line_effet = 0;//记录截断行和有效行
        int temp = 0;//临时变量                           
        byte temporary, j;
        byte a, b, c, d;
        byte b_L, b_R;
        float K_L, K_R;
        byte L_Find_Start = 199, R_Find_Start = 0;//扫线起始点，定义成全局变量，为了便于在上一场进行操作，用于本场扫线
        /******************十字******************/
        byte LoseFirst_L_Row = 0, LoseFirst_R_Row = 0;
        byte LoseRepair_L_Row = 0, LoseRepair_R_Row = 0;
        //直十字
        byte Cross_Straight_Flag = 0;
        byte Cross_Straight_in = 0;//进入十字标志
        byte Cross_Straight_L_in = 0, Cross_Straight_R_in = 0;//直入十字左右拐点找到标志
        byte Cross_Straight_L_in_Row = 0, Cross_Straight_R_in_Row = 0;
        byte Cross_Straight_L_in_Rank = 0, Cross_Straight_R_in_Rank = 0;
        float Cross_Straight_L_Slope = 0, Cross_Straight_R_Slope = 0;
        byte Cross_Straight_out = 0;//出十字标志
        byte Cross_Straight_L_out = 0, Cross_Straight_R_out = 0;
        byte Cross_Straight_L_outcnt = 0, Cross_Straight_R_outcnt = 0;
        byte Cross_Straight_L_out_Row = 0, Cross_Straight_R_out_Row = 0;
        byte Cross_Straight_L_out_Rank = 0, Cross_Straight_R_out_Rank = 0;
        //斜十字     
        byte Cross_Lean_L_in = 0, Cross_Lean_R_in = 0;//左右有拐点十字 标志
        byte Cross_Lean_L_in_Row = 0, Cross_Lean_R_in_Row = 0;//斜十字的位置 行
        byte Cross_Lean_L_in_Lose = 0, Cross_Lean_R_in_Lose = 0;

        byte Cross_Lean_L_in_Rank = 0, Cross_Lean_R_in_Rank = 0;//斜十字的位置 列
        float Cross_Lean_L_Slope = 0, Cross_Lean_R_Slope = 0;
        byte Cross_Lean_L_out = 0, Cross_Lean_R_out = 0;//左右有拐点十字 标志
        byte Cross_Lean_L_out_Row = 0, Cross_Lean_R_out_Row = 0;//斜十字的位置 行
        byte Cross_Lean_L_out_Rank = 0, Cross_Lean_R_out_Rank = 0;//斜十字的位置 列
        byte Cross_Lean_L_Saoxian, Cross_Lean_R_Saoxian;//=0时扫线左边线扫到右边线 这时停止按斜率扫线
        byte Cross_Lean_L, Cross_Lean_R;
        byte Cross_Pingyi;

        //无拐点十字
        byte Cross_No_RightAngle_L_Memory = 0, Cross_No_RightAngle_R_Memory = 0;//1无拐点，2全白
        float Cross_NR_L_Memory_Slope = 0, Cross_NR_R_Memory_Slope = 0;
        byte Cross_NR_L_Memory_in_Rank = 0, Cross_NR_R_Memory_in_Rank = 0;//第零行 进十字的位置
        byte Cross_NR_L_Memory_out_Row = 0, Cross_NR_R_Memory_out_Row = 0;//出十字行
        byte Cross_NR_L_Memory_out_Rank = 0, Cross_NR_R_Memory_out_Rank = 0;//出十字行
        byte Cross_NR_L_Memory_FindFlag = 0, Cross_NR_R_Memory_FindFlag = 0;//找到十字标志
        byte Cross_NR__Memory_out_Row = 0;
        byte Cross_NR_L_180cnt, Cross_NR_R_180cnt;
        byte Cross_NR_L_130cnt, Cross_NR_R_130cnt;
        byte Cross_NR_L_cnt, Cross_NR_R_cnt, Cross_NR_LR_cnt;//只会补30场，之后就直接清除了
        byte Cross_NR_L_start, Cross_NR_R_start;
        //十字全白
        byte Cross_Allwhite_L, Cross_Allwhite_R;
        byte Cross_Allwhite;
        byte Cross_Allwhite_L_out_Row = 0, Cross_Allwhite_R_out_Row = 0;
        byte Cross_Allwhite_L_out_Rank = 0, Cross_Allwhite_R_out_Rank = 0;
        byte Cross_Allwhite_L_start, Cross_Allwhite_R_start;
        byte Cross_Allwhite_Maybe;
        byte crossflag = 0;
        //十字全白记忆 采用中点扫线
        byte Cross_Allwhite2cnt;
        byte Cross_Allwhite2;
        byte Cross_Allwhite2_L, Cross_Allwhite2_R;

        byte Cross_Allwhite2_L_out_Row = 0, Cross_Allwhite2_R_out_Row = 0;
        byte Cross_Allw2_first;
        byte Cross_Allwhite2_R_start, Cross_Allwhite2_L_start;
        //疑似十字
        byte Cross_Lean_Lmabye2 = 0, Cross_Lean_Rmabye2 = 0;
        //出弯重新补线
        byte changeflag = 0, changezuo = 0, changeyou = 0;
        byte bianhuanflag = 0;
        /*___________________连弯_________________*/
        byte LianWan_plevel_FlagR, LianWan_plevel_FlagL;//3是普通P 0 1 2是小P小小P 3 4是大P超大P  
        byte LianWan_max, LianWan_min;
        byte LianWan_max_row, LianWan_min_row;
        byte Curve_Lianwan_L_Row, Curve_Lianwan_R_Row;
        byte Curve_Lianwan_R, Curve_Lianwan_L;
        byte Curve_Lianwan_R_pingyi, Curve_Lianwan_L_pingyi;
        byte Curve_Lianwan_LCnt, Curve_Lianwan_RCnt;
        //小S
        byte L_SmallS_Flag1 = 0, L_SmallS_Flag2 = 0, L_SmallS_Flag3 = 0, L_SmallS_Flag4 = 0;
        byte R_SmallS_Flag1 = 0, R_SmallS_Flag2 = 0, R_SmallS_Flag3 = 0, R_SmallS_Flag4 = 0;
        byte Judge_SmallS = 0;
        byte R_Big, L_Small;
        //中S
        byte bigsflag = 0;//中S
        byte L_BigS_Flag1 = 0, L_BigS_Flag2 = 0, L_BigS_Flag3 = 0, L_BigS_Flag4 = 0;
        byte R_BigS_Flag1 = 0, R_BigS_Flag2 = 0, R_BigS_Flag3 = 0, R_BigS_Flag4 = 0;
        byte Small_SWanState = 0, Small_SWanState2 = 0;
        byte S_HangL_1 = 0, S_HangL_2 = 0, S_HangR_1 = 0, S_HangR_2 = 0;
        int S_wide_center1, S_wide_center2;
        int S_wide_lblack1, S_wide_lblack2;
        int S_wide_rblack1, S_wide_rblack2;
        //环岛标志位
        byte huandaoflag = 0;
        byte huandaozuoflag1 = 0, huandaozuoflag2 = 0, huandaozuoflag3 = 0;
        byte huandaozuosao = 0, huandaozuosao1 = 0;
        byte huandaoyouflag1 = 0, huandaoyouflag2 = 0, huandaoyouflag3 = 0;
        byte huandaoyousao = 0, huandaoyousao1 = 0;
        byte leftall = 1, rightall = 1, tubianyou = 0, tubianzuo = 0, huandaochu = 0, huandaochu1 = 0;
        byte qingchuflag = 0, huandaocnt = 0;
        byte wanruzuo1 = 0, wanruzuo2 = 0, wanruzuo3 = 0;
        byte wanruyou1 = 0, wanruyou2 = 0, wanruyou3 = 0;
        byte huandaoblackpoint = 0, ruflag = 0;
        byte huandaowanflag = 0;
        byte normalhuan = 0;
        byte huandaozuoguai = 0, huandaoyouguai = 0;
				float khuan=0;
        //起跑线和坡道
        byte qipaojiance = 0;//在环岛之后检测起跑线
        byte Wide_Row_Space = 0, Normal_Row_Space = 0;
        byte Narrow_Row_Space = 0;
        byte Ramp3_ClearFieldCnt = 0;
        byte stopflag = 0;
        byte poflag = 0;
        byte lefttrend = 0, righttrend = 0;
        int pojishu = 0;
				byte poqingchucnt=0;
        //障碍
        byte blockflag = 0;
        byte Obstruction_L, Obstruction_R;//障碍判断
        byte Obstruction_LState, Obstruction_RState;//障碍标志
        byte Obstruction_L_EdgeH_Row, Obstruction_R_EdgeH_Row;//障碍上边缘 行
        byte Obstruction_L_Mid_Row, Obstruction_R_Mid_Row;//障碍上边缘 行
        byte Obstruction_L_EdgeL_Row, Obstruction_R_EdgeL_Row;//障碍下边缘 行
        byte Obstruction_L_EdgeL_Rank, Obstruction_R_EdgeL_Rank;//障碍左边缘 列
        byte Obstruction_L_EdgeR_Rank, Obstruction_R_EdgeR_Rank;
        byte Obstruction_narrow_cnt;
        byte Obstruction_0wide, Obstruction_0lastwide;//0行宽
        byte Obstruction_jumping_RowL, Obstruction_jumping_RowH;
        byte Obstruction_jumping_RowMid;
        byte Obstruction_Lin_cnt = 0, Obstruction_Rin_cnt = 0;//进障碍场数计数
        byte Obstruction_Lout_cnt = 0, Obstruction_Rout_cnt = 0;//进障碍场数计数
        byte Obstruction_L_Wan, Obstruction_R_Wan;
        //叉路补线
        byte zuotuchu = 0, zuotiaobian = 0;
        byte youtuchu = 0, youtiaobian = 0;
        byte Lwhitezhi = 0, Lxflag = 0;
        byte Rwhitezhi = 0, Rxflag = 0;
        byte CLxflag = 0, CRxflag = 0;
        byte chalucnt = 0;
        byte huandaofangxiang = 0;
        byte Shizila_flagL = 0, Shizila_flagR = 0;//左右拉线标志
				byte huanchucnt=0;
				byte jumpmem = 0;
        byte jumppot = 0;
        //记录元素个数
        byte cnt = 0;
        byte cnt1 = 0;
        byte cnt2 = 0;
        byte huandaogeshu = 0;
        byte zhangaigeshu = 0;
        byte podaogeshu = 0;
        byte firstscan = 0;
        byte scanchange = 0;
        byte crosscutflag = 0;
        byte scancnt = 0;
        byte leftlost = 0;
        byte rightlost = 0;
				
				byte dahuanflag=0;
				
				
        // ////ion
         // ////ion 自定义
        byte fab1(int a1)
        {
            if (a1 >= 0)
                return (byte)a1;
            else
                return (byte)-a1;

        }
        int fabss(int a1, int a2)
        {
            if (a1 > a2)
                return (int)(a1 - a2);
            else
                return (int)(a2 - a1);

        }//绝对值   

        byte MinNum(byte Value1, byte Value2)
        {
            if (Value1 >= Value2)
            {
                return Value2;
            }
            else
                return Value1;
        }//求最小值                               
        byte MaxNum(byte Value1, byte Value2)
        {
            if (Value1 >= Value2)
            {
                return Value1;
            }
            else
                return Value2;
        }//求最大值                               
        void Edge_Scan(byte i)//边线扫描黑白兼容
        {
            byte j;
            if (i == 1 || i == 0)
            {
                L_Find_Start = L_black[0];
                R_Find_Start = R_black[0];
            }

            if (P_Pixels[i][L_Find_Start] == 0)
            {
                for (j = L_Find_Start; j > 0; j--)
                {
                    if (P_Pixels[i][j] > 0)
                    {
                        L_black[i] = (byte)(j + 1);
                        break;
                    }
                    if (j <= 1)
                    {
                        L_black[i] = 0;
                        break;

                    }
                }
            }
            else
            {
                if (L_Find_Start == 199)
                    L_black[i] = 199;
                else
                {
                    for (j = L_Find_Start; j < 199; j++)
                    {
                        if (P_Pixels[i][j] == 0)
                        {
                            L_black[i] = j;
                            break;
                        }
                        if (j >= 198)
                            L_black[i] = 199;
                    }
                }
            }
            if (P_Pixels[i][R_Find_Start] == 0)
            {
                for (j = R_Find_Start; j < 199; j++)
                {
                    if (P_Pixels[i][j] > 0)
                    {
                        R_black[i] = (byte)(j - 1);
                        break;
                    }
                    if (j >= 198)
                        R_black[i] = 199;
                }
            }
            else
            {
                if (R_Find_Start == 0)
                    R_black[i] = 0;
                else
                {
                    for (j = R_Find_Start; j > 0; j--)
                    {
                        if (P_Pixels[i][j] == 0)
                        {
                            R_black[i] = j;
                            break;
                        }
                        if (j <= 1)
                        {
                            R_black[i] = 0;
                            break;
                        }

                    }
                }
            }
            if (i > 0)
            {
                L_Find_Start = L_black[i];
                R_Find_Start = R_black[i];
            }

        }
        void Center_Scan(byte center, byte RowNum)
        {
            if (P_Pixels[RowNum][center] > 0)//中点白色
            {

                for (i = center; i > 0; i--)
                {
                    //右线
                    if (P_Pixels[RowNum][i] == 0)
                    {
                        if (i <= 5)
                        {
                            R_black[RowNum] = (byte)(i);
                            break;
                        }
                        else
                        {
                            if (poflag != 0)//坡道防止白色赛道挨的很近 难以满足滤波条件 
                            {
                                R_black[RowNum] = (byte)(i);
                                break;
                            }
                            else if (P_Pixels[RowNum][i - 1] == 0 && P_Pixels[RowNum][i - 3] == 0)
                            {
                                R_black[RowNum] = (byte)(i);
                                break;
                            }

                        }
                    }
                    if (i == 1)
                    {
                        R_black[RowNum] = 0;
                    }
                }
                for (i = center; i < 199; i++)
                {
                    if (P_Pixels[RowNum][i] == 0)
                    {
                        if (i >= 195)
                        {
                            L_black[RowNum] = (byte)(i);
                            break;
                        }
                        else
                        {
                            if (poflag != 0)//坡道防止白色赛道挨的很近 难以满足滤波条件 
                            {

                                L_black[RowNum] = (byte)(i);
                                break;
                            }
                            else if (P_Pixels[RowNum][i + 1] == 0 && P_Pixels[RowNum][i + 3] == 0)
                            {
                                L_black[RowNum] = (byte)(i);
                                break;
                            }

                        }
                    }
                    if (i == 198)
                    {
                        L_black[RowNum] = 199;
                    }
                }

            }
            if (P_Pixels[RowNum][center] == 0)
            {
                // //"中点黑" + center);

                if (center != 199)
                {
                    for (i = center; i < 199; i++)
                    {
                        if (P_Pixels[RowNum][i] > 0)
                        {
                            center = i;
                            break;
                        }
                        if (i == 198)
                        {
                            center = 199;
                        }
                    }
                }
                if (center != 0)
                {
                    for (i = center; i > 0; i--)
                    {
                        if (P_Pixels[RowNum][i] > 0)
                        {
                            center = i;
                            break;
                        }
                        if (i == 1)
                        {
                            center = 0;
                        }
                    }
                }
                for (i = center; i > 0; i--)
                {
                    if (P_Pixels[RowNum][i] == 0)
                    {
                        R_black[RowNum] = (byte)(i);
                        break;
                    }
                    if (i == 1)
                    {
                        R_black[RowNum] = 0;
                    }
                }
                for (i = center; i < 199; i++)
                {
                    if (P_Pixels[RowNum][i] == 0)
                    {
                        L_black[RowNum] = (byte)(i);
                        break;
                    }
                    if (i == 198)
                    {
                        L_black[RowNum] = 199;
                    }
                }
            }
            LCenter[RowNum] = (byte)((L_black[RowNum] + R_black[RowNum]) / 2);

        }//中点往两边扫线  
        double K(byte wantline1, byte wantline2)
        {
            kzhi = (double)(LCenter[wantline2] - LCenter[wantline1]) / (wantline2 - wantline1);
            if (kzhi > 0)
                return kzhi;
            else
                return -kzhi;
        }    //两行中点的斜率
        byte door(byte wantline, byte zhi)//遍历 前wantline行 赛道宽度大于zhi
        {
            byte rightmax = 0, leftmin = 199, max = 0, min = 199;
            if (cutline >= wantline)
            {
                for (i = 1; i < wantline; i++)
                {

                    min = MinNum(min, L_black[i]);
                    if (min < leftmin)
                        leftmin = min;

                    max = MaxNum(max, R_black[i]);
                    if (max > rightmax)
                        rightmax = max;
                }

                if (leftmin - rightmax > zhi)
                {
                    return 1;
                }
                else
                {
                    return 0;
                }

            }
            else
            {
                return 0;
            }





        }//左线最右值 右线最左值
        byte racewide(byte wanthang, byte wantkuan)
        {
            byte rightmax = 0, leftmin = 0, max = 0, min = 199;
            if (wanthang > cutline)
            {
                return 0;
            }
            else
            {
                for (i = 1; i < wanthang; i++)
                {

                    min = MinNum(min, L_black[i]);
                    leftmin = min;

                    max = MaxNum(max, R_black[i]);
                    rightmax = max;
                }



                if (leftmin - rightmax > wantkuan)
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }

        }//比较想要行的宽度
        byte kjudge(byte wanthigh, byte fazhi)
        {
            byte flag = 0;
            byte Kpoint[70];

            for (i = 0; i < wanthigh; i++)
            {
                Kpoint[i] = (byte)(LCenter[0] + i * (double)(LCenter[wanthigh] - LCenter[0]) / wanthigh);

                if (fabss(Kpoint[i], LCenter[i]) > fazhi)
                {

                    flag = 1;
                }
            }
            if (LCenter[wanthigh] - LCenter[0] > 0)//???
            {
                kzhi = (double)(LCenter[wanthigh] - LCenter[0]) / wanthigh;
            }
            else
            {
                kzhi = (double)(LCenter[0] - LCenter[wanthigh]) / wanthigh;
            }

            if (flag != 1)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }//斜率点偏差比较
        byte kind_huancnt(byte kind)
        {

            if (kind == 0 && cnt == 0) { cnt = 1; };
            if (kind == 1 && cnt == 1) { cnt = 2; };
            if (kind == 0 && cnt == 2) { cnt = 3; };
            if (kind == 1 && cnt == 3) { cnt = 4; };
            if (kind == 0 && cnt == 4) { cnt = 5; };
            if (kind == 1 && cnt == 5) { cnt = 6; };
            if (kind == 0 && cnt == 6) { cnt = 7; };
            if (kind == 1 && cnt == 7) { cnt = 8; };
            if (kind == 0 && cnt == 8) { cnt = 9; };
            if (kind == 1 && cnt == 9) { cnt = 10; };
            if (kind == 0 && cnt == 10) { cnt = 11; };
            if (kind == 1 && cnt == 11) { cnt = 12; };
            if (kind == 0 && cnt == 12) { cnt = 13; };
            if (kind == 1 && cnt == 13) { cnt = 14; };
            return cnt;
        }//环岛计数
        byte kind_slopecnt(byte kind)
        {

            if (kind == 0 && cnt1 == 0) { cnt1 = 1; };
            if (kind == 3 && cnt1 == 1) { cnt1 = 2; };
            if (kind == 0 && cnt1 == 2) { cnt1 = 3; };
            if (kind == 3 && cnt1 == 3) { cnt1 = 4; };
            if (kind == 0 && cnt1 == 4) { cnt1 = 5; };
            if (kind == 3 && cnt1 == 5) { cnt1 = 6; };
            if (kind == 0 && cnt1 == 6) { cnt1 = 7; };
            if (kind == 3 && cnt1 == 7) { cnt1 = 8; };
            return cnt1;
        }//坡道计数
        byte kind_blockcnt(byte kind)
        {

            if (kind == 0 && cnt2 == 0) { cnt2 = 1; };
            if (kind == 1 && cnt2 == 1) { cnt2 = 2; };
            if (kind == 0 && cnt2 == 2) { cnt2 = 3; };
            if (kind == 1 && cnt2 == 3) { cnt2 = 4; };
            if (kind == 0 && cnt2 == 4) { cnt2 = 5; };
            if (kind == 1 && cnt2 == 5) { cnt2 = 6; };
            if (kind == 0 && cnt2 == 6) { cnt2 = 7; };
            if (kind == 1 && cnt2 == 7) { cnt2 = 8; };
            return cnt2;
        }//障碍计数
        
        byte Check_Overrun69(int i)
        {
            if (i < 0)
                return (byte)0;
            else if (i > 69)
                return (byte)69;
            else
                return (byte)i;
        }//防止十字斜率扫越界
        byte Check_Overrun199(int i)
        {
            if (i < 0)
                return (byte)0;
            else if (i > 199)
                return (byte)199;
            else
                return (byte)i;
        }//防止十字斜率扫越界

        void Get_lineeffect()//有效行的获取 值直接赋值给 lineeffect。建议只执行一次
        {

            if (crossflag == 1 && huandaoflag == 0)//主要用在effectline判断之前 十字中线重新左加右除以二
            {
                for (i = 0; i < cutline; i++)
                    LCenter[i] = (byte)((L_black[i] + R_black[i]) / 2);
            }
            for (j = 0; j < cutline; j++)//获得弯道有效行 必须放在 中线平移之前
            {
                for (i = 0; i < j; i++)
                {
                    temp = (byte)(LCenter[0] - (float)(LCenter[0] - LCenter[j]) / (float)j * i);
                    if (LCenter[i] > temp + 5 || LCenter[i] + 5 < temp)
                        break;
                }
                if (i == j)
                {
                    line_effet = j;
                }
                else
                {
                    break;
                }
            }


        }

				//egion
        void Image_Init()//把每场图像处理里数据里需要初始化的变量初始化
        {

            superfastflag = 0; longstraightflag = 0; shortstraightflag = 0;
            notstraightflag = 0; turnflag = 0; rightflag = 0; leftflag = 0;
            RowNum = 0; temp = 0;
            changeflag = 0; bianhuanflag = 0;
            L_SmallS_Flag1 = 0; L_SmallS_Flag2 = 0; L_SmallS_Flag3 = 0; L_SmallS_Flag4 = 0;
            R_SmallS_Flag1 = 0; R_SmallS_Flag2 = 0; R_SmallS_Flag3 = 0; R_SmallS_Flag4 = 0;
            Judge_SmallS = 0;
            bigsflag = 0;//中S
            L_BigS_Flag1 = 0; L_BigS_Flag2 = 0; L_BigS_Flag3 = 0; L_BigS_Flag4 = 0;
            R_BigS_Flag1 = 0; R_BigS_Flag2 = 0; R_BigS_Flag3 = 0; R_BigS_Flag4 = 0;
            changezuo = 0; changeyou = 0;
            leftall = 1; rightall = 1;
            tubianyou = 0; tubianzuo = 0;
            cutline = 69;
            wanruzuo1 = 0; wanruzuo2 = 0; wanruzuo3 = 0;
            wanruyou1 = 0; wanruyou2 = 0; wanruyou3 = 0;
            huandaozuoguai = 0; huandaoyouguai = 0;
            Lwhitezhi = 0; Rwhitezhi = 0;
            qingchuflag = 0; huandaoblackpoint = 0;
            zuotuchu = 0; zuotiaobian = 0;
            youtuchu = 0; youtiaobian = 0;
            ruflag = 1; Lxflag = 0; Rxflag = 0; CLxflag = 0; CRxflag = 0;
            //丢线行
            LoseFirst_L_Row = LoseFirst_R_Row = 0;
            LoseRepair_L_Row = LoseRepair_R_Row = 0;
            //直十字
            Cross_Straight_Flag = 0;
            Cross_Straight_Flag = 0;
            Cross_Straight_in = 0;
            Cross_Straight_L_in = Cross_Straight_R_in = 0;
            Cross_Straight_out = 0;
            Cross_Straight_L_out = Cross_Straight_R_out = 0;
            Cross_Straight_L_in_Row = Cross_Straight_R_in_Row = 69;
            //斜十字
            Cross_Lean_L_in = Cross_Lean_R_in = 0;
            Cross_Lean_L = Cross_Lean_R = 0;
            Cross_Lean_L_out = Cross_Lean_R_out = 0;
            Cross_Lean_L_in_Lose = Cross_Lean_R_in_Lose = 0;
            //无拐点十字
            Cross_NR_L_Memory_FindFlag = Cross_NR_R_Memory_FindFlag = 0;
            Cross_NR_L_180cnt = Cross_NR_R_180cnt = 0;
            Cross_NR_L_130cnt = Cross_NR_R_130cnt = 0;
            //全白十字
            Cross_Allwhite_L = Cross_Allwhite_R = 0;
            Cross_Allwhite = 0;
            //全白十字记忆、
            Cross_Allwhite2_R = Cross_Allwhite2_L = 0;
            Cross_Lean_Rmabye2 = Cross_Lean_Lmabye2 = 0;
            Cross_Pingyi = 0;//十字中线平移标志 
            //障碍 每场都置零 根据图像判断不需要标志位
            Obstruction_R = Obstruction_L = 0;
            crossflag = 0;
            Curve_Lianwan_L = 0;
            Curve_Lianwan_R = 0;
            huandaoyouflag1 = 0;
            crosscutflag = 0;
            Shizila_flagL = Shizila_flagR = 0;
            //环岛
            huandaozuoflag1 = 0;
            huandaoyouflag1 = 0;
        }
        void ImageProcess() //直接把循环放到这里
        {
            if (scancnt < 40)
            {
                scancnt++;
                if (scancnt == 40)
                {
                    scanchange = 1;
                }
            }

            for (RowNum = 0; RowNum < 70; RowNum++)
            {
                if (RowNum == 0)
                {

                    if (firstscan == 0)
                    {

                        Center_Scan(center, RowNum);
                        firstscan = 1;
                    }
                    if (firstscan == 1)
                    {
                        if (scanchange == 1)
                        {
                            Center_Scan(center, RowNum);

                        }
                        else
                        {
                            Edge_Scan(RowNum);

                            LCenter[RowNum] = (byte)((L_black[RowNum] + R_black[RowNum]) / 2);
                        }
                    }

                }
                else
                {
                    if (poflag == 0)
                    {
                        Edge_Scan(RowNum);
                    }
                    else
                    {
                        Center_Scan(LCenter[RowNum - 1], RowNum);
                    }
                    LCenter[RowNum] = (byte)((L_black[RowNum] + R_black[RowNum]) / 2);
                    if (huandaoflag == 1)
                    {
                        if (L_black[RowNum] == 199 && R_black[RowNum] != 0)
                        {
                            LCenter[RowNum] = (byte)(LCenter[RowNum - 1] + R_black[RowNum] - R_black[RowNum - 1]);
                            if (LCenter[RowNum - 1] + R_black[RowNum] - R_black[RowNum - 1] > 198)
                            {
                                LCenter[RowNum] = 199;
                            }
                            if (LCenter[RowNum - 1] + R_black[RowNum] - R_black[RowNum - 1] < 1)
                            {
                                LCenter[RowNum] = 0;
                            }

                        }
                        else if (R_black[RowNum] == 0 && L_black[RowNum] != 199)
                        {
                            LCenter[RowNum] = (byte)(LCenter[RowNum - 1] + L_black[RowNum] - L_black[RowNum - 1]);
                            if (LCenter[RowNum - 1] + L_black[RowNum] - L_black[RowNum - 1] < 1)
                            {
                                LCenter[RowNum] = 0;
                            }
                            if (LCenter[RowNum - 1] + L_black[RowNum] - L_black[RowNum - 1] > 198)
                            {
                                LCenter[RowNum] = 199;
                            }
                        }
                        else
                        {
                            LCenter[RowNum] = (byte)((L_black[RowNum] + R_black[RowNum]) / 2);
                        }
                    }

                }
                //n  十字
                if (huandaoflag == 0)
                {

                    if ((RowNum > 0 && RowNum < cutline && L_black[RowNum] == 199 && L_black[RowNum - 1] < 199) || (RowNum == 1 && L_black[RowNum] == 199))
                    {
                        LoseFirst_L_Row = RowNum;
                    }
                    if (RowNum > 0 && RowNum < cutline && L_black[RowNum - 1] == 199 && L_black[RowNum] < 199)
                    {

                        LoseRepair_L_Row = RowNum;
                    }
                    if ((RowNum > 0 && RowNum < cutline && R_black[RowNum] == 0 && R_black[RowNum - 1] > 0) || (RowNum == 1 && R_black[RowNum] == 0))
                    {
                        LoseFirst_R_Row = RowNum;
                    }
                    if (RowNum > 0 && RowNum < cutline && R_black[RowNum - 1] == 0 && R_black[RowNum] > 0)
                    {

                        LoseRepair_R_Row = RowNum;
                    }

                    //**********************十字**********************
                    //十字类型:直十字
                    //直十字 左拐点
                    if (Cross_Straight_Flag == 0 && Cross_Straight_L_in == 0 && Cross_No_RightAngle_L_Memory == 0 && Cross_No_RightAngle_R_Memory == 0
                       && Cross_Allwhite2 == 0
                       && (RowNum - 2) > 6 && (RowNum - 2) < 60 && (RowNum - 2) < cutline
                        && (RowNum - 2 < Cross_Straight_R_in_Row + 20)
                        )
                    {
                        //直十字条件： 尖角  横坐标范围  斜率
                        if (
                            ((L_black[RowNum - 4] - L_black[RowNum - 2] >= 0 || L_black[RowNum - 6] - L_black[RowNum - 2] >= 0) && L_black[RowNum] - L_black[RowNum - 2] > 0)
                            && ((L_black[RowNum - 2] > 40 && L_black[RowNum - 2] < 189 && RowNum - 2 <= 30) || (L_black[RowNum - 2] > 70 && L_black[RowNum - 2] < 179 && RowNum - 2 > 30))
                            && (L_black[RowNum - 4] - L_black[RowNum - 8] >= -4 || ((RowNum - 2) < 30 && (L_black[RowNum - 2] - L_black[0]) >= -(RowNum - 2)))
                            )
                        {
                            //往上找是白点  行的远近不同，判断的行数也不同
                            if (
                                (RowNum - 2 < 30 && P_Pixels[RowNum - 2 + 9][Check_Overrun199(L_black[RowNum - 2 + 6] + 25)] > 0) ||
                                (RowNum - 2 < 40 && P_Pixels[RowNum - 2 + 6][Check_Overrun199(L_black[RowNum - 2 + 6] + 25)] > 0) ||
                                (RowNum - 2 >= 40 && P_Pixels[RowNum - 2 + 4][Check_Overrun199(L_black[RowNum - 2 + 6] + 25)] > 0)
                                )
                            {
                                Cross_Straight_L_in = 1;
                                Cross_Straight_L_in_Row = (byte)(RowNum - 2);
                                Cross_Straight_L_in_Rank = L_black[RowNum - 2];
                                if (Cross_Straight_R_in == 0)
                                {
                                    if (RowNum - 2 > 15)
                                    {
                                        Cross_Straight_L_Slope = (float)(L_black[RowNum - 2] - L_black[RowNum - 17]) / (float)(15);
                                        Cross_Straight_R_Slope = (float)(R_black[RowNum - 2] - R_black[RowNum - 17]) / (float)(15);
                                    }
                                    else
                                    {
                                        Cross_Straight_L_Slope = (float)(L_black[RowNum - 2] - L_black[0]) / (float)(RowNum - 2);
                                        Cross_Straight_R_Slope = (float)(R_black[RowNum - 2] - R_black[0]) / (float)(RowNum - 2);
                                    }
                                }
                                //斜十字但是边线斜率比较小的情况  有待改进
                                if (Cross_Straight_R_in == 0 && R_black[Cross_Straight_L_in_Row] < 5 && (L_black[RowNum] - R_black[RowNum] >= (fixValue[RowNum] + 10)))
                                {
                                    Cross_Straight_L_in = 0;
                                    Cross_Lean_L_in = 1;
                                    Cross_Lean_L_in_Row = Cross_Straight_L_in_Row;
                                    Cross_Lean_L_in_Rank = Cross_Straight_L_in_Rank;
                                    Cross_Lean_L_Slope = Cross_Straight_L_Slope;
                                }
                            }
                        }
                    }

                    //直十字右拐点  
                    if (Cross_Straight_Flag == 0 && Cross_Straight_R_in == 0 && Cross_No_RightAngle_R_Memory == 0 && Cross_No_RightAngle_L_Memory == 0
                       && Cross_Allwhite2 == 0
                         && (RowNum - 2) > 6 && (RowNum - 2) < 60 && (RowNum - 2) < cutline
                        && (RowNum - 2 < Cross_Straight_L_in_Row + 20)
                        )
                    {
                        //直十字条件 尖角 横坐标范围 斜率
                        if (
                            ((R_black[RowNum - 2] - R_black[RowNum - 4] >= 0 || R_black[RowNum - 2] - R_black[RowNum - 6] >= 0) && R_black[RowNum - 2] - R_black[RowNum] > 0)
                            && ((R_black[RowNum - 2] < 159 && R_black[RowNum - 2] > 10 && RowNum - 2 <= 30) || (R_black[RowNum - 2] < 129 && R_black[RowNum - 2] > 20 && RowNum - 2 > 30))
                          && ((R_black[RowNum - 4] - R_black[RowNum - 8] <= 4) || ((RowNum - 2) < 30 && (R_black[RowNum - 2] - R_black[0]) <= (RowNum - 2)))
                            )
                        {
                            if ((RowNum - 2 < 30 && P_Pixels[RowNum - 2 + 9][Check_Overrun199(R_black[RowNum - 2 + 6] - 25)] > 0)
                                || (RowNum - 2 < 40 && P_Pixels[RowNum - 2 + 6][Check_Overrun199(R_black[RowNum - 2 + 6] - 25)] > 0)
                                || (RowNum - 2 >= 40 && P_Pixels[RowNum - 2 + 4][Check_Overrun199(R_black[RowNum - 2 + 6] - 25)] > 0)
                                )
                            {
                                Cross_Straight_R_in = 1;
                                Cross_Straight_R_in_Row = (byte)(RowNum - 2);
                                Cross_Straight_R_in_Rank = R_black[RowNum - 2];

                                //一边找到拐点时就记下斜率，当找到两个拐点时根据斜率找点
                                if (Cross_Straight_L_in == 0)
                                {
                                    if (RowNum - 2 > 15)
                                    {
                                        Cross_Straight_L_Slope = (float)(L_black[RowNum - 2] - L_black[RowNum - 17]) / (float)(15);
                                        Cross_Straight_R_Slope = (float)(R_black[RowNum - 2] - R_black[RowNum - 17]) / (float)(15);
                                    }
                                    else
                                    {
                                        Cross_Straight_L_Slope = (float)(L_black[RowNum - 2] - L_black[0]) / (float)(RowNum - 2);
                                        Cross_Straight_R_Slope = (float)(R_black[RowNum - 2] - R_black[0]) / (float)(RowNum - 2);
                                    }
                                }
                                //斜十字但是边线斜率比较小的情况  有待改进
                                if (Cross_Straight_L_in == 0 && L_black[Cross_Straight_R_in_Row] > 195 && (L_black[RowNum] - R_black[RowNum] >= (fixValue[RowNum] + 10)))
                                {
                                    Cross_Straight_R_in = 0;
                                    Cross_Lean_R_in = 1;
                                    Cross_Lean_R_in_Row = Cross_Straight_R_in_Row;
                                    Cross_Lean_R_in_Rank = Cross_Straight_R_in_Rank;
                                    Cross_Lean_R_Slope = Cross_Straight_R_Slope;
                                }
                            }
                        }
                    }
                    //当找到两个个拐点时，判断成扫线进入十字
                    if (
                        ((Cross_Straight_L_in == 1 && Cross_Straight_R_in == 1) ||
                        (Cross_Lean_L_in == 1 && Cross_Straight_R_in == 1) ||
                        (Cross_Straight_L_in == 1 && Cross_Lean_R_in == 1) ||
                       (Cross_Lean_L_in == 1 && Cross_Lean_R_in == 1)
                        )
                        && Cross_Straight_in == 0)
                    {
                        Cross_Straight_in = 1;
                        if (!(Cross_Straight_L_in == 1 && Cross_Straight_R_in == 1))
                        {
                            if (Cross_Lean_L_in == 1)
                            {
                                Cross_Straight_L_in_Row = Cross_Lean_L_in_Row;
                                Cross_Straight_L_in_Rank = Cross_Lean_L_in_Rank;
                            }
                            if (Cross_Lean_R_in == 1)
                            {
                                Cross_Straight_R_in_Row = Cross_Lean_R_in_Row;
                                Cross_Straight_R_in_Rank = Cross_Lean_R_in_Rank;
                            }
                        }

                        Cross_Lean_L_in = Cross_Lean_R_in = 0;
                    }
                    //扫线出直十字的判断
                    if (Cross_Straight_in == 1)
                    {
                        //左
                        if (Cross_Straight_L_out == 0)
                        {
                            //之前有过丢线，并且这行比上一行有跳变
                            if (
                                RowNum > Cross_Straight_L_in_Row + 10
                                && RowNum < Cross_Straight_L_in_Row + 40
                                && L_black[RowNum - 1] - L_black[RowNum - 2] < -5
                                && L_black[RowNum - 1] < 180
                                //&& L_black[RowNum ] - L_black[RowNum - 1]<=0
                                )
                            {
                                Cross_Straight_L_out = 1;//////////
                                Cross_Straight_L_outcnt = 0;

                            }
                        }
                        if (Cross_Straight_L_out == 1)
                        {
                            Cross_Straight_L_outcnt++;
                            if ((L_black[RowNum] - L_black[RowNum - 1] >= -3) && (L_black[RowNum] - L_black[RowNum - 1] <= 3))
                            {
                                Cross_Straight_L_out = 2;
                                Cross_Straight_L_out_Row = RowNum;
                                Cross_Straight_L_out_Rank = L_black[RowNum];
                            }
                            if (Cross_Straight_L_outcnt >= 5)
                            {
                                Cross_Straight_L_out = 2;
                                Cross_Straight_L_out_Row = RowNum;
                                Cross_Straight_L_out_Rank = L_black[RowNum];
                            }
                        }

                        ///右
                        if (Cross_Straight_R_out == 0)
                        {
                            //之前有过丢线，并且这行比上一行有跳变
                            if (RowNum > Cross_Straight_R_in_Row + 10
                                && RowNum < Cross_Straight_R_in_Row + 40
                                && R_black[RowNum - 1] - R_black[RowNum - 2] > 5
                                && R_black[RowNum - 1] > 20
                                //&& R_black[RowNum ] - R_black[RowNum - 1]>=0
                                )
                            {
                                Cross_Straight_R_out = 1;
                                Cross_Straight_R_outcnt = 0;

                            }
                        }
                        if (Cross_Straight_R_out == 1)
                        {
                            Cross_Straight_R_outcnt++;
                            if ((R_black[RowNum] - R_black[RowNum - 1] > -3) && (R_black[RowNum] - R_black[RowNum - 1] < 3))
                            {
                                Cross_Straight_R_out = 2;
                                Cross_Straight_R_out_Row = RowNum;
                                Cross_Straight_R_out_Rank = R_black[RowNum];
                            }
                            if (Cross_Straight_R_outcnt >= 5)
                            {
                                Cross_Straight_R_out = 2;
                                Cross_Straight_R_out_Row = RowNum;
                                Cross_Straight_R_out_Rank = R_black[RowNum];
                            }
                        }
                        //如果40行之内都没有跳变，就不是十字
                        if ((RowNum - (Cross_Straight_L_in_Row)) > 40 && (RowNum - (Cross_Straight_R_in_Row)) > 40)
                        {
                            Cross_Straight_in = Cross_Straight_out = 0;
                        }
                    }
                    //确定为为直十字
                    if (Cross_Straight_Flag == 0 && Cross_Straight_R_out == 2 && Cross_Straight_L_out == 2)
                    {
                        Cross_Straight_in = 0;
                        Cross_Straight_out = 1;
                        Cross_Straight_Flag = 1;
                    }

                    //十字类型：斜十字

                    //左拐点斜入十字
                    if (RowNum > 6 && RowNum < 50 && RowNum < cutline
                         // && Roundabout_R == 0 && Roundabout_L == 0
                         && Cross_Straight_Flag == 0 && Cross_Lean_L_in == 0 && Cross_Lean_L_out == 0 && Cross_No_RightAngle_L_Memory == 0
                       && Cross_Allwhite2 == 0
                        && Cross_Straight_in == 0)
                    {
                        if (
                        (L_black[RowNum - 4] - L_black[RowNum - 2] >= 0 || L_black[RowNum - 6] - L_black[RowNum - 2] >= 0) && (L_black[RowNum] - L_black[RowNum - 2]) > 0
                        && L_black[RowNum - 2] < 194 && R_black[RowNum - 2] < 6 && P_Pixels[RowNum - 2 + 4][L_black[RowNum - 2] + 5] > 0
                         && P_Pixels[RowNum - 2 + 7][Check_Overrun199(L_black[RowNum - 2] + 11)] > 0
                       && (L_black[RowNum - 2] - L_black[RowNum - 6] < -4 //斜率条件
                       || ((RowNum - 2) < 30 && (L_black[RowNum - 2] - L_black[0]) < -(RowNum - 5))
                       || ((RowNum - 2) > 30 && (L_black[RowNum - 2] - L_black[RowNum - 2 - 15]) < -15)
                       || ((RowNum - 2) < 30 && (L_black[RowNum - 2] - L_black[0]) >= -(RowNum - 5) && R_black[RowNum - 2] <= 195)
                       )
                         )
                        {
                            Cross_Lean_L_in = 1;
                            Cross_Lean_L_in_Row = (byte)(RowNum - 2);
                            Cross_Lean_L_in_Rank = L_black[RowNum - 2];
                            if (RowNum - 2 > 15)
                                Cross_Lean_L_Slope = (L_black[RowNum - 2] - L_black[RowNum - 17]) / (float)15.0;
                            else
                                Cross_Lean_L_Slope = (L_black[RowNum - 2] - L_black[0]) / (float)(RowNum - 2);


                            Cross_Lean_L_Saoxian = 1;
                            Cross_NR_L_180cnt = 0;

                        }
                    }
                    //右拐点斜入十字
                    if (RowNum > 6 && RowNum < 50 && RowNum < cutline
                        //  && Roundabout_R == 0 && Roundabout_L == 0
                        && Cross_Straight_Flag == 0 && Cross_Lean_R_in == 0 && Cross_Lean_R_out == 0 && Cross_No_RightAngle_R_Memory == 0
                       && Cross_Allwhite2 == 0
                        && Cross_Straight_in == 0)
                    {
                        if (
                        (R_black[RowNum - 2] - R_black[RowNum - 4] >= 0 && R_black[RowNum - 2] - R_black[RowNum] > 0)
                        && R_black[RowNum - 2] > 5 && L_black[RowNum - 2] > 195
                        && P_Pixels[RowNum - 2 + 4][R_black[RowNum - 2] - 5] > 0 && P_Pixels[RowNum - 2 + 7][Check_Overrun199(R_black[RowNum - 2] - 11)] > 0
                        && (R_black[RowNum - 2] - R_black[RowNum - 6] > 4
                        || ((RowNum - 20) < 30 && (R_black[RowNum - 2] - R_black[0]) > (RowNum - 5))
                        || ((RowNum - 20) > 30 && (R_black[RowNum - 2] - R_black[RowNum - 2 - 15]) > (15))
                        || ((RowNum - 20) < 30 && (R_black[RowNum - 2] - R_black[0]) <= (RowNum - 5) && L_black[RowNum - 2] >= 195)
                        )

                        )
                        {
                            Cross_Lean_R_in = 1;
                            Cross_Lean_R_in_Row = (byte)(RowNum - 2);
                            Cross_Lean_R_in_Rank = R_black[RowNum - 2];


                            if (RowNum - 2 > 15)
                                Cross_Lean_R_Slope = (R_black[RowNum - 2] - R_black[RowNum - 17]) / (float)15.0;
                            else
                                Cross_Lean_R_Slope = (R_black[RowNum - 2] - R_black[0]) / (float)(RowNum - 2);
                            Cross_Lean_R_Saoxian = 1;
                            Cross_NR_R_180cnt = 0;


                        }
                    }

                    //左拐点斜出十字
                    if (RowNum < cutline && (Cross_Lean_L_in == 1))
                    {
                        if (RowNum < (Cross_Lean_L_in_Row + 40)
                            && RowNum > (Cross_Lean_L_in_Row + 10)
                            && L_black[RowNum - 1] - L_black[RowNum] > 8 && L_black[RowNum] > 0
                            )//区别用斜率从赛道扫线出去的跳变
                        {

                            Cross_Lean_L_in = 0;
                            Cross_Lean_L = Cross_Lean_L_out = 1;
                            Cross_Lean_L_out_Row = (byte)(RowNum);
                            Cross_Lean_L_out_Rank = L_black[RowNum];
                            j = 0;
                            for (i = Cross_Lean_L_in_Row; i < Cross_Lean_L_out_Row; i++)
                            {
                                if (L_black[i + 2] < L_black[i])
                                    j++;
                            }
                            if (j > (Cross_Lean_L_out_Row - Cross_Lean_L_in_Row) / 2)
                            {

                                Cross_Lean_L = 0;
                            }

                            if (Cross_Straight_L_in == 1 && Cross_Lean_L == 1)
                            {
                                Cross_Straight_L_in = 0;
                                Cross_Lean_L_in_Row = Cross_Straight_L_in_Row;
                                Cross_Lean_L_in_Rank = Cross_Straight_L_in_Rank;
                            }

                        }
                    }
                    //右拐点斜出十字
                    if (RowNum < cutline && RowNum - Cross_Lean_R_in_Row > 5

                        && (Cross_Lean_R_in == 1))
                    {
                        if (RowNum < (Cross_Lean_R_in_Row + 40)
                            && RowNum > (Cross_Lean_R_in_Row + 10)
                            && R_black[RowNum - 1] - R_black[RowNum] < -8 && R_black[RowNum] < 199

                            )
                        {
                            Cross_Lean_R_in = 0;
                            Cross_Lean_R = Cross_Lean_R_out = 1;
                            Cross_Lean_R_out_Row = (byte)(RowNum);
                            Cross_Lean_R_out_Rank = R_black[RowNum];

                            j = 0;
                            for (i = Cross_Lean_R_in_Row; i < Cross_Lean_R_out_Row; i++)
                            {
                                if (L_black[i + 2] < L_black[i])
                                    j++;
                            }
                            if (j > (Cross_Lean_R_out_Row - Cross_Lean_R_in_Row) / 2)
                            {

                                Cross_Lean_R = 0;
                            }
                            if (Cross_Straight_R_in == 1 && Cross_Lean_R == 1)
                            {
                                Cross_Straight_R_in = 0;
                                Cross_Lean_R_in_Row = Cross_Straight_R_in_Row;
                                Cross_Lean_R_in_Rank = Cross_Straight_R_in_Rank;
                            }

                        }
                    }
                    //十字类型：斜十字记忆 ：无拐点十字
                    //无拐点十字
                    //清除标志 为了延迟一场清除无拐点标志
                    if (Cross_No_RightAngle_L_Memory == 2)
                        Cross_No_RightAngle_L_Memory = 0;
                    if (Cross_No_RightAngle_R_Memory == 2)
                        Cross_No_RightAngle_R_Memory = 0;
                    //清除拐点标志的判断
                    //左
                    if (Cross_No_RightAngle_L_Memory == 1)
                    {
                        if (L_black[RowNum] - R_black[RowNum] > 180 && RowNum < cutline)
                            Cross_NR_L_180cnt++;
                        if (L_black[RowNum] - R_black[RowNum] > 130 && RowNum < cutline)
                            Cross_NR_L_130cnt++;
                        //这里的Memory标志等于二相当于下一场才会清除无拐点标志，防止这场就清除造成不补线
                        if (RowNum == 69
                            && Cross_Allwhite == 1)
                        {

                            Cross_No_RightAngle_L_Memory = 0;
                            // Cross_Allwhite = 0;
                        }
                        //行数大于上一场跳变行 一定范围就清除无拐点标志
                        if (((RowNum - 12) > (Cross_NR_L_Memory_out_Row + 10) || (RowNum - 12) > 55)
                            && (Cross_NR_L_Memory_FindFlag == 0 || Cross_NR_L_130cnt < 2))
                        {
                            Cross_No_RightAngle_L_Memory = 0;


                        }


                        //对于左右无拐点十字，如果其中一个跳变找不到就清除左右无拐点标志
                        //if ((Cross_No_RightAngle_L_Memory == 0 || Cross_No_RightAngle_L_Memory == 2) && Cross_No_RightAngle_R_Memory == 1)
                        //{
                        //    Cross_No_RightAngle_R_Memory = 2;

                        //}

                    }
                    //右
                    if (Cross_No_RightAngle_R_Memory == 1)
                    {
                        if (L_black[RowNum] - R_black[RowNum] > 180 && RowNum < cutline)
                            Cross_NR_R_180cnt++;
                        if (L_black[RowNum] - R_black[RowNum] > 130 && RowNum < cutline)
                            Cross_NR_R_130cnt++;
                        if (RowNum == 69 &&
                            Cross_Allwhite == 1)
                        {

                            Cross_No_RightAngle_R_Memory = 2;
                            Cross_Allwhite = 0;
                        }
                        if (((RowNum - 12) > (Cross_NR_R_Memory_out_Row + 10) || (RowNum - 12) > 55)
                            && (Cross_NR_R_Memory_FindFlag == 0 || Cross_NR_R_130cnt < 2))
                        {

                            Cross_No_RightAngle_R_Memory = 0;
                        }


                        //if ((Cross_No_RightAngle_R_Memory == 0 || Cross_No_RightAngle_R_Memory == 2) && Cross_No_RightAngle_L_Memory == 1)
                        //{
                        //    Cross_No_RightAngle_L_Memory = 2;

                        //}
                    }
                    //如果是因为全白才清除无拐点标志就，设置一个可能是全白十字标志位
                    if (RowNum == 65 && (Cross_No_RightAngle_L_Memory == 2 || Cross_No_RightAngle_R_Memory == 2))
                    {
                        Cross_Allwhite_Maybe = 1;
                        Cross_Allwhite_L_out_Row = Cross_Allwhite_R_out_Row = 40;
                        Cross_Allwhite_L_start = Cross_NR_L_Memory_out_Rank;
                        Cross_Allwhite_R_start = Cross_NR_R_Memory_out_Rank;
                    }

                    //如果是全白十字也要设置一个扫线标志位
                    else if (RowNum == 65 && Cross_Allwhite == 1)
                    {

                        Cross_Allwhite_Maybe = 1;
                        Cross_Allwhite_L_start = Cross_Allwhite_L_out_Rank;
                        Cross_Allwhite_R_start = Cross_Allwhite_R_out_Rank;
                    }
                    //如果是全白十字记忆  也要设置一个扫线标志位
                    else if (RowNum == 65 && Cross_Allwhite2 == 1)
                    {
                        Cross_Allwhite_L_start = L_black[Cross_Allwhite2_L_out_Row];
                        Cross_Allwhite_R_start = R_black[Cross_Allwhite2_R_out_Row];
                    }
                    else if (RowNum == 65)
                    {

                        Cross_Allwhite_Maybe = 0;
                    }
                    //有无拐点十字标志时 找出十字跳变行
                    //左
                    if (RowNum > 12 && (RowNum - 12) < 50 && (RowNum - 12) < cutline
                       && Cross_No_RightAngle_L_Memory == 1 && Cross_NR_L_Memory_FindFlag == 0
                          && RowNum - 12 < (Cross_NR_L_Memory_out_Row + 10)
                          && RowNum - 12 > (Cross_NR_L_Memory_out_Row - 10)
                        )
                    {
                        if (L_black[RowNum - 12] - L_black[RowNum - 10] > 5 && L_black[RowNum - 9] < 194
                            && L_black[RowNum - 7] - L_black[RowNum - 10] <= 0//白赛道上黑色的点扫线产生跳变
                            )
                        {
                            //找到跳变小的行数，作为补线行，这也是倒着找跳变点的原因
                            for (i = (byte)(RowNum - 10); i < (RowNum - 4); i++)
                            {
                                if (L_black[i] - L_black[i - 1] < 3 && L_black[i] - L_black[i - 1] > -3)
                                    break;
                            }
                            Cross_NR_L_Memory_FindFlag = 1;
                            Cross_NR_L_Memory_in_Rank = L_black[0];
                            Cross_NR_L_Memory_out_Row = i;
                            Cross_NR_L_Memory_out_Rank = L_black[i];
                            Cross_NR_L_Memory_Slope = (float)(Cross_NR_L_Memory_out_Rank - Cross_NR_L_Memory_in_Rank) / (float)(Cross_NR_L_Memory_out_Row);
                            if (Cross_No_RightAngle_R_Memory == 1)
                            {

                                Cross_NR__Memory_out_Row = Cross_NR_L_Memory_out_Row;
                            }
                        }
                    }

                    //右
                    if (RowNum > 12 && (RowNum - 12) < 50 && (RowNum - 12) < cutline
                        && Cross_No_RightAngle_R_Memory == 1 && Cross_NR_R_Memory_FindFlag == 0
                        && RowNum - 12 < (Cross_NR_R_Memory_out_Row + 10)
                        && RowNum - 12 > (Cross_NR_R_Memory_out_Row - 10)
                        )
                    {
                        if (R_black[RowNum - 12] - R_black[RowNum - 10] < -5 && R_black[RowNum - 9] > 5
                            && R_black[RowNum - 7] - R_black[RowNum - 10] >= 0
                            )
                        {
                            for (i = (byte)(RowNum - 10); i < (RowNum - 4); i++)
                            {
                                if (R_black[i] - R_black[i - 1] < 3 && R_black[i] - R_black[i - 1] > -3)
                                    break;
                            }
                            Cross_NR_R_Memory_FindFlag = 1;
                            Cross_NR_R_Memory_in_Rank = R_black[0];
                            Cross_NR_R_Memory_out_Row = (byte)(i);
                            Cross_NR_R_Memory_out_Rank = R_black[i];
                            Cross_NR_R_Memory_Slope = (float)(Cross_NR_R_Memory_out_Rank - Cross_NR_R_Memory_in_Rank) / (float)(Cross_NR_R_Memory_out_Row);
                            if (Cross_No_RightAngle_L_Memory == 1)
                            {
                                Cross_NR__Memory_out_Row = Cross_NR_R_Memory_out_Row;

                            }

                        }
                    }

                    //左右无拐点  在一场结束之后判断 第二场开始补线
                    if (RowNum == 69 && Cross_Straight_Flag == 1 && (Cross_Straight_L_in_Row < 15 || Cross_Straight_R_in_Row < 15))
                    {
                        Cross_NR_R_Memory_in_Rank = Cross_Straight_R_in_Rank;
                        Cross_NR_R_Memory_out_Row = Cross_Straight_R_out_Row;
                        Cross_NR_R_Memory_out_Rank = Cross_Straight_R_out_Rank;
                        Cross_NR_R_Memory_Slope = (float)(Cross_NR_R_Memory_out_Rank - Cross_NR_R_Memory_in_Rank) / (float)(Cross_NR_R_Memory_out_Row);
                        Cross_No_RightAngle_R_Memory = 1;
                        Cross_NR_L_Memory_in_Rank = Cross_Straight_L_in_Rank;
                        Cross_NR_L_Memory_out_Row = Cross_Straight_L_out_Row;
                        Cross_NR_L_Memory_out_Rank = Cross_Straight_L_out_Rank;
                        Cross_NR_L_Memory_Slope = (float)(Cross_NR_L_Memory_out_Rank - Cross_NR_L_Memory_in_Rank) / (float)(Cross_NR_L_Memory_out_Row);
                        Cross_No_RightAngle_L_Memory = 1;
                        Cross_NR__Memory_out_Row = Cross_NR_L_Memory_out_Row > Cross_NR_R_Memory_out_Row ? Cross_NR_L_Memory_out_Row : Cross_NR_R_Memory_out_Row;
                        Cross_NR_LR_cnt = 30;
                        Cross_NR_L_start = L_black[Check_Overrun69(Cross_NR_L_Memory_out_Row + 5)];
                        Cross_NR_R_start = R_black[Check_Overrun69(Cross_NR_R_Memory_out_Row + 5)];

                    }

                    //左无拐点十字第一场  
                    if (RowNum == 69 && Cross_Lean_L == 1 && Cross_Lean_L_in_Row < 20
                       && Cross_No_RightAngle_L_Memory == 0
                        )
                    {
                        Cross_NR_L_Memory_in_Rank = Cross_Lean_L_in_Rank;
                        Cross_NR_R_Memory_out_Row = Cross_NR_L_Memory_out_Row = Cross_Lean_L_out_Row;
                        Cross_NR_L_Memory_out_Rank = Cross_Lean_L_out_Rank;
                        Cross_NR_L_Memory_Slope = (float)(Cross_NR_L_Memory_out_Rank - Cross_NR_L_Memory_in_Rank) / (float)(Cross_NR_L_Memory_out_Row);
                        Cross_No_RightAngle_L_Memory = 1;
                        Cross_NR_L_cnt = 30;
                        Cross_NR_L_start = L_black[Check_Overrun69(Cross_NR_L_Memory_out_Row + 5)];
                        Cross_NR_R_start = R_black[Check_Overrun69(Cross_NR_R_Memory_out_Row + 5)];

                    }
                    //右
                    if (RowNum == 69 && Cross_Lean_R == 1 && Cross_Lean_R_in_Row < 20 && Cross_No_RightAngle_R_Memory == 0)
                    {
                        Cross_NR_R_Memory_in_Rank = Cross_Lean_R_in_Rank;
                        Cross_NR_L_Memory_out_Row = Cross_NR_R_Memory_out_Row = Cross_Lean_R_out_Row;
                        Cross_NR_R_Memory_out_Rank = Cross_Lean_R_out_Rank;
                        Cross_NR_R_Memory_Slope = (float)(Cross_NR_R_Memory_out_Rank - Cross_NR_R_Memory_in_Rank) / (float)(Cross_NR_R_Memory_out_Row);
                        Cross_No_RightAngle_R_Memory = 1;
                        Cross_NR_R_cnt = 30;
                        Cross_NR_L_start = L_black[Check_Overrun69(Cross_NR_L_Memory_out_Row + 5)];
                        Cross_NR_R_start = R_black[Check_Overrun69(Cross_NR_R_Memory_out_Row + 5)];

                    }


                    //十字类型：第一行全白的十字


                    if (Cross_Allwhite == 0 && Cross_Allwhite_R == 3 && Cross_Allwhite_L == 3)
                    {

                        Cross_Allwhite = 1;
                    }
                    if (
                        //Roundabout_R == 0 && Roundabout_L == 0 &&
                        Cross_Allwhite_L == 2 && (RowNum - 10) < 55 && (RowNum - 10) < (cutline - 20))
                    {
                        if (RowNum - 10 > 0
                            && (L_black[RowNum - 11] - L_black[RowNum - 10] > 5) && L_black[RowNum - 10] < 190
                            && P_Pixels[RowNum - 9][Check_Overrun199(L_black[RowNum - 10] + 5)] == 0)
                        {
                            for (i = (byte)(RowNum - 10); i < RowNum; i++)
                            {
                                if (L_black[i] - L_black[i + 1] < 4 && L_black[i] - L_black[i + 1] > -4)
                                    break;
                            }
                            Cross_Allwhite_L = 3;
                            Cross_Allwhite_L_out_Row = i;
                            Cross_Allwhite_L_out_Rank = L_black[i];
                        }
                    }
                    if (
                        //Roundabout_R == 0 && Roundabout_L == 0 &&
                        Cross_Allwhite_R == 2 && (RowNum - 10) < 55 && (RowNum - 10) < (cutline - 20))
                    {
                        if (RowNum - 10 > 0
                            && (R_black[RowNum - 11] - R_black[RowNum - 10] < -5) && R_black[RowNum - 10] > 10
                            && P_Pixels[RowNum - 9][Check_Overrun199(R_black[RowNum - 10] - 5)] == 0)
                        {
                            for (i = (byte)(RowNum - 10); i < RowNum; i++)
                            {
                                if (R_black[i] - R_black[i + 1] < 4 && R_black[i] - R_black[i + 1] > -4)
                                    break;
                            }
                            Cross_Allwhite_R = 3;
                            Cross_Allwhite_R_out_Row = i;
                            Cross_Allwhite_R_out_Rank = R_black[i];
                        }
                    }

                    //找到丢线到不丢线的行
                    if (Cross_Allwhite_L == 1 && RowNum < 50)
                    {
                        if (LoseRepair_L_Row > 0)
                        {
                            Cross_Allwhite_L = 2;
                        }
                    }
                    if (Cross_Allwhite_R == 1 && RowNum < 50)
                    {
                        if (LoseRepair_R_Row > 0)
                        {
                            Cross_Allwhite_R = 2;
                        }
                    }

                    //找到全白
                    if (
                        Cross_Allwhite2 == 0
                        && Cross_Allwhite_L == 0 && Cross_Allwhite_R == 0 && RowNum < 5 && L_black[RowNum] > 196 && R_black[RowNum] < 4)
                    {
                        Cross_Allwhite_L = 1;
                        Cross_Allwhite_R = 1;
                    }
                    //*********************全白十字记忆2****************
                    if (Cross_Allwhite2 == 1 && Cross_Allwhite2_L == 0
                       && RowNum - 10 < Cross_Allwhite2_L_out_Row + 10 && RowNum - 10 > 0
                       && L_black[RowNum - 10] - L_black[RowNum - 11] < -5
                       && L_black[RowNum - 10] < 185)
                    {
                        Cross_Allwhite2_L = 1;
                        Cross_Allwhite2_L_out_Row = (byte)(RowNum - 10);
                        for (i = (byte)(RowNum - 10); i < RowNum; i++)
                        {
                            if (L_black[RowNum + 1] - L_black[RowNum] <= 3 && L_black[RowNum + 1] - L_black[RowNum] >= -3)
                            {
                                Cross_Allwhite2_L_out_Row = i;
                                break;
                            }
                        }
                    }

                    if (Cross_Allwhite2 == 1 && Cross_Allwhite2_R == 0
                       && RowNum - 10 < Cross_Allwhite2_R_out_Row + 10 && RowNum - 10 > 0
                       && R_black[RowNum - 10] - R_black[RowNum - 11] > 5
                       && R_black[RowNum - 10] >= 15)
                    {
                        Cross_Allwhite2_R = 1;
                        Cross_Allwhite2_R_out_Row = (byte)(RowNum - 10);
                        for (i = (byte)(RowNum - 10); i < RowNum; i++)
                        {
                            if (R_black[RowNum + 1] - R_black[RowNum] <= 3 && R_black[RowNum + 1] - R_black[RowNum] >= -3)
                            {
                                Cross_Allwhite2_R_out_Row = i;
                                break;
                            }
                        }
                    }


                    //进直十字的时候根据斜率扫线，Cross_Straight_out==1时就不按斜率
                    if (Cross_Straight_in == 1)
                    {
                        /////用户自定义(111);
                        L_Find_Start = Check_Overrun199((int)(L_black[Cross_Straight_L_in_Row] + Cross_Straight_L_Slope * (RowNum - Cross_Straight_L_in_Row)));
                        R_Find_Start = Check_Overrun199((int)(R_black[Cross_Straight_R_in_Row] + Cross_Straight_R_Slope * (RowNum - Cross_Straight_R_in_Row)));
                    }
                    //斜十字  右
                    else if (Cross_Lean_R_in == 1 && Cross_Lean_R_Saoxian == 1)
                    {
                        ////用户自定义(222);
                        R_Find_Start = Check_Overrun199((int)(R_black[Cross_Lean_R_in_Row] + Cross_Lean_R_Slope * (RowNum - Cross_Lean_R_in_Row)));
                        if (L_black[RowNum] - R_Find_Start <= 3)//如果左右线之差很小或者为负数就清除沿斜率扫线
                        {
                            R_Find_Start = R_black[RowNum];
                            //  Cross_Lean_R_in =
                            Cross_Lean_R_Saoxian = 0;
                        }
                        L_Find_Start = L_black[RowNum];
                        if (R_Find_Start >= 198)
                        {
                            Cross_Lean_R_in_Lose = 1;
                        }

                    }
                    else if (Cross_Lean_L_in == 1 && Cross_Lean_L_Saoxian == 1)
                    {
                        ////用户自定义(333);

                        L_Find_Start = Check_Overrun199((int)(L_black[Cross_Lean_L_in_Row] + Cross_Lean_L_Slope * (RowNum - Cross_Lean_L_in_Row)));

                        if (L_Find_Start - R_black[RowNum] <= 3)//如果左右线之差很小或者为负数就清除沿斜率扫线
                        {
                            L_Find_Start = L_black[RowNum];
                            // Cross_Lean_L_in = 
                            Cross_Lean_L_Saoxian = 0;
                        }
                        R_Find_Start = R_black[RowNum];
                        if (L_Find_Start <= 1)
                        {
                            Cross_Lean_L_in_Lose = 1;
                        }
                    }
                    ////无拐点十字  左
                    //else if (Cross_No_RightAngle_L_Memory == 1 && Cross_No_RightAngle_R_Memory == 0 && RowNum < (Cross_NR_L_Memory_out_Row + 10))
                    //{


                    //    L_Find_Start = Check_Overrun199((int)(-10 + Cross_NR_L_Memory_in_Rank + Cross_NR_L_Memory_Slope * (RowNum)));
                    //    R_Find_Start = R_black[RowNum];
                    //}
                    ////右
                    //else if (Cross_No_RightAngle_L_Memory == 0 && Cross_No_RightAngle_R_Memory == 1 && RowNum < (Cross_NR_R_Memory_out_Row + 10))
                    //{
                    //    L_Find_Start = L_black[RowNum];
                    //    R_Find_Start = Check_Overrun199((int)(10 + Cross_NR_R_Memory_in_Rank + Cross_NR_R_Memory_Slope * (RowNum)));
                    //}
                    ////左右无拐点十字
                    //else if (Cross_No_RightAngle_L_Memory == 1 && Cross_No_RightAngle_R_Memory == 1 && RowNum < (Cross_NR__Memory_out_Row + 10))
                    //{
                    //    // Lcr[RowNum].LEnd=
                    //    L_Find_Start = Check_Overrun199((int)(-10 + Cross_NR_L_Memory_in_Rank + Cross_NR_L_Memory_Slope * (RowNum)));
                    //    // Lcr[RowNum].REnd =
                    //    R_Find_Start = Check_Overrun199((int)(10 + Cross_NR_R_Memory_in_Rank + Cross_NR_R_Memory_Slope * (RowNum)));
                    //}
                    else if (Cross_No_RightAngle_L_Memory > 0 || Cross_No_RightAngle_R_Memory > 0)
                    {
                        //   //用户自定义(444);
                        if (RowNum < Cross_NR_L_Memory_out_Row + 5)
                            L_Find_Start = Check_Overrun199(Cross_NR_L_start - 5);
                        else
                            L_Find_Start = L_black[RowNum];

                        if (RowNum < Cross_NR_R_Memory_out_Row + 5)
                            R_Find_Start = Check_Overrun199(Cross_NR_R_start + 5);
                        else
                            R_Find_Start = R_black[RowNum];
                    }
                    //全白十字
                    else if (Cross_Allwhite_Maybe == 1)
                    {
                        if (RowNum < Cross_Allwhite_L_out_Row + 5 && RowNum < 50)
                            // Lcr[RowNum].LEnd =
                            L_Find_Start = (byte)(Cross_Allwhite_L_start - 5);
                        else
                            L_Find_Start = L_black[RowNum];

                        if (RowNum < Cross_Allwhite_R_out_Row + 5 && RowNum < 50)
                            // Lcr[RowNum].REnd = 
                            R_Find_Start = (byte)(Cross_Allwhite_R_start + 5);
                        else
                            R_Find_Start = R_black[RowNum];
                    }
                    else if (Cross_Allwhite2 == 1)
                    {

                        if (RowNum < Cross_Allwhite2_L_out_Row + 5 && RowNum < 50)
                            // Lcr[RowNum].LEnd =
                            L_Find_Start = Check_Overrun199(Cross_Allwhite2_L_start - 5);
                        else
                            L_Find_Start = L_black[RowNum];
                        if (RowNum < Cross_Allwhite2_R_out_Row + 5 && RowNum < 50)
                            // Lcr[RowNum].REnd = 
                            R_Find_Start = Check_Overrun199(Cross_Allwhite2_R_start + 5);
                        else
                            R_Find_Start = R_black[RowNum];
                    }



                }
                //

                if (L_black[RowNum] <= 10 || R_black[RowNum] >= 190 || L_black[RowNum] <= R_black[RowNum])//截断行
                {

                    if (crosscutflag == 0)//防止 截断行重复赋值
                    {
                        cutline = RowNum;
                        crosscutflag = 1;
                    }
                    if (RowNum == 69 && crosscutflag == 0)
                    {
                        cutline = 69;
                    }

                }



            }//RowNum for循环
        }
 void FieldProcess() //图像场处理     //左转岔路  岔路+十字
        {
            //十字标志赋值   
            if (crossflag == 0 &&
                          (Cross_Straight_Flag == 1 || Cross_Lean_L == 1 || Cross_Lean_R == 1 || Cross_No_RightAngle_L_Memory == 1
                          || Cross_No_RightAngle_R_Memory == 1 || Cross_Allwhite_L == 1 || Cross_Allwhite == 1 || Cross_Allwhite2 == 1))
            {
                crossflag = 1;
            }

            /**********截断行后重新赋值**********/
            for (i = cutline; i < 70; i++)
            {
                if (cutline > 5)
                {

                    if (LCenter[cutline - 5] < 100)
                    {
                        LCenter[i] = 0;
                        L_black[i] = 0;
                        R_black[i] = 0;

                    }
                    else
                    {
                        LCenter[i] = 199;
                        L_black[i] = 199;
                        R_black[i] = 199;
                    }

                }
                else
                {
                    if (LCenter[cutline] < 100)
                    {
                        LCenter[i] = 0;
                        L_black[i] = 0;
                        R_black[i] = 0;

                    }
                    else
                    {
                        LCenter[i] = 199;
                        L_black[i] = 199;
                        R_black[i] = 199;
                    }
                }
            }

            // 坡道 起跑线
            if (podaogeshu <= 2 * slopecntmax)
            {

                if (poflag == 0 && crossflag == 0 && huandaoflag == 0 && blockflag == 0 && cutline > 60)
                {

                    /******************中远坡道**********************/
                    Wide_Row_Space = 0;
                    for (i = 55; i < cutline; i++)
                    {
                        if (L_black[i] - R_black[i] - fixValue[i] >= 10)
                        {
                            Wide_Row_Space++;
                        }

                        if (L_black[i] - R_black[i] - fixValue[i] >= 30)
                        {
                            Wide_Row_Space = 0;
                            break;
                        }
                    }
                    Normal_Row_Space = 0;
                    for (i = 0; i < 55; i++)
                    {
                        if (L_black[i] - R_black[i] - fixValue[i] <= 6)
                        {
                            Normal_Row_Space++;
                        }
                    }
                    righttrend = 0;
                    lefttrend = 0;
                    for (i = 2; i <= cutline; i++)
                    {
                        if (i <= 20)
                        {
                            if (L_black[i] - L_black[i - 2] > 0)
                            {
                                lefttrend++;
                            }

                            if (R_black[i] - R_black[i - 2] < 0)
                            {
                                righttrend++;
                            }
                        }
                        else if (i > 20)
                        {
                            if (L_black[i] - L_black[i - 2] > 0 || L_black[i] > 195)
                            {
                                lefttrend++;
                            }

                            if (R_black[i] - R_black[i - 2] < 0 || R_black[i] < 5)
                            {
                                righttrend++;
                            }
                        }
                    }
                    if (Wide_Row_Space > 10 && Normal_Row_Space > 42 && lefttrend < 4 && righttrend < 4)
                    {
                        poflag = 1;

                    }
                    /**********************近坡道*************************/
                    if (poflag == 0 && lefttrend < 4 && righttrend < 4)
                    {
                        Wide_Row_Space = 0;
                        for (i = 35; i <= cutline; i++)
                        {
                            if (L_black[i] - R_black[i] - fixValue[i] >= 10)
                            {
                                Wide_Row_Space++;
                            }

                            if (L_black[i] - R_black[i] - fixValue[i] >= 50)
                            {
                                Wide_Row_Space = 0;

                                break;
                            }
                        }
                        Normal_Row_Space = 0;
                        for (i = 0; i < 35; i++)
                        {
                            if (L_black[i] - R_black[i] - fixValue[i] <= 6)
                            {
                                Normal_Row_Space++;
                            }
                        }
                        if (Wide_Row_Space > 28 && Normal_Row_Space > 23 && lefttrend < 4 && righttrend < 4)
                        {
                            poflag = 1;
                        }
                    }
                    //********************超近坡道*************************
                    if (poflag == 0 && lefttrend < 4 && righttrend < 4)
                    {
                        //?íDD?àêy
                        Wide_Row_Space = 0;
                        for (i = 10; i <= cutline; i++)
                        {
                            if (L_black[i] - R_black[i] - fixValue[i] >= 20)
                            {
                                Wide_Row_Space++;
                            }
                        }
                        if (Wide_Row_Space > 40 && lefttrend < 4 && righttrend < 4)
                        {
                            poflag = 1;
                        }
                    }

                }
                if (poflag == 1)
                {

                    Narrow_Row_Space = 0;
                    for (j = 0; j <= cutline; j++)
                    {
                        if (L_black[j] - R_black[j] - fixValue[j] < -25)
                        {
                            Narrow_Row_Space++;
                        }
                    }
                    if (Narrow_Row_Space > 20 && cutline < 69)
                    {
                        poflag = 2;
                        Narrow_Row_Space = 0;
                    }
                    poqingchucnt++;
                    if (poqingchucnt == 20)
                    {
                        poflag = 0;
                    }

                }

                if (poflag == 2)
                {
                    poqingchucnt = 0;
                    Obstruction_L = 0;
                    Obstruction_R = 0;
                    Wide_Row_Space = 0;
                    for (j = 0; j <= cutline; j++)
                    {
                        if (L_black[j] - R_black[j] - fixValue[j] > 5)
                        {
                            Wide_Row_Space++;
                        }
                    }

                    if (Wide_Row_Space > 65)
                    {
                        poflag = 3;
                        Ramp3_ClearFieldCnt = 25;
                    }
                }
                //丢线清掉坡道
                if (cutline < 47 && ((L_black[0] == 199) || (R_black[0] == 0)))
                {
                    poflag = 0;
                }
                if (poflag == 3 && Ramp3_ClearFieldCnt > 0)
                {
                    Ramp3_ClearFieldCnt--;
                }
                else if (poflag == 3 && Ramp3_ClearFieldCnt == 0)
                {
                    poflag = 0;
                }
                podaogeshu = kind_slopecnt(poflag);
            }
            /****************************起跑线***********************/
            //需要两次识别  在不是坡道的情况判断
            if (poflag != 2 && cutline > 30 && qipaojiance == 1 && qipaoflag == 1 && huandaoflag == 0)
            {
                //用户自定义("起跑线");
                temp = 0;
                for (i = R_black[4]; i <= L_black[4] - 1; i++)
                {
                    if (P_Pixels[4][i] != P_Pixels[4][i + 1])
                    { temp++; }
                }
                if (temp < 9)
                {
                    temp = 0;
                    for (i = R_black[2]; i <= L_black[2] - 1; i++)
                    {
                        if (P_Pixels[2][i] != P_Pixels[2][i + 1])
                        { temp++; }
                    }
                }
                if (temp < 9)
                {
                    temp = 0;
                    for (i = R_black[7]; i <= L_black[7] - 1; i++)
                    {
                        if (P_Pixels[7][i] != P_Pixels[7][i + 1])
                        { temp++; }
                    }
                }
								if (temp < 9)
                {
                    temp = 0;
                    for (i = R_black[10]; i <= L_black[10] - 1; i++)
                    {
                        if (P_Pixels[10][i] != P_Pixels[10][i + 1])
                        { temp++; }
                    }
                }
                if (temp > 9)
                {
                    stopflag = 1;
                }
                if (fabss(L_black[0], R_black[0]) < 30 && fabss(L_black[1], R_black[1]) < 30)
                {
                    stopflag = 1;
                }
            }
            //
            // 环岛
            /******************环岛******************/
            if (huandaogeshu <= 2 * huandaocntmax)
            {
                temp = 0;
                j = 0;
                if (poflag != 2)
                {
                    lefttrend = 0;
                    righttrend = 0;
                    a = 0;
                    if (huandaoyouflag3 == 0 && huandaozuoflag3 == 0)
                    {
                        for (i = 1; i < cutline - 5 && i < 50; i++)
                        {
                            if (L_black[i] - L_black[i - 1] > 0)
                            {
                                lefttrend++;
                            }
                            if (L_black[i] == 199)
                            {
                                a++;
                            }
                            if (fabss(L_black[i], L_black[i - 1]) > 4 || lefttrend > 5 || a > 10)
                            {
                                leftall = 0;
                                break;

                            }
                        }//环岛判断

                        b = 0;
                        for (i = 1; i < cutline - 5 && i < 50; i++)
                        {
                            if (R_black[i - 1] - R_black[i] > 0)
                            {
                                righttrend++;
                            }
                            if (R_black[i] == 0)
                            {
                                b++;
                            }
                            if (fabss(R_black[i], R_black[i - 1]) > 4 || righttrend > 5 || b > 10)
                            {
                                rightall = 0;
                                break;

                            }//环岛判断  
                        }
                    }
                    /******************************************右环岛*************************/
                    if (leftall == 1 && rightall == 0 && cutline > 55)          //可能是右环岛
                    {
                        for (i = 0; i < 40; i++)
                        {
                            if (R_black[i] > 5 && (R_black[i] - R_black[i + 3] > 10 || (R_black[i + 3] == 0)) && L_black[i + 3] - R_black[i + 3] > fixValue[i + 3])
                            {

                                if (i > 1)
                                {
                                    if (P_Pixels[i + 1][(R_black[i] + R_black[i + 1]) / 2] > 0 && P_Pixels[i][(R_black[i] + R_black[i + 1]) / 2] > 0)
                                    {

                                        tubianyou = i;
                                        break;
                                    }
                                }
                            }
                            if (i == 39)
                            {
                                tubianyou = 0;
                                break;
                            }
                        }
                        if (tubianyou != 0)
                        {
                            for (i = (uint8_t)(tubianyou + 2); i < cutline; i++)
                            {
                                if (P_Pixels[i][R_black[tubianyou]] == 0)
                                {
                                    wanruyou1 = i;
                                    break;
                                }
                                if (i == cutline - 1)
                                {
                                    wanruyou1 = 0;
                                }
                            }


                            if (wanruyou1 - tubianyou > 5 && wanruyou1 - tubianyou < 40 && L_black[tubianyou + 2] - R_black[tubianyou + 2] > fixValue[tubianyou + 2] + 5 && L_black[wanruyou1 - 2] - R_black[wanruyou1 - 2] > fixValue[wanruyou1 - 2] + 5)
                            {

                                for (i = wanruyou1; i < cutline; i++)
                                {
                                    if (P_Pixels[i][R_black[tubianyou]] > 0)
                                    {
                                        wanruyou2 = i;
                                        break;
                                    }
                                }
                                for (i = wanruyou2; i < cutline; i++)
                                {
                                    if (L_black[i] - R_black[i] > fixValue[i] + 5)
                                    {
                                        temp = 1;
                                        break;
                                    }
                                }

                                if (wanruyou2 - wanruyou1 > 10 && wanruyou2 - wanruyou1 < 50 && temp == 1)
                                {

                                    huandaoyouflag1 = 1;
                                }

                            }
                        }
                    }
                    //可能是弯道入环岛  没有 1 状态   直接判断第2状态
                    if (cutline > 55 && huandaoyouflag2 == 0 && leftall == 1 && rightall == 01)
                    {

                        temp = 0;
                        if (R_black[0] == 0 && L_black[15] - L_black[0] <= 0)
                        {

                            for (i = 0; i < 30; i++)
                            {
                                if (P_Pixels[i][0] == 0 && P_Pixels[i + 2][0] == 0 && P_Pixels[i + 3][0] == 0)
                                {
                                    wanruyou1 = i;
                                    break;
                                }
                            }

                            if (wanruyou1 > 5 && wanruyou1 < 40 && L_black[0] - R_black[0] > fixValue[0] - 5 && L_black[wanruyou1 / 2] - R_black[wanruyou1 / 2] > fixValue[wanruyou1 / 2] && R_black[wanruyou1 + 13] - R_black[wanruyou1 + 3] > 15)
                            {

                                for (i = wanruyou1; i < cutline - 3; i++)
                                {
                                    if (P_Pixels[i][0] > 0 && P_Pixels[i + 1][0] > 0)
                                    {
                                        wanruyou2 = i;
                                        break;
                                    }
                                    if (i == cutline - 1)
                                    {
                                        wanruyou2 = cutline;
                                    }
                                }
                                if (wanruyou2 != cutline && wanruyou2 > wanruyou1 + 3)
                                {

                                    for (i = wanruyou2; i < cutline; i++)
                                    {
                                        if (L_black[i] - R_black[i] > fixValue[i] + 5 && R_black[wanruyou2 - 3] > R_black[wanruyou2])
                                        {
                                            temp = 1;
                                            break;
                                        }
                                        if (i == cutline - 1)
                                        {
                                            temp = 0;
                                        }
                                    }
                                    if (temp == 1)
                                    {

                                        if (wanruyou2 - wanruyou1 > 10 && wanruyou2 - wanruyou1 < 60)
                                        {

                                            for (i = wanruyou2; i < cutline; i++)
                                            {
                                                if (P_Pixels[i][0] == 0)
                                                {
                                                    wanruyou3 = i;
                                                    break;

                                                }
                                            }

                                            if (wanruyou3 > 30 && wanruyou3 - wanruyou2 < 20)
                                            {

                                                huandaoyouflag2 = 1;
                                                huandaoyouflag1 = 1;
                                                temp = 0;
                                                for (i = 1; i < cutline; i++)
                                                {
                                                    if (P_Pixels[i][15] == 0)
                                                    {
                                                        temp = i;
                                                        break;
                                                    }
                                                }
                                                b = 0;
                                                for (i = 1; i < cutline; i++)
                                                {
                                                    if (R_black[i] - R_black[i - 1] > 10)
                                                    {
                                                        b = i;
                                                        break;
                                                    }
                                                }
                                                c = 0;
                                                if (b > 5)
                                                {
                                                    for (i = b; i < cutline - 5; i++)
                                                    {
                                                        if (R_black[i] - R_black[i + 3] > 0 && R_black[i + 3] - R_black[i + 5] > 0)
                                                        {
                                                            c = R_black[i];
                                                            break;
                                                        }
                                                    }
                                                }
                                                if (temp < wanruyou1 && c < 80)
                                                {
                                                    huandaoyouflag2 = 0;
                                                    huandaoyouflag1 = 0;
                                                }
                                                if ((L_black[wanruyou1 + 8] - R_black[wanruyou1 + 8]) - (L_black[wanruyou1 + 3] - R_black[wanruyou1 + 3]) > 0)
                                                {
                                                    huandaoyouflag2 = 0;
                                                    huandaoyouflag1 = 0;
                                                }

                                            }
                                        }
                                    }
                                }
                            }
                        }

                    }
                    if (cutline > 55 && huandaoyouflag2 == 0 && leftall == 1 && rightall == 01)
                    {
                        temp = 0;
                        if (R_black[0] == 0 && L_black[15] - L_black[0] <= 0)
                        {
                            // //用户自定义("11111");
                            for (i = 0; i < 30; i++)
                            {
                                if (P_Pixels[i][15] == 0 && P_Pixels[i + 1][15] == 0 && P_Pixels[i + 2][15] == 0)
                                {
                                    wanruyou1 = i;
                                    break;
                                }
                            }


                            if (wanruyou1 > 5 && wanruyou1 < 40 && L_black[0] - R_black[0] > fixValue[0] - 5 && L_black[wanruyou1 / 2] - R_black[wanruyou1 / 2] > fixValue[wanruyou1 / 2] && R_black[wanruyou1 + 8] - R_black[wanruyou1 + 3] > 8)
                            {
                                // //用户自定义("12222");

                                for (i = wanruyou1; i < cutline - 3; i++)
                                {
                                    if (P_Pixels[i][15] > 0 && P_Pixels[i + 1][15] > 0 && P_Pixels[i + 2][15] > 0)
                                    {
                                        wanruyou2 = i;
                                        break;
                                    }
                                    if (i == cutline - 1)
                                    {
                                        wanruyou2 = cutline;
                                    }
                                }
                                if (wanruyou2 != cutline && wanruyou2 > wanruyou1 + 3)
                                {
                                    // //用户自定义("1333331" + wanruyou2);
                                    for (i = wanruyou2; i < cutline; i++)
                                    {
                                        if (L_black[i] - R_black[i] > fixValue[i] + 5 && R_black[wanruyou2 - 3] > R_black[wanruyou2])
                                        {
                                            temp = 1;
                                            break;
                                        }
                                        if (i == cutline - 1)
                                        {
                                            temp = 0;
                                        }
                                    }
                                    if (temp == 1)
                                    {
                                        //  //用户自定义("44444444444");
                                        if (wanruyou2 - wanruyou1 > 10 && wanruyou2 - wanruyou1 < 60)
                                        {

                                            for (i = wanruyou2; i < cutline; i++)
                                            {
                                                if (P_Pixels[i][15] == 0)
                                                {
                                                    wanruyou3 = i;
                                                    break;

                                                }
                                            }

                                            if (wanruyou3 > 30 && wanruyou3 - wanruyou2 < 20)
                                            {

                                                huandaoyouflag2 = 1;
                                                huandaoyouflag1 = 1;
                                                if (wanruyou3 > 30 && wanruyou3 - wanruyou2 < 20)
                                                {
                                                    //   //用户自定义("11111111111111111");

                                                    huandaoyouflag2 = 1;
                                                    huandaoyouflag1 = 1;
                                                    temp = 0;
                                                    for (i = 1; i < cutline; i++)
                                                    {
                                                        if (P_Pixels[i][20] == 0)
                                                        {
                                                            temp = i;
                                                            break;
                                                        }
                                                    }
                                                    j = 0;
                                                    for (i = 1; i < cutline; i++)
                                                    {
                                                        if (P_Pixels[i][0] == 0)
                                                        {
                                                            j = i;
                                                            break;
                                                        }
                                                        if (i == cutline - 1)
                                                        {
                                                            j = i;
                                                        }
                                                    }
                                                    if (temp < wanruyou1 || temp < j)
                                                    {
                                                        huandaoyouflag2 = 0;
                                                        huandaoyouflag1 = 0;
                                                    }
                                                    if ((L_black[wanruyou1 + 8] - R_black[wanruyou1 + 8]) - (L_black[wanruyou1 + 3] - R_black[wanruyou1 + 3]) > 0)
                                                    {
                                                        huandaoyouflag2 = 0;
                                                        huandaoyouflag1 = 0;
                                                    }


                                                }

                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                    //如果前两种没判断出来
                    if (cutline > 55 && huandaoyouflag2 == 0 && leftall == 1 && rightall == 0)
                    {
                        temp = 0;
                        for (i = 0; i < 40; i++)
                        {
                            if (R_black[i] < 10)
                            {
                                temp++;
                            }
                            if (i == 39 || R_black[i] > 10)
                            {
                                if (i == 39)
                                {
                                    temp = 0;
                                }
                                break;
                            }
                        }
                        j = 0;
                        if (temp > 5 && (L_black[temp] - R_black[temp]) > (L_black[temp + 4] - R_black[temp + 4]))
                        {
                             //用户自定义("补充环岛" + temp);

                            a = 0;
                            for (i = (byte)(temp); i < 60; i++)
                            {
                                if (R_black[i] - R_black[i + 2] < 0)
                                {
                                    a++;
                                }
                                if (R_black[i] - R_black[i + 2] > 0)
                                {
                                    j = i;              //拐点
                                    if (R_black[i + 2] - R_black[i + 8] <= 0 || j - temp < 10 || R_black[j] - R_black[temp] < 20 || j - temp > 45)
                                    {
                                        j = 0;
                                    }
                                    break;
                                }
                                if (i == 59)
                                {
                                    j = 0;
                                }
                            }

                        }
                        if (R_black[temp + 10] - R_black[temp + 3] != 0)
                        {
                            khuan = (float)(7) / (float)(R_black[temp + 10] - R_black[temp + 3]);
                        }
                        else
                        {
                            khuan = 0;
                        }
                        //用户自定义("bbbbbbbbbbbbbb" + khuan);
                        b = 0;
                        //找上边最右值
                        for (i = j; i < cutline - 1; i++)
                        {
                            if (R_black[i + 1] > R_black[i])
                            {
                                b = i;
                                if (i == cutline - 2 || b - j < 5 || R_black[j] - R_black[i] < 20)
                                {
                                    b = 0;
                                }
                                break;
                            }
                            if (i == cutline - 2)
                            {
                                b = 0;
                            }
                        }
                        c = 0;
                        //找上边跳变
                        if (R_black[j] - R_black[b] > 20 && b > 10)
                        {
                            for (i = j; i < b; i++)
                            {
                                if (R_black[i] - R_black[i + 1] > 10)
                                {
                                    c = 1;
                                    break;

                                }
                                if (i == b - 1)
                                {
                                    c = 0;
                                }

                            }
                        }

                        //用户自定义("why" + temp + a + j);
                        if (temp > 5 && a > 10 && j > 5 && P_Pixels[j + 5][R_black[j]] > 0 && P_Pixels[j - 5][R_black[j]] > 0 && c == 1 && khuan < 0.7 && khuan > 0)
                        {
                            for (i = j; i < cutline; i++)
                            {
                                if (L_black[i] - R_black[i] > fixValue[i] + 5)
                                {
                                    huandaoyouflag1 = 1;
                                    huandaoyouflag2 = 1;
                                    break;
                                }
                            }
                        }
                    }
                    if (huandaoyouflag2 == 1 && R_black[0] > 0 && R_black[10] > 0 && R_black[20] > 0 && R_black[7] > 0 && R_black[3] > R_black[0])
                    {
                        temp = 0;
                        a = 0;
                        b = 0;
                        for (i = 0; i < cutline - 10; i++)
                        {
                            if (R_black[i + 3] - R_black[i] > 0)
                            {
                                temp++;
                            }
                            if (R_black[i + 3] - R_black[i] < 0)
                            {
                                a = i;
                                break;
                            }
                            if (i == cutline - 11)
                            {
                                temp = 0;
                            }

                        }
                        if (temp > 15)
                        {
                            for (i = a; i < cutline - 10; i++)
                            {
                                if (R_black[i] == 199 || R_black[i + 3] - R_black[i] > 0)
                                {
                                    b = i;
                                    break;
                                }
                                if (i == cutline - 11)
                                {
                                    b = 0;
                                }
                            }
                        }
                        if (temp > 10 && b - a > 5)
                        {
                            huandaoyouflag3 = 1;
                        }
                    }
                    if (huandaoyouflag3 == 1)
                    {

                        huandaofangxiang = 1;
                        huandaoyouflag2 = 0;
                        huandaoyouflag1 = 0;
                        if (huandaowanflag != 3)
                        {
                            for (i = 0; i < cutline - 6; i++)
                            {
                                if (P_Pixels[i][0] > 0 && P_Pixels[i + 2][0] > 0 && P_Pixels[i + 1][0] > 0)
                                {
                                    huandaoyousao = i;
                                    break;
                                }
                            }
                            for (i = (byte)(huandaoyousao + 3); i < 64; i++)
                            {
                                if (P_Pixels[i][0] == 0 && P_Pixels[i + 1][0] == 0 && P_Pixels[i + 2][0] == 0)
                                {
                                    huandaoyousao1 = i;
                                    break;
                                }
                            }
                        }
                        if (huandaowanflag == 0)
                        {
                            temp = 0;

                            for (i = 0; i < huandaoyousao1; i++)
                            {
                                if (R_black[i] > R_black[i + 3])
                                {
                                    temp = i;
                                    break;
                                }
                                if (i == huandaoyousao1 - 1)
                                {
                                    temp = 0;
                                }
                            }
                            if (huandaoyousao > 10)
                            {

                                for (i = (byte)(temp); i < huandaoyousao1; i++)
                                {
                                    LCenter[i] = (byte)(R_black[i] + fixValue[i] / 2);
                                    if (R_black[i] + fixValue[i] / 2 > L_black[i])
                                    {
                                        LCenter[i] = L_black[i];
                                    }
                                }
                                for (i = 0; i < temp; i++)
                                {
                                    LCenter[i] = LCenter[temp];
                                }

                                for (i = (byte)(huandaoyousao - 1); i < (huandaoyousao1 - huandaoyousao + 1) / 3 * 2 + huandaoyousao - 1; i++)
                                {
                                    LCenter[i] = (byte)(LCenter[huandaoyousao - 1] + (i - huandaoyousao + 1) * (0 - LCenter[huandaoyousao - 1]) / (double)((huandaoyousao1 - huandaoyousao + 1) / 3 * 2));
                                }
                                if (huandaoyousao1 != 0)
                                {
                                    for (i = (byte)((huandaoyousao1 - huandaoyousao + 1) / 3 * 2 + huandaoyousao - 1); i < cutline; i++)
                                    {
                                        LCenter[i] = 0;

                                    }
                                }

                            }
                            else
                            {
                                if (L_black[0] > 180)
                                {
                                    LCenter[0] = (byte)(R_black[0] + fixValue[0] / 2);
                                }
                                else
                                {
                                    LCenter[0] = (byte)((R_black[0] + L_black[0]) / 2);
                                }
                                for (i = 0; i < (huandaoyousao1 - huandaoyousao + 1) / 3 * 2 + huandaoyousao - 1; i++)
                                {
                                    LCenter[i] = (byte)(LCenter[0] + (i) * (0 - LCenter[0]) / (double)((huandaoyousao1 - huandaoyousao + 1) / 3 * 2 + huandaoyousao - 1));
                                }
                                if (huandaoyousao1 != 0)
                                {
                                    for (i = (byte)((huandaoyousao1 - huandaoyousao + 1) / 3 * 2 + huandaoyousao - 1); i < cutline; i++)
                                    {

                                        LCenter[i] = 0;


                                    }
                                }
                            }
                            temp = 0;
                            if (L_black[0] < 140)
                            {

                                for (i = L_black[0]; i < 197; i++)
                                {
                                    if (P_Pixels[0][i] > 0 && P_Pixels[0][i + 2] > 0)
                                    {
                                        temp = i;
                                        huandaoblackpoint = (byte)(i - L_black[0]);
                                        break;
                                    }
                                    if (i == 196)
                                    {
                                        normalhuan = 1;
                                        huandaoblackpoint = 0;
                                        temp = 0;
                                    }
                                }
                            }
                            j = 0;
                            if (huandaoblackpoint > 2 && temp < 195)
                            {

                                for (i = (byte)(temp + 1); i < 199; i++)
                                {
                                    if (P_Pixels[0][i] > 0)
                                    {
                                        j++;
                                    }

                                    if (j == 3)
                                    {
                                        huandaowanflag = 1;
                                        break;
                                    }
                                    if (P_Pixels[0][i] == 0)
                                    {
                                        break;
                                    }
                                }
                            }
                            if (huandaoyousao1 < 65)
                            {
                                for (i = (byte)(huandaoyousao1 + 5); i < 70; i++)
                                {
                                    if (L_black[i] != 0 || R_black[i] != 0)
                                    {
                                        ruflag = 0;
                                        break;
                                    }
                                }
                            }
                            if (ruflag == 1)
                            {

                                huandaowanflag = 1;
                            }
                        }
                        if (huandaowanflag == 1)
                        {
                            for (i = 0; i < cutline - 12 && cutline > 12; i++)
                            {
                                if (R_black[i + 10] - R_black[i] > 5)
                                {
                                    huandaowanflag = 2;
                                    break;
                                }
                            }
                        }
                        if (huandaowanflag == 2)
                        {
                            temp = 0;
                            for (i = 1; i < cutline - 2; i++)
                            {
                                if (L_black[i] - R_black[i] < 40)
                                {
                                    temp = i;
                                    break;
                                }
                                if (i == cutline - 3)
                                {
                                    temp = 0;
                                }
                            }
                        }
                        if (huandaowanflag == 2 && temp != 0)
                        {
                            j = 0;
                            for (i = (byte)temp; i < cutline - 2; i++)
                            {
                                if (L_black[i] > 60)
                                {
                                    j = i;
                                    huandaowanflag = 3;
                                    break;
                                }

                            }

                        }
                        if (huandaowanflag == 3 || (normalhuan == 1 && huandaowanflag != 1 && huandaowanflag != 2) || huandaochu1 == 1)
                        {
                            for (i = 0; i < cutline - 3; i++)
                            {
                                if (P_Pixels[i][0] > 0 && P_Pixels[i + 1][0] > 0 && P_Pixels[i + 2][0] > 0)
                                {
                                    huandaoyousao = i;
                                    break;
                                }
                            }
                            for (i = (byte)(huandaoyousao + 3); i < 66; i++)
                            {
                                if (P_Pixels[i][0] == 0 && P_Pixels[i + 1][0] == 0 && P_Pixels[i + 2][0] == 0)
                                {
                                    if (i > 5)
                                    {
                                        huandaoyousao1 = i;
                                        break;
                                    }
                                    else
                                    {
                                        break;
                                    }
                                }
                            }
                            if (dahuanflag == 0)
                            {
                                if (huandaoyousao > 10)
                                {
                                    for (i = (byte)(huandaoyousao - 1); i < (huandaoyousao1 - huandaoyousao + 1) / 3 * 2 + huandaoyousao - 1; i++)
                                    {
                                        LCenter[i] = (byte)(LCenter[huandaoyousao - 1] + (i - huandaoyousao + 1) * (0 - LCenter[huandaoyousao - 1]) / (double)((huandaoyousao1 - huandaoyousao + 1) / 3 * 2));
                                    }
                                    if (huandaoyousao1 != 0)
                                    {
                                        for (i = (byte)((huandaoyousao1 - huandaoyousao + 1) / 3 * 2 + huandaoyousao - 1); i < cutline; i++)
                                        {

                                            LCenter[i] = 0;

                                        }
                                    }
                                }
                                if (huandaoyousao <= 10)
                                {
                                    if (L_black[0] > 180)
                                    {
                                        LCenter[0] = (byte)(R_black[0] + fixValue[0] / 2);
                                    }
                                    else
                                    {
                                        LCenter[0] = (byte)((R_black[0] + L_black[0]) / 2);
                                    }
                                    for (i = 0; i < (huandaoyousao1 - huandaoyousao + 1) / 3 * 2 + huandaoyousao - 1; i++)
                                    {
                                        LCenter[i] = (byte)(LCenter[0] + (i) * (0 - LCenter[0]) / (double)((huandaoyousao1 - huandaoyousao + 1) / 3 * 2 + huandaoyousao - 1));
                                    }
                                    if (huandaoyousao1 != 0)
                                    {
                                        for (i = (byte)((huandaoyousao1 - huandaoyousao + 1) / 3 * 2 + huandaoyousao - 1); i < cutline; i++)
                                        {
                                            LCenter[i] = 0;
                                        }
                                    }

                                }
                            }
                            else
                            {
                                if (L_black[0] > 180)
                                {
                                    LCenter[0] = (byte)(R_black[0] + fixValue[0] / 2);
                                }
                                else
                                {
                                    LCenter[0] = (byte)((R_black[0] + L_black[0]) / 2);
                                }
                                for (i = 0; i < (huandaoyousao1 - huandaoyousao + 1) / 3 * 2 + huandaoyousao - 1; i++)
                                {
                                    LCenter[i] = (byte)(LCenter[0] + (i) * (0 - LCenter[0]) / (double)((huandaoyousao1 - huandaoyousao + 1) / 3 * 2 + huandaoyousao - 1));
                                }
                                if (huandaoyousao1 != 0)
                                {
                                    for (i = (byte)((huandaoyousao1 - huandaoyousao + 1) / 3 * 2 + huandaoyousao - 1); i < cutline; i++)
                                    {
                                        LCenter[i] = 0;
                                    }
                                }
                            }

                        }
                        for (i = 5; i < 25; i++)
                        {
                            if (L_black[i - 5] - L_black[i] > 2 && L_black[i + 5] - L_black[i] > 2 && L_black[i - 1] - L_black[i] >= 0 && L_black[i + 1] - L_black[i] > 0 && huandaowanflag != 0)
                            {
                                if (P_Pixels[i + 4][L_black[i]] > 0 && P_Pixels[i - 4][L_black[i]] > 0)
                                {
                                    huandaozuoguai = i;
                                    break;
                                }
                            }
                        }
                        if (huandaozuoguai != 0 && L_black[0] != 199)
                        {
                            huandaochu = 1;


                        }
                        if (huandaochu1 == 1 && L_black[0] < 190 && L_black[1] < 190 && L_black[2] < 190)
                        {
                            qingchuflag = 1;


                        }
                        if (huandaochu == 1 && L_black[0] > 190 && L_black[1] > 190 && L_black[2] > 190)
                        {
                            huandaochu1 = 1;


                        }
                        if (qingchuflag == 1)
                        {
                            huandaoyouflag1 = 0;
                            huandaoyouflag2 = 0;
                            huandaoyouflag3 = 0;
                            huandaoyousao = 0;
                            huandaoyousao1 = 0;
                            huandaochu = 0;
                            huandaochu1 = 0;

                            huandaocnt = 0;
                            huandaowanflag = 0;
                            normalhuan = 0;
                            LCenter[0] = (byte)((L_black[0] + R_black[0]) / 2);
                        }

                    }
                    if ((huandaoyouflag2 == 1 || huandaoyouflag1 == 1) && huandaoyouflag3 == 0)
                    {
                        for (i = 0; i < cutline; i++)
                        {
                            LCenter[i] = (byte)(L_black[i] - fixValue[i] / 2);
                            if (L_black[i] - fixValue[i] / 2 < R_black[i])
                            {
                                LCenter[i] = R_black[i];
                            }
                        }
                    }

                    /*************************************左环岛**************************/
                    if (leftall == 0 && rightall == 1 && cutline > 55)          //可能是左环岛
                    {
                        for (i = 0; i < 40; i++)
                        {
                            if (L_black[i] < 195 && (L_black[i + 3] - L_black[i] > 10 || L_black[i + 3] == 199) && L_black[i + 3] - R_black[i + 3] > fixValue[i + 3])
                            {
                                //  //用户自定义("aaaaaaaaaaaaaa");

                                if (i > 1)
                                {
                                    if (P_Pixels[i + 1][(L_black[i] + L_black[i + 1]) / 2] > 0)
                                    {
                                        tubianzuo = i;
                                        break;
                                    }
                                }
                                if (i == 39)
                                {
                                    tubianzuo = 0;
                                }
                            }
                        }
                        if (tubianzuo != 0)
                        {
                            //  //用户自定义("bbbbbbbbbbbbb");
                            for (i = (uint8_t)(tubianzuo + 2); i < cutline; i++)
                            {
                                if (P_Pixels[i][L_black[tubianzuo]] == 0)
                                {
                                    wanruzuo1 = i;
                                    break;
                                }
                                if (i == cutline - 1)
                                {
                                    wanruzuo1 = 0;
                                }
                            }
                            if (wanruzuo1 - tubianzuo > 5 && wanruzuo1 - tubianzuo < 40 && L_black[tubianzuo + 2] - R_black[tubianzuo + 2] > fixValue[tubianzuo + 2] + 5 && L_black[wanruzuo1 - 2] - R_black[wanruzuo1 - 2] > fixValue[wanruzuo1 - 2] + 5)
                            {
                                //   //用户自定义("ccccccccccc");
                                for (i = wanruzuo1; i < cutline; i++)
                                {
                                    if (P_Pixels[i][L_black[tubianzuo]] > 0)
                                    {
                                        wanruzuo2 = i;
                                        break;
                                    }
                                }
                                for (i = wanruzuo2; i < cutline; i++)
                                {
                                    if (L_black[i] - R_black[i] > fixValue[i] + 5)
                                    {
                                        temp = 1;
                                        break;
                                    }
                                }
                                if (wanruzuo2 - wanruzuo1 > 10 && wanruzuo2 - wanruzuo1 < 50 && temp == 1)
                                {

                                    huandaozuoflag1 = 1;

                                }
                            }
                        }

                    }
                    //可能是弯道入环岛  没有 1 状态   直接判断第2状态
                    if (cutline > 55 && huandaozuoflag2 == 0 && leftall == 0 && rightall == 11)
                    {
                        //    //用户自定义("1111111111");
                        temp = 0;
                        if (L_black[0] == 199 && R_black[15] - R_black[0] >= 0)
                        {
                            //    //用户自定义("2222");
                            for (i = 1; i < 30; i++)
                            {
                                if (P_Pixels[i][199] == 0 && P_Pixels[i + 1][199] == 0 && P_Pixels[i + 2][199] == 0)
                                {
                                    wanruzuo1 = i;
                                    break;
                                }
                            }
                            if (wanruzuo1 > 5 && wanruzuo1 < 40 && L_black[0] - R_black[0] > fixValue[0] - 5 && L_black[wanruzuo1 / 2] - R_black[wanruzuo1 / 2] > fixValue[wanruzuo1 / 2] && L_black[wanruzuo1 + 3] - L_black[wanruzuo1 + 13] > 15)
                            {
                                //     //用户自定义("33333");

                                for (i = wanruzuo1; i < cutline - 3; i++)
                                {
                                    if (P_Pixels[i][199] > 0 && P_Pixels[i + 1][199] > 0)
                                    {
                                        wanruzuo2 = i;
                                        break;
                                    }
                                    if (i == cutline - 1)
                                    {

                                        wanruzuo2 = (byte)(cutline);
                                    }
                                }
                                if (wanruzuo2 != cutline && wanruzuo2 > wanruzuo1 + 3)
                                {
                                    //   //用户自定义("44444444");
                                    for (i = wanruzuo2; i < cutline; i++)
                                    {
                                        if (L_black[i] - R_black[i] > fixValue[i] + 5 && L_black[wanruzuo2] > L_black[wanruzuo2 - 3])
                                        {
                                            temp = 1;
                                            break;
                                        }
                                        if (i == cutline - 1)
                                        {
                                            temp = 0;
                                        }
                                    }
                                    if (temp == 1)
                                    {
                                        if (wanruzuo2 - wanruzuo1 > 10 && wanruzuo2 - wanruzuo1 < 50)
                                        {
                                            //   //用户自定义("5555555555");

                                            for (i = wanruzuo2; i < cutline; i++)
                                            {
                                                if (P_Pixels[i][199] == 0)
                                                {
                                                    wanruzuo3 = i;
                                                    break;
                                                }
                                            }
                                            if (wanruzuo3 > 30 && wanruzuo3 - wanruzuo2 < 20)
                                            {
                                                //     //用户自定义("6666666666");
                                                huandaozuoflag2 = 1;
                                                huandaozuoflag1 = 1;
                                                temp = 0;
                                                for (i = 1; i < cutline; i++)
                                                {
                                                    if (P_Pixels[i][185] == 0)
                                                    {
                                                        temp = i;
                                                        break;
                                                    }
                                                }
                                                b = 0;
                                                for (i = 1; i < cutline; i++)
                                                {
                                                    if (L_black[i - 1] - L_black[i] > 10)
                                                    {
                                                        b = i;
                                                        break;
                                                    }
                                                }
                                                c = 0;
                                                if (b > 5)
                                                {
                                                    for (i = b; i < cutline - 5; i++)
                                                    {
                                                        if (L_black[i + 3] - L_black[i] > 0 && L_black[i + 5] - L_black[i + 3] > 0)
                                                        {
                                                            c = L_black[i];
                                                            break;
                                                        }
                                                    }
                                                }
                                                if (temp < wanruzuo1 && c > 120)
                                                {
                                                    //   //用户自定义("777777");
                                                    huandaozuoflag2 = 0;
                                                    huandaozuoflag1 = 0;
                                                }
                                                if ((L_black[wanruzuo1 + 8] - R_black[wanruzuo1 + 8]) - (L_black[wanruzuo1 + 3] - R_black[wanruzuo1 + 3]) > 0)
                                                {
                                                    //    //用户自定义("88888888");
                                                    huandaozuoflag2 = 0;
                                                    huandaozuoflag1 = 0;

                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                    if (cutline > 55 && huandaozuoflag2 == 0 && leftall == 0 && rightall == 11)
                    {
                        temp = 0;
                        if (L_black[0] == 199 && R_black[15] - R_black[0] >= 0)
                        {
                            for (i = 1; i < 30; i++)
                            {
                                if (P_Pixels[i][185] == 0 && P_Pixels[i + 1][185] == 0 && P_Pixels[i + 2][185] == 0)
                                {
                                    wanruzuo1 = i;
                                    break;
                                }
                            }
                            if (wanruzuo1 > 5 && wanruzuo1 < 40 && L_black[0] - R_black[0] > fixValue[0] - 5 && L_black[wanruzuo1 / 2] - R_black[wanruzuo1 / 2] > fixValue[wanruzuo1 / 2] && L_black[wanruzuo1 + 3] - L_black[wanruzuo1 + 8] > 8)
                            {

                                for (i = wanruzuo1; i < cutline - 4; i++)
                                {
                                    if (P_Pixels[i][185] > 0 && P_Pixels[i + 2][185] > 0 && P_Pixels[i + 3][185] > 0)
                                    {
                                        wanruzuo2 = i;
                                        break;
                                    }
                                    if (i == cutline - 1)
                                    {
                                        wanruzuo2 = cutline;
                                    }
                                }
                                if (wanruzuo2 != cutline && wanruzuo2 > 3 + wanruzuo1)
                                {

                                    for (i = wanruzuo2; i < cutline; i++)
                                    {
                                        if (L_black[i] - R_black[i] > fixValue[i] + 5 && L_black[wanruzuo2] > L_black[wanruzuo2 - 3])
                                        {
                                            temp = 1;
                                            break;
                                        }
                                        if (i == cutline - 1)
                                        {
                                            temp = 0;
                                        }
                                    }
                                    if (temp == 1)
                                    {
                                        if (wanruzuo2 - wanruzuo1 > 10 && wanruzuo2 - wanruzuo1 < 50)
                                        {
                                            for (i = wanruzuo2; i < cutline; i++)
                                            {
                                                if (P_Pixels[i][185] == 0)
                                                {
                                                    wanruzuo3 = i;
                                                    break;
                                                }
                                            }
                                            if (wanruzuo3 > 30 && wanruzuo3 - wanruzuo2 < 20)
                                            {
                                                huandaozuoflag2 = 1;
                                                huandaozuoflag1 = 1;

                                                temp = 0;
                                                for (i = 1; i < cutline; i++)
                                                {
                                                    if (P_Pixels[i][180] == 0)
                                                    {
                                                        temp = i;
                                                        break;
                                                    }
                                                }
                                                j = 0;
                                                for (i = 1; i < cutline; i++)
                                                {
                                                    if (P_Pixels[i][199] == 0)
                                                    {
                                                        j = i;
                                                        break;
                                                    }
                                                    if (i == cutline - 1)
                                                    {
                                                        j = i;
                                                    }
                                                }
                                                if (temp < wanruzuo1 || temp < j)
                                                {
                                                    huandaozuoflag2 = 0;
                                                    huandaozuoflag1 = 0;
                                                }
                                                if ((L_black[wanruzuo1 + 8] - R_black[wanruzuo1 + 8]) - (L_black[wanruzuo1 + 3] - R_black[wanruzuo1 + 3]) > 0)
                                                {
                                                    huandaozuoflag2 = 0;
                                                    huandaozuoflag1 = 0;

                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                    //如果前两种没判断出来
                    // //用户自定义("补充环岛" + leftall+rightall);
                    if (cutline > 55 && huandaozuoflag2 == 0 && leftall == 0 && rightall == 1)
                    {
                        temp = 0;
                        for (i = 0; i < 40; i++)
                        {
                            if (L_black[i] > 190)
                            {
                                temp++;
                            }
                            if (i == 39 || L_black[i] <= 190)
                            {
                                if (i == 39)
                                {
                                    temp = 0;
                                }
                                break;
                            }
                        }
                        j = 0;
                        //用户自定义("补充环岛" + temp);
                        if (temp > 5 && (L_black[temp] - R_black[temp]) > (L_black[temp + 4] - R_black[temp + 4]))
                        {

                            a = 0;
                            for (i = (byte)(temp); i < 60; i++)
                            {
                                if (L_black[i + 2] - L_black[i] < 0)
                                {
                                    a++;  //向右趋势
                                }
                                if (L_black[i + 2] - L_black[i] > 0)
                                {
                                    j = i;
                                    if (L_black[i + 8] - L_black[i + 2] < 0 || j - temp < 10 || L_black[temp] - L_black[j] < 20 || j - temp > 45)
                                    {
                                        j = 0;//转向
                                    }
                                    break;
                                }
                                if (i == 59)
                                {
                                    j = 0;
                                }
                            }

                        }
                        b = 0;
                        if (L_black[temp + 10] - L_black[temp + 3] != 0)
                        {
                            khuan = (float)(7) / (float)(L_black[temp + 10] - L_black[temp + 3]);
                        }
                        else
                        {
                            khuan = 0;
                        }
                        //找上边最右值
                        for (i = j; i < cutline - 1; i++)
                        {
                            if (L_black[i + 1] < L_black[i])
                            {
                                b = i;
                                if (b - j < 7 || L_black[i] - L_black[j] < 20)
                                {
                                    b = 0;
                                }
                                break;
                            }
                            if (i == cutline - 2)
                            {
                                b = 0;
                            }
                        }
                        c = 0;
                        //找上边跳变
                        if (L_black[b] - L_black[j] > 20 && b > 10)
                        {

                            for (i = j; i < b; i++)
                            {
                                if (L_black[i + 1] - L_black[i] > 10)
                                {
                                    c = 1;
                                    break;

                                }
                                if (i == b - 1)
                                {
                                    c = 0;
                                }

                            }
                        }
                        //用户自定义("aaaaaaaaaa"+khuan);
                        //用户自定义("aaaaaaaaaa" +a+j);
                        if (temp > 5 && a > 10 && j > 5 && P_Pixels[j + 5][L_black[j]] > 0 && P_Pixels[j - 5][L_black[j]] > 0 && c == 1 && khuan > -0.7 && khuan < 0)
                        {
                            for (i = j; i < cutline; i++)
                            {
                                if (L_black[i] - R_black[i] > fixValue[i] + 5)
                                {
                                    huandaozuoflag1 = 1;
                                    huandaozuoflag2 = 1;
                                    break;
                                }
                            }
                        }
                    }

                    if (huandaozuoflag2 == 1 && L_black[0] < 199 && L_black[10] < 199 && L_black[20] < 199 && L_black[5] < 199 && L_black[0] > L_black[3])
                    {
                        temp = 0;
                        a = 0;
                        b = 0;
                        for (i = 0; i < cutline - 10; i++)
                        {
                            if (L_black[i + 3] - L_black[i] < 0)
                            {
                                temp++;
                            }
                            if (L_black[i + 3] - L_black[i] > 0)
                            {
                                a = i;
                                break;
                            }
                            if (i == cutline - 11)
                            {
                                temp = 0;
                            }

                        }
                        if (temp > 15)
                        {
                            for (i = a; i < cutline - 10; i++)
                            {
                                if (L_black[i] == 199 || L_black[i + 3] - L_black[i] < 0)
                                {
                                    b = i;
                                    break;
                                }
                                if (i == cutline - 11)
                                {
                                    b = 0;
                                }
                            }
                        }
                        if (temp > 10 && b - a > 5)
                        {
                            huandaozuoflag3 = 1;
                        }
                        //用户自定义("ssssss"+temp+b+a);
                    }
                    if (huandaozuoflag3 == 1)
                    {
                        huandaofangxiang = 2;
                        huandaozuoflag2 = 0;
                        huandaozuoflag1 = 0;
                        if (huandaowanflag != 3)
                        {
                            for (i = 0; i < cutline - 6; i++)
                            {
                                if (L_black[i] == 199 && L_black[i + 1] == 199 && L_black[i + 2] == 199)
                                {
                                    huandaozuosao = i;
                                    break;
                                }
                            }
                            for (i = (byte)(huandaozuosao + 3); i < 64; i++)
                            {
                                if (P_Pixels[i][199] == 0 && P_Pixels[i + 1][199] == 0 && P_Pixels[i + 2][199] == 0)
                                {
                                    huandaozuosao1 = i;
                                    break;
                                }
                            }
                        }
                        //快要进入环岛弯
                        if (huandaowanflag == 0)
                        {
                            temp = 0;

                            for (i = 0; i < huandaozuosao1; i++)
                            {
                                if (L_black[i] < L_black[i + 3])
                                {
                                    temp = i;
                                    break;
                                }
                                if (i == huandaozuosao1 - 1)
                                {
                                    temp = 0;
                                }
                            }
                            if (huandaozuosao > 10)
                            {
                                for (i = (byte)(temp); i < huandaozuosao1; i++)
                                {
                                    LCenter[i] = (byte)(L_black[i] - fixValue[i] / 2);
                                    if (L_black[i] - fixValue[i] / 2 < R_black[i])
                                    {
                                        LCenter[i] = R_black[i];
                                    }
                                }
                                for (i = 0; i < temp; i++)
                                {
                                    LCenter[i] = LCenter[temp];

                                }
                                for (i = (byte)(huandaozuosao - 1); i < (huandaozuosao1 - huandaozuosao + 1) / 3 * 2 + huandaozuosao - 1; i++)
                                {
                                    LCenter[i] = (byte)(LCenter[huandaozuosao - 1] + (i - huandaozuosao + 1) * (199 - LCenter[huandaozuosao - 1]) / (double)((huandaozuosao1 - huandaozuosao + 1) / 3 * 2));
                                }
                                if (huandaozuosao1 != 0)
                                {
                                    for (i = (byte)((huandaozuosao1 - huandaozuosao + 1) / 3 * 2 + huandaozuosao - 1); i < cutline; i++)
                                    {
                                        LCenter[i] = 199;
                                    }
                                }

                            }
                            else
                            {
                                if (R_black[0] < 20)
                                {
                                    LCenter[0] = (byte)(L_black[0] - fixValue[0] / 2);
                                }
                                else
                                {
                                    LCenter[0] = (byte)((R_black[0] + L_black[0]) / 2);
                                }
                                for (i = 0; i < (huandaozuosao1 - huandaozuosao + 1) / 3 * 2 + huandaozuosao - 1; i++)
                                {
                                    LCenter[i] = (byte)(LCenter[0] + (i) * (199 - LCenter[0]) / (double)((huandaozuosao1 - huandaozuosao + 1) / 3 * 2 + huandaozuosao - 1));
                                }
                                if (huandaozuosao1 != 0)
                                {
                                    for (i = (byte)((huandaozuosao1 - huandaozuosao + 1) / 3 * 2 + huandaozuosao - 1); i < cutline; i++)
                                    {

                                        LCenter[i] = 199;

                                    }
                                }

                            }
                            temp = 0;
                            if (R_black[0] > 70)
                            {
                                for (i = R_black[0]; i > 2; i--)
                                {
                                    if (P_Pixels[0][i] > 0 && P_Pixels[0][i - 2] > 0)
                                    {
                                        temp = i;
                                        huandaoblackpoint = (byte)(R_black[0] - i);
                                        break;
                                    }
                                    if (i == 3)
                                    {
                                        normalhuan = 1;
                                        huandaoblackpoint = 0;
                                        temp = 0;
                                    }
                                }
                            }
                            j = 0;
                            if (huandaoblackpoint > 3 && temp > 5)
                            {
                                for (i = (byte)(temp - 1); i > 2; i--)
                                {
                                    if (P_Pixels[0][i] > 0)
                                    {
                                        j++;
                                    }

                                    if (j == 3)
                                    {
                                        huandaowanflag = 1;
                                        break;
                                    }
                                    if (P_Pixels[0][i] == 0)
                                    {
                                        break;
                                    }
                                }
                            }
                            if (huandaozuosao1 < 65)
                            {
                                for (i = (byte)(huandaozuosao1 + 5); i < 70; i++)
                                {
                                    if (L_black[i] != 199 || R_black[i] != 199)
                                    {
                                        ruflag = 0;
                                        break;
                                    }
                                }
                            }
                            if (ruflag == 1)
                            {
                                huandaowanflag = 1;
                            }
                        }
                        if (huandaowanflag == 1)
                        {
                            for (i = 0; i < cutline - 12 && cutline > 12; i++)
                            {
                                if (L_black[i] - L_black[i + 10] > 5)
                                {
                                    huandaowanflag = 2;
                                    break;
                                }
                            }



                        }
                        if (huandaowanflag == 2)
                        {
                            temp = 0;
                            for (i = 1; i < cutline - 2; i++)
                            {
                                if (L_black[i] - R_black[i] < 40)
                                {
                                    temp = i;
                                    break;
                                }
                                if (i == cutline - 3)
                                {
                                    temp = 0;
                                }
                            }

                        }
                        if (huandaowanflag == 2 && temp != 0)
                        {
                            j = 0;
                            for (i = (byte)temp; i < cutline - 2; i++)
                            {
                                if (199 - R_black[i] > 60)
                                {
                                    j = i;
                                    huandaowanflag = 3;
                                    break;
                                }

                            }

                        }


                        //快要出环岛了
                        if (huandaowanflag == 3 || (normalhuan == 1 && huandaowanflag != 1 && huandaowanflag != 2) || huandaochu1 == 1)
                        {
                            for (i = 0; i < cutline; i++)
                            {
                                if (L_black[i] == 199)
                                {
                                    huandaozuosao = i;
                                    break;
                                }
                            }
                            for (i = (byte)(huandaozuosao + 3); i < 66; i++)
                            {

                                if (P_Pixels[i][199] == 0 && P_Pixels[i + 1][199] == 0 && P_Pixels[i + 2][199] == 0)
                                {
                                    if (i > 5)
                                    {
                                        huandaozuosao1 = i;
                                        break;
                                    }
                                    else
                                    {
                                        break;
                                    }
                                }
                            }
                            if (dahuanflag == 0)
                            {
                                if (huandaozuosao > 10)
                                {
                                    for (i = (byte)(huandaozuosao - 1); i < (huandaozuosao1 - huandaozuosao + 1) / 3 * 2 + huandaozuosao - 1; i++)
                                    {
                                        LCenter[i] = (byte)(LCenter[huandaozuosao - 1] + (i - huandaozuosao + 1) * (199 - LCenter[huandaozuosao - 1]) / (double)((huandaozuosao1 - huandaozuosao + 1) / 3 * 2));
                                    }
                                    if (huandaozuosao1 != 0)
                                    {
                                        for (i = (byte)((huandaozuosao1 - huandaozuosao + 1) / 3 * 2 + huandaozuosao - 1); i < cutline; i++)
                                        {

                                            LCenter[i] = 199;

                                        }
                                    }
                                }
                                if (huandaozuosao <= 10)
                                {

                                    if (R_black[0] < 20)
                                    {
                                        LCenter[0] = (byte)(L_black[0] - fixValue[0] / 2);
                                    }
                                    else
                                    {
                                        LCenter[0] = (byte)((R_black[0] + L_black[0]) / 2);
                                    }
                                    for (i = 0; i < (huandaozuosao1 - huandaozuosao + 1) / 3 * 2 + huandaozuosao - 1; i++)
                                    {
                                        LCenter[i] = (byte)(LCenter[0] + (i) * (199 - LCenter[0]) / (double)((huandaozuosao1 - huandaozuosao + 1) / 3 * 2 + huandaozuosao - 1));
                                    }
                                    if (huandaozuosao1 != 0)
                                    {
                                        for (i = (byte)((huandaozuosao1 - huandaozuosao + 1) / 3 * 2 + huandaozuosao - 1); i < cutline; i++)
                                        {

                                            LCenter[i] = 199;

                                        }
                                    }

                                }
                            }
                            else
                            {
                                if (R_black[0] < 20)
                                {
                                    LCenter[0] = (byte)(L_black[0] - fixValue[0] / 2);
                                }
                                else
                                {
                                    LCenter[0] = (byte)((R_black[0] + L_black[0]) / 2);
                                }
                                for (i = 0; i < (huandaozuosao1 - huandaozuosao + 1) / 3 * 2 + huandaozuosao - 1; i++)
                                {
                                    LCenter[i] = (byte)(LCenter[0] + (i) * (199 - LCenter[0]) / (double)((huandaozuosao1 - huandaozuosao + 1) / 3 * 2 + huandaozuosao - 1));
                                }
                                if (huandaozuosao1 != 0)
                                {
                                    for (i = (byte)((huandaozuosao1 - huandaozuosao + 1) / 3 * 2 + huandaozuosao - 1); i < cutline; i++)
                                    {

                                        LCenter[i] = 199;

                                    }
                                }
                            }

                        }
                        for (i = 5; i < 25; i++)
                        {
                            if (R_black[i] - R_black[i - 5] > 2 && R_black[i] - R_black[i + 5] > 2 && R_black[i] - R_black[i - 1] >= 0 && R_black[i] - R_black[i + 1] > 0 && huandaowanflag != 0)
                            {
                                if (P_Pixels[i + 4][R_black[i]] > 0 && P_Pixels[i - 4][R_black[i]] > 0)
                                {
                                    huandaoyouguai = i;
                                    break;
                                }
                            }
                        }
                        if (huandaoyouguai != 0 && R_black[0] != 0)
                        {
                            huandaochu = 1;
                        }
                        if (huandaochu1 == 1 && R_black[0] > 10 && R_black[1] > 10 && R_black[2] > 10)
                        {
                            qingchuflag = 1;
                        }
                        if (huandaochu == 1 && R_black[0] < 10 && R_black[1] < 10 && R_black[2] < 10)
                        {
                            huandaochu1 = 1;

                        }
                        //用户自定义("huanaoawan"+huandaowanflag);
                        if (qingchuflag == 1)
                        {

                            huandaozuoflag1 = 0;
                            huandaozuoflag2 = 0;
                            huandaozuoflag3 = 0;
                            huandaozuosao = 0;
                            huandaozuosao1 = 0;
                            huandaochu = 0;
                            huandaochu1 = 0;

                            huandaocnt = 0;
                            huandaowanflag = 0;
                            normalhuan = 0;
                            LCenter[0] = (byte)((L_black[0] + R_black[0]) / 2);
                        }

                    }
                    if ((huandaozuoflag2 == 1 || huandaozuoflag1 == 1) && huandaozuoflag3 == 0)
                    {
                        for (i = 0; i < cutline; i++)
                        {
                            LCenter[i] = (byte)(R_black[i] + fixValue[i] / 2);
                            if (R_black[i] + fixValue[i] / 2 > L_black[i])
                            {
                                LCenter[i] = L_black[i];
                            }
                        }

                    }
                    if (huandaozuoflag3 == 1 || huandaoyouflag3 == 1)
                    {
                        qipaojiance = 1;
                    }  //开始执行起跑线检测

                    ////用户自定义("huandaowan" + huandaozuosao + huandaozuosao1);
                }
                huandaogeshu = kind_huancnt(qingchuflag);
                if (huandaogeshu == 1 && (huandao_type[0] == 4))
                {
                    dahuanflag = 1;
                }
                else if (huandaogeshu == 3 && (huandao_type[1] == 4))
                {
                    dahuanflag = 1;
                }
                else if (huandaogeshu == 5 && ( huandao_type[2] == 4))
                {
                    dahuanflag = 1;
                }
                else if (huandaogeshu == 7 && ( huandao_type[3] == 4))
                {
                    dahuanflag = 1;
                }
                else
                {
                    dahuanflag = 0;
                }

            }

            //
            if (huandaoyouflag1 == 1 || huandaoyouflag2 == 1 || huandaoyouflag3 == 1 || huandaozuoflag1 == 1 || huandaozuoflag2 == 1 || huandaozuoflag3 == 1)
            {
                huandaoflag = 1;
                crossflag = 0;
            }
            if (huandaoyouflag1 == 0 && huandaoyouflag2 == 0 && huandaoyouflag3 == 0 && huandaozuoflag1 == 0 && huandaozuoflag2 == 0 && huandaozuoflag3 == 0)
            {
                huandaoflag = 0;
            }
            /********************十字********************************/
            //  环岛修补 以及弯道接十字无拐点修补
            //斜十字
            if (Cross_Lean_L_in == 1 && Cross_Lean_L == 0 && Cross_Lean_L_in_Row < 40 && Cross_Lean_L_in_Row > 6
                && L_black[Cross_Lean_L_in_Row + 10] - L_black[Cross_Lean_L_in_Row] >= 5)
            {


                b_L = Cross_Lean_L_in_Rank;
                K_L = (float)(L_black[Cross_Lean_L_in_Row - 2] - L_black[Cross_Lean_L_in_Row - 6]) / (float)(4);
                if (K_L < 0)
                    a = 1;
                else
                {
                    a = 0;

                }

                if (a == 1)
                {

                    j = 0;
                    for (i = Cross_Lean_L_in_Row; i < cutline; i++)
                    {
                        L_black[i] = Check_Overrun199((int)(b_L + (i - Cross_Lean_L_in_Row) * K_L));
                        if (R_black[i] < 10)
                            R_black[i] = 0;
                        if (L_black[i] - R_black[i] <= 5)
                            break;

                    }

                }


            }
            if (Cross_Lean_R == 1 && Cross_Lean_R == 0 && Cross_Lean_R_in_Row < 40 && Cross_Lean_R_in_Row > 6
                && R_black[Cross_Lean_R_in_Row + 5] - R_black[Cross_Lean_R_in_Row] <= -4)
            {
                //  //用户自定义("疑似右斜十字  ");
                b_R = Cross_Lean_R_in_Rank;
                K_R = (float)(R_black[Cross_Lean_R_in_Row - 2] - R_black[Cross_Lean_R_in_Row - 6]) / (float)(4);

                if (K_R > 0)
                    b = 1;
                else
                {
                    b = 0;

                }

                if (b == 1)
                {
                    for (i = Cross_Lean_R_in_Row; i < cutline; i++)
                    {
                        R_black[i] = Check_Overrun199((int)(b_R + (i - Cross_Lean_R_in_Row) * K_R));
                        if (L_black[i] > 190)
                            L_black[i] = 199;
                        if (L_black[i] - R_black[i] <= 5)
                            break;
                    }
                }
            }
            //
            // 十字
            /********************十字********************************/
            if (huandaoflag == 0 && poflag == 0 && blockflag == 0 && smallsflag == 0)
            {
                //直入十字补线
                if (Cross_Straight_Flag == 1)
                {
                    //   //用户自定义("直十字 ");
                    // element = Element_Cross_Straight;
                    b_L = Cross_Straight_L_in_Rank;
                    b_R = Cross_Straight_R_in_Rank;
                    K_L = (float)(Cross_Straight_L_out_Rank - Cross_Straight_L_in_Rank) / (float)(Cross_Straight_L_out_Row - Cross_Straight_L_in_Row);
                    K_R = (float)(Cross_Straight_R_out_Rank - Cross_Straight_R_in_Rank) / (float)(Cross_Straight_R_out_Row - Cross_Straight_R_in_Row);

                    if (K_L < 1)
                    {
                        a = 1;
                    }
                    else
                    {
                        a = 0;
                    }
                    if (K_R > -1)
                    {
                        b = 1;
                    }
                    else
                    {
                        b = 0;
                    }
                    if (a == 1)//拉线标志
                        Shizila_flagL = 1;
                    if (b == 1)
                        Shizila_flagR = 1;
                    for (i = 0; i <= cutline; i++)
                    {
                        if (a == 1 && i >= Cross_Straight_L_in_Row && i <= Cross_Straight_L_out_Row)
                        {
                            L_black[i] = Check_Overrun199((int)(b_L + (i - Cross_Straight_L_in_Row) * K_L));
                        }
                        if (b == 1 && i >= Cross_Straight_R_in_Row && i <= Cross_Straight_R_out_Row)
                        {
                            R_black[i] = Check_Overrun199((int)(b_R + (i - Cross_Straight_R_in_Row) * K_R));
                        }
                        if ((L_black[i] - R_black[i] < fixValue[i] - 25 && L_black[i] < 190 && R_black[i] > 10))
                            break;
                    }
                    //用户自定义("十字补线跳出 i" + i);
                }
                //斜十字
                if (Cross_Lean_L == 1)
                {
                    //用户自定义("左斜十字 " + "入行 " + Cross_Lean_L_in_Row + "出行 " + Cross_Lean_L_out_Row);

                    // element = Element_Cross_Lean_L;
                    b_L = Cross_Lean_L_in_Rank;
                    K_L = (float)(Cross_Lean_L_out_Rank - Cross_Lean_L_in_Rank) / (float)(Cross_Lean_L_out_Row - Cross_Lean_L_in_Row);
                    if (K_L <= 0)
                    {
                        a = 1;
                    }
                    else
                    {
                        a = 0;

                    }
                    b = 0;
                    if (R_black[Cross_Lean_L_out_Row] > 5)
                    {
                        for (i = Check_Overrun69(Cross_Lean_L_out_Row + 10); i > Cross_Lean_L_out_Row - 10 && i > 0; i--)
                        {
                            if (R_black[i] - R_black[i - 1] > 5 && i + 4 < cutline)
                                if (R_black[i + 4] >= R_black[i])
                                {
                                    b_R = R_black[i];
                                    K_R = (float)(R_black[i + 4] - R_black[i]) / (float)4.0;
                                    b = 1;
                                    Cross_Lean_R_out_Row = i;
                                    break;
                                }
                            if (R_black[i] <= 1)
                                break;
                        }
                    }
                    if (K_R <= 0)
                        b = 0;

                    if (a == 1)
                    {
                        for (i = Cross_Lean_L_in_Row; i <= Cross_Lean_L_out_Row; i++)
                        {
                            L_black[i] = Check_Overrun199((int)(b_L + (i - Cross_Lean_L_in_Row) * K_L));

                        }
                    }
                    if (b == 1)
                    {
                        for (i = Cross_Lean_R_out_Row; i >= 0; i--)
                        {
                            j = R_black[i];
                            R_black[i] = Check_Overrun199((int)(b_R - K_R * (Cross_Lean_R_out_Row - i)));
                            if (L_black[i] - R_black[i] <= 5)//错误补线 恢复
                            {
                                R_black[i] = j;
                                break;
                            }
                            if (i == 0)
                                break;
                        }
                    }
                    if (a == 1 && b == 1 && L_black[10] - L_black[0] < -10)//根据斜率判断是否平移
                        Cross_Pingyi = 1;
                    if (a == 1)//拉线标志
                        Shizila_flagL = 1;
                    if (b == 1)
                        Shizila_flagR = 1;
                }
                if (Cross_Lean_R == 1)
                {
                    //用户自定义("右斜十字 入行 " + Cross_Lean_R_in_Row + " 出 " + Cross_Lean_R_out_Row);
                    b_R = Cross_Lean_R_in_Rank;
                    K_R = (float)(Cross_Lean_R_out_Rank - Cross_Lean_R_in_Rank) / (float)(Cross_Lean_R_out_Row - Cross_Lean_R_in_Row);

                    if (K_R >= 0)
                        b = 1;
                    else
                    {
                        b = 0;

                        //  element = 0;
                    }
                    a = 0;
                    if (L_black[Cross_Lean_R_out_Row] < 195)
                    {
                        for (i = Check_Overrun69(Cross_Lean_R_out_Row + 10); i > Cross_Lean_R_out_Row - 10 && i > 0; i--)
                        {
                            if (L_black[i] - L_black[i - 1] < -5 && i + 4 < cutline)
                                if (L_black[i + 4] <= L_black[i])
                                {
                                    b_L = L_black[i];
                                    K_L = (float)(L_black[i + 4] - L_black[i]) / (float)4.0;
                                    a = 1;
                                    Cross_Lean_L_out_Row = i;
                                    break;
                                }
                            if (L_black[i] >= 198)
                                break;
                        }
                    }
                    if (K_L >= 0)
                        a = 0;
                    if (b == 1)
                    {
                        for (i = Cross_Lean_R_in_Row; i < Cross_Lean_R_out_Row; i++)
                        {
                            R_black[i] = Check_Overrun199((int)(b_R + (i - Cross_Lean_R_in_Row) * K_R));
                        }

                    }
                    if (a == 1)
                    {
                        for (i = 0; i <= Cross_Lean_L_out_Row; i++)
                        {
                            j = L_black[i];
                            L_black[i] = Check_Overrun199((int)(b_L + (i - Cross_Lean_L_out_Row) * K_L));
                            if (L_black[i] - R_black[i] <= 5)//补线 恢复
                            {
                                L_black[i] = j;
                                break;
                            }
                        }
                    }
                    if (a == 1 && b == 1 && R_black[10] - R_black[0] > 10)
                        Cross_Pingyi = 1;
                    if (a == 1)//拉线标志
                        Shizila_flagL = 1;
                    if (b == 1)
                        Shizila_flagR = 1;
                }

                //无拐点十字  左
                if ((Cross_No_RightAngle_L_Memory == 1 || Cross_No_RightAngle_L_Memory == 2) && Cross_No_RightAngle_R_Memory == 0)
                {


                    if (L_black[0] > 180 && R_black[0] < 20 && Cross_Allwhite2cnt < 2)//判断到全白而且左右都能找到跳变
                        Cross_Allwhite2cnt++;
                    else
                        Cross_Allwhite2cnt = 0;
                    if (Cross_Allwhite2cnt == 0)
                    {
                        for (i = 0, j = 0; i < Cross_NR_L_Memory_out_Row && i < 40; i++)
                        {
                            if (L_black[i] - R_black[i] > 195)
                                j++;
                            if (j > 7)
                            {
                                Cross_Allwhite2cnt = 1;
                                break;
                            }
                        }
                    }
                    if (Cross_Allwhite2cnt >= 1)
                    {
                        //用户自定义("到全白记忆--无拐点左十字清除 ");
                        Cross_No_RightAngle_R_Memory = Cross_No_RightAngle_L_Memory = 0;
                        Cross_Allwhite2cnt = 0;
                        Cross_Allwhite2 = 1;
                        Cross_Allw2_first = 1;
                        Cross_Allwhite2_L = Cross_Allwhite2_R = 1;
                        Cross_Allwhite2_L_out_Row = Cross_NR_L_Memory_out_Row;
                        Cross_Allwhite2_R_out_Row = Cross_NR_L_Memory_out_Row;
                    }
                    if (Cross_No_RightAngle_L_Memory > 0)
                    {
                        //用户自定义("无拐点十字左 左行" + Cross_NR_L_Memory_out_Row);

                        if (Cross_NR_L_cnt > 0)
                            Cross_NR_L_cnt--;
                        if (Cross_NR_L_cnt == 0)
                        {
                            //用户自定义("计数清除左拐点 ");
                            Cross_No_RightAngle_L_Memory = 0;
                        }

                        if (R_black[Cross_NR_R_Memory_out_Row] < 20
                            && L_black[Cross_NR_R_Memory_out_Row] - L_black[Cross_NR_R_Memory_out_Row] > fixValue[Cross_NR_R_Memory_out_Row] + 10)
                            Cross_NR_R_Memory_out_Row = Check_Overrun69(Cross_NR_L_Memory_out_Row + 5);
                        else
                            Cross_NR_R_Memory_out_Row = Cross_NR_L_Memory_out_Row;

                        Cross_NR_L_start = L_black[Check_Overrun69(Cross_NR_L_Memory_out_Row + 2)];
                        Cross_NR_R_start = R_black[Check_Overrun69(Cross_NR_R_Memory_out_Row + 2)];
                        if (Cross_NR_L_start - Cross_NR_R_start <= 10 && Cross_NR_R_start < 5)
                            Cross_NR_L_start = (byte)(Cross_NR_R_start + 10);
                        b_L = L_black[Cross_NR_L_Memory_out_Row];
                        if (L_black[0] < 180)
                            K_L = (float)(L_black[Cross_NR_L_Memory_out_Row] - L_black[0]) / (float)(Cross_NR_L_Memory_out_Row);
                        else
                            K_L = (float)(L_black[Cross_NR_L_Memory_out_Row + 4] - L_black[Cross_NR_L_Memory_out_Row]) / (float)(4);

                        b_R = R_black[Cross_NR_L_Memory_out_Row];
                        if (R_black[0] >= 10)
                            K_R = (float)(R_black[Cross_NR_L_Memory_out_Row] - R_black[0]) / (float)(Cross_NR_L_Memory_out_Row);
                        else
                            K_R = (float)(R_black[Cross_NR_L_Memory_out_Row + 4] - R_black[Cross_NR_L_Memory_out_Row]) / (float)(4);
                        if (K_L <= 0)
                            a = 1;
                        else
                        {
                            a = 0;
                        }
                        if (K_R >= 0)
                            b = 1;
                        else
                        {
                            b = 0;

                        }
                        for (i = Cross_NR_L_Memory_out_Row; i >= 0; i--)
                        {
                            if (a == 1)
                                L_black[i] = Check_Overrun199((int)(b_L + (i - Cross_NR_L_Memory_out_Row) * K_L));
                            if (b == 1)
                                R_black[i] = Check_Overrun199((int)(b_R + (i - Cross_NR_L_Memory_out_Row) * K_R));
                            if (L_black[i] - R_black[i] < 20 && L_black[i] < 190 && R_black[i] > 0)
                                break;
                            if (i == 0)
                                break;
                        }
                        //用户自定义("ab" + a + b + " i " + i);


                    }

                    if (a == 1)//拉线标志
                        Shizila_flagL = 1;
                    if (b == 1)
                        Shizila_flagR = 1;
                }
                //右
                if ((Cross_No_RightAngle_L_Memory == 0) && (Cross_No_RightAngle_R_Memory == 2 || Cross_No_RightAngle_R_Memory == 1))
                {
                    if (L_black[0] > 180 && R_black[0] < 20 && Cross_Allwhite2cnt < 2)
                        Cross_Allwhite2cnt++;
                    else
                        Cross_Allwhite2cnt = 0;
                    if (Cross_Allwhite2cnt == 0)
                    {
                        for (i = 0, j = 0; i < Cross_NR_R_Memory_out_Row && i < 40; i++)
                        {
                            if (L_black[i] - R_black[i] > 195)
                                j++;
                            if (j > 7)
                            {
                                Cross_Allwhite2cnt = 1;
                                break;
                            }
                        }
                    }
                    if (Cross_Allwhite2cnt >= 1)
                    {
                        Cross_No_RightAngle_L_Memory = Cross_No_RightAngle_R_Memory = 0;
                        Cross_Allwhite2cnt = 0;
                        Cross_Allwhite2 = 1;
                        Cross_Allw2_first = 1;
                        Cross_Allwhite2_L = Cross_Allwhite2_R = 1;
                        Cross_Allwhite2_L_out_Row = Cross_NR_R_Memory_out_Row;
                        Cross_Allwhite2_R_out_Row = Cross_NR_R_Memory_out_Row;
                    }

                    if (Cross_No_RightAngle_R_Memory > 0)
                    {
                        //用户自定义("无拐点十字右 出右行" + Cross_NR_R_Memory_out_Row + " 出左行 " + Cross_NR_L_Memory_out_Row);

                        if (Cross_NR_R_cnt > 0)
                            Cross_NR_R_cnt--;
                        if (Cross_NR_R_cnt == 0)
                            Cross_No_RightAngle_R_Memory = 0;

                        if (L_black[Cross_NR_R_Memory_out_Row] < 180
                            && L_black[Cross_NR_R_Memory_out_Row] - L_black[Cross_NR_R_Memory_out_Row] > fixValue[Cross_NR_R_Memory_out_Row] + 10)
                            Cross_NR_L_Memory_out_Row = Cross_NR_R_Memory_out_Row;
                        else
                            Cross_NR_L_Memory_out_Row = Check_Overrun69(Cross_NR_R_Memory_out_Row + 5);

                        Cross_NR_L_start = L_black[Check_Overrun69(Cross_NR_L_Memory_out_Row + 5)];
                        Cross_NR_R_start = R_black[Check_Overrun69(Cross_NR_R_Memory_out_Row + 5)];
                        if (Cross_NR_L_start - Cross_NR_R_start <= 10 && Cross_NR_L_start > 195)
                            Cross_NR_R_start = (byte)(Cross_NR_L_start - 10);

                        b_L = L_black[Cross_NR_L_Memory_out_Row];
                        if (L_black[0] <= 190)
                            K_L = (float)(L_black[Cross_NR_L_Memory_out_Row] - L_black[0]) / (float)(Cross_NR_L_Memory_out_Row);
                        else
                            K_L = (float)(L_black[Cross_NR_L_Memory_out_Row + 4] - L_black[Cross_NR_L_Memory_out_Row]) / (float)(4);

                        b_R = R_black[Cross_NR_R_Memory_out_Row];
                        if (R_black[0] > 20)
                            K_R = (float)(R_black[Cross_NR_R_Memory_out_Row] - R_black[0]) / (float)(Cross_NR_R_Memory_out_Row);
                        else
                            K_R = (float)(R_black[Cross_NR_R_Memory_out_Row + 4] - R_black[Cross_NR_R_Memory_out_Row]) / (float)(4);
                        if (K_L <= 0)
                            a = 1;
                        else
                        {
                            a = 0;

                        }
                        if (K_R >= 0)
                            b = 1;
                        else
                        {
                            b = 0;
                        }
                        //用户自定义("a" + a + "b" + b);
                        for (i = Cross_NR_R_Memory_out_Row; i >= 0; i--)
                        {
                            if (a == 1)
                                L_black[i] = Check_Overrun199((int)(b_L + (i - Cross_NR_R_Memory_out_Row) * K_L));
                            if (b == 1)
                                R_black[i] = Check_Overrun199((int)(b_R + (i - Cross_NR_R_Memory_out_Row) * K_R));
                            if (L_black[i] - R_black[i] < 20 && L_black[i] < 190 && R_black[i] > 10)
                                break;
                            if (i == 0)
                                break;
                        }
                        //用户自定义("i" + i);
                    }
                    if (a == 1)//拉线标志
                        Shizila_flagL = 1;
                    if (b == 1)
                        Shizila_flagR = 1;
                }

                //左右拐点同时丢
                if (Cross_No_RightAngle_L_Memory > 0 && Cross_No_RightAngle_R_Memory > 0 && Cross_Straight_Flag == 0)
                {
                    if (L_black[0] > 180 && R_black[0] < 20 && Cross_Allwhite2cnt < 2)
                        Cross_Allwhite2cnt++;
                    else
                        Cross_Allwhite2cnt = 0;
                    if (Cross_Allwhite2cnt >= 1)
                    {
                        //用户自定义("左右拐点同时丢 --全白十字记忆");
                        Cross_No_RightAngle_L_Memory = Cross_No_RightAngle_R_Memory = 0;
                        Cross_Allwhite2cnt = 0;
                        Cross_Allwhite2 = 1;
                        Cross_Allw2_first = 1;

                        Cross_Allwhite2_L = Cross_Allwhite2_R = 1;
                        Cross_Allwhite2_L_out_Row = Cross_NR_L_Memory_out_Row;
                        Cross_Allwhite2_R_out_Row = Cross_NR_R_Memory_out_Row;
                        Cross_Allwhite_L_start = L_black[Check_Overrun69(Cross_Allwhite2_L_out_Row + 5)];
                        Cross_Allwhite_R_start = R_black[Check_Overrun69(Cross_Allwhite2_R_out_Row + 5)];
                    }

                    if (Cross_No_RightAngle_L_Memory > 0 && Cross_No_RightAngle_R_Memory > 0)
                    {
                        Cross_NR_L_start = L_black[Check_Overrun69(Cross_NR_L_Memory_out_Row + 5)];
                        Cross_NR_R_start = R_black[Check_Overrun69(Cross_NR_R_Memory_out_Row + 5)];

                        if (L_black[Cross_NR_L_Memory_out_Row] > 175)//一边跳变位置 靠边
                        {
                            Cross_No_RightAngle_L_Memory = 0;
                            Cross_NR_R_cnt = Cross_NR_LR_cnt;

                        }
                        if (R_black[Cross_NR_R_Memory_out_Row] < 25)//一边跳变位置 
                        {
                            Cross_No_RightAngle_R_Memory = 0;
                            Cross_NR_L_cnt = Cross_NR_LR_cnt;
                            //用户自定义("右侧无跳变 cnt " + Cross_NR_R_cnt);
                        }
                        //用户自定义("无拐点十字左右 ");

                        if (Cross_NR_LR_cnt > 0)
                            Cross_NR_LR_cnt--;
                        if (Cross_NR_LR_cnt == 0)
                            Cross_No_RightAngle_L_Memory = Cross_No_RightAngle_R_Memory = 0;

                        // element = Element_Cross_NR;
                        b_L = L_black[Cross_NR_L_Memory_out_Row];
                        if (L_black[0] < 180)
                            K_L = (float)(L_black[Cross_NR_L_Memory_out_Row] - L_black[0]) / (float)(Cross_NR_L_Memory_out_Row);
                        else
                            K_L = (float)(L_black[Cross_NR_L_Memory_out_Row + 6] - L_black[Cross_NR_L_Memory_out_Row + 2]) / (float)(4);

                        b_R = R_black[Cross_NR_R_Memory_out_Row];
                        if (R_black[0] > 20)
                            K_R = (float)(R_black[Cross_NR_R_Memory_out_Row] - R_black[0]) / (float)(Cross_NR_R_Memory_out_Row);
                        else
                            K_R = (float)(R_black[Cross_NR_R_Memory_out_Row + 6] - R_black[Cross_NR_R_Memory_out_Row + 2]) / (float)(4);

                        if (K_L <= 0)
                            a = 1;
                        else
                        {
                            a = 0;
                        }
                        if (K_R >= 0)
                            b = 1;
                        else
                        {
                            b = 0;
                        }
                        for (i = Cross_NR_R_Memory_out_Row > Cross_NR_L_Memory_out_Row ? Cross_NR_R_Memory_out_Row : Cross_NR_L_Memory_out_Row
                            ; i >= 0; i--)
                        {
                            if (a == 1 && i < Cross_NR_L_Memory_out_Row)
                                L_black[i] = Check_Overrun199((int)(b_L + (i - Cross_NR_L_Memory_out_Row) * K_L));
                            if (b == 1 && i < Cross_NR_R_Memory_out_Row)
                                R_black[i] = Check_Overrun199((int)(b_R + (i - Cross_NR_R_Memory_out_Row) * K_R));
                            if (i == 0 || (L_black[i] - R_black[i] < fixValue[i] - 25 && L_black[i] < 190 && R_black[i] > 10))
                                break;
                        }
                    }
                    if (a == 1)//拉线标志
                        Shizila_flagL = 1;
                    if (b == 1)
                        Shizila_flagR = 1;
                }

                if (Cross_Allwhite == 1)//全白十字前两场
                {
                    a = b = 0;
                    if (L_black[0] > 180 && R_black[0] < 20 && Cross_Allwhite2cnt < 2)
                        Cross_Allwhite2cnt++;
                    else
                        Cross_Allwhite2cnt = 0;
                    if (Cross_Allwhite2cnt >= 1)
                    {
                        //用户自定义("左右拐点同时丢 --全白十字记忆");
                        Cross_Allwhite2cnt = 0;
                        Cross_Allwhite2 = 1;
                        Cross_Allw2_first = 1;
                        Cross_Allwhite = 0;
                        Cross_Allwhite2_L = Cross_Allwhite2_R = 1;
                        Cross_Allwhite2_L_out_Row = Cross_Allwhite_L_out_Row;
                        Cross_Allwhite2_R_out_Row = Cross_Allwhite_R_out_Row;
                        Cross_Allwhite_L_start = L_black[Check_Overrun69(Cross_Allwhite2_L_out_Row + 5)];
                        Cross_Allwhite_R_start = R_black[Check_Overrun69(Cross_Allwhite2_R_out_Row + 5)];
                    }

                    if (Cross_Allwhite == 1)
                    {
                        Cross_Allwhite_L_start = L_black[Check_Overrun69(Cross_Allwhite2_L_out_Row + 5)];
                        Cross_Allwhite_R_start = R_black[Check_Overrun69(Cross_Allwhite2_R_out_Row + 5)];

                        //用户自定义("全白十字");
                        b_L = Cross_Allwhite_L_out_Rank;
                        K_L = (float)(L_black[Cross_Allwhite_L_out_Row + 4] - L_black[Cross_Allwhite_L_out_Row]) / (float)(4);
                        b_R = Cross_Allwhite_R_out_Rank;
                        K_R = (float)(R_black[Cross_Allwhite_R_out_Row + 4] - R_black[Cross_Allwhite_R_out_Row]) / (float)(4);
                        if (K_L <= 0)
                            a = 1;
                        else
                        {
                            a = 0;

                        }
                        if (K_R >= 0)
                            b = 1;
                        else
                        {
                            b = 0;

                        }

                        for (i = Cross_Allwhite_L_out_Row > Cross_Allwhite_R_out_Row ? Cross_Allwhite_L_out_Row : Cross_Allwhite_R_out_Row
                            ; i >= 0; i--)
                        {
                            if (a == 1 && i < Cross_Allwhite_L_out_Row)
                                L_black[i] = Check_Overrun199((int)(b_L + (i - Cross_Allwhite_L_out_Row) * K_L));
                            if (b == 1 && i < Cross_Allwhite_R_out_Row)
                                R_black[i] = Check_Overrun199((int)(b_R + (i - Cross_Allwhite_R_out_Row) * K_R));
                            if (i == 0 || (L_black[i] - R_black[i] < fixValue[i] - 10 && L_black[i] < 190 && R_black[i] > 10))
                                break;
                        }
                    }
                    if (a == 1)//拉线标志
                        Shizila_flagL = 1;
                    if (b == 1)
                        Shizila_flagR = 1;
                    if (Cross_Allwhite_L_out_Row > 3 && Cross_Allwhite_R_out_Row > 3//全白十字直补一场，就进到十字记忆状态
                       && L_black[Cross_Allwhite_L_out_Row + 1] - L_black[Cross_Allwhite_L_out_Row - 3] < -5
                        && R_black[Cross_Allwhite_R_out_Row + 1] - R_black[Cross_Allwhite_R_out_Row - 3] > 5)
                    {
                        Cross_Allwhite2cnt = 0;
                        Cross_Allwhite2 = 1;
                        Cross_Allwhite = 0;
                        Cross_Allw2_first = 1;
                        Cross_Allwhite2_L = Cross_Allwhite2_R = 1;
                        Cross_Allwhite2_L_out_Row = Cross_Allwhite_L_out_Row;
                        Cross_Allwhite2_R_out_Row = Cross_Allwhite_R_out_Row;
                    }
                }
                if (Cross_Allwhite2 > 0)//全白十字记忆 补线
                {

                    //用户自定义("全白记忆2 " + Cross_Allwhite2_R + Cross_Allwhite2_L);
                    for (i = 0; i < 30; i++)
                    {
                        if (L_black[i] - R_black[i] > 190)
                            break;
                    }
                    if (Cross_Allw2_first == 0 &&
                        (L_black[0] - R_black[0] <= 170) && i == 30)//不满足宽度条件或者宽度条件
                    {
                        //用户自定义("十字清除1");
                        Cross_Allwhite2 = 0;
                    }
                    if ((Cross_Allwhite2_L == 0 && R_black[Cross_Allwhite2_R_out_Row + 1] - R_black[Cross_Allwhite2_R_out_Row - 1] < 10)//比如左边无跳变而且右边跳变不够大就清除处十字
                        || (Cross_Allwhite2_R == 0 && L_black[Cross_Allwhite2_L_out_Row + 1] - L_black[Cross_Allwhite2_L_out_Row - 1] > -10))
                    {
                        //用户自定义("十字清除2");

                        Cross_Allwhite2 = 0;
                    }

                    if (Cross_Allw2_first == 1)
                        Cross_Allw2_first = 0;
                    if (Cross_Allwhite2 == 1)
                    {
                        crossflag = 1;

                        if (Cross_Allwhite2_R == 0)
                            Cross_Allwhite2_R_out_Row = Cross_Allwhite2_L_out_Row;
                        if (Cross_Allwhite2_L == 0)
                            Cross_Allwhite2_L_out_Row = Cross_Allwhite2_R_out_Row;
                        Cross_Allwhite2_R_start = R_black[Check_Overrun69(Cross_Allwhite2_R_out_Row + 5)];
                        Cross_Allwhite2_L_start = L_black[Check_Overrun69(Cross_Allwhite2_L_out_Row + 5)];

                        b_L = L_black[Cross_Allwhite2_L_out_Row + 4];
                        K_L = (float)(L_black[Cross_Allwhite2_L_out_Row + 8] - L_black[Cross_Allwhite2_L_out_Row + 4]) / (float)(4);
                        b_R = R_black[Cross_Allwhite2_R_out_Row + 4];
                        K_R = (float)(R_black[Cross_Allwhite2_R_out_Row + 8] - R_black[Cross_Allwhite2_R_out_Row + 4]) / (float)(4);
                        if (K_L <= 0)
                            a = 1;
                        else
                        {
                            a = 0;
                        }
                        if (K_R >= 0)
                            b = 1;
                        else
                        {
                            b = 0;
                        }

                        //用户自定义("12123 " + Cross_Allwhite2_R + Cross_Allwhite2_L + " L " + Cross_Allwhite2_L_out_Row + " R " + Cross_Allwhite2_R_out_Row + "a " + a + " b " + b);

                        for (i = Cross_Allwhite2_L_out_Row > Cross_Allwhite2_R_out_Row ? Cross_Allwhite2_L_out_Row : Cross_Allwhite2_R_out_Row
                       ; i >= 0; i--)
                        {
                            if (a == 1 && i < Cross_Allwhite2_L_out_Row)
                                L_black[i] = Check_Overrun199((int)(b_L + (i - Cross_Allwhite2_L_out_Row) * K_L));
                            if (b == 1 && i < Cross_Allwhite2_R_out_Row)
                                R_black[i] = Check_Overrun199((int)(b_R + (i - Cross_Allwhite2_R_out_Row) * K_R));
                            if (i == 0 || (L_black[i] - R_black[i] < fixValue[i] - 25 && L_black[i] < 190 && R_black[i] > 10))
                                break;
                        }

                        //用户自定义("十字补线跳出 i" + i);

                    }
                    if (a == 1)//拉线标志
                        Shizila_flagL = 1;
                    if (b == 1)
                        Shizila_flagR = 1;
                }


            }

            //

            // 障碍
            /****************障碍*****************/
            if (zhangaigeshu <= 2 * blockcntmax)
            {

                if (poflag != 2 && crossflag == 0
                    && huandaoflag == 0 &&
                     cutline > 50
                    )
                {
                    Obstruction_0wide = (byte)((L_black[0] - R_black[0]));

                    if (Obstruction_LState == 0 && Obstruction_RState == 0 && L_black[0] - R_black[0] < fixValue[0] + 10)//障碍第一场判断
                    {

                        // Obstruction_RState
                        if (Cross_Straight_Flag == 1)
                            temporary = Cross_Straight_L_in_Row < Cross_Straight_R_in_Row ? Cross_Straight_L_in_Row : Cross_Straight_R_in_Row;
                        else if (Cross_Lean_L == 1)
                            temporary = Cross_Lean_L_in_Row;
                        else if (Cross_Lean_R == 1)
                            temporary = Cross_Lean_R_in_Row;
                        else
                            temporary = cutline;
                        //左障碍  
                        for (i = 0, j = 0, e = 0; i < temporary; i++)
                        {
                            if ((L_black[i] - R_black[i] <= fixValue[i] + 15) && P_Pixels[i][(L_black[i] + LCenter[i]) >> 1] == 0)
                            {
                                j += 1;
                                e = 0;
                            }
                            else if (j < 6)
                            {
                                if (e == 1)
                                    j = 0;
                                e = 1;
                            }

                            if (j == 6)
                            {
                                Obstruction_L_EdgeL_Row = Obstruction_L_EdgeH_Row = i;
                            }
                            //if (R_black[i] - R_black[i + 1] > 5 || L_black[i + 1] - L_black[i] > 5
                            //    )
                            //{
                            //    break;
                            //}
                            if (L_black[i] - L_black[i + 1] > 15 && i < 20)
                            {
                                j = 0;
                                break;
                            }

                        }

                        if (j > 6)
                        {
                            Obstruction_L_EdgeR_Rank = Obstruction_L_EdgeL_Rank =
                                (byte)((L_black[Obstruction_L_EdgeH_Row] + LCenter[Obstruction_L_EdgeH_Row]) >> 1);
                            //左边缘
                            for (i = Obstruction_L_EdgeL_Rank; i < (Obstruction_L_EdgeL_Rank + 15) && i < 199; i++)
                            {
                                if (P_Pixels[Obstruction_L_EdgeL_Row][i] > 0 || i >= L_black[Obstruction_L_EdgeL_Row])
                                    break;
                            }
                            Obstruction_L_EdgeL_Rank = i;
                            for (i = Obstruction_L_EdgeR_Rank; i > (Obstruction_L_EdgeR_Rank - 15) && i > 0; i--)
                            {
                                if (P_Pixels[Obstruction_L_EdgeL_Row][i] > 0 || i <= R_black[Obstruction_L_EdgeL_Row])
                                    break;
                            }
                            Obstruction_L_EdgeR_Rank = i;

                            j = (byte)((Obstruction_L_EdgeR_Rank + Obstruction_L_EdgeL_Rank) >> 1);
                            //上边缘行
                            for (i = Obstruction_L_EdgeH_Row; i < (Obstruction_L_EdgeH_Row + 30) && i < cutline; i++)
                            {
                                if (P_Pixels[i][j] > 0)
                                    break;
                            }
                            Obstruction_L_EdgeH_Row = i;
                            for (i = Obstruction_L_EdgeL_Row; i > (Obstruction_L_EdgeL_Row - 15) && i > 0; i--)
                            {
                                if (P_Pixels[i][j] > 0)
                                    break;
                            }
                            Obstruction_L_EdgeL_Row = i;
                            Obstruction_L_Mid_Row = (byte)((Obstruction_L_EdgeH_Row + Obstruction_L_EdgeL_Row) >> 1);

                            if (
                                Obstruction_L_EdgeH_Row - Obstruction_L_EdgeL_Row < 42
                                && ((Obstruction_L_EdgeL_Row < 2 && Obstruction_L_EdgeH_Row - Obstruction_L_EdgeL_Row > 6)
                                || ((Obstruction_L_EdgeL_Row < 30 && Obstruction_L_EdgeL_Row >= 2) && Obstruction_L_EdgeH_Row - Obstruction_L_EdgeL_Row > 15)
                                || ((Obstruction_L_EdgeL_Row < 55 && Obstruction_L_EdgeL_Row >= 30) && Obstruction_L_EdgeH_Row - Obstruction_L_EdgeL_Row > 6))
                                 && (((Obstruction_L_EdgeL_Row < 30) && Obstruction_L_EdgeL_Rank - Obstruction_L_EdgeR_Rank > 18)//障碍宽度条件
                                || ((Obstruction_L_EdgeL_Row < 55 && Obstruction_L_EdgeL_Row >= 30) && Obstruction_L_EdgeL_Rank - Obstruction_L_EdgeR_Rank > 8))
                                )
                            {
                                Obstruction_L = 1;
                                if (Obstruction_Lin_cnt < 2)
                                    Obstruction_Lin_cnt++;
                            }

                        }

                        //右障碍
                        for (i = 0, j = 0, e = 0; i < temporary; i++)
                        {
                            if ((L_black[i] - R_black[i] <= fixValue[i] + 15) && P_Pixels[i][(R_black[i] + LCenter[i]) >> 1] == 0)
                            {
                                j += 1;
                                e = 0;
                            }
                            else if (j < 6)
                            {
                                if (e == 1)
                                    j = 0;
                                e = 1;
                            }
                            if (j == 6)
                            {
                                Obstruction_R_EdgeL_Row = Obstruction_R_EdgeH_Row = i;
                            }
                            //    break;
                            //if (R_black[i] - R_black[i + 1] > 5 || L_black[i + 1] - L_black[i] > 5)
                            //    break;
                            if (R_black[i + 1] - R_black[i] > 15 && i < 20)
                            {
                                j = 0;
                                break;
                            }
                        }
                        // //用户自定义("右j" + j + " temporary " + temporary + "i" + i);

                        if (j > 6)
                        {
                            Obstruction_R_EdgeR_Rank = Obstruction_R_EdgeL_Rank =
                                (byte)((R_black[Obstruction_R_EdgeH_Row] + LCenter[Obstruction_R_EdgeH_Row]) >> 1);
                            //左边缘
                            for (i = Obstruction_R_EdgeL_Rank; i < (Obstruction_R_EdgeL_Rank + 15) && i < 199; i++)
                            {
                                if (P_Pixels[Obstruction_R_EdgeL_Row][i] > 0 || i >= L_black[Obstruction_R_EdgeL_Row])
                                    break;
                            }
                            Obstruction_R_EdgeL_Rank = i;
                            for (i = Obstruction_R_EdgeR_Rank; i > (Obstruction_R_EdgeR_Rank - 15) && i > 0; i--)
                            {
                                if (P_Pixels[Obstruction_R_EdgeL_Row][i] > 0 || i <= R_black[Obstruction_R_EdgeL_Row])
                                    break;
                            }
                            Obstruction_R_EdgeR_Rank = i;

                            j = (byte)((Obstruction_R_EdgeR_Rank + Obstruction_R_EdgeL_Rank) >> 1);
                            //上边缘行
                            for (i = Obstruction_R_EdgeH_Row; i < (Obstruction_R_EdgeH_Row + 30) && i < cutline; i++)
                            {
                                if (P_Pixels[i][j] > 0)
                                    break;
                            }
                            Obstruction_R_EdgeH_Row = i;
                            for (i = Obstruction_R_EdgeL_Row; i > (Obstruction_R_EdgeL_Row - 15) && i > 0; i--)
                            {
                                if (P_Pixels[i][j] > 0)
                                    break;
                            }
                            Obstruction_R_EdgeL_Row = i;
                            Obstruction_R_Mid_Row = (byte)((Obstruction_R_EdgeH_Row + Obstruction_R_EdgeL_Row) >> 1);

                            if (
                                Obstruction_R_EdgeL_Row - Obstruction_R_EdgeL_Row < 42
                                 && ((Obstruction_R_EdgeL_Row < 2 && Obstruction_R_EdgeH_Row - Obstruction_R_EdgeL_Row > 6)//障碍高度条件
                                || ((Obstruction_R_EdgeL_Row < 30 && Obstruction_R_EdgeL_Row >= 2) && Obstruction_R_EdgeH_Row - Obstruction_R_EdgeL_Row > 15)
                                || ((Obstruction_R_EdgeL_Row < 55 && Obstruction_R_EdgeL_Row >= 30) && Obstruction_R_EdgeH_Row - Obstruction_R_EdgeL_Row > 6))
                                 && (((Obstruction_R_EdgeL_Row < 30) && Obstruction_R_EdgeL_Rank - Obstruction_R_EdgeR_Rank > 18)//障碍宽度条件  有时候障碍会有跳变
                                || ((Obstruction_R_EdgeL_Row < 55 && Obstruction_R_EdgeL_Row >= 30) && Obstruction_R_EdgeL_Rank - Obstruction_R_EdgeR_Rank > 8))
                                )
                            {
                                Obstruction_R = 1;
                                if (Obstruction_Rin_cnt < 2)
                                    Obstruction_Rin_cnt++;
                            }

                        }

                        //障碍特殊情况 连续障碍先补近处的障碍
                        if (Obstruction_L > 0 && Obstruction_R > 0)
                        {
                            if (Obstruction_L_EdgeL_Row > Obstruction_R_EdgeL_Row)
                            {
                                Obstruction_L = 0;
                            }
                            else
                                Obstruction_R = 0;
                        }
                        if (Obstruction_L == 0)
                            Obstruction_Lin_cnt = 0;
                        if (Obstruction_R == 0)
                            Obstruction_Rin_cnt = 0;
                        if (Obstruction_Lin_cnt >= 2)
                        {
                            Obstruction_LState = 1;
                        }
                        if (Obstruction_Rin_cnt >= 2)
                        {
                            Obstruction_RState = 1;
                        }


                    }

                    if (Obstruction_LState == 1 || Obstruction_RState == 1)//障碍状态1 到第0行宽度变小之前
                    {
                        if (Obstruction_LState == 1)
                        {
                            Obstruction_L_Wan = 0;
                            if (Obstruction_0lastwide < fixValue[0] + 10 && Obstruction_0lastwide - Obstruction_0wide > 10 && Obstruction_0wide < fixValue[0] - 15)
                                Obstruction_LState = 2;
                            ///障碍状态中仍然要满足  赛道中间有黑色的条件
                            if (Obstruction_LState == 1)
                            {
                                for (i = 0, j = 0; i < temporary; i++)
                                {
                                    if ((L_black[i] - R_black[i] <= fixValue[i] + 10) && P_Pixels[i][(L_black[i] + LCenter[i]) >> 1] == 0)
                                        j += 1;

                                    if (j == 6)
                                    {
                                        Obstruction_L_EdgeL_Row = Obstruction_L_EdgeH_Row = i;
                                    }
                                    if (R_black[i] - R_black[i + 1] > 5 || L_black[i + 1] - L_black[i] > 5
                                        )
                                    {
                                        break;
                                    }
                                    if (L_black[i] - L_black[i + 1] > 15 && i < 20)
                                    {
                                        j = 0;
                                        break;
                                    }

                                }
                                if (R_black[0] < 4 && L_black[10] - L_black[0] < -10)//弯道接障碍
                                    Obstruction_L_Wan = 1;
                                //障碍补线  平移中线 左障碍
                                if (Obstruction_LState == 1)
                                {
                                    if (L_black[0] - R_black[0] < fixValue[0] + 10)
                                    {
                                        if (Obstruction_L_Wan == 1)
                                        {
                                            for (i = 0; i < cutline; i++)
                                            {
                                                LCenter[i] = (byte)Check_Overrun199(L_black[i] - fixValue[i] * 2 / 3);
                                            }
                                        }
                                        else
                                        {
                                            for (i = 0; i < cutline; i++)
                                            {
                                                LCenter[i] = (byte)Check_Overrun199(R_black[i] + fixValue[i] / 3);
                                            }
                                        }
                                    }
                                    else
                                    {
                                        for (i = 0; i < cutline; i++)
                                        {
                                            LCenter[i] = (byte)Check_Overrun199(R_black[i] + (L_black[i] - R_black[i]) / 3);
                                        }
                                    }
                                }
                            }

                        }
                        if (Obstruction_RState == 1)//右障碍
                        {
                            Obstruction_R_Wan = 0;
                            if (Obstruction_0lastwide < fixValue[0] + 10 && Obstruction_0lastwide - Obstruction_0wide > 10 && Obstruction_0wide < fixValue[0] - 15)
                                Obstruction_RState = 2;
                            if (Obstruction_RState == 1)
                            {
                                for (i = 0, j = 0; i < temporary; i++)
                                {
                                    if ((L_black[i] - R_black[i] <= fixValue[i] + 10) && P_Pixels[i][(R_black[i] + LCenter[i]) >> 1] == 0)
                                        j += 1;
                                    if (j == 6)
                                    {
                                        Obstruction_R_EdgeL_Row = Obstruction_R_EdgeH_Row = i;
                                    }
                                    //    break;
                                    if (R_black[i] - R_black[i + 1] > 5 || L_black[i + 1] - L_black[i] > 5)
                                        break;
                                    if (R_black[i + 1] - R_black[i] > 15 && i < 20)
                                    {
                                        j = 0;
                                        break;
                                    }
                                }

                                //if (j < 6)//不满足6个黑色点清除障碍标志
                                //    Obstruction_RState = 0;
                                if (L_black[0] > 196 && R_black[10] - R_black[0] > 10)
                                    Obstruction_R_Wan = 1;

                                //障碍补线  平移中线 右障碍
                                if (Obstruction_RState == 1)//第一行宽度宽不平移，，颠簸接障碍的情况
                                {
                                    if (L_black[0] - R_black[0] < fixValue[0] + 10)
                                    {
                                        if (Obstruction_R_Wan == 1)
                                        {
                                            for (i = 0; i < cutline; i++)
                                            {
                                                LCenter[i] = (byte)Check_Overrun199(R_black[i] + fixValue[i] * 2 / 3);
                                            }
                                        }
                                        else
                                        {
                                            for (i = 0; i < cutline; i++)
                                            {
                                                LCenter[i] = (byte)Check_Overrun199(L_black[i] - fixValue[i] / 3);
                                            }

                                        }
                                    }
                                    else
                                    {
                                        //  //用户自定义("有障碍 平i中线了啊");
                                        for (i = 0; i < cutline; i++)
                                        {
                                            LCenter[i] = (byte)Check_Overrun199(L_black[i] - (L_black[i] - R_black[i]) / 3);
                                        }
                                    }
                                }
                            }
                        }
                    }

                    if (Obstruction_LState == 2 || Obstruction_RState == 2)//障碍状态2 到出障碍之前
                    {
                        if (Obstruction_LState == 2)
                        {
                            if (Obstruction_0wide - Obstruction_0lastwide > 5 && Obstruction_0wide > fixValue[0] - 10)
                            {
                                Obstruction_LState = 0;
                                Obstruction_Lout_cnt = 11;

                            }
                            if (Obstruction_LState == 2 && Obstruction_0wide > fixValue[0] - 5)
                            {
                                Obstruction_LState = 0;
                            }
                            //障碍补线  平移中线 左障碍
                            if (Obstruction_LState == 2)
                            {
                                for (i = 0; i < cutline; i++)
                                {
                                    LCenter[i] = (byte)Check_Overrun199(R_black[i] + fixValue[i] / 3);
                                }
                            }
                        }
                        if (Obstruction_RState == 2)//右障碍
                        {
                            if (Obstruction_0wide - Obstruction_0lastwide > 5 && Obstruction_0wide > fixValue[0] - 5)
                            {
                                Obstruction_RState = 0;
                                Obstruction_Rout_cnt = 11;
                            }
                            if (Obstruction_RState == 2 && Obstruction_0wide > fixValue[0] - 5)
                                Obstruction_RState = 0;

                            //障碍补线  平移中线 右障碍
                            if (Obstruction_RState == 2)
                            {
                                for (i = 0; i < cutline; i++)
                                {
                                    LCenter[i] = (byte)Check_Overrun199(L_black[i] - fixValue[i] / 3);
                                }
                            }
                        }

                    }
                    Obstruction_0lastwide = Obstruction_0wide;
                }
                else
                {
                    Obstruction_LState = Obstruction_RState = 0;
                }

            }
            if (Obstruction_Lout_cnt > 0)
                Obstruction_Lout_cnt--;
            if (Obstruction_Rout_cnt > 0)
                Obstruction_Rout_cnt--;

            //出障碍 平移边线 10场  截断行小于50会清除
            if (Obstruction_Lout_cnt > 0 && cutline > 50)
            {
                for (i = 0; i < cutline; i++)
                {
                    LCenter[i] = (byte)Check_Overrun199(R_black[i] + fixValue[i] / 3);
                }
            }
            else
                Obstruction_Lout_cnt = 0;
            if (Obstruction_Rout_cnt > 0 && cutline > 50)
            {

                for (i = 0; i < cutline; i++)
                {
                    LCenter[i] = (byte)Check_Overrun199(L_black[i] - fixValue[i] / 3);
                }
            }
            else
                Obstruction_Rout_cnt = 0;

            //
        
            if (Obstruction_LState > 0 || Obstruction_RState > 0 || Obstruction_Lout_cnt > 0 || Obstruction_Rout_cnt > 0)
            {
                blockflag = 1;
            }
            else
                blockflag = 0;

            Get_lineeffect();
            R_Big = R_black[0];
            L_Small = L_black[0];
            for (i = 0; i <= 55; i++)
            {
                if (L_black[i] < L_Small)
                    L_Small = L_black[i];
                if (R_black[i] > R_Big)
                    R_Big = R_black[i];
            }
            //中S小S共用的 中线趋势判断 
            if (smallsflag == 0)
            {
                a = b = c = d = 0;
                Small_SWanState = Small_SWanState2 = 0;
                for (i = 1; i < cutline; i++)
                {
                    //S弯形状1
                    if (Small_SWanState == 0 && LCenter[i] > LCenter[i - 1])
                    {
                        a++;
                    }
                    if (Small_SWanState == 0 && a > 3 && LCenter[i] < LCenter[i - 1])
                    {
                        b++;
                    }
                    if (b >= 3 && Small_SWanState == 0)
                    {
                        S_HangL_1 = (byte)(i - 3);
                        Small_SWanState = 1;
                        a = b = 0;
                    }
                    if (Small_SWanState == 1 && LCenter[i] < LCenter[i - 1])
                        a++;
                    if (Small_SWanState == 1 && a > 3 && LCenter[i] > LCenter[i - 1])
                        b++;
                    if (b >= 3 && Small_SWanState == 1)
                    {
                        S_HangL_2 = (byte)(i - 3);
                        a = b = 0;
                        Small_SWanState = 2;
                        break;
                    }

                    ///形状2
                    if (Small_SWanState2 == 0 && LCenter[i] < LCenter[i - 1])
                    {
                        c++;
                    }
                    if (Small_SWanState2 == 0 && c > 3 && LCenter[i] > LCenter[i - 1])
                        d++;
                    if (d >= 3 && Small_SWanState2 == 0)
                    {
                        S_HangR_1 = (byte)(i - 3);
                        Small_SWanState2 = 1;
                        c = d = 0;
                    }
                    if (Small_SWanState2 == 1 && LCenter[i] > LCenter[i - 1])
                        c++;
                    if (Small_SWanState2 == 1 && c > 3 && LCenter[i] < LCenter[i - 1])
                        d++;
                    if (d >= 3 && Small_SWanState2 == 1)
                    {
                        S_HangR_2 = (byte)(i - 3);
                        c = d = 0;
                        Small_SWanState2 = 2;
                        break;
                    }

                    if (L_black[i] - L_black[i - 1] >= 10 || R_black[i - 1] - R_black[i] >= 10)
                        Small_SWanState = Small_SWanState2 = 0;

                    if (Small_SWanState == 2 || Small_SWanState2 == 2)
                        break;
                }
                S_wide_center1 = (LCenter[S_HangL_1] - LCenter[S_HangL_2]);
                S_wide_center2 = (LCenter[S_HangR_1] - LCenter[S_HangR_2]);
                S_wide_lblack1 = (L_black[S_HangL_1] - L_black[S_HangL_2]);
                S_wide_lblack2 = (L_black[S_HangR_1] - L_black[S_HangR_2]);
                S_wide_rblack1 = (R_black[S_HangL_1] - R_black[S_HangL_2]);
                S_wide_rblack2 = (R_black[S_HangR_1] - R_black[S_HangR_2]);




                /**********************小S*********************/
                if (poflag == 0 && crossflag == 0 && huandaoflag == 0 && blockflag == 0 && smallsflag == 0)
                {
                    if (cutline > 60 && smallsflag == 0 && crossflag == 0)
                    {
                        temp = 0;
                        for (i = 0; i < cutline; i++)
                        {
                            if (i < 50)
                            {
                                if (LCenter[60] < L_black[i] && LCenter[60] > R_black[i])
                                {
                                    temp++;
                                }
                                else
                                {
                                    smallsflag = 0;
                                    break;
                                }
                            }
                        }
                        if (temp >= 45 && line_effet < 34)
                        {


                            //前40行平均值 
                            temp = 0;
                            for (i = 0; i < 40; i++)
                                temp += LCenter[i];
                            temp = temp / 40;
                            // //用户自定义("temp" + temp);
                            //小S弯标志

                            if ((Small_SWanState == 2)
                                && (L_Small - R_Big > 26)
                                && (temp > 50 && temp < 150)//中线差不多摆正
                                && fab1(S_wide_center1) < 28 && fab1(S_wide_center1) > 5
                                //&& (S_wide_center1 > 5 || S_wide_center1 < -5)//也不能距离太小
                                && S_HangL_2 < 69)//最后一个条件有问题取巧，，防止误判大S
                            {
                                //  //用户自定义("判断小S1 高行 " + S_HangL_2 + " 低行 " + S_HangL_1 + " 中线差 " + S_wide_center1 + " " + (L_Small - R_Big));
                                smallsflag = 1;
                            }
                            else if ((Small_SWanState2 == 2)
                                && L_Small - R_Big > 26
                           && (temp > 50 && temp < 150)//中线差不多摆正
                                && fab1(S_wide_center2) < 28 && fab1(S_wide_center2) > 5
                                //&& (S_wide_center2 >= -30) && (S_wide_center2 <= 30)
                                //&& (S_wide_center2 > 5 || S_wide_center2 < -5)
                                && S_HangR_2 < 65)
                            {
                                //   //用户自定义("判断小S2 高行 " + S_HangR_2 + " 低行 " + S_HangR_1 + " 中线差 " + S_wide_center2 + " " + (L_Small - R_Big));
                                smallsflag = 1;
                            }

                        }
                    }
                }
            }
            if (smallsflag == 1)//清除小S
            {
                temp = 0;
                //学长的清除flag方法
                for (i = 0; i < cutline - 5 && i <= 50; i++)//遇到弯道
                {
                    if (L_black[i] != 199 && L_black[i + 1] == 199 && L_black[i + 1] - L_black[i] > 5)//清除拐点形跳变
                    {
                        //用户自定义("1");
                        smallsflag = 0;
                        break;
                    }
                    if (R_black[i] != 0 && R_black[i + 1] == 0 && R_black[i] - R_black[i + 1] > 5)
                    {
                        //用户自定义("2");
                        smallsflag = 0;
                        break;
                    }
                    if (L_black[i] > 195 && L_black[i + 1] - L_black[i] < -10)//出环岛形跳变
                    {
                        smallsflag = 0;
                        break;
                    }
                    if (R_black[i] < 5 && R_black[i + 1] - R_black[i] > 10)
                    {
                        smallsflag = 0;
                        break;
                    }

                }

                if (turnflag == 1 || crossflag == 1 || crossflag == 1 || huandaoflag == 1 || poflag != 0 || blockflag == 1 || L_black[0] - R_black[0] > fixValue[0] + 20 || L_black[8] - R_black[8] > fixValue[8] + 20)
                {
                    //用户自定义("学长的 小S清除");
                    smallsflag = 0;
                }

                ///我的清除flag方法
                if (
                    (line_effet != 0 && line_effet > 45) || cutline < 55 || (L_Small - R_Big < 30)
                  )
                {
                    //if (Small_SWanState != 2 && Small_SWanState2 != 2)
                    //用户自定义("无前60行最小宽度 小S清除");
                    smallsflag = 0;
                }
                //遇到连弯或者弯道也清除标志
                else
                {
                    for (i = 0; i < cutline && i < 55; i++)
                    {
                        if (LCenter[i] < 20 || LCenter[i] > 180)
                        {
                            smallsflag = 0;
                            //用户自定义("连弯 小S清除");

                            break;
                        }
                    }
                }

            }
            //if (Small_SWanState == 2)
            //{
            //    //用户自定义(" 11enter1 " + S_wide_center1 + "  lblack1 " + S_wide_lblack1 + "  rblack1 " + S_wide_rblack1 + "宽度" + (L_Small - R_Big));
            //    //用户自定义("S_HangL_1 " + S_HangL_1 + " S_HangL_2 " + S_HangL_2);
            //}
            //if (Small_SWanState2 == 2)
            //{
            //    //用户自定义(" 22enter " + S_wide_center2 + "  black2 " + S_wide_lblack2 + "  rblack2 " + S_wide_rblack2 + " 宽度 " + " " + (L_Small - R_Big));
            //    //用户自定义("S_HangR_1 " + S_HangR_1 + " S_HangR_2 " + S_HangR_2);
            //}
            /****************中S*************************/
            if (door(30, 45) == 1 && poflag == 0 && crossflag == 0 && huandaoflag == 0 && blockflag == 0 && smallsflag == 0)
            {
                if (Mid_S_Switch == 1 && crossflag == 0 && huandaoflag == 0 && poflag == 0)
                {

                    if (
                        Small_SWanState == 2 &&
                  fab1(S_wide_center1) > 30 && fab1(S_wide_center1) < 80 &&
                  fabss(LCenter[S_HangL_2], LCenter[0]) < 80 &&
                 (L_Small - R_Big) < 20 &&
                   (S_HangL_2 - S_HangL_1 > 10 && S_HangL_2 - S_HangL_1 < 50)
                       )
                    {
                        bigsflag = 1;
                        //用户自定义("大S11 ");

                    }
                    else
                        if (
                   Small_SWanState2 == 2 &&
                   fab1(S_wide_center2) > 30 && fab1(S_wide_center2) < 80 &&
                   (L_Small - R_Big) < 20 &&
                 fabss(LCenter[S_HangR_2], LCenter[0]) < 80 &&
                (S_HangR_2 - S_HangR_1 > 10 && S_HangR_2 - S_HangR_1 < 50)
                         )
                    {
                        bigsflag = 1;
                        //用户自定义("大S22 ");
                    }
                }
            }

            /****************连弯***********************/
            if (poflag == 0 && crossflag == 0 && huandaoflag == 0 && blockflag == 0 && smallsflag == 0)
            {
                ////用户自定义("111 line_effet " + line_effet);
                //条件1 弯道有效行比较低 说明有中线有弯折
                if (line_effet < 38 && cutline > 50)
                {

                    Curve_Lianwan_LCnt = Curve_Lianwan_RCnt = 0;
                    for (i = 0; i < 20; i++)
                    {
                        if (LCenter[i + 2] > LCenter[i])
                            Curve_Lianwan_LCnt++;
                        if (LCenter[i + 2] < LCenter[i])
                            Curve_Lianwan_RCnt++;
                    }

                    //左-右连弯
                    if (Curve_Lianwan_LCnt > 10)
                    {

                        Curve_Lianwan_L_pingyi = 0;
                        Curve_Lianwan_LCnt = Curve_Lianwan_RCnt = 0;

                        Curve_Lianwan_L_Row = 0;
                        for (i = 10; i < cutline && i < 55; i++)
                        {
                            if (R_black[i] < R_black[i - 2] || LCenter[i] < LCenter[i - 2])//有的弯道弯曲程度不够就用中线判断道路趋势
                                Curve_Lianwan_RCnt++;
                            if (Curve_Lianwan_RCnt > 3)
                            {
                                Curve_Lianwan_L_Row = (byte)(i - 4);
                                break;
                            }
                        }
                        if (Curve_Lianwan_L_Row > 0)
                        {
                            Curve_Lianwan_L = 1;
                            //根据行数高低不同，根据宽度判断平移的条件也不同
                            if (Curve_Lianwan_L_Row > 40 && (L_black[Curve_Lianwan_L_Row] - R_black[Curve_Lianwan_L_Row]) < 38)
                                Curve_Lianwan_L_pingyi = 1;
                            else if (Curve_Lianwan_L_Row > 20 && (L_black[Curve_Lianwan_L_Row] - R_black[Curve_Lianwan_L_Row]) < 45)//中线平移判断  
                                Curve_Lianwan_L_pingyi = 1;
                            else if (Curve_Lianwan_L_Row > 0 && (L_black[Curve_Lianwan_L_Row] - R_black[Curve_Lianwan_L_Row]) < 50)//中线平移判断  
                                Curve_Lianwan_L_pingyi = 1;

                            LianWan_max_row = Curve_Lianwan_L_Row;
                            for (i = Curve_Lianwan_L_Row; i < cutline - 2 && i < Curve_Lianwan_L_Row + 35; i++)
                            {
                                if (L_black[i + 1] - L_black[i] > 18)
                                    break;
                                if (R_black[i] < R_black[LianWan_max_row])
                                {
                                    LianWan_max_row = i;
                                }
                            }

                            if (R_black[Curve_Lianwan_L_Row] - R_black[LianWan_max_row] > 60)
                            {
                                //if (Curve_Lianwan_L_pingyi == 1)//连弯处宽度
                                //{
                                LianWan_plevel_FlagL = 3;
                                //}
                                //else
                                //{
                                //    LianWan_plevel_FlagL = 2;
                                //}

                            }
                            else
                            {
                                if (Curve_Lianwan_L_pingyi == 1)
                                {
                                    LianWan_plevel_FlagL = 3;
                                }
                                else
                                {
                                    LianWan_plevel_FlagL = 3;
                                }

                            }
                        }

                    }
                    //右左连弯
                    else if (Curve_Lianwan_RCnt > 10)
                    {
                        Curve_Lianwan_R_pingyi = 0;
                        Curve_Lianwan_LCnt = Curve_Lianwan_RCnt = 0;
                        Curve_Lianwan_R_Row = 0;
                        for (i = 10; i < cutline && i < 55; i++)
                        {
                            if (L_black[i] > L_black[i - 2] || LCenter[i] > LCenter[i - 2])
                                Curve_Lianwan_LCnt++;
                            if (Curve_Lianwan_LCnt > 3)
                            {
                                Curve_Lianwan_R_Row = (byte)(i - 4);
                                break;
                            }
                        }
                        if (Curve_Lianwan_R_Row > 0)
                        {

                            Curve_Lianwan_R = 1;
                            //根据行数高低不同，根据宽度判断平移的条件也不同
                            if (Curve_Lianwan_R_Row > 40 && (L_black[Curve_Lianwan_R_Row] - R_black[Curve_Lianwan_R_Row]) < 38)
                                Curve_Lianwan_R_pingyi = 1;
                            else if (Curve_Lianwan_R_Row > 20 && (L_black[Curve_Lianwan_R_Row] - R_black[Curve_Lianwan_R_Row]) < 45)//中线平移判断  
                                Curve_Lianwan_R_pingyi = 1;
                            else if (Curve_Lianwan_R_Row > 0 && (L_black[Curve_Lianwan_R_Row] - R_black[Curve_Lianwan_R_Row]) < 50)//中线平移判断  
                                Curve_Lianwan_R_pingyi = 1;

                            LianWan_max_row = Curve_Lianwan_R_Row;
                            for (i = Curve_Lianwan_R_Row; i < cutline - 2 && i < Curve_Lianwan_R_Row + 35; i++)
                            {
                                if (R_black[i + 1] - R_black[i] < -18)
                                    break;
                                if (L_black[i] > L_black[LianWan_max_row])
                                {
                                    LianWan_max_row = i;
                                }
                            }
                            if (L_black[LianWan_max_row] - L_black[Curve_Lianwan_R_Row] > 60)
                            {
                                //if (Curve_Lianwan_R_pingyi == 1)
                                //{
                                LianWan_plevel_FlagR = 3;
                                //}
                                //else
                                //{
                                //    LianWan_plevel_FlagR = 2;
                                //}
                            }
                            else
                            {
                                if (Curve_Lianwan_R_pingyi == 1)
                                {

                                    LianWan_plevel_FlagR = 3;
                                }
                                else
                                {

                                    LianWan_plevel_FlagR = 3;
                                }

                            }

                        }
                    }

                }
            }
            if (Curve_Lianwan_R == 1)
            {
                //用户自定义(" 右连弯 连弯级别" + LianWan_plevel_FlagR + "/3");

            }
            else if (Curve_Lianwan_L == 1)
            {
                //用户自定义(" 左连弯 连弯级别" + LianWan_plevel_FlagL + "/3");

            }
            /****************修补叉路突然跳变判断**************/
            if (huandaoflag == 0 && poflag == 0 && smallsflag == 0 && blockflag == 0 && cutline > 40)
            {
                //左岔路
                if (Shizila_flagL == 0)
                {
                    for (i = 0; i < 20; i++)
                    {
                        if (P_Pixels[i][199] > 0 && P_Pixels[i + 2][199] > 0 && P_Pixels[i + 4][199] > 0 && L_black[i + 1] == 199 && L_black[i + 4] == 199)
                        {
                            Lwhitezhi = i;
                            break;
                        }
                        if (i == 19)
                        {
                            Lwhitezhi = 20;
                        }

                    }
                    if (Lwhitezhi != 20)
                    {
                        for (i = Lwhitezhi; i < 50; i++)
                        {
                            if (L_black[i] != 199 && i > 0)
                            {
                                zuotuchu = (byte)(i - 1);
                                break;
                            }
                            if (i == 49)
                            {
                                zuotuchu = 0;
                            }
                        }
                    }
                    if (zuotuchu != 0 && P_Pixels[zuotuchu + 1][199] == 0 && P_Pixels[zuotuchu + 2][198] == 0 && R_black[zuotuchu + 2] < 196 && L_black[zuotuchu] - L_black[zuotuchu + 2] > 5)
                    {
                        zuotiaobian = L_black[zuotuchu + 1];
                    }
                    if (zuotiaobian != 0 && L_black[zuotuchu + 10] != 199)
                    {
                        Lxflag = 1;
                        temp = 0;
                        j = 0;
                        for (i = Lwhitezhi; i < cutline; i++)
                        {
                            if (P_Pixels[i][199] == 0)
                            {
                                temp = i;
                                break;
                            }
                        }
                        for (i = Lwhitezhi; i < cutline; i++)
                        {
                            if (P_Pixels[i][194] == 0)
                            {
                                j = i;
                                break;
                            }
                        }
                        if (temp > j)
                        {
                            CLxflag = 1;
                        }

                    }
                }
                //右岔路
                if (Shizila_flagR == 0)
                {
                    for (i = 0; i < 20; i++)
                    {
                        if (P_Pixels[i][0] > 0 && P_Pixels[i + 2][0] > 0 && P_Pixels[i + 4][0] > 0 && R_black[i + 1] == 0 && R_black[i + 4] == 0)
                        {
                            Rwhitezhi = i;
                            break;
                        }
                        if (i == 19)
                        {
                            Rwhitezhi = 20;
                        }

                    }
                    if (Rwhitezhi != 20)
                    {
                        for (i = Rwhitezhi; i < 50; i++)
                        {
                            if (R_black[i] != 0 && i > 0)
                            {
                                youtuchu = (byte)(i - 1);   //白的
                                break;
                            }
                            if (i == 49)
                            {
                                youtuchu = 0;
                            }
                        }
                    }
                    if (youtuchu != 0 && P_Pixels[youtuchu + 1][0] == 0 && P_Pixels[youtuchu + 2][1] == 0 && L_black[youtuchu + 2] > 3 && R_black[youtuchu + 2] - R_black[youtuchu] > 5)
                    {
                        youtiaobian = R_black[youtuchu + 1];
                    }
                    if (youtiaobian != 0 && R_black[youtuchu + 10] != 0)
                    {
                        Rxflag = 1;
                        temp = 0;
                        j = 0;
                        for (i = Rwhitezhi; i < cutline; i++)
                        {
                            if (P_Pixels[i][0] == 0)
                            {
                                temp = i;
                                break;
                            }
                        }
                        for (i = Rwhitezhi; i < cutline; i++)
                        {
                            if (P_Pixels[i][5] == 0)
                            {
                                j = i;
                                break;
                            }
                        }
                        if (temp > j)
                        {
                            CRxflag = 1;
                        }

                    }
                }
            }
            if (huandaogeshu == 2 && (huandao_type[0] == 3 || huandao_type[0] == 4))
            {
                huanchucnt = 40;
            }
            else if (huandaogeshu == 4 && (huandao_type[1] == 3 || huandao_type[1] == 4))
            {
                huanchucnt = 40;
            }
            else if (huandaogeshu == 6 && (huandao_type[2] == 3 || huandao_type[2] == 4))
            {
                huanchucnt = 40;
            }
            else if (huandaogeshu == 8 && (huandao_type[3] == 3 || huandao_type[3] == 4))
            {
                huanchucnt = 40;
            }
            else
            {
                huanchucnt = 20;
            }
           
            if (huandaogeshu % 2 == 0)
            {
                chalucnt = 1;
                //用户自定义("ssssssssssssss");
            }
            if (huandaoflag == 0)
            {
                if (chalucnt < huanchucnt && chalucnt > 0)
                {
                    chalucnt++;
                    jumpmem = jumppot;
                    if (huandaofangxiang == 2 && Lxflag == 0)
                    {
                        for (i = 0; i < 60; i++)
                        {
                            if (L_black[i] - L_black[i + 1] > 10 && fabss(L_black[i + 1], L_black[i + 2]) < 3 && fabss(L_black[i + 2], L_black[i + 3]) < 3)
                            {
                               
                                jumppot = i;
                                break;
                            }
                            if (i == 59)
                            {
                                jumppot = 0;
                            }
                        }

                        if (jumppot > 5)
                        {

                            if (L_black[0] > 190)
                            {
                                for (i = 0; i < jumppot + 3; i++)
                                {
                                    L_black[i] = (byte)(L_black[jumppot + 2] + (jumppot + 2 - i) * (double)(L_black[jumppot + 2] - L_black[jumppot + 6]) / 4);
                                    if (L_black[jumppot + 2] + (jumppot + 2 - i) * (double)(L_black[jumppot + 2] - L_black[jumppot + 6]) / 4 > 199)
                                    {
                                        L_black[i] = 199;
                                    }
                                    if (L_black[jumppot + 2] + (jumppot + 2 - i) * (double)(L_black[jumppot + 2] - L_black[jumppot + 6]) / 4 < 1)
                                    {
                                        L_black[i] = 0;
                                    }
                                }
                            }
                            else
                            {
                                for (i = 0; i < jumppot + 3; i++)
                                {
                                    L_black[i] = (byte)(L_black[jumppot + 2] + (jumppot + 2 - i) * (double)(L_black[0] - L_black[jumppot + 2]) / (jumppot + 2));
                                    if (L_black[jumppot + 2] + (jumppot + 2 - i) * (double)(L_black[0] - L_black[jumppot + 2]) / (jumppot + 2) > 199)
                                    {
                                        L_black[i] = 199;
                                    }
                                    if (L_black[jumppot + 2] + (jumppot + 2 - i) * (double)(L_black[0] - L_black[jumppot + 2]) / (jumppot + 2) < 1)
                                    {
                                        L_black[i] = 0;
                                    }
                                }
                            }
                        }
                    }
                    if (huandaofangxiang == 1 && Rxflag == 0)
                    {
                        //用户自定义("aaaaaaa11111111111");
                        for (i = 0; i < 60; i++)
                        {
                            if (R_black[i + 1] - R_black[i] > 10 && fabss(R_black[i + 1], R_black[i + 2]) < 3 && fabss(R_black[i + 2], R_black[i + 3]) < 3)
                            {
                                jumppot = i;
                                break;
                            }
                            if (i == 59)
                            {
                                jumppot = 0;
                            }
                        }
                        if (jumppot > 5)
                        {
                            //用户自定义("aaaaaaa222222222222");
                            if (R_black[0] < 10)
                            {
                                for (i = 0; i < jumppot + 3; i++)
                                {
                                    R_black[i] = (byte)(R_black[jumppot + 2] - (jumppot + 2 - i) * (double)(R_black[jumppot + 6] - R_black[jumppot + 2]) / 4);
                                    if (R_black[jumppot + 2] - (jumppot + 2 - i) * (double)(R_black[jumppot + 6] - R_black[jumppot + 2]) / 4 < 1)
                                    {
                                        R_black[i] = 0;
                                    }
                                    if (R_black[jumppot + 2] - (jumppot + 2 - i) * (double)(R_black[jumppot + 6] - R_black[jumppot + 2]) / 4 > 198)
                                    {
                                        R_black[i] = 199;
                                    }
                                }
                            }
                            else
                            {
                                for (i = 0; i < jumppot + 3; i++)
                                {
                                    R_black[i] = (byte)(R_black[jumppot + 2] - (jumppot + 2 - i) * (double)(R_black[jumppot + 2] - R_black[0]) / (jumppot + 2));
                                    if (R_black[jumppot + 2] - (jumppot + 2 - i) * (double)(R_black[jumppot + 2] - R_black[0]) / (jumppot + 2) < 1)
                                    {
                                        R_black[i] = 0;
                                    }
                                    if (R_black[jumppot + 2] - (jumppot + 2 - i) * (double)(R_black[jumppot + 2] - R_black[0]) / (jumppot + 2) > 198)
                                    {
                                        R_black[i] = 199;
                                    }
                                }
                            }
                        }
                    }
                    if ( chalucnt == huanchucnt - 1||(jumpmem!=0&&jumppot>jumpmem+5))
                    {
                        chalucnt = 0;
                        jumpmem = 0;
                        jumppot = 0;
                    }
                }
                if (Lxflag == 1)
                {
                    //用户自定义("左叉路");
                    for (i = 0; i < zuotuchu + 3; i++)
                    {
                        L_black[i] = (byte)(L_black[zuotuchu + 3] - (double)(L_black[zuotuchu + 10] - L_black[zuotuchu + 3]) / 7 * (zuotuchu + 3 - i));
                        if (L_black[zuotuchu + 3] - (double)(L_black[zuotuchu + 10] - L_black[zuotuchu + 3]) / 7 * (zuotuchu + 3 - i) > 198)
                        {
                            L_black[i] = 199;
                        }
                        LCenter[i] = (byte)((L_black[i] + R_black[i]) / 2);
                    }
                }
                if (Rxflag == 1)
                {
                    //用户自定义("右叉路");
                    for (i = 0; i < youtuchu + 3; i++)
                    {
                        R_black[i] = (byte)(R_black[youtuchu + 3] - (double)(R_black[youtuchu + 10] - R_black[youtuchu + 3]) / 7 * (youtuchu + 3 - i));
                        if (R_black[youtuchu + 3] - (double)(R_black[youtuchu + 10] - R_black[youtuchu + 3]) / 7 * (youtuchu + 3 - i) < 1)
                        {
                            R_black[i] = 0;
                        }
                        LCenter[i] = (byte)((L_black[i] + R_black[i]) / 2);
                    }
                }
            }
            //用户自定义("tiaobiandian"+jumppot+jumpmem);
            kind();
            /**********中点补线*****************/
            if (blockflag != 1 && huandaoflag == 0)//障碍平移1/3 在判断后就平移
            {
                leftlost = 0;
                rightlost = 0;
                for (i = 0; i < 45; i++)
                {
                    if (L_black[i] == 199)
                    {
                        leftlost++;
                    }
                    if (R_black[i] == 0)
                    {
                        rightlost++;
                    }
                }

                if (cutline < 45 || (smallsflag != 1 &&
                    (
                    (Curve_Lianwan_R == 1 && Curve_Lianwan_R_pingyi == 1) //右连弯 符合平移条件
                        || (Curve_Lianwan_L == 1 && Curve_Lianwan_L_pingyi == 1)//左连弯
                        || (Curve_Lianwan_R == 0 && Curve_Lianwan_L == 0 && (leftlost > 35 || rightlost > 35 || door(40, 20) == 0) && turnflag == 1)//首先不是连弯丢线 或者 20行宽度很小
                     || (crossflag == 1 && Cross_Pingyi == 1)
                        )
                    ))
                {


                    //用户自定义("中线平移");
                    for (RowNum = 0; RowNum < cutline; RowNum++)
                    {
                        if (RowNum == 0)
                        {
                            LCenter[RowNum] = (byte)((L_black[RowNum] + R_black[RowNum]) / 2);
                        }
                        else
                        {
                            if (L_black[RowNum] == 199 && R_black[RowNum] != 0)
                            {
                                LCenter[RowNum] = (byte)(LCenter[RowNum - 1] + R_black[RowNum] - R_black[RowNum - 1]);
                                if (LCenter[RowNum - 1] + R_black[RowNum] - R_black[RowNum - 1] > 198)
                                {
                                    LCenter[RowNum] = 199;
                                }
                                if (LCenter[RowNum - 1] + R_black[RowNum] - R_black[RowNum - 1] < 1)
                                {
                                    LCenter[RowNum] = 0;
                                }

                            }
                            else if (R_black[RowNum] == 0 && L_black[RowNum] != 199)
                            {
                                LCenter[RowNum] = (byte)(LCenter[RowNum - 1] + L_black[RowNum] - L_black[RowNum - 1]);
                                if (LCenter[RowNum - 1] + L_black[RowNum] - L_black[RowNum - 1] < 1)
                                {
                                    LCenter[RowNum] = 0;
                                }
                                if (LCenter[RowNum - 1] + L_black[RowNum] - L_black[RowNum - 1] > 198)
                                {
                                    LCenter[RowNum] = 199;
                                }
                            }
                            else
                            {
                                LCenter[RowNum] = (byte)((L_black[RowNum] + R_black[RowNum]) / 2);
                            }
                        }
                    }

                }
                else if (turnflag == 1 && bigsflag == 0)//判断成大S得时候不满足上一个判断时不能平移
                {
                    //用户自定义("turnflag 中线平移");
                    for (RowNum = 0; RowNum < cutline; RowNum++)
                    {
                        if (RowNum == 0)
                        {
                            LCenter[RowNum] = (byte)((L_black[RowNum] + R_black[RowNum]) / 2);
                        }
                        else
                        {
                            if (L_black[RowNum] == 199 && R_black[RowNum] != 0)
                            {
                                LCenter[RowNum] = (byte)(LCenter[RowNum - 1] + R_black[RowNum] - R_black[RowNum - 1]);
                                if (LCenter[RowNum - 1] + R_black[RowNum] - R_black[RowNum - 1] > 198)
                                {
                                    LCenter[RowNum] = 199;
                                }
                                if (LCenter[RowNum - 1] + R_black[RowNum] - R_black[RowNum - 1] < 1)
                                {
                                    LCenter[RowNum] = 0;
                                }

                            }
                            else if (R_black[RowNum] == 0 && L_black[RowNum] != 199)
                            {
                                LCenter[RowNum] = (byte)(LCenter[RowNum - 1] + L_black[RowNum] - L_black[RowNum - 1]);
                                if (LCenter[RowNum - 1] + L_black[RowNum] - L_black[RowNum - 1] < 1)
                                {
                                    LCenter[RowNum] = 0;
                                }
                                if (LCenter[RowNum - 1] + L_black[RowNum] - L_black[RowNum - 1] > 198)
                                {
                                    LCenter[RowNum] = 199;
                                }
                            }
                            else
                            {
                                LCenter[RowNum] = (byte)((L_black[RowNum] + R_black[RowNum]) / 2);
                            }
                        }
                    }

                }

                else
                {
                    //用户自定义("中线左加右");
                    for (i = 0; i < cutline; i++)
                    {
                        LCenter[i] = (byte)((L_black[i] + R_black[i]) / 2);
                    }
                }

            }
            if (poflag == 0 && crossflag == 0 && huandaoflag == 0 && blockflag == 0)
            {
                if (crossflag == 0 && blockflag == 0)
                {
                    for (i = 0; i < cutline - 3; i++)
                    {
                        if (fabss(LCenter[i], LCenter[i + 1]) >= 4)
                        {
                            changeflag = 1;
                            break;
                        }
                    }
                    if (changeflag == 1)
                    {
                        for (i = 1; i < cutline - 3; i++)
                        {

                            if (L_black[i] == 199 && L_black[i + 1] != 199 && L_black[i + 1] != 0 && L_black[i + 2] != 199 && L_black[i + 2] != 0 && L_black[i + 3] != 199 && L_black[i + 3] != 0)
                            {
                                changezuo = i;
                                bianhuanflag = 1;
                                break;

                            }
                            if (R_black[i] == 0 && R_black[i + 1] != 0 && R_black[i + 1] != 199 && R_black[i + 2] != 0 && R_black[i + 2] != 199 && R_black[i + 3] != 0 && R_black[i + 3] != 199)
                            {

                                bianhuanflag = 1;
                                changeyou = i;
                                break;
                            }
                        }
                    }

                    if (cutline >= 40 && bianhuanflag == 1)
                    {
                        for (j = 1; i < cutline; i++)
                        {
                            LCenter[j] = (uint8_t)((L_black[j] + R_black[j]) / 2);
                        }
                    }
                }
            }
            /*****************第1行中点记忆***************/
            center = LCenter[0];
            /*************防止突然没图***************/
            //没图是从100扫线
            if (L_black[5] == LCenter[5] && LCenter[5] == R_black[5] && L_black[10] == LCenter[10] && LCenter[10] == R_black[10] && L_black[20] == LCenter[20] && LCenter[20] == R_black[20] && L_black[30] == LCenter[30] && LCenter[30] == R_black[30] && L_black[65] == LCenter[65] && LCenter[65] == R_black[65])
            {
                center = 100;
            }
            if (LCenter[0] > 199 || LCenter[0] < 0)
            {
                center = 100;
            }
            //用户自定义("huandaogeshu" + huandaogeshu);
        }


				void kind()
        {
            //确定有效行（移动到场处理开始）   line_effet  应放在中线平移之前否则平移之后的跳变会导致 有效行误判  
            //而effect)line 在小S和连弯判断中还要用到 故放在他们前面
            /******************判断长直道*****************/
             // ////ion
            if (speed >= 800) //根据速度决定长直道行数
            { longstraightline = 69; }
            else if (speed >= 750)
            { longstraightline = 68; }
            else if (speed >= 720)
            { longstraightline = 67; }
            else if (speed >= 700)
            { longstraightline = 66; }
            else if (speed >= 680)
            { longstraightline = 65; }
            else if (speed >= 660)
            { longstraightline = 64; }
            else if (speed >= 640)
            { longstraightline = 63; }
            else if (speed >= 620)
            { longstraightline = 62; }
            else if (speed >= 600)
            { longstraightline = 61; }
            else if (speed <640)
            { longstraightline = 60; }
            if (cutline > longstraightline && L_black[0] - R_black[0] - fixValue[0] > -30)
            {
                leftmin = L_black[0];
                rightmax = R_black[0];
                leftmax = L_black[0];
                rightmin = R_black[0];
                for (i = 1; i <= (byte)(65 < cutline ? 65 : cutline); i++)
                {
                    if (L_black[i] - leftmin < 0)
                    { leftmin = L_black[i]; }
                    if (L_black[i] - leftmax > 0)
                    { leftmax = L_black[i]; }
                    if (R_black[i] - rightmin < 0)
                    { rightmin = R_black[i]; }
                    if (R_black[i] - rightmax > 0)
                    { rightmax = R_black[i]; }
                }
                //根据左右先范围判断长直道  
                //有效行条件:十字补线不好导致有效行会小于20 想让十字加速  同时防止直道接弯道又要限制有效行  范围确定为,20或者 大于50
                if (leftmin - rightmax >= 15 && leftmin > 60 && leftmin < 175 && rightmax > 25 && rightmax < 140 && leftmax - leftmin < 85 && rightmax - rightmin < 85
                    && (line_effet > longstraightline || line_effet < 20))
                {
                     // ////ion用户自定义("长直道直道111");
                    longstraightflag = 1;
                }
            }      //判断长直道
            if (K(line_effet, 0) < 1 && line_effet > longstraightline && L_black[0] - R_black[0] - fixValue[0] > -50)
            {
                 // ////ion用户自定义("直道222");
                longstraightflag = 1;
            }
            if (kjudge(longstraightline, 5) == 1 && fabss(LCenter[longstraightline], LCenter[longstraightline - 5]) < 7)
            {
                 // ////ion用户自定义("直道333");
                longstraightflag = 1;
            }
            if (longstraightflag == 1)
            {
                if (L_black[0] < 195 && R_black[0] > 5 && L_black[10] < 190 && R_black[10] > 10)
                {
                    longstraightflag = 1;
                }
                else
                {
                    longstraightflag = 0;
                    notstraightflag = 1;
                }
            }
            // ////ion    //判断长直道
            /*******************判断短直道*****************/
             // ////ion
            temp = 0;
            if (L_black[0] - R_black[0] - fixValue[0] > -20)
            {
                temp = 0;
                if (line_effet >= shortstraightline)
                {
                    for (i = 0; i < 20; i++)
                    { temp += LCenter[i + 20] - LCenter[i]; }
                    if (temp < 400 && temp > -400)
                    {
                        shortstraightflag = 1;
                    }
                }
            }
            if (shortstraightflag == 1)
            {
                if (L_black[0] < 195 && R_black[0] > 5 && L_black[10] < 190 && R_black[10] > 10)
                {
                    shortstraightflag = 1;
                }
                else
                {
                    shortstraightflag = 0;
                    notstraightflag = 1;
                }
            }
            // ////ion
            /*********************判断弯道****************/
             // ////ion
            if (racewide(45, 40) == 0 || K(line_effet, 0) > 1.7)
            {
                turnflag = 1;
                if (pwm< zhong)
                {
                    leftflag = 1;
                }
                else
                {
                    rightflag = 1;
                }
            }
            // ////ion
            /**************超长直道**************/
            if (poflag == 0 && crossflag == 0 && huandaoflag == 0 && blockflag == 0 && (longstraightflag == 1&&smallsflag==0) && bigsflag == 0 && cutline > 68 && Curve_Lianwan_R == 0 && Curve_Lianwan_L == 0)
            {
                if (L_black[0] < 185 && R_black[0] > 15 && L_black[40] < 180 && R_black[40] > 20 && L_black[60] < 150 && R_black[60] > 50)
                {
                    if (K(0, 20) < 0.7 && K(0, 40) < 0.7 && K(0, 60) < 0.7)
                    {
                        superfastflag = 1;
                    }

                }
            }

        }
				void run()
        {
					
            if(dianbo_switch==1&&Diaobo_flag==0&&Lastroadtype==1&&(Gyro_Y>1000||Gyro_Y<-1000))
				    {
					Dianbo_cnt=10;
					Diaobo_flag=1;
				}
			    	if(Diaobo_flag==1&&Dianbo_cnt>0)
		    		{
					Dianbo_cnt--;
					if(Dianbo_cnt==0)
						Diaobo_flag=0;
				}
				
			    	if(turnflag==1&&kaiqiflag==0&&kaiqi<10)
			     	{
							kaiqi++;
						}
				    else if(kaiqi>3&&turnflag==0)
			    	{
							kaiqiflag=1;
						}
					  if(huandaoflag==1)//环岛大小
            {
							i=0;
							if(huandaogeshu<=2)
							{
								i=0;
 							}
							else if(huandaogeshu<=4)
							{
								i=1;
 							}
							else if(huandaogeshu<=6)
							{
								i=2;
 							}
							else if(huandaogeshu<=8)
							{
								i=3;
							}
							else 
								i=3;
							Huandao_type=huandao_type[i];
						}
						
						if(huandaoflag==1)
            {
							 if(Huandao_type==1)
						 {
							 dajiao_ceshi=dajiaochange(Ispeed1dj);
							 midleline=LCenter[dajiao_ceshi];
						 }
							 else  if(Huandao_type==2)
						 {
					 	 dajiao_ceshi=dajiaochange(Ispeed2dj);
							 midleline=LCenter[dajiao_ceshi];
						 }
								 else if(Huandao_type==3)
									 {
							 dajiao_ceshi=dajiaochange(Ispeed3dj);
							 midleline=LCenter[dajiao_ceshi];
						 }
									 else if(Huandao_type==4)
										 {
								dajiao_ceshi=dajiaochange(Ispeed4dj);
							 midleline=LCenter[dajiao_ceshi];
						 }
										 else
											 {
							  dajiao_ceshi=dajiaochange(Ispeed1dj);
							 midleline=LCenter[dajiao_ceshi];
						 }
											 
					}
						else if( huandaoflag!=1)
						{
						  dajiao_ceshi=dajiaochange(dajiao);
							midleline=LCenter[dajiao_ceshi];
						}
            
						//电机PID 舵机PID
						
						if(huandaoflag==1)
            {
					
						  jiance=20;
						 if(Huandao_type==1)
						 {			
               Huandao_pp=IkP1;				
               Huandao_dd=IkD1;				 							 
							 aim=10*Ispeed1;
						 }
						 else if(Huandao_type==2)
							{
							 Huandao_pp=IkP2;				
               Huandao_dd=IkD2;	
						 		aim=10*Ispeed2;
						   }
								 else if(Huandao_type==3)
									 {
										 Huandao_pp=IkP3;				
               Huandao_dd=IkD3;	
						 								aim=10*Ispeed3;
						 }
									 else if(Huandao_type==4)
										 {
											 Huandao_pp=IkP4;				
               Huandao_dd=IkD4;	
						 								aim=10*Ispeed4;
						 }
										 else
											 {
												 Huandao_pp=IkP1;				
               Huandao_dd=IkD1;	
						 								aim=10*Ispeed1;
						 }
											 
							zuo=(int)(zhong-(double)(zhong-steerzuo)*0.9);
							you=(int)(zhong+(double)(steeryou-zhong)*0.9);
						 if(leftflag==1)//确定环岛舵机PD
						 {
							 huandaop=(int)((Huandao_pp/100)*leftp);
						   huandaod=(int)((Huandao_dd/100)*leftd);
						 }
						  else if(rightflag==1)
						 {
							 huandaop=(int)((Huandao_pp/100)*rightp);
						   huandaod=(int)((Huandao_dd/100)*rightd);
						 }
						 else
						 {
							 huandaop=(int)((Huandao_pp/100)*straightp);
						   huandaod=(int)((Huandao_dd/100)*straightd);
						 }
              FTM_PWM_ChangeDuty(Steer_port,Steer_ch,huandaopid()); 						
							bianmai=120;
						  bianmap=40;
						  bianmad=0;
							fuzhiup=3500;						 

					}
						else if (longstraightflag == 1&&smallsflag!=1)
            {
							zuo=(int)(zhong-(double)(zhong-steerzuo)*0.8);
							you=(int)(zhong+(double)(steeryou-zhong)*0.8);
							aim=10*longspeed;
              jiance=2;					
              FTM_PWM_ChangeDuty(Steer_port,Steer_ch,longstraightpid()); 						

//							if(aim-speed>aim-10*speedturn)
//							{
//							bianmai=70;
//						  bianmad=60;
//							}
//							else
//							{
							bianmai=120;
						  bianmap=40;
						  bianmad=0;

						//	}
							fuzhiup=6000;

            }
            else if(shortstraightflag==1 && smallsflag != 1)
             {
							zuo=(int)(zhong-(double)(zhong-steerzuo)*0.8);
							you=(int)(zhong+(double)(steeryou-zhong)*0.8);
							aim=10*shortspeed;
              jiance=3;						
              FTM_PWM_ChangeDuty(Steer_port,Steer_ch,longstraightpid()); 

							bianmai=120;
						  bianmap=40;
						  bianmad=0;
		
							fuzhiup=6000;
            }
						else if(notstraightflag==1&&smallsflag==0)
						{
							zuo=(int)(zhong-(double)(zhong-steerzuo)*0.9);
							you=(int)(zhong+(double)(steeryou-zhong)*0.9);
							aim=10*speedstraight;
					  	jiance=4;
            	FTM_PWM_ChangeDuty(Steer_port,Steer_ch,straightpid());					
							bianmai=125;
						  bianmap=40;
						  bianmad=0;
							fuzhiup=4000;
						}
            else if (smallsflag == 1&&cutline>65)
            {
							zuo=(int)(zhong-(double)(zhong-steerzuo)*0.6);
							you=(int)(zhong+(double)(steeryou-zhong)*0.6);
							aim=10*longSS_speed;
              jiance=7;
	             FTM_PWM_ChangeDuty(Steer_port,Steer_ch,smallspid());
              bianmai=130;
						  bianmap=40;
						  bianmad=0;
							fuzhiup=6000;
            }
						 else if (smallsflag == 1&&cutline<=65)
            {
							zuo=(int)(zhong-(double)(zhong-steerzuo)*0.6);
							you=(int)(zhong+(double)(steeryou-zhong)*0.6);
							aim=10*speedstraight;
              jiance=7;
	             FTM_PWM_ChangeDuty(Steer_port,Steer_ch,smallspid());
              bianmai=120;
						  bianmap=40;
						  bianmad=0;
							fuzhiup=6000;
            }
//				  	else if (bigsflag==1&&Mid_S_Switch==1)
//						{
//							zuo=(int)(zhong-(double)(zhong-steerzuo)*0.8);
//							you=(int)(zhong+(double)(steeryou-zhong)*0.8);
//							aim=10*speedBigs;
//              jiance=8;				   
//              FTM_PWM_ChangeDuty(Steer_port,Steer_ch,bigspid());
//               bianmai=55;//电机控制 I
//							bianmad=40;
//							 fuzhiup=3500;		
//					 					
//						}
						else if (Curve_Lianwan_L==1)
						{
								if(LianWan_plevel_FlagL==0)
	             doub_temp=0.95;
               else if(LianWan_plevel_FlagL==1)
             	doub_temp=0.95;
                else if(LianWan_plevel_FlagL==2)
             	doub_temp=0.95;
                else 
             	doub_temp=0.95;
							zuo=(int)(zhong-(double)(zhong-steerzuo)*0.9);
							you=(int)(zhong+(double)(steeryou-zhong)*0.9);
							aim=10*speedturn;
              jiance=9;				
              FTM_PWM_ChangeDuty(Steer_port,Steer_ch,lianwanzuo());
               bianmai=110;
						  bianmap=40;
						  bianmad=0;
								if(speed>aim)
								{
									 fuzhiup=3700;		
								}
								else
								{
									 fuzhiup=4500;		
								}
							
						}
						else if (Curve_Lianwan_R==1)
						{
								if(LianWan_plevel_FlagR==0)
	             doub_temp=0.95;
               else if(LianWan_plevel_FlagR==1)
             	doub_temp=0.95;
                else if(LianWan_plevel_FlagR==2)
             	doub_temp=0.95;
                else 
             	doub_temp=0.95;
							zuo=(int)(zhong-(double)(zhong-steerzuo)*0.9);
							you=(int)(zhong+(double)(steeryou-zhong)*0.9);
							aim=10*speedturn;
              jiance=9;				
              FTM_PWM_ChangeDuty(Steer_port,Steer_ch,lianwanyou());
               bianmai=110;
						  bianmap=40;
						  bianmad=0;
								if(speed>aim)
								{
									 fuzhiup=3700;		
								}
								else
								{
									 fuzhiup=4500;		
								}
						}
       
            else if (rightflag == 1)
            {
						
							zuo=(int)(zhong-(double)(zhong-steerzuo)*1);
							you=(int)(zhong+(double)(steeryou-zhong)*1);
							
							aim=10*speedturn;
               jiance=6;
               midleline=LCenter[dajiaochange(dajiao)];
	             FTM_PWM_ChangeDuty(Steer_port,Steer_ch,turnpidyou());
							bianmai=110;
						  bianmap=40;
						  bianmad=0;
							if(speed>aim)
								{
									 fuzhiup=4000;		
								}
								else
								{
									 fuzhiup=5000;		
								}
               
            }
            else if (leftflag == 1)
            {
						
							zuo=(int)(zhong-(double)(zhong-steerzuo)*1);
							you=(int)(zhong+(double)(steeryou-zhong)*1);
							
							aim=10*speedturn;
              jiance=5;
	            FTM_PWM_ChangeDuty(Steer_port,Steer_ch,turnpidzuo());
							bianmai=110;
						  bianmap=40;
						  bianmad=0;
              if(speed>aim)
								{
									 fuzhiup=4000;		
								}
								else
								{
									 fuzhiup=5000;		
								}
            }
            else 
						{
						  zuo=(int)(zhong-(double)(zhong-steerzuo)*0.9);
							you=(int)(zhong+(double)(steeryou-zhong)*0.9);
							aim=10*speedstraight;
						  jiance=4;             
            	FTM_PWM_ChangeDuty(Steer_port,Steer_ch,straightpid());
							bianmai=125;
						  bianmap=40;
						  bianmad=0;
							if(speed>aim)
								{
									 fuzhiup=4000;		
								}
								else
								{
									 fuzhiup=4500;		
								}
            }
						
						//目标速度 


						
						if(stopflag==1&&qipaoflag==1&&qipao_cnt<11)
						qipao_cnt++;
			  	  if(stopflag==1&&qipaoflag==1&&qipao_cnt>=10)
				   {
					  bianmai=180;
						  bianmap=100;
						  bianmad=0;						 
				    aim=0;
			     }
						 else
            {
           	if(blockflag==1)
						{
							if((Obstruction_R_EdgeL_Row>45&&Obstruction_R>0)||(Obstruction_L_EdgeL_Row>45&&Obstruction_L>0))
							aim=10*longspeed;
							else
						  aim=10*blockspeed;
						}
						 
        		if(superfastflag==1)
						{
//							if(aim-speed>aim-10*speedturn)
//							{
//							bianmai=120;
//						  bianmap=40;
//						  bianmad=0;
//							}
//							else
//							{
//							bianmai=60;
//						  bianmad=40;
//							}
							bianmai=140;
						  bianmap=40;
						  bianmad=0;
						  aim=10*superspeed;
							jiance=0;
							fuzhiup=6500;
						}

						if(poflag!=0)//坡道速度
            {
						aim=10*po_speed;
							gpio_init(buzzer_Port,GPO,2);
            }
						else
						{
							gpio_init(buzzer_Port,GPO,0);
						}
						if(bigsflag==1)
						{
						aim=10*speedBigs;
						}

				
						if(Diaobo_flag==1)//蜂鸣器   //颠簸只单独给速度
						{
							bianmai=60;
						  bianmap=0;
						  bianmad=40;
							fuzhiup=3000;
				  		aim=10*speedturn;
					   gpio_init(buzzer_Port,GPO,2);
						}					
						else
            {
			     	gpio_init(buzzer_Port,GPO,0);//	GPIO_WriteBit(PTC,GPIO_Pin_12,Bit_RE//);
            }

						}


					  motorpwm=Motor_PID(aim,speed)+motorpwm;
            Dianji_Ftm=motorpwm;						
						if(slowstart==0)  //起跑接长直道
				   	{					

						if(Dianji_Ftm>=fuzhiup)
						{
							motorpwm=fuzhiup;
							
						}
		      	if(Dianji_Ftm<=-5000)
						{
							motorpwm=-5000;
						}
				    }



						
					
				  	if(slowstart==1)   //慢速起跑
            {		
							
					  if(kaiqiflag==0)
						{
					
						if(Dianji_Ftm>=3000)
						{
							motorpwm=3000;
						}
		      	if(Dianji_Ftm<=-5000)
						{
							motorpwm=-5000;
						}
				  	}
						
						if(kaiqiflag==1)
						{
						 
						if(Dianji_Ftm>=fuzhiup)
						{
							motorpwm=fuzhiup;
						}
		      	if(Dianji_Ftm<=-5000)
						{
							motorpwm=-5000;
						}
						
				  	}
						
			     	}
		




						if(stopflag==1&&qipaoflag==1&&qipao_cnt>=10)//起跑线电机控制
						{
							if(motorpwm<0&&speed>100)//这里Speed》100改小会倒车 
						{
							FTM_PWM_ChangeDuty(Motorup_port,Motorup_ch,0);
            	FTM_PWM_ChangeDuty(Motordown_port,Motordown_ch,-motorpwm);
						}
						else
						{
							FTM_PWM_ChangeDuty(Motorup_port,Motorup_ch,0);
            	FTM_PWM_ChangeDuty(Motordown_port,Motordown_ch,0);
						}		
						
					  }
						else  //正常跑车情况 电机输出
						{

				    if(motorpwm>0)
						{
							FTM_PWM_ChangeDuty(Motorup_port,Motorup_ch,motorpwm);
            	FTM_PWM_ChangeDuty(Motordown_port,Motordown_ch,0);
						}
						if(motorpwm<0)
						{
							FTM_PWM_ChangeDuty(Motorup_port,Motorup_ch,0);
            	FTM_PWM_ChangeDuty(Motordown_port,Motordown_ch,-motorpwm);
						}
						
						}
				if((longstraightflag==1||shortstraightflag==1||jiance==4)&&poflag==0&&cutline<=65)
					Lastroadtype=1;//直道
				else
					Lastroadtype=2;//不是直道
				}
			
			 void SignalProcess()//图像处理
        {
	
            Image_Init();//变量初始化 

            ImageProcess(); //图像行处理

            FieldProcess();//图像场处理
        
        }
			
				void steercontrol()  //速度控制
       {
				 
				 L3G4200D_XYZ();//陀螺仪
				 speedlast=speed;
				if(PDin(3)==0)//方向
				{
	      speed=DMACNT_GetValue(DMA_CH1);
				}
				else
				 speed=-DMACNT_GetValue(DMA_CH1);

		    SignalProcess();			          
				run();		
			 }
