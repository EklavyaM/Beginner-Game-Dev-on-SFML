#include "headers/Game.h"

Game::~Game(){}

Game::Game(){
	room_dimensions = sf::Vector2f(1280,720);
	number_of_particles = 150000;

	_window = new sf::RenderWindow(sf::VideoMode(room_dimensions.x,room_dimensions.y),"Particles");

	_generator = new ParticleGenerator(room_dimensions,number_of_particles);
	_particles = new sf::VertexArray(sf::Points,number_of_particles);

	_mouse_position = sf::Vector2f(room_dimensions.x/2,room_dimensions.y/2);
}


void Game::_processInput(){
	sf::Event event;
	while(_window->pollEvent(event)){
		switch(event.type){
		case sf::Event::Closed:
			_window->close();
			break;
		case sf::Event::MouseMoved:
			_mouse_position = static_cast<sf::Vector2f>(sf::Mouse::getPosition(*_window));
			break;
		case sf::Event::MouseLeft:
			_mouse_position = sf::Vector2f(room_dimensions.x/2,room_dimensions.y/2);
		}
	}
}

void Game::_update(sf::Time dt){
	const std::list<Particle*> &p = _generator->getParticles();

	_generator->update(_mouse_position,dt);

	int i=0;
	for(Particle* temp:p){
		(*_particles)[i].position = temp->_position;
		(*_particles)[i].color = temp->_color;
		i++;
	}

}

void Game::_render(){
	_window->clear();
	_window->draw(*_particles);
	_window->display();
}

void Game::run(){
	sf::Clock game_clock;
	sf::Time time_per_frame = sf::seconds(1.f/30.f);
	sf::Time time_since_last_update = sf::Time::Zero;

	while(_window->isOpen()){
		_processInput();
		time_since_last_update += game_clock.restart();

		while(time_since_last_update>time_per_frame){
			time_since_last_update -= time_per_frame;
			_processInput();
			_update(time_per_frame);
		}

		sf::sleep(sf::Time(sf::seconds(0.01)));

		_render();
	}
}
