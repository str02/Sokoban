#include "snake.h"
#include<conio.h>
//���캯��
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
//�ز�
void snake::Initimg(IMAGE img[])
{
	loadimage(&img[0], "�ز�/ˮ���.png", 60, 60);
	loadimage(&img[1], "�ز�/ǽ.png", 60, 60);
	loadimage(&img[2], "�ز�/����.png", 60, 60);
	loadimage(&img[3], "�ز�/��ɫ����.png", 60, 60);
	loadimage(&img[4], "�ز�/�յ�.png", 60, 60);
	loadimage(&img[5], "�ز�/����.jpg", 60, 60);
	loadimage(&img[6], "�ز�/��Ϣ����.jpg");
	loadimage(&img[7], "�ز�/��ʼ.jpg", 800, 600);
	loadimage(&img[8], "�ز�/��Ϸ����.jpg", 800, 600);
	loadimage(&img[9], "�ز�/����.jpg", 150, 80);
	loadimage(&img[10], "�ز�/���������.png", 60, 60);
	loadimage(&img[11], "�ز�/�ұ�����.png", 60, 60);
	loadimage(&img[12], "�ز�/�ұ�������.png", 60, 60);
	loadimage(&img[13], "�ز�/ǰ������.png", 60, 60);
	loadimage(&img[14], "�ز�/ǰ��������.png", 60, 60);
	loadimage(&img[15], "�ز�/ǰ��������2.png", 60, 60);
	loadimage(&img[16], "�ز�/��������.png", 60, 60);
	loadimage(&img[17], "�ز�/����������.png", 60, 60);
	loadimage(&img[18], "�ز�/����������2.png", 60, 60);
	loadimage(&img[19], "�ز�/���������black.png", 60, 60);
	loadimage(&img[20], "�ز�/����black.png", 60, 60);
	loadimage(&img[21], "�ز�/�ұ�����black.png", 60, 60);
	loadimage(&img[22], "�ز�/�ұ�������black.png", 60, 60);
	loadimage(&img[23], "�ز�/ǰ������black.png", 60, 60);
	loadimage(&img[24], "�ز�/ǰ��������black.png", 60, 60);
	loadimage(&img[25], "�ز�/ǰ��������2black.png", 60, 60);
	loadimage(&img[26], "�ز�/��������black.png", 60, 60);
	loadimage(&img[27], "�ز�/����������black.png", 60, 60);
	loadimage(&img[28], "�ز�/����������2black.png", 60, 60);
	loadimage(&img[29], "�ز�/�յ�black.png", 60, 60);
	loadimage(&img[30], "�ز�/��ɫ����black.png", 60, 60);

}
//��ں���
void snake::init(int data)
{
		//ѡȡ��ͼ
	if (data >= 5)
	{
		data = 0;
		if (MessageBox(GetHWnd(), "��ϲ�㣬�Ѿ�ͨ�ص�ȫ���ؿ����Ƿ����¿�ʼ", "GOOD", MB_OKCANCEL) == IDOK)
		{
			state_value = 0;
			//���ջ�Ƿ��ǿյ�
			while (!mystack.empty())
			{
				mystack.pop();//��ջ
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
		//state_value ��ʾ��ֵ 0û�н�����Ϸ 1��Ϸͨ��  -1��Ϸʧ��
		printmap();
		while (state_value==0)
		{
			choice();
			win();
		}
		if (state_value == 1)
		{
			if (MessageBox(GetHWnd(), "��Ӯ�� �Ƿ������һ��", "GOOD", MB_OKCANCEL) == IDOK)
			{
				state_value = 0;
				//���ջ�Ƿ��ǿյ�
				while (!mystack.empty())
				{
					mystack.pop();//��ջ
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
			if (MessageBox(GetHWnd(), "������ �Ƿ����¿�ʼ", "Gsorry", MB_OKCANCEL) == IDOK)
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
//�����߶�rr
void snake::choice()
{
	size_t x=0, y=0;//ȷ����������λ�� 
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
			//������
		case 'w':
		case 'W':
		case 72:
			number_to++;
			//���ǰ���ǿյػ������յ�
			if (map[x - 1][y] == 0 || map[x - 1][y] == 4)
			{
				map[x][y] -= 2;
				map[x - 1][y] += 2;
				inputend(0);
			}
			//���ǰ�������ӻ������Ѿ���ɵ�����
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
			//������
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
			//������
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
			//������
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
			//�˻�
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
//�ж���Ϸ����
void snake::win()
{
	int i = 0, j = 0, k = 0;
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			if (map[i][j] == 3)
			{
				k++;//��û�����������
				if (map[i - 1][j]==1 || map[i + 1][j] == 1|| map[i + 1][j]==7)//�����������
				{
					if (map[i][j - 1]==1 || map[i][j + 1] == 1 || map[i + 1][j] == 7)//�����������
					{
						state_value = -1;
						return;
					}
				}
			}
		}

	}
	if (k == 0)//�������ȫ������
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
//����
void snake::inputend(size_t data)
{
	mystack.push(data);
}
//�ص�����Ϸ���ˣ�
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
		//������
	case 0:
		map[x][y] -= 2;
		map[x + 1][y] += 2;
		break;
		//������������
	case 1:
		map[x - 1][y] -= 3;
		map[x][y] += 1;
		map[x + 1][y] += 2;
		break;
		//������
	case 2:
		map[x][y] -= 2;
		map[x - 1][y] += 2;
		break;
		//������������
	case 3:
		map[x - 1][y] += 2;
		map[x][y] += 1;
		map[x+1][y] -= 3;
		break;
		//������
	case 4:
		map[x][y] -= 2;
		map[x][y + 1] += 2;
		break;
		//������������
	case 5:
		map[x][y + 1] += 2;
		map[x][y] += 1;
		map[x][y - 1] -= 3;
		break;
		//������
	case 6:
		map[x][y] -= 2;
		map[x][y -1] += 2;
		break;
		//������������
	case 7:
		map[x][y + 1] -= 3;
		map[x][y] += 1;
		map[x][y - 1] += 2;
		break;
	}
	
	mystack.pop();
	
}
//��ͼģ��
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
//ջ
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
//������ͼ����
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
	settextstyle(20, 0, _T("���ķ���"));
	outtextxy(620, 180, _T("����"));
	//wchar_t str_sc[40] = { 0 };
	//swprintf(str_sc, 40, L"%d", this->number_to);
	outtextxy(670, 180, inr);
}
void snake::show_guan()
{
	char inr[10];
	itoa(guan, inr, 10);
	settextcolor(RGB(79, 160, 178));
	settextstyle(20, 0, _T("���ķ���"));
	outtextxy(620, 240, _T("�ؿ�"));

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
				putimage(j * 60, i * 60, &img[0]);//����Ҫ�е�ɫ�ſ��� ��Ȼ�޷��к���ɫ
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
//�����ͼ
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
//��������
snake::~snake()
{
	closegraph();
	exit(0);
}