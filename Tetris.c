#include <stdio.h>
#include <dos.h>
#include <conio.h>
#include "bios.h"
#include <stdlib.h>
#include "graphics.h"
#include <time.h>
#include <math.h>

#define closegr closegraph
#define UNITLENGTH 20
#define preboxX 488
#define preboxY 50
#define m1preboxX 278
#define m1preboxY 36
#define m2preboxX 278
#define m2preboxY 248
#define numberwidth 15
#define scoreboxX 488
#define scoreboxY 200
#define lineboxX 488
#define lineboxY 250
#define m1scoreboxX 278
#define m1scoreboxY 186
#define m1lineboxX 278
#define m1lineboxY 216
#define m2scoreboxX 278
#define m2scoreboxY 400
#define m2lineboxX 278
#define m2lineboxY 433
#define numbercolor 4
#define Lv1C 11
#define Lv2C 2
#define Lv3C 3
#define Lv4C 1
#define Lv5C 14
#define Lv6C 5
#define Lv7C 7
#define Lv1I 7
#define Lv2I 6
#define Lv3I 5
#define Lv4I 4
#define Lv5I 3
#define Lv6I 2
#define Lv7I 1
#define basescore 120;

long randpeer;

int NL=1,PL=1;

double unit=50;

int mid;

int sg[12][23],m1sg[12][23],m2sg[12][23];

int activeX[4],m1activeX[4],m2activeX[4];

int activeY[4],m1activeY[4],m2activeY[4];

int over=0,com=0;

void end(int a);

void drawbomb(int x,int y);

void clearbomb(int x,int y);

void drawton(int x,int y);

void clearton(int x,int y);

void drawlighting(int x,int y);

void clearlighting(int x,int y);

void drawlightingburst(int x,int y);

void clearlightingburst(int x,int y);

void drawdropper(int x,int y);

void cleardropper(int x,int y);

void drawasquare(int x,int y,int color);

void np1(int x,int y);

void np2(int x,int y);

void np3(int x,int y);

void np4(int x,int y);

void np5(int x,int y);

void n8(int x,int y,int color);

void n0(int x,int y,int color);

void n1(int x,int y,int color);

void n2(int x,int y,int color);

void n3(int x,int y,int color);

void n4(int x,int y,int color);

void n5(int x,int y,int color);

void n6(int x,int y,int color);

void n7(int x,int y,int color);

void n9(int x,int y,int color);

int m1transX(int x);											//玩家1坐标转换X

int m1transY(int y);											//玩家1坐标转换Y

int m2transX(int x);											//玩家2坐标转换X

void m1clearp(void);											//玩家1清除预测框

void m1fillp(int type,int status);								//玩家1填充预测框

void m2clearp(void);											//玩家2清除预测框

void m2fillp(int type,int status);								//玩家2填充预测框

void m1adjust(int x,int y,int type,int status);				//玩家1调整activeX、activeY的值  x,y为左上角模拟坐标 

void m2adjust(int x,int y,int type,int status);				//玩家2调整activeX、activeY的值  x,y为左上角模拟坐标 

void m1addline(void);										//玩家1补充边线

void m2addline(void);										//玩家2补充边线

int m1can(int o);												//玩家1判断操作是否可行 o表示操作 0:左移 1:右移 2:下移 3:不

int m2can(int o);												//玩家2判断操作是否可行 o表示操作 0:左移 1:右移 2:下移 3:不

int m1dispel(int row);											//玩家1满行消除

int m1drop();											//玩家1落下方块   返回落下行数

void m1scanrow(int row);									//玩家1扫描一行并描绘

int m2dispel(int row);											//玩家2满行消除

int m2drop();											//玩家2落下方块  返回落下行数

void m2scanrow(int row);									//玩家2扫描一行并描绘

void initgr(void);												//图形界面初始化

void clearscreen(void);										//清屏

void clearp(void);											//清除预测框

void fillp(int type,int status);								//填充预测框

int transX(int x);												//坐标转换X

int transY(int y);												//坐标转换Y

int randcolor(void);											//随机设定颜色

void setc(int c);												//设定颜色

int randtype(void);											//随机生成方块 返回值:0:O 1:I 2:L 3:FL 4:T 5:Z 6:FZ

int randitem(void);

int randstatus(int type);										//随机生成方块状态 输入方块类型 返回随机状态

void drawaunit(int x,int y);									//描绘基本单元  x，y为左上角坐标  (描绘前必须先设定颜色)

void clearaunit(int x,int y);									//清除一个基本单元 x，y为左上角坐标

void drawO(int x,int y);										//描绘方块 x，y为左上角坐标  (描绘前必须先设定颜色)

void clearO(int x,int y);										//清除方块  x，y为左上角坐标

void drawI(int x,int y,int pose);								//描绘长条  x，y为左上角坐标,pose为当前状态，0：__ ; 1: |  (描绘前必须先设定颜色)

void clearI(int x,int y,int pose);								//清除长条   x，y为左上角坐标,pose为当前状态，0：__ ; 1: | 

void drawL(int x,int y,int pose);								//描绘L    x，y为左上角坐标,pose为当前状态，0：L; 1: __|; 2:^|; 3:i~~  (描绘前必须先设定颜色)

void clearL(int x,int y,int pose);								//清除L    x，y为左上角坐标,pose为当前状态，0：L; 1: __|; 2:^|; 3:i~~  

void drawFL(int x,int y,int pose);							//描绘反L    x，y为左上角坐标,pose为当前状态，0：_|; 1:~~~i; 2:|^; 3:i__ (描绘前必须先设定颜色)

void clearFL(int x,int y,int pose);							//清除反L    x，y为左上角坐标,pose为当前状态，0：_|; 1:~~~i; 2:|^; 3:i__ 

void drawT(int x,int y,int pose);							//描绘T    x，y为左上角坐标,pose为当前状态，0：T; 1: |--; 2:_|_; 3:-- |(描绘前必须先设定颜色)

void clearT(int x,int y,int pose);							//清除T    x，y为左上角坐标,pose为当前状态，0：T; 1: |--; 2:_|_; 3:-- |

void drawZ(int x,int y,int pose);							//描绘Z    x，y为左上角坐标,pose为当前状态，0：Z; 1: 竖着;(描绘前必须先设定颜色)

void clearZ(int x,int y,int pose);							//清除Z    x，y为左上角坐标,pose为当前状态，0：Z; 1: 竖着;

void drawFZ(int x,int y,int pose);							//描绘FZ    x，y为左上角坐标,pose为当前状态，0：Z; 1: 竖着;(描绘前必须先设定颜色)

void clearFZ(int x,int y,int pose);							//清除FZ    x，y为左上角坐标,pose为当前状态，0：Z; 1: 竖着;

void scanrow(int row);										//扫描一行并描绘

void draw(int x,int y,int type,int status);					//描绘图形 (x,y)为左上角坐标 type为图形形状 status为图形状态

void clear(int x,int y,int type,int status);					//清除图形 (x,y)为左上角坐标 type为图形形状 status为图形状态

void addline(void);											//补充边线
	
void single();													//单人游戏模式

void multi();													//双人游戏模式  com:0.经典模式  1.竞技模式 

void adjust(int x,int y,int type,int status);					//调整activeX、activeY的值  x,y为左上角模拟坐标 

int can(int o);												//判断操作是否可行 o表示操作 0:左移 1:右移 2:下移 3:不动

int dispel(int row);											//满行消除

int drop(void);												//落下方块   返回落下行数

void account(long score);										//计分

void acline(int line);											//统计行数

void m1account(int score);										//玩家1计分

void m1acline(int line);											//玩家1统计行数

void m2account(int score);										//玩家2计分

void m2acline(int line);											//玩家2统计行数

void drawa2p2(int x,int y);

void drawalet_a(int x,int y,int color);
	
void drawalet_b(int x,int y,int color);

void drawalet_c(int x,int y,int color);

void drawalet_d(int x,int y,int color);

void drawalet_e(int x,int y,int color);

void drawalet_f(int x,int y,int color);

void drawalet_g(int x,int y,int color);

void drawalet_z(int x,int y,int color);

void drawalet_y(int x,int y,int color);

void drawalet_x(int x,int y,int color);

void drawalet_w(int x,int y,int color);

void drawalet_v(int x,int y,int color);

void drawalet_u(int x,int y,int color);

void drawalet_t(int x,int y,int color);

void drawalet_s(int x,int y,int color);

void drawalet_r(int x,int y,int color);

void drawalet_q(int x,int y,int color);

void drawalet_p(int x,int y,int color);

void drawalet_o(int x,int y,int color);

void drawalet_n(int x,int y,int color);

void drawalet_m(int x,int y,int color);

void drawalet_l(int x,int y,int color);

void drawalet_k(int x,int y,int color);

void drawalet_j(int x,int y,int color);

void drawalet_i(int x,int y,int color);

void drawalet_h(int x,int y,int color);

void drawalet_T(int x,int y,int color);

void drawaletter(int x,int y,int color,char c);

void displaystring(int x,int y,char * p,int color);

void drawasquare(int x,int y,int color);						//描绘基本立方体	

void drawSL(int x,int y,int color);							//描绘立体L

void drawSI(int x,int y,int color);							//描绘立体I

void drawSZ(int x,int y,int color);							//描绘立体Z

void logo(int x,int y);

void ui(void);													

int main(void)
{
	char c,d;
	int a;
	mid=sqrt((unit*unit)/2);
	
	initgr();
	logo(200,170);
	randpeer=123456;
	/*while (1)
	{
	do
	{
Beginning:		system("cls");
		printf("Choose Game Mode:\n");
		printf("1:One Player\n");
		printf("2:Two Players\n");
		printf("3:Quit\n");
		c=getch();
	}
	while (!(c=='1'||c=='2'||c=='3'));

	switch (c)
	{
		case '1':
			initgr(); 
			single();
			break;
		case '2':
			do
			{
				system("cls");
				printf("Choose Game Mode:\n");
				printf("1:Classical\n");
				printf("2:Competitive\n");
				printf("3:Back\n");
				d=getch();
			}
			while (!(d=='1'||c=='2'||c=='3'));
			switch (d)
			{
				case '1':
					com=0;
					break;
				case '2':
					com=1;
					break;
				case '3':
					goto Beginning;
				default:
					break;
			}
			initgr(); 
			multi();
			break;
		case '3':
			return 0;
		default:
			break;
	}*/
ui();
return 0;
}


void initgr(void) 												//图形界面初始化
{

int gd = DETECT, gm = 0; 
registerbgidriver(EGAVGA_driver);

initgraph(&gd, &gm, "");

}

void clearscreen(void)										//清屏
{
	int poly[8];
	poly[0]=0;
	poly[1]=0;
	poly[2]=0;
	poly[3]=480;
	poly[4]=640;
	poly[5]=480;
	poly[6]=640;
	poly[7]=0;
	setcolor(0);
	setfillstyle(1,0);
	fillpoly(4,poly);
	return;
}

void drawaunit(int x,int y)									//描绘基本单元  x，y为左上角坐标  (描绘前必须先设定颜色)
{
	int un[8];
	un[0]=x;
	un[1]=y;
	un[2]=x;
	un[3]=y+UNITLENGTH;
	un[4]=x+UNITLENGTH;
	un[5]=y+UNITLENGTH;
	un[6]=x+UNITLENGTH;
	un[7]=y;
	fillpoly(4,un);
	return;
}

void clearaunit(int x,int y)									//清除一个基本单元 x，y为左上角坐标
{
	int un[8];
	setcolor(0);
	setfillstyle(1,0);
	un[0]=x;
	un[1]=y;
	un[2]=x;
	un[3]=y+UNITLENGTH+1;
	un[4]=x+UNITLENGTH;
	un[5]=y+UNITLENGTH+1;
	un[6]=x+UNITLENGTH;
	un[7]=y;
	fillpoly(4,un);
}

void drawO(int x,int y)										//描绘方块 x，y为左上角坐标  (描绘前必须先设定颜色)
{
	drawaunit(x,y);
	drawaunit(x+UNITLENGTH,y);
	drawaunit(x,y+UNITLENGTH);
	drawaunit(x+UNITLENGTH,y+UNITLENGTH);
	return;
}

void clearO(int x,int y)										//清除方块  x，y为左上角坐标
{
	clearaunit(x,y);
	clearaunit(x+UNITLENGTH,y);
	clearaunit(x,y+UNITLENGTH);
	clearaunit(x+UNITLENGTH,y+UNITLENGTH);
	return;
}

void drawI(int x,int y,int pose)								//描绘长条  x，y为左上角坐标,pose为当前状态，0：__ ; 1: |  (描绘前必须先设定颜色)
{
	if (pose==0)
	{
		drawaunit(x,y);
		drawaunit(x+UNITLENGTH,y);
		drawaunit(x+2*UNITLENGTH,y);
		drawaunit(x+3*UNITLENGTH,y);
	}
	if (pose==1)
	{
		drawaunit(x,y);
		drawaunit(x,y+UNITLENGTH);
		drawaunit(x,y+2*UNITLENGTH);
		drawaunit(x,y+3*UNITLENGTH);
	}
	return;
}	

void clearI(int x,int y,int pose)								//清除长条   x，y为左上角坐标,pose为当前状态，0：__ ; 1: | 
{
	if (pose==0)
	{
		clearaunit(x,y);
		clearaunit(x+UNITLENGTH,y);
		clearaunit(x+2*UNITLENGTH,y);
		clearaunit(x+3*UNITLENGTH,y);
	}
	if (pose==1)
	{
		clearaunit(x,y);
		clearaunit(x,y+UNITLENGTH);
		clearaunit(x,y+2*UNITLENGTH);
		clearaunit(x,y+3*UNITLENGTH);
	}
	return;
}

void drawL(int x,int y,int pose)								//描绘L    x，y为左上角坐标,pose为当前状态，0：L; 1: __|; 2:^|; 3:i~~  (描绘前必须先设定颜色)
{
	switch (pose)
	{
		case 0:
			drawaunit(x,y);
			drawaunit(x,y+UNITLENGTH);
			drawaunit(x,y+2*UNITLENGTH);
			drawaunit(x+UNITLENGTH,y+2*UNITLENGTH);
			break;
		case 1:
			drawaunit(x,y+UNITLENGTH);
			drawaunit(x+UNITLENGTH,y+UNITLENGTH);
			drawaunit(x+2*UNITLENGTH,y+UNITLENGTH);
			drawaunit(x+2*UNITLENGTH,y);
			break;
		case 2:
			drawaunit(x,y);
			drawaunit(x+UNITLENGTH,y);
			drawaunit(x+UNITLENGTH,y+UNITLENGTH);
			drawaunit(x+UNITLENGTH,y+2*UNITLENGTH);
			break;
		case 3:
			drawaunit(x,y);
			drawaunit(x,y+UNITLENGTH);
			drawaunit(x+UNITLENGTH,y);
			drawaunit(x+2*UNITLENGTH,y);
			break;
		default:
			break;
	}
	return;
}

void clearL(int x,int y,int pose)								//清除L    x，y为左上角坐标,pose为当前状态，0：L; 1: __|; 2:^|; 3:i~~  
{
	switch (pose)
	{
		case 0:
			clearaunit(x,y);
			clearaunit(x,y+UNITLENGTH);
			clearaunit(x,y+2*UNITLENGTH);
			clearaunit(x+UNITLENGTH,y+2*UNITLENGTH);
			break;
		case 1:
			clearaunit(x,y+UNITLENGTH);
			clearaunit(x+UNITLENGTH,y+UNITLENGTH);
			clearaunit(x+2*UNITLENGTH,y+UNITLENGTH);
			clearaunit(x+2*UNITLENGTH,y);
			break;
		case 2:
			clearaunit(x,y);
			clearaunit(x+UNITLENGTH,y);
			clearaunit(x+UNITLENGTH,y+UNITLENGTH);
			clearaunit(x+UNITLENGTH,y+2*UNITLENGTH);
			break;
		case 3:
			clearaunit(x,y);
			clearaunit(x,y+UNITLENGTH);
			clearaunit(x+UNITLENGTH,y);
			clearaunit(x+2*UNITLENGTH,y);
			break;
		default:
			break;
	}
	return;
}

void drawFL(int x,int y,int pose)							//描绘反L    x，y为左上角坐标,pose为当前状态，0：_|; 1:~~~i; 2:|^; 3:i__ (描绘前必须先设定颜色)
{
	switch (pose)
	{
		case 0:
			drawaunit(x+UNITLENGTH,y);
			drawaunit(x+UNITLENGTH,y+UNITLENGTH);
			drawaunit(x+UNITLENGTH,y+2*UNITLENGTH);
			drawaunit(x,y+2*UNITLENGTH);
			break;
		case 1:
			drawaunit(x,y);
			drawaunit(x+UNITLENGTH,y);
			drawaunit(x+2*UNITLENGTH,y);
			drawaunit(x+2*UNITLENGTH,y+UNITLENGTH);
			break;
		case 2:
			drawaunit(x,y);
			drawaunit(x+UNITLENGTH,y);
			drawaunit(x,y+UNITLENGTH);
			drawaunit(x,y+2*UNITLENGTH);
			break;
		case 3:
			drawaunit(x,y);
			drawaunit(x,y+UNITLENGTH);
			drawaunit(x+UNITLENGTH,y+UNITLENGTH);
			drawaunit(x+2*UNITLENGTH,y+UNITLENGTH);
			break;
		default:
			break;
	}
	return;
}

void clearFL(int x,int y,int pose)							//清除反L    x，y为左上角坐标,pose为当前状态，0：_|; 1:~~~i; 2:|^; 3:i__ 
{
	switch (pose)
	{
		case 0:
			clearaunit(x+UNITLENGTH,y);
			clearaunit(x+UNITLENGTH,y+UNITLENGTH);
			clearaunit(x+UNITLENGTH,y+2*UNITLENGTH);
			clearaunit(x,y+2*UNITLENGTH);
			break;
		case 1:
			clearaunit(x,y);
			clearaunit(x+UNITLENGTH,y);
			clearaunit(x+2*UNITLENGTH,y);
			clearaunit(x+2*UNITLENGTH,y+UNITLENGTH);
			break;
		case 2:
			clearaunit(x,y);
			clearaunit(x+UNITLENGTH,y);
			clearaunit(x,y+UNITLENGTH);
			clearaunit(x,y+2*UNITLENGTH);
			break;
		case 3:
			clearaunit(x,y);
			clearaunit(x,y+UNITLENGTH);
			clearaunit(x+UNITLENGTH,y+UNITLENGTH);
			clearaunit(x+2*UNITLENGTH,y+UNITLENGTH);
			break;
		default:
			break;
	}
	return;
}

void drawT(int x,int y,int pose)								//描绘T    x，y为左上角坐标,pose为当前状态，0：T; 1: |--; 2:_|_; 3:-- |(描绘前必须先设定颜色)
{
	switch (pose)
	{
		case 0:
			drawaunit(x,y);
			drawaunit(x+UNITLENGTH,y);
			drawaunit(x+2*UNITLENGTH,y);
			drawaunit(x+UNITLENGTH,y+UNITLENGTH);
			break;
		case 1:
			drawaunit(x,y);
			drawaunit(x+UNITLENGTH,y+UNITLENGTH);
			drawaunit(x,y+UNITLENGTH);
			drawaunit(x,y+2*UNITLENGTH);
			break;
		case 2:
			drawaunit(x,y+UNITLENGTH);
			drawaunit(x+UNITLENGTH,y);
			drawaunit(x+2*UNITLENGTH,y+UNITLENGTH);
			drawaunit(x+UNITLENGTH,y+UNITLENGTH);
			break;
		case 3:
			drawaunit(x,y+UNITLENGTH);
			drawaunit(x+UNITLENGTH,y);
			drawaunit(x+UNITLENGTH,y+UNITLENGTH);
			drawaunit(x+UNITLENGTH,y+2*UNITLENGTH);
			break;
		default:
			break;
	}
	return;
}

void clearT(int x,int y,int pose)								//清除T    x，y为左上角坐标,pose为当前状态，0：T; 1: |--; 2:_|_; 3:-- 
{
	switch (pose)
	{
		case 0:
			clearaunit(x,y);
			clearaunit(x+UNITLENGTH,y);
			clearaunit(x+2*UNITLENGTH,y);
			clearaunit(x+UNITLENGTH,y+UNITLENGTH);
			break;
		case 1:
			clearaunit(x,y);
			clearaunit(x+UNITLENGTH,y+UNITLENGTH);
			clearaunit(x,y+UNITLENGTH);
			clearaunit(x,y+2*UNITLENGTH);
			break;
		case 2:
			clearaunit(x,y+UNITLENGTH);
			clearaunit(x+UNITLENGTH,y);
			clearaunit(x+2*UNITLENGTH,y+UNITLENGTH);
			clearaunit(x+UNITLENGTH,y+UNITLENGTH);
			break;
		case 3:
			clearaunit(x,y+UNITLENGTH);
			clearaunit(x+UNITLENGTH,y);
			clearaunit(x+UNITLENGTH,y+UNITLENGTH);
			clearaunit(x+UNITLENGTH,y+2*UNITLENGTH);
			break;
		default:
			break;
	}
	return;
}

