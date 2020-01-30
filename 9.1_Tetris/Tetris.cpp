#include <iostream>
#include <Windows.h>
#include <graphics.h>
using namespace std;

void welcome(){
	//初始化画布
	initgraph(550, 660);

	//设置窗口标题,按
	HWND hWnd = GetHWnd();//get handle window获得句柄窗口,即当前窗口封装名
	SetWindowText(hWnd, "俄罗斯方块Tetris		--虾虾");

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
int score = 0;
int level = 1;
void gameScene(){
	cleardevice();

	rectangle(27, 27, 336, 635);
	rectangle(29, 29, 334, 633);
	rectangle(370, 50, 515, 195);

	setfont(24, 0, _T("楷体"));
	outtextxy(405, 215, _T("下一个"));

	setcolor(RED);
	outtextxy(405, 280, _T("分数:"));
	
	//分数值可能全局调用,故设为全局变量.防止其他文件有重名故设为静态.等级值同理
	char s_str[16];	sprintf(s_str, _T("%d"), score);
	outtextxy(415, 310, s_str);

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

	system("pause");
}

//双层方框:显高级

int main(){
	welcome();
	gameScene();


	closegraph();//记得关闭
	return 0;
}