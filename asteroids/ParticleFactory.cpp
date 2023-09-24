#include "ParticleFactory.h"

std::shared_ptr<Particle> ParticleFactory::createParticle(GlobalConfig::PARTICLES type, sf::Vector2f position, sf::Vector2f orientation)
{
	switch (type)
	{
		case GlobalConfig::PARTICLES::EXPLOSION_PIXEL:
		{
			float deg = rand() % 360;
			orientation = rotateVectorByAngle(orientation, degToRad(deg));
			sf::Vector2f velocity = orientation * 500.f;
			std::shared_ptr<Particle> object = std::make_shared<Particle>(position, velocity);

			return object;
			break;
		}
		case GlobalConfig::PARTICLES::DEBRIS_PIXEL:
		{
			float deg = rand() % 360;
			orientation = rotateVectorByAngle(orientation, degToRad(deg));
			sf::Vector2f velocity = orientation * (rand()%15 + 10.f);
			std::shared_ptr<Particle> object = std::make_shared<Particle>(position, velocity, 20.f, sf::Color::White);

			return object;

			break;
		}
	}
}