#pragma once

#include "stdafx.h"

class Game {
public:
	void run();
	Game();
	~Game();
private:
	void processInput();
	void updateLogic(sf::Time dt);
	void render();
	void checkBounds(sf::RectangleShape* obj);

	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

	sf::RenderWindow *window;
	sf::RectangleShape *player;
	sf::RectangleShape *ground;

	bool isMovingLeft;
	bool isMovingRight;
	bool isOnGround;
	bool wasOnGround;

	bool isReversing;

	int playerSpeed;
	int jumpSpeed;
	int gravity;
	float verticalVelocity;

	std::vector<sf::Vector2f> position;
};