void drawZ(int x,int y,int pose)								//描绘Z    x，y为左上角坐标,pose为当前状态，0：Z; 1: 竖着;(描绘前必须先设定颜色)
{
	if (pose==0)
	{
		drawaunit(x,y);
		drawaunit(x+UNITLENGTH,y);
		drawaunit(x+UNITLENGTH,y+UNITLENGTH);
		drawaunit(x+2*UNITLENGTH,y+UNITLENGTH);
	}
	if (pose==1)
	{
		drawaunit(x+UNITLENGTH,y);
		drawaunit(x,y+UNITLENGTH);
		drawaunit(x+UNITLENGTH,y+UNITLENGTH);
		drawaunit(x,y+2*UNITLENGTH);
	}
	return;
}

void clearZ(int x,int y,int pose)								//清除Z    x，y为左上角坐标,pose为当前状态，0：Z; 1: 竖着;
{
	if (pose==0)
	{
		clearaunit(x,y);
		clearaunit(x+UNITLENGTH,y);
		clearaunit(x+UNITLENGTH,y+UNITLENGTH);
		clearaunit(x+2*UNITLENGTH,y+UNITLENGTH);
	}
	if (pose==1)
	{
		clearaunit(x+UNITLENGTH,y);
		clearaunit(x,y+UNITLENGTH);
		clearaunit(x+UNITLENGTH,y+UNITLENGTH);
		clearaunit(x,y+2*UNITLENGTH);
	}
	return;
}

void drawFZ(int x,int y,int pose)							//描绘FZ    x，y为左上角坐标,pose为当前状态，0：Z; 1: 竖着;(描绘前必须先设定颜色)
{
	if (pose==0)
	{
		drawaunit(x,y+UNITLENGTH);
		drawaunit(x+UNITLENGTH,y);
		drawaunit(x+UNITLENGTH,y+UNITLENGTH);
		drawaunit(x+2*UNITLENGTH,y);
	}
	if (pose==1)
	{
		drawaunit(x,y);
		drawaunit(x,y+UNITLENGTH);
		drawaunit(x+UNITLENGTH,y+UNITLENGTH);
		drawaunit(x+UNITLENGTH,y+2*UNITLENGTH);
	}
	return;
}

void clearFZ(int x,int y,int pose)							//清除FZ    x，y为左上角坐标,pose为当前状态，0：Z; 1: 竖着;
{
	if (pose==0)
	{
		clearaunit(x,y+UNITLENGTH);
		clearaunit(x+UNITLENGTH,y);
		clearaunit(x+UNITLENGTH,y+UNITLENGTH);
		clearaunit(x+2*UNITLENGTH,y);
	}
	if (pose==1)
	{
		clearaunit(x,y);
		clearaunit(x,y+UNITLENGTH);
		clearaunit(x+UNITLENGTH,y+UNITLENGTH);
		clearaunit(x+UNITLENGTH,y+2*UNITLENGTH);
	}
	return;
}

int transX(int x)												//坐标转换X
{
	return 200+20*x;
}
	
int transY(int y)												//坐标转换Y
{
	return 17+20*y;
}

void setc(int c)												//设定颜色
{
	setcolor(15);
	setlinestyle(0,0,1);
	setfillstyle(1,c);
	return;
}

int randcolor(void)											//随机设定颜色
{
	int u;
	srand(((unsigned)time(NULL)+clock()+randpeer)*1233465645);
	randpeer=rand()*342;
	while ((u=rand()%14+1)==2);
	setcolor(15);
	setlinestyle(0,0,1);
	setfillstyle(1,u);
	return u;
}

int randtype(void)											//随机生成方块 返回值:0:O 1:I 2:L 3:FL 4:T 5:Z 6:FZ
{
	int u;
	srand(((unsigned)time(NULL)+clock()-randpeer)*345432142);
	randpeer=rand()*563;
	u=rand()%7;
	return u;
}

int randitem(void)
{
	int u;
	srand(((unsigned)time(NULL)+clock()-randpeer)*3465745);
	randpeer=rand()*532;
	u=rand()*randpeer%100;
	if (u>70)
	{
		srand(((unsigned)time(NULL)+clock()-randpeer)*6453645);
		randpeer=rand()*765;
		u=rand()%4+7;
		return u;
	}
	else return 0;
}

int randstatus(int type)										//随机生成方块状态 输入方块类型 返回随机状态
{
	int u;
	srand(((unsigned)time(NULL)+clock())*3256456+randpeer);
	randpeer=rand()*973;
	switch (type)
	{
		case 1:
		case 5:
		case 6:
			u=rand()%2;
			break;
		case 2:
		case 3:
		case 4:
			u=rand()%4;
			break;
		default:
			break;
	}
	return u;
}

void clearp(void)												//清除预测框
{
	int poly[8];
	setcolor(0);
	setlinestyle(0,0,1);
	setfillstyle(1,0);
	poly[0]=preboxX+2;
	poly[1]=preboxY+2;
	poly[2]=preboxX+2;
	poly[3]=preboxY+6*UNITLENGTH-2;
	poly[4]=preboxX+4*UNITLENGTH+2;
	poly[5]=preboxY+6*UNITLENGTH-2;
	poly[6]=preboxX+4*UNITLENGTH+2;
	poly[7]=preboxY+2;
	fillpoly(4,poly);
	return;
}

void fillp(int type,int status)									//填充预测框
{
	switch(type)
	{
		case 0:
			drawO(preboxX+UNITLENGTH+2,preboxY+2*UNITLENGTH);
			break;
		case 1:
			if (status==0) drawI(preboxX+2,preboxY+3*UNITLENGTH,0);
			else drawI(preboxX+UNITLENGTH+2,preboxY+UNITLENGTH,1);
			break;
		case 2:
			if (status==0||status==2) drawL(preboxX+UNITLENGTH+2,preboxY+UNITLENGTH,status);
			else drawL(preboxX+UNITLENGTH+2,preboxY+2*UNITLENGTH,status);
			break;
		case 3:
			if (status==0||status==2) drawFL(preboxX+UNITLENGTH+2,preboxY+UNITLENGTH,status);
			else drawFL(preboxX+UNITLENGTH+2,preboxY+2*UNITLENGTH,status);
			break;
		case 4:
			if (status==1||status==3) drawT(preboxX+UNITLENGTH+2,preboxY+UNITLENGTH,status);
			else drawT(preboxX+UNITLENGTH+2,preboxY+2*UNITLENGTH,status);
			break;
		case 5:
			if (status==0) drawZ(preboxX+UNITLENGTH+2,preboxY+2*UNITLENGTH,0);
			else drawZ(preboxX+UNITLENGTH+2,preboxY+UNITLENGTH,1);
			break;
		case 6:
			if (status==0) drawFZ(preboxX+UNITLENGTH+2,preboxY+2*UNITLENGTH,0);
			else drawFZ(preboxX+UNITLENGTH+2,preboxY+UNITLENGTH,1);
			break;
		default:
			break;
	}
	return;
}

void scanrow(int row)										//扫描一行并描绘
{
	int i;
	for (i=0;i<=11;i++) 
	{
		setc(sg[i][row]);
		if (sg[i][row]<=0) clearaunit(transX(i),transY(row));
		else drawaunit(transX(i),transY(row));
	}
	return;
}
	
void addline(void)											//补充边线
{
	int i,j;
	for (i=0;i<=11;i++)
		for (j=0;j<=22;j++)
			if (sg[i][j]>0)
			{
				setcolor(15);
				setlinestyle(0,0,1);
				rectangle(transX(i),transY(j),transX(i+1),transY(j+1));
			}
	return;
}

void draw(int x,int y,int type,int status)					//描绘图形 (x,y)为左上角坐标 type为图形形状 status为图形状态
{
	switch(type)
	{
		case 0:
			drawO(x,y);
			break;
		case 1:
			drawI(x,y,status);
			break;
		case 2:
			drawL(x,y,status);
			break;
		case 3:
			drawFL(x,y,status);
			break;
		case 4:
			drawT(x,y,status);
			break;
		case 5:
			drawZ(x,y,status);
			break;
		case 6:
			drawFZ(x,y,status);
			break;
		case 7:
			drawbomb(x,y);
			break;
		case 8:
			drawton(x,y);
			break;
		case 9:
			drawlighting(x,y);
			break;
		case 10:
			drawdropper(x,y);
			break;
		default:
			break;
	}
	return;
}

void clear(int x,int y,int type,int status)					//清除图形 (x,y)为左上角坐标 type为图形形状 status为图形状态
{
	switch(type)
	{
		case 0:
			clearO(x,y);
			break;
		case 1:
			clearI(x,y,status);
			break;
		case 2:
			clearL(x,y,status);
			break;
		case 3:
			clearFL(x,y,status);
			break;
		case 4:
			clearT(x,y,status);
			break;
		case 5:
			clearZ(x,y,status);
			break;
		case 6:
			clearFZ(x,y,status);
			break;
		case 7:
			clearbomb(x,y);
			break;
		case 8:
			clearton(x,y);
			break;
		case 9:
			clearlighting(x,y);
			break;
		case 10:
			cleardropper(x,y);
			break;
		default:
			break;
	}
	return;
}
	
void adjust(int x,int y,int type,int status)					//调整activeX、activeY的值  x,y为左上角模拟坐标 
{
	switch(type)
	{
		case 0:
			activeX[0]=x;
			activeY[0]=y;
			activeX[1]=x+1;
			activeY[1]=y;
			activeX[2]=x;
			activeY[2]=y+1;
			activeX[3]=x+1;
			activeY[3]=y+1;
			break;
		case 1:
			if (status==0)
			{
				activeX[0]=x;
				activeY[0]=y;
				activeX[1]=x+1;
				activeY[1]=y;
				activeX[2]=x+2;
				activeY[2]=y;
				activeX[3]=x+3;
				activeY[3]=y;
			}
			else 
			{
				activeX[0]=x;
				activeY[0]=y;
				activeX[1]=x;
				activeY[1]=y+1;
				activeX[2]=x;
				activeY[2]=y+2;
				activeX[3]=x;
				activeY[3]=y+3;
			}
			break;
		case 2:
			switch(status)
			{
				case 0:
					activeX[0]=x;
					activeY[0]=y;
					activeX[1]=x;
					activeY[1]=y+1;
					activeX[2]=x;
					activeY[2]=y+2;
					activeX[3]=x+1;
					activeY[3]=y+2;
					break;
				case 1:
					activeX[0]=x;
					activeY[0]=y+1;
					activeX[1]=x+1;
					activeY[1]=y+1;
					activeX[2]=x+2;
					activeY[2]=y+1;
					activeX[3]=x+2;
					activeY[3]=y;
					break;
				case 2:
					activeX[0]=x;
					activeY[0]=y;
					activeX[1]=x+1;
					activeY[1]=y;
					activeX[2]=x+1;
					activeY[2]=y+1;
					activeX[3]=x+1;
					activeY[3]=y+2;
					break;
				case 3:
					activeX[0]=x;
					activeY[0]=y;
					activeX[1]=x+1;
					activeY[1]=y;
					activeX[2]=x+2;
					activeY[2]=y;
					activeX[3]=x;
					activeY[3]=y+1;
					break;
		
				default:
					break;
			}
			break;
		case 3:
			switch(status)
			{
				case 0:
					activeX[0]=x+1;
					activeY[0]=y;
					activeX[1]=x+1;
					activeY[1]=y+1;
					activeX[2]=x+1;
					activeY[2]=y+2;
					activeX[3]=x;
					activeY[3]=y+2;
					break;
				case 1:
					activeX[0]=x;
					activeY[0]=y;
					activeX[1]=x+1;
					activeY[1]=y;
					activeX[2]=x+2;
					activeY[2]=y;
					activeX[3]=x+2;
					activeY[3]=y+1;
					break;
				case 2:
					activeX[0]=x;
					activeY[0]=y;
					activeX[1]=x+1;
					activeY[1]=y;
					activeX[2]=x;
					activeY[2]=y+1;
					activeX[3]=x;
					activeY[3]=y+2;
					break;
				case 3:
					activeX[0]=x;
					activeY[0]=y;
					activeX[1]=x;
					activeY[1]=y+1;
					activeX[2]=x+1;
					activeY[2]=y+1;
					activeX[3]=x+2;
					activeY[3]=y+1;
					break;
				default:
					break;
			}
			break;
		case 4:
			switch(status)
			{
				case 0:
					activeX[0]=x;
					activeY[0]=y;
					activeX[1]=x+1;
					activeY[1]=y;
					activeX[2]=x+2;
					activeY[2]=y;
					activeX[3]=x+1;
					activeY[3]=y+1;
					break;
				case 1:
					activeX[0]=x;
					activeY[0]=y;
					activeX[1]=x;
					activeY[1]=y+1;
					activeX[2]=x;
					activeY[2]=y+2;
					activeX[3]=x+1;
					activeY[3]=y+1;
					break;
				case 2:
					activeX[0]=x;
					activeY[0]=y+1;
					activeX[1]=x+1;
					activeY[1]=y+1;
					activeX[2]=x+2;
					activeY[2]=y+1;
					activeX[3]=x+1;
					activeY[3]=y;
					break;
				case 3:
					activeX[0]=x+1;
					activeY[0]=y;
					activeX[1]=x+1;
					activeY[1]=y+1;
					activeX[2]=x+1;
					activeY[2]=y+2;
					activeX[3]=x;
					activeY[3]=y+1;
					break;
				default:
					break;
			}
			break;
		case 5:
			if (status==0)
			{
				activeX[0]=x;
				activeY[0]=y;
				activeX[1]=x+1;
				activeY[1]=y;
				activeX[2]=x+1;
				activeY[2]=y+1;
				activeX[3]=x+2;
				activeY[3]=y+1;
			}
			else 
			{
				activeX[0]=x+1;
				activeY[0]=y;
				activeX[1]=x;
				activeY[1]=y+1;
				activeX[2]=x+1;
				activeY[2]=y+1;
				activeX[3]=x;
				activeY[3]=y+2;
			}
			break;
		case 6:
			if (status==0)
			{
				activeX[0]=x;
				activeY[0]=y+1;
				activeX[1]=x+1;
				activeY[1]=y;
				activeX[2]=x+1;
				activeY[2]=y+1;
				activeX[3]=x+2;
				activeY[3]=y;
			}
			else 
			{
				activeX[0]=x;
				activeY[0]=y;
				activeX[1]=x;
				activeY[1]=y+1;
				activeX[2]=x+1;
				activeY[2]=y+1;
				activeX[3]=x+1;
				activeY[3]=y+2;
			}
			break;
		case 7:
			activeX[0]=x;
			activeY[0]=y;
			activeX[1]=x+1;
			activeY[1]=y;
			activeX[2]=x;
			activeY[2]=y+1;
			activeX[3]=x+1;
			activeY[3]=y+1;	
			break;
		case 8:
			activeX[0]=x;
			activeY[0]=y;
			activeX[1]=-1;
			activeY[1]=-1;
			activeX[2]=-1;
			activeY[2]=-1;
			activeX[3]=x+1;
			activeY[3]=y+2;	
			break;
		case 9:
			activeX[0]=x;
			activeY[0]=y;
			activeX[1]=x;
			activeY[1]=y;
			activeX[2]=x;
			activeY[2]=y+1;
			activeX[3]=x;
			activeY[3]=y+1;	
			break;
		case 10:
			activeX[0]=x;
			activeY[0]=y;
			activeX[1]=x;
			activeY[1]=y;
			activeX[2]=x;
			activeY[2]=y+1;
			activeX[3]=x;
			activeY[3]=y+1;	
			break;
		default:
			break;
	}
	return;
}

int can(int o)													//判断操作是否可行 o表示操作 0:左移 1:右移 2:下移 3:不动
{
	int i,j;
	int p=0;
	for (i=0;i<=3;i++)
		if (activeX[i]==-1) p=1;
	switch(o)
	{
		case 0:
			if (p)
			for (i=activeX[0];i<=activeX[0]+1;i++)
			for (j=activeY[0];j<=activeY[0]+2;j++)
			{
				if (i-1<0) return 0;
				else if (sg[i-1][j]>0) return 0;
			}
			else
			for (i=0;i<=3;i++)
				if (activeX[i]-1<0) return 0;
				else if (sg[activeX[i]-1][activeY[i]]>0) return 0;
			break;
		case 1:
			if (p)
			for (i=activeX[0];i<=activeX[0]+1;i++)
			for (j=activeY[0];j<=activeY[0]+2;j++)
			{
				if (i+1>11) return 0;
				else if (sg[i+1][j]>0) return 0;
			}
			else
			for (i=0;i<=3;i++)
				if (activeX[i]+1>11) return 0;
				else if (sg[activeX[i]+1][activeY[i]]>0) return 0;
			break;
		case 2:
			if (p)
			for (i=activeX[0];i<=activeX[0]+1;i++)
			for (j=activeY[0];j<=activeY[0]+2;j++)
			{
				if (j+1>22) return 0;
				else if (sg[i][j+1]>0) return 0;
			}
			else
			for (i=0;i<=3;i++)
				if (activeY[i]+1>22) return 0;
				else if (sg[activeX[i]][activeY[i]+1]>0) return 0;
				
			break;
		case 3:
			if (p)
			for (i=activeX[0];i<=activeX[0]+1;i++)
			for (j=activeY[0];j<=activeY[0]+2;j++)
			{
				if (i<0||i>11||j<0||j>22) return 0;
				else if (sg[i][j]>0) return 0;
			}
			else
			for (i=0;i<=3;i++)
				if (activeX[i]<0||activeX[i]>11||activeY[i]<0||activeY[i]>22) return 0;
				else if (sg[activeX[i]][activeY[i]]>0) return 0;
			break;
		default:
			break;
	}
	return 1;
}

int dispel(int row)											//满行消除 返回值: 1:此行消除 0:此行不消除 
{
	int i,a;
	a=1;
	for (i=0;i<=11;i++)
		if (sg[i][row]==0) a=0;
	if (a) for (i=0;i<=11;i++) sg[i][row]=0;
	if (a) return 1;
	else return 0;
}

int drop(void)												//落下方块    返回落下行数
{
	int i,j,a,k,t,s;
	s=0;
	t=0;
	a=1;
	while (a)
	{
		a=1;
		for (j=0;j<=11;j++)
			if (sg[j][t]>0) a=0;
		t++;
	}
	t--;
	for (i=t;i<=22;i++)
	{
		a=1;
		for (j=0;j<=11;j++)
			if (sg[j][i]>0) a=0;
		if (a) 
		{
			s++;
			for (k=i;k>=t;k--)
			{
				for (j=0;j<=11;j++)	sg[j][k]=sg[j][k-1];
				scanrow(k);
			}
		}
	}
	return s;
}

