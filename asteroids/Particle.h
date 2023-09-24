#pragma once

#include <SFML/Graphics.hpp>

class Particle : public sf::Drawable
{
public:
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	float m_elapsedTime;
	float m_lifetime;
	sf::Color m_color;
	bool m_markedForDeath;
	sf::VertexArray va;

	Particle(sf::Vector2f position, sf::Vector2f velocity = { 0.f, 0.f }, float lifetime = 1.0f, sf::Color color = sf::Color::Red);
	void update(float dt);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};