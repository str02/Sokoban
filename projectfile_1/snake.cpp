#include "snake.h"
#include<conio.h>
//构造函数
snake::snake()
{
	for (size_t i = 0; i < 6; i++)
	{
		img[i] = 0;
	}
	for (size_t i = 0; i < 5; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
				map[i][j] = 0;
		}
	}
	number_to = 0;
	guan = 1;
}
//素材
void snake::Initimg(IMAGE img[])
{
	loadimage(&img[0], "素材/水泥地.png", 60, 60);
	loadimage(&img[1], "素材/墙.png", 60, 60);
	loadimage(&img[2], "素材/人物.png", 60, 60);
	loadimage(&img[3], "素材/蓝色箱子.png", 60, 60);
	loadimage(&img[4], "素材/终点.png", 60, 60);
	loadimage(&img[5], "素材/以推.jpg", 60, 60);
	loadimage(&img[6], "素材/信息版面.jpg");
	loadimage(&img[7], "素材/开始.jpg", 800, 600);
	loadimage(&img[8], "素材/游戏结束.jpg", 800, 600);
	loadimage(&img[9], "素材/结束.jpg", 150, 80);
	loadimage(&img[10], "素材/左边人物走.png", 60, 60);
	loadimage(&img[11], "素材/右边人物.png", 60, 60);
	loadimage(&img[12], "素材/右边人物走.png", 60, 60);
	loadimage(&img[13], "素材/前面人物.png", 60, 60);
	loadimage(&img[14], "素材/前面人物走.png", 60, 60);
	loadimage(&img[15], "素材/前面人物走2.png", 60, 60);
	loadimage(&img[16], "素材/后面人物.png", 60, 60);
	loadimage(&img[17], "素材/后面人物走.png", 60, 60);
	loadimage(&img[18], "素材/后面人物走2.png", 60, 60);
	loadimage(&img[19], "素材/左边人物走black.png", 60, 60);
	loadimage(&img[20], "素材/人物black.png", 60, 60);
	loadimage(&img[21], "素材/右边人物black.png", 60, 60);
	loadimage(&img[22], "素材/右边人物走black.png", 60, 60);
	loadimage(&img[23], "素材/前面人物black.png", 60, 60);
	loadimage(&img[24], "素材/前面人物走black.png", 60, 60);
	loadimage(&img[25], "素材/前面人物走2black.png", 60, 60);
	loadimage(&img[26], "素材/后面人物black.png", 60, 60);
	loadimage(&img[27], "素材/后面人物走black.png", 60, 60);
	loadimage(&img[28], "素材/后面人物走2black.png", 60, 60);
	loadimage(&img[29], "素材/终点black.png", 60, 60);
	loadimage(&img[30], "素材/蓝色箱子black.png", 60, 60);

}
//入口函数
void snake::init(int data)
{
		//选取地图
	if (data >= 5)
	{
		data = 0;
		if (MessageBox(GetHWnd(), "恭喜你，已经通关的全部关卡，是否重新开始", "GOOD", MB_OKCANCEL) == IDOK)
		{
			state_value = 0;
			//检查栈是否是空的
			while (!mystack.empty())
			{
				mystack.pop();//出栈
				initassist(assistarr, map);
			}
			init(data);
		}
		return;
	}
	else
	{
		map_template(data, map);

	}
		//state_value 表示数值 0没有结束游戏 1游戏通关  -1游戏失败
		printmap();
		while (state_value==0)
		{
			choice();
			win();
		}
		if (state_value == 1)
		{
			if (MessageBox(GetHWnd(), "你赢了 是否进入下一关", "GOOD", MB_OKCANCEL) == IDOK)
			{
				state_value = 0;
				//检查栈是否是空的
				while (!mystack.empty())
				{
					mystack.pop();//出栈
				}
				guan++;
				number_to = 0;
				init(++data);
			}
			else
			{
				show_end();
				closegraph();
				return;
			}
		}
		if (state_value == -1)
		{
			if (MessageBox(GetHWnd(), "你输了 是否重新开始", "Gsorry", MB_OKCANCEL) == IDOK)
			{
				state_value = 0;
				guan = 1;
				number_to = 0;
			}
			else
			{
				state_value = 0;
				show_end();
				closegraph();
				return ;
			}
			init();

		}
};
//人物走动rr
void snake::choice()
{
	size_t x=0, y=0;//确定这个人物的位置 
	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			if (map[i][j] == 2||map[i][j]==6)
			{
				x = i;
				y = j;
			}
		}
	}
	if (((kbhit())!=0))
	{
		switch (_getch())
		{
			//往上走
		case 'w':
		case 'W':
		case 72:
			number_to++;
			//如果前面是空地或者是终点
			if (map[x - 1][y] == 0 || map[x - 1][y] == 4)
			{
				map[x][y] -= 2;
				map[x - 1][y] += 2;
				inputend(0);
			}
			//如果前面是箱子或者是已经完成的箱子
			else if (map[x - 1][y] == 3 || map[x - 1][y] == 7)
			{
				if (map[x - 2][y] == 0 || map[x - 2][y] == 4)
				{
					map[x][y] -= 2;
					map[x - 1][y] -= 1;
					map[x - 2][y] += 3;
					inputend(1);
				}
			}
			rear_move_left();
			Sleep(50);
			rear_move_right();
			Sleep(50);
			rear_move();
			break;
			//往下走
		case 's':
		case 'S':
		case 80:
			number_to++;
			if (map[x + 1][y] == 0 || map[x + 1][y] == 4)
			{
				map[x][y] -= 2;
				map[x + 1][y] += 2;
				inputend(2);
			}
			else if (map[x + 1][y] == 3 || map[x + 1][y] == 7)
			{
				if (map[x + 2][y] == 0 || map[x + 2][y] == 4)
				{
					map[x][y] -= 2;
					map[x + 1][y] -= 1;
					map[x + 2][y] += 3;
					inputend(3);
				}
			}
			front_move_left();
			Sleep(50);
			front_move_right();
			Sleep(50);
			front();

			break;
			//往左走
		case 'a':
		case 'A':
		case 75:
			number_to++;
			if (map[x][y - 1] == 0 || map[x][y - 1] == 4)
			{
				map[x][y] -= 2;
				map[x][y - 1] += 2;
				inputend(4);
			}
			else if (map[x][y - 1] == 3 || map[x][y - 1] == 7)
			{
				if (map[x][y - 2] == 0 || map[x][y - 2] == 4)
				{
					map[x][y] -= 2;
					map[x][y - 1] -= 1;
					map[x][y - 2] += 3;
					inputend(5);

				}
			}
			left_move();
			Sleep(200);
			printmap();
			break;
			//往右走
		case 'd':
		case 'D':
		case 77:
			number_to++;
			if (map[x][y + 1] == 0 || map[x][y + 1] == 4)
			{
				map[x][y] -= 2;
				map[x][y + 1] += 2;
				inputend(6);
			}
			else if (map[x][y + 1] == 3 || map[x][y + 1] == 7)
			{
				if (map[x][y + 2] == 0 || map[x][y + 2] == 4)
				{
					map[x][y] -= 2;
					map[x][y + 1] -= 1;
					map[x][y + 2] += 3;
					inputend(7);

				}
			}
			
			right_move();
			Sleep(200);
			right_up();
			break;
			//退回
		case 'r':
		case 'R':

			if (mystack.empty())
			{
				break;
			}
			else
			{
				returnhead();
				right_up();
			}
			break;
		}
	}
	else if(MouseHit())
	{
	mymouse = GetMouseMsg();
	switch (mymouse.uMsg)
	{
	case WM_LBUTTONDOWN:
		if ((mymouse.x > 625 && mymouse.x < 775) && (mymouse.y > 495 && mymouse.y < 530))
		{
			show_end();
			Sleep(3000);
			closegraph();
			
			exit(0);
		}
		break;
	default:
		break;
	}
	}
}
//判断游戏进程
void snake::win()
{
	int i = 0, j = 0, k = 0;
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			if (map[i][j] == 3)
			{
				k++;//还没有推完的箱子
				if (map[i - 1][j]==1 || map[i + 1][j] == 1|| map[i + 1][j]==7)//检查箱子上下
				{
					if (map[i][j - 1]==1 || map[i][j + 1] == 1 || map[i + 1][j] == 7)//检查箱子左右
					{
						state_value = -1;
						return;
					}
				}
			}
		}

	}
	if (k == 0)//如果箱子全部推完
	{

		state_value = 1;
		return;
	}
	else
	{
		state_value = 0;
		return;
	}
}
//进档
void snake::inputend(size_t data)
{
	mystack.push(data);
}
//回档（游戏回退）
void  snake::returnhead()
{

    
	size_t x=0, y=0;
	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			if (map[i][j] == 2 || map[i][j] == 6)
			{
				x = i;
				y = j;
			}
		}
	}
	switch (mystack.top())
	{
		//往下走
	case 0:
		map[x][y] -= 2;
		map[x + 1][y] += 2;
		break;
		//带箱子往下走
	case 1:
		map[x - 1][y] -= 3;
		map[x][y] += 1;
		map[x + 1][y] += 2;
		break;
		//往上走
	case 2:
		map[x][y] -= 2;
		map[x - 1][y] += 2;
		break;
		//带箱子往上走
	case 3:
		map[x - 1][y] += 2;
		map[x][y] += 1;
		map[x+1][y] -= 3;
		break;
		//往右走
	case 4:
		map[x][y] -= 2;
		map[x][y + 1] += 2;
		break;
		//带箱子往右走
	case 5:
		map[x][y + 1] += 2;
		map[x][y] += 1;
		map[x][y - 1] -= 3;
		break;
		//往左走
	case 6:
		map[x][y] -= 2;
		map[x][y -1] += 2;
		break;
		//带箱子往左走
	case 7:
		map[x][y + 1] -= 3;
		map[x][y] += 1;
		map[x][y - 1] += 2;
		break;
	}
	
	mystack.pop();
	
}
//地图模板
void snake::map_template(int number,size_t map[][10])
{
	
	size_t mymap[5][10][10] = {
	{
	{0,0,0,0,0,0,0,0,0,0 },
	{0,1,1,1,1,1,1,1,1,0 },
	{0,1,0,0,0,0,0,2,1,0 },
	{0,1,0,3,0,0,0,0,1,0 },
	{0,1,1,1,1,0,0,0,1,0 },
	{0,1,1,0,0,0,1,1,1,0 },
	{0,1,0,0,0,0,0,0,1,0 },
	{0,1,1,4,0,0,0,0,1,0 },
	{0,1,1,1,1,1,1,1,1,0 },
	{0,0,0,0,0,0,0,0,0,0 },
	},
	{
	{0,0,0,0,0,0,0,0,0,0 },
	{0,1,1,1,1,1,1,1,0,0 },
	{0,1,0,2,0,0,0,0,1,0 },
	{0,1,3,3,3,3,0,4,1,0 },
	{0,1,4,0,0,0,0,1,0,0 },
	{0,1,0,0,0,1,0,1,0,0 },
	{0,1,1,0,0,0,1,0,0,0 },
	{0,0,1,4,0,0,4,1,0,0 },
	{0,1,1,1,1,1,1,1,0,0 },
	{0,0,0,0,0,0,0,0,0,0 },
	},{
	{0,0,0,0,0,0,0,0,0,0 },
	{0,1,1,1,1,1,1,1,0,0 },
	{0,1,0,2,0,0,0,0,1,0 },
	{0,1,3,3,3,3,0,4,1,0 },
	{0,1,4,0,0,0,0,1,0,0 },
	{0,1,0,0,0,1,0,1,0,0 },
	{0,1,1,0,0,0,1,0,0,0 },
	{0,0,1,4,0,0,4,1,0,0 },
	{0,1,1,1,1,1,1,1,0,0 },
	{0,0,0,0,0,0,0,0,0,0 },
	},{
	{0,0,0,0,0,0,0,0,0,0 },
	{0,1,1,1,1,1,1,1,0,0 },
	{0,1,0,2,0,0,0,0,1,0 },
	{0,1,3,3,3,3,0,4,1,0 },
	{0,1,4,0,0,1,0,1,0,0 },
	{0,1,0,0,0,1,0,1,0,0 },
	{0,1,1,0,0,0,1,0,0,0 },
	{0,0,1,4,0,0,4,1,0,0 },
	{0,1,1,1,1,1,1,1,0,0 },
	{0,0,0,0,0,0,0,0,0,0 },
	},{
	{0,0,0,0,0,0,0,0,0,0 },
	{0,1,1,1,1,1,1,1,0,0 },
	{0,1,0,2,0,0,0,0,1,0 },
	{0,1,3,3,3,3,0,4,1,0 },
	{0,1,4,0,0,0,0,1,0,0 },
	{0,1,0,0,0,1,0,1,0,0 },
	{0,1,1,1,0,0,1,0,0,0 },
	{0,0,1,4,0,0,4,1,0,0 },
	{0,1,1,1,1,1,1,1,0,0 },
	{0,0,0,0,0,0,0,0,0,0 },
	}, };
	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			map[i][j] = mymap[number][i][j];
		}
	}
}
//栈
/*void snake::stack(int)
{
	typedef struct stack
	{
		int data;
		struct stack* nest;
	};
	typedef struct noet
	{
		struct stack* head;
	};

}*/
//辅助地图数组
void snake::initassist(assists assistarr[][10], size_t maparr[][10])
{
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			assistarr[i][j].assist = maparr[i][j];
			assistarr[i][j].isfind = false;
			assistarr[i][j].dir = up;
		}

	}
}

