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
	//״ֵ̬
	int state_value;
	//����Ѿ�ѡȡ�ĵ�ͼ
	size_t map[10][10];
	//��ں���
	void init(int data=0);
	//�ж���Ϸ����
	void win();
	//���زķ�������
	void Initimg(IMAGE[]);
	//����һ�����Դ��ͼƬ��Ϣ����������
	IMAGE img[35];
	//��ʼ��Ϸ����
	void stack_game();
public:
	//������ͼ����
	assists assistarr[10][10];
	//��ʼ����������
	void initassist(assists assistarr[][10], size_t maparr[][10]);
	spot beginspot;//���������
	spot endlspot;//Ҫ�����յ�
	spot assistpot;//��ǰλ��
private:
	 //�����ͼ
	 void printmap();
	 //��ͼģ��
	 void  map_template(int number, size_t map[][10]);
private:
	//�����߶�
	void choice();
	//ջ
	//void stack(int);
	//����
	void inputend(size_t);
	//�ص�
	void returnhead();
private:
	//���߲���
	int number_to;
	//�ؿ�
	int guan;
	//�����Ϣ
	MOUSEMSG mymouse;
	//��ʾ������Ϣ
	void show_number_to();
	//��ʾ�ؿ���Ϣ
	void show_guan();
	//��ʾ��������
	void show_end();
private:
	//����ƶ�
	void left_move();
	//�ұ�
	void right_up();
	//�ұ��ƶ�
	void right_move();
	//ǰ���ƶ�
	void front();
	void front_move_left();
	void front_move_right();
	//�����ƶ�
	void rear_move();
	void rear_move_left();
	void rear_move_right();
};

