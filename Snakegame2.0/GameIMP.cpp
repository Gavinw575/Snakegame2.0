#include "Game.h"

void SnakeGame::initVariables()
{
    this->window = nullptr;

}

void SnakeGame::initWindow()
{
    this->videoMode.height = 600;
    this->videoMode.width = 800;

    this->window = new RenderWindow(this->videoMode, "Snake Game", Style::Titlebar | Style::Close);
}


SnakeGame::~SnakeGame()
{
    delete this->window;
}

SnakeGame::SnakeGame(int diff) : gameSpeed(diff)
{
    this->initVariables();
    this->initWindow();
    score = 0;
    gameOver = false;
    fruitX = rand() % width;
    fruitY = rand() % height;
    SnakeX = width / 2;
    SnakeY = height / 2;
    obstacleCount = 0;
}

//Accessors
const bool SnakeGame::running() const
{
    return this->window->isOpen();
}


void SnakeGame::Body(string playerName)
{
    system("cls");
    for (int i = 0; i < width + 2; i++)
        cout << "-";
    cout << endl;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j <= width; j++)
        {
            if (j == 0 || j == width)
                cout << "|";
            if (i == SnakeY && j == SnakeX)
                cout << "*";
            else if (i == fruitY && j == fruitX)
                cout << "#";
            else
            {
                bool printTail = false;
                for (size_t k = 0; k < tailX.size(); k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "~";
                        printTail = true;
                    }
                }
                for (const auto& obstacle : obstacles) {
                    if (obstacle.first == j && obstacle.second == i) {
                        cout << "/"; 
                        printTail = true;
                        break;
                    }
                }

                if (!printTail)
                    cout << " ";
            }
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++)
        cout << "-";
    cout << endl;

    cout << playerName << "'s Score: " << score << endl;
}

void SnakeGame::EatingFruit()
{
    int prevX = SnakeX;
    int prevY = SnakeY;
    int prev2X, prev2Y;
    if (!tailX.empty())
    {
        prevX = tailX[0];
        prevY = tailY[0];
        tailX[0] = SnakeX;
        tailY[0] = SnakeY;
        for (size_t i = 1; i < tailX.size(); i++)
        {
            prev2X = tailX[i];
            prev2Y = tailY[i];
            tailX[i] = prevX;
            tailY[i] = prevY;
            prevX = prev2X;
            prevY = prev2Y;
        }
    }
    switch (direction)
    {
    case left:
        SnakeX--;
        break;
    case right:
        SnakeX++;
        break;
    case up:
        SnakeY--;
        break;
    case down:
        SnakeY++;
        break;
    }

    if (SnakeX >= width || SnakeX < 0 || SnakeY >= height || SnakeY < 0)
        gameOver = true;

    for (size_t i = 0; i < tailX.size(); i++)
    {
        if (tailX[i] == SnakeX && tailY[i] == SnakeY)
            gameOver = true;
    }

    if (SnakeX == fruitX && SnakeY == fruitY)
    {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        tailX.push_back(SnakeX);
        tailY.push_back(SnakeY);
        if (score % 30 == 0)
        {
            obstacles.push_back(make_pair(rand() % width, rand() % height));
            obstacleCount++;
        }
    }
    for (const auto& obstacle : obstacles)
    {
        if (SnakeX == obstacle.first && SnakeY == obstacle.second)
        {
            gameOver = true;
            break;
        }
    }
    
}
//    void SnakeGame::Keys()
//{
//        if (_kbhit())
//        {
//            switch (_getch())
//            {
//            case 'a':
//                direction = left;
//                break;
//            case 'd':
//                direction = right;
//                break;
//            case 'w':
//                direction = up;
//                break;
//            case 's':
//                direction = down;
//                break;
//            case 'q':
//                gameOver = true;
//                break;
//            }
//        }
//}

//void SnakeGame::Program(string playerName)
//{
//    while (!gameOver)
//    {
//        Body(playerName);
//        Keys();
//        EatingFruit();
//        Sleep(gameSpeed);
//    }
//    system("cls");
//    cout << endl << endl << "***************************************" << endl << "Game Over! x_x " << endl << "Score: "
//        << score << endl << "Obsticals Ovoided: " << obstacleCount + 2 << endl << "***************************************" << endl << endl; 
//}

void SnakeGame::pollEvents()
{
    while (this->window->pollEvent(this->ev))
    {

        switch (this->ev.type)
        {


        case Event::Closed:
            this->window->close();
            break;
        case Event::KeyPressed:
            switch (this->ev.key.code)
            {
            case Keyboard::A:
                direction = left;
                break;
            case Keyboard::D:
                direction = right;
                break;
            case Keyboard::W:
                direction = up;
                break;
            case Keyboard::S:
                direction = down;
                break;
            }
            if (this->ev.key.code == Keyboard::Q)
                this->window->close();
            break;

        }



    }

}

void SnakeGame::Update()
{
    pollEvents(); 
    EatingFruit();

}

void SnakeGame::Render()
{
    // Clear old frame
    this->window->clear(Color::Blue); 

    
    // Draw Snake
    Body("Player");
    RectangleShape snakePart(Vector2f(20, 20));
    snakePart.setFillColor(Color::Green);
    snakePart.setPosition(SnakeX * 20, SnakeY * 20);
    this->window->draw(snakePart);

    // Draw Fruit
    RectangleShape fruit(Vector2f(20, 20));
    fruit.setFillColor(Color::Red);
    fruit.setPosition(fruitX * 20, fruitY * 20);
    this->window->draw(fruit);

    // Draw obstacles
    for (const auto& obstacle : obstacles) {
        RectangleShape obs(Vector2f(20, 20));
        obs.setFillColor(Color::Yellow);
        obs.setPosition(obstacle.first * 20, obstacle.second * 20);
        this->window->draw(obs);
    }

    // Display frame in window
    this->window->display();

}