void snake::show_number_to()
{
	char inr[10] ;
	itoa(number_to, inr, 10);
	settextcolor(RGB(79, 160, 178));
	settextstyle(20, 0, _T("华文仿宋"));
	outtextxy(620, 180, _T("步数"));
	//wchar_t str_sc[40] = { 0 };
	//swprintf(str_sc, 40, L"%d", this->number_to);
	outtextxy(670, 180, inr);
}
void snake::show_guan()
{
	char inr[10];
	itoa(guan, inr, 10);
	settextcolor(RGB(79, 160, 178));
	settextstyle(20, 0, _T("华文仿宋"));
	outtextxy(620, 240, _T("关卡"));

	/*wchar_t str_sc[12] = { 0 };
	swprintf(str_sc,12, L"%d", this->guan);*/
	outtextxy(670, 240, inr);
}
void snake::stack_game()
{
	BeginBatchDraw();
	putimage(0, 0, &img[7]);
	EndBatchDraw();
	
	while (true)
	{
		mymouse = GetMouseMsg();
		switch (mymouse.uMsg)
		{
		case WM_LBUTTONDOWN:
			if ((mymouse.x > 150 && mymouse.x < 650) && (mymouse.y > 225 && mymouse.y < 375))
			{
				init();
				return;
			}
			
		default:
			break;
		}
	}
	
}
void snake::show_end()
{
	BeginBatchDraw();
	putimage(0, 0, &img[8]);
	EndBatchDraw();
	Sleep(3000);
}
void snake::left_move()
{
	BeginBatchDraw();
	setbkmode(TRANSPARENT);
	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			switch (map[i][j])
			{
			case 0:
				putimage(j * 60, i * 60, &img[0]);
				break;
			case 1:
				putimage(j * 60, i * 60, &img[1]);
				break;
			case 2:
				putimage(j * 60, i * 60, &img[0]);//必须要有底色才可以 不然无法中和颜色
				putimage(j * 60, i * 60, &img[19],NOTSRCERASE);
				putimage(j * 60, i * 60, &img[10],SRCINVERT);
				break;
			case 3:
				putimage(j * 60, i * 60, &img[0]);
				putimage(j * 60, i * 60, &img[30], NOTSRCERASE);
				putimage(j * 60, i * 60, &img[3], SRCINVERT);
				break;
			case 4:
				putimage(j * 60, i * 60, &img[0]);
				putimage(j * 60, i * 60, &img[29],NOTSRCERASE);
				putimage(j * 60, i * 60, &img[4], SRCINVERT);
				break;
			case 6:
				putimage(j * 60, i * 60, &img[0]);
				putimage(j * 60, i * 60, &img[20], NOTSRCERASE);
				putimage(j * 60, i * 60, &img[2], SRCINVERT);
				break;
			case 7:
				putimage(j * 60, i * 60, &img[5]);
				break;
			}

		}
	}
	putimage(600, 0, &img[6]);
	putimage(625, 470, &img[9]);
	show_number_to();
	show_guan();
	EndBatchDraw();
}
//输出地图
void snake::printmap()
{
	BeginBatchDraw();
	setbkmode(TRANSPARENT);
	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			switch (map[i][j])
			{
			case 0:
				putimage(j * 60, i * 60, &img[0]);
				break;
			case 1:
				putimage(j * 60, i * 60, &img[1]);
				break;
			case 2:
				putimage(j * 60, i * 60, &img[0]);
				putimage(j * 60, i * 60, &img[20], NOTSRCERASE);
				putimage(j * 60, i * 60, &img[2], SRCINVERT);
				break;
			case 3:
				putimage(j * 60, i * 60, &img[0]);
				putimage(j * 60, i * 60, &img[30], NOTSRCERASE);
				putimage(j * 60, i * 60, &img[3], SRCINVERT);
				break;
			case 4:
				putimage(j * 60, i * 60, &img[0]);
				putimage(j * 60, i * 60, &img[29], NOTSRCERASE);
				putimage(j * 60, i * 60, &img[4], SRCINVERT);
				break;
			case 6:
				putimage(j * 60, i * 60, &img[0]);
				putimage(j * 60, i * 60, &img[20], NOTSRCERASE);
				putimage(j * 60, i * 60, &img[2], SRCINVERT);
				break;
			case 7:
				putimage(j * 60, i * 60, &img[5]);
				break;
			}

		}
	}
	putimage(600, 0, &img[6]);
	putimage(625, 470, &img[9]);
	show_number_to();
	show_guan();
	EndBatchDraw();
}
void snake::right_up()
{
	BeginBatchDraw();
	setbkmode(TRANSPARENT);
	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			switch (map[i][j])
			{
			case 0:
				putimage(j * 60, i * 60, &img[0]);
				break;
			case 1:
				putimage(j * 60, i * 60, &img[1]);
				break;
			case 2:
				putimage(j * 60, i * 60, &img[0]);
				putimage(j * 60, i * 60, &img[21], NOTSRCERASE);
				putimage(j * 60, i * 60, &img[11], SRCINVERT);
				break;
			case 3:
				putimage(j * 60, i * 60, &img[0]);
				putimage(j * 60, i * 60, &img[30], NOTSRCERASE);
				putimage(j * 60, i * 60, &img[3], SRCINVERT);
				break;
			case 4:
				putimage(j * 60, i * 60, &img[0]);
				putimage(j * 60, i * 60, &img[29], NOTSRCERASE);
				putimage(j * 60, i * 60, &img[4], SRCINVERT);
				break;
			case 6:
				putimage(j * 60, i * 60, &img[0]);
				putimage(j * 60, i * 60, &img[21], NOTSRCERASE);
				putimage(j * 60, i * 60, &img[11], SRCINVERT);
				break;
			case 7:
				putimage(j * 60, i * 60, &img[5]);
				break;
			}

		}
	}
	putimage(600, 0, &img[6]);
	putimage(625, 470, &img[9]);
	show_number_to();
	show_guan();
	EndBatchDraw();
}
void snake::right_move()
{
	BeginBatchDraw();
	setbkmode(TRANSPARENT);
	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			switch (map[i][j])
			{
			case 0:
				putimage(j * 60, i * 60, &img[0]);
				break;
			case 1:
				putimage(j * 60, i * 60, &img[1]);
				break;
			case 2:
				putimage(j * 60, i * 60, &img[0]);
				putimage(j * 60, i * 60, &img[22], NOTSRCERASE);
				putimage(j * 60, i * 60, &img[12], SRCINVERT);
				break;
			case 3:
				putimage(j * 60, i * 60, &img[0]);
				putimage(j * 60, i * 60, &img[30], NOTSRCERASE);
				putimage(j * 60, i * 60, &img[3], SRCINVERT);
				break;
			case 4:
				putimage(j * 60, i * 60, &img[0]);
				putimage(j * 60, i * 60, &img[29], NOTSRCERASE);
				putimage(j * 60, i * 60, &img[4], SRCINVERT);
				break;
			case 6:
				putimage(j * 60, i * 60, &img[0]);
				putimage(j * 60, i * 60, &img[22], NOTSRCERASE);
				putimage(j * 60, i * 60, &img[12], SRCINVERT);
				break;
			case 7:
				putimage(j * 60, i * 60, &img[5]);
				break;
			}

		}
	}
	putimage(600, 0, &img[6]);
	putimage(625, 470, &img[9]);
	show_number_to();
	show_guan();
	EndBatchDraw();
}
void snake::front()
{
	BeginBatchDraw();
	setbkmode(TRANSPARENT);
	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			switch (map[i][j])
			{
			case 0:
				putimage(j * 60, i * 60, &img[0]);
				break;
			case 1:
				putimage(j * 60, i * 60, &img[1]);
				break;
			case 2:
				putimage(j * 60, i * 60, &img[0]);
				putimage(j * 60, i * 60, &img[23], NOTSRCERASE);
				putimage(j * 60, i * 60, &img[13], SRCINVERT);
				break;
			case 3:
				putimage(j * 60, i * 60, &img[0]);
				putimage(j * 60, i * 60, &img[30], NOTSRCERASE);
				putimage(j * 60, i * 60, &img[3], SRCINVERT);
				break;
			case 4:
				putimage(j * 60, i * 60, &img[0]);
				putimage(j * 60, i * 60, &img[29], NOTSRCERASE);
				putimage(j * 60, i * 60, &img[4], SRCINVERT);
				break;
			case 6:
				putimage(j * 60, i * 60, &img[0]);
				putimage(j * 60, i * 60, &img[23], NOTSRCERASE);
				putimage(j * 60, i * 60, &img[13], SRCINVERT);
				break;
			case 7:
				putimage(j * 60, i * 60, &img[5]);
				break;
			}

		}
	}
	putimage(600, 0, &img[6]);
	putimage(625, 470, &img[9]);
	show_number_to();
	show_guan();
	EndBatchDraw();

}
void snake::front_move_left()
{
	BeginBatchDraw();
	setbkmode(TRANSPARENT);
	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			switch (map[i][j])
			{
			case 0:
				putimage(j * 60, i * 60, &img[0]);
				break;
			case 1:
				putimage(j * 60, i * 60, &img[1]);
				break;
			case 2:
				putimage(j * 60, i * 60, &img[0]);
				putimage(j * 60, i * 60, &img[24], NOTSRCERASE);
				putimage(j * 60, i * 60, &img[14], SRCINVERT);
				break;
			case 3:
				putimage(j * 60, i * 60, &img[0]);
				putimage(j * 60, i * 60, &img[30], NOTSRCERASE);
				putimage(j * 60, i * 60, &img[3], SRCINVERT);
				break;
			case 4:
				putimage(j * 60, i * 60, &img[0]);
				putimage(j * 60, i * 60, &img[29], NOTSRCERASE);
				putimage(j * 60, i * 60, &img[4], SRCINVERT);
				break;
			case 6:
				putimage(j * 60, i * 60, &img[0]);
				putimage(j * 60, i * 60, &img[24], NOTSRCERASE);
				putimage(j * 60, i * 60, &img[14], SRCINVERT);
				break;
			case 7:
				putimage(j * 60, i * 60, &img[5]);
				break;
			}

		}
	}
	putimage(600, 0, &img[6]);
	putimage(625, 470, &img[9]);
	show_number_to();
	show_guan();
	EndBatchDraw();
}

