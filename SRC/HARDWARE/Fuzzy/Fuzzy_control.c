
#include "Fuzzy_control.h"

float tioashi_1,tioashi_2,tioashi_3,tioashi_4,tioashi_5,tioashi_6,tioashi_7,tioashi_8;
/***************FUZZY_steer���ģ��*****************/
//Input P language feature.

        float Error_Domain1[5] = { 0, 20, 40, 60,80};//ƫ������

//        float Error_Domain1[6] = { 0, 10, 20, 30,40,50};//ƫ������
        float DError_Domain1[6] = { 0, 5, 10, 15, 20 ,25 };//ƫ���ƫ������
        float UP1[7] = { 0.8, 0.9, 1, 1.1, 1.2, 1.3 ,1.4 };//�ֶ�P����ϵ�� up[0]�����Χ0.8-1.4
				 float UD1[7] = { 1, 1.1, 1.2, 1.3, 1.4, 1.5 ,1.6 }; 

        //���
        float Error_Domain2[6] = { 0, 10, 25, 40, 55,70 };//ƫ������
        float DError_Domain2[6] = { 0, 3, 7, 12,17 ,22 };//ƫ���ƫ������
        float UP2[7] = { 8, 8.5, 9, 9.5,10,10.5,11 };//�ֶ�P����ϵ��  5
        float UD2[7] = { 8, 8.5, 9, 9.5,10,10.5,11 };//�ֶ�P����ϵ��  5

				
												//���ģ��  //7.12�汾
						byte Dianji_ruleP2[9][9]={//Pģ����
//ƫ�� NSB,NB,NM,NS,ZO,PS,PM,PB,PSB  
       { 2, 2, 2, 2, 2, 2, 2, 3, 4 }, //NSB  ƫ���ƫ��

       { 2, 2, 2, 2, 2, 2, 2, 3, 4 }, //NB 

       { 2, 2, 2, 2, 2, 2, 2, 3, 4 }, //NM 

       { 2, 2, 2, 2, 2, 2, 2, 3, 4 }, //NS 

       { 2, 2, 2, 2, 2, 2, 2, 3, 4 },  //ZO 

       { 2, 2, 2, 2, 2, 2, 2, 3, 4 }, //PS 

       { 2, 2, 2, 2, 2, 2, 2, 3, 4 },  //PM 

       { 2, 2, 2, 2, 2, 2, 2, 3, 4 },  //PB 

       { 2, 2, 2, 2, 2, 2, 2, 3, 4 }, //PSB 
			
			};
						
//								//���ģ��  //7.11�汾
//						byte Dianji_ruleP2[9][9]={//Pģ����
////ƫ�� NSB,NB,NM,NS,ZO,PS,PM,PB,PSB  
//       { 3, 3, 2, 2, 2, 2, 2, 3, 4 }, //NSB  ƫ���ƫ��

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

//												//���ģ��  
//						byte Dianji_ruleP2[9][9]={//Pģ����
////ƫ�� NSB,NB,NM,NS,ZO,PS,PM,PB,PSB  
//       { 2, 2, 2, 2, 2, 2, 2, 2, 2 }, //NSB  ƫ���ƫ��

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
//				//���ģ��
//						byte Dianji_ruleP2[9][9]={//Pģ����
////ƫ�� NSB,NB,NM,NS,ZO,PS,PM,PB,PSB  
//      { 4, 3, 2, 1, 1, 2, 3, 4, 5 }, //NSB  ƫ���ƫ��

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
		
		byte  Dianji_ruleD2[9][9]={//Dģ����
		
//ƫ�� NSB,NB,NM,NS,ZO,PS,PM,PB,PSB  
      { 4, 3, 2, 1, 1, 2, 3, 4, 5 }, //NSB  ƫ���ƫ��

      { 4, 3, 2, 1, 1, 2, 3, 4, 5 }, //NB 

      { 4, 3, 2, 1, 1, 2, 3, 4, 5 },//NM 

      { 4, 3, 2, 1, 1, 2, 3, 4, 5 }, //NS 

      { 4, 3, 2, 1, 1, 2, 3, 4, 5 }, //ZO 

      { 4, 3, 2, 1, 1, 2, 3, 4, 5 },//PS 

      { 4, 3, 2, 1, 1, 2, 3, 4, 5 }, //PM 

      { 4, 3, 2, 1, 1, 2, 3, 4, 5 }, //PB 

      { 4, 3, 2, 1, 1, 2, 3, 4, 5 },//PSB 
		
		};



		//���ģ����
				byte Steering_Engine_ruleP2[9][9]={//Pģ����
//ƫ�� NSB,NB,NM,NS,ZO,PS,PM,PB,PSB  
      { 4, 4, 3, 3, 2, 1, 1, 1, 2 }, //NSB  ƫ���ƫ��

      { 4, 3, 3, 3, 2, 1, 1, 2, 2 }, //NB 

      { 4, 3, 3, 2, 2, 1, 1, 2, 3 }, //NM 

      { 3, 3, 2, 1, 1, 1, 2, 3, 3}, //NS 

      { 3, 3, 2, 1, 0, 1, 2, 3, 3 }, //ZO 

      { 3, 3, 2, 1, 1, 1, 2, 3, 3 },//PS 

      { 3, 3, 1, 1, 2, 2, 2, 3, 4 }, //PM 

      { 2, 2, 1, 1, 2, 3, 3, 3, 4 }, //PB 

      { 2, 2, 1, 1, 2, 3, 3, 4, 4 }, //PSB 
			};
		
		
		byte  Steering_Engine_ruleD2[9][9]={//Dģ����
		
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
		����:���ģ������ 
		error:ƫ�� ���뷶ΧΪ(-100��100) ����Ϊƫ�� ����Ϊ����
		Derror:ƫ���ƫ��
		PDFlg:=0 ���P��ģ����1���D��ģ��
********************************/
       float MyFuzzy2(int Error, int DError, byte PD_Flag)//���ģ�� 
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

            //ƫ��,,7����������������С�����󡢸�С�ȡ���
            //���������Ⱥ�������ñ���
            if (Error <= Error_Domain2[1])
            {
                //���������Ⱥ����е�������ERROR��������ֵ֮��
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

            //ƫ��ı仯,5��������
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
          //  setText�û��Զ���("NP_DError " + NP_Error + " NP_DError " + NP_DError);
            //MAX-MIN�����˴�����
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
		name���ģ������ 
		error:ƫ�� ���뷶ΧΪ 
		Derror:ƫ���ƫ��
		PDFlg:=0 ���P��ģ����1���D��ģ��
********************************/      
				float MyFuzzy1(int Error, int DError, byte PD_Flag)//���ģ�� 
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

            //ƫ��,,7����������������С�����󡢸�С�ȡ���
            //���������Ⱥ�������ñ���
            if (Error <= Error_Domain1[1])
            {
                //���������Ⱥ����е�������ERROR��������ֵ֮��
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

            //ƫ��ı仯,5��������
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
          //  setText�û��Զ���("NP_DError " + NP_Error + " NP_DError " + NP_DError);
            //MAX-MIN�����˴�����
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


				