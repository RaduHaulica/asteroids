#include "Particle.h"

Particle::Particle(sf::Vector2f position, sf::Vector2f velocity, float lifetime, sf::Color color) :
	m_position{ position },
	m_velocity{ velocity },
	m_elapsedTime{ 0.f },
	m_lifetime{ lifetime },
	m_color{ color },
	m_markedForDeath{ false }
{
	va.setPrimitiveType(sf::PrimitiveType::Points);
}

void Particle::update(float dt)
{
	m_elapsedTime += dt;
	m_position += m_velocity * dt;

	if (m_elapsedTime > m_lifetime)
	{
		m_markedForDeath = true;
	}
	else
	{
		va.clear();
		va.append(sf::Vertex(m_position, m_color));
	}
}

void Particle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(va);
}