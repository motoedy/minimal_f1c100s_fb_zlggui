
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <dma.h>
#include <framebuffer.h>

#include <types.h>
#include <common.h>


framebuffer_t fb_f1c100s;
render_t* render;


void Screen_Init(void){
	fb_f1c100s_init(&fb_f1c100s);
	render = fb_f1c100s_create(&fb_f1c100s);
}

void Set_Point(int x,int y,uint32_t color){
	((uint32_t*)render->pixels)[x+y*800] = color;
}
void Fill_Screen(uint32_t color){
	 for (int i = 0; i < render->pixlen/4;i++)
        {
            ((uint32_t*)render->pixels)[i] =color;
        }
}

uint32_t Get_Point(int x ,int y){
	return ((uint32_t*)render->pixels)[x+y*800];
}

void Show_Screen(void){
	fb_f1c100s_present(&fb_f1c100s, render);
}
void Screen_Setbl(void){
 	fb_f1c100s_setbl(&fb_f1c100s, 100);
}



