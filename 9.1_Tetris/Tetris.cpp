#include <iostream>
#include <Windows.h>
#include <graphics.h>
using namespace std;

void welcome(){
	//��ʼ������
	initgraph(550, 600);

	//���ô��ڱ���,��
	HWND hWnd = GetHWnd();//get handle window��þ������,����ǰ���ڷ�װ��
	SetWindowText(hWnd, "����˹����Tetris		ϺϺ");

	//������
	setfont(40, 0, _T("΢���ź�"));//������ֲ��:���г����ַ���ǰ������_T(,�������).
	setcolor(WHITE);
	outtextxy(205, 200, _T("����˹����"));

	//������
	setfont(20, 0, _T("����"));//��֮ǰ�趨�Ĳ�һ��,Ҫд
	//setcolor(WHITE);��֮ǰ�趨��һ��,������д
	outtextxy(185, 300, _T("����һ�����������~"));

	//��ͣ
	Sleep(2000);
}

int main(){
	welcome();

	closegraph();//�ǵùر�
	return 0;
}