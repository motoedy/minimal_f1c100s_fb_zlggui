#ifndef __COMMON__H_
#define __COMMON__H_
#include <types.h>
#include <stdint.h>
void Screen_Init(void);
void Set_Point(int x,int y,uint32_t color);
void Fill_Screen(uint32_t color);
uint32_t Get_Point(int x ,int y);
void Show_Screen(void);
void Screen_Setbl(void);
#endif