void single()												//单人游戏模式
{
	int i,j,k,key,x,y,dp,line=0,level=1,interval=Lv1I,combo=0;
	long t,score=0;
	int pt,ps,at,as,pc,ac,ts,tx,ty,temp;
	NL=1;
	for (i=0;i<=11;i++)
	for (j=0;j<=22;j++)
	sg[i][j]=0;
	over=0;
	for (i=0;i<=3;i++)
	{
		activeX[i]=0;
		activeY[i]=0;
	}
	clearscreen();
	account(0);
	acline(0);

	setcolor(Lv1C);
	setlinestyle(0,0,3);
	rectangle(preboxX,preboxY,preboxX+4*UNITLENGTH+4,preboxY+6*UNITLENGTH);						  			//描绘预测框
	rectangle(198,15,442,479);                    																			   //描绘游戏框
	
	setcolor(15); 
	setlinestyle(0,0,1);
	setfillstyle(1,4);
	pt=randtype();
	ps=randstatus(pt);		
	pc=randcolor();
	t=clock();
	while (1)
	{
		if ((line/10+1)!=level)
		{
			level=line/10+1;
			setlinestyle(0,0,3);
			switch(level)
			{
				case 1:
					setcolor(Lv1C);
					interval=Lv1I;
					break;
				case 2:
					setcolor(Lv2C);
					interval=Lv2I;
					break;
				case 3:
					setcolor(Lv3C);
					interval=Lv3I;
					break;
				case 4:
					setcolor(Lv4C);
					interval=Lv4I;
					break;
				case 5:
					setcolor(Lv5C);
					interval=Lv5I;
					break;
				case 6:
					setcolor(Lv6C);
					interval=Lv6I;
					break;
				case 7:
					setcolor(Lv7C);
					interval=Lv7I;
					break;
				default:
					break;
			}
			rectangle(preboxX,preboxY,preboxX+4*UNITLENGTH+4,preboxY+6*UNITLENGTH);			  			//描绘预测框
			rectangle(198,15,442,479);                    																			   //描绘游戏框
		}
		if (at<7) at=randitem();
		else at=0;
		if (!(line&&at))
		{
		at=pt;
		as=ps;
		ac=pc;
		clearp();
		pt=randtype();
		ps=randstatus(pt);
		pc=randcolor();
		fillp(pt,ps);
		}
		x=4;
		y=0;
		setc(ac);
		draw(transX(x),transY(y),at,as);
		adjust(x,y,at,as);
		for (i=0;i<=3;i++) if (!can(3)&&(at<7)) 
		{
			end(0);
			return;
		}
		temp=1;
		while (temp)
		{
			if (bioskey(1)) key=bioskey(0);
			else key=0;
			if (!can(3)) key=0;
			switch(key)
			{
			case 0:														//无按键
				break;
			case 18432:													//上
				ts=as+1;
				switch(at)
				{
					case 1:
						if (ts>1) ts=0;
						if (ts==0) 
						{
							tx=x-1;
							ty=y+1;
						}
						else
						{
							tx=x+1;
							ty=y-1;
						}
						adjust(tx,ty,at,ts);
						if (can(3)) 
						{
							clear(transX(x),transY(y),at,as);
							x=tx;
							y=ty;
							as=ts;
							setc(ac);
							draw(transX(x),transY(y),at,as);
							addline();
						}
						else adjust(x,y,at,as);
						break;
					case 2:
						if (ts>3) ts=0;
						switch (ts)
						{
							case 0:
								tx=x+1;
								ty=y-1;
								break;
							case 1:
								tx=x-1;
								ty=y;
								break;
							case 2:
								tx=x;
								ty=y;
								break;
							case 3:
								tx=x;
								ty=y+1;
								break;
							default:
								break;
						}
						adjust(tx,ty,at,ts);
						if (can(3)) 
						{
							clear(transX(x),transY(y),at,as);
							x=tx;
							y=ty;
							as=ts;
							setc(ac);
							draw(transX(x),transY(y),at,as);
							addline();
						}
						else adjust(x,y,at,as);
						break;
					case 3:
						if (ts>3) ts=0;
						switch (ts)
						{
							case 0:
								tx=x;
								ty=y;
								break;
							case 1:
								tx=x;
								ty=y+1;
								break;
							case 2:
								tx=x+1;
								ty=y-1;
								break;
							case 3:
								tx=x-1;
								ty=y;
								break;
							default:
								break;
						}
						adjust(tx,ty,at,ts);
						if (can(3)) 
						{
							clear(transX(x),transY(y),at,as);
							x=tx;
							y=ty;
							as=ts;
							setc(ac);
							draw(transX(x),transY(y),at,as);
							addline();
						}
						else adjust(x,y,at,as);
						break;
					case 4:
						if (ts>3) ts=0;
						switch (ts)
						{
							case 0:
								tx=x;
								ty=y+1;
								break;
							case 1:
								tx=x+1;
								ty=y-1;
								break;
							case 2:
								tx=x-1;
								ty=y;
								break;
							case 3:
								tx=x;
								ty=y;
								break;
							default:
								break;
						}
						adjust(tx,ty,at,ts);
						if (can(3)) 
						{
							clear(transX(x),transY(y),at,as);
							x=tx;
							y=ty;
							as=ts;
							setc(ac);
							draw(transX(x),transY(y),at,as);
							addline();
						}
						else adjust(x,y,at,as);
						break;
					case 5:
						if (ts>1) ts=0;
						if (ts==0) 
						{
							tx=x-1;
							ty=y+1;
						}
						else
						{
							tx=x+1;
							ty=y-1;
						}
						adjust(tx,ty,at,ts);
						if (can(3)) 
						{
							clear(transX(x),transY(y),at,as);
							x=tx;
							y=ty;
							as=ts;
							setc(ac);
							draw(transX(x),transY(y),at,as);
							addline();
						}
						else adjust(x,y,at,as);
						break;
					case 6:
						if (ts>1) ts=0;
						if (ts==0) 
						{
							tx=x-1;
							ty=y+1;
						}
						else
						{
							tx=x+1;
							ty=y-1;
						}
						adjust(tx,ty,at,ts);
						if (can(3)) 
						{
							clear(transX(x),transY(y),at,as);
							x=tx;
							y=ty;
							as=ts;
							setc(ac);
							draw(transX(x),transY(y),at,as);
							addline();
						}
						else adjust(x,y,at,as);
						break;
					default:
						break;
				}
				break;
			case 20480:													//下
				clear(transX(x),transY(y),at,as);
				while (can(2))
				{
					y++;
					adjust(x,y,at,as);
				}
				setc(ac);
				draw(transX(x),transY(y),at,as);
				addline();
				t=clock()-interval;
				break;
			case 19200:													//左
				if (can(0)) 
				{
					clear(transX(x),transY(y),at,as);
					x--;
					adjust(x,y,at,as);
					setc(ac);
					draw(transX(x),transY(y),at,as);
					addline();
				}
				break;
			case 19712:													//右
				if (can(1))
				{
					clear(transX(x),transY(y),at,as);
					x++;
					adjust(x,y,at,as);
					setc(ac);
					draw(transX(x),transY(y),at,as);
					addline();
				}
				break;
			case 283:														//esc
				return;
			default:
				break;
			}
			if (clock()-t>=interval)
			{
				t=clock();
				if (can(2))
				{
					clear(transX(x),transY(y),at,as);
					y++;
					adjust(x,y,at,as);
					setc(ac);
					draw(transX(x),transY(y),at,as);
					addline();
				}
				else
				{
					temp=0;
					dp=0;
					if (at<7)
					{
					adjust(x,y,at,as);
					for (i=0;i<=3;i++)
						sg[activeX[i]][activeY[i]]=ac;
					for (i=0;i<=3;i++)
						if (dispel(activeY[i]))
						{
							dp=1;
							scanrow(activeY[i]);
							addline();
						}
					if (dp) 
					{
						combo++;
						delay(300);
						dp=drop();
						line+=dp;
						switch(dp)
						{
							case 1:
								score+=combo*level*basescore;
								break;
							case 2:
								score+=3*combo*level*basescore;
								break;
							case 3:
								score+=6*combo*level*basescore;
								break;
							case 4:
								score+=10*combo*level*basescore;
								break;
							default:
								break;
						}
						addline();
					}
					else combo=0;
					}
					else switch(at)
					{
						case 7:
							clearbomb(transX(x),transY(y));
							for (i=1;i<=3;i++)
							for (j=0;j<=i*2-1;j++)
							{
								if (y-3+i>=0&&y-3+i<=22&&x-i+1+j>=0&&x-i+1+j<=11)
								if (sg[x-i+1+j][y-3+i])
								{
									score+=10;
									sg[x-i+1+j][y-3+i]=0;
								}
							}
							for (i=1;i<=3;i++)
							for (j=0;j<=i*2-1;j++)
							{
								if (y+4-i>=0&&y+4-i<=22&&x-i+1+j>=0&&x-i+1+j<=11)
								if (sg[x-i+1+j][y+4-i])
								{
									score+=10;
									sg[x-i+1+j][y+4-i]=0;
								}
							}
							for (i=0;i<=22;i++)
								scanrow(i);
							addline();
							delay(300);
							if (drop()) 
							{
								for (i=0;i<=22;i++)
								scanrow(i);
								addline();
							}
							break;
						case 8:
							clearton(transX(x),transY(y));
							for (i=0;i<=1;i++)
							for (j=y;j<=22;j++)
							if (sg[x+i][j])
							{
								score+=10;
								sg[x+i][j]=0;
							}
							for (i=0;i<=22;i++)
								scanrow(i);
							addline();
							y=20;
							drawton(transX(x),transY(y));
							delay(300);
							clearton(transX(x),transY(y));
							break;
						case 9:
							for(i=0;i<=11;i++)
							for(j=0;j<=1;j++)
							if (sg[i][j+y])
							{
								sg[i][j+y]=0;
								score+=10;
							}
							drawlightingburst(transX(0),transY(y));	
							delay(100);
							clearlightingburst(transX(0),transY(y));	
							addline();
							delay(200);
							drop();
							for (i=0;i<=22;i++)
								scanrow(i);
							addline();
							break;
						case 10:
							dp=sg[x][y+2];
							cleardropper(transX(x),transY(y));
							addline();
							for (i=0;i<=11;i++)
							for (j=0;j<=22;j++)
							if (sg[i][j]==dp)
							{
								sg[i][j]=-1;
								score+=10;
							}
							for (i=0;i<=22;i++)
								scanrow(i);
							addline();
							delay(300);
							for (i=0;i<=11;i++)
							for (j=0;j<=22;j++)
							if (sg[i][j]==-1)
							{
								for (k=j;k>0;k--)
									sg[i][k]=sg[i][k-1];
								sg[i][0]=0;
							}
							for (i=0;i<=22;i++) scanrow(i);
							addline();
							delay(300);
							for (i=0;i<=22;i++)
							if (dispel(i))
							{
								score+=120;
								scanrow(i);
								addline();
								delay(300);
							}
							drop();
							addline();
							break;
						default:
							break;
					}
					account(score);
					acline(line);
				}
			}
				
		}
	}	
}

