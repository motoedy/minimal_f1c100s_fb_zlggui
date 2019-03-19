/****************************************************************************************
* 文件名：MENU.C
* 功能：菜单显示及操作(下拉式菜单)。
* 作者：黄绍斌
* 日期：2004.02.26
* 备注：使用GUI_SetBackColor()函数设置显示颜色及背景色。
****************************************************************************************/
#include "config.h"


#if  GUI_MenuDown_EN==1
/****************************************************************************
* 名称：GUI_MMenuDraw()
* 功能：显示主菜单，加上边框。
* 入口参数：men		主菜单句柄
* 出口参数：返回0表示操作失败，返回1表示操作成功
****************************************************************************/
uint8  GUI_MMenuDraw(MMENU *men)
{  WINDOWS  *mwin;
   uint8  i;
   uint8  xx;

   /* 参数过滤 */
   if( (men->no)==0 ) return(0);
   
   mwin = men->win;						// 取得窗口句柄
   /* 判断是否可以显示主菜单 */
   if( (mwin->hight)<50 ) return(0);
   if( (mwin->with)<50 ) return(0);
   
   /* 画菜单条，并显示菜主单 */
   GUI_HLine(mwin->x, mwin->y + 22, mwin->x + mwin->with - 1, disp_color);
   
   xx = mwin->x;
   for(i=0; i<(men->no); i++)
   {  if( (xx+MMENU_WIDTH) > (mwin->x + mwin->with) ) return(0);
      
      GUI_PutNoStr(xx+2, mwin->y + 14, men->str[i], 4);			// 书写主菜单文字
      xx += MMENU_WIDTH;
      GUI_RLine(xx, mwin->y + 12, mwin->y + 22, disp_color);	// 显示主菜单分界线      
   }
   
   return(1);
}


/****************************************************************************
* 名称：GUI_MMenuSelect()
* 功能：当前主菜单，加下划线，表示当前主菜单。
* 入口参数：men		主菜单句柄
*          no		所选的主菜单项
* 出口参数：无
****************************************************************************/
void  GUI_MMenuSelect(MMENU *men, uint8 no)
{  WINDOWS  *mwin;
   uint8  xx;

   /* 参数过滤 */
   if( (men->no)==0 ) return;
   if( no>(men->no) ) return;
  
   mwin = men->win;						// 取得窗口句柄
   /* 判断是否可以显示主菜单 */
   if( (mwin->hight)<50 ) return;
   if( (mwin->with)<50 ) return;
   
   /* 显示下划线 */
   xx = mwin->x + no*MMENU_WIDTH;
   GUI_HLine(xx+1, mwin->y + 22-1, xx+MMENU_WIDTH- 1, disp_color);
}


/****************************************************************************
* 名称：GUI_MMenuNSelect()
* 功能：取消当前主菜单，去除下划线。
* 入口参数：men		主菜单句柄
*          no		所选的主菜单项
* 出口参数：无
****************************************************************************/
void  GUI_MMenuNSelect(MMENU *men, uint8 no)
{  WINDOWS  *mwin;
   uint8  xx;

   /* 参数过滤 */
   if( (men->no)==0 ) return;
   if( no>(men->no) ) return;
  
   mwin = men->win;						// 取得窗口句柄
   /* 判断是否可以显示主菜单 */
   if( (mwin->hight)<50 ) return;
   if( (mwin->with)<50 ) return;
   
   /* 显示下划线 */
   xx = mwin->x + no*MMENU_WIDTH;
   GUI_HLine(xx+1, mwin->y + 22-1, xx+MMENU_WIDTH- 1, back_color);
}



