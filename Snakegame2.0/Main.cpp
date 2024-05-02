#include "Game.h"

int main() {
	//Creates an instance of the game
	SnakeGame game(1);

	//Initlizes the game window
	game.initWindow();

	//Game loop that runs our functions
	while (game.running())
	{
		//Updates the game state
		game.Update();

		game.Render();
	}

	return 0;
}