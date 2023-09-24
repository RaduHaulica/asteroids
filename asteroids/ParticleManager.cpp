#include "ParticleManager.h"

void ParticleManager::update(float dt)
{
	for (int i = 0; i < m_particles.size(); i++)
	{
		m_particles[i]->update(dt);

		if (m_particles[i]->m_markedForDeath)
		{
			m_particles.erase(m_particles.begin() + i);
			i--;
		}
	}
}

void ParticleManager::addParticle(std::shared_ptr<Particle> particle)
{
	m_particles.push_back(particle);
}

void ParticleManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (int i = 0; i < m_particles.size(); i++)
	{
		target.draw(*m_particles[i]);
	}
}