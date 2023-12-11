#include "prepare.h"

void prepare::CursorJump(int x, int y) {
	COORD pos;
	pos.X = x;
	pos.Y = y;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(handle, pos);
}

void prepare::color(int x) {
	switch (x)
	{
	case 0:
		x = 14;
		break;
	case 1:
		x = 13;
		break;
	case 2:
		x = 12;
		break;
	case 3:
		x = 11;
		break;
	case 4:
		x = 10;
		break;
	case 5:
		x = 9;
		break;
	case 6:
		x = 8;
		break;
	default:
		x = 7;
		break;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
}

void prepare::InitFace() {


	color(7);
	for (int i = 0; i < LINES; i++) {
		for (int j = 0; j < COLS + 10; j++) {
			if (j == COLS - 1 || j == 0 || j == COLS + 9) {
				face.data[i][j] = 1;
				CursorJump(2 * j, i);
				std::cout << "■";
			}
			else if (i == LINES - 1) {
				face.data[i][j] = 1;
				std::cout << "■";
			}
			else
				face.data[i][j] = 0;
		}
	}
	for (int j = COLS; j < COLS + 9; j++)
	{
		face.data[8][j] = 1;
		CursorJump(2 * j, 8);
		std::cout<< "■";
	}
	CursorJump(2 * COLS, 1);
	std::cout << "下一个方块：";
	CursorJump(2 * COLS + 4, 10);
	std::cout << "左移：←";
	CursorJump(2 * COLS + 4, 12);
	std::cout << "右移：→";
	CursorJump(2 * COLS + 4, 14);
	std::cout << "加速：↓";
	CursorJump(2 * COLS + 4, 16);
	std::cout << "旋转：空格";
	CursorJump(2 * COLS + 4, 18);
	std::cout << "暂停：S";
	CursorJump(2 * COLS + 4, 20);
	std::cout << "退出：Esc";
	CursorJump(2 * COLS + 4, 22);
	std::cout << "重新开始：R";
	CursorJump(2 * COLS + 4, 24);
	std::cout << "最高纪录：";
	CursorJump(2 * COLS + 4, 26);
	std::cout << "当前分数：";
}
void prepare::HideCursor() {
	CONSOLE_CURSOR_INFO cursor;
	cursor.dwSize = 1;
	cursor.bVisible = false;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(handle, &cursor);
}
void prepare::InitBlock() {

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (i == 1 && j >= 0 && j < 3) {
				block[0][0].space[i][j] = 1;
			}
			else if (i == 2 && j == 1)
				block[0][0].space[i][j] = 1;
			else
				block[0][0].space[i][j] = 0;
		}
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (i > 0 && i <= 3 && j == 1) {
				block[1][0].space[i][j] = 1;
			}
		}
	}
		block[1][0].space[3][2] = 1;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (i > 0 && i <= 3 && j == 1) {
				block[2][0].space[i][j] = 1;
			}
		}
	}
	block[2][0].space[3][0] = 1;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (i == 1 && j >= 0 && j < 2) {
				block[3][0].space[i][j] = 1;
			}
			else if (i == 2 && j >= 1 && j < 3)
				block[3][0].space[i][j] = 1;
			else
				block[3][0].space[i][j] = 0;
		}
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (i == 1 && j >= 1 && j < 3) {
				block[4][0].space[i][j] = 1;
			}
			else if (i == 2 && j >= 0 && j < 2)
				block[4][0].space[i][j] = 1;
			else
				block[4][0].space[i][j] = 0;
		}
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (i == 1 && j > 0 && j < 3) {
				block[5][0].space[i][j] = 1;
			}
			else if (i == 2 && j > 0 && j < 3)
				block[5][0].space[i][j] = 1;
			else
				block[5][0].space[i][j] = 0;
		}
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (i >= 0 && i <= 3 && j == 1) {
				block[6][0].space[i][j] = 1;
			}
			else
				block[6][0].space[i][j] = 0;
		}
	}

	for (int shape = 0; shape < 7; shape++) {
		for (int form = 0; form < 3; form++) {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					block[shape][form + 1].space[i][j] = block[shape][form].space[3 - j][i];
				}
			}
		}
	}
}
