#pragma once

#include "Particle.h"

class ParticleManager: public sf::Drawable
{
public:
	std::vector<std::shared_ptr<Particle>> m_particles;
	void update(float dt);
	void addParticle(std::shared_ptr<Particle> particle);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};