void multi()														//双人游戏模式  com:0.经典模式  1.竞技模式
{
	int i,j,k,key,m1x,m2x,m1y,m2y,dp,m1interval=Lv1I,m2interval=Lv1I;
	long m1t,m2t;
	int m1pt,m2pt,m1ps,m2ps,m1at,m2at,m1as,m2as,m1pc,m2pc,m1ac,m2ac,ts,tx,ty,m1temp,m2temp,m1av,m2av;
	int m1line=0,m1score=0,m1level=1,m1combo=0,m2line=0,m2score=0,m2level=1,m2combo=0;
	int m1over=0,m2over=0;
	over=0;
	NL=1;
	for (i=0;i<=11;i++)
	for (j=0;j<=22;j++)
	{
		m1sg[i][j]=0;
		m2sg[i][j]=0;
	}
	for (i=0;i<=3;i++)
	{
		m1activeX[i]=0;
		m1activeY[i]=0;
		m2activeX[i]=0;
		m2activeY[i]=0;
	}
	clearscreen();
	
	m1account(0);
	m1acline(0);
	m2account(0);
	m2acline(0);


	setcolor(Lv1C);
	setlinestyle(0,0,3);
	rectangle(1,15,245,479);             	         //描绘游戏框
	rectangle(m1preboxX,m1preboxY,m1preboxX+4*UNITLENGTH+4,m1preboxY+6*UNITLENGTH);					//描绘预测框
	rectangle(395,15,639,479);                       //描绘游戏框
	rectangle(m2preboxX,m2preboxY,m2preboxX+4*UNITLENGTH+4,m2preboxY+6*UNITLENGTH);						//描绘预测框
	setcolor(15);
	setlinestyle(0,0,1);
	setfillstyle(1,4);
	
	m1temp=0;
	m1pt=randtype();
	m1ps=randstatus(m1pt);		
	m1pc=randcolor();
	m1t=clock();
	m1av=1;
	
	m2temp=0;
	m2pt=randtype();
	m2ps=randstatus(m2pt);		
	m2pc=randcolor();
	m2t=clock();
	m2av=1;
	
	while (1)
	{
		
		if (!m1temp)
		{
			if (!m1over)
			{
			m1x=4;
			m1y=0;
			m1at=m1pt;
			m1as=m1ps;
			m1ac=m1pc;
			m1clearp();
			m1pt=randtype();
			m1ps=randstatus(m1pt);
			m1pc=randcolor();
			m1fillp(m1pt,m1ps);
			setc(m1ac);
			draw(m1transX(m1x),m1transY(m1y),m1at,m1as);
			m1adjust(m1x,m1y,m1at,m1as);
			dp=0;
			for (i=0;i<=3;i++) if (m1sg[m1activeX[i]][m1activeY[i]]>0) dp=1;
			if (dp)
			{
				m1av=0;
				m1over=1;
				over=1;
			}
			if ((m1line/10+1)!=m1level)
			{
			m1level=m1line/10+1;
			setlinestyle(0,0,3);
			switch(m1level)
			{
				case 1:
					setcolor(Lv1C);
					m1interval=Lv1I;
					break;
				case 2:
					setcolor(Lv2C);
					m1interval=Lv2I;
					break;
				case 3:
					setcolor(Lv3C);
					m1interval=Lv3I;
					break;
				case 4:
					setcolor(Lv4C);
					m1interval=Lv4I;
					break;
				case 5:
					setcolor(Lv5C);
					m1interval=Lv5I;
					break;
				case 6:
					setcolor(Lv6C);
					m1interval=Lv6I;
					break;
				case 7:
					setcolor(Lv7C);
					m1interval=Lv7I;
					break;
				default:
					break;
			}
			rectangle(m1preboxX,m1preboxY,m1preboxX+4*UNITLENGTH+4,m1preboxY+6*UNITLENGTH);			  			//描绘预测框
			rectangle(1,15,245,479);                     																			   //描绘游戏框
		}
		}
		m1temp=1;
		}
		
		if (!m2temp)
		{
			if(!m2over)
			{
			m2x=4;
			m2y=0;
			m2at=m2pt;
			m2as=m2ps;
			m2ac=m2pc;
			m2clearp();
			m2pt=randtype();
			m2ps=randstatus(m2pt);
			m2pc=randcolor();
			m2fillp(m2pt,m2ps);
			setc(m2ac);
			draw(m2transX(m2x),m2transY(m2y),m2at,m2as);
			m2adjust(m2x,m2y,m2at,m2as);
			dp=0;
			for (i=0;i<=3;i++) if (m2sg[m2activeX[i]][m2activeY[i]]>0) dp=1;
			if (dp)
			{
				m2av=0;
				m2over=1;
				over=2;
			}
			if ((m2line/10+1)!=m2level)
			{
			m2level=m2line/10+1;
			setlinestyle(0,0,3);
			switch(m2level)
			{
				case 1:
					setcolor(Lv1C);
					m2interval=Lv1I;
					break;
				case 2:
					setcolor(Lv2C);
					m2interval=Lv2I;
					break;
				case 3:
					setcolor(Lv3C);
					m2interval=Lv3I;
					break;
				case 4:
					setcolor(Lv4C);
					m2interval=Lv4I;
					break;
				case 5:
					setcolor(Lv5C);
					m2interval=Lv5I;
					break;
				case 6:
					setcolor(Lv6C);
					m2interval=Lv6I;
					break;
				case 7:
					setcolor(Lv7C);
					m2interval=Lv7I;
					break;
				default:
					break;
			}
			rectangle(m2preboxX,m2preboxY,m2preboxX+4*UNITLENGTH+4,m2preboxY+6*UNITLENGTH);			  			//描绘预测框
			rectangle(395,15,639,479);                     																			   //描绘游戏框
		}
	}
	m2temp=1;
		}
		
		//if ((m1av==0)&&(m2av==0)) return;
		if (m1over&&m2over) 
		{
			if (m1score>=m2score) end(1);
			else end(2);
			return;
		}
		if (com&&over) 
		{
			if (over==1) end (2);
			else end(1);
			return;
		}
			
		while (m1temp&&m2temp)
		{			
			if (bioskey(1)) key=bioskey(0);
			else key=0;
			if (m1av)
			switch(key)
			{
			case 0:														//无按键
				break;
			case 4439:
			case 4471:													//W
				ts=m1as+1;
				switch(m1at)
				{
					case 1:
						if (ts>1) ts=0;
						if (ts==0) 
						{
							tx=m1x-1;
							ty=m1y+1;
						}
						else
						{
							tx=m1x+1;
							ty=m1y-1;
						}
						m1adjust(tx,ty,m1at,ts);
						if (m1can(3)) 
						{
							clear(m1transX(m1x),m1transY(m1y),m1at,m1as);
							m1x=tx;
							m1y=ty;
							m1as=ts;
							setc(m1ac);
							draw(m1transX(m1x),m1transY(m1y),m1at,m1as);
							m1addline();
						}
						else m1adjust(m1x,m1y,m1at,m1as);
						break;
					case 2:
						if (ts>3) ts=0;
						switch (ts)
						{
							case 0:
								tx=m1x+1;
								ty=m1y-1;
								break;
							case 1:
								tx=m1x-1;
								ty=m1y;
								break;
							case 2:
								tx=m1x;
								ty=m1y;
								break;
							case 3:
								tx=m1x;
								ty=m1y+1;
								break;
							default:
								break;
						}
						m1adjust(tx,ty,m1at,ts);
						if (m1can(3)) 
						{
							clear(m1transX(m1x),m1transY(m1y),m1at,m1as);
							m1x=tx;
							m1y=ty;
							m1as=ts;
							setc(m1ac);
							draw(m1transX(m1x),m1transY(m1y),m1at,m1as);
							m1addline();
						}
						else m1adjust(m1x,m1y,m1at,m1as);
						break;
					case 3:
						if (ts>3) ts=0;
						switch (ts)
						{
							case 0:
								tx=m1x;
								ty=m1y;
								break;
							case 1:
								tx=m1x;
								ty=m1y+1;
								break;
							case 2:
								tx=m1x+1;
								ty=m1y-1;
								break;
							case 3:
								tx=m1x-1;
								ty=m1y;
								break;
							default:
								break;
						}
						m1adjust(tx,ty,m1at,ts);
						if (m1can(3)) 
						{
							clear(m1transX(m1x),m1transY(m1y),m1at,m1as);
							m1x=tx;
							m1y=ty;
							m1as=ts;
							setc(m1ac);
							draw(m1transX(m1x),m1transY(m1y),m1at,m1as);
							m1addline();
						}
						else m1adjust(m1x,m1y,m1at,m1as);
						break;
					case 4:
						if (ts>3) ts=0;
						switch (ts)
						{
							case 0:
								tx=m1x;
								ty=m1y+1;
								break;
							case 1:
								tx=m1x+1;
								ty=m1y-1;
								break;
							case 2:
								tx=m1x-1;
								ty=m1y;
								break;
							case 3:
								tx=m1x;
								ty=m1y;
								break;
							default:
								break;
						}
						m1adjust(tx,ty,m1at,ts);
						if (m1can(3)) 
						{
							clear(m1transX(m1x),m1transY(m1y),m1at,m1as);
							m1x=tx;
							m1y=ty;
							m1as=ts;
							setc(m1ac);
							draw(m1transX(m1x),m1transY(m1y),m1at,m1as);
							m1addline();
						}
						else m1adjust(m1x,m1y,m1at,m1as);
						break;
					case 5:
						if (ts>1) ts=0;
						if (ts==0) 
						{
							tx=m1x-1;
							ty=m1y+1;
						}
						else
						{
							tx=m1x+1;
							ty=m1y-1;
						}
						m1adjust(tx,ty,m1at,ts);
						if (m1can(3)) 
						{
							clear(m1transX(m1x),m1transY(m1y),m1at,m1as);
							m1x=tx;
							m1y=ty;
							m1as=ts;
							setc(m1ac);
							draw(m1transX(m1x),m1transY(m1y),m1at,m1as);
							m1addline();
						}
						else m1adjust(m1x,m1y,m1at,m1as);
						break;
					case 6:
						if (ts>1) ts=0;
						if (ts==0) 
						{
							tx=m1x-1;
							ty=m1y+1;
						}
						else
						{
							tx=m1x+1;
							ty=m1y-1;
						}
						m1adjust(tx,ty,m1at,ts);
						if (m1can(3)) 
						{
							clear(m1transX(m1x),m1transY(m1y),m1at,m1as);
							m1x=tx;
							m1y=ty;
							m1as=ts;
							setc(m1ac);
							draw(m1transX(m1x),m1transY(m1y),m1at,m1as);
							m1addline();
						}
						else m1adjust(m1x,m1y,m1at,m1as);
						break;
					default:
						break;
				}
				break;
			case 8019:
			case 8051:													//S
				clear(m1transX(m1x),m1transY(m1y),m1at,m1as);
				while (m1can(2))
				{
					m1y++;
					m1adjust(m1x,m1y,m1at,m1as);
				}
				setc(m1ac);
				draw(m1transX(m1x),m1transY(m1y),m1at,m1as);
				m1addline();
				m1t=clock()-m1interval;
				break;
			case 7745:
			case 7777:													//A
				if (m1can(0)) 
				{
					clear(m1transX(m1x),m1transY(m1y),m1at,m1as);
					m1x--;
					m1adjust(m1x,m1y,m1at,m1as);
					setc(m1ac);
					draw(m1transX(m1x),m1transY(m1y),m1at,m1as);
					m1addline();
				}
				break;
			case 8260:
			case 8292:													//D
				if (m1can(1))
				{
					clear(m1transX(m1x),m1transY(m1y),m1at,m1as);
					m1x++;
					m1adjust(m1x,m1y,m1at,m1as);
					setc(m1ac);
					draw(m1transX(m1x),m1transY(m1y),m1at,m1as);
					m1addline();
				}
				break;
			case 283:														//esc
				return;
			default:
				break;
			}
			
			if (m2av)
			switch(key)
			{
			case 0:														//无按键
				break;
			case 18432:													//上
				ts=m2as+1;
				switch(m2at)
				{
					case 1:
						if (ts>1) ts=0;
						if (ts==0) 
						{
							tx=m2x-1;
							ty=m2y+1;
						}
						else
						{
							tx=m2x+1;
							ty=m2y-1;
						}
						m2adjust(tx,ty,m2at,ts);
						if (m2can(3)) 
						{
							clear(m2transX(m2x),m2transY(m2y),m2at,m2as);
							m2x=tx;
							m2y=ty;
							m2as=ts;
							setc(m2ac);
							draw(m2transX(m2x),m2transY(m2y),m2at,m2as);
							m2addline();
						}
						else m2adjust(m2x,m2y,m2at,m2as);
						break;
					case 2:
						if (ts>3) ts=0;
						switch (ts)
						{
							case 0:
								tx=m2x+1;
								ty=m2y-1;
								break;
							case 1:
								tx=m2x-1;
								ty=m2y;
								break;
							case 2:
								tx=m2x;
								ty=m2y;
								break;
							case 3:
								tx=m2x;
								ty=m2y+1;
								break;
							default:
								break;
						}
						m2adjust(tx,ty,m2at,ts);
						if (m2can(3)) 
						{
							clear(m2transX(m2x),m2transY(m2y),m2at,m2as);
							m2x=tx;
							m2y=ty;
							m2as=ts;
							setc(m2ac);
							draw(m2transX(m2x),m2transY(m2y),m2at,m2as);
							m2addline();
						}
						else m2adjust(m2x,m2y,m2at,m2as);
						break;
					case 3:
						if (ts>3) ts=0;
						switch (ts)
						{
							case 0:
								tx=m2x;
								ty=m2y;
								break;
							case 1:
								tx=m2x;
								ty=m2y+1;
								break;
							case 2:
								tx=m2x+1;
								ty=m2y-1;
								break;
							case 3:
								tx=m2x-1;
								ty=m2y;
								break;
							default:
								break;
						}
						m2adjust(tx,ty,m2at,ts);
						if (m2can(3)) 
						{
							clear(m2transX(m2x),m2transY(m2y),m2at,m2as);
							m2x=tx;
							m2y=ty;
							m2as=ts;
							setc(m2ac);
							draw(m2transX(m2x),m2transY(m2y),m2at,m2as);
							m2addline();
						}
						else m2adjust(m2x,m2y,m2at,m2as);
						break;
					case 4:
						if (ts>3) ts=0;
						switch (ts)
						{
							case 0:
								tx=m2x;
								ty=m2y+1;
								break;
							case 1:
								tx=m2x+1;
								ty=m2y-1;
								break;
							case 2:
								tx=m2x-1;
								ty=m2y;
								break;
							case 3:
								tx=m2x;
								ty=m2y;
								break;
							default:
								break;
						}
						m2adjust(tx,ty,m2at,ts);
						if (m2can(3)) 
						{
							clear(m2transX(m2x),m2transY(m2y),m2at,m2as);
							m2x=tx;
							m2y=ty;
							m2as=ts;
							setc(m2ac);
							draw(m2transX(m2x),m2transY(m2y),m2at,m2as);
							m2addline();
						}
						else m2adjust(m2x,m2y,m2at,m2as);
						break;
					case 5:
						if (ts>1) ts=0;
						if (ts==0) 
						{
							tx=m2x-1;
							ty=m2y+1;
						}
						else
						{
							tx=m2x+1;
							ty=m2y-1;
						}
						m2adjust(tx,ty,m2at,ts);
						if (m2can(3)) 
						{
							clear(m2transX(m2x),m2transY(m2y),m2at,m2as);
							m2x=tx;
							m2y=ty;
							m2as=ts;
							setc(m2ac);
							draw(m2transX(m2x),m2transY(m2y),m2at,m2as);
							m2addline();
						}
						else m2adjust(m2x,m2y,m2at,m2as);
						break;
					case 6:
						if (ts>1) ts=0;
						if (ts==0) 
						{
							tx=m2x-1;
							ty=m2y+1;
						}
						else
						{
							tx=m2x+1;
							ty=m2y-1;
						}
						m2adjust(tx,ty,m2at,ts);
						if (m2can(3)) 
						{
							clear(m2transX(m2x),m2transY(m2y),m2at,m2as);
							m2x=tx;
							m2y=ty;
							m2as=ts;
							setc(m2ac);
							draw(m2transX(m2x),m2transY(m2y),m2at,m2as);
							m2addline();
						}
						else m2adjust(m2x,m2y,m2at,m2as);
						break;
					default:
						break;
				}
				break;
			case 20480:													//下
				clear(m2transX(m2x),m2transY(m2y),m2at,m2as);
				while (m2can(2))
				{
					m2y++;
					m2adjust(m2x,m2y,m2at,m2as);
				}
				setc(m2ac);
				draw(m2transX(m2x),m2transY(m2y),m2at,m2as);
				m2addline();
				m2t=clock()-m2interval;
				break;
			case 19200:													//左
				if (m2can(0)) 
				{
					clear(m2transX(m2x),m2transY(m2y),m2at,m2as);
					m2x--;
					m2adjust(m2x,m2y,m2at,m2as);
					setc(m2ac);
					draw(m2transX(m2x),m2transY(m2y),m2at,m2as);
					m2addline();
				}
				break;
			case 19712:													//右
				if (m2can(1))
				{
					clear(m2transX(m2x),m2transY(m2y),m2at,m2as);
					m2x++;
					m2adjust(m2x,m2y,m2at,m2as);
					setc(m2ac);
					draw(m2transX(m2x),m2transY(m2y),m2at,m2as);
					m2addline();
				}
				break;
			case 283:														//esc
				return;
			default:
				break;
			}
			
			
			
			if (!m1av&&!m1over&&(clock()-m1t>=3)) 
			{
				m1t=clock();
				m1av=1;
				dp=m1drop(com);
				m1addline();
				m1temp=0;
				m1combo++;
				m1line+=dp;
						switch(dp)
						{
							case 1:
								m1score+=m1combo*m1level*basescore;
								break;
							case 2:
								m1score+=3*m1combo*m1level*basescore;
								break;
							case 3:
								m1score+=6*m1combo*m1level*basescore;
								break;
							case 4:
								m1score+=10*m1combo*m1level*basescore;
								break;
							default:
								break;
						}
						m1account(m1score);
						m1acline(m1line);
			}
			
			
			
			if (m1av)
			if (clock()-m1t>=m1interval)
			{
				m1t=clock();
				if (m1can(2))
				{
					clear(m1transX(m1x),m1transY(m1y),m1at,m1as);
					m1y++;
					m1adjust(m1x,m1y,m1at,m1as);
					setc(m1ac);
					draw(m1transX(m1x),m1transY(m1y),m1at,m1as);
					m1addline();
				}
				else
				{
					m1adjust(m1x,m1y,m1at,m1as);
					setc(m1ac);
					draw(m1transX(m1x),m1transY(m1y),m1at,m1as);
					dp=0;
					m1temp=0;
					for (i=0;i<=3;i++)
						m1sg[m1activeX[i]][m1activeY[i]]=m1ac;
					for (i=0;i<=3;i++)
						if (m1dispel(m1activeY[i]))
						{
							dp=1;
							m1scanrow(m1activeY[i]);
							m1addline();
							
							
							if (com&&!m2can(3))
							{
								
								while (!m2can(3))
								{
									m2y--;
									m2adjust(m2x,m2y,m2at,m2as);
									if (m2y<0) 
									{
										over=2;
										m2y=0;
										break;
									}
								}
								m2adjust(m2x,m2y,m2at,m2as);
								//setc(m2ac);
								//draw(m2transX(m2x),m2transY(m2y),m2at,m2as);
								//m2addline();
							}
							else if(com)
							{
								m2adjust(m2x,m2y,m2at,m2as);
								setc(m2ac);
								draw(m2transX(m2x),m2transY(m2y),m2at,m2as);
								m2addline();
							}
							
						}
					if (dp) 
					{
						m1av=0;
						m1temp=1;
					}		
					else m1combo=0;
				}
			}
			
			
			if (!m2av&&!m2over&&(clock()-m2t>=3)) 
			{
				m2t=clock();
				m2av=1;
				dp=m2drop();
				m2addline();
				m2temp=0;
				m2combo++;
				m2line+=dp;
						switch(dp)
						{
							case 1:
								m2score+=m2combo*m2level*basescore;
								break;
							case 2:
								m2score+=3*m2combo*m2level*basescore;
								break;
							case 3:
								m2score+=6*m2combo*m2level*basescore;
								break;
							case 4:
								m2score+=10*m2combo*m2level*basescore;
								break;
							default:
								break;
						}
						m2account(m2score);
						m2acline(m2line);
			}
			if (m2av)
			if (clock()-m2t>=m2interval)
			{
				m2t=clock();
				if (m2can(2))
				{
					clear(m2transX(m2x),m2transY(m2y),m2at,m2as);
					m2y++;
					m2adjust(m2x,m2y,m2at,m2as);
					setc(m2ac);
					draw(m2transX(m2x),m2transY(m2y),m2at,m2as);
					m2addline();
				}
				else
				{
					m2adjust(m2x,m2y,m2at,m2as);
					setc(m2ac);
					draw(m2transX(m2x),m2transY(m2y),m2at,m2as);
					dp=0;
					m2temp=0;
					for (i=0;i<=3;i++)
						m2sg[m2activeX[i]][m2activeY[i]]=m2ac;
					for (i=0;i<=3;i++)
						if (m2dispel(m2activeY[i]))
						{
							dp=1;
							m2scanrow(m2activeY[i]);
							m2addline();
							
							
							
							if (com&&!m1can(3))
							{
								while (!m1can(3))
								{
									m1y--;
									m1adjust(m1x,m1y,m1at,m1as);
									if (m1y<0) 
									{
										over=2;
										m1y=0;
										break;
									}
								}
								m1adjust(m1x,m1y,m1at,m1as);
								//setc(m1ac);
								//draw(m1transX(m1x),m1transY(m1y),m1at,m1as);
								//m1addline();
							}
							else if(com)
							{
								m1adjust(m1x,m1y,m1at,m1as);
								setc(m1ac);
								draw(m1transX(m1x),m1transY(m1y),m1at,m1as);
								m1addline();
							}
							
							
							
							
						}
					if (dp) 
					{
						m2av=0;
						m2temp=1;
					}			
					else m2combo=0;
				}
			}
				
		}		
	}	
}

int m1transX(int x)											//玩家1坐标转换X
{
	return 3+x*UNITLENGTH;
}

int m1transY(int y)											//玩家1坐标转换Y
{
	return 17+y*UNITLENGTH;
}

int m2transX(int x)											//玩家2坐标转换X
{
	return 397+x*UNITLENGTH;
}

int m2transY(int y)											//玩家2坐标转换Y
{
	return 17+y*UNITLENGTH;
}

void m1clearp(void)											//玩家1清除预测框
{
	int poly[8];
	setcolor(0);
	setlinestyle(0,0,1);
	setfillstyle(1,0);
	poly[0]=m1preboxX+2;
	poly[1]=m1preboxY+2;
	poly[2]=m1preboxX+2;
	poly[3]=m1preboxY+6*UNITLENGTH-2;
	poly[4]=m1preboxX+4*UNITLENGTH+2;
	poly[5]=m1preboxY+6*UNITLENGTH-2;
	poly[6]=m1preboxX+4*UNITLENGTH+2;
	poly[7]=m1preboxY+2;
	fillpoly(4,poly);
	return;
}

void m1fillp(int type,int status)								//玩家1填充预测框
{
		switch(type)
	{
		case 0:
			drawO(m1preboxX+UNITLENGTH+2,m1preboxY+2*UNITLENGTH);
			break;
		case 1:
			if (status==0) drawI(m1preboxX+2,m1preboxY+3*UNITLENGTH,0);
			else drawI(m1preboxX+UNITLENGTH+2,m1preboxY+UNITLENGTH,1);
			break;
		case 2:
			if (status==0||status==2) drawL(m1preboxX+UNITLENGTH+2,m1preboxY+UNITLENGTH,status);
			else drawL(m1preboxX+UNITLENGTH+2,m1preboxY+2*UNITLENGTH,status);
			break;
		case 3:
			if (status==0||status==2) drawFL(m1preboxX+UNITLENGTH+2,m1preboxY+UNITLENGTH,status);
			else drawFL(m1preboxX+UNITLENGTH+2,m1preboxY+2*UNITLENGTH,status);
			break;
		case 4:
			if (status==1||status==3) drawT(m1preboxX+UNITLENGTH+2,m1preboxY+UNITLENGTH,status);
			else drawT(m1preboxX+UNITLENGTH+2,m1preboxY+2*UNITLENGTH,status);
			break;
		case 5:
			if (status==0) drawZ(m1preboxX+UNITLENGTH+2,m1preboxY+2*UNITLENGTH,0);
			else drawZ(m1preboxX+UNITLENGTH+2,m1preboxY+UNITLENGTH,1);
			break;
		case 6:
			if (status==0) drawFZ(m1preboxX+UNITLENGTH+2,m1preboxY+2*UNITLENGTH,0);
			else drawFZ(m1preboxX+UNITLENGTH+2,m1preboxY+UNITLENGTH,1);
			break;
		default:
			break;
	}
	return;
}

void m2clearp(void)											//玩家2清除预测框
{
	int poly[8];
	setcolor(0);
	setlinestyle(0,0,1);
	setfillstyle(1,0);
	poly[0]=m2preboxX+2;
	poly[1]=m2preboxY+2;
	poly[2]=m2preboxX+2;
	poly[3]=m2preboxY+6*UNITLENGTH-2;
	poly[4]=m2preboxX+4*UNITLENGTH+2;
	poly[5]=m2preboxY+6*UNITLENGTH-2;
	poly[6]=m2preboxX+4*UNITLENGTH+2;
	poly[7]=m2preboxY+2;
	fillpoly(4,poly);
	return;
}

void m2fillp(int type,int status)								//玩家2填充预测框
{
	switch(type)
	{
		case 0:
			drawO(m2preboxX+UNITLENGTH+2,m2preboxY+2*UNITLENGTH);
			break;
		case 1:
			if (status==0) drawI(m2preboxX+2,m2preboxY+3*UNITLENGTH,0);
			else drawI(m2preboxX+UNITLENGTH+2,m2preboxY+UNITLENGTH,1);
			break;
		case 2:
			if (status==0||status==2) drawL(m2preboxX+UNITLENGTH+2,m2preboxY+UNITLENGTH,status);
			else drawL(m2preboxX+UNITLENGTH+2,m2preboxY+2*UNITLENGTH,status);
			break;
		case 3:
			if (status==0||status==2) drawFL(m2preboxX+UNITLENGTH+2,m2preboxY+UNITLENGTH,status);
			else drawFL(m2preboxX+UNITLENGTH+2,m2preboxY+2*UNITLENGTH,status);
			break;
		case 4:
			if (status==1||status==3) drawT(m2preboxX+UNITLENGTH+2,m2preboxY+UNITLENGTH,status);
			else drawT(m2preboxX+UNITLENGTH+2,m2preboxY+2*UNITLENGTH,status);
			break;
		case 5:
			if (status==0) drawZ(m2preboxX+UNITLENGTH+2,m2preboxY+2*UNITLENGTH,0);
			else drawZ(m2preboxX+UNITLENGTH+2,m2preboxY+UNITLENGTH,1);
			break;
		case 6:
			if (status==0) drawFZ(m2preboxX+UNITLENGTH+2,m2preboxY+2*UNITLENGTH,0);
			else drawFZ(m2preboxX+UNITLENGTH+2,m2preboxY+UNITLENGTH,1);
			break;
		default:
			break;
	}
	return;
}

void m1adjust(int x,int y,int type,int status)				//玩家1调整activeX、activeY的值  x,y为左上角模拟坐标 
{
	switch(type)
	{
		case 0:
			m1activeX[0]=x;
			m1activeY[0]=y;
			m1activeX[1]=x+1;
			m1activeY[1]=y;
			m1activeX[2]=x;
			m1activeY[2]=y+1;
			m1activeX[3]=x+1;
			m1activeY[3]=y+1;
			break;
		case 1:
			if (status==0)
			{
				m1activeX[0]=x;
				m1activeY[0]=y;
				m1activeX[1]=x+1;
				m1activeY[1]=y;
				m1activeX[2]=x+2;
				m1activeY[2]=y;
				m1activeX[3]=x+3;
				m1activeY[3]=y;
			}
			else 
			{
				m1activeX[0]=x;
				m1activeY[0]=y;
				m1activeX[1]=x;
				m1activeY[1]=y+1;
				m1activeX[2]=x;
				m1activeY[2]=y+2;
				m1activeX[3]=x;
				m1activeY[3]=y+3;
			}
			break;
		case 2:
			switch(status)
			{
				case 0:
					m1activeX[0]=x;
					m1activeY[0]=y;
					m1activeX[1]=x;
					m1activeY[1]=y+1;
					m1activeX[2]=x;
					m1activeY[2]=y+2;
					m1activeX[3]=x+1;
					m1activeY[3]=y+2;
					break;
				case 1:
					m1activeX[0]=x;
					m1activeY[0]=y+1;
					m1activeX[1]=x+1;
					m1activeY[1]=y+1;
					m1activeX[2]=x+2;
					m1activeY[2]=y+1;
					m1activeX[3]=x+2;
					m1activeY[3]=y;
					break;
				case 2:
					m1activeX[0]=x;
					m1activeY[0]=y;
					m1activeX[1]=x+1;
					m1activeY[1]=y;
					m1activeX[2]=x+1;
					m1activeY[2]=y+1;
					m1activeX[3]=x+1;
					m1activeY[3]=y+2;
					break;
				case 3:
					m1activeX[0]=x;
					m1activeY[0]=y;
					m1activeX[1]=x+1;
					m1activeY[1]=y;
					m1activeX[2]=x+2;
					m1activeY[2]=y;
					m1activeX[3]=x;
					m1activeY[3]=y+1;
					break;
		
				default:
					break;
			}
			break;
		case 3:
			switch(status)
			{
				case 0:
					m1activeX[0]=x+1;
					m1activeY[0]=y;
					m1activeX[1]=x+1;
					m1activeY[1]=y+1;
					m1activeX[2]=x+1;
					m1activeY[2]=y+2;
					m1activeX[3]=x;
					m1activeY[3]=y+2;
					break;
				case 1:
					m1activeX[0]=x;
					m1activeY[0]=y;
					m1activeX[1]=x+1;
					m1activeY[1]=y;
					m1activeX[2]=x+2;
					m1activeY[2]=y;
					m1activeX[3]=x+2;
					m1activeY[3]=y+1;
					break;
				case 2:
					m1activeX[0]=x;
					m1activeY[0]=y;
					m1activeX[1]=x+1;
					m1activeY[1]=y;
					m1activeX[2]=x;
					m1activeY[2]=y+1;
					m1activeX[3]=x;
					m1activeY[3]=y+2;
					break;
				case 3:
					m1activeX[0]=x;
					m1activeY[0]=y;
					m1activeX[1]=x;
					m1activeY[1]=y+1;
					m1activeX[2]=x+1;
					m1activeY[2]=y+1;
					m1activeX[3]=x+2;
					m1activeY[3]=y+1;
					break;
				default:
					break;
			}
			break;
		case 4:
			switch(status)
			{
				case 0:
					m1activeX[0]=x;
					m1activeY[0]=y;
					m1activeX[1]=x+1;
					m1activeY[1]=y;
					m1activeX[2]=x+2;
					m1activeY[2]=y;
					m1activeX[3]=x+1;
					m1activeY[3]=y+1;
					break;
				case 1:
					m1activeX[0]=x;
					m1activeY[0]=y;
					m1activeX[1]=x;
					m1activeY[1]=y+1;
					m1activeX[2]=x;
					m1activeY[2]=y+2;
					m1activeX[3]=x+1;
					m1activeY[3]=y+1;
					break;
				case 2:
					m1activeX[0]=x;
					m1activeY[0]=y+1;
					m1activeX[1]=x+1;
					m1activeY[1]=y+1;
					m1activeX[2]=x+2;
					m1activeY[2]=y+1;
					m1activeX[3]=x+1;
					m1activeY[3]=y;
					break;
				case 3:
					m1activeX[0]=x+1;
					m1activeY[0]=y;
					m1activeX[1]=x+1;
					m1activeY[1]=y+1;
					m1activeX[2]=x+1;
					m1activeY[2]=y+2;
					m1activeX[3]=x;
					m1activeY[3]=y+1;
					break;
				default:
					break;
			}
			break;
		case 5:
			if (status==0)
			{
				m1activeX[0]=x;
				m1activeY[0]=y;
				m1activeX[1]=x+1;
				m1activeY[1]=y;
				m1activeX[2]=x+1;
				m1activeY[2]=y+1;
				m1activeX[3]=x+2;
				m1activeY[3]=y+1;
			}
			else 
			{
				m1activeX[0]=x+1;
				m1activeY[0]=y;
				m1activeX[1]=x;
				m1activeY[1]=y+1;
				m1activeX[2]=x+1;
				m1activeY[2]=y+1;
				m1activeX[3]=x;
				m1activeY[3]=y+2;
			}
			break;
		case 6:
			if (status==0)
			{
				m1activeX[0]=x;
				m1activeY[0]=y+1;
				m1activeX[1]=x+1;
				m1activeY[1]=y;
				m1activeX[2]=x+1;
				m1activeY[2]=y+1;
				m1activeX[3]=x+2;
				m1activeY[3]=y;
			}
			else 
			{
				m1activeX[0]=x;
				m1activeY[0]=y;
				m1activeX[1]=x;
				m1activeY[1]=y+1;
				m1activeX[2]=x+1;
				m1activeY[2]=y+1;
				m1activeX[3]=x+1;
				m1activeY[3]=y+2;
			}
			break;
		default:
			break;
	}
	return;
}

