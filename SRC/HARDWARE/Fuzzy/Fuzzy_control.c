
#include "Fuzzy_control.h"

float tioashi_1,tioashi_2,tioashi_3,tioashi_4,tioashi_5,tioashi_6,tioashi_7,tioashi_8;
/***************FUZZY_steer打角模糊*****************/
//Input P language feature.

        float Error_Domain1[5] = { 0, 20, 40, 60,80};//偏差论域

//        float Error_Domain1[6] = { 0, 10, 20, 30,40,50};//偏差论域
        float DError_Domain1[6] = { 0, 5, 10, 15, 20 ,25 };//偏差的偏差论域
        float UP1[7] = { 0.8, 0.9, 1, 1.1, 1.2, 1.3 ,1.4 };//分段P比例系数 up[0]输出范围0.8-1.4
				 float UD1[7] = { 1, 1.1, 1.2, 1.3, 1.4, 1.5 ,1.6 }; 

        //舵机
        float Error_Domain2[6] = { 0, 10, 25, 40, 55,70 };//偏差论域
        float DError_Domain2[6] = { 0, 3, 7, 12,17 ,22 };//偏差的偏差论域
        float UP2[7] = { 8, 8.5, 9, 9.5,10,10.5,11 };//分段P比例系数  5
        float UD2[7] = { 8, 8.5, 9, 9.5,10,10.5,11 };//分段P比例系数  5

				
												//电机模糊  //7.12版本
						byte Dianji_ruleP2[9][9]={//P模糊表
//偏差 NSB,NB,NM,NS,ZO,PS,PM,PB,PSB  
       { 2, 2, 2, 2, 2, 2, 2, 3, 4 }, //NSB  偏差的偏差

       { 2, 2, 2, 2, 2, 2, 2, 3, 4 }, //NB 

       { 2, 2, 2, 2, 2, 2, 2, 3, 4 }, //NM 

       { 2, 2, 2, 2, 2, 2, 2, 3, 4 }, //NS 

       { 2, 2, 2, 2, 2, 2, 2, 3, 4 },  //ZO 

       { 2, 2, 2, 2, 2, 2, 2, 3, 4 }, //PS 

       { 2, 2, 2, 2, 2, 2, 2, 3, 4 },  //PM 

       { 2, 2, 2, 2, 2, 2, 2, 3, 4 },  //PB 

       { 2, 2, 2, 2, 2, 2, 2, 3, 4 }, //PSB 
			
			};
						
//								//电机模糊  //7.11版本
//						byte Dianji_ruleP2[9][9]={//P模糊表
////偏差 NSB,NB,NM,NS,ZO,PS,PM,PB,PSB  
//       { 3, 3, 2, 2, 2, 2, 2, 3, 4 }, //NSB  偏差的偏差

//       { 3, 3, 2, 2, 2, 2, 2, 3, 4 }, //NB 

//       { 3, 3, 2, 2, 2, 2, 2, 3, 4 }, //NM 

//       { 3, 3, 2, 2, 2, 2, 2, 3, 4 }, //NS 

//       { 3, 3, 2, 2, 2, 2, 2, 3, 4 },  //ZO 

//       { 3, 3, 2, 2, 2, 2, 2, 3, 4 }, //PS 

//       { 3, 3, 2, 2, 2, 2, 2, 3, 4 },  //PM 

//       { 3, 3, 2, 2, 2, 2, 2, 3, 4 },  //PB 

//      { 3, 3, 2, 2, 2, 2, 2, 3, 4 }, //PSB 
//			
//			};

//												//电机模糊  
//						byte Dianji_ruleP2[9][9]={//P模糊表
////偏差 NSB,NB,NM,NS,ZO,PS,PM,PB,PSB  
//       { 2, 2, 2, 2, 2, 2, 2, 2, 2 }, //NSB  偏差的偏差

//       { 2, 2, 2, 2, 2, 2, 2, 2, 2 }, //NB 

//       { 2, 2, 2, 2, 2, 2, 2, 2, 2 }, //NM 

//       { 2, 2, 2, 2, 2, 2, 2, 2, 2 },//NS 

