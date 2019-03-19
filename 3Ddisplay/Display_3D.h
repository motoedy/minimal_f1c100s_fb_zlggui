/*******************************************************************************
* 文档: Display_3D.h
* 作者: 执念执战
* 		QQ:572314251
*		微信：zhinianzhizhan
*		随梦，随心，随愿，恒执念，为梦执战，执战苍天！
*
* 描述:
*	1.三维图形变换操作
*       2.3D-transform.c包含“变换算法”和“投影算法”
*       
*       3.3D_Rotateapplitation对“变换矩阵算法”和“投影算法”的应用
*       4.rotation_font3D.c实现三维空间中旋转图片（优化算法）
*       5.本3D算法学习自《基于STC单片机“12864液晶显示旋转立方体和图片（优化算法）”实例》
*	6.		作者是Wu LianWei
*	7.本文档为整理后的.h文件
*	8：注意：视点到平面的距离，当屏幕上的立方图转着转着乱了，
		满图画色时试着改改视点到物体的距离FOCAL_DISTANCE、比例变换矩阵中数值的大小及XO,YO 的大小
		要确保图形旋转过程中不会超出边界，不然就会乱码
	9.下面注释中的240 400等数字是之前在240*400的屏幕上移植时写的，自行转换为128   64 等，不影响
******* 进行了后期整合，将多个文档整合为四个。//时间：2017/2/5
*******
	10.转载使用时请注明出处
*******************************************************************************/
/*******************************************/
//
//描述：移植ZLG_GUI后将以前的3D显示移植一下，
//		改为使用ZLG_GUI的绘图函数来显示
//
//备注：本3D转换与显示函数为以前学习和改编
//		具体来源请看详细文档描述


//作者：	执念执战
//时间：2017/2/5  	21：50
//******************************************/


#ifndef _Display_3D_H
#define _Display_3D_H


#include <common.h>
//#include <types.h>
#define OLED_X_MAX 800  //修改为Licheepi nano的800*480的屏幕   执念执战 wcc 2018-12-1    OLED的名字懒得改了。
#define OLED_Y_MAX 480

///************************************************
//					坐标结构体
//					用于2D 和3D坐标
//*************************************************/
typedef struct{
	unsigned int  x;
	unsigned int  y;
}_2Dzuobiao ;				//不能直接用数字揩开头来做结构体的名称，所以前面加个—

typedef struct
{
	float x;
	float y;
	float z;
}_3Dzuobiao;

/*****************************************************/
//3D-transform.c 部分
//“变换算法”和“投影算法”
/****************************************************/
void MATRIX_copy(float sourceMAT[4][4],float targetMAT[4][4]);//矩阵拷贝
void MATRIX_multiply(float MAT1[4][4],float MAT2[4][4],float newMAT[4][4]);//矩阵相乘
_3Dzuobiao vector_matrix_MULTIPLY(_3Dzuobiao Source,float MAT[4][4]);//矢量与矩阵相乘
void structure_3D(float MAT[4][4]);//构造单位矩阵
void Translate3D(float MAT[4][4],int16_t tx,int16_t ty,int16_t tz);//平移变换矩阵
void  Scale_3D(float MAT[4][4],float sx,float sy,float sz);//比例变换矩阵
void Rotate_3D(float MAT[4][4],float ax,float ay,float az);//旋转变换矩阵


/*****************************************************/
//3D-transform.c部分
//		投影算法	三维转二维的相关函数		
/****************************************************/
_2Dzuobiao OrtProject(_3Dzuobiao Space);//正射投影（Orthographic projection）
_2Dzuobiao	PerProject(_3Dzuobiao Space,int16_t  XO,int16_t  YO);//透视投影（Perspective projection?

/*****************************************************/
//3D_Rotateapplitation.c 部分
//“变换矩阵算法”和“投影算法”的应用
/****************************************************/
void Rotate_cube(float ax,float ay,float az);//旋转的立方体
void RateCube(float x,float y,float z,uint32_t color,uint16_t XO,uint16_t YO);//透视投影
void RateCube_all(float x,float y,float z,float mx,float my,float mz,float bx,float by,float bz,
											int16_t XO,int16_t YO,uint32_t color);
void RotatePic32X32(unsigned char *dp,float ax,float ay,float az,
												uint32_t color,uint16_t XO,uint16_t YO);//在三维空间中旋转一个32x32的字符或图形
void RotatePic29X32(unsigned char *dp,float ax,float ay,float az,uint32_t color,uint16_t XO,uint16_t YO);
void Rotatecircle(float ax,float ay,float az,uint16_t r,uint32_t color,uint16_t XO,uint16_t YO);//在三维空间中旋转一个圆形
#endif