void m2adjust(int x,int y,int type,int status)				//玩家2调整m2activeX、m2activeY的值  x,y为左上角模拟坐标 
{
	switch(type)
	{
		case 0:
			m2activeX[0]=x;
			m2activeY[0]=y;
			m2activeX[1]=x+1;
			m2activeY[1]=y;
			m2activeX[2]=x;
			m2activeY[2]=y+1;
			m2activeX[3]=x+1;
			m2activeY[3]=y+1;
			break;
		case 1:
			if (status==0)
			{
				m2activeX[0]=x;
				m2activeY[0]=y;
				m2activeX[1]=x+1;
				m2activeY[1]=y;
				m2activeX[2]=x+2;
				m2activeY[2]=y;
				m2activeX[3]=x+3;
				m2activeY[3]=y;
			}
			else 
			{
				m2activeX[0]=x;
				m2activeY[0]=y;
				m2activeX[1]=x;
				m2activeY[1]=y+1;
				m2activeX[2]=x;
				m2activeY[2]=y+2;
				m2activeX[3]=x;
				m2activeY[3]=y+3;
			}
			break;
		case 2:
			switch(status)
			{
				case 0:
					m2activeX[0]=x;
					m2activeY[0]=y;
					m2activeX[1]=x;
					m2activeY[1]=y+1;
					m2activeX[2]=x;
					m2activeY[2]=y+2;
					m2activeX[3]=x+1;
					m2activeY[3]=y+2;
					break;
				case 1:
					m2activeX[0]=x;
					m2activeY[0]=y+1;
					m2activeX[1]=x+1;
					m2activeY[1]=y+1;
					m2activeX[2]=x+2;
					m2activeY[2]=y+1;
					m2activeX[3]=x+2;
					m2activeY[3]=y;
					break;
				case 2:
					m2activeX[0]=x;
					m2activeY[0]=y;
					m2activeX[1]=x+1;
					m2activeY[1]=y;
					m2activeX[2]=x+1;
					m2activeY[2]=y+1;
					m2activeX[3]=x+1;
					m2activeY[3]=y+2;
					break;
				case 3:
					m2activeX[0]=x;
					m2activeY[0]=y;
					m2activeX[1]=x+1;
					m2activeY[1]=y;
					m2activeX[2]=x+2;
					m2activeY[2]=y;
					m2activeX[3]=x;
					m2activeY[3]=y+1;
					break;
		
				default:
					break;
			}
			break;
		case 3:
			switch(status)
			{
				case 0:
					m2activeX[0]=x+1;
					m2activeY[0]=y;
					m2activeX[1]=x+1;
					m2activeY[1]=y+1;
					m2activeX[2]=x+1;
					m2activeY[2]=y+2;
					m2activeX[3]=x;
					m2activeY[3]=y+2;
					break;
				case 1:
					m2activeX[0]=x;
					m2activeY[0]=y;
					m2activeX[1]=x+1;
					m2activeY[1]=y;
					m2activeX[2]=x+2;
					m2activeY[2]=y;
					m2activeX[3]=x+2;
					m2activeY[3]=y+1;
					break;
				case 2:
					m2activeX[0]=x;
					m2activeY[0]=y;
					m2activeX[1]=x+1;
					m2activeY[1]=y;
					m2activeX[2]=x;
					m2activeY[2]=y+1;
					m2activeX[3]=x;
					m2activeY[3]=y+2;
					break;
				case 3:
					m2activeX[0]=x;
					m2activeY[0]=y;
					m2activeX[1]=x;
					m2activeY[1]=y+1;
					m2activeX[2]=x+1;
					m2activeY[2]=y+1;
					m2activeX[3]=x+2;
					m2activeY[3]=y+1;
					break;
				default:
					break;
			}
			break;
		case 4:
			switch(status)
			{
				case 0:
					m2activeX[0]=x;
					m2activeY[0]=y;
					m2activeX[1]=x+1;
					m2activeY[1]=y;
					m2activeX[2]=x+2;
					m2activeY[2]=y;
					m2activeX[3]=x+1;
					m2activeY[3]=y+1;
					break;
				case 1:
					m2activeX[0]=x;
					m2activeY[0]=y;
					m2activeX[1]=x;
					m2activeY[1]=y+1;
					m2activeX[2]=x;
					m2activeY[2]=y+2;
					m2activeX[3]=x+1;
					m2activeY[3]=y+1;
					break;
				case 2:
					m2activeX[0]=x;
					m2activeY[0]=y+1;
					m2activeX[1]=x+1;
					m2activeY[1]=y+1;
					m2activeX[2]=x+2;
					m2activeY[2]=y+1;
					m2activeX[3]=x+1;
					m2activeY[3]=y;
					break;
				case 3:
					m2activeX[0]=x+1;
					m2activeY[0]=y;
					m2activeX[1]=x+1;
					m2activeY[1]=y+1;
					m2activeX[2]=x+1;
					m2activeY[2]=y+2;
					m2activeX[3]=x;
					m2activeY[3]=y+1;
					break;
				default:
					break;
			}
			break;
		case 5:
			if (status==0)
			{
				m2activeX[0]=x;
				m2activeY[0]=y;
				m2activeX[1]=x+1;
				m2activeY[1]=y;
				m2activeX[2]=x+1;
				m2activeY[2]=y+1;
				m2activeX[3]=x+2;
				m2activeY[3]=y+1;
			}
			else 
			{
				m2activeX[0]=x+1;
				m2activeY[0]=y;
				m2activeX[1]=x;
				m2activeY[1]=y+1;
				m2activeX[2]=x+1;
				m2activeY[2]=y+1;
				m2activeX[3]=x;
				m2activeY[3]=y+2;
			}
			break;
		case 6:
			if (status==0)
			{
				m2activeX[0]=x;
				m2activeY[0]=y+1;
				m2activeX[1]=x+1;
				m2activeY[1]=y;
				m2activeX[2]=x+1;
				m2activeY[2]=y+1;
				m2activeX[3]=x+2;
				m2activeY[3]=y;
			}
			else 
			{
				m2activeX[0]=x;
				m2activeY[0]=y;
				m2activeX[1]=x;
				m2activeY[1]=y+1;
				m2activeX[2]=x+1;
				m2activeY[2]=y+1;
				m2activeX[3]=x+1;
				m2activeY[3]=y+2;
			}
			break;
		default:
			break;
	}
	return;
}


void m1addline(void)											//玩家1补充边线
{
	int i,j;
	for (i=0;i<=11;i++)
		for (j=0;j<=22;j++)
			if (m1sg[i][j]>0)
			{
				setcolor(15);
				setlinestyle(0,0,1);
				rectangle(m1transX(i),m1transY(j),m1transX(i+1),m1transY(j+1));
			}
	return;
}

void m2addline(void)											//玩家2补充边线
{
	int i,j;
	for (i=0;i<=11;i++)
		for (j=0;j<=22;j++)
			if (m2sg[i][j]>0)
			{
				setcolor(15);
				setlinestyle(0,0,1);
				rectangle(m2transX(i),m2transY(j),m2transX(i+1),m2transY(j+1));
			}
	return;
}

int m1can(int o)												//玩家1判断操作是否可行 o表示操作 0:左移 1:右移 2:下移 3:不
{
	int i;
	switch(o)
	{
		case 0:
			for (i=0;i<=3;i++)
				if (m1activeX[i]-1<0) return 0;
				else if (m1sg[m1activeX[i]-1][m1activeY[i]]>0) return 0;
			break;
		case 1:
			for (i=0;i<=3;i++)
				if (m1activeX[i]+1>11) return 0;
				else if (m1sg[m1activeX[i]+1][m1activeY[i]]>0) return 0;
			break;
		case 2:
			for (i=0;i<=3;i++)
				if (m1activeY[i]+1>22) return 0;
				else if (m1sg[m1activeX[i]][m1activeY[i]+1]>0) return 0;
			break;
		case 3:
			for (i=0;i<=3;i++)
				if (m1activeX[i]<0||m1activeX[i]>11||m1activeY[i]<0||m1activeY[i]>22) return 0;
				else if (m1sg[m1activeX[i]][m1activeY[i]]>0) return 0;
			break;
		default:
			break;
	}
	return 1;
}

int m2can(int o)												//玩家2判断操作是否可行 o表示操作 0:左移 1:右移 2:下移 3:不
{
	int i;
	switch(o)
	{
		case 0:
			for (i=0;i<=3;i++)
				if (m2activeX[i]-1<0) return 0;
				else if (m2sg[m2activeX[i]-1][m2activeY[i]]>0) return 0;
			break;
		case 1:
			for (i=0;i<=3;i++)
				if (m2activeX[i]+1>11) return 0;
				else if (m2sg[m2activeX[i]+1][m2activeY[i]]>0) return 0;
			break;
		case 2:
			for (i=0;i<=3;i++)
				if (m2activeY[i]+1>22) return 0;
				else if (m2sg[m2activeX[i]][m2activeY[i]+1]>0) return 0;
			break;
		case 3:
			for (i=0;i<=3;i++)
				if (m2activeX[i]<0||m2activeX[i]>11||m2activeY[i]<0||m2activeY[i]>22) return 0;
				else if (m2sg[m2activeX[i]][m2activeY[i]]>0) return 0;
			break;
		default:
			break;
	}
	return 1;
}

int m1dispel(int row)											//玩家1满行消除
{
	int i,j,k,a;
	a=1;
	for (i=0;i<=11;i++)
		if (m1sg[i][row]==0) a=0;
	if (a) 
	{
		
			if (com)
			{
				for (j=0;j<=11;j++)
					if (m2sg[j][0]>0) over=2;
				for (j=0;j<=3;j++) 
					if (m1activeY[j]==row) m1sg[m1activeX[j]][row]=0;
				for (k=0;k<22;k++)
					for (j=0;j<=11;j++) m2sg[j][k]=m2sg[j][k+1];
				for (j=0;j<=11;j++) m2sg[j][22]=m1sg[j][row];
				for (i=0;i<=22;i++)
					m2scanrow(i);
				m2addline();
			}

			
		for (i=0;i<=11;i++) m1sg[i][row]=0;
		return 1;
	}
	else return 0;
}

int m1drop()											//玩家1落下方块   返回落下行数
{
	int i,j,a,k,t,s;
	s=0;
	t=0;
	a=1;
	while (a)
	{
		a=1;
		for (j=0;j<=11;j++)
			if (m1sg[j][t]>0) a=0;
		t++;
	}
	t--;
	for (i=t;i<=22;i++)
	{
		a=1;
		for (j=0;j<=11;j++)
			if (m1sg[j][i]>0) a=0;
		if (a) 
		{
			s++;
			for (k=i;k>=t;k--)
			{
				for (j=0;j<=11;j++)	m1sg[j][k]=m1sg[j][k-1];
				m1scanrow(k);
			}
		}
	}
	return s;
}

void m1scanrow(int row)										//玩家1扫描一行并描绘
{
	int i;
	for (i=0;i<=11;i++) 
	{
		setc(m1sg[i][row]);
		if (m1sg[i][row]==0) clearaunit(m1transX(i),m1transY(row));
		else drawaunit(m1transX(i),m1transY(row));
	}
	return;
}

int m2dispel(int row)											//玩家2满行消除
{
	int i,a,j,k;
	a=1;
	for (i=0;i<=11;i++)
		if (m2sg[i][row]==0) a=0;
	if (a) 
	{
		
		
		
		if (com)
			{
				
				for (j=0;j<=11;j++)
					if (m1sg[j][0]>0) over=2;
				for (j=0;j<=3;j++) 
					if (m2activeY[j]==row) m2sg[m2activeX[j]][row]=0;
				for (k=0;k<22;k++)
					for (j=0;j<=11;j++) m1sg[j][k]=m1sg[j][k+1];
				for (j=0;j<=11;j++) m1sg[j][22]=m2sg[j][row];
				for (i=0;i<=22;i++)
					m1scanrow(i);
				m1addline();
			}

			
			
			
		for (i=0;i<=11;i++) m2sg[i][row]=0;
		return 1;
	}
	else return 0;
}

int m2drop()												//玩家2落下方块   返回落下行数
{
	int i,j,a,k,t,s;
	s=0;
	t=0;
	a=1;
	while (a)
	{
		a=1;
		for (j=0;j<=11;j++)
			if (m2sg[j][t]>0) a=0;
		t++;
	}
	t--;
	for (i=t;i<=22;i++)
	{
		a=1;
		for (j=0;j<=11;j++)
			if (m2sg[j][i]>0) a=0;
		if (a) 
		{
			s++;
			for (k=i;k>=t;k--)
			{
				for (j=0;j<=11;j++)	m2sg[j][k]=m2sg[j][k-1];
				m2scanrow(k);
			}
		}
	}
	return s;
}

void m2scanrow(int row)										//玩家2扫描一行并描绘
{
	int i;
	for (i=0;i<=11;i++) 
	{
		setc(m2sg[i][row]);
		if (m2sg[i][row]==0) clearaunit(m2transX(i),m2transY(row));
		else drawaunit(m2transX(i),m2transY(row));
	}
	return;
}

void np1(int x,int y)
{
	int poly[8];
	poly[0]=x;
	poly[1]=y;
	poly[2]=x+2*NL;
	poly[3]=y+2*NL;
	poly[4]=x+8*NL;
	poly[5]=y+2*NL;
	poly[6]=x+10*NL;
	poly[7]=y;
	fillpoly(4,poly);
	return;
}

void np2(int x,int y)
{
	int poly[8];
	poly[0]=x;
	poly[1]=y;
	poly[2]=x+2*NL;
	poly[3]=y+2*NL;
	poly[4]=x+2*NL;
	poly[5]=y+7*NL;
	poly[6]=x;
	poly[7]=y+9*NL;
	fillpoly(4,poly);
	return;
}

void np3(int x,int y)
{
	int poly[8];
	poly[0]=x;
	poly[1]=y;
	poly[2]=x;
	poly[3]=y+5*NL;
	poly[4]=x+2*NL;
	poly[5]=y+7*NL;
	poly[6]=x+2*NL;
	poly[7]=y-2*NL;
	fillpoly(4,poly);
	return;
}

void np4(int x,int y)
{
	int poly[8];
	poly[0]=x;
	poly[1]=y;
	poly[2]=x+2*NL;
	poly[3]=y-2*NL;
	poly[4]=x+8*NL;
	poly[5]=y-2*NL;
	poly[6]=x+10*NL;
	poly[7]=y;
	fillpoly(4,poly);
	return;
}

void np5(int x,int y)
{
	int poly[12];
	poly[0]=x;
	poly[1]=y;
	poly[2]=x+2*NL;
	poly[3]=y-1*NL;
	poly[4]=x+6*NL;
	poly[5]=y-1*NL;
	poly[6]=x+8*NL;
	poly[7]=y;
	poly[8]=x+6*NL;
	poly[9]=y+1*NL;
	poly[10]=x+2*NL;
	poly[11]=y+1*NL;
	fillpoly(6,poly);
	return;
}

void n8(int x,int y,int color)
{
	setcolor(color);
	setlinestyle(0,0,1);
	setfillstyle(1,color);
	np1(x,y);
	np2(x-1*NL,y+2*NL);
	np3(x+9*NL,y+4*NL);
	np5(x+1*NL,y+12*NL);
	np2(x-1*NL,y+13*NL);
	np3(x+9*NL,y+15*NL);
	np4(x,y+24*NL);
	return;
}

void n0(int x,int y,int color)
{
	setcolor(color);
	setlinestyle(0,0,1);
	setfillstyle(1,color);
	np1(x,y);
	np2(x-1*NL,y+2*NL);
	np3(x+9*NL,y+4*NL);
	//np5(x+1*NL,y+12*NL);
	np2(x-1*NL,y+13*NL);
	np3(x+9*NL,y+15*NL);
	np4(x,y+24*NL);
	return;
}

void n1(int x,int y,int color)
{
	setcolor(color);
	setlinestyle(0,0,1);
	setfillstyle(1,color);
	//np1(x,y);
	//np2(x-1*NL,y+2*NL);
	np3(x+9*NL,y+4*NL);
	//np5(x+1*NL,y+12*NL);
	//np2(x-1*NL,y+13*NL);
	np3(x+9*NL,y+15*NL);
	//np4(x,y+24*NL);
	return;
}

void n2(int x,int y,int color)
{
	setcolor(color);
	setlinestyle(0,0,1);
	setfillstyle(1,color);
	np1(x,y);
	//np2(x-1*NL,y+2*NL);
	np3(x+9*NL,y+4*NL);
	np5(x+1*NL,y+12*NL);
	np2(x-1*NL,y+13*NL);
	//np3(x+9*NL,y+15*NL);
	np4(x,y+24*NL);
	return;
}

void n3(int x,int y,int color)
{
	setcolor(color);
	setlinestyle(0,0,1);
	setfillstyle(1,color);
	np1(x,y);
	//np2(x-1*NL,y+2*NL);
	np3(x+9*NL,y+4*NL);
	np5(x+1*NL,y+12*NL);
	//np2(x-1*NL,y+13*NL);
	np3(x+9*NL,y+15*NL);
	np4(x,y+24*NL);
}

void n4(int x,int y,int color)
{
	setcolor(color);
	setlinestyle(0,0,1);
	setfillstyle(1,color);
	//np1(x,y);
	np2(x-1*NL,y+2*NL);
	np3(x+9*NL,y+4*NL);
	np5(x+1*NL,y+12*NL);
	//np2(x-1*NL,y+13*NL);
	np3(x+9*NL,y+15*NL);
	//np4(x,y+24*NL);
	return;
}

void n5(int x,int y,int color)
{
	setcolor(color);
	setlinestyle(0,0,1);
	setfillstyle(1,color);
	np1(x,y);
	np2(x-1*NL,y+2*NL);
	//np3(x+9*NL,y+4*NL);
	np5(x+1*NL,y+12*NL);
	//np2(x-1*NL,y+13*NL);
	np3(x+9*NL,y+15*NL);
	np4(x,y+24*NL);
	return;
}

void n6(int x,int y,int color)
{
	setcolor(color);
	setlinestyle(0,0,1);
	setfillstyle(1,color);
	np1(x,y);
	np2(x-1*NL,y+2*NL);
	//np3(x+9*NL,y+4*NL);
	np5(x+1*NL,y+12*NL);
	np2(x-1*NL,y+13*NL);
	np3(x+9*NL,y+15*NL);
	np4(x,y+24*NL);
	return;
}