//       { 2, 2, 2, 2, 2, 2, 2, 2, 2 },  //ZO 

//       { 2, 2, 2, 2, 2, 2, 2, 2, 2 }, //PS 

//       { 2, 2, 2, 2, 2, 2, 2, 2, 2 },  //PM 

//       { 2, 2, 2, 2, 2, 2, 2, 2, 2 },  //PB 

//      { 2, 2, 2, 2, 2, 2, 2, 2, 2 }, //PSB 
//			
//			};		
//				//电机模糊
//						byte Dianji_ruleP2[9][9]={//P模糊表
////偏差 NSB,NB,NM,NS,ZO,PS,PM,PB,PSB  
//      { 4, 3, 2, 1, 1, 2, 3, 4, 5 }, //NSB  偏差的偏差

//      { 4, 3, 2, 1, 1, 2, 3, 4, 5 }, //NB 

//      { 4, 3, 2, 1, 1, 2, 3, 4, 5 },//NM 

//      { 4, 3, 2, 1, 1, 2, 3, 4, 5 }, //NS 

//      { 4, 3, 2, 1, 1, 2, 3, 4, 5 }, //ZO 

//      { 4, 3, 2, 1, 1, 2, 3, 4, 5 },//PS 

//      { 4, 3, 2, 1, 1, 2, 3, 4, 5 }, //PM 

//      { 4, 3, 2, 1, 1, 2, 3, 4, 5 }, //PB 

