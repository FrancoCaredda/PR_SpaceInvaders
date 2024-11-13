#include "Game.h"

int main(void)
{
	Game game;

	game.Init();
	game.Start();
	game.Run();
	game.End();

	return 0;
}