void n7(int x,int y,int color)
{
	setcolor(color);
	setlinestyle(0,0,1);
	setfillstyle(1,color);
	np1(x,y);
	//np2(x-1*NL,y+2*NL);
	np3(x+9*NL,y+4*NL);
	//np5(x+1*NL,y+12*NL);
	//np2(x-1*NL,y+13*NL);
	np3(x+9*NL,y+15*NL);
	//np4(x,y+24*NL);
	return;
}

void n9(int x,int y,int color)
{
	setcolor(color);
	setlinestyle(0,0,1);
	setfillstyle(1,color);
	np1(x,y);
	np2(x-1*NL,y+2*NL);
	np3(x+9*NL,y+4*NL);
	np5(x+1*NL,y+12*NL);
	//np2(x-1*NL,y+13*NL);
	np3(x+9*NL,y+15*NL);
	np4(x,y+24*NL);
	return;
}

void account(long score)											//计分
{
	int a[10];
	int i,j,k=0;
	int poly[8];
	setcolor(0);
	setlinestyle(0,0,0);
	setfillstyle(1,0);
	poly[0]=scoreboxX-1;
	poly[1]=scoreboxY;
	poly[2]=scoreboxX-1;
	poly[3]=scoreboxY+25;
	poly[4]=scoreboxX+numberwidth*10;
	poly[5]=scoreboxY+25;
	poly[6]=scoreboxX+numberwidth*10;
	poly[7]=scoreboxY;
	fillpoly(4,poly);
	
	while (score>=10)
	{
		a[k++]=score%10;
		score/=10;
	}
	a[k]=score;
	for (i=k;i>=0;i--)
	switch(a[i])
	{
		case 0:
			n0(scoreboxX+numberwidth*(k-i),scoreboxY,numbercolor);
			break;
		case 1:
			n1(scoreboxX+numberwidth*(k-i),scoreboxY,numbercolor);
			break;
		case 2:
			n2(scoreboxX+numberwidth*(k-i),scoreboxY,numbercolor);
			break;
		case 3:
			n3(scoreboxX+numberwidth*(k-i),scoreboxY,numbercolor);
			break;
		case 4:
			n4(scoreboxX+numberwidth*(k-i),scoreboxY,numbercolor);
			break;
		case 5:
			n5(scoreboxX+numberwidth*(k-i),scoreboxY,numbercolor);
			break;
		case 6:
			n6(scoreboxX+numberwidth*(k-i),scoreboxY,numbercolor);
			break;
		case 7:
			n7(scoreboxX+numberwidth*(k-i),scoreboxY,numbercolor);
			break;
		case 8:
			n8(scoreboxX+numberwidth*(k-i),scoreboxY,numbercolor);
			break;
		case 9:
			n9(scoreboxX+numberwidth*(k-i),scoreboxY,numbercolor);
			break;
		default:
			break;
	}
	return;
}
	
void acline(int line)											     //统计行数
{
	int a[10];
	int i,j,k=0;
	int poly[8];
	setcolor(0);
	setlinestyle(0,0,0);
	setfillstyle(1,0);
	poly[0]=lineboxX-1;
	poly[1]=lineboxY;
	poly[2]=lineboxX-1;
	poly[3]=lineboxY+25;
	poly[4]=lineboxX+numberwidth*10;
	poly[5]=lineboxY+25;
	poly[6]=lineboxX+numberwidth*10;
	poly[7]=lineboxY;
	fillpoly(4,poly);
	
	while (line>=10)
	{
		a[k++]=line%10;
		line/=10;
	}
	a[k]=line;
	for (i=k;i>=0;i--)
	switch(a[i])
	{
		case 0:
			n0(lineboxX+numberwidth*(k-i),lineboxY,numbercolor);
			break;
		case 1:
			n1(lineboxX+numberwidth*(k-i),lineboxY,numbercolor);
			break;
		case 2:
			n2(lineboxX+numberwidth*(k-i),lineboxY,numbercolor);
			break;
		case 3:
			n3(lineboxX+numberwidth*(k-i),lineboxY,numbercolor);
			break;
		case 4:
			n4(lineboxX+numberwidth*(k-i),lineboxY,numbercolor);
			break;
		case 5:
			n5(lineboxX+numberwidth*(k-i),lineboxY,numbercolor);
			break;
		case 6:
			n6(lineboxX+numberwidth*(k-i),lineboxY,numbercolor);
			break;
		case 7:
			n7(lineboxX+numberwidth*(k-i),lineboxY,numbercolor);
			break;
		case 8:
			n8(lineboxX+numberwidth*(k-i),lineboxY,numbercolor);
			break;
		case 9:
			n9(lineboxX+numberwidth*(k-i),lineboxY,numbercolor);
			break;
		default:
			break;
	}
	return;
}


void m1account(int score)										//玩家1计分
{
	int a[10];
	int i,j,k=0;
	int poly[8];
	setcolor(0);
	setlinestyle(0,0,0);
	setfillstyle(1,0);
	poly[0]=m1scoreboxX-1;
	poly[1]=m1scoreboxY;
	poly[2]=m1scoreboxX-1;
	poly[3]=m1scoreboxY+25;
	poly[4]=m1scoreboxX+numberwidth*7;
	poly[5]=m1scoreboxY+25;
	poly[6]=m1scoreboxX+numberwidth*7;
	poly[7]=m1scoreboxY;
	fillpoly(4,poly);
	
	while (score>=10)
	{
		a[k++]=score%10;
		score/=10;
	}
	a[k]=score;
	for (i=k;i>=0;i--)
	switch(a[i])
	{
		case 0:
			n0(m1scoreboxX+numberwidth*(k-i),m1scoreboxY,numbercolor);
			break;
		case 1:
			n1(m1scoreboxX+numberwidth*(k-i),m1scoreboxY,numbercolor);
			break;
		case 2:
			n2(m1scoreboxX+numberwidth*(k-i),m1scoreboxY,numbercolor);
			break;
		case 3:
			n3(m1scoreboxX+numberwidth*(k-i),m1scoreboxY,numbercolor);
			break;
		case 4:
			n4(m1scoreboxX+numberwidth*(k-i),m1scoreboxY,numbercolor);
			break;
		case 5:
			n5(m1scoreboxX+numberwidth*(k-i),m1scoreboxY,numbercolor);
			break;
		case 6:
			n6(m1scoreboxX+numberwidth*(k-i),m1scoreboxY,numbercolor);
			break;
		case 7:
			n7(m1scoreboxX+numberwidth*(k-i),m1scoreboxY,numbercolor);
			break;
		case 8:
			n8(m1scoreboxX+numberwidth*(k-i),m1scoreboxY,numbercolor);
			break;
		case 9:
			n9(m1scoreboxX+numberwidth*(k-i),m1scoreboxY,numbercolor);
			break;
		default:
			break;
	}
	return;
}
	
void m1acline(int line)											//玩家1统计行数
{
	int a[10];
	int i,j,k=0;
	int poly[8];
	setcolor(0);
	setlinestyle(0,0,0);
	setfillstyle(1,0);
	poly[0]=m1lineboxX-1;
	poly[1]=m1lineboxY;
	poly[2]=m1lineboxX-1;
	poly[3]=m1lineboxY+25;
	poly[4]=m1lineboxX+numberwidth*7;
	poly[5]=m1lineboxY+25;
	poly[6]=m1lineboxX+numberwidth*7;
	poly[7]=m1lineboxY;
	fillpoly(4,poly);
	
	while (line>=10)
	{
		a[k++]=line%10;
		line/=10;
	}
	a[k]=line;
	for (i=k;i>=0;i--)
	switch(a[i])
	{
		case 0:
			n0(m1lineboxX+numberwidth*(k-i),m1lineboxY,numbercolor);
			break;
		case 1:
			n1(m1lineboxX+numberwidth*(k-i),m1lineboxY,numbercolor);
			break;
		case 2:
			n2(m1lineboxX+numberwidth*(k-i),m1lineboxY,numbercolor);
			break;
		case 3:
			n3(m1lineboxX+numberwidth*(k-i),m1lineboxY,numbercolor);
			break;
		case 4:
			n4(m1lineboxX+numberwidth*(k-i),m1lineboxY,numbercolor);
			break;
		case 5:
			n5(m1lineboxX+numberwidth*(k-i),m1lineboxY,numbercolor);
			break;
		case 6:
			n6(m1lineboxX+numberwidth*(k-i),m1lineboxY,numbercolor);
			break;
		case 7:
			n7(m1lineboxX+numberwidth*(k-i),m1lineboxY,numbercolor);
			break;
		case 8:
			n8(m1lineboxX+numberwidth*(k-i),m1lineboxY,numbercolor);
			break;
		case 9:
			n9(m1lineboxX+numberwidth*(k-i),m1lineboxY,numbercolor);
			break;
		default:
			break;
	}
	return;
}

void m2account(int score)										//玩家2计分
{
	int a[10];
	int i,j,k=0;
	int poly[8];
	setcolor(0);
	setlinestyle(0,0,0);
	setfillstyle(1,0);
	poly[0]=m2scoreboxX-1;
	poly[1]=m2scoreboxY;
	poly[2]=m2scoreboxX-1;
	poly[3]=m2scoreboxY+25;
	poly[4]=m2scoreboxX+numberwidth*7;
	poly[5]=m2scoreboxY+25;
	poly[6]=m2scoreboxX+numberwidth*7;
	poly[7]=m2scoreboxY;
	fillpoly(4,poly);
	
	while (score>=10)
	{
		a[k++]=score%10;
		score/=10;
	}
	a[k]=score;
	for (i=k;i>=0;i--)
	switch(a[i])
	{
		case 0:
			n0(m2scoreboxX+numberwidth*(k-i),m2scoreboxY,numbercolor);
			break;
		case 1:
			n1(m2scoreboxX+numberwidth*(k-i),m2scoreboxY,numbercolor);
			break;
		case 2:
			n2(m2scoreboxX+numberwidth*(k-i),m2scoreboxY,numbercolor);
			break;
		case 3:
			n3(m2scoreboxX+numberwidth*(k-i),m2scoreboxY,numbercolor);
			break;
		case 4:
			n4(m2scoreboxX+numberwidth*(k-i),m2scoreboxY,numbercolor);
			break;
		case 5:
			n5(m2scoreboxX+numberwidth*(k-i),m2scoreboxY,numbercolor);
			break;
		case 6:
			n6(m2scoreboxX+numberwidth*(k-i),m2scoreboxY,numbercolor);
			break;
		case 7:
			n7(m2scoreboxX+numberwidth*(k-i),m2scoreboxY,numbercolor);
			break;
		case 8:
			n8(m2scoreboxX+numberwidth*(k-i),m2scoreboxY,numbercolor);
			break;
		case 9:
			n9(m2scoreboxX+numberwidth*(k-i),m2scoreboxY,numbercolor);
			break;
		default:
			break;
	}
	return;
}
	
void m2acline(int line)											//玩家2统计行数
{
	int a[10];
	int i,j,k=0;
	int poly[8];
	setcolor(0);
	setlinestyle(0,0,0);
	setfillstyle(1,0);
	poly[0]=m2lineboxX-1;
	poly[1]=m2lineboxY;
	poly[2]=m2lineboxX-1;
	poly[3]=m2lineboxY+25;
	poly[4]=m2lineboxX+numberwidth*7;
	poly[5]=m2lineboxY+25;
	poly[6]=m2lineboxX+numberwidth*7;
	poly[7]=m2lineboxY;
	fillpoly(4,poly);
	
	while (line>=10)
	{
		a[k++]=line%10;
		line/=10;
	}
	a[k]=line;
	for (i=k;i>=0;i--)
	switch(a[i])
	{
		case 0:
			n0(m2lineboxX+numberwidth*(k-i),m2lineboxY,numbercolor);
			break;
		case 1:
			n1(m2lineboxX+numberwidth*(k-i),m2lineboxY,numbercolor);
			break;
		case 2:
			n2(m2lineboxX+numberwidth*(k-i),m2lineboxY,numbercolor);
			break;
		case 3:
			n3(m2lineboxX+numberwidth*(k-i),m2lineboxY,numbercolor);
			break;
		case 4:
			n4(m2lineboxX+numberwidth*(k-i),m2lineboxY,numbercolor);
			break;
		case 5:
			n5(m2lineboxX+numberwidth*(k-i),m2lineboxY,numbercolor);
			break;
		case 6:
			n6(m2lineboxX+numberwidth*(k-i),m2lineboxY,numbercolor);
			break;
		case 7:
			n7(m2lineboxX+numberwidth*(k-i),m2lineboxY,numbercolor);
			break;
		case 8:
			n8(m2lineboxX+numberwidth*(k-i),m2lineboxY,numbercolor);
			break;
		case 9:
			n9(m2lineboxX+numberwidth*(k-i),m2lineboxY,numbercolor);
			break;
		default:
			break;
	}
	return;
}

void drawbomb(int x,int y)
{
	setcolor(8);
	setfillstyle(1,8);
	setlinestyle(0,0,1);
	pieslice(x+20,y+20,0,360,10);
	setcolor(15);
	line(x+20,y+15,x+30,y);
	return;
}

void clearbomb(int x,int y)
{
	setcolor(0);
	setfillstyle(1,0);
	setlinestyle(0,0,1);
	pieslice(x+20,y+20,0,360,10);
	line(x+20,y+15,x+30,y);
	return;
}

void drawton(int x,int y)
{
	int poly[8];
	setcolor(7);
	setfillstyle(1,7);
	setlinestyle(0,0,1);
	poly[0]=x+10;
	poly[1]=y+10;
	poly[2]=x;
	poly[3]=y+60;
	poly[4]=x+40;
	poly[5]=y+60;
	poly[6]=x+30;
	poly[7]=y+10;
	fillpoly(4,poly);
	setcolor(15);
	line(x+10,y+27,x+10,y+42);
	circle(x+17,y+34,4);
	line(x+25,y+27,x+25,y+42);
	line(x+22,y+32,x+29,y+32);
	line(x+25,y+42,x+28,y+42);
	return;
}

void clearton(int x,int y)
{
	int poly[8];
	setcolor(0);
	setfillstyle(1,0);
	setlinestyle(0,0,1);
	poly[0]=x;
	poly[1]=y;
	poly[2]=x;
	poly[3]=y+61;
	poly[4]=x+40;
	poly[5]=y+61;
	poly[6]=x+40;
	poly[7]=y;
	fillpoly(4,poly);
	return;
}

void drawlighting(int x,int y)
{
	int poly[12];
	setcolor(14);
	setfillstyle(1,14);
	setlinestyle(0,0,1);
	poly[0]=x+15;
	poly[1]=y;
	poly[2]=x;
	poly[3]=y+15;
	poly[4]=x+10;
	poly[5]=y+25;
	poly[6]=x+5;
	poly[7]=y+40;
	poly[8]=x+20;
	poly[9]=y+25;
	poly[10]=x+10;
	poly[11]=y+15;
	fillpoly(6,poly);
	return;
}

void clearlighting(int x,int y)
{
	int poly[8];
	setcolor(0);
	setfillstyle(1,0);
	setlinestyle(0,0,1);
	poly[0]=x;
	poly[1]=y;
	poly[2]=x;
	poly[3]=y+41;
	poly[4]=x+20;
	poly[5]=y+41;
	poly[6]=x+20;
	poly[7]=y;
	fillpoly(4,poly);
	return;
}

void drawdropper(int x,int y)
{
	setfillstyle(1,4);
	setlinestyle(0,0,1);
	setcolor(15);
	line(x+6,y+13,x+10,y+40);
	line(x+10,y+40,x+14,y+13);
	setcolor(4);
	pieslice(x+10,y+10,0,360,7);
	return;
}

void cleardropper(int x,int y)
{
	setfillstyle(1,0);
	setlinestyle(0,0,1);
	setcolor(0);
	line(x+6,y+13,x+10,y+40);
	line(x+10,y+40,x+14,y+13);
	pieslice(x+10,y+10,0,360,7);
	return;
}

void drawlightingburst(int x,int y)
{
	int poly[8];
	setcolor(14);
	setlinestyle(0,0,1);
	setfillstyle(1,14);
	poly[0]=x;
	poly[1]=y;
	poly[2]=x;
	poly[3]=y+2*UNITLENGTH;
	poly[4]=x+12*UNITLENGTH;
	poly[5]=y+2*UNITLENGTH;
	poly[6]=x+12*UNITLENGTH;
	poly[7]=y;
	fillpoly(4,poly);
	return;
}

void clearlightingburst(int x,int y)
{
	int poly[8];
	setcolor(0);
	setlinestyle(0,0,1);
	setfillstyle(0,0);
	poly[0]=x-1;
	poly[1]=y-1;
	poly[2]=x-1;
	poly[3]=y+2*UNITLENGTH+1;
	poly[4]=x+12*UNITLENGTH+1;
	poly[5]=y+2*UNITLENGTH+1;
	poly[6]=x+12*UNITLENGTH+1;
	poly[7]=y-1;
	fillpoly(4,poly);
	return;
}

void drawa2p2(int x,int y)
{
	int poly[8];
	poly[0]=x;
	poly[1]=y;
	poly[2]=x+PL-1;
	poly[3]=y;
	poly[4]=x+PL-1;
	poly[5]=y+PL-1;
	poly[6]=x;
	poly[7]=y+PL-1;
	fillpoly(4,poly);
	return;
}

void drawalet_a(int x,int y,int color)
{
	setcolor(color);
	setlinestyle(0,0,1);
	setfillstyle(1,color);
	
	drawa2p2(x+4*PL,y+2*PL);
	drawa2p2(x+5*PL,y+2*PL);
	drawa2p2(x+3*PL,y+2*PL);
	
	drawa2p2(x+2*PL,y+3*PL);
	drawa2p2(x+6*PL,y+3*PL);
	
	drawa2p2(x+1*PL,y+4*PL);
	drawa2p2(x+6*PL,y+4*PL);
	
	drawa2p2(x+1*PL,y+5*PL);
	drawa2p2(x+6*PL,y+5*PL);
	
	drawa2p2(x+1*PL,y+6*PL);
	drawa2p2(x+6*PL,y+6*PL);
	
	drawa2p2(x+1*PL,y+7*PL);
	drawa2p2(x+6*PL,y+7*PL);
	
	drawa2p2(x+2*PL,y+8*PL);
	drawa2p2(x+6*PL,y+8*PL);
	
	drawa2p2(x+4*PL,y+9*PL);
	drawa2p2(x+5*PL,y+9*PL);
	drawa2p2(x+3*PL,y+9*PL);
	drawa2p2(x+7*PL,y+9*PL);
	
	return;
}
	
void drawalet_b(int x,int y,int color)
{
	setcolor(color);
	setlinestyle(0,0,1);
	setfillstyle(1,color);

	drawa2p2(x+2*PL,y);
	drawa2p2(x+2*PL,y+PL);
	drawa2p2(x+2*PL,y+2*PL);

	drawa2p2(x+2*PL,y+3*PL);
	drawa2p2(x+3*PL,y+3*PL);
	drawa2p2(x+4*PL,y+3*PL);

	drawa2p2(x+2*PL,y+4*PL);
	drawa2p2(x+5*PL,y+4*PL);

	drawa2p2(x+2*PL,y+5*PL);
	drawa2p2(x+6*PL,y+5*PL);

	drawa2p2(x+2*PL,y+6*PL);
	drawa2p2(x+6*PL,y+6*PL);

	drawa2p2(x+2*PL,y+7*PL);
	drawa2p2(x+6*PL,y+7*PL);

	drawa2p2(x+2*PL,y+8*PL);
	drawa2p2(x+5*PL,y+8*PL);

	drawa2p2(x+2*PL,y+9*PL);
	drawa2p2(x+4*PL,y+9*PL);
	drawa2p2(x+3*PL,y+9*PL);

	return;
}

void drawalet_c(int x,int y,int color)
{
	setcolor(color);
	setlinestyle(0,0,1);
	setfillstyle(1,color);

	drawa2p2(x+4*PL,y+PL);
	drawa2p2(x+5*PL,y+PL);
	drawa2p2(x+6*PL,y+PL);
	drawa2p2(x+7*PL,y+PL);

	drawa2p2(x+3*PL,y+2*PL);

	drawa2p2(x+2*PL,y+4*PL);

	drawa2p2(x+2*PL,y+5*PL);

	drawa2p2(x+2*PL,y+6*PL);

	drawa2p2(x+2*PL,y+7*PL);

	drawa2p2(x+2*PL,y+3*PL);

	drawa2p2(x+3*PL,y+8*PL);

	drawa2p2(x+4*PL,y+9*PL);
	drawa2p2(x+5*PL,y+9*PL);
	drawa2p2(x+6*PL,y+9*PL);
	drawa2p2(x+7*PL,y+9*PL);

	return;
}