void snake::front_move_right()
{
	BeginBatchDraw();
	setbkmode(TRANSPARENT);
	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			switch (map[i][j])
			{
			case 0:
				putimage(j * 60, i * 60, &img[0]);
				break;
			case 1:
				putimage(j * 60, i * 60, &img[1]);
				break;
			case 2:
				putimage(j * 60, i * 60, &img[0]);
				putimage(j * 60, i * 60, &img[25], NOTSRCERASE);
				putimage(j * 60, i * 60, &img[15], SRCINVERT);
				break;
			case 3:
				putimage(j * 60, i * 60, &img[0]);
				putimage(j * 60, i * 60, &img[30], NOTSRCERASE);
				putimage(j * 60, i * 60, &img[3], SRCINVERT);
				break;
			case 4:
				putimage(j * 60, i * 60, &img[0]);
				putimage(j * 60, i * 60, &img[29], NOTSRCERASE);
				putimage(j * 60, i * 60, &img[4], SRCINVERT);
				break;
			case 6:
				putimage(j * 60, i * 60, &img[0]);
				putimage(j * 60, i * 60, &img[25], NOTSRCERASE);
				putimage(j * 60, i * 60, &img[15], SRCINVERT);
				break;
			case 7:
				putimage(j * 60, i * 60, &img[5]);
				break;
			}

		}
	}
	putimage(600, 0, &img[6]);
	putimage(625, 470, &img[9]);
	show_number_to();
	show_guan();
	EndBatchDraw();
}
void snake::rear_move()
{
	BeginBatchDraw();
	setbkmode(TRANSPARENT);
	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			switch (map[i][j])
			{
			case 0:
				putimage(j * 60, i * 60, &img[0]);
				break;
			case 1:
				putimage(j * 60, i * 60, &img[1]);
				break;
			case 2:
				putimage(j * 60, i * 60, &img[0]);
				putimage(j * 60, i * 60, &img[26], NOTSRCERASE);
				putimage(j * 60, i * 60, &img[16], SRCINVERT);
				break;
			case 3:
				putimage(j * 60, i * 60, &img[0]);
				putimage(j * 60, i * 60, &img[30], NOTSRCERASE);
				putimage(j * 60, i * 60, &img[3], SRCINVERT);
				break;
			case 4:
				putimage(j * 60, i * 60, &img[0]);
				putimage(j * 60, i * 60, &img[29], NOTSRCERASE);
				putimage(j * 60, i * 60, &img[4], SRCINVERT);
				break;
			case 6:
				putimage(j * 60, i * 60, &img[0]);
				putimage(j * 60, i * 60, &img[26], NOTSRCERASE);
				putimage(j * 60, i * 60, &img[16], SRCINVERT);
				break;
			case 7:
				putimage(j * 60, i * 60, &img[5]);
				break;
			}

		}
	}
	putimage(600, 0, &img[6]);
	putimage(625, 470, &img[9]);
	show_number_to();
	show_guan();
	EndBatchDraw();
}
void snake::rear_move_left()
{
	BeginBatchDraw();
	setbkmode(TRANSPARENT);
	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			switch (map[i][j])
			{
			case 0:
				putimage(j * 60, i * 60, &img[0]);
				break;
			case 1:
				putimage(j * 60, i * 60, &img[1]);
				break;
			case 2:
				putimage(j * 60, i * 60, &img[0]);
				putimage(j * 60, i * 60, &img[27], NOTSRCERASE);
				putimage(j * 60, i * 60, &img[17], SRCINVERT);
				break;
			case 3:
				putimage(j * 60, i * 60, &img[0]);
				putimage(j * 60, i * 60, &img[30], NOTSRCERASE);
				putimage(j * 60, i * 60, &img[3], SRCINVERT);
				break;
			case 4:
				putimage(j * 60, i * 60, &img[0]);
				putimage(j * 60, i * 60, &img[29], NOTSRCERASE);
				putimage(j * 60, i * 60, &img[4], SRCINVERT);
				break;
			case 6:
				putimage(j * 60, i * 60, &img[0]);
				putimage(j * 60, i * 60, &img[27], NOTSRCERASE);
				putimage(j * 60, i * 60, &img[17], SRCINVERT);
				break;
			case 7:
				putimage(j * 60, i * 60, &img[5]);
				break;
			}

		}
	}
	putimage(600, 0, &img[6]);
	putimage(625, 470, &img[9]);
	show_number_to();
	show_guan();
	EndBatchDraw();
}
void snake::rear_move_right()
{
	BeginBatchDraw();
	setbkmode(TRANSPARENT);
	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			switch (map[i][j])
			{
			case 0:
				putimage(j * 60, i * 60, &img[0]);
				break;
			case 1:
				putimage(j * 60, i * 60, &img[1]);
				break;
			case 2:
				putimage(j * 60, i * 60, &img[0]);
				putimage(j * 60, i * 60, &img[28], NOTSRCERASE);
				putimage(j * 60, i * 60, &img[18], SRCINVERT);
				break;
			case 3:
				putimage(j * 60, i * 60, &img[0]);
				putimage(j * 60, i * 60, &img[30], NOTSRCERASE);
				putimage(j * 60, i * 60, &img[3], SRCINVERT);
				break;
			case 4:
				putimage(j * 60, i * 60, &img[0]);
				putimage(j * 60, i * 60, &img[29], NOTSRCERASE);
				putimage(j * 60, i * 60, &img[4], SRCINVERT);
				break;
			case 6:
				putimage(j * 60, i * 60, &img[0]);
				putimage(j * 60, i * 60, &img[28], NOTSRCERASE);
				putimage(j * 60, i * 60, &img[18], SRCINVERT);
				break;
			case 7:
				putimage(j * 60, i * 60, &img[5]);
				break;
			}

		}
	}
	putimage(600, 0, &img[6]);
	putimage(625, 470, &img[9]);
	show_number_to();
	show_guan();
	EndBatchDraw();
}
//析构函数
snake::~snake()
{
	closegraph();
	exit(0);
}