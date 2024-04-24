#include <iostream>
#define NOMINMAX
#include <windows.h>
#include <conio.h>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

using namespace sf;
using namespace std;



class SnakeGame {
protected:
    RenderWindow* window;

    VideoMode videoMode;
    Event ev;

    int SnakeX, SnakeY;
    int fruitX, fruitY;
    int score;
    vector<int> tailX, tailY;
    enum Direction { left, right, up, down };
    Direction direction;
    const int width = 30;
    const int height = 10;
    bool gameOver;
    int gameSpeed;
    int x, y;
    vector<pair<int, int>> obstacles;
    int obstacleCount;

public:
    SnakeGame(int diff);

    void Body(string playerName);

    void EatingFruit();

    //void Keys();

    //void Program(string playerName);

    const bool running() const;

    void Update();

    void Render();

    void pollEvents();

    ~SnakeGame();

    void initVariables();

    void initWindow();

};