void drawalet_d(int x,int y,int color)
{
	setcolor(color);
	setlinestyle(0,0,1);
	setfillstyle(1,color);

	drawa2p2(x+7*PL,y);

	drawa2p2(x+7*PL,y+1*PL);

	drawa2p2(x+7*PL,y+2*PL);

	drawa2p2(x+7*PL,y+3*PL);
	drawa2p2(x+6*PL,y+3*PL);
	drawa2p2(x+5*PL,y+3*PL);

	drawa2p2(x+4*PL,y+4*PL);
	drawa2p2(x+7*PL,y+4*PL);

	drawa2p2(x+3*PL,y+5*PL);
	drawa2p2(x+7*PL,y+5*PL);

	drawa2p2(x+3*PL,y+6*PL);
	drawa2p2(x+7*PL,y+6*PL);

	drawa2p2(x+3*PL,y+7*PL);
	drawa2p2(x+7*PL,y+7*PL);

	drawa2p2(x+4*PL,y+8*PL);
	drawa2p2(x+7*PL,y+8*PL);

	drawa2p2(x+5*PL,y+9*PL);
	drawa2p2(x+6*PL,y+9*PL);
	drawa2p2(x+7*PL,y+9*PL);

	return;
}

void drawalet_e(int x,int y,int color)
{
	x+=5;
	setcolor(color);
	setlinestyle(0,0,1);
	setfillstyle(1,color);
	
	drawa2p2(x+3*PL,y+3*PL);
	drawa2p2(x+4*PL,y+3*PL);
	drawa2p2(x+5*PL,y+3*PL);
	
	drawa2p2(x+2*PL,y+4*PL);
	drawa2p2(x+6*PL,y+4*PL);

	drawa2p2(x+2*PL,y+5*PL);
	drawa2p2(x+6*PL,y+5*PL);

	drawa2p2(x+2*PL,y+6*PL);
	drawa2p2(x+3*PL,y+6*PL);
	drawa2p2(x+4*PL,y+6*PL);
	drawa2p2(x+5*PL,y+6*PL);
	drawa2p2(x+6*PL,y+6*PL);

	drawa2p2(x+2*PL,y+7*PL);	

	drawa2p2(x+2*PL,y+8*PL);
	drawa2p2(x+6*PL,y+8*PL);
	
	drawa2p2(x+3*PL,y+9*PL);
	drawa2p2(x+4*PL,y+9*PL);
	drawa2p2(x+5*PL,y+9*PL);
	return;
}


void drawalet_f(int x,int y,int color)
{
	setcolor(color);
	setlinestyle(0,0,1);
	setfillstyle(1,color);

	drawa2p2(x+4*PL,y);
	drawa2p2(x+5*PL,y);

	drawa2p2(x+3*PL,y+1*PL);
	drawa2p2(x+6*PL,y+1*PL);

	drawa2p2(x+3*PL,y+2*PL);

	drawa2p2(x+3*PL,y+3*PL);

	drawa2p2(x+1*PL,y+4*PL);
	drawa2p2(x+2*PL,y+4*PL);
	drawa2p2(x+3*PL,y+4*PL);
	drawa2p2(x+4*PL,y+4*PL);
	drawa2p2(x+5*PL,y+4*PL);
	drawa2p2(x+6*PL,y+4*PL);

	drawa2p2(x+3*PL,y+5*PL);

	drawa2p2(x+3*PL,y+6*PL);

	drawa2p2(x+3*PL,y+7*PL);

	drawa2p2(x+3*PL,y+8*PL);

	drawa2p2(x+3*PL,y+9*PL);

	return;
}

void drawalet_g(int x,int y,int color)
{
	y+=5;
	
	setcolor(color);
	setlinestyle(0,0,1);
	setfillstyle(1,color);

	drawa2p2(x+3*PL,y);
	drawa2p2(x+4*PL,y);
	drawa2p2(x+5*PL,y);
	
	drawa2p2(x+2*PL,y+1*PL);
	drawa2p2(x+6*PL,y+1*PL);

	drawa2p2(x+2*PL,y+2*PL);
	drawa2p2(x+6*PL,y+2*PL);

	drawa2p2(x+2*PL,y+3*PL);
	drawa2p2(x+6*PL,y+3*PL);

	drawa2p2(x+2*PL,y+4*PL);
	drawa2p2(x+6*PL,y+4*PL);

	drawa2p2(x+3*PL,y+5*PL);
	drawa2p2(x+4*PL,y+5*PL);
	drawa2p2(x+5*PL,y+5*PL);
	drawa2p2(x+6*PL,y+5*PL);

	drawa2p2(x+6*PL,y+6*PL);

	drawa2p2(x+6*PL,y+7*PL);

	drawa2p2(x+6*PL,y+8*PL);
	drawa2p2(x+2*PL,y+8*PL);

	drawa2p2(x+3*PL,y+9*PL);
	drawa2p2(x+4*PL,y+9*PL);
	drawa2p2(x+5*PL,y+9*PL);

	return;
}

void drawalet_z(int x,int y,int color)
{
	setcolor(color);
	setlinestyle(0,0,1);
	setfillstyle(1,color);
	
	drawa2p2(x+2*PL,y+2*PL);
	drawa2p2(x+3*PL,y+2*PL);
	drawa2p2(x+4*PL,y+2*PL);
        drawa2p2(x+5*PL,y+2*PL);
        drawa2p2(x+6*PL,y+2*PL);
	
	drawa2p2(x+6*PL,y+3*PL);
	
	
	drawa2p2(x+5*PL,y+4*PL);
	
	drawa2p2(x+4*PL,y+5*PL);	
	
	drawa2p2(x+3*PL,y+6*PL);
	
	drawa2p2(x+2*PL,y+7*PL);
	
	drawa2p2(x+2*PL,y+8*PL);
	
	drawa2p2(x+2*PL,y+9*PL);
	drawa2p2(x+3*PL,y+9*PL);
	drawa2p2(x+4*PL,y+9*PL);
	drawa2p2(x+5*PL,y+9*PL);
	drawa2p2(x+6*PL,y+9*PL);	
	return;
}


void drawalet_y(int x,int y,int color)
{
	setcolor(color);
	setlinestyle(0,0,1);
	setfillstyle(1,color);
	
	y+=3*PL;
	
	drawa2p2(x+2*PL,y+2*PL);
	drawa2p2(x+5*PL,y+2*PL);
	
	drawa2p2(x+2*PL,y+3*PL);
	drawa2p2(x+5*PL,y+3*PL);
	
	drawa2p2(x+2*PL,y+4*PL);
	drawa2p2(x+5*PL,y+4*PL);
	
	drawa2p2(x+3*PL,y+5*PL);	
	drawa2p2(x+4*PL,y+5*PL);
	drawa2p2(x+5*PL,y+5*PL);
	
	drawa2p2(x+5*PL,y+6*PL);
	
	drawa2p2(x+2*PL,y+7*PL);
	drawa2p2(x+5*PL,y+7*PL);	

	drawa2p2(x+2*PL,y+8*PL);
	drawa2p2(x+5*PL,y+8*PL);
	
	drawa2p2(x+3*PL,y+9*PL);
	drawa2p2(x+4*PL,y+9*PL);
	return;
}



void drawalet_x(int x,int y,int color)
{
	setcolor(color);
	setlinestyle(0,0,1);
	setfillstyle(1,color);
	
	drawa2p2(x+7*PL,y+3*PL);
	drawa2p2(x+3*PL,y+3*PL);	
	
	drawa2p2(x+7*PL,y+4*PL);
	drawa2p2(x+3*PL,y+4*PL);
	
	drawa2p2(x+4*PL,y+5*PL);	
	drawa2p2(x+6*PL,y+5*PL);
	
	drawa2p2(x+5*PL,y+6*PL);
	
	drawa2p2(x+4*PL,y+7*PL);	
	drawa2p2(x+6*PL,y+7*PL);
	
	drawa2p2(x+3*PL,y+8*PL);
	drawa2p2(x+7*PL,y+8*PL);
	
        drawa2p2(x+3*PL,y+9*PL);
	drawa2p2(x+7*PL,y+9*PL);

	return;
}


void drawalet_w(int x,int y,int color)
{
	setcolor(color);
	setlinestyle(0,0,1);
	setfillstyle(1,color);
	
	drawa2p2(x+0*PL,y+3*PL);
	drawa2p2(x+4*PL,y+3*PL);
	drawa2p2(x+8*PL,y+3*PL);
	
	drawa2p2(x+1*PL,y+4*PL);
	drawa2p2(x+3*PL,y+4*PL);
	drawa2p2(x+5*PL,y+4*PL);
	drawa2p2(x+7*PL,y+4*PL);

	drawa2p2(x+1*PL,y+5*PL);
	drawa2p2(x+3*PL,y+5*PL);
	drawa2p2(x+5*PL,y+5*PL);
	drawa2p2(x+7*PL,y+5*PL);

	drawa2p2(x+1*PL,y+6*PL);
	drawa2p2(x+3*PL,y+6*PL);
	drawa2p2(x+5*PL,y+6*PL);
	drawa2p2(x+7*PL,y+6*PL);
	
	drawa2p2(x+1*PL,y+7*PL);
	drawa2p2(x+3*PL,y+7*PL);
	drawa2p2(x+5*PL,y+7*PL);
	drawa2p2(x+7*PL,y+7*PL);	

	drawa2p2(x+2*PL,y+8*PL);
	drawa2p2(x+6*PL,y+8*PL);
	
	drawa2p2(x+2*PL,y+9*PL);
	drawa2p2(x+6*PL,y+9*PL);
	return;
}



void drawalet_v(int x,int y,int color)
{
	setcolor(color);
	setlinestyle(0,0,1);
	setfillstyle(1,color);
	
	drawa2p2(x+3*PL,y+3*PL);
	drawa2p2(x+7*PL,y+3*PL);
	
	drawa2p2(x+3*PL,y+4*PL);
	drawa2p2(x+7*PL,y+4*PL);

	drawa2p2(x+3*PL,y+5*PL);
	drawa2p2(x+7*PL,y+5*PL);

	drawa2p2(x+3*PL,y+6*PL);
	drawa2p2(x+7*PL,y+6*PL);

	drawa2p2(x+4*PL,y+7*PL);
	drawa2p2(x+6*PL,y+7*PL);	

	drawa2p2(x+4*PL,y+8*PL);
	drawa2p2(x+6*PL,y+8*PL);
	
	drawa2p2(x+5*PL,y+9*PL);
	return;
}



void drawalet_u(int x,int y,int color)
{
	setcolor(color);
	setlinestyle(0,0,1);
	setfillstyle(1,color);
	
	drawa2p2(x+4*PL,y+3*PL);
	drawa2p2(x+7*PL,y+3*PL);
	
	drawa2p2(x+4*PL,y+4*PL);
	drawa2p2(x+7*PL,y+4*PL);

	drawa2p2(x+4*PL,y+5*PL);
	drawa2p2(x+7*PL,y+5*PL);

	drawa2p2(x+4*PL,y+6*PL);
	drawa2p2(x+7*PL,y+6*PL);

	drawa2p2(x+4*PL,y+7*PL);
	drawa2p2(x+7*PL,y+7*PL);	

	drawa2p2(x+4*PL,y+8*PL);
	drawa2p2(x+7*PL,y+8*PL);
	
	drawa2p2(x+5*PL,y+9*PL);
	drawa2p2(x+6*PL,y+9*PL);
	return;
}



void drawalet_t(int x,int y,int color)
{
	setcolor(color);
	setlinestyle(0,0,1);
	setfillstyle(1,color);
	
	drawa2p2(x+4*PL,y+2*PL);

	drawa2p2(x+4*PL,y+3*PL);
	
	drawa2p2(x+3*PL,y+4*PL);
	drawa2p2(x+4*PL,y+4*PL);
	drawa2p2(x+5*PL,y+4*PL);
	drawa2p2(x+6*PL,y+4*PL);
	drawa2p2(x+7*PL,y+4*PL);

	drawa2p2(x+4*PL,y+5*PL);

	drawa2p2(x+4*PL,y+6*PL);

	drawa2p2(x+4*PL,y+7*PL);
	drawa2p2(x+6*PL,y+9*PL);	

	drawa2p2(x+4*PL,y+8*PL);
	drawa2p2(x+5*PL,y+9*PL);
	
	drawa2p2(x+4*PL,y+9*PL);
	return;
}




void drawalet_s(int x,int y,int color)
{
	setcolor(color);
	setlinestyle(0,0,1);
	setfillstyle(1,color);
	

	drawa2p2(x+3*PL,y+4*PL);
	
	drawa2p2(x+4*PL,y+3*PL);
	drawa2p2(x+5*PL,y+3*PL);
	drawa2p2(x+6*PL,y+3*PL);
	drawa2p2(x+7*PL,y+3*PL);

	drawa2p2(x+3*PL,y+5*PL);

	drawa2p2(x+4*PL,y+6*PL);
	drawa2p2(x+5*PL,y+6*PL);
	drawa2p2(x+6*PL,y+6*PL);

	drawa2p2(x+7*PL,y+7*PL);

	drawa2p2(x+7*PL,y+8*PL);
	
	drawa2p2(x+3*PL,y+9*PL);
	drawa2p2(x+4*PL,y+9*PL);
	drawa2p2(x+5*PL,y+9*PL);
	drawa2p2(x+6*PL,y+9*PL);
	return;
}





void drawalet_r(int x,int y,int color)
{
	setcolor(color);
	setlinestyle(0,0,1);
	setfillstyle(1,color);
	
	drawa2p2(x+4*PL,y+2*PL);

	drawa2p2(x+4*PL,y+4*PL);
        drawa2p2(x+6*PL,y+4*PL);
	
	drawa2p2(x+4*PL,y+3*PL);
	drawa2p2(x+6*PL,y+3*PL);

	drawa2p2(x+4*PL,y+5*PL);
	drawa2p2(x+5*PL,y+5*PL);

	drawa2p2(x+4*PL,y+6*PL);
	drawa2p2(x+5*PL,y+6*PL);

	drawa2p2(x+4*PL,y+7*PL);

	drawa2p2(x+4*PL,y+8*PL);
	
	drawa2p2(x+4*PL,y+9*PL);
	
	drawa2p2(x+7*PL,y+2*PL);
	return;
}



void drawalet_q(int x,int y,int color)
{
	setcolor(color);
	setlinestyle(0,0,1);
	setfillstyle(1,color);
	
	y+=3*PL;
	x+=2*PL;
	
	drawa2p2(x+2*PL,y+1*PL);
	drawa2p2(x+3*PL,y+1*PL);
	drawa2p2(x+4*PL,y+1*PL);
        drawa2p2(x+5*PL,y+1*PL);
	
	drawa2p2(x+1*PL,y+2*PL);
	drawa2p2(x+5*PL,y+2*PL);

	drawa2p2(x+1*PL,y+3*PL);
	drawa2p2(x+5*PL,y+3*PL);
	drawa2p2(x+1*PL,y+4*PL);
	drawa2p2(x+5*PL,y+4*PL);
	drawa2p2(x+1*PL,y+5*PL);
	drawa2p2(x+5*PL,y+5*PL);

	drawa2p2(x+2*PL,y+6*PL);
	drawa2p2(x+3*PL,y+6*PL);
	drawa2p2(x+4*PL,y+6*PL);
	drawa2p2(x+5*PL,y+6*PL);

	drawa2p2(x+5*PL,y+7*PL);	

	drawa2p2(x+5*PL,y+8*PL);
	drawa2p2(x+5*PL,y+9*PL);

	return;
}



void drawalet_p(int x,int y,int color)
{
	setcolor(color);
	setlinestyle(0,0,1);
	setfillstyle(1,color);
	
	y+=3*PL;

	drawa2p2(x+6*PL,y+1*PL);
	drawa2p2(x+4*PL,y+1*PL);
	drawa2p2(x+5*PL,y+1*PL);
	
	drawa2p2(x+4*PL,y+2*PL);
	drawa2p2(x+7*PL,y+2*PL);

	drawa2p2(x+4*PL,y+3*PL);
	drawa2p2(x+7*PL,y+3*PL);
	
	drawa2p2(x+4*PL,y+4*PL);
	drawa2p2(x+7*PL,y+4*PL);

	drawa2p2(x+6*PL,y+5*PL);
	drawa2p2(x+5*PL,y+5*PL);
	drawa2p2(x+4*PL,y+5*PL);

	drawa2p2(x+4*PL,y+6*PL);

	drawa2p2(x+4*PL,y+7*PL);

	drawa2p2(x+4*PL,y+8*PL);
	
	drawa2p2(x+4*PL,y+9*PL);
	return;
}





void drawalet_o(int x,int y,int color)
{
	setcolor(color);
	setlinestyle(0,0,1);
	setfillstyle(1,color);

	drawa2p2(x+4*PL,y+3*PL);
	drawa2p2(x+5*PL,y+3*PL);
	drawa2p2(x+6*PL,y+3*PL);
	
	drawa2p2(x+3*PL,y+4*PL);
	drawa2p2(x+7*PL,y+4*PL);

	drawa2p2(x+2*PL,y+5*PL);
	drawa2p2(x+8*PL,y+5*PL);

	drawa2p2(x+2*PL,y+6*PL);
	drawa2p2(x+8*PL,y+6*PL);

	drawa2p2(x+2*PL,y+7*PL);
	drawa2p2(x+8*PL,y+7*PL);

	drawa2p2(x+3*PL,y+8*PL);
	drawa2p2(x+7*PL,y+8*PL);
	
	drawa2p2(x+4*PL,y+9*PL);
	drawa2p2(x+5*PL,y+9*PL);
	drawa2p2(x+6*PL,y+9*PL);
	return;
}




void drawalet_n(int x,int y,int color)
{
	setcolor(color);
	setlinestyle(0,0,1);
	setfillstyle(1,color);

	drawa2p2(x+4*PL,y+3*PL);
	drawa2p2(x+5*PL,y+3*PL);
	
	drawa2p2(x+3*PL,y+4*PL);
	drawa2p2(x+6*PL,y+4*PL);

	drawa2p2(x+3*PL,y+5*PL);
	drawa2p2(x+6*PL,y+5*PL);

	drawa2p2(x+3*PL,y+6*PL);
	drawa2p2(x+6*PL,y+6*PL);

	drawa2p2(x+3*PL,y+7*PL);
	drawa2p2(x+6*PL,y+7*PL);

	drawa2p2(x+3*PL,y+8*PL);
	drawa2p2(x+6*PL,y+8*PL);
	
	drawa2p2(x+3*PL,y+9*PL);
	drawa2p2(x+6*PL,y+9*PL);
	return;
}



void drawalet_m(int x,int y,int color)
{
	setcolor(color);
	setlinestyle(0,0,1);
	setfillstyle(1,color);

	drawa2p2(x+4*PL,y+3*PL);
	drawa2p2(x+3*PL,y+3*PL);
	drawa2p2(x+6*PL,y+3*PL);
	drawa2p2(x+7*PL,y+3*PL);
	
	drawa2p2(x+2*PL,y+4*PL);
	drawa2p2(x+5*PL,y+4*PL);
        drawa2p2(x+8*PL,y+4*PL);

	drawa2p2(x+2*PL,y+5*PL);
	drawa2p2(x+5*PL,y+5*PL);
        drawa2p2(x+8*PL,y+5*PL);

	drawa2p2(x+2*PL,y+6*PL);
	drawa2p2(x+5*PL,y+6*PL);
        drawa2p2(x+8*PL,y+6*PL);

	drawa2p2(x+2*PL,y+7*PL);
	drawa2p2(x+5*PL,y+7*PL);
        drawa2p2(x+8*PL,y+7*PL);

	drawa2p2(x+2*PL,y+8*PL);
	drawa2p2(x+5*PL,y+8*PL);
        drawa2p2(x+8*PL,y+8*PL);
	
	drawa2p2(x+2*PL,y+9*PL);
	drawa2p2(x+5*PL,y+9*PL);
        drawa2p2(x+8*PL,y+9*PL);
	return;
}




void drawalet_l(int x,int y,int color)
{
	setcolor(color);
	setlinestyle(0,0,1);
	setfillstyle(1,color);
	drawa2p2(x+3*PL,y+0*PL);
	drawa2p2(x+3*PL,y+1*PL);
	drawa2p2(x+3*PL,y+3*PL);
	drawa2p2(x+3*PL,y+2*PL);
	drawa2p2(x+3*PL,y+4*PL);
	
	drawa2p2(x+3*PL,y+5*PL);
	drawa2p2(x+3*PL,y+6*PL);
        drawa2p2(x+3*PL,y+7*PL);

	drawa2p2(x+3*PL,y+8*PL);
	drawa2p2(x+5*PL,y+8*PL);
        drawa2p2(x+4*PL,y+9*PL);
	return;
}



