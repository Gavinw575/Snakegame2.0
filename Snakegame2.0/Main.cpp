#include "Game.h"

int main() {

    srand(time(nullptr));

  
    SnakeGame game(100); 

 
    game.initWindow();

   
    while (game.running())
    {
     
        game.Update();

        game.Render();
    }

    return 0;

    return 0;
}
