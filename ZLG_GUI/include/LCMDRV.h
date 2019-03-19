/****************************************************************************
* 文件名：LCMDRV.H
* 功能：12864图形液晶模块驱动程序。
*       用于ZLG/GUI用户图形界面。
*  
*  作者：黄绍斌
*  日期：2005/3/7
****************************************************************************/
#ifndef  LCMDRV_H
#define  LCMDRV_H  
#include <types.h>
#include <stdint.h>

/* 定义颜色数据类型(可以是数据结构) */
#define  TCOLOR	  uint32_t 		//自行修改，原来是	uint8_t 

/* 定义LCM像素数宏 */
#define  GUI_LCM_XMAX		800				//自行修改			/* 定义液晶x轴的像素数 */
#define  GUI_LCM_YMAX		480			//自行修改			/* 定义液晶y轴的像素数 */


void  GUI_Initialize(void);
void  GUI_FillSCR(TCOLOR dat);
void  GUI_ClearSCR(void);
void  GUI_Point(uint16_t x, uint16_t y, TCOLOR color);
uint32_t  GUI_ReadPoint(uint16_t x, uint16_t y, TCOLOR *ret);
void  GUI_HLine(uint16_t x0, uint16_t y0, uint16_t x1, TCOLOR color);
void  GUI_RLine(uint16_t x0, uint16_t y0, uint8_t y1, TCOLOR color);
void  GUI_Exec(void);

/****************************************************************************
* 名称：GUI_CmpColor()
* 功能：判断颜色值是否一致。
* 入口参数：color1		颜色值1
*		   color2		颜色值2
* 出口参数：返回1表示相同，返回0表示不相同。
* 说明：由于颜色类型TCOLOR可以是结构类型，所以需要用户编写比较函数。
****************************************************************************/
#define  GUI_CmpColor(color1, color2)	( (color1&0x01) == (color2&0x01) )

/****************************************************************************
* 名称：GUI_CopyColor()
* 功能：颜色值复制。
* 入口参数：color1		目标颜色变量
*		   color2		源颜色变量
* 出口参数：无
* 说明：由于颜色类型TCOLOR可以是结构类型，所以需要用户编写复制函数。
****************************************************************************/
#define  GUI_CopyColor(color1, color2) 	*color1 = color2



#endif
