#include "process.h"
#include "main.h"

prepare game;
int max = 0; int grade = 0;
process Game;

void process::EnterFace() {
	game.color(7);
	game.CursorJump(game.COLS / 2, game.LINES / 2 - 4);

	std::cout << "   欢迎来到俄罗斯方块\n\n	  是否开始游戏 是(y) 否(n)";
	char c;
	while (1) {
		std::cin >> c;
		getchar();
		if (c == 'y' || c == 'Y') {
			system("cls");
			break;
		}
		else if (c == 'n' || c == 'N') {
			std::exit(0);
		}
		else {
			system("cls");
			game.CursorJump(game.COLS / 2, game.LINES / 2 - 4);
			std::cout << "输入错误，请重新输入";
		}
		
	}
}

void process::BlockControl() {
	game.color(7);
	game.CursorJump(2 * game.COLS + 14, game.LINES - 5);
	std::cout << max;//展示分数
	srand(time(NULL));
	int shape = rand() % 7;
	int form = rand() % 4;

	game.InitFace();
	game.InitBlock();//第一次修改尝试添加chu

	while (1) {
		int x = game.COLS / 2 - 2; int y = 0;
		int nextshape = rand() % 7; int nextform = rand() % 4;
		DrawBlock(game.COLS + 3, 3,nextshape,nextform);
		while (1) {
			DrawBlock(x, y, shape, form);
			int t = 8888;
			while (--t) {  //t-- 和 --t 差别
				if (kbhit() != 0) //如果点击了键盘，则不再t不再减少
					break;
			}
			if (t == 0) {
				if (Islegal(x, y + 1, shape, form) == 0) {
					for (int i = 0; i < 4; i++) {
						for (int j = 0; j < 4; j++) {
							if (game.block[shape][form].space[i][j] == 1) {
								game.face.data[y + i][x + j] = 1;
								game.face.color[y + i][x + j] = shape;	
							}
						}
					}
					while (BlockRemove(grade, max));
					break;
				}
				else
				{
					DrawSpace(x, y, shape, form);
					y++;
					
				}
			}
			else//按键 控制移动
			{
				char ch = getch();
				switch (ch) {
				case LEFT:
					if (Islegal(x - 1, y + 1, shape, form) == 1) {
						DrawSpace(x, y, shape, form);
						x--;
						y++;
					}
					break;
				case RIGHT:
					if (Islegal(x + 1, y + 1, shape, form) == 1) {
						DrawSpace(x, y, shape, form);
						x++;
						y++;
					}
					break;
				case DOWN:
					if (Islegal(x , y + 1, shape, form) == 1) {
						DrawSpace(x, y, shape, form);
						y++;
					}
					break;
				case SPACE:
					if (Islegal(x , y + 1, shape,(form + 1) % 4) == 1) {
						DrawSpace(x, y, shape, form);
						y++;
						form = (form + 1) % 4;
					}
					break;
				case 'R':
				case 'r':
					system("cls");
					main();
					break;
				case 'S':
				case 's':
					system("pause > nul");
					break;
				case ESC:
					system("cls");
					game.color(7);
					game.CursorJump(game.COLS, game.LINES / 2);
					std::cout << "游戏结束，谢谢你的体验";
					exit(0);
					break;

				}
			}
			
		}
		shape = nextshape; form = nextform;
		DrawSpace(game.COLS + 3, 3, shape, form);

	}
}


void process::DrawBlock(int x,int y,int shape,int form) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (game.block[shape][form].space[i][j] == 1)
			{
				game.color(shape);
				game.CursorJump((x + j) * 2, y + i);
				std::cout << "■";
			}
		}
	}
}
void process::DrawSpace(int x, int y, int shape, int form) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (game.block[shape][form].space[i][j] == 1)
			{
				game.CursorJump((x + j) * 2, y + i);
				std::cout << "  ";
			}
		}
	}
}

int process::Islegal(int x, int y, int shape, int form) {
	
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (game.block[shape][form].space[i][j] == 1 && game.face.data[y + i][x + j] == 1)
				return 0;
		}
	}
	return 1; //修改处 注意位置
}//判断是否接触到方块

