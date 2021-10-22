#include "main.h"
int main(int argc, char* argv[])
{
	Game* game = new Game("DOD", 1000, 1000, false);

	game->GameLoop();

	return 0;
}