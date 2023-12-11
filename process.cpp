#include "process.h"
#include "main.h"

prepare game;
int max = 0; int grade = 0;
process Game;

void process::EnterFace() {
	game.color(7);
	game.CursorJump(game.COLS / 2, game.LINES / 2 - 4);

	std::cout << "   ��ӭ��������˹����\n\n	  �Ƿ�ʼ��Ϸ ��(y) ��(n)";
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
			std::cout << "�����������������";
		}
		
	}
}

void process::BlockControl() {
	game.color(7);
	game.CursorJump(2 * game.COLS + 14, game.LINES - 5);
	std::cout << max;//չʾ����
	srand(time(NULL));
	int shape = rand() % 7;
	int form = rand() % 4;

	game.InitFace();
	game.InitBlock();//��һ���޸ĳ������chu

	while (1) {
		int x = game.COLS / 2 - 2; int y = 0;
		int nextshape = rand() % 7; int nextform = rand() % 4;
		DrawBlock(game.COLS + 3, 3,nextshape,nextform);
		while (1) {
			DrawBlock(x, y, shape, form);
			int t = 8888;
			while (--t) {  //t-- �� --t ���
				if (kbhit() != 0) //�������˼��̣�����t���ټ���
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
			else//���� �����ƶ�
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
					std::cout << "��Ϸ������лл�������";
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
				std::cout << "��";
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
	return 1; //�޸Ĵ� ע��λ��
}//�ж��Ƿ�Ӵ�������

//��鷽�鲻���ƶ�ʱ�Ƿ���������Ҫ��
int process::BlockRemove(int &grade,int &max) {

	//�����һ�п�ʼ���������ÿ�з������Ŀ
	for (int i = game.LINES - 2; i > 4; i--) {
		int sum = 0;
		for (int j = 1; j < game.COLS - 1; j++) {
			sum += game.face.data[i][j];
		}
			if (sum == 0)
				break;//�����ϸ�����˵���ѵ��ѷŷ������߲����һ��
			if (sum == game.COLS - 2) {
				grade += 10;
				game.color(7);
				game.CursorJump(2 * game.COLS + 14, game.LINES - 3);
				std::cout << grade;//չʾ����
				for (int j = 1; j < game.COLS - 1; j++) {
					game.face.data[i][j] = 0;
					game.CursorJump(2 * j, i);
					std::cout << "  ";
				}//��������еķ���
				//����������ϵķ�������
				for (int m = i; m > 1; m--) {
					int sum = 0;//��¼��������ϲ��ÿ��ķ�����Ŀ
					for (int j = 1; j < game.COLS - 1; j++) {
						sum += game.face.data[m - 1][j];


						game.face.data[m][j] = game.face.data[m - 1][j];
						game.face.color[m][j] = game.face.color[m - 1][j];
						if (game.face.data[m][j] == 1) {
							game.CursorJump(2 * j, m);
							game.color(game.face.color[m - 1][j]);
							std::cout << "��";
						}
						else if (game.face.data[m][j] == 0) {
							game.CursorJump(2 * j, m);
							std::cout << "  ";
						}

					}
					if (sum == 0)//���ж�������Ҫ������һ��ѭ���ڲ���ѭ��ÿ��������У�sum����Ҫ��ֵ�ǣ�һ��ѭ�����
						return 1;//û�з��飬�򷵻أ��˳�ѭ��
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
					std::cout << "��ϲ�������ʷ��¼����߼�¼����Ϊ" << grade;
					WriteGrade();
				}
				else if (grade == max)
				{
					std::cout << "����߼�¼��ƽ�������ٴ��Ѽ�";
				}
				else
				{
					std::cout << "��������ͣ���ǰ����߼�¼���" << max - grade;
				}
				while (1) {
					char ch;
					game.CursorJump(2 * (game.COLS / 3), game.LINES / 2 + 3);
					std::cout << "����һ��?(y/n):";
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
						std::cout << "ѡ��������ٴ�ѡ��";
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
		printf("����ʧ��\n");
		exit(0);
	}fwrite(&grade, sizeof(int), 1, pf); 
	fclose(pf); 
	pf = NULL; 
}