//检查方块不能移动时是否满足清行要求
int process::BlockRemove(int &grade,int &max) {

	//从最后一行开始向上逐层检查每行方块的数目
	for (int i = game.LINES - 2; i > 4; i--) {
		int sum = 0;
		for (int j = 1; j < game.COLS - 1; j++) {
			sum += game.face.data[i][j];
		}
			if (sum == 0)
				break;//若符合该条件说明已到堆放方块的最高层的上一层
			if (sum == game.COLS - 2) {
				grade += 10;
				game.color(7);
				game.CursorJump(2 * game.COLS + 14, game.LINES - 3);
				std::cout << grade;//展示分数
				for (int j = 1; j < game.COLS - 1; j++) {
					game.face.data[i][j] = 0;
					game.CursorJump(2 * j, i);
					std::cout << "  ";
				}//清除掉该行的方块
				//将清除行以上的方块下移
				for (int m = i; m > 1; m--) {
					int sum = 0;//记录清除行以上层的每层的方块数目
					for (int j = 1; j < game.COLS - 1; j++) {
						sum += game.face.data[m - 1][j];


						game.face.data[m][j] = game.face.data[m - 1][j];
						game.face.color[m][j] = game.face.color[m - 1][j];
						if (game.face.data[m][j] == 1) {
							game.CursorJump(2 * j, m);
							game.color(game.face.color[m - 1][j]);
							std::cout << "■";
						}
						else if (game.face.data[m][j] == 0) {
							game.CursorJump(2 * j, m);
							std::cout << "  ";
						}

					}
					if (sum == 0)//该判断条件不要放在上一个循环内部，循环每次逐个进行，sum所需要的值是，一行循环后的
						return 1;//没有方块，则返回，退出循环
				}
			}
			int mark = 0;
			for (int j = 1; j < game.COLS - 1; j++) {
				if (game.face.data[1][j] == 1) {
					mark = 1;
					break;
				}
			}
			if (mark == 1) {
				Sleep(1000); 
				system("cls"); 
				game.color(7);
				game.CursorJump(2 * (game.COLS / 3), game.LINES / 2 - 3);
				std::cout << "GAME OVER";
				Sleep(1000);
				system("cls");
				game.color(7);
				game.CursorJump(2 * (game.COLS / 3), game.LINES / 2 - 3);
				if (grade > max)
				{
					std::cout << "恭喜你打破历史记录，最高记录更新为" << grade;
					WriteGrade();
				}
				else if (grade == max)
				{
					std::cout << "与最高记录持平，加油再创佳绩";
				}
				else
				{
					std::cout << "请继续加油，当前与最高记录相差" << max - grade;
				}
				while (1) {
					char ch;
					game.CursorJump(2 * (game.COLS / 3), game.LINES / 2 + 3);
					std::cout << "再来一局?(y/n):";
					std::cin >> ch;
					if (ch == 'y' || ch == 'Y')
					{
						system("cls");
						main();
					}
					else if (ch == 'n' || ch == 'N')
					{
						game.CursorJump(2 * (game.COLS / 3), game.LINES / 2 + 5);
						exit(0);
					}
					else
					{
						game.CursorJump(2 * (game.COLS / 3), game.LINES / 2 + 4);
						std::cout << "选择错误，请再次选择";
					}
				}
			}

	}
	return 0;
}
void process::ReadGrade()
{
	FILE* pf = fopen("max score.txt", "r"); 
	if (pf == NULL) 
	{
		pf = fopen("max score.txt", "w"); 
		fwrite(&grade, sizeof(int), 1, pf); 
	}
	fseek(pf, 0, SEEK_SET); 
	fread(&max, sizeof(int), 1, pf); 
	fclose(pf); 
	pf = NULL; 
}

void process::WriteGrade()
{
	FILE* pf = fopen("max score.txt", "w");
	if (pf == NULL) 
	{
		printf("保存失败\n");
		exit(0);
	}fwrite(&grade, sizeof(int), 1, pf); 
	fclose(pf); 
	pf = NULL; 
}

