#include "tetris.h"

#include <iostream>
#include <Windows.h>
#include <graphics.h>
#include <time.h>
using namespace std;

#define BLOCK_CNT	 5//方块组合种类数
#define FORM_CNT	 4//一种方块形态数
#define BLOCK_ROW	 5
#define BLOCK_COLUMN 5
#define UNIT_SIZE	 25//单元小方块边长,大黑格子边长
#define UNIT_SMALL	 24.9//小彩格子边长和清除它的小黑格子边长
//全局量首字母大写,初始化值为无意义数
int Color[BLOCK_CNT]={GREEN,CYAN,MAGENTA,BROWN,YELLOW};//在easyX帮助手册中颜色的值为6位十六进制数,故数组类型为int足够(int有4个字节32位二进制,8位十六进制)
int NxtIndex = -1;//因正常在0-(BLOCK_CNT-1),初始化为不正常值,若出现-1可知初始化后为赋值,快速检索错误点

//初始化方块:1表示填充,0表示未填充-因底色为黑色,即填充黑色方块"■",即clrBlock
int block[BLOCK_CNT * FORM_CNT][BLOCK_ROW][BLOCK_COLUMN] = {
	// | 形方块
	{ 0,0,0,0,0,
	0,0,1,0,0,
	0,0,1,0,0,
	0,0,1,0,0,
	0,0,0,0,0 },

	{ 0,0,0,0,0,
	0,0,0,0,0,
	0,1,1,1,0,
	0,0,0,0,0,
	0,0,0,0,0 },

	{ 0,0,0,0,0,
	0,0,1,0,0,
	0,0,1,0,0,
	0,0,1,0,0,
	0,0,0,0,0 },

	{ 0,0,0,0,0,
	0,0,0,0,0,
	0,1,1,1,0,
	0,0,0,0,0,
	0,0,0,0,0 },

	// L 形方块
	{ 0,0,0,0,0,
	0,0,1,0,0,
	0,0,1,0,0,
	0,0,1,1,0,
	0,0,0,0,0 },

	{ 0,0,0,0,0,
	0,0,0,0,0,
	0,1,1,1,0,
	0,1,0,0,0,
	0,0,0,0,0 },

	{ 0,0,0,0,0,
	0,1,1,0,0,
	0,0,1,0,0,
	0,0,1,0,0,
	0,0,0,0,0 },

	{ 0,0,0,0,0,
	0,0,0,1,0,
	0,1,1,1,0,
	0,0,0,0,0,
	0,0,0,0,0 },

	// 田 形方块
	{ 0,0,0,0,0,
	0,1,1,0,0,
	0,1,1,0,0,
	0,0,0,0,0,
	0,0,0,0,0 },

	{ 0,0,0,0,0,
	0,1,1,0,0,
	0,1,1,0,0,
	0,0,0,0,0,
	0,0,0,0,0 },

	{ 0,0,0,0,0,
	0,1,1,0,0,
	0,1,1,0,0,
	0,0,0,0,0,
	0,0,0,0,0 },

	{ 0,0,0,0,0,
	0,1,1,0,0,
	0,1,1,0,0,
	0,0,0,0,0,
	0,0,0,0,0 },

	// T 形方块
	{ 0,0,0,0,0,
	0,1,1,1,0,
	0,0,1,0,0,
	0,0,0,0,0,
	0,0,0,0,0 },

	{ 0,0,0,0,0,
	0,0,0,1,0,
	0,0,1,1,0,
	0,0,0,1,0,
	0,0,0,0,0 },

	{ 0,0,0,0,0,
	0,0,1,0,0,
	0,1,1,1,0,
	0,0,0,0,0,
	0,0,0,0,0 },

	{ 0,0,0,0,0,
	0,1,0,0,0,
	0,1,1,0,0,
	0,1,0,0,0,
	0,0,0,0,0 },

	// Z 形方块
	{ 0,0,0,0,0,
	0,1,1,0,0,
	0,0,1,1,0,
	0,0,0,0,0,
	0,0,0,0,0 },

	{ 0,0,0,0,0,
	0,0,1,0,0,
	0,1,1,0,0,
	0,1,0,0,0,
	0,0,0,0,0 },

	{ 0,0,0,0,0,
	0,1,1,0,0,
	0,0,1,1,0,
	0,0,0,0,0,
	0,0,0,0,0 },

	{ 0,0,0,0,0,
	0,0,1,0,0,
	0,1,1,0,0,
	0,1,0,0,0,
	0,0,0,0,0 },
};
void welcome(){
	//初始化画布
	initgraph(550, 660);

	//设置窗口标题
	HWND hWnd = GetHWnd();//get handle window获得句柄窗口,即当前窗口封装名
	SetWindowText(hWnd, "俄罗斯方块Tetris			--甜甜虾");

	//主标题
	setfont(40, 0, _T("微软雅黑"));//编码移植性:所有常量字符串前都加上_T(,后面加上).
	setcolor(WHITE);
	outtextxy(205, 200, _T("俄罗斯方块"));

	//副标题
	setfont(20, 0, _T("楷体"));//与之前设定的不一致,要写
	//setcolor(WHITE);与之前设定的一致,不必再写
	outtextxy(185, 300, _T("我们一起来玩吧嘻嘻~"));

	//暂停
	Sleep(1000);
}

