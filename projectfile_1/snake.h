#pragma once
#include<easyx.h>
#include<stack>
#include"filesnake.h"
#include<string>
using std::stack;
class snake
{
public:
	stack<int> mystack;
	snake();
	~snake();
public:
	//状态值
	int state_value;
	//存放已经选取的地图
	size_t map[10][10];
	//入口函数
	void init(int data=0);
	//判断游戏进程
	void win();
	//将素材放入数组
	void Initimg(IMAGE[]);
	//声明一个可以存放图片信息的数据类型
	IMAGE img[35];
	//开始游戏界面
	void stack_game();
public:
	//辅助地图数组
	assists assistarr[10][10];
	//初始化辅助数组
	void initassist(assists assistarr[][10], size_t maparr[][10]);
	spot beginspot;//辅助的起点
	spot endlspot;//要到的终点
	spot assistpot;//当前位置
private:
	 //输出地图
	 void printmap();
	 //地图模版
	 void  map_template(int number, size_t map[][10]);
private:
	//人物走动
	void choice();
	//栈
	//void stack(int);
	//进档
	void inputend(size_t);
	//回档
	void returnhead();
private:
	//行走步数
	int number_to;
	//关卡
	int guan;
	//鼠标消息
	MOUSEMSG mymouse;
	//显示步数信息
	void show_number_to();
	//显示关卡信息
	void show_guan();
	//显示结束画面
	void show_end();
private:
	//左边移动
	void left_move();
	//右边
	void right_up();
	//右边移动
	void right_move();
	//前面移动
	void front();
	void front_move_left();
	void front_move_right();
	//后面移动
	void rear_move();
	void rear_move_left();
	void rear_move_right();
};

