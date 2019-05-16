#ifndef _SONYCCD_h
#define _SONYCCD_h

#include "headfile.h"

#define SonyCCD_W  640
#define SonyCCD_H  480


#define CCD_IMAGE_H  70
#define CCD_IMAGE_W  200
#define DMACnt 700

#define sonyccd_HREF_Port	 D8	//行中断
#define sonyccd_VSYNC_Port A5	//场中断

#define sonyccd_DMA_CH			DMA_CH0
#define sonyccd_DATA_PORT		B_IN_DATA(0)
#define sonyccd_DATA_BIN		DMABuffer
#define sonyccd_DATA_NUM		700


extern uint8_t P_Pixels[CCD_IMAGE_H][CCD_IMAGE_W];

extern uint8_t CCD_flag;

extern uint8_t MoveIamge;
extern uint8_t YuZhi;
void SonyCCD_Init(void);
void New_OLED_DISAPLAY(void);
void oled_Display(void);


#endif
