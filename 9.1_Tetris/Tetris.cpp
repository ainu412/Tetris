#include <iostream>
#include <Windows.h>
#include <graphics.h>
using namespace std;

void welcome(){
	//��ʼ������
	initgraph(550, 660);

	//���ô��ڱ���,��
	HWND hWnd = GetHWnd();//get handle window��þ������,����ǰ���ڷ�װ��
	SetWindowText(hWnd, "����˹����Tetris		--ϺϺ");

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
int score = 0;
int level = 1;
void gameScene(){
	cleardevice();

	rectangle(27, 27, 336, 635);
	rectangle(29, 29, 334, 633);
	rectangle(370, 50, 515, 195);

	setfont(24, 0, _T("����"));
	outtextxy(405, 215, _T("��һ��"));

	setcolor(RED);
	outtextxy(405, 280, _T("����:"));
	
	//����ֵ����ȫ�ֵ���,����Ϊȫ�ֱ���.��ֹ�����ļ�����������Ϊ��̬.�ȼ�ֵͬ��
	char s_str[16];	sprintf(s_str, _T("%d"), score);
	outtextxy(415, 310, s_str);

	outtextxy(405, 375, _T("�ȼ�:"));
	char l_str[16]; sprintf(l_str, _T("%d"), score);
	outtextxy(425, 405, l_str);

	setcolor(LIGHTBLUE);
	outtextxy(390, 475, "����˵��:");
	outtextxy(390, 500, "��: ��ת");
	outtextxy(390, 525, "��: �½�");
	outtextxy(390, 550, "��: ����");
	outtextxy(390, 575, "��: ����");
	outtextxy(390, 600, "�ո�: ��ͣ");

	system("pause");
}

//˫�㷽��:�Ը߼�

int main(){
	welcome();
	gameScene();


	closegraph();//�ǵùر�
	return 0;
}