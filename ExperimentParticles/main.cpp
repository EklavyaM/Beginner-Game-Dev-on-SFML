#include<SFML/Graphics.hpp>
#include<cmath>
#include<iostream>
#include<random>

using namespace sf;
using namespace std;

class Particle{
private:
	Vector2f _center;

	CircleShape _shape;

	const double _RADIUSX;
	const double _RADIUSY;
	const double _SPEEDX;
	const double _SPEEDY;

	double _angleX;
	double _angleY;

public:

	Particle(Vector2f pos, Vector2f cen, double radx, double rady, double shapeRad, double speedX, double speedY, Color color):
		_RADIUSX(radx),
		_RADIUSY(rady),
		_SPEEDX(speedX),
		_SPEEDY(speedY)
		{

		_center = cen;

		_shape.setFillColor(color);
		_shape.setRadius(shapeRad);
		_shape.setPosition(pos);
		_shape.setOrigin(Vector2f(_shape.getRadius(),_shape.getRadius()));

	}

	void update(){
		Vector2f offset(_RADIUSX*cos(_angleX), _RADIUSY*sin(_angleY));
		_shape.setPosition(_center+offset);
		_angleX+=_SPEEDX;
		_angleY+=_SPEEDY;
	}

	CircleShape& getSprite(){
		return _shape;
	}

};

int main(){

	int roomWidth = 1600, roomHeight = 900;
	RenderWindow window(VideoMode(roomWidth,roomHeight),"Sup");
	window.setFramerateLimit(60);

	int numOfParticles = 5000;
	int maxArc = 50;
	int maxRadius = 10;
	float maxSpeed = 0.02;

	random_device rd;
	mt19937 e2(rd());
	uniform_int_distribution<> randomWidth(0,roomWidth);
	uniform_int_distribution<> randomHeight(0,roomHeight);
	uniform_real_distribution<> randomRadiusX(1,maxArc);
	uniform_real_distribution<> randomRadiusY(1,maxArc);
	uniform_real_distribution<> randomShapeRadius(1,maxRadius);
	uniform_real_distribution<> randomVelocityX(0,maxSpeed);
	uniform_real_distribution<> randomVelocityY(0,maxSpeed);
	uniform_int_distribution<> randomR(0,255);
	uniform_int_distribution<> randomG(0,255);
	uniform_int_distribution<> randomB(0,255);
	uniform_int_distribution<> randomA(100,200);

	float randomPosX;
	float randomPosY;
	float randomCenX;
	float randomCenY;
	float randomSpeedX;
	float randomSpeedY;
	float randomArcX;
	float randomArcY;
	float randomRadius;

	Particle* particle[numOfParticles];
	Color c;

	for(int i=0;i<numOfParticles;i++){

		randomPosX = randomWidth(e2);
		randomPosY = randomHeight(e2);
		randomCenX = randomWidth(e2);
		randomCenY = randomHeight(e2);
		randomArcX = randomRadiusX(e2);
		randomArcY = randomRadiusY(e2);
		randomSpeedX = randomVelocityX(e2);
		randomSpeedY = randomVelocityY(e2);
		randomRadius = randomShapeRadius(e2);

		c.r = randomR(e2);
		c.g = randomG(e2);
		c.b = randomB(e2);
		c.a = randomA(e2);

		particle[i] = new Particle(Vector2f(randomPosX,randomPosY),Vector2f(randomCenX,randomCenY),randomArcX, randomArcY, randomRadius, randomSpeedX,randomSpeedY, c);
	}

	while(window.isOpen()){
		Event event;
		while(window.pollEvent(event)){
			if(event.type == Event::Closed) window.close();
		}
		window.clear(Color::Black);

		for(int i=0;i<numOfParticles;i++){
			particle[i]->update();
			window.draw(particle[i]->getSprite());
		}

		window.display();
	}

	return 0;
}
