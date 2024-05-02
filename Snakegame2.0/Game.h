#pragma once

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp> //Main library used for the code

//Namespaces' to make for a more smoother looking code
using namespace sf;
using namespace std;

class SnakeGame {
protected:
	RenderWindow* window;       //Pointer to the game window
	VideoMode videoMode;        //Sets the type of window style
	Event ev;                   //Object for handling our events/polling
	int SnakeX, SnakeY;         //Coordinates of the snake's head
	int fruitX, fruitY;         //Coordinates of the fruit
	int obstacleCount;          //Count of obstacles on screen
	int prevX, prevY;           //Previous coordinates of the snake's head
	int score;                  //Keeps track of player's score
	vector<int> tailX, tailY;   //Coordinates of the snake's tail segments
	enum Direction { left, right, up, down }; //Enum for snake movement direction
	Direction direction;        //Saves the current direction of snake movement
	const int width = 39;       //Width of the game area (also changes out of bounds border)
	const int height = 29;      //Height of the game area (also changes out of bounds border)
	bool gameOver;              //Bool  indicating if game over state
	vector<pair<int, int>> obstacles;  //Vector to store coordinates of the obstacles

public:

	SnakeGame(int diff);				   //Constructor to initialize game variables
	~SnakeGame();						   //Destructor to clean up window memory
	const bool running() const;            //Checks if game is running
	void initVariables();                  //Initialize window pointer
	void initWindow();                     //Initialize game window
	bool checkCollision(int x, int y);     //Checks for collisions with self, obsticals, walls
	void SnakeState();                     //Helps controll snake logic
	void ProcessSnakeDevelopment();        //Allows for snake to have a head and a body
	void Fruit_ObsticalDevlopment();       //Process our fruit and obstical rendering
	void displayGameOverScreen();          //Displays the game over screen
	void KeyPress();                       //Maps the movement keys
	void GameSpeed();                      //Controlls game update time
	void Update();                         //Update game state
	void Render();                         //Render game graphics
};
