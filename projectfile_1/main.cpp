/*
ֻ��һ�������ӵ���Ϸ
����ʱ�� 2019-9-10
��д�� ĺ��
welconme your using the do'is new fine game
thank your using in finese date to
�յ�0  ǽ�� 1  ���� 2  ���� 3  Ŀ��4    */
#include<iostream>
#include<windows.h>
#include<time.h> 
#include<stdio.h>
#include<math.h>
#include"snake.h"
#include"filesnake.h"
#include<easyx.h>
#include<conio.h>
#include<mmsystem.h>
#pragma comment(lib, "winmm.lib")
using std::cout;
using std::endl;
snake mysnake;
int main()
{
	
	//����������ļ�
	mciSendString("open mp3/jjj.mp3", 0, 0, 0);
	//������������ļ�
	mciSendString("play  mp3/jjj.mp3", 0, 0, 0);
	//����һ������Ϊ600*600�Ŀ�
	initgraph(800, 600);
	//��ȡ�����ͼ�ز�
	mysnake.Initimg(mysnake.img);
	//������Ϸѭ��
	mysnake.stack_game();
	return 0;
}