/****************************************************************************
* 名称：GUI_SMenuDraw()
* 功能：显示子菜单，加上边框。
* 入口参数：men		子菜单句柄
* 出口参数：返回0表示操作失败，返回1表示操作成功
****************************************************************************/
uint8  GUI_SMenuDraw(SMENU *men)
{  WINDOWS  *mwin;
   uint32   xx, yy;
   uint8    i;

   mwin = men->win;
   /* 判断是否可以显示主菜单 */
   if( (mwin->hight)<50 ) return(0);
   if( (mwin->with)<50 ) return(0);
    
   /* 画菜子单项。下拉子菜单，以向左下拉为原则，若右边溢出则以右下拉显示 */
   xx = mwin->x;
   xx += (men->mmenu_no)*MMENU_WIDTH;
   yy = mwin->y + 22;
   yy +=  (men->no) * 11 + 2;
   if( (xx+SMENU_WIDTH) <= (mwin->x + mwin->with - 1) ) 
   {  /* 以左下拉为原则显示子菜单 */
      if( (men->mmenu_no) == 0 )
      {  GUI_RLine(xx+SMENU_WIDTH, mwin->y + 22, yy, disp_color);
         GUI_HLine(xx, yy, xx+SMENU_WIDTH, disp_color);
      }
      else
      {  GUI_Rectangle(xx, mwin->y + 22, xx+SMENU_WIDTH, yy, disp_color);
      }
      GUI_HLine(xx+1, mwin->y + 22, xx+MMENU_WIDTH-1, back_color);
      
   }
   else
   {  /* 以右下拉为原则 */
      if( (xx+MMENU_WIDTH) == (mwin->x + mwin->with - 1) )
      {  GUI_RLine(xx-(SMENU_WIDTH-MMENU_WIDTH), mwin->y + 22, yy, disp_color);
         GUI_HLine(xx-(SMENU_WIDTH-MMENU_WIDTH), yy, xx+MMENU_WIDTH, disp_color);
         
      }
      else
      {  GUI_Rectangle(xx-(SMENU_WIDTH-MMENU_WIDTH), mwin->y + 22, xx+MMENU_WIDTH, yy, disp_color);
      }
      GUI_HLine(xx+1, mwin->y + 22, xx+MMENU_WIDTH-1, back_color);
      
      xx = xx-(SMENU_WIDTH-MMENU_WIDTH);
   }
   
   /* 显示菜单文字 */
   xx++;
   yy = mwin->y + 22 + 2;
   for(i=0; i<(men->no); i++)
   {  if( i == (men->state) )								// 判断所选择的菜单项
      {  /* 显示背景色 */
         GUI_RectangleFill(xx, yy, xx+SMENU_WIDTH-2, yy+10, disp_color);
         /* 显示菜单字符 */
         GUI_ExchangeColor();
         GUI_PutNoStr(xx+1, yy+1, men->str[i], 8);			// 书写子菜单文字
         GUI_ExchangeColor();
      }
      else
      {  /* 显示背景色 */
         GUI_RectangleFill(xx, yy, xx+SMENU_WIDTH-2, yy+10, back_color);
         /* 显示菜单字符 */
         GUI_PutNoStr(xx+1, yy+1, men->str[i], 8);			// 书写子菜单文字
      }   
      
      yy += 11;
   }
    
   return(1);
}