void drawalet_k(int x,int y,int color)
{
	setcolor(color);
	setlinestyle(0,0,1);
	setfillstyle(1,color);
	drawa2p2(x+2*PL,y+0*PL);
	drawa2p2(x+2*PL,y+1*PL);
	drawa2p2(x+2*PL,y+3*PL);
	drawa2p2(x+2*PL,y+2*PL);
	drawa2p2(x+2*PL,y+4*PL);
	
	drawa2p2(x+2*PL,y+5*PL);
	drawa2p2(x+2*PL,y+6*PL);
        drawa2p2(x+2*PL,y+7*PL);

	drawa2p2(x+2*PL,y+8*PL);
        drawa2p2(x+2*PL,y+9*PL);
	drawa2p2(x+5*PL,y+4*PL);
	drawa2p2(x+4*PL,y+5*PL);
	drawa2p2(x+3*PL,y+6*PL);
	drawa2p2(x+4*PL,y+7*PL);
	drawa2p2(x+5*PL,y+8*PL);
	drawa2p2(x+6*PL,y+9*PL);

	return;
}



void drawalet_j(int x,int y,int color)
{
	setcolor(color);
	setlinestyle(0,0,1);
	setfillstyle(1,color);

	drawa2p2(x+7*PL,y+0*PL);
	drawa2p2(x+7*PL,y+2*PL);
	drawa2p2(x+7*PL,y+3*PL);
	drawa2p2(x+7*PL,y+4*PL);
	drawa2p2(x+7*PL,y+5*PL);
	drawa2p2(x+7*PL,y+6*PL);

	drawa2p2(x+3*PL,y+7*PL);
	drawa2p2(x+7*PL,y+7*PL);

	drawa2p2(x+3*PL,y+8*PL);
	drawa2p2(x+6*PL,y+8*PL);
	
	drawa2p2(x+4*PL,y+9*PL);
	drawa2p2(x+5*PL,y+9*PL);
	return;
}



void drawalet_i(int x,int y,int color)
{
	setcolor(color);
	setlinestyle(0,0,1);
	setfillstyle(1,color);

	drawa2p2(x+4*PL,y+1*PL);
	drawa2p2(x+4*PL,y+3*PL);
	drawa2p2(x+4*PL,y+4*PL);
	
	drawa2p2(x+4*PL,y+5*PL);
	drawa2p2(x+4*PL,y+6*PL);

	drawa2p2(x+4*PL,y+7*PL);
	drawa2p2(x+4*PL,y+8*PL);

	drawa2p2(x+4*PL,y+9*PL);
	return;
}



void drawalet_T(int x,int y,int color)
{
	setcolor(color);
	setlinestyle(0,0,1);
	setfillstyle(1,color);
	
	drawa2p2(x+1*PL,y+0*PL);
	drawa2p2(x+2*PL,y+0*PL);
	drawa2p2(x+3*PL,y+0*PL);
	drawa2p2(x+4*PL,y+0*PL);
	drawa2p2(x+5*PL,y+0*PL);
	drawa2p2(x+6*PL,y+0*PL);
	drawa2p2(x+7*PL,y+0*PL);
	
	drawa2p2(x+4*PL,y+1*PL);
	drawa2p2(x+4*PL,y+2*PL);
	drawa2p2(x+4*PL,y+3*PL);
	drawa2p2(x+4*PL,y+4*PL);
	drawa2p2(x+4*PL,y+5*PL);
	drawa2p2(x+4*PL,y+6*PL);
	drawa2p2(x+4*PL,y+7*PL);
	drawa2p2(x+4*PL,y+8*PL);
	drawa2p2(x+4*PL,y+9*PL);


	return;
}


void drawalet_h(int x,int y,int color)
{
	setcolor(color);
	setlinestyle(0,0,1);
	setfillstyle(1,color);

	drawa2p2(x+2*PL,y+0*PL);
	drawa2p2(x+2*PL,y+1*PL);
	drawa2p2(x+2*PL,y+2*PL);

	drawa2p2(x+2*PL,y+3*PL);
	drawa2p2(x+3*PL,y+3*PL);
	drawa2p2(x+4*PL,y+3*PL);
	drawa2p2(x+5*PL,y+3*PL);
	
	drawa2p2(x+2*PL,y+4*PL);
	drawa2p2(x+6*PL,y+4*PL);

	drawa2p2(x+2*PL,y+5*PL);
	drawa2p2(x+6*PL,y+5*PL);

	drawa2p2(x+2*PL,y+6*PL);
	drawa2p2(x+6*PL,y+6*PL);

	drawa2p2(x+2*PL,y+7*PL);
	drawa2p2(x+6*PL,y+7*PL);

	drawa2p2(x+2*PL,y+8*PL);
	drawa2p2(x+6*PL,y+8*PL);
	
	drawa2p2(x+2*PL,y+9*PL);
	drawa2p2(x+6*PL,y+9*PL);
	return;
}

void drawaletter(int x,int y,int color,char c)
{
	switch (c)
	{
		case 'a':
			drawalet_a(x,y,color);
			break;
		case 'b':
			drawalet_b(x,y,color);
			break;
		case 'c':
			drawalet_c(x,y,color);
			break;
		case 'd':
			drawalet_d(x,y,color);
			break;
		case 'e':
			drawalet_e(x,y,color);
			break;
		case 'f':
			drawalet_f(x,y,color);
			break;
		case 'g':
			drawalet_g(x,y,color);
			break;
		case 'h':
			drawalet_h(x,y,color);
			break;
		case 'i':
			drawalet_i(x,y,color);
			break;
		case 'j':
			drawalet_j(x,y,color);
			break;
		case 'k':
			drawalet_k(x,y,color);
			break;
		case 'l':
			drawalet_l(x,y,color);
			break;
		case 'm':
			drawalet_m(x,y,color);
			break;
		case 'n':
			drawalet_n(x,y,color);
			break;
		case 'o':
			drawalet_o(x,y,color);
			break;
		case 'p':
			drawalet_p(x,y,color);
			break;
		case 'q':
			drawalet_q(x,y,color);
			break;
		case 'r':
			drawalet_r(x,y,color);
			break;
		case 's':
			drawalet_s(x,y,color);
			break;
		case 't':
			drawalet_t(x,y,color);
			break;
		case 'u':
			drawalet_u(x,y,color);
			break;
		case 'v':
			drawalet_v(x,y,color);
			break;
		case 'w':
			drawalet_w(x,y,color);
			break;
		case 'x':
			drawalet_x(x,y,color);
			break;
		case 'y':
			drawalet_y(x,y,color);
			break;
		case 'z':
			drawalet_z(x,y,color);
			break;
		case 'T':
			drawalet_T(x,y,color);
			break;
		default:
			break;
	}
	return;
}


void displaystring(int x,int y,char * p,int color)
{
	while (*p!='\0')
	{
		drawaletter(x,y,color,*p);
		p++;
		x+=7*PL;
	}
	return;
}
void drawasquare(int x,int y,int color)						//描绘基本立方体	
{
	int poly[8];
	setcolor(15);
	setlinestyle(0,0,1);
	setfillstyle(1,color);

	poly[0]=x;
	poly[1]=y;
	poly[2]=x+mid;
	poly[3]=y-mid/2;
	poly[4]=x+mid*2;
	poly[5]=y;
	poly[6]=x+mid;
	poly[7]=y+mid/2;
	fillpoly(4,poly);


	poly[0]=x+mid;
	poly[1]=y+mid/2;
	poly[2]=x+mid;
	poly[3]=y+mid/2+unit;
	poly[4]=x+mid*2;
	poly[5]=y+unit;
	poly[6]=x+mid*2;
	poly[7]=y;
	fillpoly(4,poly);

	poly[0]=x;
	poly[1]=y;
	poly[2]=x;
	poly[3]=y+unit;
	poly[4]=x+mid;
	poly[5]=y+mid/2+unit;
	poly[6]=x+mid;
	poly[7]=y+mid/2;
	fillpoly(4,poly);
	return;
}

void drawSL(int x,int y,int color)							//描绘立体L
{
	drawasquare(x,y+2*unit,color);
	drawasquare(x,y+unit,color);
	drawasquare(x+mid,y-mid/2,color);
	drawasquare(x,y,color);
	return;
}

void drawSO(int x,int y,int color)							//描绘立体O
{
	drawasquare(x,y+unit,color);
	drawasquare(x+2*mid,y+unit,color);
	drawasquare(x+mid,y+mid/2+unit,color);
	drawasquare(x+mid,y-mid/2,color);
	drawasquare(x,y,color);
	drawasquare(x+2*mid,y,color);
	drawasquare(x+mid,y+mid/2,color);
	return;
}

void drawSI(int x,int y,int color)							//描绘立体I
{
	drawasquare(x,y+3*unit,color);
	drawasquare(x,y+2*unit,color);
	drawasquare(x,y+unit,color);
	drawasquare(x,y,color);
	return;
}

void drawSZ(int x,int y,int color)							//描绘立体Z
{
	drawasquare(x+mid,y-mid/2+2*unit,color);
	drawasquare(x+mid,y-mid/2+unit,color);
	drawasquare(x,y+unit,color);
	drawasquare(x,y,color);
	return;
}

void logo(int x,int y)
{
	int L=4,O=1,I=14,Z=2,key;
	int j,k,t,color;
	char s[10];
	double n;
	unit=50;
	mid=sqrt((unit*unit)/2);
	color=4;
	drawSI(x+4*mid,y-mid-unit,I);
	drawSO(x+mid,y-mid/2+unit,O);
	drawasquare(x+2*mid,y-mid,Z);
	drawasquare(x+2*mid,y-mid-unit,Z);
	drawSL(x,y,L);
	NL=3;
	x-=140;
	y+=200;
	n4(x,y,color);
	n0(x+16*NL,y,color);
	n6(x+34*NL,y,color);
	n1(x+45*NL,y,color);
	x+=62*NL;
	color=2;
	strcpy(s,"studio");
	PL=8;
	y-=10;
	displaystring(x,y,s,color);
	delay(300);
	t=clock();
	n=54475;
	srand(clock());
	/*for (j=0;j<640;j++)
		for (k=0;k<480;k++)
			if (getpixel(j,k)>0) n+=1;*/
	for (j=0;j<n;j++)
	{
		while (getpixel(x=rand()%640,y=rand()%480)==0);
		putpixel(x,y,0);
		putpixel(x+5,y,0);
		putpixel(x,y-5,0);
		putpixel(x-7,y,0);
		putpixel(x,y+7,0);
		putpixel(x+3,y,0);
		putpixel(x,y-3,0);
		putpixel(x+12,y,0);
		putpixel(x,y+12,0);
		putpixel(x,y-12,0);
		putpixel(x-12,y,0);
		putpixel(x+9,y,0);
		putpixel(x,y+9,0);
		putpixel(x,y-9,0);
		putpixel(x-9,y,0);
		if (bioskey(1)) key=bioskey(0);
		else key=0;
		if (clock()-t>120||key==283) break;
	}
	
	
	clearscreen();
	return;
}


void ui(void)
{
	int poly[8];
	int x,y,color,opt=1,oopt=0,key=0,c=0,l;
	char s[15];
while (1)
{
	opt=1;
	oopt=0;
	key=0;
	clearscreen();
	x=20;
	y=30;
	PL=15;
	color=Lv1C;
	drawaletter(x,y,color,'T');
	x+=6*PL;
	color=Lv2C;
	drawaletter(x,y,color,'e');
	x+=6*PL;
	color=Lv3C;
	drawaletter(x,y,color,'t');
	x+=6*PL;
	color=Lv4C;
	drawaletter(x,y,color,'r');
	x+=6*PL;
	color=Lv5C;
	drawaletter(x,y,color,'i');
	x+=6*PL;
	color=Lv6C;
	drawaletter(x,y,color,'s');
	
	while (key!=7181)
	{
		if (bioskey(1)) key=bioskey(0);
		else key=0;
		switch(key)
		{
			case 0:														//无按键
				break;
			case 18432:													//上
				opt--;
				if (opt<0) opt=2;
				break;
			case 20480:													//下
				opt++;
				if (opt>2) opt=0;
				break;
			case 283:														//esc
				opt=0;
				key=7181;
				break;
			default:
				break;
		}
		if (oopt!=opt)
		{
			oopt=opt;
		if (!c)
		{
			x=210;
			y=230;
			l=11;
			setcolor(0);
			setlinestyle(0,0,1);
			setfillstyle(1,0);
			PL=3;
			poly[0]=x;
			poly[1]=y-PL;
			poly[2]=x;
			poly[3]=y+13*PL+1;
			poly[4]=x+(7*l-4)*PL;
			poly[5]=y+13*PL+1;
			poly[6]=x+(7*l-4)*PL;
			poly[7]=y-PL;
			fillpoly(4,poly);
			
			x=210;
			y=280;
			l=12;
			poly[0]=x;
			poly[1]=y-PL;
			poly[2]=x;
			poly[3]=y+13*PL+1;
			poly[4]=x+(7*l-4)*PL;
			poly[5]=y+13*PL+1;
			poly[6]=x+(7*l-4)*PL;
			poly[7]=y-PL;
			fillpoly(4,poly);
			
			x=260;
			y=380;
			l=5;
			poly[0]=x;
			poly[1]=y-PL;
			poly[2]=x;
			poly[3]=y+13*PL+1;
			poly[4]=x+(7*l-4)*PL;
			poly[5]=y+13*PL+1;
			poly[6]=x+(7*l-4)*PL;
			poly[7]=y-PL;
			fillpoly(4,poly);
			switch (opt)
			{
				case 1:
					x=210;
					y=230;
					l=11;
					break;
				case 2:
					x=210;
					y=280;
					l=12;
					break;
				case 0:
					x=260;
					y=380;
					l=5;
					break;
				default:
					break;
			}
			poly[0]=x;
			poly[1]=y-PL;
			poly[2]=x;
			poly[3]=y+13*PL;
			poly[4]=x+(7*l-4)*PL;
			poly[5]=y+13*PL;
			poly[6]=x+(7*l-4)*PL;
			poly[7]=y-PL;
			setcolor(2);
			setlinestyle(0,0,1);
			setfillstyle(1,2);
			fillpoly(4,poly);
			
			strcpy(s,"one player");
			displaystring(210,230,s,15);
			
			strcpy(s,"two players");
			displaystring(210,280,s,15);
			
			strcpy(s,"quit");
			displaystring(260,380,s,15);
		}
		else
		{
			x=210;
			y=230;
			l=8;
			setcolor(0);
			setlinestyle(0,0,1);
			setfillstyle(1,0);
			PL=3;
			poly[0]=x;
			poly[1]=y-PL;
			poly[2]=x;
			poly[3]=y+13*PL+1;
			poly[4]=x+(7*l-4)*PL;
			poly[5]=y+13*PL+1;
			poly[6]=x+(7*l-4)*PL;
			poly[7]=y-PL;
			fillpoly(4,poly);
			
			x=210;
			y=280;
			l=12;
			poly[0]=x;
			poly[1]=y-PL;
			poly[2]=x;
			poly[3]=y+13*PL+1;
			poly[4]=x+(7*l-4)*PL;
			poly[5]=y+13*PL+1;
			poly[6]=x+(7*l-4)*PL;
			poly[7]=y-PL;
			fillpoly(4,poly);
			
			x=260;
			y=380;
			l=5;
			poly[0]=x;
			poly[1]=y-PL;
			poly[2]=x;
			poly[3]=y+13*PL+1;
			poly[4]=x+(7*l-4)*PL;
			poly[5]=y+13*PL+1;
			poly[6]=x+(7*l-4)*PL;
			poly[7]=y-PL;
			fillpoly(4,poly);
			switch (opt)
			{
				case 1:
					x=210;
					y=230;
					l=8;
					break;
				case 2:
					x=210;
					y=280;
					l=12;
					break;
				case 0:
					x=260;
					y=380;
					l=5;
					break;
				default:
					break;
			}
			poly[0]=x;
			poly[1]=y-PL;
			poly[2]=x;
			poly[3]=y+13*PL;
			poly[4]=x+(7*l-4)*PL;
			poly[5]=y+13*PL;
			poly[6]=x+(7*l-4)*PL;
			poly[7]=y-PL;
			setcolor(2);
			setlinestyle(0,0,1);
			setfillstyle(1,2);
			fillpoly(4,poly);
			
			strcpy(s,"classic");
			displaystring(210,230,s,15);
			
			strcpy(s,"competitive");
			displaystring(210,280,s,15);
			
			strcpy(s,"back");
			displaystring(260,380,s,15);
		}
		}
	}
	
	switch (opt+10*c)
	{
		case 1:
			single();
			break;
		case 11:
			com=0;
			multi();
			c=0;
			break;
		case 12:
			com=1;
			multi();
			c=0;
			break;
		case 0:
			closegr();
			return;
		default:
			break;
	}
	if (!c&&opt==2) c=1;
	if (c&&opt==0) c=0;
}
}


void end(int a)
{
	int poly[8];
	int x,y,l,color,key=0;
	char s[15];
	switch(a)
	{
		case 0:
			x=220;
			y=210;
			color=14;
			l=11;
			setcolor(0);
			setlinestyle(0,0,1);
			setfillstyle(1,0);
			PL=3;
			poly[0]=x;
			poly[1]=y-PL;
			poly[2]=x;
			poly[3]=y+13*PL+1;
			poly[4]=x+(7*l-4)*PL;
			poly[5]=y+13*PL+1;
			poly[6]=x+(7*l-4)*PL;
			poly[7]=y-PL;
			fillpoly(4,poly);
			setlinestyle(0,0,1);
			setfillstyle(1,2);
			strcpy(s,"game over");
			displaystring(x,y,s,color);
			break;
		case 1:
			x=85;
			y=210;
			color=14;
			l=4;
			setcolor(0);
			setlinestyle(0,0,1);
			setfillstyle(1,0);
			PL=3;
			poly[0]=x;
			poly[1]=y-PL;
			poly[2]=x;
			poly[3]=y+13*PL+1;
			poly[4]=x+(7*l-4)*PL;
			poly[5]=y+13*PL+1;
			poly[6]=x+(7*l-4)*PL;
			poly[7]=y-PL;
			fillpoly(4,poly);
			setlinestyle(0,0,1);
			setfillstyle(1,2);
			strcpy(s,"win");
			displaystring(x,y,s,color);
			x=460;
			y=210;
			color=14;
			l=5;
			setcolor(0);
			setlinestyle(0,0,1);
			setfillstyle(1,0);
			PL=3;
			poly[0]=x;
			poly[1]=y-PL;
			poly[2]=x;
			poly[3]=y+13*PL+1;
			poly[4]=x+(7*l-4)*PL;
			poly[5]=y+13*PL+1;
			poly[6]=x+(7*l-4)*PL;
			poly[7]=y-PL;
			fillpoly(4,poly);
			setlinestyle(0,0,1);
			setfillstyle(1,2);
			strcpy(s,"lose");
			displaystring(x,y,s,color);
			break;
		case 2:
			x=85;
			y=210;
			color=14;
			l=5;
			setcolor(0);
			setlinestyle(0,0,1);
			setfillstyle(1,0);
			PL=3;
			poly[0]=x;
			poly[1]=y-PL;
			poly[2]=x;
			poly[3]=y+13*PL+1;
			poly[4]=x+(7*l-4)*PL;
			poly[5]=y+13*PL+1;
			poly[6]=x+(7*l-4)*PL;
			poly[7]=y-PL;
			fillpoly(4,poly);
			setlinestyle(0,0,1);
			setfillstyle(1,2);
			strcpy(s,"lose");
			displaystring(x,y,s,color);
			x=480;
			y=210;
			color=14;
			l=4;
			setcolor(0);
			setlinestyle(0,0,1);
			setfillstyle(1,0);
			PL=3;
			poly[0]=x;
			poly[1]=y-PL;
			poly[2]=x;
			poly[3]=y+13*PL+1;
			poly[4]=x+(7*l-4)*PL;
			poly[5]=y+13*PL+1;
			poly[6]=x+(7*l-4)*PL;
			poly[7]=y-PL;
			fillpoly(4,poly);
			setlinestyle(0,0,1);
			setfillstyle(1,2);
			strcpy(s,"win");
			displaystring(x,y,s,color);
			break;
	}
	while(key!=283)
		if (bioskey(1)) key=bioskey(0);
		else key=0;
}
