#pragma once
enum direction { up, left, below, right };//这是我准备四个方位
struct spot { int low; int hight; };//这是辅助行走的下标
struct assists
{
	int assist;//地图的数值
	bool isfind;//是否查找
	direction dir;//他的方位
};
