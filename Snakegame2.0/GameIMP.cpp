#include "Game.h"

//Constructor that initializes some variables
SnakeGame::SnakeGame(int diff)
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

//Deconstructor to clear memory from the window pointer
SnakeGame::~SnakeGame()
{
	delete this->window;
}

//Initializes the window pointer
void SnakeGame::initVariables()
{
	this->window = nullptr;
}

//Sets the stle, width, and height of the window
void SnakeGame::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	this->window = new RenderWindow(this->videoMode, "Snake Game", Style::Titlebar | Style::Close);
}

//Checks to see if the game is running via the open window, used in main
const bool SnakeGame::running() const
{
	return this->window->isOpen();
}

//Function that checks to see if the snake has hit any endpoints
bool SnakeGame::checkCollision(int x, int y)
{	//checks for collision from the obstacles
	for (const auto& obstacle : obstacles)
	{
		if (x == obstacle.first && y == obstacle.second)
		{
			return true;
		}
	}
	//Makes sure that the snake can't hit itself
	for (size_t i = 0; i < tailX.size(); i++)
	{
		if (x == tailX[i] && y == tailY[i])
		{
			return true;
		}
	}
	//Border to make sure the snake cant escape
	if (SnakeX < 0 || SnakeY < 0 || SnakeX >= width + 1 || SnakeY >= height + 1)
	{
		return true;
	}

	return false;
}

//Stores the snakes position to keep track of his X and Y movements so things dont spawn within the snake
void SnakeGame::SnakeState()
{
	if (!tailX.empty())
	{
		prevX = tailX.back();
		prevY = tailY.back();
		for (size_t i = tailX.size() - 1; i > 0; i--)
		{
			tailX[i] = tailX[i - 1];
			tailY[i] = tailY[i - 1];
		}
		tailX[0] = SnakeX;
		tailY[0] = SnakeY;
	}

	//Helps to controll the snakes movement and set the direction of each "direction"
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
}

//Sets the shape of the snake, the color, and the size
void SnakeGame::ProcessSnakeDevelopment()
{
	//Draws the snake's head
	RectangleShape snakeHead(Vector2f(20, 20));
	snakeHead.setFillColor(Color::Green);
	snakeHead.setPosition(SnakeX * 20, SnakeY * 20);
	snakeHead.setOutlineThickness(1);
	snakeHead.setOutlineColor(Color::Black);
	this->window->draw(snakeHead);

	//Draws the snake's tail
	for (size_t i = 0; i < tailX.size(); i++)
	{
		RectangleShape snakePart(Vector2f(20, 20));
		snakePart.setFillColor(Color::Green);
		snakePart.setOutlineThickness(1);
		snakePart.setOutlineColor(Color::Black);
		snakePart.setPosition(tailX[i] * 20, tailY[i] * 20);
		this->window->draw(snakePart);
	}
}

//Sets our fruit and obstical size, shape, and color
void SnakeGame::Fruit_ObsticalDevlopment()
{
	CircleShape fruit(10);
	fruit.setFillColor(Color::Red);
	fruit.setPosition(fruitX * 20, fruitY * 20);
	this->window->draw(fruit);

	//Draws our obsticls that we can hit
	for (const auto& obstacle : obstacles)
	{
		//Sets the size ans shape (size [ppi], number of edges)
		CircleShape obs(10, 4);
		obs.setFillColor(Color::Black);
		obs.setPosition(obstacle.first * 20, obstacle.second * 20);
		this->window->draw(obs);
	}

	//Function that checks if fruit was eating, if so it increases score
	if (SnakeX == fruitX && SnakeY == fruitY)
	{
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;

		//Creates another piece of the tail with the push_back function
		tailX.push_back(prevX);
		tailY.push_back(prevY);

		//Spawns another obstical if score is divisable by 30
		if (score % 30 == 0)
		{
			obstacles.push_back(make_pair(rand() % width, rand() % height));
			obstacleCount++;
		}
	}
}

//Our game over screen that displays at the end of each game to show score and # of obsticals
void SnakeGame::displayGameOverScreen()
{
	this->window->close();
	cout << "Game Over! x_x" << endl;
	cout << "Score: " << score << endl;
	cout << "Obstacles Avoided: " << obstacleCount << endl;
}

//This function continuously checks the status of a condition in a program by repeatedly checking the state at regular intervals
void SnakeGame::KeyPress()
{
	while (this->window->pollEvent(this->ev))
	{
		//Makes sure that our key presses are mapped to speciefic keys
		switch (this->ev.type)
		{
		case Event::Closed:
			this->window->close();
			break;
		case Event::KeyPressed:
			switch (this->ev.key.code)
			{
				//Makes sure the snake cant turn into himself by going in the oposite direction
			case Keyboard::A:
				if (direction != right)
					direction = left;
				break;
			case Keyboard::D:
				if (direction != left)
					direction = right;
				break;
			case Keyboard::W:
				if (direction != down)
					direction = up;
				break;
			case Keyboard::S:
				if (direction != up)
					direction = down;
				break;
			}

			//Closes the game if 'q' is pressed
			if (this->ev.key.code == Keyboard::Q)
			{
				this->window->close();
				displayGameOverScreen();
			}
			break;
		}
	}
}

//Sets the speed or difficulty of the game based on our updateInterval
void SnakeGame::GameSpeed()
{
	static Clock clock;

	Time elapsed = clock.getElapsedTime();

	double elapsedSeconds = elapsed.asSeconds();

	double updateInterval = 0.09f;

	//Makes sure that the other functions Operate on the same time scale
	if (elapsedSeconds >= updateInterval)
	{
		KeyPress();
		SnakeState();
		clock.restart();
	}
}

//Runs most of the functions and keeps everything on the screen refreshed
void SnakeGame::Update()
{
	GameSpeed();
	//Makes sure that if there is a collision it is captured
	if (checkCollision(SnakeX, SnakeY))
	{
		gameOver = true;
	}
	//If gameOver = true then this will display the game over screen
	if (gameOver)
	{
		displayGameOverScreen();
	}
}

//Refreshes the window content
void SnakeGame::Render()
{
	//Resets the window so there is no mix up
	this->window->clear(Color::White);

	//A loop to make sure everything is operating while the game is still going
	if (!gameOver)
	{
		ProcessSnakeDevelopment();
		Fruit_ObsticalDevlopment();
	}
	this->window->display();
}