/****************************************************************************
* 名称：GUI_SMenuSelect()
* 功能：选择新的子菜单。
* 入口参数：men		子菜单句柄
*          old_no	原先选择的子菜单项
*		   new_no	现要选择的子菜单项
* 出口参数：无
****************************************************************************/
void  GUI_SMenuSelect(SMENU *men, uint8 old_no, uint8 new_no)
{  WINDOWS  *mwin;
   uint8  xx, yy;

   /* 参数过滤 */ 
   if(old_no==new_no) return;
   xx = men->no;
   if( (old_no>xx) || (new_no>xx) ) return;
   
   /* 设置新的选择的子菜单项 */
   men->state = new_no;
   
   /* 进行菜单反相显示 */
   mwin = men->win;	 
   xx = mwin->x;
   xx +=  (men->mmenu_no)*MMENU_WIDTH;
   if( (xx+SMENU_WIDTH) > (mwin->x + mwin->with - 1) ) 
   {  /* 以右下拉为原则显示子菜单，所以xx设置在左端 */
      xx = xx-(SMENU_WIDTH-MMENU_WIDTH);
   }
   xx++;
 
   /* 取消原子菜单选择 */  
   yy = mwin->y + 22 + 2;
   yy += old_no*11;
   GUI_RectangleFill(xx, yy, xx+SMENU_WIDTH-2, yy+10, back_color);
   GUI_PutNoStr(xx+1, yy+1, men->str[old_no], 8);
   /* 选择新的子菜单 */
   yy = mwin->y + 22 + 2;
   yy += new_no*11;
   GUI_RectangleFill(xx, yy, xx+SMENU_WIDTH-2, yy+10, disp_color);
   GUI_ExchangeColor();
   GUI_PutNoStr(xx+1, yy+1, men->str[new_no], 8);
   GUI_ExchangeColor();
}



/****************************************************************************
* 名称：GUI_SMenuHide()
* 功能：消隐子菜单项。
* 入口参数：men		子菜单句柄
* 出口参数：返回0表示操作失败，返回1表示操作成功
****************************************************************************/
uint8  GUI_SMenuHide(SMENU *men)
{  WINDOWS  *mwin;
   uint8    xx, yy;

   mwin = men->win;
   /* 判断是否可以显示主菜单 */
   if( (mwin->hight)<50 ) return(0);
   if( (mwin->with)<50 ) return(0);
    
   /* 画菜子单项。下拉子菜单，以向左下拉为原则，若右边溢出则以右下拉显示 */
   xx = mwin->x;
   xx +=  (men->mmenu_no)*MMENU_WIDTH;
   yy = mwin->y + 22;
   yy +=  (men->no) * 11 + 2;
   if( (xx+SMENU_WIDTH) <= (mwin->x + mwin->with - 1) ) 
   {  /* 以左下拉为原则显示子菜单 */
      if( (men->mmenu_no) == 0 )
      {  GUI_RectangleFill(xx+1, mwin->y + 22+1, xx+SMENU_WIDTH, yy, back_color);
      }
      else
      {  GUI_RectangleFill(xx, mwin->y + 22+1, xx+SMENU_WIDTH, yy, back_color);
      }
      GUI_HLine(xx+1, mwin->y + 22, xx+MMENU_WIDTH-1, disp_color);
   }
   else
   {  /* 以右下拉为原则 */
      if( (xx+MMENU_WIDTH) == (mwin->x + mwin->with - 1) )
      {  GUI_RectangleFill(xx-(SMENU_WIDTH-MMENU_WIDTH), mwin->y + 22+1, xx+MMENU_WIDTH-1, yy, back_color);
      }
      else
      {  GUI_RectangleFill(xx-(SMENU_WIDTH-MMENU_WIDTH), mwin->y + 22+1, xx+MMENU_WIDTH, yy, back_color);
      }
      GUI_HLine(xx+1, mwin->y + 22, xx+MMENU_WIDTH-1, disp_color);
   }
    
   return(1);
}
#endif




#if  GUI_MenuIco_EN==1

/*--  调入了一幅图像：C:\WINDOWS\Desktop\OK.bmp  --*/
/*--  宽度x高度=49x14  --*/
/*--  宽度不是8的倍数，现调整为：宽度x高度=56x14  --*/
uint8  const  button_ok[] = 
{
0x07,0xFF,0xFF,0xFF,0xFF,0xF0,0x00,0x18,0x00,0x00,0x00,0x00,0x0C,0x00,0x20,0x00,
0x00,0x00,0x00,0x02,0x00,0x40,0x00,0x0E,0x76,0x00,0x01,0x00,0x80,0x00,0x11,0x24,
0x00,0x00,0x80,0x80,0x00,0x11,0x28,0x00,0x00,0x80,0x80,0x00,0x11,0x30,0x00,0x00,
0x80,0x80,0x00,0x11,0x28,0x00,0x00,0x80,0x80,0x00,0x11,0x28,0x00,0x00,0x80,0x80,
0x00,0x11,0x24,0x00,0x00,0x80,0x40,0x00,0x0E,0x76,0x00,0x01,0x00,0x20,0x00,0x00,
0x00,0x00,0x02,0x00,0x18,0x00,0x00,0x00,0x00,0x0C,0x00,0x07,0xFF,0xFF,0xFF,0xFF,
0xF0,0x00
};



