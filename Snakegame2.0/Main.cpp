#include "Game.h"

int main() {

    srand(time(nullptr));

    // Create an instance of SnakeGame
    SnakeGame game(100); // Adjust difficulty here

    // Initialize SFML window
    game.initWindow();

    // Game loop
    while (game.running())
    {
        // Update game state
        game.Update();

        // Render game
        game.Render();
    }

    return 0;

    return 0;
}
