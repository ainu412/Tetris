#include <iostream>
#include <Windows.h>
#include <graphics.h>
using namespace std;

void welcome(){
	//初始化画布
	initgraph(550, 600);

	//设置窗口标题,按
	HWND hWnd = GetHWnd();//get handle window获得句柄窗口,即当前窗口封装名
	SetWindowText(hWnd, "俄罗斯方块Tetris		虾虾");

	//主标题
	setfont(40, 0, _T("微软雅黑"));//编码移植性:所有常量字符串前都加上_T(,后面加上).
	setcolor(WHITE);
	outtextxy(205, 200, _T("俄罗斯方块"));

	//副标题
	setfont(20, 0, _T("楷体"));//与之前设定的不一致,要写
	//setcolor(WHITE);与之前设定的一致,不必再写
	outtextxy(185, 300, _T("我们一起来玩吧嘻嘻~"));

	//暂停
	Sleep(2000);
}

int main(){
	welcome();

	closegraph();//记得关闭
	return 0;
}