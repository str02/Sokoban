#pragma once
enum direction { up, left, below, right };//������׼���ĸ���λ
struct spot { int low; int hight; };//���Ǹ������ߵ��±�
struct assists
{
	int assist;//��ͼ����ֵ
	bool isfind;//�Ƿ����
	direction dir;//���ķ�λ
};