int score = 0;
int level = 1;
void gameScene(){
	cleardevice();

	rectangle(27, 27, 336, 635);//双层方框:显高级
	rectangle(29, 29, 334, 633);
	rectangle(370, 50, 515, 195);

	setfont(24, 0, _T("楷体"));
	outtextxy(405, 215, _T("下一个"));

	setcolor(RED);
	outtextxy(405, 280, _T("分数:"));
	
	//分数值可能全局调用,故设为全局变量.防止其他文件有重名故设为静态.等级值同理
	char s_str[16];	sprintf(s_str, _T("%d"), score);//s[5]能存整数1024
	outtextxy(425, 310, s_str);

	outtextxy(405, 375, _T("等级:"));
	char l_str[16]; sprintf(l_str, _T("%d"), score);
	outtextxy(425, 405, l_str);

	setcolor(LIGHTBLUE);
	outtextxy(390, 475, "操作说明:");
	outtextxy(390, 500, "↑: 旋转");
	outtextxy(390, 525, "↓: 下降");
	outtextxy(390, 550, "←: 左移");
	outtextxy(390, 575, "→: 右移");
	outtextxy(390, 600, "空格: 暂停");
}

void drawBlock(){
	setcolor(Color[NxtIndex]);
	setfont(UNIT_SMALL, 0, "楷体");//楷体中加载实心方块,明显紧凑
	for (int r=0; r<BLOCK_ROW; r++){
		for (int c=0; c<BLOCK_COLUMN; c++){
			if (block[NxtIndex * FORM_CNT][r][c] == 1)
				outtextxy(381 + c*UNIT_SIZE, 71 + r*UNIT_SIZE,"■");
		}
	}
}

//大型项目常量/判断函数多次使用时一定宏定义
void clrBlock(){
	setcolor(BLACK);
	setfont(UNIT_SMALL, 0, "楷体");//视为大黑色格子(边长25)上有小彩色格子(边长23)和小黑格子(边长23),大黑色格子宽出的部分自动归位不同彩色格子的分界线,小黑格子用来清除彩色格子
	for (int r=0; r<BLOCK_ROW; r++){
		for (int c=0; c<BLOCK_COLUMN; c++){
			if (block[NxtIndex * FORM_CNT][r][c] == 0)
				outtextxy(381 + c*UNIT_SIZE, 71 + r*UNIT_SIZE,"■");
		}
	}
}

void nxtblock(){
	clrBlock();

	//生成随机数,以此随机数生成新方块
	srand(time(NULL));//以时间作为随机种子,因不同时间调用函数
	NxtIndex = rand() % BLOCK_CNT;//使生成数字:0-(BLOCK_CNT-1)

	drawBlock();//在新方块产生后有其他操作,故画新方块为函数中的最后一步	
}

int main(){
	welcome();
	gameScene();
	nxtblock();

	system("pause");
	closegraph();//记得关闭图像
	return 0;
}