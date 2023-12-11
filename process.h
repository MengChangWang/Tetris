#pragma once
#include "prepare.h"
#include <conio.h>
#include <cstdlib>

#define DOWN 80 //���������
#define LEFT 75 //���������
#define RIGHT 77 //���������

#define SPACE 32 //�ո��
#define ESC 27 //Esc��

class process {
public:
	void EnterFace();
	void BlockControl();
	void DrawBlock(int x,int y,int shape,int form);
	void DrawSpace(int x,int y,int shape,int form);
	int Islegal(int x, int y, int shape, int form);
	int BlockRemove(int &grade,int &max);//��鷽�鲻���ƶ�ʱ�Ƿ���������Ҫ��(���ô��ݣ��޸Ĵ���Ĳ�����ֵ)
	void ReadGrade();
	void WriteGrade();

	static const int COLS = 20;
	static const int LINES = 29;

	struct Face {
		int data[LINES][COLS + 10];
		int color[LINES][COLS + 10];
	}face;

};
