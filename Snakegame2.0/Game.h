#pragma once
#define NOMINMAX
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class SnakeGame {
protected:
	// Member Variables
	RenderWindow* window;
	VideoMode videoMode;
	Event ev;
	bool gameOverDisplayed;

	int SnakeX, SnakeY;
	int fruitX, fruitY;
	int obstacleCount;
	int prevX = SnakeX;
	int prevY = SnakeY;
	int prev2X, prev2Y;
	int score;
	vector<int> tailX, tailY;
	enum Direction { left, right, up, down };
	Direction direction;
	const int width = 39;
	const int height = 29;
	bool gameOver;
	int x, y;
	vector<pair<int, int>> obstacles;

public:
	// Constructor and Destructor
	SnakeGame(int diff);
	~SnakeGame();
	const bool running() const;
	void initVariables();
	void initWindow();
	bool checkCollision(int x, int y);
	void SnakeState();
	void ProcessSnakeDevelopment();
	void Fruit_ObsticalDevlopment();
	void displayGameOverScreen();
	void KeyPress();
	void GameSpeed();
	// Public Member Functions

	void Update();
	void Render();
};
