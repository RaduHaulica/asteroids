#pragma once

#include "Config.h"
#include "Utility.h"
#include "Particle.h"

class ParticleFactory
{
public:
	std::shared_ptr<Particle> createParticle(GlobalConfig::PARTICLES type, sf::Vector2f position, sf::Vector2f orientation = { 0.f, 0.f });
};