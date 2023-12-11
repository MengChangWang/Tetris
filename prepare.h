#pragma once
#pragma warning (disable:4996)
#include<iostream>
#include<windows.h>
#include<cstdlib>



class prepare {
public:
	static const int COLS = 20;
	static const int LINES = 29;

	struct Face {
		int data[LINES][COLS + 10];
		int color[LINES][COLS + 10];
	}face;

	struct Block {
		int space[4][4];
	}block[7][4];


	void InitFace();
	void InitBlock();
	void HideCursor();
	void color(int x);
	void CursorJump(int x, int y);
	
	
};