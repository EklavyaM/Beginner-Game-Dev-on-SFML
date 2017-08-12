/*
 * Particle.h
 *
 *  Created on: Jul 8, 2017
 *      Author: kladspear
 */

#ifndef SOURCE_HEADERS_PARTICLE_H_
#define SOURCE_HEADERS_PARTICLE_H_

#include "stdafx.h"

class Particle{
public:
	sf::Vector2f _velocity;
	sf::Vector2f _position;
	sf::Color _color;

	Particle(sf::Vector2f initial_position, sf::Color initial_color);
};


#endif /* SOURCE_HEADERS_PARTICLE_H_ */