/*--  调入了一幅图像：C:\WINDOWS\Desktop\OK1.bmp  --*/
/*--  宽度x高度=49x14  --*/
/*--  宽度不是8的倍数，现调整为：宽度x高度=56x14  --*/
uint8  const  button_ok1[] = 
{
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0xFF,0xFF,0xFF,0xFF,0xF0,0x00,0x1F,0xFF,
0xFF,0xFF,0xFF,0xFC,0x00,0x3F,0xFF,0xF1,0x89,0xFF,0xFE,0x00,0x7F,0xFF,0xEE,0xDB,
0xFF,0xFF,0x00,0x7F,0xFF,0xEE,0xD7,0xFF,0xFF,0x00,0x7F,0xFF,0xEE,0xCF,0xFF,0xFF,
0x00,0x7F,0xFF,0xEE,0xD7,0xFF,0xFF,0x00,0x7F,0xFF,0xEE,0xD7,0xFF,0xFF,0x00,0x7F,
0xFF,0xEE,0xDB,0xFF,0xFF,0x00,0x3F,0xFF,0xF1,0x89,0xFF,0xFE,0x00,0x1F,0xFF,0xFF,
0xFF,0xFF,0xFC,0x00,0x07,0xFF,0xFF,0xFF,0xFF,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00
};



/*--  调入了一幅图像：C:\WINDOWS\Desktop\Cancle.bmp  --*/
/*--  宽度x高度=49x14  --*/
/*--  宽度不是8的倍数，现调整为：宽度x高度=56x14  --*/
uint8  const  button_cancle[] =
{
0x07,0xFF,0xFF,0xFF,0xFF,0xF0,0x00,0x18,0x00,0x00,0x00,0x00,0x0C,0x00,0x20,0x00,
0x00,0x00,0x00,0x02,0x00,0x40,0xF0,0x00,0x00,0x07,0x01,0x00,0x81,0x10,0x00,0x00,
0x01,0x00,0x80,0x81,0x00,0x00,0x00,0x01,0x00,0x80,0x81,0x01,0x9E,0x1C,0x61,0x00,
0x80,0x81,0x02,0x49,0x24,0x91,0x00,0x80,0x81,0x01,0xC9,0x20,0xF1,0x00,0x80,0x81,
0x12,0x49,0x20,0x81,0x00,0x80,0x40,0xE1,0xFD,0x9C,0x77,0xC1,0x00,0x20,0x00,0x00,
0x00,0x00,0x02,0x00,0x18,0x00,0x00,0x00,0x00,0x0C,0x00,0x07,0xFF,0xFF,0xFF,0xFF,
0xF0,0x00
};




/*--  调入了一幅图像：C:\WINDOWS\Desktop\Cancle1.bmp  --*/
/*--  宽度x高度=49x14  --*/
/*--  宽度不是8的倍数，现调整为：宽度x高度=56x14  --*/
uint8  const  button_cancle1[] =
{
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0xFF,0xFF,0xFF,0xFF,0xF0,0x00,0x1F,0xFF,
0xFF,0xFF,0xFF,0xFC,0x00,0x3F,0x0F,0xFF,0xFF,0xF8,0xFE,0x00,0x7E,0xEF,0xFF,0xFF,
0xFE,0xFF,0x00,0x7E,0xFF,0xFF,0xFF,0xFE,0xFF,0x00,0x7E,0xFE,0x61,0xE3,0x9E,0xFF,
0x00,0x7E,0xFD,0xB6,0xDB,0x6E,0xFF,0x00,0x7E,0xFE,0x36,0xDF,0x0E,0xFF,0x00,0x7E,
0xED,0xB6,0xDF,0x7E,0xFF,0x00,0x3F,0x1E,0x02,0x63,0x88,0x3E,0x00,0x1F,0xFF,0xFF,
0xFF,0xFF,0xFC,0x00,0x07,0xFF,0xFF,0xFF,0xFF,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00
};




