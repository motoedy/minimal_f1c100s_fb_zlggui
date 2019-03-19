#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <dma.h>
#include <framebuffer.h>
#include <gpio-f1c100s.h>
#include <pwm-f1c100s.h>

#include <Mymath.h>
#include <config.h>
#include <front.h>
#include <Display_3D.h>
//#include <common.h>
#define TEST_GPIO   0
#define TEST_PWM    0
#define TEST_FB     1

extern void sys_uart_putc(char c);




int boot_main(int argc, char **argv) {
    int a,b;
	float num;
	int flg=0,flg1=1; 
	uint32_t i=0;
	char buf[10];
	float turn;
	uint8_t pic;
	int XO=128,YO=64;
	turn=0,pic=0;
	back_color= 0x00FFFFFFU;
	disp_color=0x000000FFU;


    /* Do initial mem pool */
	do_init_mem_pool();
    do_init_dma_pool();
	
	
	
	GUI_Initialize();

                                                                        
	Screen_Setbl();
    while(1)
    {
	i++;
	if(i>200){
		i=0;
		GUI_FillSCR(back_color);
		RateCube(0,turn,0,0xF000FF00,XO,YO);
		RateCube(turn,0,0,0xF000FF00,128,200);

		GUI_PutString(turn+200,turn+200,"Hello Lichee pi Nano !"); 
		RotatePic29X32(&SETCH33X29[flg][0],0,turn,0,0x00FF00FFU,XO,YO);
		RotatePic29X32(&SETCH33X29[flg1][0],0,turn-90,0,0x00FF00FFU,XO,YO);
		//sprintf(buf,"%d",turn);  //可能是和math库一样的原因？找不到。
		//GUI_PutString(0,0,buf); 
		RotatePic32X32(&SETICO[flg][0],turn,0,0,0x00FF00FFU,128,200) ;
		RotatePic32X32(&SETICO[flg1][0],turn-90,0,0,0x00FF00FFU,128,200) ;
		turn++;if(turn>90){
		turn=0;		
		flg++;
		flg1++;
		if (flg>3)flg=0;
		if (flg1>3)flg1=0;
		}			
		

		Show_Screen();
}else{
sys_uart_putc('A');
}
    }
    return 0;
}

void __fatal_error(const char *msg) {
    while (1);
}

#ifndef NDEBUG
void __assert_func(const char *file, int line, const char *func, const char *expr) {
    //printf("Assertion '%s' failed, at file %s:%d\n", expr, file, line);
    __fatal_error("Assertion failed");
}
#endif

