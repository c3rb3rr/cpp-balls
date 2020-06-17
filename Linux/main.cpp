#include "Game.h"

int main()
{
	//inicjalizuje losowy seed (ctime w Game.h)
	srand(static_cast<unsigned>(time(0)));

	//inicjalizuje game object
	Game game;

	//Game loop
	while (game.running())
	{
		game.update();
		game.render();
	}

	//koniec aplikacji
	return 0;
}