/****************************************************************************
* 名称：GUI_Button49x14()
* 功能：显示49*14按钮。
* 入口参数： x		指定显示位置，x坐标
*           y		指定显示位置，y坐标
*           dat		显示的数据地址
* 出口参数：无
****************************************************************************/
void  GUI_Button49x14(uint32 x, uint32 y, uint8 *dat)
{  GUI_LoadPic(x, y, (uint8 *)dat, 49, 14);
}



/****************************************************************************
* 名称：GUI_Button_OK()
* 功能：显示49*14按钮"OK"。
* 入口参数： x		指定显示位置，x坐标
*           y		指定显示位置，y坐标
* 出口参数：无
****************************************************************************/
void  GUI_Button_OK(uint32 x, uint32 y)
{  GUI_LoadPic(x, y, (uint8 *) button_ok, 49, 14);
}


/****************************************************************************
* 名称：GUI_Button_OK1()
* 功能：显示49*14按钮，选择状态的"OK"。
* 入口参数： x		指定显示位置，x坐标
*           y		指定显示位置，y坐标
* 出口参数：无
****************************************************************************/
void  GUI_Button_OK1(uint32 x, uint32 y)
{  GUI_LoadPic(x, y, (uint8 *) button_ok1, 49, 14);
}


/****************************************************************************
* 名称：GUI_Button_Cancle()
* 功能：显示49*14按钮"Cancle"。
* 入口参数： x		指定显示位置，x坐标
*           y		指定显示位置，y坐标
* 出口参数：无
****************************************************************************/
void  GUI_Button_Cancle(uint32 x, uint32 y)
{  GUI_LoadPic(x, y, (uint8 *) button_cancle, 49, 14);
}


/****************************************************************************
* 名称：GUI_Button_Cancle1()
* 功能：显示49*14按钮，选择状态的"Cancle"。
* 入口参数： x		指定显示位置，x坐标
*           y		指定显示位置，y坐标
* 出口参数：无
****************************************************************************/
void  GUI_Button_Cancle1(uint32 x, uint32 y)
{  GUI_LoadPic(x, y, (uint8 *) button_cancle1, 49, 14);
}



/****************************************************************************
* 名称：GUI_MenuIcoDraw()
* 功能：显示图标菜单。
* 入口参数：ico		图标菜单句柄
* 出口参数：返回0表示操作失败，返回1表示操作成功
****************************************************************************/
uint8  GUI_MenuIcoDraw(MENUICO *ico)
{  
   /* 参数过滤 */
   if( ( (ico->x)<5 ) || ( (ico->x)>(GUI_LCM_XMAX-37 ) ) ) return(0);	// 显示起始地址判断
   if( ( (ico->icodat)==NULL ) || ( (ico->title)==NULL ) ) return(0);	// 显示数据内容判断
   
   GUI_LoadPic(ico->x, ico->y, (uint8 *) ico->icodat, 32, 32);			// 显示ICO图
   GUI_HLine(ico->x-5, ico->y+32, ico->x+37, back_color);				// 显示一空行
   if( (ico->state)==0 )
   {  GUI_LoadPic(ico->x-5, ico->y+33, (uint8 *) ico->title, 42, 13);
   }
   else
   {  GUI_LoadPic1(ico->x-5, ico->y+33, (uint8 *) ico->title, 42, 13);
   }
   
   return(1);
}
#endif