//      { 4, 3, 2, 1, 1, 2, 3, 4, 5 },//PSB 
//			
//			};
		
		byte  Dianji_ruleD2[9][9]={//D模糊表
		
//偏差 NSB,NB,NM,NS,ZO,PS,PM,PB,PSB  
      { 4, 3, 2, 1, 1, 2, 3, 4, 5 }, //NSB  偏差的偏差

      { 4, 3, 2, 1, 1, 2, 3, 4, 5 }, //NB 

      { 4, 3, 2, 1, 1, 2, 3, 4, 5 },//NM 

      { 4, 3, 2, 1, 1, 2, 3, 4, 5 }, //NS 

      { 4, 3, 2, 1, 1, 2, 3, 4, 5 }, //ZO 

      { 4, 3, 2, 1, 1, 2, 3, 4, 5 },//PS 

      { 4, 3, 2, 1, 1, 2, 3, 4, 5 }, //PM 

      { 4, 3, 2, 1, 1, 2, 3, 4, 5 }, //PB 

      { 4, 3, 2, 1, 1, 2, 3, 4, 5 },//PSB 
		
		};



		//舵机模糊表
				byte Steering_Engine_ruleP2[9][9]={//P模糊表
//偏差 NSB,NB,NM,NS,ZO,PS,PM,PB,PSB  
      { 4, 4, 3, 3, 2, 1, 1, 1, 2 }, //NSB  偏差的偏差

      { 4, 3, 3, 3, 2, 1, 1, 2, 2 }, //NB 

      { 4, 3, 3, 2, 2, 1, 1, 2, 3 }, //NM 

      { 3, 3, 2, 1, 1, 1, 2, 3, 3}, //NS 

      { 3, 3, 2, 1, 0, 1, 2, 3, 3 }, //ZO 

      { 3, 3, 2, 1, 1, 1, 2, 3, 3 },//PS 

      { 3, 3, 1, 1, 2, 2, 2, 3, 4 }, //PM 

      { 2, 2, 1, 1, 2, 3, 3, 3, 4 }, //PB 

      { 2, 2, 1, 1, 2, 3, 3, 4, 4 }, //PSB 
			};
		
		
		byte  Steering_Engine_ruleD2[9][9]={//D模糊表
		
		  //NSB,NB,NM,NS,ZO,PS,PM,PB,PSB
      { 4, 4, 3, 3, 2, 2, 2, 1, 0 }, //NSB 

      { 4, 3, 3, 2, 1, 2, 1, 1, 0 }, //NB 

      { 4, 3, 2, 2, 1, 2, 1, 2, 3 }, //NM 

      { 4, 3, 2, 2, 0, 2, 2, 3, 4 }, //NS 

      { 4, 3, 2, 0, 0, 0, 2, 3, 4 }, //ZO 

      { 4, 3, 2, 2, 0, 2, 2, 3, 4 },//PS 

      { 3, 2, 1, 2, 1, 2, 2, 3, 4 }, //PM 

      { 0, 1, 1, 2, 1, 2, 3, 3, 4 }, //PB 

      { 0, 1, 2, 2, 2, 3, 3, 4, 4 }, //PSB 
		
		};

		
		
		/******************************
		功能:舵机模糊控制 
		error:偏差 输入范围为(-100，100) 输入为偏左 输入为负数
		Derror:偏差的偏差
		PDFlg:=0 输出P的模糊，1输出D的模糊
********************************/
       float MyFuzzy2(int Error, int DError, byte PD_Flag)//舵机模糊 
        {
            byte x1 = 0, x2 = 0, y1 = 0, y2 = 0;
            byte NP_Error = 1, NP_DError = 1;
            float membershipx1 = 0, membershipx2 = 0, membershipy1 = 0, membershipy2 = 0;
            float i1, i2, i3, i4;
            float Back;

            if (Error < 0)
            {
                NP_Error = 0;
                Error = -Error;
            }
            if (DError < 0)
            {
                NP_DError = 0;
                DError = -DError;
            }

            //偏差,,7个描述量，正大、正小、负大、负小等。。
            //根据隶属度函数，获得比例
            if (Error <= Error_Domain2[1])
            {
                //符合隶属度函数中的两条，ERROR介于论域值之间
                x1 = 0;
                x2 = 1;
                membershipx2 = (float)(Error - Error_Domain2[0]) / (float)(Error_Domain2[1] - Error_Domain2[0]);
                membershipx1 = (float)1 - membershipx2;
            }
            else if (Error <= Error_Domain2[2])
            {
                x1 = 1;
                x2 = 2;
                membershipx2 = (float)(Error - Error_Domain2[1]) / (float)(Error_Domain2[2] - Error_Domain2[1]);
                membershipx1 = (float)1 - membershipx2;
            }
            else if (Error <= Error_Domain2[3])
            {
                x1 = 2;
                x2 = 3;
                membershipx2 = (float)(Error - Error_Domain2[2]) / (float)(Error_Domain2[3] - Error_Domain2[2]);
                membershipx1 = (float)1 - membershipx2;
            }
            else if (Error <= Error_Domain2[4])
            {
                x1 = 3;
                x2 = 4;
                membershipx2 = (float)(Error - Error_Domain2[3]) / (float)(Error_Domain2[4] - Error_Domain2[3]);
                membershipx1 = (float)1 - membershipx2;
            }
            else
            {
                x1 = 4;
                x2 = 4;
                ///membershipx2 = (float)(Error - Error_Domain[3]) / (float)(Error_Domain[4] - Error_Domain[3]);
                // membershipx1 = (float)1 - membershipx2;
                membershipx2 = membershipx1 = 1;
            }

            //偏差的变化,5个描述量
            if (DError <= DError_Domain2[1])
            {
                y1 = 0;
                y2 = 1;
                membershipy2 = (float)(DError - DError_Domain2[0]) / (float)(DError_Domain2[1] - DError_Domain2[0]);
                membershipy1 = (float)1 - membershipy2;
            }
            else if (DError <= DError_Domain2[2])
            {
                y1 = 1;
                y2 = 2;
                membershipy2 = (float)(DError - DError_Domain2[1]) / (float)(DError_Domain2[2] - DError_Domain2[1]);
                membershipy1 = (float)1 - membershipy2;
            }
            else if (DError <= DError_Domain2[3])
            {
                y1 = 2;
                y2 = 3;
                membershipy2 = (float)(DError - DError_Domain2[2]) / (float)(DError_Domain2[3] - DError_Domain2[2]);
                membershipy1 = (float)1 - membershipy2;
            }
            else if (DError <= DError_Domain2[4])
            {
                y1 = 3;
                y2 = 4;
                membershipy2 = (float)(DError - DError_Domain2[3]) / (float)(DError_Domain2[4] - DError_Domain2[3]);
                membershipy1 = (float)1 - membershipy2;
            }
            else 
            {
                y1 = 4;
                y2 = 4;
             
                membershipy2 = membershipy1 = 1;
            }
            if (NP_Error == 1)
            {
                x1 = (byte)(x1+4);
                x2 = (byte)(x2+4);
            }
            else  
            {
             x1 = (byte)(4-x1);
             x2 = (byte)( 4-x2);
            }
            if (NP_DError == 1)
            {
                y1 += 4;
                y2 += 4;
            }
            else
            {
                y1 = (byte)(4 - y1);
                y2 = (byte)(4 - y2);
            }
          //  setText用户自定义("NP_DError " + NP_Error + " NP_DError " + NP_DError);
            //MAX-MIN法？此处不懂
            if (membershipx1 > membershipy1)
                membershipx1 = membershipy1;
            if (membershipx1 > membershipy2)
                membershipx1 = membershipy2;
            if (membershipx2 > membershipy1)
                membershipx2 = membershipy1;
            if (membershipx2 > membershipy2)
                membershipx2 = membershipy2;


            if (PD_Flag == 0)
            {
                i1 = UP2[Steering_Engine_ruleP2[y1][x1]];
                i2 = UP2[Steering_Engine_ruleP2[y2][x1]];
                i3 = UP2[Steering_Engine_ruleP2[y1][x2]];
                i4 = UP2[Steering_Engine_ruleP2[y2][x2]];
                Back = (i1 * membershipx1 + i2 * membershipx2 + i3 * membershipy1 + i4 * membershipy2) /
                    (membershipx1 + membershipx2 + membershipy1 + membershipy2);
                return Back;
            }
            else
            {
                i1 = UP2[Steering_Engine_ruleD2[y1][ x1]];
                i2 = UP2[Steering_Engine_ruleD2[y2][ x1]];
                i3 = UP2[Steering_Engine_ruleD2[y1][ x2]];
                i4 = UP2[Steering_Engine_ruleD2[y2][ x2]];
                Back = (i1 * membershipx1 + i2 * membershipx2 + i3 * membershipy1 + i4 * membershipy2) /
                    (membershipx1 + membershipx2 + membershipy1 + membershipy2);
                return Back;
            }

        }

     		/******************************
		name电机模糊控制 
		error:偏差 输入范围为 
		Derror:偏差的偏差
		PDFlg:=0 输出P的模糊，1输出D的模糊
********************************/      
				float MyFuzzy1(int Error, int DError, byte PD_Flag)//电机模糊 
        {
            byte x1 = 0, x2 = 0, y1 = 0, y2 = 0;
            byte NP_Error = 1, NP_DError = 1;
            float membershipx1 = 0, membershipx2 = 0, membershipy1 = 0, membershipy2 = 0;
            float i1, i2, i3, i4;
            float Back;

            if (Error < 0)
            {
                NP_Error = 0;
                Error = -Error;
            }
            if (DError < 0)
            {
                NP_DError = 0;
                DError = -DError;
            }

            //偏差,,7个描述量，正大、正小、负大、负小等。。
            //根据隶属度函数，获得比例
            if (Error <= Error_Domain1[1])
            {
                //符合隶属度函数中的两条，ERROR介于论域值之间
                x1 = 0;
                x2 = 1;
                membershipx2 = (float)(Error - Error_Domain1[0]) / (float)(Error_Domain1[1] - Error_Domain1[0]);
                membershipx1 = (float)1 - membershipx2;
            }
            else if (Error <= Error_Domain1[2])
            {
                x1 = 1;
                x2 = 2;
                membershipx2 = (float)(Error - Error_Domain1[1]) / (float)(Error_Domain1[2] - Error_Domain1[1]);
                membershipx1 = (float)1 - membershipx2;
            }
            else if (Error <= Error_Domain1[3])
            {
                x1 = 2;
                x2 = 3;
                membershipx2 = (float)(Error - Error_Domain1[2]) / (float)(Error_Domain1[3] - Error_Domain1[2]);
                membershipx1 = (float)1 - membershipx2;
            }
            else if (Error <= Error_Domain1[4])
            {
                x1 = 3;
                x2 = 4;
                membershipx2 = (float)(Error - Error_Domain1[3]) / (float)(Error_Domain1[4] - Error_Domain1[3]);
                membershipx1 = (float)1 - membershipx2;
            }
            else
            {
                x1 = 4;
                x2 = 4;
                ///membershipx2 = (float)(Error - Error_Domain[3]) / (float)(Error_Domain[4] - Error_Domain[3]);
                // membershipx1 = (float)1 - membershipx2;
                membershipx2 = membershipx1 = 1;
            }

            //偏差的变化,5个描述量
            if (DError <= DError_Domain1[1])
            {
                y1 = 0;
                y2 = 1;
                membershipy2 = (float)(DError - DError_Domain1[0]) / (float)(DError_Domain1[1] - DError_Domain1[0]);
                membershipy1 = (float)1 - membershipy2;
            }
            else if (DError <= DError_Domain1[2])
            {
                y1 = 1;
                y2 = 2;
                membershipy2 = (float)(DError - DError_Domain1[1]) / (float)(DError_Domain1[2] - DError_Domain1[1]);
                membershipy1 = (float)1 - membershipy2;
            }
            else if (DError <= DError_Domain1[3])
            {
                y1 = 2;
                y2 = 3;
                membershipy2 = (float)(DError - DError_Domain1[2]) / (float)(DError_Domain1[3] - DError_Domain1[2]);
                membershipy1 = (float)1 - membershipy2;
            }
            else if (DError <= DError_Domain1[4])
            {
                y1 = 3;
                y2 = 4;
                membershipy2 = (float)(DError - DError_Domain1[3]) / (float)(DError_Domain1[4] - DError_Domain1[3]);
                membershipy1 = (float)1 - membershipy2;
            }
            else 
            {
                y1 = 4;
                y2 = 4;
             
                membershipy2 = membershipy1 = 1;
            }
            if (NP_Error == 1)
            {
                x1 = (byte)(x1+4);
                x2 = (byte)(x2+4);
            }
            else  
            {
             x1 = (byte)(4-x1);
             x2 = (byte)( 4-x2);
            }
            if (NP_DError == 1)
            {
                y1 += 4;
                y2 += 4;
            }
            else
            {
                y1 = (byte)(4 - y1);
                y2 = (byte)(4 - y2);
            }
          //  setText用户自定义("NP_DError " + NP_Error + " NP_DError " + NP_DError);
            //MAX-MIN法？此处不懂
            if (membershipx1 > membershipy1)
                membershipx1 = membershipy1;
            if (membershipx1 > membershipy2)
                membershipx1 = membershipy2;
            if (membershipx2 > membershipy1)
                membershipx2 = membershipy1;
            if (membershipx2 > membershipy2)
                membershipx2 = membershipy2;


            if (PD_Flag == 0)
            {
							
                tioashi_1=i1 = UP1[Dianji_ruleP2[y1][x1]];
                tioashi_2=i2 = UP1[Dianji_ruleP2[y2][x1]];
                tioashi_3=i3 = UP1[Dianji_ruleP2[y1][x2]];
                tioashi_4=i4 = UP1[Dianji_ruleP2[y2][x2]];
							tioashi_5=membershipx1;
						  tioashi_6=membershipx2;
							tioashi_7=membershipy1;
							tioashi_8=membershipy2;

                Back = (i1 * membershipx1 + i2 * membershipx2 + i3 * membershipy1 + i4 * membershipy2) /
                    (membershipx1 + membershipx2 + membershipy1 + membershipy2);
                return Back;
							
            }
            else
            {
                i1 = UP1[Dianji_ruleD2[y1][ x1]];
                i2 = UP1[Dianji_ruleD2[y2][ x1]];
                i3 = UP1[Dianji_ruleD2[y1][ x2]];
                i4 = UP1[Dianji_ruleD2[y2][ x2]];
                Back = (i1 * membershipx1 + i2 * membershipx2 + i3 * membershipy1 + i4 * membershipy2) /
                    (membershipx1 + membershipx2 + membershipy1 + membershipy2);
                return Back;
            }

        }


				