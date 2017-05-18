#include "Game.h"
using namespace sf;

Game::Game() {
	window = new RenderWindow(VideoMode(600, 800), "My Game");

	player = new RectangleShape(Vector2f(16, 16));
	player->setFillColor(Color::Black);
	player->setOutlineColor(Color::White);
	player->setOutlineThickness(2);
	player->setOrigin(0, 0);
	player->setPosition(300, 700);

	ground = new RectangleShape(Vector2f(window->getSize().x*2, 2));
	ground->setFillColor(Color::White);
	ground->setOrigin(0, 0);
	ground->setPosition(0, 717);

	playerSpeed = 400;
	jumpSpeed = 400;
	gravity = 10;
	isOnGround = true;
	wasOnGround = true;
	verticalVelocity = 0;
}

Game::~Game() {
	delete player;
}

void Game::run() {
	sf::Clock inputTimer;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const sf::Time timePerFrame = sf::seconds(1.f/60.f);

	while (window->isOpen()) {
		processInput();
		timeSinceLastUpdate += inputTimer.restart();
		while (timeSinceLastUpdate > timePerFrame) {
			timeSinceLastUpdate -= timePerFrame;
			processInput();
			updateLogic(timePerFrame);
		}
		render();
	}
}

void Game::processInput() {
	Event event;
	while (window->pollEvent(event)) {
		switch (event.type) {
		case Event::KeyPressed:
			handlePlayerInput(event.key.code, true);
			break;
		case Event::KeyReleased:
			handlePlayerInput(event.key.code, false);
			break;
		case Event::Closed:
			window->close();
			break;
		}
	}
}

void Game::updateLogic(Time dt) {

	if (!isReversing) {
		player->setFillColor(Color::Black);
		position.push_back(player->getPosition());
		if (position.size() > 30000) position.erase(position.begin(), position.begin() + 1);
		Vector2f movement(0, 0);

		float horizontalVelocity = playerSpeed*(dt.asSeconds());

		if (isMovingLeft) movement.x -= horizontalVelocity;
		if (isMovingRight) movement.x += horizontalVelocity;

		if (wasOnGround && !isOnGround) {
			verticalVelocity = -jumpSpeed*(dt.asSeconds());
			wasOnGround = false;
		}

		verticalVelocity += gravity*(dt.asSeconds());

		if (!wasOnGround && isOnGround) {
			verticalVelocity = 0;
			wasOnGround = true;
		}

		movement.y = verticalVelocity;
		player->move(movement);

		checkBounds(player);
	}
	else {
		if (!position.empty()) {
			player->setFillColor(Color::White);
			player->setPosition(position.back());
			position.erase(position.end() - 1, position.end());
		}
	}
}

void Game::checkBounds(RectangleShape* obj) {
	std::bitset<4> bound;
	//0 for right, 1 for left, 2 for down, 3 for up

	Vector2f position = obj->getPosition();
	Vector2f groundPosition = ground->getPosition();
	Vector2u windowSize = window->getSize();
	Vector2f size = obj->getSize();

	int offset = 1;

	if (position.x > windowSize.x - size.x - offset) bound.set(0);
	if (position.x < offset) bound.set(1);
	if (position.y > groundPosition.y - size.y - offset) {
		bound.set(2);
		isOnGround = true;
	}
	if (position.y < offset) bound.set(3);

	if (bound.count() == 1) {
		if (bound[0]) obj->setPosition(windowSize.x - size.x - offset, position.y);
		else if (bound[1]) obj->setPosition(offset, position.y);
		else if (bound[2]) obj->setPosition(position.x, groundPosition.y - size.y - offset);
		else if (bound[3]) obj->setPosition(position.x, offset);
	}
	else if (bound.count() == 2) {
		if (bound[0] && bound[2]) obj->setPosition(windowSize.x - size.x - offset, groundPosition.y - size.y - offset);
		else if (bound[0] && bound[3]) obj->setPosition(windowSize.x - size.x - offset, offset);
		else if (bound[1] && bound[2]) obj->setPosition(offset, groundPosition.y - size.y - offset);		
		else if (bound[1] && bound[3]) obj->setPosition(offset, offset);
	}

}

void Game::handlePlayerInput(Keyboard::Key key, bool isPressed) {

	switch (key) {
	case Keyboard::A:
		isMovingLeft = isPressed;
		break;
	case Keyboard::D:
		isMovingRight = isPressed;
		break;
	case Keyboard::Space:
		if (wasOnGround && isOnGround) isOnGround = false;
		break;
	case Keyboard::LShift:
		isReversing = isPressed;
		break;
	}

}

void Game::render() {
	window->clear(Color::Black);
	window->draw(*ground);
	window->draw(*player);
	window->display();
}
