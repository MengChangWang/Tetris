#include"prepare.h"
#include"process.h"

int main(void) {
	system("title ¶íÂÞË¹·½¿é");
	system("mode con: cols=60 lines=29");
	prepare Game;
	process game;
	game.ReadGrade();
	game.EnterFace();
	Game.HideCursor();
	Game.InitFace();
	game.BlockControl();
	return 0;
}