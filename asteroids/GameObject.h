#pragma once

#include "Interfaces.h"

#include "GraphicsComponent.h"
#include "ColliderComponent.h"
#include "Config.h"
#include "MessageQueue.h"

class GameObject : public Updatable, public Body, public sf::Drawable
{
public:
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	sf::Vector2f m_acceleration;
	sf::Vector2f m_orientation;
	GlobalConfig::OBJECTS m_type;

	float m_maxVelocity{ 200.f };
	float m_maxAcceleration { 100.f };
	float m_maxRotationSpeed{ 3.14159f };

	bool m_markedForDeath{ false };

	GraphicsComponent m_graphicsComponent = GraphicsComponent(this);
	ColliderComponent m_colliderComponent = ColliderComponent(this);

	GameObject();
	GameObject(sf::Vector2f origin);
	void update(float dt);
	void render();
	void collide();
	void rotate(float dt);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};