#include "Game.h"

int main() {
	// Creating an initialization of the game
	SnakeGame game(1);

	// Initializing the game window
	game.initWindow();

	// Game loop
	while (game.running())
	{
		// Updates game state
		game.Update();

		// displays the game
		game.Render();
	}

	return 0;
}