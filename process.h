#pragma once
#include "prepare.h"
#include <conio.h>
#include <cstdlib>

#define DOWN 80 //方向键：下
#define LEFT 75 //方向键：左
#define RIGHT 77 //方向键：右

#define SPACE 32 //空格键
#define ESC 27 //Esc键

class process {
public:
	void EnterFace();
	void BlockControl();
	void DrawBlock(int x,int y,int shape,int form);
	void DrawSpace(int x,int y,int shape,int form);
	int Islegal(int x, int y, int shape, int form);
	int BlockRemove(int &grade,int &max);//检查方块不能移动时是否满足清行要求(引用传递，修改传入的参数的值)
	void ReadGrade();
	void WriteGrade();

	static const int COLS = 20;
	static const int LINES = 29;

	struct Face {
		int data[LINES][COLS + 10];
		int color[LINES][COLS + 10];
	}face;

};
