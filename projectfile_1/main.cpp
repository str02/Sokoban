/*
只是一个推向子的游戏
创建时间 2019-9-10
编写人 暮齐
welconme your using the do'is new fine game
thank your using in finese date to
空地0  墙壁 1  人物 2  箱子 3  目标4    */
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
	
	//打开这个音乐文件
	mciSendString("open mp3/jjj.mp3", 0, 0, 0);
	//播放这个音乐文件
	mciSendString("play  mp3/jjj.mp3", 0, 0, 0);
	//设置一个长宽为600*600的框
	initgraph(800, 600);
	//获取这个地图素材
	mysnake.Initimg(mysnake.img);
	//进入游戏循环
	mysnake.stack_game();
	return 0;
}
