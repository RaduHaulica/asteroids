#include "GameObject.h"

GameObject::GameObject():
	m_type { GlobalConfig::OBJECTS::GENERIC}
{
	;
}

GameObject::GameObject(sf::Vector2f origin) :
	m_position { origin },
	m_type { GlobalConfig::OBJECTS::GENERIC}
{
	;
}

void GameObject::update(float dt)
{
	m_velocity += (m_acceleration * dt);
	if (norm(m_velocity) > m_maxVelocity)
	{
		m_velocity = m_maxVelocity * normalize(m_velocity);
	}
	m_position += (m_velocity * dt);

	m_graphicsComponent.update(dt);
	m_colliderComponent.update(dt);

	if (m_position.x < GlobalConfig::BOUNDARY_MIN_X - 20.f || m_position.x > GlobalConfig::BOUNDARY_MAX_X + 20.f || m_position.y < GlobalConfig::BOUNDARY_MIN_Y - 20.f || m_position.y > GlobalConfig::BOUNDARY_MAX_Y + 20.f)
	{
		m_markedForDeath = true;
	}
}

void GameObject::collide()
{
	m_velocity = -m_velocity;
}

void GameObject::render()
{
	m_colliderComponent.render();
}

void GameObject::rotate(float angle)
{
	m_orientation = rotateVectorByAngle(m_orientation, angle);
	m_graphicsComponent.rotate(angle);
	m_colliderComponent.rotate(angle);
}

void GameObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_graphicsComponent);
	if (GlobalConfig::DEBUG_MODE)
	{
		target.draw(m_colliderComponent);
	}
}