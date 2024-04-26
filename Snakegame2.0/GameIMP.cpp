#include "Game.h"

SnakeGame::SnakeGame(int diff)
{
	bool gameOverDisplayed = false;
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

SnakeGame::~SnakeGame()
{
	delete this->window;
}

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

const bool SnakeGame::running() const
{
	return this->window->isOpen();
}

bool SnakeGame::checkCollision(int x, int y)
{
	// Check if the given position (x, y) overlaps with any obstacle
	for (const auto& obstacle : obstacles)
	{
		if (x == obstacle.first && y == obstacle.second)
		{
			return true;
		}
	}

	for (size_t i = 0; i < tailX.size(); i++) {
		if (x == tailX[i] && y == tailY[i])
		{
			return true; // Collision detected
		}
	}
	// Border to make sure the snake cant escape
	if (SnakeX < 0 || SnakeY < 0 || SnakeX >= width + 1 || SnakeY >= height + 1)
	{
		return true;
	}

	return false; // No collision detected
}

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

void SnakeGame::ProcessSnakeDevelopment()
{
	// Draws the snake head
	RectangleShape snakeHead(Vector2f(20, 20));
	snakeHead.setFillColor(Color::Green);
	snakeHead.setPosition(SnakeX * 20, SnakeY * 20);
	snakeHead.setOutlineThickness(1);
	snakeHead.setOutlineColor(Color::Black);
	this->window->draw(snakeHead);

	// Draws the snake tail
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

void SnakeGame::Fruit_ObsticalDevlopment()
{
	CircleShape fruit(10);
	fruit.setFillColor(Color::Red);
	fruit.setPosition(fruitX * 20, fruitY * 20);
	this->window->draw(fruit);
	// Draws the obstacles that can be hit
	for (const auto& obstacle : obstacles)
	{
		CircleShape obs(10, 4);
		obs.setFillColor(Color::Black);
		obs.setPosition(obstacle.first * 20, obstacle.second * 20);
		this->window->draw(obs);
	}
	if (SnakeX == fruitX && SnakeY == fruitY)
	{
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		tailX.push_back(prevX);
		tailY.push_back(prevY);
		if (score % 30 == 0)
		{
			obstacles.push_back(make_pair(rand() % width, rand() % height));
			obstacleCount++;
		}
	}
}

void SnakeGame::displayGameOverScreen()
{
	if (!gameOverDisplayed)
	{
		this->window->close();
		cout << "Game Over! x_x" << endl;
		cout << "Score: " << score << endl;
		cout << "Obstacles Avoided: " << obstacleCount << endl;
		gameOverDisplayed = true;
	}
}

void SnakeGame::KeyPress()
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
				if (direction != right) // Prevent reverse to right
					direction = left;
				break;
			case Keyboard::D:
				if (direction != left) // Prevent reverse to left
					direction = right;
				break;
			case Keyboard::W:
				if (direction != down) // Prevent reverse to down
					direction = up;
				break;
			case Keyboard::S:
				if (direction != up) // Prevent reverse to up
					direction = down;
				break;
			}
			if (this->ev.key.code == Keyboard::Q)
			{
				this->window->close();
				displayGameOverScreen();
			}
			break;
		}
	}
}

void SnakeGame::GameSpeed()
{
	// Limit snake movement speed by only updating its position if enough time has passed

	static Clock clock;
	Time elapsed = clock.getElapsedTime(); // Get elapsed time without restarting the clock

	// Convert elapsed time to seconds
	double elapsedSeconds = elapsed.asSeconds();

	// Define the desired interval (e.g., 0.1 seconds)
	double updateInterval = 0.09f;

	if (elapsedSeconds >= updateInterval)
	{
		KeyPress(); // Handle SFML events (e.g., window closing)
		SnakeState(); // Update game state (e.g., snake movement, score)
		clock.restart();
	}
}

void SnakeGame::Update()
{
	GameSpeed();

	if (checkCollision(SnakeX, SnakeY))
	{
		gameOver = true;
	}

	if (gameOver)
	{
		displayGameOverScreen();
	}
}

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
	else
		displayGameOverScreen();
	this->window->display();
}